package Test::Pod;

use strict;

=head1 NAME

Test::Pod - check for POD errors in files

=head1 VERSION

Version 1.20

    $Header: /home/cvs/test-pod/Pod.pm,v 1.10 2004/06/23 05:35:27 andy Exp $

=cut

use vars qw( $VERSION );
$VERSION = '1.20';

=head1 SYNOPSIS

C<Test::Pod> lets you check the validity of a POD file, and report
its results in standard C<Test::Simple> fashion.

    use Test::Pod;
    plan tests => $num_tests;
    pod_file_ok( $file, "Valid POD file" );

Module authors can include the following in a F<t/pod.t> file and
have C<Test::Pod> automatically find and check all POD files in a
module distribution:

    use Test::More;
    eval "use Test::Pod 1.00";
    plan skip_all => "Test::Pod 1.00 required for testing POD" if $@;
    all_pod_files_ok();

You can also specify a list of files to check, using the
C<all_pod_files()> function supplied:

    use strict;
    use Test::More;
    eval "use Test::Pod 1.00";
    plan skip_all => "Test::Pod 1.00 required for testing POD" if $@;
    my @poddirs = qw( blib script );
    all_pod_files_ok( all_pod_files( @poddirs ) );

Or even (if you're running under L<Apache::Test>):

    use strict;
    use Test::More;
    eval "use Test::Pod 1.00";
    plan skip_all => "Test::Pod 1.00 required for testing POD" if $@;

    my @poddirs = qw( blib script );
    use File::Spec::Functions qw( catdir updir );
    all_pod_files_ok(
        all_pod_files( map { catdir updir, $_ } @poddirs )
    );


=head1 DESCRIPTION

Check POD files for errors or warnings in a test file, using
C<Pod::Simple> to do the heavy lifting.

=cut

use 5.004;

use Pod::Simple;
use Test::Builder;
use File::Spec;

my $Test = Test::Builder->new;

use constant OK       =>  0;
use constant NO_FILE  => -2;
use constant NO_POD   => -1;
use constant WARNINGS =>  1;
use constant ERRORS   =>  2;

sub import {
    my $self = shift;
    my $caller = caller;
    no strict 'refs';
    *{$caller.'::pod_ok'}       = \&pod_ok;
    *{$caller.'::pod_file_ok'}  = \&pod_file_ok;
    *{$caller.'::all_pod_files'}  = \&all_pod_files;
    *{$caller.'::all_pod_files_ok'}  = \&all_pod_files_ok;

    *{$caller.'::POD_OK'}       = \&OK;
    *{$caller.'::NO_FILE'}      = \&NO_FILE;
    *{$caller.'::NO_POD'}       = \&NO_POD;
    *{$caller.'::POD_WARNINGS'} = \&WARNINGS;
    *{$caller.'::POD_ERRORS'}   = \&ERRORS;

    $Test->exported_to($caller);
    $Test->plan(@_);
}

=head1 FUNCTIONS

=head2 pod_file_ok( FILENAME[, TESTNAME ] )

C<pod_file_ok()> will okay the test if the POD parses correctly.  Certain
conditions are not reported yet, such as a file with no pod in it at all.

When it fails, C<pod_file_ok()> will show any pod checking errors as
diagnostics.

The optional second argument TESTNAME is the name of the test.  If it
is omitted, C<pod_file_ok()> chooses a default test name "POD test
for FILENAME".

=cut

sub pod_file_ok {
    my $file = shift;
    my $name = @_ ? shift : "POD test for $file";

    if ( !-f $file ) {
        $Test->ok( 0, $name );
        $Test->diag( "$file does not exist" );
        return;
    }

    my $checker = Pod::Simple->new;

    $checker->output_string( \my $trash ); # Ignore any output
    $checker->parse_file( $file );

    my $ok = !$checker->any_errata_seen;
    $Test->ok( $ok, $name );
    if ( !$ok ) {
        my $lines = $checker->{errata};
        for my $line ( sort { $a<=>$b } keys %$lines ) {
            my $errors = $lines->{$line};
            $Test->diag( "$file ($line): $_" ) for @$errors;
        }
    }

    return $ok;
} # pod_file_ok

=head2 all_pod_files_ok( [@files/@directories] )

Checks all the files in C<@files> for valid POD.  It runs
L<all_pod_files()> on each file/directory, and calls the C<plan()> function for you
(one test for each function), so you can't have already called C<plan>.

If C<@files> is empty or not passed, the function finds all POD files in
the F<blib> directory if it exists, or the F<lib> directory if not.
A POD file is one that ends with F<.pod>, F<.pl> and F<.pm>, or any file
where the first line looks like a shebang line.

If you're testing a module, just make a F<t/pod.t>:

    use Test::More;
    eval "use Test::Pod 1.00";
    plan skip_all => "Test::Pod 1.00 required for testing POD" if $@;
    all_pod_files_ok();

Returns true if all pod files are ok, or false if any fail.

=cut

sub all_pod_files_ok {
    my @files = @_ ? @_ : all_pod_files();

    $Test->plan( tests => scalar @files );

    my $ok = 1;
    foreach my $file ( @files ) {
        pod_file_ok( $file, $file ) or undef $ok;
    }
    return $ok;
}

=head2 all_pod_files( [@dirs] )

Returns a list of all the Perl files in I<$dir> and in directories below.
If no directories are passed, it defaults to F<blib> if F<blib> exists,
or else F<lib> if not.  Skips any files in CVS or .svn directories.

A Perl file is:

=over 4

=item * Any file that ends in F<.PL>, F<.pl>, F<.pm>, F<.pod> or F<.t>.

=item * Any file that has a first line with a shebang and "perl" on it.

=back

The order of the files returned is machine-dependent.  If you want them
sorted, you'll have to sort them yourself.

=cut

sub all_pod_files {
    my @queue = @_ ? @_ : _starting_points();
    my @pod = ();

    while ( @queue ) {
        my $file = shift @queue;
        if ( -d $file ) {
            local *DH;
            opendir DH, $file or next;
            my @newfiles = readdir DH;
            closedir DH;

            @newfiles = File::Spec->no_upwards( @newfiles );
            @newfiles = grep { $_ ne "CVS" && $_ ne ".svn" } @newfiles;

            push @queue, map "$file/$_", @newfiles;
        }
        if ( -f $file ) {
            push @pod, $file if _is_perl( $file );
        }
    } # while
    return @pod;
}

sub _starting_points {
    return 'blib' if -e 'blib';
    return 'lib';
}

sub _is_perl {
    my $file = shift;

    return 1 if $file =~ /\.PL$/;
    return 1 if $file =~ /\.p(l|m|od)$/;
    return 1 if $file =~ /\.t$/;

    local *FH;
    open FH, $file or return;
    my $first = <FH>;
    close FH;

    return 1 if defined $first && ($first =~ /^#!.*perl/);

    return;
}

=head2 pod_ok( FILENAME [, EXPECTED [, NAME ]]  )

Note: This function is B<deprecated>.  Use pod_file_ok() going forward.

pod_ok parses the POD in filename and returns one of five
symbolic constants starting from the top of this list:

        NO_FILE       Could not find the file
        NO_POD        File had no pod directives
        POD_ERRORS    POD had errors
        POD_WARNINGS  POD had warnings
        POD_OK        No errors or warnings

pod_ok will okay the test if you don't specify any expected
result and it finds no errors or warnings, or if you specify
what you expect and it finds that condition.  For instance, if
you can live with warnings,

        pod_ok( $file, POD_WARNINGS );

When it fails, pod_ok will show any pod checking errors.

The optional third argument NAME is the name of the test
which pod_ok passes through to Test::Builder.  Otherwise,
it chooses a default test name "POD test for FILENAME".

=cut

sub pod_ok {
    my $filename = shift;
    my $expected = shift; # No longer used

    my $ok = pod_file_ok( $filename, @_ );
    $Test->diag( "NOTE: pod_ok() is deprecated" );
    return $ok;
} # pod_ok


=head1 TODO

STUFF TO DO

Note the changes that are being made.

Note that you no longer can test for "no pod".

=head1 AUTHOR

Currently maintained by Andy Lester, C<< <andy@petdance.com> >>.

Originally by brian d foy, C<< <bdfoy@cpan.org> >>.

=head1 COPYRIGHT

Copyright 2004, Andy Lester, All Rights Reserved.

You may use, modify, and distribute this package under the
same terms as Perl itself.

=cut

1;
