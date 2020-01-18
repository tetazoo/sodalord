#!/usr/athena/bin/perl -w
use DBI;

# format of database: name email debt h00-h23 pwd time

my $dbh = DBI->connect("dbi:mysql:sodalord","foo","foopass") || die "Can't connect: $DBI::errstr";
my $getid_sth = $dbh->prepare("SELECT user.* FROM user,names WHERE user.name=names.id AND names.alias=?");

sub in_keys
{
    my $id = shift;
    $getid_sth->execute($id);
    my $arrayref = $getid_sth->fetchrow_arrayref;
    return ($arrayref ? (@$arrayref) : 0);
}
if ( my @baz = split ' ', <STDIN> ) {
    chomp @baz;
    if ( $baz[0] !~ /\W/i ) {
	chomp $baz[0];
	my ($name, undef, $debt, @key) = (in_keys($baz[0]));
	if (@key)
	{
	    my $tally = 0;
	    for (my $i=0; $i < 24; $i++)
	    {
		$tally += $key[$i];
	    }
	    print "$name has a soda tally of $tally and a debt of $debt.\n";
	}
	else { print "$baz[0] doesn't have a sodalord account\n"; }
    } else {print "Use alphanumerics only!\n";}
}
