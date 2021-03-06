#!/usr/athena/bin/perl -w

use DBI;
use Digest::MD5 qw( md5 md5_base64);

my $sodacost = .4;
my $hardlimit = 0.5;
my $softlimit = 0;
open(LOGFILE,">>/soda/logs/sodacard.log");

my $dbh = DBI->connect("dbi:mysql:sodalord") || die "Can't connect: $DBI::errstr\n";

my $values_sth = $dbh->prepare("SELECT user.* FROM user,names WHERE names.alias=? and names.id=user.name");
my $whoami_sth = $dbh->prepare("SELECT id FROM names WHERE alias = ?");
my $whose_card_sth = $dbh->prepare("SELECT user FROM card WHERE card=?");
my $add_card_sth = $dbh->prepare("INSERT INTO card VALUES (?,?)");

system "stty -echo";

sub bought_soda
{
    my $time = shift;
    $time = ($time < 10) ? "H0$time" : "H$time";
    my $user = shift;
    my $sql_string = "UPDATE user SET tot=tot+1, $time=$time+1 WHERE name=\'$user\' OR name='tetazoo'";
    my $sth = $dbh->prepare("$sql_string");
    $sth->execute();

}

sub in_keys
{
    my $alias = shift;
    $whoami_sth->execute("$alias");
    my $arrayref = $whoami_sth->fetchrow_arrayref;
    return ${$arrayref}[0] if (defined $arrayref);
    return 0;
} 

sub buy_soda
{
    my $name = shift;
    my $word = "";
    $values_sth->execute("$name");
    my @data = @{$values_sth->fetchrow_arrayref};
    if ($data[2] + 1 > $hardlimit)
    {
	print "You have reached the hard soda limit ($hardlimit). Please add more credit to\nyour account.\n";
	return;
    }
    my @time = localtime();
    my $hour = $time[2];
    $values_sth->execute("tetazoo");
    my @tetazoodata = @{$values_sth->fetchrow_arrayref};
    my $curdebt = $data[2] * -1 * $sodacost;
    printf "Authenticated.  Have a soda!\n\nYou have \$ %.2f left on your account.\n", $curdebt;
    print_time();
    print LOGFILE "$name bought a soda on the card!\n";
    bought_soda($hour,$data[0]);
    
    system("/soda/zinit.sh");
    if ($data[2] > $softlimit)
    {
	my $penalty = $data[2] - $softlimit;
	my $ouch = int(3**$penalty) + 1;
	    
	open (ZEPHYR, "|/usr/athena/bin/zwrite -s \"I am your god.\" -c sodalord");
	print ZEPHYR "\n$name is over the soft credit limit! Laugh as he/she waits for $ouch seconds!";
	close ZEPHYR;
	print "\nYou are over the soft credit limit!  Pay tha man... C'mon...\n";
	print "You are over the soft credit limit by $penalty sodas.  So.  You now have to\nsuffer DELAYED GRATIFICATION!!\n\nYour soda will be freed Real Soon Now(tm).\n";

	for(my $i=0;$i<$ouch;$i++)
	{
	    print "$i ";
	    sleep 1;
	}	       
	print "\n";
	system("/soda/lpt_out","255");
	select(undef, undef, undef, 0.5);
	system("/soda/lpt_out","0"); 
    }
    else
    {
	system("/soda/lpt_out","255");
	select(undef, undef, undef, 0.5);
	system("/soda/lpt_out","0"); 
	open (ZEPHYR, "|/usr/athena/bin/zwrite -s \"I am your god.\" -c sodalord");
	print ZEPHYR "$name bought a soda on the card!";
	close ZEPHYR;
    }

}

sub print_time
{
    my $now = localtime;
    print LOGFILE "Time: $now\n";
}


sub key {
    my $foo = shift;
    my $cryptocard = md5_base64($foo);
#    print "Cryptocard: $cryptocard\n";
    $whose_card_sth->execute($cryptocard);
    my $arrayref = $whose_card_sth->fetchrow_arrayref;
    return ($arrayref ? ${$arrayref}[0] : undef);
}


for(;;) {
    print "Card Reader: ";
    chomp(my $foo = <STDIN>);
    if ($foo =~ /^addcard$/i)
    {
	print "\nEnter username: ";
	chomp(my $user = <STDIN>);
	print "\n\nSwipe card: ";
	chomp(my $card = <STDIN>);
	my $cryptocard = md5_base64($card);
	print "Cryptocard: $cryptocard\n";
	$add_card_sth->execute($cryptocard,$user) ? print "\nSuccessfully added card to $user.\n" : print "\nFailed to add card.\n";
	
    }

    elsif (($foo) && (my $id = key($foo))) {
#	print "A card belonging to $id was swiped!\n";
	buy_soda($id);
    }
    elsif ($foo) {
	print "Unknown card.\n";
    }
}



