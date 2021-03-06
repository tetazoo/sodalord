#!/usr/athena/bin/perl -w
use Socket;
use Carp;
use FileHandle;
use Chart::Bars;
use DB_File;

sub spawn;
sub logmsg 
{ 
    open(LOGFILE,">>/soda/logs/sodaweb.log");
    print LOGFILE "$0 $$: @_ at ", scalar localtime , "\n";
    close LOGFILE;
}

my $port = shift || 2345;
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


sub draw_histogram
{
    my $nameis = shift;
    my @data = @_ ;
    my %quux;
    $graph = Chart::Bars->new(500,300);
    for (my $i=0;$i<24;$i++)
    {
	$quux{"$i"} = $data[$i+1];
    }
    foreach my $j (sort {$a <=> $b} (keys %quux))
    {
        my $v = $quux{"$j"};
	$graph->set ('title' => "Soda Consumption of $nameis",
		     'legend' => 'none',
		     'colors' => { 'background' => [255,127,0]},
		     'x_label' => 'Time of Day',
		     'y_label' => 'Sodas Purchased');

	$graph->add_pt ($j, $v);
#	print "Key $j Value $v";
    }
    $graph->png("/soda/graphics/$nameis.png")
}

$SIG{CHLD} = \&REAPER;

for ( ; $paddr = accept(Client, Server) ; close Client) {
    my($port,$iaddr) = sockaddr_in($paddr);
    my $name = gethostbyaddr($iaddr,AF_INET);
    
    logmsg "connection from $name [", inet_ntoa($iaddr), "] at port $port";

    spawn sub {
	
	if ( my @baz = split ' ', <STDIN> ) {
	    chomp @baz;
	    if ( $baz[0] =~ /^get/i ) {
		%foo = ();
		tie %foo, "DB_File", $tallyfile, O_RDWR, 0400, $DB_HASH;
		print "<HTML>\n";
		print "<BODY BGCOLOR=\"FF7F00\">\n";
		$baz[1] =~ s/^\///;
		if ($baz[1] !~ /\W/)
		{
		    chomp $baz[1];
		    if (! $baz[1]) {$baz[1] = "tetazoo";}
		    my $key_id = (in_keys($baz[1]));
		    if ($key_id)
		    {
			@names = split '!!', $key_id;
			@data = split '!!', $foo{"$key_id"};
			draw_histogram($names[0],@data);
			print "$names[0] has a soda tally of $data[0].\n\<BR\>\<P\>";
			
			print "<IMG SRC =\"http\:\/\/sodalord.mit.edu\:80\/$names[0].png\">\n";
		    }
		
		    else { print "$baz[1] doesn't have a sodalord account\n"; }
		} else {print "Use alphanumerics only!\n";}
		untie %foo;
		print "</body>\n";
		print "</html>\n";
	    }
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











