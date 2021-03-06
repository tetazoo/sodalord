
use strict;
use Pod::Simple::Search;
use Test;
BEGIN { plan tests => 7 }

print "# ", __FILE__,
 ": Testing the scanning of several (well, two) docroots...\n";

my $x = Pod::Simple::Search->new;
die "Couldn't make an object!?" unless ok defined $x;

$x->inc(0);

$x->callback(sub {
  print "#  ", join("  ", map "{$_}", @_), "\n";
  return;
});

use File::Spec;
use Cwd;
my $cwd = cwd();
print "# CWD: $cwd\n";

my($here1, $here2);
if(        -e ($here1 = File::Spec->catdir($cwd,      'test^lib'      ))) {
  die "But where's $here2?"
    unless -e ($here2 = File::Spec->catdir($cwd,      'other^test^lib'));
} elsif(   -e ($here1 = File::Spec->catdir($cwd, 't', 'test^lib'      ))) {
  die "But where's $here2?"
    unless -e ($here2 = File::Spec->catdir($cwd, 't', 'other^test^lib'));
} else {
  die "Can't find the test corpora";
}
print "# OK, found the test corpora\n#  as $here1\n# and $here2\n";
ok 1;

print $x->_state_as_string;
#$x->verbose(12);

use Pod::Simple;
*pretty = \&Pod::Simple::BlackBox::pretty;

print "# OK, starting run...\n# [[\n";
my($name2where, $where2name) = $x->survey($here1, $here2);
print "# ]]\n#OK, run done.\n";

my $p = pretty( $where2name, $name2where )."\n";
$p =~ s/, +/,\n/g;
$p =~ s/^/#  /mg;
print $p;

{
my $names = join "|", sort values %$where2name;
ok $names, "Blorm|Sizzlesuzzle|Zonk::Pronk|perlfliff|perlthang|perlzuk|squaa|squaa::Glunk|squaa::Vliff|squaa::Wowo|zikzik";
}

{
my $names = join "|", sort keys %$name2where;
ok $names, "Blorm|Sizzlesuzzle|Zonk::Pronk|perlfliff|perlthang|perlzuk|squaa|squaa::Glunk|squaa::Vliff|squaa::Wowo|zikzik";
}

ok( ($name2where->{'squaa'} || 'huh???'), '/squaa\.pm$/');

ok grep( m/squaa\.pm/, keys %$where2name ), 1;

ok 1;

__END__

