# https://redis.io/commands/?group=connection
use Test2::V0 -target => $ENV{REDIS_CLASS} // 'Redis::XS';

my $redis   = CLASS->new;
my $version = $redis->redis_version;

# https://redis.io/commands/client-getredir/
# https://redis.io/commands/client-id/
# https://redis.io/commands/client-info/
subtest CLIENT => sub {
    skip_all 'Redis 6.2 required' if $version lt v6.2;

    my $info = {
        'db'       => 0,
        'id'       => $redis->client_id,
      ( 'lib-name' => CLASS          ) x ( $version ge v7.2 ),
      ( 'lib-ver'  => CLASS->VERSION ) x ( $version ge v7.2 ),
        'name'     => CLASS,
        'redir'    => $redis->client_getredir,
      ( 'resp'     => 3              ) x ( $version ge v7.0 ),
        'user'     => 'default',
    };

    like $redis->client_info, $info,                   'CLIENT INFO';
    like $redis->client_list, bag { item $info; etc }, 'CLIENT LIST';
};

# https://redis.io/commands/echo/
is $redis->echo('Hello World!'), 'Hello World!', 'ECHO';

# https://redis.io/commands/ping/
subtest PING => sub {
    is $redis->ping, 'PONG';
    is $redis->ping('Hello World!'), 'Hello World!';
};

# https://redis.io/commands/select/
is $redis->select(0), 'OK', 'SELECT';

done_testing;
