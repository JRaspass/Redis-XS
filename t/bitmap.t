# https://redis.io/commands/?group=bitmap
use Test2::V0 -target => $ENV{REDIS_CLASS} // 'Redis::XS';
use Test2::Tools::xUnit;

my $redis   = CLASS->new;
my $version = $redis->redis_version;

## Ensure each test starts clean and we clean up after ourselves.
sub before_each : BeforeEach { is $redis->flushdb, 'OK', 'FLUSHDB' }
sub after_all   : AfterAll   { is $redis->flushdb, 'OK', 'FLUSHDB' }

# https://redis.io/commands/bitcount/
sub BITCOUNT : Test {
    is $redis->set('mykey', 'foobar'), 'OK';

    is $redis->bitcount('mykey'), 26;
    is $redis->bitcount('mykey', 0, 0), 4;
    is $redis->bitcount('mykey', 1, 1), 6;

    SKIP: {
        skip 'Redis 7.0 required', 2 if $version lt v7;

        is $redis->bitcount('mykey', 1, 1, 'BYTE'), 6;
        is $redis->bitcount('mykey', 5, 30, 'BIT'), 17;
    }
}

# https://redis.io/commands/bitfield/
sub BITFIELD : Test {
    is $redis->bitfield(qw(mykey INCRBY i5 100 1 GET u4 0)), [1, 0];

    {
        no warnings 'qw';
        is $redis->bitfield(qw(mystring SET i8 #0 100 SET i8 #1 200)), [0, 0];
    }

    is $redis->bitfield(qw(mykey INCRBY u2 100 1 OVERFLOW SAT INCRBY u2 102 1)), [1, 1];
    is $redis->bitfield(qw(mykey INCRBY u2 100 1 OVERFLOW SAT INCRBY u2 102 1)), [2, 2];
    is $redis->bitfield(qw(mykey INCRBY u2 100 1 OVERFLOW SAT INCRBY u2 102 1)), [3, 3];
    is $redis->bitfield(qw(mykey INCRBY u2 100 1 OVERFLOW SAT INCRBY u2 102 1)), [0, 3];

    is $redis->bitfield(qw(mykey OVERFLOW FAIL INCRBY u2 102 1)), [undef];
}

# https://redis.io/commands/bitfield_ro/
sub BITFIELD_RO : Test {
    is $redis->bitfield_ro('hello', 'GET', 'i8', 16), [0];
}

done_testing;
