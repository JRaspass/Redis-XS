# https://redis.io/commands/?group=json
use Test2::V0 -target => $ENV{REDIS_CLASS} // 'Redis::XS';

my $redis = CLASS->new;

skip_all 'Module ReJSON required'
    unless grep $_->{name} eq 'ReJSON', $redis->module_list;

# https://redis.io/commands/json.strlen/
subtest JSON_STRLEN => sub {
    is $redis->flushdb, 'OK', 'FLUSHDB';

    my $doc = '{"a":"foo", "nested": {"a": "hello"}, "nested2": {"a": 31}}';
    is $redis->json_set('doc', '$', $doc), 'OK', 'JSON.SET';

    is $redis->json_strlen(qw(doc $..a)), [3, 5, undef], 'JSON.STRLEN';
};

is $redis->flushdb, 'OK', 'FLUSHDB';

done_testing;
