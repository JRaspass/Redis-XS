# https://redis.io/commands/?group=hyperloglog
use Test2::V0 -target => $ENV{REDIS_CLASS} // 'Redis::XS';

my $redis = CLASS->new;

$redis->flushdb;

# https://redis.io/commands/pfadd/
subtest PFADD => sub {
    is $redis->pfadd( hll => 'a' .. 'g' ), 1, 'PFADD hll a b c d e f g';
    is $redis->pfcount('hll'),             7, 'PFCOUNT hll';
};

# https://redis.io/commands/pfcount/
is $redis->pfcount('nonexisting'), 0, 'PFCOUNT nonexisting';

# https://redis.io/commands/pfmerge/
subtest PFMERGE => sub {
    is $redis->pfadd( hll1 => qw(foo bar zap a) ), 1, 'PFADD hll1 ...';
    is $redis->pfadd( hll2 => qw(a b c foo    ) ), 1, 'PFADD hll2 ...';

    is $redis->pfmerge(qw(hll3 hll1 hll2)), 'OK','PFMERGE hll3 hll1 hll2';
    is $redis->pfcount('hll3'),             6,   'PFCOUNT hll3';
};

done_testing;
