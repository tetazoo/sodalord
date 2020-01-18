#!/usr/athena/bin/perl -wT

use DBI;
use CGI qw(:standard);
my $dbh = DBI->connect("dbi:mysql:sodalord","foo","foopass");
my $values_sth = $dbh->prepare("SELECT user.* FROM user,names WHERE names.alias=? and names.id=user.name");
print header, start_html('THiRD EAst'),h1('Sodalord Administration');
my $search = param('search');
if ($search)
{
    print start_form();
    my @ary = param();
    foreach (@ary)
    { print "$_ :" . param($_) . "\n";}
    $values_sth->execute($search);
    my $rref = $values_sth->fetchrow_arrayref;
    if ($rref)
    {
#	print @$rref;
	param('username', $$rref[0]);
	param('email', $$rref[1]);
	param('debt', $$rref[2]);
	print
	    h2("Information for user $search"),
	    table(Tr([th(['Username','Email Address','Debt']),td([textfield(-name=>'username'),textfield(-name=>'email'),textfield(-size=>10,-maxlength=>10,-name=>'debt')])])),
	    h2('Hourly soda tallies'),
            '<TABLE>';
	for (my $row = 0; $row<4; $row++)
	{
	    print '<TR>';
		for (my $col = 0; $col<6; $col++)
		{
		    my $name=sprintf("H%02u",($row*6+$col));
		    param($name, $$rref[(3+$row*6+$col)]);
		    print "\n" . td(textfield(-size=>'8', -name=>$name));

		}
	    print '</TR>';
	}
	print '</TABLE>';
	print hidden(-name=>'search');
	print submit(-name=>'submit', -value=>"Update");
	print end_form;
    } else { print h2("No records for user $search."); }
} 
print end_html;
