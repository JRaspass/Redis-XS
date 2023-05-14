# https://redis.io/commands/?group=generic
use Test2::V0 -target => $ENV{REDIS_CLASS} // 'Redis::XS';

my $redis = CLASS->new;

# https://redis.io/commands/del/
subtest DEL => sub {
    $redis->mset( foo => 'foo', bar => 'bar' );

    is $redis->del(qw(foo bar baz)), 2, 'DEL foo bar baz';
};

done_testing;
