# https://redis.io/commands/?group=sorted-set
use Test2::V0 -target => $ENV{REDIS_CLASS} // 'Redis::XS';

my $redis = CLASS->new;

# https://redis.io/commands/zscore/
subtest ZSCORE => sub {
    is $redis->zadd(   myzset => 1, 'one' ), 1, 'ZADD';
    is $redis->zscore( myzset =>    'one' ), 1, 'ZSCORE';
};

done_testing;
