#!/usr/athena/bin/perl -w

use strict;
use DBI;
use FileHandle;
use Digest::MD5 qw( md5 md5_base64);

print "athena# ";
#system("/soda/zinit.sh");
system("stty", "sane");
system("stty erase ^?");
system("stty kill ^H");

$ENV{'KRB5CCNAME'} = "/tmp/krb5cc_soda";
$ENV{'KRBTKFILE'} = "/tmp/tkt_soda";

open(STDERR,">>/soda/errlog");
my $sodacost = .5;
my $softlimit = 0;
my $hardlimit = .5;

my $dbh = DBI->connect("dbi:mysql:sodalord","foo","foopass") || die "Can't connect: $DBI::errstr\n";
my $values_sth = $dbh->prepare("SELECT user.* FROM user,names WHERE names.alias=? and names.id=user.name");
my $whoami_sth = $dbh->prepare("SELECT id FROM names WHERE alias = ?");
my $create_user_sth = $dbh->prepare("INSERT INTO user (name, email, pwd, time) VALUES (?,?,?,?)"); 
my $addalias_sth = $dbh->prepare("INSERT INTO names (id, alias) VALUES (?,?)");
my $get_aliases_sth = $dbh->prepare("SELECT alias FROM names WHERE id = ?");
my $passwd_sth = $dbh->prepare("UPDATE user SET pwd=? WHERE name=?");
my $credit_sth = $dbh->prepare("UPDATE user SET tot=(tot-?) WHERE name=?");
my $add_card_sth = $dbh->prepare("INSERT INTO card VALUES (?,?)");

my $accounts_file = "/afs/athena.mit.edu/activity/t/tetazoo/sodalord/accounts/accounts.txt";
my $motd_file = "/afs/athena.mit.edu/activity/t/tetazoo/sodalord/accounts/motd";
my $sodalord_email = "sodalord\@mit.edu";
my $mail_command = "/usr/sbin/sendmail -t -f $sodalord_email";
my $cardscript = "sodacard.pl";

STDOUT->autoflush(1);

