#!/opt/ActivePerl-5.8/bin/perl -w

use strict;
use DBI;
use FileHandle;

my $dbh = DBI->connect("dbi:mysql:sodalord","foo","foopass") || die "Can't connect: $DBI::errstr\n";

my $total_sth = $dbh->prepare("SELECT SUM(tot) FROM user WHERE name != 'tetazoo' AND name != 'testuser' AND name != 'testuser7' AND name != 'frosh'");
$total_sth->execute();
my ($sum) = $total_sth->fetchrow_array;
$total_sth->finish();
$dbh->disconnect();

print "Soda balance is $sum\n";
