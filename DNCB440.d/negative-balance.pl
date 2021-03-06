#!/opt/ActivePerl-5.8/bin/perl -w

use DBI;

my $dbh = DBI->connect("dbi:mysql:sodalord","foo","foopass") || die "Can't connect: $DBI::errstr\n";

my $negative_sth = $dbh->prepare("SELECT name,email,tot FROM user WHERE tot < 0 AND name != 'tetazoo' AND name != 'testuser' AND name != 'testuser7'");
$negative_sth->execute();
my $arrayref;

system("kinit -k -t /etc/krb5.keytab");

while ($arrayref = $negative_sth->fetchrow_arrayref) {
    my $username = $$arrayref[0];
    my $email = $$arrayref[1];
    my $negbalance = -$$arrayref[2];
    my $negbalancestr = sprintf("\$%.2f", $negbalance);

    open(MAIL, "|/usr/sbin/sendmail -odb -t -f sodalord\@mit.edu");

    print MAIL <<EOM;
To: $username <$email>
Cc: sodalord\@mit.edu
From: Agent for Sodalord <sodalord\@mit.edu>
Subject: $username: $negbalancestr negative Sodalord balance

This is an automatically weekly generated message from the Sodalord
balance program.

You have a negative balance of $negbalancestr.  Please give money to
Kevin in person or leave it on his desk and e-mail sodalord\@mit.edu.

If you cannot pay Kevin in person (for example, if you are not in the
area), you can send a check to:

Kevin Chen
3 Ames St., \#4
Cambridge, MA 02142-1305

You can also send a Paypal payment to kchen\@mit.edu.

						Sodalord
EOM
    close(MAIL);

}
