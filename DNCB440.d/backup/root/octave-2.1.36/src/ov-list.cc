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

#if defined (__GNUG__)
#pragma implementation
#endif

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <strstream>

#include "lo-utils.h"

#include "defun.h"
#include "error.h"
#include "ov-list.h"
#include "unwind-prot.h"

DEFINE_OCTAVE_ALLOCATOR (octave_list);

DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_list, "list");

octave_value
octave_list::do_index_op (const octave_value_list& idx)
{
  octave_value retval;

  if (idx.length () == 1)
    {
      idx_vector i = idx (0).index_vector ();

      retval = octave_value_list (lst.index (i));
    }
  else
    error ("lists may only be indexed by a single scalar");

  return retval;
}

void
octave_list::assign (const octave_value_list& idx, const octave_value& rhs)
{
  if (idx.length () == 1)
    {
      int i = idx(0).int_value (true);

      if (! error_state)
	{
	  int n = lst.length ();

	  if (i > 0 && (Vresize_on_range_error || i <= n))
	    lst(i-1) = rhs;
	  else
	    error ("list index = %d out of range", i);
	}
      else
	error ("list index must be an integer");
    }
  else
    error ("lists may only be indexed by a single scalar");
}

void
octave_list::print (std::ostream& os, bool) const
{
  print_raw (os);
}

void
octave_list::print_raw (std::ostream& os, bool) const
{
  unwind_protect::begin_frame ("octave_list_print");

  int n = lst.length ();

  if (n > 0)
    {
      indent (os);
      os << "(";
      newline (os);

      increment_indent_level ();

      for (int i = 0; i < n; i++)
	{
	  std::ostrstream buf;
	  buf << "[" << i+1 << "]" << std::ends;
	  const char *nm = buf.str ();

	  octave_value val = lst(i);

	  val.print_with_name (os, nm);

	  delete [] nm;
	}

      decrement_indent_level ();

      indent (os);
      os << ")";
    }
  else
    os << "()";

  newline (os);

  unwind_protect::run_frame ("octave_list_print");
}

bool
octave_list::print_name_tag (std::ostream& os, const std::string& name) const
{
  indent (os);
  if (lst.length () == 0)
    os << name << " = ";
  else
    {
      os << name << " =";
      newline (os);
    }
  return false;
}

DEFUN (list, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} list (@var{a1}, @var{a2}, @dots{})\n\
Create a new list with elements given by the arguments @var{a1},\n\
@var{a2}, @dots{}.\n\
@end deftypefn")
{
  return octave_value (args);
}

DEFUN (nth, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} nth (@var{list}, @var{n})\n\
Return the @var{n}-th element of @var{list}.\n\
@end deftypefn")
{
  octave_value retval;

  if (args.length () == 2)
    {
      octave_value_list lst = args(0).list_value ();

      if (! error_state)
	{
	  int n = args(1).int_value (true);

	  if (! error_state)
	    {
	      if (n > 0 && n <= lst.length ())
		retval = lst(n-1);
	      else
		error ("nth: index = %d out of range", n);
	    }
	  else
	    error ("nth: second argument must be an integer");
	}
      else
	error ("nth: first argument must be a list");
    }
  else
    print_usage ("nth");

  return retval;
}

DEFUN (append, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} append (@var{list}, @var{a1}, @var{a2}, @dots{})\n\
Return a new list created by appending @var{a1}, @var{a1}, @dots{}, to\n\
@var{list}.  If any of the arguments to be appended is a list, its\n\
elements are appended individually.  For example,\n\
\n\
@example\n\
x = list (1, 2);\n\
y = list (3, 4);\n\
append (x, y);\n\
@end example\n\
\n\
@noindent\n\
results in the list containing the four elements @samp{(1 2 3 4)}, not\n\
a list containing the three elements @samp{(1 2 (3 4))}.\n\
@end deftypefn")
{
  octave_value retval;

  int nargin = args.length ();

  if (nargin > 1)
    {
      octave_value_list tmp = args(0).list_value ();

      if (! error_state)
	{
	  for (int i = 1; i < nargin; i++)
	    {
	      octave_value ov = args(i);

	      if (ov.is_list ())
		tmp.append (ov.list_value ());
	      else
		tmp.append (ov);
	    }

	  retval = tmp;
	}
    }
  else
    print_usage ("append");

  return retval;
}

DEFUN (reverse, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} reverse (@var{list})\n\
Return a new list created by reversing the elements of @var{list}.\n\
@end deftypefn")
{
  octave_value retval;

  int nargin = args.length ();

  if (nargin == 1)
    {
      octave_value_list tmp = args(0).list_value ();

      if (! error_state)
	  retval = tmp.reverse ();
    }
  else
    print_usage ("reverse");

  return retval;
}

DEFUN (splice, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} splice (@var{list_1}, @var{offset}, @var{length}, @var{list_2})\n\
Replace @var{length} elements of @var{list_1} beginning at\n\
@var{offset} with the contents of @var{list_2} (if any).  If\n\
@var{length} is omitted, all elements from @var{offset} to the end of\n\
@var{list_1} are replaced.  As a special case, if @var{offset} is one\n\
greater than the length of @var{list_1} and @var{length} is 0, splice\n\
is equivalent to @code{append (@var{list_1}, @var{list_2})}.\n\
@end deftypefn") 
{
  octave_value retval;

  int nargin = args.length ();

  if (nargin > 1 && nargin < 5)
    {
      octave_value_list list_1 = args(0).list_value ();

      if (! error_state)
	{
	  int offset = args(1).int_value (true);

	  if (! error_state)
	    {
	      offset--;

	      int length = 0;

	      octave_value_list list_2;

	      if (nargin < 3)
		length = list_1.length () - offset;
	      else
		{
		  length = args(2).int_value (true);

		  if (! error_state)
		    {
		      if (nargin == 4)
			{
			  list_2 = args(3).list_value ();

			  if (error_state)
			    error ("splice: fourth argument must be a list");
			}
		    }
		  else
		    error ("splice: LENGTH must be an integer");
		}

	      if (! error_state)
		retval = list_1.splice (offset, length, list_2);
	    }
	  else
	    error ("splice: OFFSET must be an integer");
	}
      else
	error ("splice: first argument must be a list");      
    }
  else
    print_usage ("splice");

  return retval;
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
