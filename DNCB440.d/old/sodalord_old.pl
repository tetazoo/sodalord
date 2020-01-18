#!/usr/athena/bin/perl -w

use DB_File;
use Mail::Mailer;
use FileHandle;
print "athena# ";
$tallyfile = "/soda/tally.db";
system("/soda/zinit.sh");
system("stty", "sane");
system("stty erase ^?");
system("stty kill ^H");

my $sodacost = .4;
my $softlimit = 0;
my $hardlimit = .5;

STDOUT->autoflush(1);

sub in_keys
{
    my $id = shift;
    
    foreach my $i (keys %foo)
    {
	@baz = split '!!', $i;
	foreach $test (@baz)
	{
	    if ($id =~ /^$test$/i)
	    {
		return $i;
	    }
	}
    }
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
    my $user = shift;
    my $word = "";
    my @data = split '!!', $foo{"$user"};
    system "stty -echo";
    print "Password: ";
    chomp($word = <STDIN>);
    print "\n";
    system "stty echo";
    if (crypt($word, $data[25]) eq $data[25])
    { 
	if ($data[0] + 1 > $hardlimit)
	{
	    print "You have reached the hard soda limit ($hardlimit). Please add more credit to\nyour account.\n";
	    return;
	}
	my @time = localtime();
	my $hour = $time[2];
	my $tetazoo_id = in_keys("tetazoo");
	my @tetazoodata = split '!!', $foo{"$tetazoo_id"};
	$data[0]++;
	$data[$hour+1]++;
	$tetazoodata[0]++;
	$tetazoodata[$hour+1]++;
	my $tetazoodatastr = "$tetazoodata[0]";
	my $curdebt = $data[0] * -1 * $sodacost;
	printf "Authenticated.  Have a soda!\n\nYou have \$ %.2f left on your account.\n", $curdebt;
	print_time();
	print LOGFILE "$name bought a soda!\n";
	my $datastring = "$data[0]";
	for (my $i=1; $i<27; $i++)
	{
	    $datastring .= "!!$data[$i]";
	    $tetazoodatastr .= "!!$tetazoodata[$i]";
	}
	$foo{"$user"} = "$datastring";
	$foo{"$tetazoo_id"} = "$tetazoodatastr";
	system("/soda/zinit.sh");
	if ($data[0] > $softlimit)
	{
	    my $penalty = $data[0] - $softlimit;
	    my $ouch = int(3**$penalty) + 1;
	    
	    open (ZEPHYR, "|/usr/athena/bin/zwrite -s \"I am your god.\" -c sodalord");
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
	    open (ZEPHYR, "|/usr/athena/bin/zwrite -s \"I am your god.\" -c sodalord");
	    print ZEPHYR "$name bought a soda!";
	    close ZEPHYR;
	}

    }
    else {print "\nWrong password.\n\n";}
}

