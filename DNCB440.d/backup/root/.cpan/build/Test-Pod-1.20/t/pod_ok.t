#!perl -T

use strict;

use Test::Builder::Tester tests => 1;
use Test::Pod;

use constant DEPRECATED => 'NOTE: pod_ok() is deprecated';

FOO: {
    my $name = 'test ok';
    for ( 1 .. 4 ) {
        test_out( "ok $_ - $name" );
        test_diag( DEPRECATED );
    }
    pod_ok( "t/pod/good.pod",         undef,       , $name );
    pod_ok( "t/pod/good.pod",         POD_OK       , $name );
    pod_ok( "t/pod/good.pod",         POD_WARNINGS , $name );
    pod_ok( "t/pod/good.pod",         POD_ERRORS   , $name );

    test_test( 'All files okay with explicit (but deprecated) expectations' );
}
