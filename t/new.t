# Test passing arguments to new().
use Test2::V0 -target => $ENV{REDIS_CLASS} // 'Redis::XS';

like dies { CLASS->new(1) }, qr/^Odd number of arguments at /, 'Odd args';

like dies { CLASS->new( foo => 1 ) }, qr/^Unknown argument: foo at /, 'Unknown arg';

is CLASS->new( name => 'foo' )->client_getname, 'foo', 'name => "foo"';

done_testing;
