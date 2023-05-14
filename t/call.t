use Test2::V0 -target => 'Redis::XS';

my $txt = quotemeta 'Usage: Redis::XS::call(self, cmd, ...) at ' . __FILE__;
my $err = qr/^$txt line \d+.\n/;

like dies { CLASS->call      }, $err, 'no self';
like dies { CLASS->new->call }, $err, 'no args';

done_testing;
