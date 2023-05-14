package Redis::XS 0.001;

use v5.14;
use warnings;

use XSLoader;

# TODO Port to XS. Work out how we're handling space cmds.
sub client_info {
    return { split /[\s=]/, shift->call(qw(CLIENT INFO)) };
}

# TODO Port to XS. Work out how we're handling space cmds.
sub client_list {
    return [ map +{ split /[\s=]/ }, split /\n/, shift->call(qw(CLIENT LIST)) ];
};

# TODO Port to XS.
sub info {
    my $info = shift->call( INFO => @_ );

    return { map m/^#/ ? () : split( /:/, $_, 2 ), split /\r\n/, $info };
}

# TODO Port to XS.
sub redis_version {
    return version->parse( shift->info('server')->{redis_version} );
}

XSLoader::load;
