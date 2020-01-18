#!/usr/athena/bin/perl -w
open(LOGFILE,">>/soda/logs/sodacard.log");

$< = 35366;
$> = 35366;
use strict;
use DBI;
use Digest::MD5 qw( md5 md5_base64);
use Fcntl;

$ENV{'KRB5CCNAME'} = "/tmp/krb5cc_sodacard";
$ENV{'KRBTKFILE'} = "/tmp/tkt_sodacard";

my $sodacost = .5;
my $hardlimit = 0.5;
my $softlimit = 0;
print LOGFILE "Gets this far\n";
my $dbh = DBI->connect("dbi:mysql:sodalord", "foo", "foopass") || print LOGFILE "Can't connect: $DBI::errstr\n";
print LOGFILE "Gets a little further...\n";

my $values_sth = $dbh->prepare("SELECT user.* FROM user,names WHERE names.alias=? and names.id=user.name");
my $whose_card_sth = $dbh->prepare("SELECT user.name FROM user,names,card WHERE card.card=? AND card.user=names.alias AND user.name=names.id");
my $aliases_sth = $dbh->prepare("SELECT alias FROM names WHERE id=?");

system "stty -echo";
#system "stty echo";

$SIG{ALRM} = \&add_card;
print LOGFILE "should work from here!\n";



sub add_card
{
    print "\n\nSwipe your card now!\n\n";
    sysopen(FIFO, "/soda/pipe", O_WRONLY);
    chomp(my $card = <STDIN>);
    my $cryptocard = md5_base64($card);
    print FIFO $cryptocard . "\n";
    close FIFO;
    print "\nCard swiped and sent.  Thank you!\n\n";
}
    

sub bought_soda
{
    my $time = shift;
    $time = ($time < 10) ? "H0$time" : "H$time";
    my $user = shift;
    my $sql_string = "UPDATE user SET tot=tot+1, $time=$time+1 WHERE name=\'$user\' OR name='tetazoo'";
    my $sth = $dbh->prepare("$sql_string");
    $sth->execute();
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
    $aliases_sth->execute("$name");
    my @aliases = map { $$_[0] } @{$aliases_sth->fetchall_arrayref};
    my $randalias = $aliases[rand ($#aliases + 1)];
    my @time = localtime();
    my $hour = $time[2];
    $values_sth->execute("tetazoo");
    my @tetazoodata = @{$values_sth->fetchrow_arrayref};
    my $curdebt = ($data[2]+1) * -1 * $sodacost;
    open(SODACONSOLE, ">/dev/ttyS0");
    print SODACONSOLE "\n\n$name bought a soda on the card!\n\n";
    printf SODACONSOLE "Authenticated.  Have a soda!\n\nYou have \$ %.2f left on your account.\n", $curdebt;
    close SODACONSOLE;
    print_time();
    print LOGFILE "$randalias bought a soda on the card!\n";
    bought_soda($hour,$data[0]);
    system("/soda/zinitc.sh");
    if ($data[2] > $softlimit)
    {
	my $penalty = $data[2] - $softlimit;
	my $ouch = int(3**$penalty) + 1;
	    
	open (ZEPHYR, "|/usr/athena/bin/zwrite -s \"I am your god.\" -c sodalord -i $randalias");
	print ZEPHYR "\n$randalias is over the soft credit limit! Laugh as he/she waits for $ouch seconds!";
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
	open (ZEPHYR, "|/usr/athena/bin/zwrite -s \"I am your god.\" -c sodalord -i $randalias");
	print ZEPHYR "$randalias bought a soda on the card!";
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
    $whose_card_sth->execute($cryptocard);
    my $arrayref = $whose_card_sth->fetchrow_arrayref;
    return ($arrayref ? ${$arrayref}[0] : undef);
}


for(;;) {
    print "\nCard Reader: ";
    chomp(my $foo = <STDIN> );

    if (($foo) && (my $id = key($foo))) {
	buy_soda($id);
    }
    elsif ($foo) {
	print "Unknown card.\n";
    }
}
