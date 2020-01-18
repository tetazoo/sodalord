#!/usr/athena/bin/perl -w
use Socket;
use Carp;
use FileHandle;
use Chart::Bars;
use DB_File;
sub spawn;
sub logmsg
{
    open(LOGFILE,'>>/soda/logs/sodafinger.log');
    print LOGFILE "$0 $$: @_ at ", scalar localtime , "\n";
    close LOGFILE;
}

my $port = shift || 79;
my $proto = getprotobyname('tcp');
socket(Server, PF_INET, SOCK_STREAM, $proto) or die "socket: $!";
setsockopt(Server, SOL_SOCKET, SO_REUSEADDR, pack("l", 1))
    or die "setsockopt: $!";
bind(Server, sockaddr_in($port, INADDR_ANY)) or die "bind: $!";
listen(Server, SOMAXCONN) or die "listen: $!";

logmsg "server started on port $port";

$tallyfile = "/soda/tally.db";
my $waitedpid = 0;
my $paddr;

sub REAPER {
    $waitedpid = wait;
    $SIG{CHLD} = \&REAPER;
    logmsg "reaped $waitedpid" . ($? ? " with exit $?" : "");
}


sub in_keys
{
    my $id = shift;
    foreach my $i (keys %foo)
    {
	@baz = split '!!', $i;
	foreach my $test (@baz)
	{
	    if ($id =~ /^$test$/i)
	    {
		return $i;
	    }
	}
    }
    return 0;
}

$SIG{CHLD} = \&REAPER;

for ( ; $paddr = accept(Client, Server) ; close Client) {
    my($port,$iaddr) = sockaddr_in($paddr);
    my $name = gethostbyaddr($iaddr,AF_INET);
    
    logmsg "connection from $name [", inet_ntoa($iaddr), "] at port $port";

    spawn sub {
	
	if ( my @baz = split ' ', <STDIN> ) {
	    chomp @baz;
	    if ( $baz[0] !~ /\W/i ) {
		%foo = ();
		tie %foo, "DB_File", $tallyfile, O_RDWR, 0400, $DB_HASH;
		chomp $baz[0];
		my $key_id = (in_keys($baz[0]));
		if ($key_id)
		{
		    @names = split '!!', $key_id;
		    @data = split '!!', $foo{"$key_id"};
		    print "$names[0] has a soda tally of $data[0].\n";
		}
		
		else { print "$baz[0] doesn't have a sodalord account\n"; }
	    } else {print "Use alphanumerics only!\n";}
	    untie %foo;
	}
    }
}

sub spawn {
    my $coderef = shift;

    unless (@_ == 0  && $coderef && ref($coderef) eq 'CODE') {
	confess "usage: spawn CODEREF";
    }

    my $pid;
    if (!defined($pid = fork)) {
	logmsg "cannot fork: $!";
	return;
    } elsif ($pid) {
	logmsg "begat $pid";
	return;
    }

    open (STDIN, "<&Client") or die "can't dup client to stdin";
    open (STDOUT, ">&Client") or die "can't dup client to stdout";
    STDOUT->autoflush();
    exit &$coderef();
}











