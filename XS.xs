#define PERL_NO_GET_CONTEXT
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "commands.h"
#include "hiredis/hiredis.h"
#include "hiredis/hiredis_ssl.h"
#include "ppport.h"

// TODO Port these to Devel::PPPort. Copy parts/inc/newRV.
#ifndef av_store_simple
#  define av_store_simple av_store
#endif

#ifndef newAV_alloc_x
#  define newAV_alloc_x(size) ({ AV *av = newAV(); av_extend(av, size); av; })
#endif

typedef struct { SV *sv, *err; } replyTuple;

static replyTuple decodeReply(pTHX_ redisReply* reply) {
    replyTuple tup = {};

    switch (reply->type) {
        case REDIS_REPLY_ARRAY:
        case REDIS_REPLY_SET: {
            AV* const av = newAV_alloc_x(reply->elements);
            tup.sv = sv_2mortal(newRV_noinc((SV*) av));

            for (size_t i = 0; i < reply->elements; i++) {
                // TODO Handle tup.err
                replyTuple tup = decodeReply(aTHX_ reply->element[i]);

                av_store_simple(av, i, SvREFCNT_inc(tup.sv));
            }

            break;
        }
        case REDIS_REPLY_BIGNUM:
        case REDIS_REPLY_STATUS:
        case REDIS_REPLY_STRING:
        case REDIS_REPLY_VERB:
            tup.sv = sv_2mortal(newSVpvn(reply->str, reply->len));
            break;
        case REDIS_REPLY_BOOL:
            tup.sv = boolSV(reply->integer);
            break;
        case REDIS_REPLY_DOUBLE:
            tup.sv = sv_2mortal(newSVnv(strtod(reply->str, NULL)));
            break;
        case REDIS_REPLY_ERROR:
            tup.err = sv_2mortal(newSVpvn(reply->str, reply->len));
            break;
        case REDIS_REPLY_INTEGER:
            tup.sv = sv_2mortal(newSViv(reply->integer));
            break;
        case REDIS_REPLY_MAP: {
            HV *hv = newHV();
            tup.sv = sv_2mortal(newRV_noinc((SV*) hv));

            for (size_t i = 0; i < reply->elements; i += 2) {
                // TODO Handle key.err, val.err
                replyTuple key = decodeReply(aTHX_ reply->element[i]);
                replyTuple val = decodeReply(aTHX_ reply->element[i + 1]);

                if (!hv_store_ent(hv, key.sv, SvREFCNT_inc(val.sv), 0))
                    SvREFCNT_dec(val.sv);
            }

            break;
        }
        case REDIS_REPLY_NIL:
            tup.sv = &PL_sv_undef;
            break;
        default:
            tup.err = sv_2mortal(newSVpvf("Unknown reply type: %d", reply->type));
    }

    return tup;
}

// TODO I feel this stack manipulation could be simpler.
static IV runCommand(
    pTHX_ SV **sp, U32 ax,
    redisContext *self, int argc, const char **argv, const size_t *argvlen
) {
    redisReply *reply = redisCommandArgv(self, argc, argv, argvlen);
    if (!reply || self->err) {
        fprintf(stderr, "Error: Couldn't execute redisCommandArgv\n");
        exit(1);
    }

    replyTuple tup = decodeReply(aTHX_ reply);
    freeReplyObject(reply);

    if (tup.err) croak_sv(tup.err);

    // Return arrays as a list in list context.
    // TODO Do the same for hashes.
    if (GIMME_V == G_LIST && SvROK(tup.sv) && SvTYPE(SvRV(tup.sv)) == SVt_PVAV) {
        AV    *av = (AV *) SvRV(tup.sv);
        SV  **svs = AvARRAY(av);
        int count = av_count(av);

        EXTEND(SP, count);
        for(int i = 0; i < count; i++) ST(i) = svs[i];
        return count;
    }

    ST(0) = tup.sv;
    return 1;
}

MODULE = Redis::XS PACKAGE = Redis::XS

PROTOTYPES: DISABLE

TYPEMAP: <<TYPEMAP
redisContext * T_REDIS_XS

INPUT
T_REDIS_XS
    $var = INT2PTR($type, SvIVX(SvRV($arg)));

OUTPUT
T_REDIS_XS
    sv_setref_pv($arg, class, (void *) $var);

TYPEMAP

