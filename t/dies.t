use Test2::V0 -target => 'Redis::XS';

sub t(&$);

t { CLASS->call      } 'Usage: Redis::XS::call(self, cmd, ...)';
t { CLASS->new->call } 'Usage: Redis::XS::call(self, cmd, ...)';

t { CLASS->new( host => 'foo' ) } 'Connection error: No address associated with hostname';
t { CLASS->new( port => 9999  ) } 'Connection error: Connection refused';

sub t(&$) {
    my ( $code, $err ) = @_;

    $err = quotemeta "$err at " . __FILE__;

    like &dies($code), qr/^$err line \d+\.\n$/;
}

done_testing;
