#!/usr/athena/bin/perl -w

use DB_File;
use Mail::Mailer;

my $hallcost = .4;
my $othercost = .6;

print "athena# ";
$tallyfile = "/soda/tally.db";
sub in_keys
{
    my $id = shift;

    foreach my $i (keys %foo)
    {
	@baz = split '!!', $i;
	foreach $test (@baz)
	{
#	    print "checking $id against $test\n";
	    if ($test =~ /$id.*/i)
	    {
		print "Match! $test eq $id . \n";
		print "Return this value? ";
		chomp($d = <STDIN>);
		if ($d eq "y")
		{
		    return $i;
		}
	    }
	}
    }
    print "string $id not found.\n";

    return 0;
}

sub print_time
{
    my $now = localtime;
    print LOGFILE "ADMIN: Time: $now\n";
}

for (;;)
{

    @bar = split ' ', <STDIN>;
    tie %foo, "DB_File", $tallyfile, O_RDWR|O_CREAT, 0644, $DB_HASH || die "Can't tie $tallyfile";
    open(LOGFILE,'>>/soda/logs/sodalord.log');

    chomp @bar;
    if (! $bar[0]) {}
    elsif ($bar[0] =~ /\W/)
    {
	print "Use alphanumerics only.";
    }
    elsif ($bar[0] =~ /^chk27$/i) {
	foreach my $i (keys %foo)
	{
	    @asdf = split '!!', $i;
	    @jkl = split '!!', $foo{"$i"};
	    if ($#jkl == 25) 
	    {
		print "$asdf[0]\n";
	    }
	}
    }	    
    elsif ($bar[0] =~ /^adduser$/i) {
	if (($#bar > 0) && ($#bar < 3)) {
	    if ($bar[1] !~ /\W/) {
		$key_id = (in_keys($bar[1]));
		if ($key_id)
		{ print "\nThat username is taken.  Please choose another.\n"; }
		elsif ($bar[2])
		{ 
		    my $rndstr = join('', (0..9,'A'..'Z','a'..'z')[rand 62, rand 62]);
		    my $pass = crypt($bar[2], $rndstr);
                    my $timeisnow = time;
########Data format: total!!0am!!1am!!...!!11pm!!passwd!!timeofinit

		    $foo{"$bar[1]"} = "0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!$pass!!$timeisnow";
		}
		else
		{
		    my $pass = "";
		    my $email;
		    my $pass2 = "";
		    print "\nE-Mail Address: ";
		    chomp($email = <STDIN>);
		    my $nameis = "$bar[1]!!\<$email\>";
		    system "stty -echo";
		    print "\nSoda Password: ";
		    chomp($pass = <STDIN>);
		    print "\nConfirm Soda Password:";
		    chomp($pass2 = <STDIN>);
		    print "\n";
		    system "stty echo";
		    if ($pass eq $pass2)
		    {
			my $rndstr = join('', (0..9,'A'..'Z','a'..'z')[rand 62,rand 62]);
			my $pwd = crypt($pass, $rndstr);
                        my $timeisnow = time;
			$foo{"$nameis"} = "0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!0!!$pwd!!$timeisnow";
			print_time();
			print LOGFILE "ADMIN: Added user $bar[1] with email $email\n";
		    }
		    else {
			print "\nPasswords do not match!\n";
		    }
		}
	    } else {print "\nUse alphabetic characters only.\n";}   
	}
	else { print "\nSyntax: adduser username [password]\n"; }
    }

    elsif ($bar[0] =~ /^delete$/i) {
	if ($#bar == 1)
	{
	    my $key_id = (in_keys($bar[1]));
	    my $d;
	    print "key = $key_id\n";
	    print "Delete? ";
	    chomp($d = <STDIN>);
	    if ($d eq "y")
	    {
		delete $foo{"$key_id"};
		print_time();
		print LOGFILE "ADMIN: Deleted $key_id from database.\n";
	    }
	}
	else { print "Syntax: delete <key>\n"; }
    }
    

    elsif ($bar[0] =~ /^chgkey$/i) {
	my $key_id = (in_keys($bar[1]));
	my $d;
	print "key = $key_id\n";
	print "Chg? ";
	chomp($d = <STDIN>);
	if ($d eq "y")
	{
	    print "Chg to? ";
	    chomp($e = <STDIN>);
	    $foo{"$e"} = $foo{"$key_id"};
	    delete $foo{"$key_id"};
	    print_time();
	    print LOGFILE "ADMIN: Changed key for $key_id to $e\n";
	}
    }

    elsif ($bar[0] =~ /^rmalias$/i) {
	my $key_id = (in_keys($bar[1]));
	if ($key_id) {
	    my @a = split '!!', $key_id;
	    my $d = "$a[0]";
	    for (my $i=1;$i<=$#a;$i++) {
		if ($a[$i] ne $bar[1])
		{ $d .= "!!$a[$i]"; }
	    }
	    $foo{"$d"} = $foo{"$key_id"};
	    delete $foo{"$key_id"};
	    print_time();
	    print LOGFILE "ADMIN: Removed alias $bar[1] from $a[0]\n";
	}
    }

    elsif ($bar[0] =~ /^chgdata$/i) {
	my $key_id = (in_keys($bar[1]));
	my $d;
	my $val = $foo{"$key_id"};
	print "val = $val\n";
	print "Chg? ";
	chomp($d = <STDIN>);
	if ($d eq "y")
	{
	    print "Chg to? ";
	    chomp($e = <STDIN>);
	    $foo{"$key_id"} = "$e";
	    print_time();
	    print LOGFILE "ADMIN: Changed data of $bar[1] to $e.\n";
	}
    }
    elsif ($bar[0] =~ /^chgdebt$/i) {
	my $key_id = (in_keys($bar[1]));
	my $d;
	my $val = $foo{"$key_id"};
	print "val = $val\n";
	print "Chg? ";
	chomp($d = <STDIN>);
	if ($d eq "y")
	{
	    my @quuux = split '!!', $val;
	    print "Chg debt to: ";
	    chomp($e = <STDIN>);
	    my $f = "$e";
	    for (my $i=1;$i<26;$i++)
	    {
		$f .= "!!$quuux[$i]";
	    }
	    $foo{"$key_id"} = "$f";
	    print_time();
	    print LOGFILE "ADMIN: Changed debt of $bar[1] to $e.\n";
	}
    }

    elsif ($bar[0] =~ /^addalias$/i) {
	if ($#bar == 2) {
	    
	    $key_id = (in_keys($bar[1]));
#		print "key = $key_id\n";
	    if (! $key_id)
	    { 
		
		$key_id = (in_keys($bar[2]));
#		print "key = $key_id\n";
		if ($key_id)
		{
		    my $newkey = "$key_id!!$bar[1]";
		    $foo{"$newkey"} = $foo{"$key_id"};
		    delete $foo{"$key_id"};
		    print_time();
		    print LOGFILE "ADMIN: Added alias $bar[1] to $key_id\n";
		}
		else
		{
		    print "\nUsername $bar[2] not found in database.\n";
		}
	    } else { print "\nThat alias is taken.\n";}
	    
	    
	} else { print "\nSyntax: addalias alias username\n"; }
    }

    elsif ($bar[0] =~ /^passwd$/i) {
	if (($#bar == 1) && ($bar[1] !~ /\W/)) {
	    my $key_id = (in_keys($bar[1]));
	    if ($key_id)
	    {
		my @data = split '!!', $foo{"$key_id"};
		my $pass;
		my $pass2;
		print "\nOld passwd: $data[25]\n";
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
		    print "\nNew passwd: $data[25]\n";
		    my $datastring = "$data[0]";
		    for (my $i=1; $i<27; $i++)
		    {
			$datastring .="!!$data[$i]";
		    }
		    $foo{"$key_id"} = "$datastring";
		    print_time();
		    print LOGFILE "ADMIN: Password for $bar[1] changed.\n";
		}
		else { print "\nPasswords do not match!\n";}
	    }
	    else { print "\nUser $bar[1] not found in database.\n";}
	}
	else {print "\nSyntax: passwd username\n";}
    }


    elsif ($bar[0] =~ /^listalias$/i) {
	if (($#bar == 1) && ($bar[1] !~ /\W/)) {
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

    elsif ($bar[0] =~ /^listall$/i) {
	if ($#bar == 0) {
	    my $mailer;
	    my $p;
	    my $print_flag = 0;
	    my $mail_flag = 0;
	    my @all_keys = keys %foo;
	    print "Print to file soda.data? ";
	    chomp ($p = <STDIN>);
	    if ($p =~ /^y/i)
	    {
		open(DATA, '>soda.data');
		$print_flag = 1; 
	    }
	    print "Send mass mailing? ";
	    chomp ($p = <STDIN>);
	    if ($p =~ /^y/i) { $mail_flag = 1; }
	    my $total = 0;
	    my %debtors;
	    foreach $key (@all_keys)
	    {
		my @names = split '!!', $key;
		if ($names[0] !~ /^tetazoo$/)
		{
		    my @data = split '!!', $foo{"$key"};
		    my $bill = $data[0] * -.4;
		    print "User $names[0] with email $names[1] has a debt of $data[0] sodas (\$ $bill)\n";
		    if ($bill < 0)
		    {
			$debtors{"$names[1]"} = $bill;
		    }
		    $total += $bill;
		    if ($print_flag)
		    {
			print DATA "Name: $names[0]\tEmail: $names[1]\tDebt: $data[0]\n";
		    }
		    if ($mail_flag)
		    {
			$mailer = Mail::Mailer::new;
			$mailer->open( { To => $names[1],
					 From => 'root\@sodalord.mit.edu',
					 Subject => 'Current Soda Debt'});
			print $mailer <<EOF;
Sodalord
------------------------------------------
Dear $names[0],


Thank you for using the Tetazoo Soda System.

EOF

			if ($bill != 0)
			{ 
			    print $mailer <<EOF;

This is a reminder that you have a debt if negative, credit if positive of
\$ $bill on Sodalord.

EOF
		        }
		      $mailer->close;
		    }
		}	    
	    }
	    print "The debtors are:\n";
	    while (($key, $value) = each %debtors)
	    {
		print "$key with debt $value\n";
	    }
	    print "Total bill is $total\n";
	    if ($print_flag) { close DATA; }
	}
	else {print "\nSyntax: listall\n";}
    }
	

    elsif ($bar[0] =~ /^list$/i) {
	if (($#bar == 1) && ($bar[1] !~ /\W/)) {
	    $key_id = (in_keys($bar[1]));
	    if ($key_id)
	    {
		my @names = split '!!', $key_id ;
		my @info = split '!!', $foo{"$key_id"};
		print "\n$names[0] has a debt of $info[0] sodas.\nVisit http://sodalord.mit.edu:2345/<username> for more detail!\n\n";
	    }
	    else { print "\nUser $bar[1] not found.\n"}
	}
	else { print "\nSyntax: list username\n"; }
    }
	    
    elsif ($bar[0] =~ /^buy$/i) {
	if (($#bar == 1) && ($bar[1] !~ /\W/) && ($bar[1] ne "tetazoo")) {
	    my $key_id = (in_keys($bar[1]));
	    if ($key_id)
	    { 
		my @data = split '!!', $foo{"$key_id"};
		my @time = localtime();
		my $hour = $time[2];
		$data[0]++;
		$data[$hour+1]++;
		my $tetazoo_id = (in_keys("tetazoo"));
		my @tetazoodata = split '!!', $foo{"$tetazoo_id"};
		$tetazoodata[0]++;
		$tetazoodata[$hour+1]++;
		my $tetazoodatastr = "$tetazoodata[0]";
		print "Authenticated.  Have a soda!\n\n";
		print_time();
		print LOGFILE "ADMIN: $bar[1] bought a soda!\n";
		my $datastring = "$data[0]";
		for (my $i=1; $i<27; $i++)
		{
		    $datastring .="!!$data[$i]";
		    $tetazoodatastr .="!!$data[$i]";
		    
		}
		$foo{"$key_id"} = "$datastring";
		$foo{"tetazoo"} = "$tetazoodatastr";
	    }
	    else {print "\nYou don\'t have an account.  Make one first.\n";}
	}
	else { print "\nSyntax: buy username|alias \n"; }
    }


    elsif ($bar[0] =~ /^credit$/i) {
	if (($#bar == 1) && ($bar[1] !~ /\W/) && ($bar[1] ne "tetazoo"))
	{
	    my $key_id = in_keys($bar[1]);
	    if ($key_id) 
	    {
		my @names = split '!!', $key_id;
		my @data = split '!!', $foo{"$key_id"};

                print "Current debt is $data[0].\n";

		print "Credit how much? (dollars) ";
		chomp (my $credit = <STDIN>);
		print "\n";
		if (($credit !~ /\d+\.?\d*/) && ($credit !~ /\.\d+/))
		{ print "Use a numeric value only.\n"; }
		else
		{
		    print "Hall member? (y/n) ";
		    chomp (my $test = <STDIN>);
		    my $sodacost = ($test =~ /y/i) ? $hallcost : $othercost;
		    my $sodas = $credit / $sodacost;
		    print "\nCredited $sodas sodas to $names[0].\n";
		    print_time();
		    print LOGFILE "ADMIN: Credited $sodas sodas to $names[0]\n"; 
		    $data[0] -= $sodas;
		    my $datastring = "$data[0]";
		    for (my $i=1; $i<27; $i++)
		    {
			$datastring .="!!$data[$i]";
		    }
		    $foo{"$key_id"} = "$datastring";
		}
	    }
	}
	else {print "\nSyntax: credit user\n"};
    }

#    while (($k, $v) = each %foo)
#    { print "$k -> $v\n" }
    

    elsif (($bar[0] =~ /^quit$/i) || ($bar[0] =~ /^exit$/i))
    {
	close LOGFILE;
	untie %foo;
	exit 0;
    }
    elsif ($bar[0])
    {print "I don\'t know $bar[0].  I know the following:\n\nadduser\tbuy\taddalias\tlist\tlistalias\tpasswd\tcredit\nchgkey\tchgdata\tchgdebt\n\n";}

    close LOGFILE;
    untie %foo;

    print "athena# ";
}