for (;;)
{
    @bar = split ' ', <STDIN>;
    tie %foo, "DB_File", $tallyfile, O_RDWR|O_CREAT, 0644, $DB_HASH;
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
    elsif ($bar[0] =~ /^cat$/i) { print "The cats are Smoky, MOSFET, Mia, and Rachel.\n";}
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
		$key_id = (in_keys($bar[1]));
		if ($key_id)
		{ print "\nThat username is taken.  Please choose another.\n"; }
		else
		{
		    my $pass = "";
		    my $email;
		    my $pass2 = "";
		    print "\nFull E-Mail Address: ";
		    chomp($email = <STDIN>);
		    my $nameis = "$bar[1]!!\<$email\>";
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
			$foo{"$nameis"} = "0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!$pwd!!$timeisnow";
			print_time();
			print LOGFILE "Added user $bar[1] with email $email\n";
		    }
		    else {
			print "\nPasswords do not match!\n";
		    }
		}
	    } else {print "\nUse alphabetic characters only.\n";}   
	}
	else { print "\nSyntax: adduser username\n"; }
    }
    
    
    elsif ($bar[0] =~ /^addalias$/i) {
	if ($#bar == 2) {
	    if (($bar[1] !~ /\W/) && ($bar[1] !~/\s/) && ($bar[1])) {
		$key_id = (in_keys($bar[1]));
		if (! $key_id)
		{ 
		    $key_id = (in_keys($bar[2]));
		    if ($key_id)
		    {
			my $word = "";
			my @data = split '!!', $foo{"$key_id"};
			system "stty -echo";
			print "Password: ";
			chomp($word = <STDIN>);
			print "\n";
			system "stty echo";
			if (crypt($word, $data[25]) eq $data[25])
			{ 
			    my $newkey = "$key_id!!$bar[1]";
			    $foo{"$newkey"} = $foo{"$key_id"};
			    delete $foo{"$key_id"};
			    print_time();
			    print LOGFILE "Added alias $bar[1] to $key_id\n";
			}
			else {print "\nWrong password!\n";}
		    } else {print "\nUsername $bar[2] not found in database.\n";}
		} else { print "\nThat alias is taken.\n";}
	    } else {print "\nUse alphabetic characters only.\n";}   
	} else { print "\nSyntax: addalias alias username\n"; }
    }
    
    elsif ($bar[0] =~ /^passwd$/i) {
	if (($#bar == 1) && ($bar[1] !~ /\W/) && ($bar[1] !~/\s/)) {
	    my $key_id = (in_keys($bar[1]));
	    if ($key_id)
	    {
		my $pass;
		my @data = split '!!', $foo{"$key_id"};
		system "stty -echo";
		print "\nSoda Password: ";
		chomp($pass = <STDIN>);
		if (crypt($pass, $data[25]) eq $data[25])
		{
		    my $pass;
		    my $pass2;
		    print "\nNew Soda Password:";
		    chomp($pass = <STDIN>);
		    print "\n";
		    print "\nConfirm Soda Password:";
		    chomp($pass2 = <STDIN>);
		    print "\n";
		    if ($pass eq $pass2)
		    {
			my $rndstr = join('', (0..9,'A'..'Z','a'..'z')[rand 62,rand 62]);
			my $pwd = crypt($pass, $rndstr);
			$data[25] = $pwd;
			my $datastring = "$data[0]";
			for (my $i=1; $i<27; $i++)
			{
			    $datastring .="!!$data[$i]";
			}
			$foo{"$key_id"} = "$datastring";
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
	    my $key_id = (in_keys($bar[1]));
	    if ($key_id)
	    {
		my @names = split '!!', $key_id;
		print "Aliases for $bar[1]:\n";
		foreach my $name (@names)
		{
		    print "$name\n";
		}
	    }
	    else {print "\nUser $bar[1] not found in database.\n";}
	}
	else {print "\nSyntax: listalias username\n";}
    }
    elsif ($bar[0] =~ /^list$/i) {
	if (($#bar == 1) && ($bar[1] !~ /\W/) && ($bar[1] !~ /\s/)) {
	    $key_id = (in_keys($bar[1]));
	    if ($key_id)
	    {
		my @names = split '!!', $key_id ;
		my @info = split '!!', $foo{"$key_id"};
		print "\n$names[0] has a debt of $info[0] sodas.\nVisit http://sodalord.mit.edu/?user=$names[0] for more detail!\n\n";
	    }
	    else { print "\nUser $bar[1] not found.\n"}
	}
	else { print "\nSyntax: list username\n"; }
    }


    elsif (($bar[0] =~ /^buy$/i) && ($#bar == 1)) {
	if (($#bar == 1) && ($bar[1] !~ /\W/) && ($bar[1] !~ /tetazoo/i) && ($bar[1] !~ /\s/)) {
	    my $key_id = (in_keys($bar[1]));
	    if ($key_id)
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
	    my $key_id = in_keys($bar[1]);
	    if ($key_id) 
	    {
		my @names = split '!!', $key_id;
		my @data = split '!!', $foo{"$key_id"};

		my $word= "";
		system "stty -echo";
		print "Password: ";
		chomp($word = <STDIN>);
		print "\n";
		system "stty echo";
		if (crypt($word, $data[25]) eq $data[25])
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
			
			my $mailer = Mail::Mailer::new;
			$mailer->open( {To => 'sodalord@mit.edu',
					From => 'sodalord@mit.edu',
					Subject => 'Credit to soda account'});
			print $mailer <<EOF;

User $names[0] with email address $names[1] credited
$credit dollars to his/her account.
$names[0] said $reason was a good enough reason.
EOF
                        $mailer->close;
		    
			print_time();
			my $sodas = $credit / $sodacost;
			print "\nCredited $credit dollars to $names[0].\n";
			print LOGFILE "Credited $credit dollars to $names[0]\n"; 
			$data[0] -= $sodas;
			print "New debt is: $data[0] sodas\n";
			my $datastring = "$data[0]";
			for (my $i=1; $i<27; $i++)
			{
			    $datastring .="!!$data[$i]";
			}
			$foo{"$key_id"} = "$datastring";
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
	untie %foo;
	system("killall zwgc");
	exit 0;
    }
    elsif (($bar[0] !~ /\W/) && ($bar[0] !~ /^tetazoo$/i) && ($key_id=in_keys($bar[0])))
    { buy_soda($bar[0],$key_id) }

    elsif ($bar[0])
    {

	if ($bar[0] !~ /^help$/i)
	{ 
	    print LOGFILE "Invalid command $bar[0]\n";
	    print "I don\'t know $bar[0]. ";
	}
	print "I know the following:\n\nadduser\tbuy\taddalias\tlist\tlistalias\tpasswd\tcredit\n\n";

    }

    
    untie %foo;
    close LOGFILE;
    print "athena# ";
}

system("killall zwgc");