BOOT:
    redisInitOpenSSL();

    for (int i = 1; commands[i]; i++) {
        // FIXME This code is terrible.
        int len = strlen("Redis::XS::") + strlen(commands[i]);
        char *name = alloca(len) + 1;
        strcpy(name, "Redis::XS::");
        strcpy(name + strlen("Redis::XS::"), commands[i]);

        // Replace pipes and hyphens with underscores in the sub name.
        for (int j = 0; j < len; j++)
            if (name[j] == '|' || name[j] == '-')
                name[j] = '_';

        CV *cv = newXS(name, XS_Redis__XS_bitcount, file);
        XSANY.any_i32 = i;
    }

redisContext *new(const char *class, ...)
    CODE:
        if (!(items % 2)) croak("Odd number of arguments");

        // Default arguments.
        const char *host     = "localhost",
                   *lib_name = class,
                   *lib_ver  = VERSION,
                   *name     = class,
                   *password = NULL,
                   *username = "default";

        int port = 6379;

        // Parse arguments.
        for (int i = 1; i < items; i += 2) {
            char *key = SvPV_nolen(ST(i));
            SV   *val = ST(i + 1);

            if (strEQ(key, "host"))
                host = SvPV_nolen(val);
            else if (strEQ(key, "lib_name"))
                lib_name = SvPV_nolen(val);
            else if (strEQ(key, "lib_ver"))
                lib_ver = SvPV_nolen(val);
            else if (strEQ(key, "name"))
                name = SvPV_nolen(val);
            else if (strEQ(key, "password"))
                password = SvPV_nolen(val);
            else if (strEQ(key, "port"))
                port = SvIV(val);
            else if (strEQ(key, "username"))
                username = SvPV_nolen(val);
            else
                croak("Unknown argument: %s", key);
        }

        redisOptions opt = { .options = REDIS_OPT_PREFER_IP_UNSPEC };
        REDIS_OPTIONS_SET_TCP(&opt, host, port);

        // Connect.
        redisContext *self = redisConnectWithOptions(&opt);
        if (!self || self->err) {
            SV *err;
            if (self) {
                err = sv_2mortal(newSVpvf("Connection error: %s", self->errstr));
                redisFree(self);
            } else {
                err = sv_2mortal(newSVpvs("Connection error: can't allocate redis context"));
            }
            croak_sv(err);
        }

        // TODO AUTH. Pipeline.
        redisReply *reply;
        if (password)
            reply = redisCommand(self, "HELLO 3 AUTH %s %s SETNAME %s",
                username, password, name);
        else
            reply = redisCommand(self, "HELLO 3 SETNAME %s", name);
        if (!reply || self->err) {
            fprintf(stderr, "Error: Couldn't execute redisCommandArgv\n");
            exit(1);
        }

        // Set library name & version, but ignore errors as command is 7.2+.
        redisAppendCommand(self, "CLIENT SETINFO LIB-NAME %s", lib_name);
        redisAppendCommand(self, "CLIENT SETINFO LIB-VER %s", lib_ver);
        redisGetReply(self, (void *) &reply);
        freeReplyObject(reply);
        redisGetReply(self, (void *) &reply);
        freeReplyObject(reply);

        RETVAL = self;
    OUTPUT:
        RETVAL

void call(redisContext *self, cmd, ...)
    PPCODE:
        int          argc    = items - 1;
        const char **argv    = alloca(argc * sizeof(const char *));
        size_t      *argvlen = alloca(argc * sizeof(size_t));

        for (int i = 0; i < argc; i++) {
            STRLEN len;
            argv[i] = SvPV(ST(i + 1), len);
            argvlen[i] = len;
        }

        XSRETURN(runCommand(aTHX_ sp, ax, self, argc, argv, argvlen));

void bitcount(redisContext *self, ...)
    PPCODE:
        // FIXME This logic could be (hopefully) simplified.
        const char* const cmd = commands[XSANY.any_i32];
        char *subcmd          = strchr(cmd, '|');

        int base = subcmd ? 1 : 0;
        int argc = base + items;

        const char **argv    = alloca(argc * sizeof(const char *));
        size_t      *argvlen = alloca(argc * sizeof(size_t));

        if (subcmd) {
            argv[0]    = cmd;
            argvlen[0] = subcmd - cmd;
            argv[1]    = ++subcmd;
            argvlen[1] = strlen(subcmd);
        }
        else {
            argv[0]    = cmd;
            argvlen[0] = strlen(cmd);
        }

        // Append any arguments.
        for (int i = 1; i < items; i++) {
            STRLEN len;
            argv[base + i] = SvPV(ST(i), len);
            argvlen[base + i] = len;
        }

        XSRETURN(runCommand(aTHX_ sp, ax, self, argc, argv, argvlen));

void DESTROY(redisContext *self);
    CODE:
        redisFree(self);
