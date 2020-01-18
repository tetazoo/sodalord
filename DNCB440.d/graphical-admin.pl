#!/opt/ActivePerl-5.8/bin/perl -T

use strict;
use warnings;

use DBI;
use Curses::UI;
use Curses;
use Digest::MD5 qw( md5 md5_base64 );

# initialize database
my $dbh = DBI->connect("dbi:mysql:sodalord", "foo", "foopass") || die "Can't connect: $DBI::errstr\n";
my $values_sth = $dbh->prepare("SELECT user.* FROM user,names WHERE names.alias=? and names.id=user.name");
my $addalias_sth = $dbh->prepare("REPLACE INTO names (id, alias) VALUES (?,?)");
my $get_aliases_sth = $dbh->prepare("SELECT alias FROM names WHERE id = ?");
my $update_userdata_sth = $dbh->prepare("REPLACE user VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
my $delallalias_sth = $dbh->prepare("DELETE FROM names WHERE names.id=?");
my $delalias_sth = $dbh->prepare("DELETE FROM names WHERE names.alias=?");
my $add_card_sth = $dbh->prepare("REPLACE INTO card VALUES (?,?)");
my $cards_sth = $dbh->prepare("SELECT card FROM card WHERE user=?");

# initialize window system

my $cui = new Curses::UI;

my $w1 = $cui->add('w1', 'Window', -border  => 1);

my @labels = ([0,0,'CTRL-Q: Quit  CTRL-X: Return to Search Box ' . 
	       ' Use TAB and SHIFT-TAB to move'],
	      [25,1,'Search for User:'],
	      [1,5,'User ID'],
	      [1,7,'Alias List'],
	      [15,5,'Email Address'],
	      [45,5,'Current Debt'],
	      [60,5,'Time Added'],
	      [25,7,'New Password'],
	      [45,7,'Re-Enter Password'],
	      [65,7,'Update pass?'],
	      [25,10,'Crypt of current password:'],
	      );

foreach my $ref (@labels) {
    $w1->add(undef,'Label',-x=>$$ref[0], -y => $$ref[1], -text => $$ref[2]);
}

my $searchbox = $w1->add('searchbox', 'TextEntry', -sbborder => 1,
	 -y => 2, -x => 20, -width => 30);

$w1->add('searchbutton', 'Buttonbox', -y => 3, -x => 20,
	 -buttons => [
	     { -label => '< Search >', -value => 'search', -onpress => \&search},
	     { -label => '< Clear >', -value => 'clear', -onpress => \&clearbox},
	     { -label => '< Update >', -value => 'update', -onpress => \&dbupdate}]);

my $userbox = $w1->add('userbox', 'TextEntry', -sbborder => 1,
		       -y => 6, -x => 1, -width => 13);

my $aliasbox = $w1->add('aliasbox', 'TextEditor',
			-border => 1, -scrollbar => 1,
			-x => 1, -y => 8, -height => 17, -width => 20);

my $emailbox = $w1->add('emailbox', 'TextEntry', -sbborder =>1,
			-y => 6, -x => 15, -width => 25);

my $debtbox = $w1->add('debtbox', 'TextEntry', -sbborder =>1,
			-y => 6, -x => 45, -width => 10);

my $timebox = $w1->add('timebox', 'TextEntry', -sbborder => 1,
		       -y => 6, -x => 60, -width => 15);

my $passwdbox1 = $w1->add('passwdbox1', 'PasswordEntry', -sbborder =>1,
			-y => 8, -x => 25, -width => 15);

my $passwdbox2 = $w1->add('passwdbox2', 'PasswordEntry',
			-sbborder =>1, -y => 8, -x => 45, -width => 15);

my $passwdradio = $w1->add('passwdradio', 'Radiobuttonbox',
			   -y => 8, -x => 65,
			   -values => ['Yes','No'],
			   -height => 2, -selected => 1);

my $pwdbox = $w1->add('curpasswd', 'Label', -y => 11, -x => 25, -width => 15,
		      -text => '');

my %hours;
my %boxpos = (
'H00' => [25,13], 'H01' => [25,14], 'H02' => [25,15], 'H03' => [25,16],
'H04' => [25,17], 'H05' => [25,18], 'H06' => [25,19], 'H07' => [25,20],
'H08' => [40,13], 'H09' => [40,14], 'H10' => [40,15], 'H11' => [40,16],
'H12' => [40,17], 'H13' => [40,18], 'H14' => [40,19], 'H15' => [40,20],
'H16' => [55,13], 'H17' => [55,14], 'H18' => [55,15], 'H19' => [55,16],
'H20' => [55,17], 'H21' => [55,18], 'H22' => [55,19], 'H23' => [55,20]);

$w1->add('hourslabel', 'Label', -y =>12, -x => 37,
	 -text => 'Hourly Soda Tallies');

my @sortedbox = sort keys %boxpos;
for (my $j=0; $j <= $#sortedbox; $j++)
{
    my $i = $sortedbox[$j]; 
    my $prev = $sortedbox[$j-1];
    my $next = ( $j == $#sortedbox ? $sortedbox[0] : $sortedbox[$j+1]);
    my $xy = $boxpos{$i};
    $w1->add($i . 'lbl', 'Label', -text => $i, -x => $$xy[0], -y => $$xy[1]);
    $hours{$i} = $w1->add($i, 'TextEntry', -sbborder => 1,
			  -x => $$xy[0] + 3, -y => $$xy[1],
			  -width => 10, -text => '0');
    $hours{$i}->set_binding( sub{ $hours{$prev}->focus }, (KEY_UP()) );
    $hours{$i}->set_binding( sub{ $hours{$next}->focus }, (KEY_DOWN()) );
    
}

my $w2 = $cui->add('w2', 'Window', -border => 1);

$w2->add('usrlabel', 'Label', -text => 'User name to associate with card',
	 -x => 15, -y => 3);

my $usrcard = $w2->add('usrcard', 'TextEntry', -sbborder => 1,
		       -y => 4, -x => 15, -width => 25);

$w2->add('scanlabel', 'Label', -text => 'Highlight here to scan-->',
	 -x => 1, -y => 6);

$w2->add('crdlabel', 'Label', -text => 'Card Data', -x => 50, -y => 5);

my $cardbox = $w2->add('cardbox', 'PasswordEntry', -sbborder => 1,
		       -y => 6, -x => 26, -width => 2, -height => 5,
		       -text => '');

my $cbox2 = $w2->add('cbox2', 'TextViewer', -sbborder => 1,
		     -y => 6, -x => 50, -width => 25, -height => 1,
		     -text => '');

$cardbox->onFocus( sub { $cardbox->text('') });
$cardbox->onBlur( sub { $cardbox->get
			    ? $cbox2->text(md5_base64($cardbox->get))
			    : $cbox2->text('')} );


$w2->add('cardbutton', 'Buttonbox', -y => 7, -x => 15,
	 -buttons =>
	 [
	  { -label => '< Search for User >', -value => 'clear',
	    -onpress => \&findcards},
	  { -label => '< Clear >', -value => 'clear', -onpress => \&clearbox},
	  { -label => '< Add to Database >', -value => 'update', -onpress => \&cardupdate}
	  ]);

$w2->add('crdlistlabel', 'Label', -text => 'Cards Associated:',
	 -x => 1, -y => 9);

my $cardlistbox = $w2->add('clistbox', 'TextViewer',
			-border => 1, -scrollbar => 1,
			-x => 1, -y => 10, -height => 17, -width => 25);


# Set bindings and focus rules
$cui->set_binding( sub { $searchbox->focus }, "\cX" );
$cui->set_binding( \&switchwin, "\cA" );
$cui->set_binding( sub{ exit }, "\cQ" );
$w1->focus();

MainLoop;

sub search
{
    my $i = 0;
    my $stext = $searchbox->text;
    $values_sth->execute($searchbox->text);
    if (my $rowref = $values_sth->fetchrow_arrayref)
    {
	my @row = @$rowref;
	$get_aliases_sth->execute($row[0]);
	my $aliases_ref = $get_aliases_sth->fetchall_arrayref;
	my @aliases = map { $$_[0] } @$aliases_ref;
	$userbox->text($row[$i++]);
	$emailbox->text($row[$i++]);
	$debtbox->text($row[$i++]);
	foreach my $j (sort keys %hours)
	{
	    $hours{$j}->text($row[$i++]);
	}
	$aliasbox->text(join "\n", @aliases);
	$pwdbox->text($row[$i++]);
	$timebox->text($row[$i++]);
    }
    else
    {
	$cui->dialog("User $stext not found.");
	&clearbox;
    }
}   

sub clearbox
{
    $timebox->text('');
    $searchbox->text('');
    $userbox->text('');
    $aliasbox->text('');
    $emailbox->text('');
    $debtbox->text('');
    $passwdbox1->text('');
    $passwdbox2->text('');
    $pwdbox->text('');
    map { $hours{$_}->text('0') } (keys %hours);
    $usrcard->text('');
    $cardbox->text('');
    $cbox2->text('');
    $cardlistbox->text('');
}
    
sub dbupdate
{
    my $value =
	$cui->error(-message => "Update will change the information in the " .
		    "database.\nAre you sure?",
		    -buttons => [ 'yes', 'no' ],
		    -title   => "WARNING: UPDATING DATABASE!");
    if ($value)
    {
	my $pwd = $pwdbox->text;
	my $user = $userbox->text;
	my $aliastext = $aliasbox->text;
	my @aliases = split "\n", $aliastext;
	if ($passwdradio->get eq 'Yes')
	{
	    if ($passwdbox1->text ne $passwdbox2->text) {$cui->dialog("Error: New passwords do not match."); return}
	    $pwd = crypt($passwdbox1->text, join '', (0..9, 'A'..'Z', 'a'..'z')[rand 62, rand 62]);
	}
	
	my @hourdata = map { $hours{$_}->text } (sort keys %hours);
	foreach my $i (@hourdata)
	{
	    if (($i eq '' ) || ($i =~ /\D/))
	    {
		$cui->error("All hour values must be non-negative integers.\nDatabase NOT updated.");
		return 1;
	    }
	}
	my $email = $emailbox->text;
	my $debt = $debtbox->text;
	my $timeb = $timebox->text;
	$timeb = time() if (! $timeb || $timeb =~ /\D/);
	if ($user eq '' || $email eq '' || $debt eq '' || $timeb eq '')
	{
	    $cui->error('All fields must contain information.');
	    return 1;
	}
	$delallalias_sth->execute($user);
        $update_userdata_sth->execute($user, $emailbox->text, $debtbox->text, @hourdata, $pwd, $timebox->text);
	$addalias_sth->execute($user, $user);
	map { $addalias_sth->execute($user, $_) } @aliases;
    }	
}

sub switchwin
{
    if ($w1 eq $cui->getfocusobj())
    { $w2->focus(); } else { $w1->focus(); }
}


sub cardupdate
{
    my $user = $usrcard->get;
    my $card = md5_base64($cardbox->get);
    my $value = $cui->dialog(-message => 'Add card to database?',
			     -buttons => ['yes','no']);
    if (($user) && ($value) && ($cardbox->get() ne ''))
    { $add_card_sth->execute($card, $user); }
}

sub findcards
{
    my $user = $usrcard->get;
    $cards_sth->execute($user);
    if (my $cardref = $cards_sth->fetchall_arrayref)
    {
	my @cards = map { $$_[0] } @$cardref;
	$cardlistbox->text(join "\n", @cards);
    }
    else { $cui->dialog('User ' . $user . ' not found.') }
}
	
