#define PERL_NO_GET_CONTEXT
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "commands.h"
#include "modules/hiredis/hiredis.h"
#include "modules/hiredis/hiredis_ssl.h"
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

    // TODO REDIS_REPLY_PUSH
    switch (reply->type) {
        case REDIS_REPLY_ARRAY:
        case REDIS_REPLY_SET: {
            AV* const av = newAV_alloc_x(reply->elements);
            tup.sv = newRV_noinc((SV*) av);

            for (size_t i = 0; i < reply->elements; i++) {
                // TODO Handle tup.err
                replyTuple tup = decodeReply(aTHX_ reply->element[i]);

                av_store_simple(av, i, tup.sv);
            }

            break;
        }
        case REDIS_REPLY_ATTR:
        case REDIS_REPLY_MAP: {
            HV *hv = newHV();
            tup.sv = newRV_noinc((SV*) hv);

            for (size_t i = 0; i < reply->elements; i += 2) {
                // TODO Handle key.err, val.err
                replyTuple key = decodeReply(aTHX_ reply->element[i]);
                replyTuple val = decodeReply(aTHX_ reply->element[i + 1]);

                hv_store_ent(hv, key.sv, val.sv, 0);
            }

            break;
        }
        case REDIS_REPLY_BIGNUM:
        case REDIS_REPLY_DOUBLE:
        case REDIS_REPLY_STATUS:
        case REDIS_REPLY_STRING:
        case REDIS_REPLY_VERB:
            tup.sv = newSVpvn(reply->str, reply->len);
            break;
        case REDIS_REPLY_BOOL:
            tup.sv = boolSV(reply->integer);
            break;
        case REDIS_REPLY_ERROR:
            tup.err = newSVpvn(reply->str, reply->len);
            break;
        case REDIS_REPLY_INTEGER:
            tup.sv = newSViv(reply->integer);
            break;
        case REDIS_REPLY_NIL:
            tup.sv = newSV(0);
            break;
        default:
            tup.err = newSVpvf("Unknown reply type: %d", reply->type);
    }

    SvTAINTED_on(tup.sv);

    return tup;
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

    for (int i = 1; commands[i].name; i++)
        CvXSUBANY(newXS(commands[i].name, XS_Redis__XS_call, file)).any_i32 = i;

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
                err = newSVpvf("Connection error: %s", self->errstr);
                redisFree(self);
            } else {
                err = newSVpvs("Connection error: can't allocate redis context");
            }
            croak_sv(sv_2mortal(err));
        }

        // TODO AUTH. Pipeline.
        redisReply *reply;
        if (password)
            reply = redisCommand(self, "HELLO 3 AUTH %s %s SETNAME %s",
                username, password, name);
        else
            reply = redisCommand(self, "HELLO 3 SETNAME %s", name);
        if (!reply || self->err)
            croak("Command error: %s", self->errstr);

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

void call(...)
    PPCODE:
        // Validate operands: $r->call('CMD', ...) or $r->cmd(...).
        bool isCall  = XSANY.any_i32 == 0;
        int minItems = isCall ? 2 : 1;
        if (items < minItems || !sv_isobject(ST(0)))
            croak_xs_usage(cv, isCall ? "self, cmd, ..." : "self, ...");

        redisContext *self = INT2PTR(redisContext *, SvIVX(SvRV(ST(0))));

        int              argc       = items - 1;
        redisCommandData cmd        = commands[XSANY.any_i32];
        int              total_argc = argc + cmd.argc;

        const char **argv    = alloca(total_argc * sizeof(const char *));
        size_t      *argvlen = alloca(total_argc * sizeof(size_t));

        for (int i = 0; i < cmd.argc; i++) {
            argv[i] = cmd.argv[i];
            argvlen[i] = strlen(cmd.argv[i]);   // Consider storing these?
        }

        for (int i = 0; i < argc; i++) {
            STRLEN len;
            argv[cmd.argc + i] = SvPV(ST(i + 1), len);
            argvlen[cmd.argc + i] = len;
        }

        redisReply *reply = redisCommandArgv(self, total_argc, argv, argvlen);
        if (!reply || self->err)
            croak("Command error: %s", self->errstr);

        replyTuple tup = decodeReply(aTHX_ reply);
        freeReplyObject(reply);

        tup.sv = sv_2mortal(tup.sv);

        if (tup.err) croak_sv(sv_2mortal(tup.err));

        // Return arrays as a list in list context.
        // TODO Do the same for hashes.
        if (GIMME_V == G_LIST && SvROK(tup.sv) && SvTYPE(SvRV(tup.sv)) == SVt_PVAV) {
            AV    *av = (AV *) SvRV(tup.sv);
            SV  **svs = AvARRAY(av);
            int count = av_count(av);

            EXTEND(SP, count);
            for(int i = 0; i < count; i++) ST(i) = svs[i];
            XSRETURN(count);
        }

        ST(0) = tup.sv;
        XSRETURN(1);

void DESTROY(redisContext *self);
    CODE:
        redisFree(self);
