#!/opt/ActivePerl-5.8/bin/perl -w

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

	if ($baz[0] eq "total") {
	    my $total_sth = $dbh->prepare("SELECT SUM(tot) FROM user WHERE name != 'tetazoo' AND name != 'testuser' AND name != 'testuser7' AND name != 'frosh'");
	    $total_sth->execute();
	    my ($sum) = $total_sth->fetchrow_array;
	    printf "Total soda balance is \$ %.2f.\n", $sum;
	    $total_sth->finish();
	    $dbh->disconnect();
	    exit 0;
	}

	my ($name, undef, $balance, @key) = (in_keys($baz[0]));
	if (@key)
	{
	    my $tally = 0;
	    for (my $i=0; $i < 24; $i++)
	    {
		$tally += $key[$i];
	    }
	    printf "$name has a soda tally of $tally and a balance of \$ %.2f.\n", $balance;
	}
	else { print "$baz[0] doesn't have a sodalord account\n"; }
    } else {print "Use alphanumerics only!\n";}
}
