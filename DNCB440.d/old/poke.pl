#!/usr/athena/bin/perl -w

system("/usr/athena/bin/kinit -k -t /etc/krb5.keytab");

$accounts_file = "/afs/athena.mit.edu/activity/t/tetazoo/sodalord/accounts/accounts.txt";

open(ACCOUNTS, "<$accounts_file");

while ($nextline = <ACCOUNTS>) {
    last if ($nextline =~ /\*\*BEGIN\*\*/);
}

while ($nextline = <ACCOUNTS>) {
    last if ($nextline =~ /\*\*END\*\*/);
    if (!($nextline =~ /PAID/)) {
	#$nextline =~ s/^\s*//;
	print $nextline;
	@data = split(/\s+/, $nextline);
	$user = $data[3];
	$email = $data[4];
	$amount = $data[5];
	$email{$user} = $email;
	$amounts{$user} += $amount;
	$trans{$user} .= $nextline;
    }
}

foreach $user (keys %email) {
    $amounts{$user} = sprintf("\$%.2f", $amounts{$user});
    $message = <<EndMessage;
From: Agent for Sodalord <sodalord\@mit.edu>
To: $user <$email{$user}>
Cc: sodalord\@mit.edu
Subject: $user: $amounts{$user} in Sodalord Debt

Hi,

You currently owe a total of $amounts{$user} in Sodalord debts (or
personal debts to Kevin) from the transactions listed below:

$trans{$user}
Please pay these when you have a chance.  If this information is
inaccurate, please let us know either in person or by e-mail at
sodalord\@mit.edu.

Thanks!
EndMessage

print $message;

    open(NEWMAIL, "|/usr/sbin/sendmail -t -f sodalord\@mit.edu");
    print NEWMAIL $message;
    close(NEWMAIL);
    
}
