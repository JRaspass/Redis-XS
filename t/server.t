# https://redis.io/commands/?group=server
use Test2::V0 -target => $ENV{REDIS_CLASS} // 'Redis::XS';

my $redis = CLASS->new;
my $int   = qr/^\d+$/a;

$redis->flushdb;

# https://redis.io/commands/acl-genpass/
subtest 'ACL GENPASS' => sub {
    like $redis->acl_genpass,     qr/^.{64}$/, 'ACL GENPASS';
    like $redis->acl_genpass(32), qr/^.{8}$/,  'ACL GENPASS 32';
    like $redis->acl_genpass(5),  qr/^..$/,    'ACL GENPASS 5';
};

# https://redis.io/commands/acl-users/
is $redis->acl_users, ['default'], 'ACL USERS';

# https://redis.io/commands/acl-whoami/
is $redis->acl_whoami, 'default', 'ACL WHOAMI';

# https://redis.io/commands/command-count/
like $redis->command_count, $int, 'COMMAND COUNT';

# https://redis.io/commands/dbsize/
is $redis->dbsize, 0, 'DBSIZE';

# https://redis.io/commands/memory-malloc-stats/
like $redis->memory_malloc_stats, qr/^___ Begin jemalloc statistics ___/,
    'MEMORY MALLOC-STATS';

# https://redis.io/commands/time/
like $redis->time, [ ( $int ) x 2 ], 'TIME';

done_testing;
