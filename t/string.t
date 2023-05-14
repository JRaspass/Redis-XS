# https://redis.io/commands/?group=string
use Test2::V0 -target => $ENV{REDIS_CLASS} // 'Redis::XS';

my $redis = CLASS->new;

# https://redis.io/commands/getset/
subtest GETSET => sub {
    is $redis->set(    mykey => 'Hello' ), 'OK',    'SET mykey "Hello"';
    is $redis->getset( mykey => 'World' ), 'Hello', 'GETSET mykey "World"';
    is $redis->get('mykey'),               'World', 'GET mykey';
};

# https://redis.io/commands/lcs/
my $cmd = $redis->redis_version ge v7 ? 'LCS' : 'STRALGO LCS';
subtest $cmd => sub {
    $redis->mset( key1 => 'ohmytext', key2 => 'mynewtext' );

    my $method = lc $cmd =~ y/ /_/r;
    my @args   = ( $cmd eq 'LCS' ? () : 'KEYS', 'key1', 'key2' );

    is $redis->$method(@args), 'mytext', "$cmd @args";
    is $redis->$method(@args, 'LEN'), 6, "$cmd @args LEN";

    is $redis->$method(@args, 'IDX'), {
        len     => 6,
        matches => [ [ [4, 7], [5, 8] ], [ [2, 3], [0, 1] ] ],
    }, "$cmd @args IDX";

    is $redis->$method(@args, 'IDX', 'MINMATCHLEN', 4), {
        len     => 6,
        matches => [ [ [4, 7], [5, 8] ] ],
    }, "$cmd @args IDX MINMATCHLEN 4";

    is $redis->$method(@args, 'IDX', 'MINMATCHLEN', 4, 'WITHMATCHLEN'), {
        len     => 6,
        matches => [ [ [4, 7], [5, 8], 4 ] ],
    }, "$cmd @args IDX MINMATCHLEN 4 WITHMATCHLEN";
};

# https://redis.io/commands/strlen/
subtest STRLEN => sub {
    is $redis->set( mykey => 'Hello world' ), 'OK', 'SET mykey "Hello world"';
    is $redis->strlen('mykey'),               11,   'STRLEN mykey';
    is $redis->strlen('nonexisting'),         0,    'STRLEN nonexisting';
};

done_testing;
