#!perl -T

use Scalar::Util 'tainted';
use Test2::V0 -target => $ENV{REDIS_CLASS} // 'Redis::XS';

skip_all 'Taint support required' unless ${^TAINT};

my $redis = CLASS->new;

ok tainted $redis->ping;
ok tainted $redis->get('unknown');

done_testing;
