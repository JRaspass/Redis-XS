#!perl -T

use Scalar::Util 'tainted';
use Test2::V0 -target => $ENV{REDIS_CLASS} // 'Redis::XS';

skip_all 'Taint support required' unless ${^TAINT};

ok tainted CLASS->new->ping;

done_testing;
