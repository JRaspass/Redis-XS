use Test2::V0 -target => $ENV{REDIS_CLASS} // 'Redis::XS';

my $redis = CLASS->new;

skip_all 'Redis 7.0 required' if $redis->redis_version lt v7;

ok $redis->can(s/\W/_/gr), $_ for sort $redis->command_list;

done_testing;
