static const char* const commands[] = {
// Bitmap
"bitcount", "bitfield", "bitfield_ro", "bitop", "bitpos", "getbit", "setbit",

// Cluster Management
"asking", "cluster", "cluster|addslots", "cluster|addslotsrange",
"cluster|bumpepoch", "cluster|count-failure-reports",
"cluster|countkeysinslot", "cluster|delslots", "cluster|delslotsrange",
"cluster|failover", "cluster|flushslots", "cluster|forget",
"cluster|getkeysinslot", "cluster|help", "cluster|info", "cluster|keyslot",
"cluster|links", "cluster|meet", "cluster|myid", "cluster|myshardid",
"cluster|nodes", "cluster|replicas", "cluster|replicate", "cluster|reset",
"cluster|saveconfig", "cluster|set-config-epoch", "cluster|setslot",
"cluster|shards", "cluster|slaves", "cluster|slots", "readonly", "readwrite",

// Connection Management
"auth", "client", "client|caching", "client|getname", "client|getredir",
"client|help", "client|id", /* client|info */ "client|kill", /* client|list */
"client|no-evict", "client|no-touch", "client|pause", "client|reply",
"client|setinfo", "client|setname", "client|tracking", "client|trackinginfo",
"client|unblock", "client|unpause", "echo", "hello", "ping", "quit", "reset",
"select",

// Generic
"copy", "del", "dump", "exists", "expire", "expireat", "expiretime", "keys",
"migrate", "move", "object", "object|encoding", "object|freq", "object|help",
"object|idletime", "object|refcount", "persist", "pexpire", "pexpireat",
"pexpiretime", "pttl", "randomkey", "rename", "renamenx", "restore", "scan",
"sort", "sort_ro", "touch", "ttl", "type", "unlink", "wait", "waitaof",

// Geospatial Indices
"geoadd", "geodist", "geohash", "geopos", "georadius", "georadius_ro",
"georadiusbymember", "georadiusbymember_ro", "geosearch", "geosearchstore",

// Hash
"hdel", "hexists", "hget", "hgetall", "hincrby", "hincrbyfloat", "hkeys",
"hlen", "hmget", "hmset", "hrandfield", "hscan", "hset", "hsetnx", "hstrlen",
"hvals",

// HyperLogLog
"pfadd", "pfcount", "pfdebug", "pfmerge", "pfselftest",

// List
"blmove", "blmpop", "blpop", "brpop", "brpoplpush", "lindex", "linsert",
"llen", "lmove", "lmpop", "lpop", "lpos", "lpush", "lpushx", "lrange", "lrem",
"lset", "ltrim", "rpop", "rpoplpush", "rpush", "rpushx",

// Pub/Sub
"psubscribe", "publish", "pubsub", "pubsub|channels", "pubsub|help",
"pubsub|numpat", "pubsub|numsub", "pubsub|shardchannels",
"pubsub|shardnumsub", "punsubscribe", "spublish", "ssubscribe", "subscribe",
"sunsubscribe", "unsubscribe",

// Scripting and Functions
"eval", "eval_ro", "evalsha", "evalsha_ro", "fcall", "fcall_ro", "function",
"function|delete", "function|dump", "function|flush", "function|help",
"function|kill", "function|list", "function|load", "function|restore",
"function|stats", "script", "script|debug", "script|exists", "script|flush",
"script|help", "script|kill", "script|load",

// Server Management
"acl", "acl|cat", "acl|deluser", "acl|dryrun", "acl|genpass", "acl|getuser",
"acl|help", "acl|list", "acl|load", "acl|log", "acl|save", "acl|setuser",
"acl|users", "acl|whoami", "bgrewriteaof", "bgsave", "command",
"command|count", "command|docs", "command|getkeys", "command|getkeysandflags",
"command|help", "command|info", "command|list", "config", "config|get",
"config|help", "config|resetstat", "config|rewrite", "config|set", "dbsize",
"debug", "failover", "flushall", "flushdb", /* info */ "lastsave", "latency",
"latency|doctor", "latency|graph", "latency|help", "latency|histogram",
"latency|history", "latency|latest", "latency|reset", "lolwut", "memory",
"memory|doctor", "memory|help", "memory|malloc-stats", "memory|purge",
"memory|stats", "memory|usage", "module", "module|help", "module|list",
"module|load", "module|loadex", "module|unload", "monitor", "psync",
"replconf", "replicaof", "restore-asking", "role", "save", "shutdown",
"slaveof", "slowlog", "slowlog|get", "slowlog|help", "slowlog|len",
"slowlog|reset", "swapdb", "sync", "time",

// Set
"sadd", "scard", "sdiff", "sdiffstore", "sinter", "sintercard", "sinterstore",
"sismember", "smembers", "smismember", "smove", "spop", "srandmember", "srem",
"sscan", "sunion", "sunionstore",

// Sorted Set
"bzmpop", "bzpopmax", "bzpopmin", "zadd", "zcard", "zcount", "zdiff",
"zdiffstore", "zincrby", "zinter", "zintercard", "zinterstore", "zlexcount",
"zmpop", "zmscore", "zpopmax", "zpopmin", "zrandmember", "zrange",
"zrangebylex", "zrangebyscore", "zrangestore", "zrank", "zrem",
"zremrangebylex", "zremrangebyrank", "zremrangebyscore", "zrevrange",
"zrevrangebylex", "zrevrangebyscore", "zrevrank", "zscan", "zscore", "zunion",
"zunionstore",

// Stream
"xack", "xadd", "xautoclaim", "xclaim", "xdel", "xgroup", "xgroup|create",
"xgroup|createconsumer", "xgroup|delconsumer", "xgroup|destroy",
"xgroup|help", "xgroup|setid", "xinfo", "xinfo|consumers", "xinfo|groups",
"xinfo|help", "xinfo|stream", "xlen", "xpending", "xrange", "xread",
"xreadgroup", "xrevrange", "xsetid", "xtrim",

// String
"append", "decr", "decrby", "get", "getdel", "getex", "getrange", "getset",
"incr", "incrby", "incrbyfloat", "lcs", "mget", "mset", "msetnx", "psetex",
"set", "setex", "setnx", "setrange", "stralgo|lcs", "strlen", "substr",

// Transactions
"discard", "exec", "multi", "unwatch", "watch",

0};
