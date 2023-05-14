use v5.14;
use warnings;

use ExtUtils::MakeMaker;

WriteMakefile
    CCFLAGS      => "$Config::Config{ccflags} -Wall -Wextra -std=c99",
    LIBS         => '-lcrypto -lssl',
    MYEXTLIB     => join( ' ', <hiredis/libhiredis{,_ssl}\$(LIB_EXT)> ),
    NAME         => 'Redis::XS',
    VERSION_FROM => 'lib/Redis/XS.pm',

    # Duplicated in cpanfile for GitHub Actions.
    # TODO add the other phases.
    TEST_REQUIRES => {
        'Test2::Suite' => '0.000072',   # For Test2::V0.
    };

sub MY::postamble { <<'MAKE' }
$(MYEXTLIB): hiredis/Makefile
	$(MAKE) -C hiredis USE_SSL=1
MAKE
