#!/usr/athena/bin/perl -wT

use DBI;
use CGI;
use Chart::Composite;
use DB_File;

################################################################################
sub draw_histogram
{
    my $nameis = shift;
    my @data = @_ ;
    my %quux;
    my $totalsodas = 0;
    my @sodadata;
    my @regressiondata;
    my @xticks;
    for (my $i=0;$i<240;$i++)
    { 
	push @xticks, $i/10;
    }
    for (my $i=0;$i<24;$i++)
    {
	$quux{"$i"} = $data[$i+1];
	$totalsodas += $data[$i+1];
    }
    foreach my $j (sort {$a <=> $b} (keys %quux))
    {
        my $v = $quux{"$j"};
	
	push @sodadata, 0,$v,$v,$v,$v,$v,$v,$v,$v,0;
    }
    
    open (OCTAVE, ">/soda/web/octave/$nameis.m");

print OCTAVE <<EOF;
    y = [$data[1] $data[2] $data[3] $data[4] $data[5] $data[6] $data[7] $data[8] $data[9] $data[10] $data[11] $data[12] $data[13] $data[14] $data[15] $data[16] $data[17] $data[18] $data[19] $data[20] $data[21] $data[22] $data[23] $data[24]]\';
    t = [0:23]\';
    X = [ones(size(t)) sin(pi/12*t) cos(pi/12*t)];
    a = X\\y;
    T = [0:.1:23.9]\';
    Y = [ones(size(T)) sin(T*pi/12) cos(T*pi/12)]*a
    Yc = [ones(size(t)) sin(t*pi/12) cos(t*pi/12)]*a;
    r = sum((Yc-a(1)).^2)/sum((y-a(1)).^2)
    alpha = a(1)
    beta = sqrt(a(2)^2 + a(3)^2)
    omega = pi/12;
    phi = atan(-a(3)/a(2)) / omega;
    if sign(a(2)) < 0
        phi = phi + 12;
    endif
    if phi < 0
        phi = phi + 24
    else
        phi = phi
    endif
EOF

    close(OCTAVE);

    $ENV{PATH} = '/bin:/usr/bin';
    chomp(@octave_output = `/usr/local/bin/octave -q /soda/web/octave/$nameis.m`);
    
    #discard first two lines
    shift @octave_output;
    shift @octave_output;
    
    for (my $i = 0; $i<240; $i++)
    {
	push @regressiondata, $octave_output[$i];
    }
    print LOG "xticks: @xticks";
    
    my $graph = Chart::Composite->new(640,480);
    $graph->set ('title' => "Soda Consumption of $nameis",
		 'legend' => 'none',
		 'colors' => { 'background' => [0,0,0x80], 
			       'text' => [0xff,0xcc,0],
			       'y_label' => [0xff,0xcc,0]
			       },
		 'x_label' => 'Time of Day',
		 'y_label' => 'Sodas Purchased',
		 'min_val' => '0',
		 'include_zero' => 'true',
		 'composite_info' => [ [ 'Bars' , [1]],
				       [ 'Lines' , [2]]],
		 'same_y_axes' => 'true',
		 'skip_x_ticks' => '10',
		 'precision' => 0, 
		 'max_y_ticks' => 10,
		 'spaced_bars' => 'false');

    # Make Image
    $graph->png("/soda/web/graphics/$nameis.png", [\@xticks, \@sodadata, \@regressiondata]); 

    my @ret_vals = ( $totalsodas );
    for (my $i = 241; $i < 245; $i++)
    {
	push @ret_vals, (split " ", $octave_output[$i])[2];
    }
    return @ret_vals;
}

################################################################################

print "Content-type: text/html\n\n";
print <<HEADER;
<HTML>
  <HEAD>
    <TITLE>THiRD EAst</TITLE>
  </HEAD>
  <BODY TEXT=#FFCC00 BGCOLOR=#000080>
HEADER

open(LOG,">/soda/web/logfile-asedeno.log");

$dbh=DBI->connect("dbi:mysql:sodalord","foo","foopass");

my $values_sth = $dbh->prepare("SELECT user.* FROM user,names WHERE names.alias=? and names.id=user.name");

$cgi = CGI->new();
$user = ($cgi->param('user')
	 ? $cgi->param('user')
	 : 'tetazoo');

if ($user !~ /\W/)
{
    $values_sth->execute($user);
    my $arrayref = $values_sth->fetchrow_arrayref;
    if ($arrayref)
    {
	my ($name, $email, @data) = @$arrayref;
	my @information = draw_histogram($name,@data);

	my $days = (time - $data[26]) / 86400;
	my $sodasperday = $information[0] / $days;

print <<SODADATA
    <P>$name ($user) has a soda tally of $information[0].<BR></P>
    <P>On average, $name has purchased $sodasperday sodas per day.<BR></P>

    <IMG SRC =\"\/graphics\/$name.png\">

    <P>
    The sinusoidal best-fit curve for this data is defined as
    y = $information[2] + $information[3] * sin ( (t - $information[4]) * &\#960; / 12 ) 
    <BR>
    This fit has a correlation coefficient of $information[1].</P>
SODADATA

    }
    else
    {
	print "$user doesn't have a sodalord account\n"; 
    }
} 
else
{
    print "Use alphanumerics only!\n";
}

print <<FOOTER;
    <FORM ACTION="index-asedeno.cgi" METHOD=GET>
      Username to query:
      <input type="text" name="user">
      <input value="SUBNIT TO ANARCHY" type=submit>
    </FORM>
  </body>
</html>
FOOTER
