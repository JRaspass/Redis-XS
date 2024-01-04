typedef struct {
    const char* const name;
    int               argc;
    const char* const argv[2];
} redisCommandData;

static const redisCommandData commands[] = {

    {},

    // bitmap
    {"Redis::XS::bitcount",    1, {"bitcount"}},
    {"Redis::XS::bitfield",    1, {"bitfield"}},
    {"Redis::XS::bitfield_ro", 1, {"bitfield_ro"}},
    {"Redis::XS::bitop",       1, {"bitop"}},
    {"Redis::XS::bitpos",      1, {"bitpos"}},
    {"Redis::XS::getbit",      1, {"getbit"}},
    {"Redis::XS::setbit",      1, {"setbit"}},

    // cluster
    {"Redis::XS::asking",                        1, {"asking"}},
    {"Redis::XS::cluster",                       1, {"cluster"}},
    {"Redis::XS::cluster_addslots",              2, {"cluster", "addslots"}},
    {"Redis::XS::cluster_addslotsrange",         2, {"cluster", "addslotsrange"}},
    {"Redis::XS::cluster_bumpepoch",             2, {"cluster", "bumpepoch"}},
    {"Redis::XS::cluster_count_failure_reports", 2, {"cluster", "count-failure-reports"}},
    {"Redis::XS::cluster_countkeysinslot",       2, {"cluster", "countkeysinslot"}},
    {"Redis::XS::cluster_delslots",              2, {"cluster", "delslots"}},
    {"Redis::XS::cluster_delslotsrange",         2, {"cluster", "delslotsrange"}},
    {"Redis::XS::cluster_failover",              2, {"cluster", "failover"}},
    {"Redis::XS::cluster_flushslots",            2, {"cluster", "flushslots"}},
    {"Redis::XS::cluster_forget",                2, {"cluster", "forget"}},
    {"Redis::XS::cluster_getkeysinslot",         2, {"cluster", "getkeysinslot"}},
    {"Redis::XS::cluster_help",                  2, {"cluster", "help"}},
    {"Redis::XS::cluster_info",                  2, {"cluster", "info"}},
    {"Redis::XS::cluster_keyslot",               2, {"cluster", "keyslot"}},
    {"Redis::XS::cluster_links",                 2, {"cluster", "links"}},
    {"Redis::XS::cluster_meet",                  2, {"cluster", "meet"}},
    {"Redis::XS::cluster_myid",                  2, {"cluster", "myid"}},
    {"Redis::XS::cluster_myshardid",             2, {"cluster", "myshardid"}},
    {"Redis::XS::cluster_nodes",                 2, {"cluster", "nodes"}},
    {"Redis::XS::cluster_replicas",              2, {"cluster", "replicas"}},
    {"Redis::XS::cluster_replicate",             2, {"cluster", "replicate"}},
    {"Redis::XS::cluster_reset",                 2, {"cluster", "reset"}},
    {"Redis::XS::cluster_saveconfig",            2, {"cluster", "saveconfig"}},
    {"Redis::XS::cluster_set_config_epoch",      2, {"cluster", "set-config-epoch"}},
    {"Redis::XS::cluster_setslot",               2, {"cluster", "setslot"}},
    {"Redis::XS::cluster_shards",                2, {"cluster", "shards"}},
    {"Redis::XS::cluster_slaves",                2, {"cluster", "slaves"}},
    {"Redis::XS::cluster_slots",                 2, {"cluster", "slots"}},
    {"Redis::XS::readonly",                      1, {"readonly"}},
    {"Redis::XS::readwrite",                     1, {"readwrite"}},

    // connection
    {"Redis::XS::auth",                1, {"auth"}},
    {"Redis::XS::client",              1, {"client"}},
    {"Redis::XS::client_caching",      2, {"client", "caching"}},
    {"Redis::XS::client_getname",      2, {"client", "getname"}},
    {"Redis::XS::client_getredir",     2, {"client", "getredir"}},
    {"Redis::XS::client_help",         2, {"client", "help"}},
    {"Redis::XS::client_id",           2, {"client", "id"}},
 // {"Redis::XS::client_info",         2, {"client", "info"}},
    {"Redis::XS::client_kill",         2, {"client", "kill"}},
 // {"Redis::XS::client_list",         2, {"client", "list"}},
    {"Redis::XS::client_no_evict",     2, {"client", "no-evict"}},
    {"Redis::XS::client_no_touch",     2, {"client", "no-touch"}},
    {"Redis::XS::client_pause",        2, {"client", "pause"}},
    {"Redis::XS::client_reply",        2, {"client", "reply"}},
    {"Redis::XS::client_setinfo",      2, {"client", "setinfo"}},
    {"Redis::XS::client_setname",      2, {"client", "setname"}},
    {"Redis::XS::client_tracking",     2, {"client", "tracking"}},
    {"Redis::XS::client_trackinginfo", 2, {"client", "trackinginfo"}},
    {"Redis::XS::client_unblock",      2, {"client", "unblock"}},
    {"Redis::XS::client_unpause",      2, {"client", "unpause"}},
    {"Redis::XS::echo",                1, {"echo"}},
    {"Redis::XS::hello",               1, {"hello"}},
    {"Redis::XS::ping",                1, {"ping"}},
    {"Redis::XS::quit",                1, {"quit"}},
    {"Redis::XS::reset",               1, {"reset"}},
    {"Redis::XS::select",              1, {"select"}},

    // generic
    {"Redis::XS::copy",            1, {"copy"}},
    {"Redis::XS::del",             1, {"del"}},
    {"Redis::XS::dump",            1, {"dump"}},
    {"Redis::XS::exists",          1, {"exists"}},
    {"Redis::XS::expire",          1, {"expire"}},
    {"Redis::XS::expireat",        1, {"expireat"}},
    {"Redis::XS::expiretime",      1, {"expiretime"}},
    {"Redis::XS::keys",            1, {"keys"}},
    {"Redis::XS::migrate",         1, {"migrate"}},
    {"Redis::XS::move",            1, {"move"}},
    {"Redis::XS::object",          1, {"object"}},
    {"Redis::XS::object_encoding", 2, {"object", "encoding"}},
    {"Redis::XS::object_freq",     2, {"object", "freq"}},
    {"Redis::XS::object_help",     2, {"object", "help"}},
    {"Redis::XS::object_idletime", 2, {"object", "idletime"}},
    {"Redis::XS::object_refcount", 2, {"object", "refcount"}},
    {"Redis::XS::persist",         1, {"persist"}},
    {"Redis::XS::pexpire",         1, {"pexpire"}},
    {"Redis::XS::pexpireat",       1, {"pexpireat"}},
    {"Redis::XS::pexpiretime",     1, {"pexpiretime"}},
    {"Redis::XS::pttl",            1, {"pttl"}},
    {"Redis::XS::randomkey",       1, {"randomkey"}},
    {"Redis::XS::rename",          1, {"rename"}},
    {"Redis::XS::renamenx",        1, {"renamenx"}},
    {"Redis::XS::restore",         1, {"restore"}},
    {"Redis::XS::scan",            1, {"scan"}},
    {"Redis::XS::sort",            1, {"sort"}},
    {"Redis::XS::sort_ro",         1, {"sort_ro"}},
    {"Redis::XS::touch",           1, {"touch"}},
    {"Redis::XS::ttl",             1, {"ttl"}},
    {"Redis::XS::type",            1, {"type"}},
    {"Redis::XS::unlink",          1, {"unlink"}},
    {"Redis::XS::wait",            1, {"wait"}},
    {"Redis::XS::waitaof",         1, {"waitaof"}},

    // geo
    {"Redis::XS::geoadd",               1, {"geoadd"}},
    {"Redis::XS::geodist",              1, {"geodist"}},
    {"Redis::XS::geohash",              1, {"geohash"}},
    {"Redis::XS::geopos",               1, {"geopos"}},
    {"Redis::XS::georadius",            1, {"georadius"}},
    {"Redis::XS::georadius_ro",         1, {"georadius_ro"}},
    {"Redis::XS::georadiusbymember",    1, {"georadiusbymember"}},
    {"Redis::XS::georadiusbymember_ro", 1, {"georadiusbymember_ro"}},
    {"Redis::XS::geosearch",            1, {"geosearch"}},
    {"Redis::XS::geosearchstore",       1, {"geosearchstore"}},

    // hash
    {"Redis::XS::hdel",         1, {"hdel"}},
    {"Redis::XS::hexists",      1, {"hexists"}},
    {"Redis::XS::hget",         1, {"hget"}},
    {"Redis::XS::hgetall",      1, {"hgetall"}},
    {"Redis::XS::hincrby",      1, {"hincrby"}},
    {"Redis::XS::hincrbyfloat", 1, {"hincrbyfloat"}},
    {"Redis::XS::hkeys",        1, {"hkeys"}},
    {"Redis::XS::hlen",         1, {"hlen"}},
    {"Redis::XS::hmget",        1, {"hmget"}},
    {"Redis::XS::hmset",        1, {"hmset"}},
    {"Redis::XS::hrandfield",   1, {"hrandfield"}},
    {"Redis::XS::hscan",        1, {"hscan"}},
    {"Redis::XS::hset",         1, {"hset"}},
    {"Redis::XS::hsetnx",       1, {"hsetnx"}},
    {"Redis::XS::hstrlen",      1, {"hstrlen"}},
    {"Redis::XS::hvals",        1, {"hvals"}},

    // hyperloglog
    {"Redis::XS::pfadd",      1, {"pfadd"}},
    {"Redis::XS::pfcount",    1, {"pfcount"}},
    {"Redis::XS::pfdebug",    1, {"pfdebug"}},
    {"Redis::XS::pfmerge",    1, {"pfmerge"}},
    {"Redis::XS::pfselftest", 1, {"pfselftest"}},

    // json
    {"Redis::XS::json_arrappend",    1, {"json.arrappend"}},
    {"Redis::XS::json_arrindex",     1, {"json.arrindex"}},
    {"Redis::XS::json_arrinsert",    1, {"json.arrinsert"}},
    {"Redis::XS::json_arrlen",       1, {"json.arrlen"}},
    {"Redis::XS::json_arrpop",       1, {"json.arrpop"}},
    {"Redis::XS::json_arrtrim",      1, {"json.arrtrim"}},
    {"Redis::XS::json_clear",        1, {"json.clear"}},
    {"Redis::XS::json_debug",        1, {"json.debug"}},
    {"Redis::XS::json_debug_help",   2, {"json.debug", "help"}},
    {"Redis::XS::json_debug_memory", 2, {"json.debug", "memory"}},
    {"Redis::XS::json_del",          1, {"json.del"}},
    {"Redis::XS::json_forget",       1, {"json.forget"}},
    {"Redis::XS::json_get",          1, {"json.get"}},
    {"Redis::XS::json_merge",        1, {"json.merge"}},
    {"Redis::XS::json_mget",         1, {"json.mget"}},
    {"Redis::XS::json_mset",         1, {"json.mset"}},
    {"Redis::XS::json_numincrby",    1, {"json.numincrby"}},
    {"Redis::XS::json_nummultby",    1, {"json.nummultby"}},
    {"Redis::XS::json_numpowby",     1, {"json.numpowby"}},
    {"Redis::XS::json_objkeys",      1, {"json.objkeys"}},
    {"Redis::XS::json_objlen",       1, {"json.objlen"}},
    {"Redis::XS::json_resp",         1, {"json.resp"}},
    {"Redis::XS::json_set",          1, {"json.set"}},
    {"Redis::XS::json_strappend",    1, {"json.strappend"}},
    {"Redis::XS::json_strlen",       1, {"json.strlen"}},
    {"Redis::XS::json_toggle",       1, {"json.toggle"}},
    {"Redis::XS::json_type",         1, {"json.type"}},

    // list
    {"Redis::XS::blmove",     1, {"blmove"}},
    {"Redis::XS::blmpop",     1, {"blmpop"}},
    {"Redis::XS::blpop",      1, {"blpop"}},
    {"Redis::XS::brpop",      1, {"brpop"}},
    {"Redis::XS::brpoplpush", 1, {"brpoplpush"}},
    {"Redis::XS::lindex",     1, {"lindex"}},
    {"Redis::XS::linsert",    1, {"linsert"}},
    {"Redis::XS::llen",       1, {"llen"}},
    {"Redis::XS::lmove",      1, {"lmove"}},
    {"Redis::XS::lmpop",      1, {"lmpop"}},
    {"Redis::XS::lpop",       1, {"lpop"}},
    {"Redis::XS::lpos",       1, {"lpos"}},
    {"Redis::XS::lpush",      1, {"lpush"}},
    {"Redis::XS::lpushx",     1, {"lpushx"}},
    {"Redis::XS::lrange",     1, {"lrange"}},
    {"Redis::XS::lrem",       1, {"lrem"}},
    {"Redis::XS::lset",       1, {"lset"}},
    {"Redis::XS::ltrim",      1, {"ltrim"}},
    {"Redis::XS::rpop",       1, {"rpop"}},
    {"Redis::XS::rpoplpush",  1, {"rpoplpush"}},
    {"Redis::XS::rpush",      1, {"rpush"}},
    {"Redis::XS::rpushx",     1, {"rpushx"}},

    // pubsub
    {"Redis::XS::psubscribe",           1, {"psubscribe"}},
    {"Redis::XS::publish",              1, {"publish"}},
    {"Redis::XS::pubsub",               1, {"pubsub"}},
    {"Redis::XS::pubsub_channels",      2, {"pubsub", "channels"}},
    {"Redis::XS::pubsub_help",          2, {"pubsub", "help"}},
    {"Redis::XS::pubsub_numpat",        2, {"pubsub", "numpat"}},
    {"Redis::XS::pubsub_numsub",        2, {"pubsub", "numsub"}},
    {"Redis::XS::pubsub_shardchannels", 2, {"pubsub", "shardchannels"}},
    {"Redis::XS::pubsub_shardnumsub",   2, {"pubsub", "shardnumsub"}},
    {"Redis::XS::punsubscribe",         1, {"punsubscribe"}},
    {"Redis::XS::spublish",             1, {"spublish"}},
    {"Redis::XS::ssubscribe",           1, {"ssubscribe"}},
    {"Redis::XS::subscribe",            1, {"subscribe"}},
    {"Redis::XS::sunsubscribe",         1, {"sunsubscribe"}},
    {"Redis::XS::unsubscribe",          1, {"unsubscribe"}},

    // scripting
    {"Redis::XS::eval",             1, {"eval"}},
    {"Redis::XS::eval_ro",          1, {"eval_ro"}},
    {"Redis::XS::evalsha",          1, {"evalsha"}},
    {"Redis::XS::evalsha_ro",       1, {"evalsha_ro"}},
    {"Redis::XS::fcall",            1, {"fcall"}},
    {"Redis::XS::fcall_ro",         1, {"fcall_ro"}},
    {"Redis::XS::function",         1, {"function"}},
    {"Redis::XS::function_delete",  2, {"function", "delete"}},
    {"Redis::XS::function_dump",    2, {"function", "dump"}},
    {"Redis::XS::function_flush",   2, {"function", "flush"}},
    {"Redis::XS::function_help",    2, {"function", "help"}},
    {"Redis::XS::function_kill",    2, {"function", "kill"}},
    {"Redis::XS::function_list",    2, {"function", "list"}},
    {"Redis::XS::function_load",    2, {"function", "load"}},
    {"Redis::XS::function_restore", 2, {"function", "restore"}},
    {"Redis::XS::function_stats",   2, {"function", "stats"}},
    {"Redis::XS::script",           1, {"script"}},
    {"Redis::XS::script_debug",     2, {"script", "debug"}},
    {"Redis::XS::script_exists",    2, {"script", "exists"}},
    {"Redis::XS::script_flush",     2, {"script", "flush"}},
    {"Redis::XS::script_help",      2, {"script", "help"}},
    {"Redis::XS::script_kill",      2, {"script", "kill"}},
    {"Redis::XS::script_load",      2, {"script", "load"}},

    // server
    {"Redis::XS::acl",                     1, {"acl"}},
    {"Redis::XS::acl_cat",                 2, {"acl", "cat"}},
    {"Redis::XS::acl_deluser",             2, {"acl", "deluser"}},
    {"Redis::XS::acl_dryrun",              2, {"acl", "dryrun"}},
    {"Redis::XS::acl_genpass",             2, {"acl", "genpass"}},
    {"Redis::XS::acl_getuser",             2, {"acl", "getuser"}},
    {"Redis::XS::acl_help",                2, {"acl", "help"}},
    {"Redis::XS::acl_list",                2, {"acl", "list"}},
    {"Redis::XS::acl_load",                2, {"acl", "load"}},
    {"Redis::XS::acl_log",                 2, {"acl", "log"}},
    {"Redis::XS::acl_save",                2, {"acl", "save"}},
    {"Redis::XS::acl_setuser",             2, {"acl", "setuser"}},
    {"Redis::XS::acl_users",               2, {"acl", "users"}},
    {"Redis::XS::acl_whoami",              2, {"acl", "whoami"}},
    {"Redis::XS::bgrewriteaof",            1, {"bgrewriteaof"}},
    {"Redis::XS::bgsave",                  1, {"bgsave"}},
    {"Redis::XS::command",                 1, {"command"}},
    {"Redis::XS::command_count",           2, {"command", "count"}},
    {"Redis::XS::command_docs",            2, {"command", "docs"}},
    {"Redis::XS::command_getkeys",         2, {"command", "getkeys"}},
    {"Redis::XS::command_getkeysandflags", 2, {"command", "getkeysandflags"}},
    {"Redis::XS::command_help",            2, {"command", "help"}},
    {"Redis::XS::command_info",            2, {"command", "info"}},
    {"Redis::XS::command_list",            2, {"command", "list"}},
    {"Redis::XS::config",                  1, {"config"}},
    {"Redis::XS::config_get",              2, {"config", "get"}},
    {"Redis::XS::config_help",             2, {"config", "help"}},
    {"Redis::XS::config_resetstat",        2, {"config", "resetstat"}},
    {"Redis::XS::config_rewrite",          2, {"config", "rewrite"}},
    {"Redis::XS::config_set",              2, {"config", "set"}},
    {"Redis::XS::dbsize",                  1, {"dbsize"}},
    {"Redis::XS::debug",                   1, {"debug"}},
    {"Redis::XS::failover",                1, {"failover"}},
    {"Redis::XS::flushall",                1, {"flushall"}},
    {"Redis::XS::flushdb",                 1, {"flushdb"}},
 // {"Redis::XS::info",                    1, {"info"}},
    {"Redis::XS::lastsave",                1, {"lastsave"}},
    {"Redis::XS::latency",                 1, {"latency"}},
    {"Redis::XS::latency_doctor",          2, {"latency", "doctor"}},
    {"Redis::XS::latency_graph",           2, {"latency", "graph"}},
    {"Redis::XS::latency_help",            2, {"latency", "help"}},
    {"Redis::XS::latency_histogram",       2, {"latency", "histogram"}},
    {"Redis::XS::latency_history",         2, {"latency", "history"}},
    {"Redis::XS::latency_latest",          2, {"latency", "latest"}},
    {"Redis::XS::latency_reset",           2, {"latency", "reset"}},
    {"Redis::XS::lolwut",                  1, {"lolwut"}},
    {"Redis::XS::memory",                  1, {"memory"}},
    {"Redis::XS::memory_doctor",           2, {"memory", "doctor"}},
    {"Redis::XS::memory_help",             2, {"memory", "help"}},
    {"Redis::XS::memory_malloc_stats",     2, {"memory", "malloc-stats"}},
    {"Redis::XS::memory_purge",            2, {"memory", "purge"}},
    {"Redis::XS::memory_stats",            2, {"memory", "stats"}},
    {"Redis::XS::memory_usage",            2, {"memory", "usage"}},
    {"Redis::XS::module",                  1, {"module"}},
    {"Redis::XS::module_help",             2, {"module", "help"}},
    {"Redis::XS::module_list",             2, {"module", "list"}},
    {"Redis::XS::module_load",             2, {"module", "load"}},
    {"Redis::XS::module_loadex",           2, {"module", "loadex"}},
    {"Redis::XS::module_unload",           2, {"module", "unload"}},
    {"Redis::XS::monitor",                 1, {"monitor"}},
    {"Redis::XS::psync",                   1, {"psync"}},
    {"Redis::XS::replconf",                1, {"replconf"}},
    {"Redis::XS::replicaof",               1, {"replicaof"}},
    {"Redis::XS::restore_asking",          1, {"restore-asking"}},
    {"Redis::XS::role",                    1, {"role"}},
    {"Redis::XS::save",                    1, {"save"}},
    {"Redis::XS::shutdown",                1, {"shutdown"}},
    {"Redis::XS::slaveof",                 1, {"slaveof"}},
    {"Redis::XS::slowlog",                 1, {"slowlog"}},
    {"Redis::XS::slowlog_get",             2, {"slowlog", "get"}},
    {"Redis::XS::slowlog_help",            2, {"slowlog", "help"}},
    {"Redis::XS::slowlog_len",             2, {"slowlog", "len"}},
    {"Redis::XS::slowlog_reset",           2, {"slowlog", "reset"}},
    {"Redis::XS::swapdb",                  1, {"swapdb"}},
    {"Redis::XS::sync",                    1, {"sync"}},
    {"Redis::XS::time",                    1, {"time"}},

    // set
    {"Redis::XS::sadd",        1, {"sadd"}},
    {"Redis::XS::scard",       1, {"scard"}},
    {"Redis::XS::sdiff",       1, {"sdiff"}},
    {"Redis::XS::sdiffstore",  1, {"sdiffstore"}},
    {"Redis::XS::sinter",      1, {"sinter"}},
    {"Redis::XS::sintercard",  1, {"sintercard"}},
    {"Redis::XS::sinterstore", 1, {"sinterstore"}},
    {"Redis::XS::sismember",   1, {"sismember"}},
    {"Redis::XS::smembers",    1, {"smembers"}},
    {"Redis::XS::smismember",  1, {"smismember"}},
    {"Redis::XS::smove",       1, {"smove"}},
    {"Redis::XS::spop",        1, {"spop"}},
    {"Redis::XS::srandmember", 1, {"srandmember"}},
    {"Redis::XS::srem",        1, {"srem"}},
    {"Redis::XS::sscan",       1, {"sscan"}},
    {"Redis::XS::sunion",      1, {"sunion"}},
    {"Redis::XS::sunionstore", 1, {"sunionstore"}},

    // sorted_set
    {"Redis::XS::bzmpop",           1, {"bzmpop"}},
    {"Redis::XS::bzpopmax",         1, {"bzpopmax"}},
    {"Redis::XS::bzpopmin",         1, {"bzpopmin"}},
    {"Redis::XS::zadd",             1, {"zadd"}},
    {"Redis::XS::zcard",            1, {"zcard"}},
    {"Redis::XS::zcount",           1, {"zcount"}},
    {"Redis::XS::zdiff",            1, {"zdiff"}},
    {"Redis::XS::zdiffstore",       1, {"zdiffstore"}},
    {"Redis::XS::zincrby",          1, {"zincrby"}},
    {"Redis::XS::zinter",           1, {"zinter"}},
    {"Redis::XS::zintercard",       1, {"zintercard"}},
    {"Redis::XS::zinterstore",      1, {"zinterstore"}},
    {"Redis::XS::zlexcount",        1, {"zlexcount"}},
    {"Redis::XS::zmpop",            1, {"zmpop"}},
    {"Redis::XS::zmscore",          1, {"zmscore"}},
    {"Redis::XS::zpopmax",          1, {"zpopmax"}},
    {"Redis::XS::zpopmin",          1, {"zpopmin"}},
    {"Redis::XS::zrandmember",      1, {"zrandmember"}},
    {"Redis::XS::zrange",           1, {"zrange"}},
    {"Redis::XS::zrangebylex",      1, {"zrangebylex"}},
    {"Redis::XS::zrangebyscore",    1, {"zrangebyscore"}},
    {"Redis::XS::zrangestore",      1, {"zrangestore"}},
    {"Redis::XS::zrank",            1, {"zrank"}},
    {"Redis::XS::zrem",             1, {"zrem"}},
    {"Redis::XS::zremrangebylex",   1, {"zremrangebylex"}},
    {"Redis::XS::zremrangebyrank",  1, {"zremrangebyrank"}},
    {"Redis::XS::zremrangebyscore", 1, {"zremrangebyscore"}},
    {"Redis::XS::zrevrange",        1, {"zrevrange"}},
    {"Redis::XS::zrevrangebylex",   1, {"zrevrangebylex"}},
    {"Redis::XS::zrevrangebyscore", 1, {"zrevrangebyscore"}},
    {"Redis::XS::zrevrank",         1, {"zrevrank"}},
    {"Redis::XS::zscan",            1, {"zscan"}},
    {"Redis::XS::zscore",           1, {"zscore"}},
    {"Redis::XS::zunion",           1, {"zunion"}},
    {"Redis::XS::zunionstore",      1, {"zunionstore"}},

    // stream
    {"Redis::XS::xack",                  1, {"xack"}},
    {"Redis::XS::xadd",                  1, {"xadd"}},
    {"Redis::XS::xautoclaim",            1, {"xautoclaim"}},
    {"Redis::XS::xclaim",                1, {"xclaim"}},
    {"Redis::XS::xdel",                  1, {"xdel"}},
    {"Redis::XS::xgroup",                1, {"xgroup"}},
    {"Redis::XS::xgroup_create",         2, {"xgroup", "create"}},
    {"Redis::XS::xgroup_createconsumer", 2, {"xgroup", "createconsumer"}},
    {"Redis::XS::xgroup_delconsumer",    2, {"xgroup", "delconsumer"}},
    {"Redis::XS::xgroup_destroy",        2, {"xgroup", "destroy"}},
    {"Redis::XS::xgroup_help",           2, {"xgroup", "help"}},
    {"Redis::XS::xgroup_setid",          2, {"xgroup", "setid"}},
    {"Redis::XS::xinfo",                 1, {"xinfo"}},
    {"Redis::XS::xinfo_consumers",       2, {"xinfo", "consumers"}},
    {"Redis::XS::xinfo_groups",          2, {"xinfo", "groups"}},
    {"Redis::XS::xinfo_help",            2, {"xinfo", "help"}},
    {"Redis::XS::xinfo_stream",          2, {"xinfo", "stream"}},
    {"Redis::XS::xlen",                  1, {"xlen"}},
    {"Redis::XS::xpending",              1, {"xpending"}},
    {"Redis::XS::xrange",                1, {"xrange"}},
    {"Redis::XS::xread",                 1, {"xread"}},
    {"Redis::XS::xreadgroup",            1, {"xreadgroup"}},
    {"Redis::XS::xrevrange",             1, {"xrevrange"}},
    {"Redis::XS::xsetid",                1, {"xsetid"}},
    {"Redis::XS::xtrim",                 1, {"xtrim"}},

    // string
    {"Redis::XS::append",      1, {"append"}},
    {"Redis::XS::decr",        1, {"decr"}},
    {"Redis::XS::decrby",      1, {"decrby"}},
    {"Redis::XS::get",         1, {"get"}},
    {"Redis::XS::getdel",      1, {"getdel"}},
    {"Redis::XS::getex",       1, {"getex"}},
    {"Redis::XS::getrange",    1, {"getrange"}},
    {"Redis::XS::getset",      1, {"getset"}},
    {"Redis::XS::incr",        1, {"incr"}},
    {"Redis::XS::incrby",      1, {"incrby"}},
    {"Redis::XS::incrbyfloat", 1, {"incrbyfloat"}},
    {"Redis::XS::lcs",         1, {"lcs"}},
    {"Redis::XS::mget",        1, {"mget"}},
    {"Redis::XS::mset",        1, {"mset"}},
    {"Redis::XS::msetnx",      1, {"msetnx"}},
    {"Redis::XS::psetex",      1, {"psetex"}},
    {"Redis::XS::set",         1, {"set"}},
    {"Redis::XS::setex",       1, {"setex"}},
    {"Redis::XS::setnx",       1, {"setnx"}},
    {"Redis::XS::setrange",    1, {"setrange"}},
    {"Redis::XS::stralgo_lcs", 2, {"stralgo", "lcs"}},
    {"Redis::XS::strlen",      1, {"strlen"}},
    {"Redis::XS::substr",      1, {"substr"}},

    // transactions
    {"Redis::XS::discard", 1, {"discard"}},
    {"Redis::XS::exec",    1, {"exec"}},
    {"Redis::XS::multi",   1, {"multi"}},
    {"Redis::XS::unwatch", 1, {"unwatch"}},
    {"Redis::XS::watch",   1, {"watch"}},

    {},
};
