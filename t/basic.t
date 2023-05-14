use Test2::V0 -target => $ENV{REDIS_CLASS} // 'Redis::XS';

my $redis = CLASS->new;

is $redis->flushdb, 'OK', 'FLUSHDB';

is $redis->get('unknown'), undef, 'GET unknown';

is $redis->set('foo', 'bar'), 'OK',    'SET';
is $redis->get('foo'),        'bar',   'GET';
is $redis->keys('*'),         ['foo'], 'KEYS';
is $redis->strlen('foo'),     3,       'STRLEN';

done_testing;