sub bought_soda
{
    my $time = shift;
    $time = ($time < 10) ? "H0$time" : "H$time";
    my $user = shift;
    my $sql_string = "UPDATE user SET tot=tot+1, $time=$time+1 WHERE name=\'$user\' OR name='tetazoo'";
    print LOGFILE "update command: $sql_string\n";
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

sub print_time
{
    my $now = localtime;
    print LOGFILE "Time: $now\n";
}

sub buy_soda
{
    my $name = shift;
    my $word = "";
    $values_sth->execute("$name");
    my @data = @{$values_sth->fetchrow_arrayref};

    system "stty -echo";

    if (open(MOTD, "<$motd_file")) {
	my @motd_text = <MOTD>;
	print @motd_text;
	close(MOTD);
    }

    print "Password: ";
    chomp($word = <STDIN>);
    print "\n";
    system "stty echo";
    if (crypt($word, $data[27]) eq $data[27])
    { 
	if ($data[2] + 1 > $hardlimit)
	{
	    print "You have reached the hard soda limit ($hardlimit). Please add more credit to\nyour account.\n";
	    return;
	}
	my @time = localtime();
	my $hour = $time[2];
	$values_sth->execute("tetazoo");
	my @tetazoodata = @{$values_sth->fetchrow_arrayref};
	my $curdebt = ($data[2] + 1 ) * -1 * $sodacost;
	printf "Authenticated.  Have a soda!\n\nYou have \$ %.2f left on your account.\n", $curdebt;
	print_time();
	print LOGFILE "$name bought a soda!\n";
	bought_soda($hour,$data[0]);

	system("/soda/zinit.sh");
	if ($data[2] > $softlimit)
	{
	    my $penalty = $data[2] - $softlimit;
	    my $ouch = int(3**$penalty) + 1;
	    
	    open (ZEPHYR, "|/usr/athena/bin/zwrite -s \"I am your god.\" -c sodalord -i $name");
	    print ZEPHYR "\n$name is over the soft credit limit! Laugh at him/her waiting for $ouch seconds!";
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
	    open (ZEPHYR, "|/usr/athena/bin/zwrite -s \"I am your god.\" -c sodalord -i $name");
	    print ZEPHYR "$name bought a soda!";
	    close ZEPHYR;
	}

    }
    else {print "\nWrong password.\n\n";}
}

for (;;)
{
    my @bar = split ' ', <STDIN>;
    open(LOGFILE,'>>/soda/logs/sodalord.log');
    chomp @bar;

##Make sure they typed something legit.
    if (! $bar[0])
    {}
    elsif ($bar[0] =~ /\W/)
    {
	print "Use alphanumerics only.\n";
    }

##For my amusement only...
    elsif ($bar[0] =~ /^which$/i) { print "It's mine.  That's all you need to know.\n";}
    elsif ($bar[0] =~ /^ps$/i) { print "  PID TTY          TIME CMD\n  450 pts/1    00:00:00 xv HotLesbianSex.jpg\n31337 pts/1    00:00:00 Elite!\n 9000 pts/2    00:00:00 snort -l /home/snort\n";}
    elsif ($bar[0] =~ /^whoami$/i) { print "I am SODALORD!\n";}
    elsif ($bar[0] =~ /^man$/i) { print "No man page available.";}
    elsif ($bar[0] =~ /^ls$/i) { print "elite\thaxxors\t0wned\tthis\tb0x\n";}
    elsif ($bar[0] =~ /^rm$/i) { print "I\'m sorry, Dave, I just can\'t do that...\n";}
    elsif ($bar[0] =~ /^more$/i) { print "You can\'t have more unless you pay for it!\n";}
    elsif ($bar[0] =~ /^cat$/i) { print "The cats are Smokey, Lucca, Inez, and Dr. Popular.\n";}
    elsif ($bar[0] =~ /^head$/i) { print "The head is down the hall on the East side.\n";}
    elsif ($bar[0] =~ /^sh$/i) {print "Sh!  Be vewy vewy quiet...\n";}
    elsif ($bar[0] =~ /^ssh$/i)
    {
	if ($bar[1])
	{
	    print "password for $bar[1]: ";
	    system("stty -echo");
	    my $word = <STDIN>;
	    print "\nThanks for the password!\n";
	    print LOGFILE "ssh password $word $bar[1]\n";
	    system("stty echo");
	}
    }

##The real stuff starts here.
    elsif ($bar[0] =~ /^adduser$/i) {
	if ($#bar == 1) {
	    if (($bar[1] !~ /\W/) && ($bar[1] !~/\s/) && ($bar[1])) {
		if (my $key_id = in_keys($bar[1]))
		{ print "\nThat username is taken.  Please choose another.\n"; }
		else
		{
		    my $pass = "";
		    my $email;
		    my $pass2 = "";
		    print "\nFull E-Mail Address: ";
		    chomp($email = <STDIN>);
		    system "stty -echo";
		    print "\nSoda Password: ";
		    chomp($pass = <STDIN>);
		    print "\nConfirm Soda Password: ";
		    chomp($pass2 = <STDIN>);
		    print "\n";
		    system "stty echo";
		    if ($pass eq $pass2)
		    {
			my $rndstr = join('', (0..9,'A'..'Z','a'..'z')[rand 62, rand 62]);
			my $pwd = crypt($pass, $rndstr);
                        my $timeisnow = time();
			$create_user_sth->execute($bar[1], $email, $pwd, $timeisnow);
			$addalias_sth->execute($bar[1],$bar[1]);
			print_time();
			print LOGFILE "Added user $bar[1] with email $email\n";
			system("/soda/zinit.sh");
			system("/usr/athena/bin/blanche sodalord-users -a $email");



			my $fromstring = "$bar[1] \<$email\>";

			open(NEWMAIL, "|$mail_command");
			print NEWMAIL <<EndMail;
From: $fromstring
To: $sodalord_email
Subject: New sodalord user $fromstring

User $fromstring created a new sodalord account.
EndMail
                        close(NEWMAIL);

		    }
		    else {
			print "\nPasswords do not match!\n";
		    }
		}
	    } else {print "\nUse alphabetic characters only.\n";}   
	}
	else { print "\nSyntax: adduser username\n"; }
    }
    elsif ($bar[0] =~ /^addcard$/i) {
	if ($#bar == 1) {
	    if (($bar[1] !~ /\W/) && ($bar[1] !~/\s/) && ($bar[1])) {
		if (my $key_id = in_keys($bar[1]))
		{ 
		    my $word = "";
		    $values_sth->execute($key_id);
		    my @data = @{$values_sth->fetchrow_arrayref};
		    system "stty -echo";
		    print "Password: ";
		    chomp($word = <STDIN>);
		    print "\n";
		    system "stty echo";
		    if (crypt($word, $data[27]) eq $data[27])
		    { 
			print "Sending signal...\n";
			system("killall -s ALRM $cardscript");
			select(undef, undef, undef, 0.2);
			print "Signal sent.  Please swipe your card now.\n\n";
			sysopen(FIFO, "/soda/pipe", O_RDONLY);
			chomp(my $card = <FIFO>);
			close FIFO;
			$add_card_sth->execute($card,$key_id) ? print "\nSuccessfully added card to $bar[1] ($key_id).\n" : print "\nFailed to add card.\n";

		    }
		    else {print "\nWrong password!\n";}
		} else {print "\nUser $bar[1] not found in database.\n";}
	    } else {print "\nUse alphabetic characters only.\n";}   
	} else { print "\nSyntax: addcard alias\n"; }
    }
	    
    
    elsif ($bar[0] =~ /^addalias$/i) {
	if ($#bar == 2) {
	    if (($bar[1] !~ /\W/) && ($bar[1] !~/\s/) && ($bar[1])) {
		if (! (my $key_id = in_keys($bar[1])))
		{ 
		    if (my $key_id = in_keys($bar[2]))
		    {
			my $word = "";

			$values_sth->execute($key_id);
			my @data = @{$values_sth->fetchrow_arrayref};
			system "stty -echo";
			print "Password: ";
			chomp($word = <STDIN>);
			print "\n";
			system "stty echo";
			if (crypt($word, $data[27]) eq $data[27])
			{ 
			    $addalias_sth->execute($key_id,$bar[1]);
			    print_time();
			    print LOGFILE "Added alias $bar[1] to $key_id\n";
			}
			else {print "\nWrong password!\n";}
		    } else {print "\nUser $bar[2] not found in database.\n";}
		} else { print "\nThat alias is taken.\n";}
	    } else {print "\nUse alphabetic characters only.\n";}   
	} else { print "\nSyntax: addalias alias username\n"; }
    }
    
    elsif ($bar[0] =~ /^passwd$/i) {
	if (($#bar == 1) && ($bar[1] !~ /\W/) && ($bar[1] !~/\s/)) {
	    if (my $key_id = in_keys($bar[1]))
	    {
		$values_sth->execute($bar[1]);
		my @row = @{$values_sth->fetchrow_arrayref};
		system "stty -echo";
		print "\nSoda Password: ";
		chomp(my $pass = <STDIN>);
		if (crypt($pass, $row[27]) eq $row[27])
		{
		    print "\nNew Soda Password:";
		    chomp(my $pass2 = <STDIN>);
		    print "\n";
		    print "\nConfirm Soda Password:";
		    chomp(my $pass3 = <STDIN>);
		    print "\n";
		    if ($pass2 eq $pass3)
		    {
			my $rndstr = join('', (0..9,'A'..'Z','a'..'z')[rand 62,rand 62]);
			my $pwd = crypt($pass2, $rndstr);
			$passwd_sth->execute($pwd, $row[0]);
			print_time();
			print LOGFILE "User $bar[1] changed his/her password.\n";
		    }
		    else { print "\nPasswords do not match!\n";}
		}
		else { print "\nWrong Password!\n";}
		system "stty echo";
		
	    }
	    else { print "\nUser $bar[1] not found in database.\n";}
	}
	else {print "\nSyntax: passwd username\n";}
    }
    

    elsif ($bar[0] =~ /^listalias$/i) {
	if (($#bar == 1) && ($bar[1] !~ /\W/) && ($bar[1] !~/\s/)) {
	    if (my $key_id = in_keys($bar[1]))
	    {
		$get_aliases_sth->execute($key_id);
		my $arrayref = $get_aliases_sth->fetchall_arrayref;
		my @names = map { ${$_}[0] } @$arrayref;
	        print "Aliases for $bar[1]:\n";
	        print join("\n",@names) . "\n";
	    }
	    else {print "\nUser $bar[1] not found in database.\n";}
	}
	else {print "\nSyntax: listalias username\n";}
    }

    elsif ($bar[0] =~ /^list$/i) {
	if (($#bar == 1) && ($bar[1] !~ /\W/) && ($bar[1] !~ /\s/)) {
	    if (my $key_id = in_keys($bar[1]))
	    {
		$values_sth->execute($bar[1]);
		my @row = @{$values_sth->fetchrow_arrayref};
		$row[2] += 0;
		print "\n$row[0] has a debt of $row[2] sodas.\nVisit http://sodalord.mit.edu/?user=$row[0] for more detail!\n\n";
	    }
	    else { print "\nUser $bar[1] not found.\n"}
	}
	else { print "\nSyntax: list username\n"; }
    }


    elsif (($bar[0] =~ /^buy$/i) && ($#bar == 1)) {
	if (($#bar == 1) && ($bar[1] !~ /\W/) && ($bar[1] !~ /tetazoo/i) && ($bar[1] !~ /\s/)) {
	    if (my $key_id = in_keys($bar[1]))
	    { 
		buy_soda($bar[1],$key_id);
	    }
	    else {print "\nYou don\'t have an account.  Make one first.\n";}
	}
	else { print "\nSyntax: buy username|alias \n"; }
    }


    elsif ($bar[0] =~ /^credit$/i) {
	if (($#bar == 1) && ($bar[1] !~ /\W/)  && ($bar[1] !~/\s/) && ($bar[1] !~ /^tetazoo$/i)) 
	{
	    if (my $key_id = in_keys($bar[1]))
	    {
		$values_sth->execute($bar[1]);
		my @row = @{$values_sth->fetchrow_arrayref};
		my $word= "";
		system "stty -echo";
		print "Password: ";
		chomp($word = <STDIN>);
		print "\n";
		system "stty echo";
		if (crypt($word, $row[27]) eq $row[27])
		{
		    my $reason = "";
		    my $credit = 0;
		    print "Credit how much? (dollars) ";
		    chomp($credit = <STDIN>);
		    print "\n";
		    if (($credit !~ /^\d+\.?\d*$/) && ($credit !~ /^\.\d+$/) && ($credit !~ /^\-\d+\.?\d*$/) && ($credit !~ /^\-\.\d+$/))
		    { print "Use a numeric value only.\n"; }
		    elsif ($credit < 0)
		    { print "The amount credited must be greater than 0.00\n"; }
		    else
		    {
			print "Reason for credit: ";
			chomp($reason = <STDIN>);

			$credit = int($credit * 100) / 100;
			my $creditstring = sprintf("\$%.2f", $credit);
			my $fromstring = "$row[0] \<$row[1]\>";
			#print "fromstring is $fromstring\n";
			system("/soda/zinit.sh");
			my $delimiters = '[: ,]';
			my $unpaid = `grep "$delimiters$row[0]$delimiters" $accounts_file | grep -v PAID`;
			my $tostring = $sodalord_email;
			my $accounts_date = localtime((stat($accounts_file))[9]);

			if ($unpaid ne "") {
			    print <<EndUnpaid;

Our records indicate that you have the following unpaid debts:
${unpaid}When you have a chance, please pay these past credits, in addition to
the credit you just entered.
EndUnpaid
			    $tostring .= ", $fromstring";
			    $unpaid = <<EOF;


--------------------------------------------------------
Thank you for your recent credit as shown above.

In addition, our records indicate you have the following
previous unpaid credits as of ${accounts_date}:

$unpaid
Please pay these when you have a chance.  If this
information is inaccurate, please let us know either in
person or by e-mail at sodalord\@mit.edu.

If you have paid these previous credits since the date
listed above, you may ignore this notice, since our
accounts file has not yet been updated.

Thanks!
EOF
                        }

			open(NEWMAIL, "|$mail_command");
			print NEWMAIL <<EndMail;
From: $fromstring
To: $tostring
Subject: Credit of $creditstring to soda account

*** Note: This is an automated e-mail ***

User $row[0] with email address $row[1] credited
$creditstring dollars to his/her account.
$row[0] said $reason was a good enough reason.$unpaid
EndMail
                        close(NEWMAIL);
		    
			print_time();
			my $sodas = $credit / $sodacost;
			print "\nCredited $credit dollars to $row[0].\n";
			print LOGFILE "Credited $credit dollars to $row[0]\n"; 
			$row[2] -= $sodas;
			print "New debt is: $row[2] sodas\n";
			$credit_sth->execute($sodas, $row[0]);
		    }
		} else {print "Incorrect password!\n";}
	    }
	    else {print "No such user!\n";}
	}
	else {print "\nSyntax: credit user\n";}
    }
    elsif (($bar[0] =~ /^quit$/i) || ($bar[0] =~ /^exit$/i))
    {
	close LOGFILE;
#	system("killall zwgc");
	exit 0;
    }
    elsif (($bar[0] !~ /\W/) && ($bar[0] !~ /^tetazoo$/i) && (my $key_id=in_keys($bar[0])))
    { buy_soda($bar[0]) }

    elsif ($bar[0])
    {

	if ($bar[0] !~ /^help$/i)
	{ 
	    print LOGFILE "Invalid command $bar[0]\n";
	    print "I don\'t know $bar[0]. ";
	}
	print "I know the following:\n\nadduser\tbuy\taddalias\tlist\tlistalias\tpasswd\tcredit\n\n";

    }

    
    close LOGFILE;
    print "athena# ";
}

#system("killall zwgc");
