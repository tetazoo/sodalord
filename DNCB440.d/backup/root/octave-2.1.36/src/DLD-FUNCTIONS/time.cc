/*

Copyright (C) 1996, 1997 John W. Eaton

This file is part of Octave.

Octave is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2, or (at your option) any
later version.

Octave is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with Octave; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <string>

#include "defun-dld.h"
#include "error.h"
#include "oct-map.h"
#include "oct-time.h"
#include "ov.h"
#include "oct-obj.h"

// Date and time functions.

static Octave_map
mk_tm_map (const octave_base_tm& t)
{
  Octave_map m;

  m ["usec"] = static_cast<double> (t.usec ());
  m ["sec"] = static_cast<double> (t.sec ());
  m ["min"] = static_cast<double> (t.min ());
  m ["hour"] = static_cast<double> (t.hour ());
  m ["mday"] = static_cast<double> (t.mday ());
  m ["mon"] = static_cast<double> (t.mon ());
  m ["year"] = static_cast<double> (t.year ());
  m ["wday"] = static_cast<double> (t.wday ());
  m ["yday"] = static_cast<double> (t.yday ());
  m ["isdst"] = static_cast<double> (t.isdst ());
  m ["zone"]  = t.zone ();

  return m;
}

static octave_base_tm
extract_tm (Octave_map &m)
{
  octave_base_tm tm;

  tm.usec (static_cast<int> (m ["usec"] . double_value ()));
  tm.sec (static_cast<int> (m ["sec"] . double_value ()));
  tm.min (static_cast<int> (m ["min"] . double_value ()));
  tm.hour (static_cast<int> (m ["hour"] . double_value ()));
  tm.mday (static_cast<int> (m ["mday"] . double_value ()));
  tm.mon (static_cast<int> (m ["mon"] . double_value ()));
  tm.year (static_cast<int> (m ["year"] . double_value ()));
  tm.wday (static_cast<int> (m ["wday"] . double_value ()));
  tm.yday (static_cast<int> (m ["yday"] . double_value ()));
  tm.isdst (static_cast<int> (m ["isdst"] . double_value ()));
  tm.zone (m ["zone"] . string_value ());

  return tm;
}

DEFUN_DLD (time, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} time ()\n\
Return the current time as the number of seconds since the epoch.  The\n\
epoch is referenced to 00:00:00 CUT (Coordinated Universal Time) 1 Jan\n\
1970.  For example, on Monday February 17, 1997 at 07:15:06 CUT, the\n\
value returned by @code{time} was 856163706.\n\
@end deftypefn")
{
  octave_value retval;

  if (args.length () == 0)
    retval = static_cast<double> (octave_time ());
  else
    print_usage ("time");

  return retval;
}

DEFUN_DLD (gmtime, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} gmtime (@var{t})\n\
Given a value returned from time (or any nonnegative integer),\n\
return a time structure corresponding to CUT.  For example,\n\
\n\
@example\n\
@group\n\
gmtime (time ())\n\
     @result{} @{\n\
           usec = 0\n\
           year = 97\n\
           mon = 1\n\
           mday = 17\n\
           sec = 6\n\
           zone = CST\n\
           min = 15\n\
           wday = 1\n\
           hour = 7\n\
           isdst = 0\n\
           yday = 47\n\
         @}\n\
@end group\n\
@end example\n\
@end deftypefn")
{
  octave_value retval;

  if (args.length () == 1)
    {
      double tmp = args(0).double_value ();

      if (! error_state)
	retval = octave_value (mk_tm_map (octave_gmtime (tmp)));
    }
  else
    print_usage ("gmtime");

  return retval;
}

DEFUN_DLD (localtime, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} localtime (@var{t})\n\
Given a value returned from time (or any nonnegative integer),\n\
return a time structure corresponding to the local time zone.\n\
\n\
@example\n\
@group\n\
localtime (time ())\n\
     @result{} @{\n\
           usec = 0\n\
           year = 97\n\
           mon = 1\n\
           mday = 17\n\
           sec = 6\n\
           zone = CST\n\
           min = 15\n\
           wday = 1\n\
           hour = 1\n\
           isdst = 0\n\
           yday = 47\n\
         @}\n\
@end group\n\
@end example\n\
@end deftypefn")
{
  octave_value retval;

  if (args.length () == 1)
    {
      double tmp = args(0).double_value ();

      if (! error_state)
	retval = octave_value (mk_tm_map (octave_localtime (tmp)));
    }
  else
    print_usage ("localtime");

  return retval;
}

DEFUN_DLD (mktime, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} mktime (@var{tm_struct})\n\
Convert a time structure corresponding to the local time to the number\n\
of seconds since the epoch.  For example,\n\
\n\
@example\n\
@group\n\
mktime (localtime (time ())\n\
     @result{} 856163706\n\
@end group\n\
@end example\n\
@end deftypefn")
{
  octave_value retval;

  if (args.length () == 1)
    {
      Octave_map map = args(0).map_value ();

      if (! error_state)
	{
	  octave_base_tm tm = extract_tm (map);

	  if (! error_state)
	    retval = static_cast<double> (octave_time (tm));
	  else
	    error ("mktime: invalid TMSTRUCT argument");
	}
      else
	error ("mktime: expecting structure argument");
    }
  else
    print_usage ("mktime");

  return retval;
}

DEFUN_DLD (strftime, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} strftime (@var{tm_struct})\n\
Format a time structure in a flexible way using @samp{%} substitutions\n\
similar to those in @code{printf}.  Except where noted, substituted\n\
fields have a fixed size; numeric fields are padded if necessary.\n\
Padding is with zeros by default; for fields that display a single\n\
number, padding can be changed or inhibited by following the @samp{%}\n\
with one of the modifiers described below.  Unknown field specifiers are\n\
copied as normal characters.  All other characters are copied to the\n\
output without change.  For example,\n\
\n\
@example\n\
@group\n\
strftime (\"%r (%Z) %A %e %B %Y\", localtime (time ())\n\
     @result{} \"01:15:06 AM (CST) Monday 17 February 1997\"\n\
@end group\n\
@end example\n\
\n\
Octave's @code{strftime} function supports a superset of the ANSI C\n\
field specifiers.\n\
\n\
@noindent\n\
Literal character fields:\n\
\n\
@table @code\n\
@item %\n\
% character.\n\
\n\
@item n\n\
Newline character.\n\
\n\
@item t\n\
Tab character.\n\
@end table\n\
\n\
@noindent\n\
Numeric modifiers (a nonstandard extension):\n\
\n\
@table @code\n\
@item - (dash)\n\
Do not pad the field.\n\
\n\
@item _ (underscore)\n\
Pad the field with spaces.\n\
@end table\n\
\n\
@noindent\n\
Time fields:\n\
\n\
@table @code\n\
@item %H\n\
Hour (00-23).\n\
\n\
@item %I\n\
Hour (01-12).\n\
\n\
@item %k\n\
Hour (0-23).\n\
\n\
@item %l\n\
Hour (1-12).\n\
\n\
@item %M\n\
Minute (00-59).\n\
\n\
@item %p\n\
Locale's AM or PM.\n\
\n\
@item %r\n\
Time, 12-hour (hh:mm:ss [AP]M).\n\
\n\
@item %R\n\
Time, 24-hour (hh:mm).\n\
\n\
@item %s\n\
Time in seconds since 00:00:00, Jan 1, 1970 (a nonstandard extension).\n\
\n\
@item %S\n\
Second (00-61).\n\
\n\
@item %T\n\
Time, 24-hour (hh:mm:ss).\n\
\n\
@item %X\n\
Locale's time representation (%H:%M:%S).\n\
\n\
@item %Z\n\
Time zone (EDT), or nothing if no time zone is determinable.\n\
@end table\n\
\n\
@noindent\n\
Date fields:\n\
\n\
@table @code\n\
@item %a\n\
Locale's abbreviated weekday name (Sun-Sat).\n\
\n\
@item %A\n\
Locale's full weekday name, variable length (Sunday-Saturday).\n\
\n\
@item %b\n\
Locale's abbreviated month name (Jan-Dec).\n\
\n\
@item %B\n\
Locale's full month name, variable length (January-December).\n\
\n\
@item %c\n\
Locale's date and time (Sat Nov 04 12:02:33 EST 1989).\n\
\n\
@item %C\n\
Century (00-99).\n\
\n\
@item %d\n\
Day of month (01-31).\n\
\n\
@item %e\n\
Day of month ( 1-31).\n\
\n\
@item %D\n\
Date (mm/dd/yy).\n\
\n\
@item %h\n\
Same as %b.\n\
\n\
@item %j\n\
Day of year (001-366).\n\
\n\
@item %m\n\
Month (01-12).\n\
\n\
@item %U\n\
Week number of year with Sunday as first day of week (00-53).\n\
\n\
@item %w\n\
Day of week (0-6).\n\
\n\
@item %W\n\
Week number of year with Monday as first day of week (00-53).\n\
\n\
@item %x\n\
Locale's date representation (mm/dd/yy).\n\
\n\
@item %y\n\
Last two digits of year (00-99).\n\
\n\
@item %Y\n\
Year (1970-).\n\
@end table\n\
@end deftypefn\n")
{
  octave_value retval;

  if (args.length () == 2)
    {
      std::string fmt = args(0).string_value ();

      if (! error_state)
	{
	  Octave_map map = args(1).map_value ();

	  if (! error_state)
	    {
	      octave_base_tm tm = extract_tm (map);

	      if (! error_state)
		retval = tm.strftime (fmt);
	      else
		error ("strftime: invalid TMSTRUCT argument");
	    }
	  else
	    error ("strftime: expecting structure as second argument");
	}
      else
	error ("strftime: expecting format string as first argument");
    }
  else
    print_usage ("strftime");

  return retval;
}

DEFUN_DLD (strptime, args, ,
 "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {[@var{tm_struct}, @var{nchars}] =} stpftime (@var{str}, @var{fmt})\n\
Convert the string @var{str} to a time structure under the control of\n\
the format @var{fmt}.\n\
@end deftypefn")
{
  octave_value_list retval;

  if (args.length () == 2)
    {
      std::string str = args(0).string_value ();

      if (! error_state)
	{
	  std::string fmt = args(1).string_value ();

	  if (! error_state)
	    {
	      octave_strptime t (str, fmt);

	      retval(1) = static_cast<double> (t.characters_converted ());
	      retval(0) = octave_value (mk_tm_map (t));
	    }
	  else
	    error ("strptime: expecting format string as second argument");
	}
      else
	error ("strptime: expecting string as first argument");
    }
  else
    print_usage ("strptime");

  return retval;
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
