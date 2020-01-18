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

#if defined (__GNUG__) && defined (USE_PRAGMA_INTERFACE_IMPLEMENTATION)
#pragma implementation
#endif

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>

#include "lo-sstream.h"
#include "lo-utils.h"

#include "Cell.h"
#include "defun.h"
#include "error.h"
#include "ov-list.h"
#include "unwind-prot.h"

#include "byte-swap.h"
#include "ls-oct-ascii.h"
#include "ls-oct-binary.h"
#include "ls-hdf5.h"
#include "ls-utils.h"

DEFINE_OCTAVE_ALLOCATOR (octave_list);

DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_list, "list", "list");

octave_list::octave_list (const Cell& c)
  : octave_base_value (), data ()
{
  int n = c.length ();

  data.resize (dim_vector (1, n));

  for (int i = 0; i < n; i++)
    data(i) = c(i);
}

octave_value
octave_list::subsref (const std::string& type,
		      const std::list<octave_value_list>& idx)
{
  octave_value retval;

  switch (type[0])
    {
    case '(':
      {
	octave_value_list tmp_idx = idx.front ();

	if (tmp_idx.length () == 1)
	  {
	    idx_vector i = tmp_idx (0).index_vector ();

	    retval = octave_list (data.index (i));
	  }
	else
	  error ("only one index allowed for lists");
      }
      break;

    case '{':
      {
	octave_value_list tmp_idx = idx.front ();

	if (tmp_idx.length () == 1)
	  {
	    idx_vector i = tmp_idx (0).index_vector ();

	    Cell tmp = data.index (i);

	    if (tmp.length () == 1)
	      retval = tmp(0);
	  }
	else
	  error ("only one index allowed for lists");
      }
      break;

    case '.':
      {
	std::string nm = type_name ();
	error ("%s cannot be indexed with %c", nm.c_str (), type[0]);
      }
      break;

    default:
      panic_impossible ();
    }

  return retval.next_subsref (type, idx);
}

octave_value
octave_list::do_index_op (const octave_value_list& idx, int resize_ok)
{
  octave_value retval;

  if (idx.length () == 1)
    {
      idx_vector i = idx (0).index_vector ();

      retval = octave_list (data.index (i, resize_ok));
    }
  else
    error ("lists may only be indexed by a single scalar");

  return retval;
}

octave_value
octave_list::subsasgn (const std::string& type,
		       const std::list<octave_value_list>& idx,
		       const octave_value& rhs)
{
  octave_value retval;

  int n = type.length ();

  octave_value t_rhs = rhs;

  if (n > 1)
    {
      switch (type[0])
	{
	case '(':
	  {
	    octave_value tmp = do_index_op (idx.front (), true);

	    if (! tmp.is_defined ())
	      tmp = octave_value::empty_conv (type.substr (1), rhs);

	    if (! error_state)
	      {
		std::list<octave_value_list> next_idx (idx);

		next_idx.erase (next_idx.begin ());

		t_rhs = tmp.subsasgn (type.substr (1), next_idx, rhs);
	      }
	  }
	  break;

	case '{':
	case '.':
	  {
	    std::string nm = type_name ();
	    error ("%s cannot be indexed with %c", nm.c_str (), type[0]);
	  }
	  break;

	default:
	  panic_impossible ();
	}
    }

  if (! error_state)
    {
      switch (type[0])
	{
	case '(':
	  {
	    octave_value_list i = idx.front ();

	    int len = i.length ();

	    for (int k = 0; k < len; k++)
	      data.set_index (i(k).index_vector ());

	    ::assign (data, Cell (t_rhs), Cell::resize_fill_value ());

	    retval = octave_value (this, count + 1);
	  }
	  break;

	case '{':
	case '.':
	  {
	    std::string nm = type_name ();
	    error ("%s cannot be indexed with %c", nm.c_str (), type[0]);
	  }
	  break;

	default:
	  panic_impossible ();
	}
    }

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
	  int n = data.length ();

	  if (i > 0)
	    {
	      if (Vwarn_resize_on_range_error && i > n)
		warning ("list index = %d out of range", i);

	      data(i-1) = rhs;
	    }
	  else
	    error ("list index = %d out of range", i);
	}
      else
	error ("list index must be an integer");
    }
  else
    error ("lists may only be indexed by a single scalar");
}

size_t
octave_list::byte_size (void) const
{
  size_t retval = 0;

  for (int i = 0; i < numel (); i++)
    retval += data(i).byte_size ();

  return retval;
}

octave_value_list
octave_list::list_value (void) const
{
  octave_value_list retval;

  int n = data.length ();

  retval.resize (n);
  
  for (int i = 0; i < n; i++)
    retval(i) = data(i);

  return retval;
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

  int n = data.length ();

  if (n > 0)
    {
      indent (os);
      os << "(";
      newline (os);

      increment_indent_level ();

      for (int i = 0; i < n; i++)
	{
	  OSSTREAM buf;

	  buf << "[" << i+1 << "]" << OSSTREAM_ENDS;

	  octave_value val = data(i);

	  val.print_with_name (os, OSSTREAM_STR (buf));

	  OSSTREAM_FREEZE (buf);
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
  if (data.length () == 0)
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
  static bool warned = false;

  if (! warned)
    {
      warning ("list objects are deprecated; use cell arrays instead");
      warned = true;
    }

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

	  retval = octave_value (tmp);
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
	  retval = octave_value (tmp.reverse ());
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
		retval = octave_value (list_1.splice (offset, length, list_2));
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

bool 
octave_list::save_ascii (std::ostream& os, bool& infnan_warned, 
			   bool strip_nan_and_inf)
{
  octave_value_list lst = list_value ();
  os << "# length: " << lst.length () << "\n";

  for (int i = 0; i < lst.length (); ++i)
    {
      // should we use lst.name_tags () to label the elements?
      char s[20];
      sprintf (s, "_%d", i);
      bool b = save_ascii_data (os, lst (i), s, infnan_warned, 
				strip_nan_and_inf, 0, 0);
      
      if (! b)
	return false;
    }

  return true;
}

bool 
octave_list::load_ascii (std::istream& is)
{
  int len = 0;
  bool success = true;

  if (extract_keyword (is, "length", len) && len >= 0)
    {
      if (len > 0)
	{
	  octave_value_list lst;

	  for (int j = 0; j < len; j++)
	    {
	      octave_value t2;
	      bool dummy;

	      // recurse to read list elements
	      std::string nm
		= read_ascii_data (is, std::string (), dummy, t2, count);

	      if (!is)
		break;

	      lst.append (t2);
	    }

	  if (is) 
	    data = lst;
	  else
	    {
	      error ("load: failed to load list");
	      success = false;
	    }
	}
      else if (len == 0 )
	data = Cell (0, 0);
      else
	panic_impossible ();
    }
  else {
    error ("load: failed to extract number of elements in list");
    success = false;
  }

  return success;
}

bool 
octave_list::save_binary (std::ostream& os, bool& save_as_floats)
{
  octave_value_list lst = list_value ();

  FOUR_BYTE_INT len = lst.length();
  os.write (X_CAST (char *, &len), 4);
  
  for (int i = 0; i < lst.length (); i++)
    {
      // should we use lst.name_tags () to label the elements?
      char s[20];
      sprintf (s, "_%d", i);

      // Recurse to print sub-value.
      bool b = save_binary_data (os, lst(i), s, "", 0, save_as_floats);
	      
      if (! b)
	return false;
    }
  
  return true;
}

bool 
octave_list::load_binary (std::istream& is, bool swap,
				 oct_mach_info::float_format fmt)
{
  FOUR_BYTE_INT len;
  if (! is.read (X_CAST (char *, &len), 4))
    return false;
  if (swap)
    swap_4_bytes (X_CAST (char *, &len));

  if (len > 0)
    {
      octave_value_list lst;

      for (int i = 0; i < len; i++)
	{
	  octave_value t2;
	  bool dummy;
	  std::string doc;
	  
	  // recurse to read list elements
	  std::string nm = read_binary_data (is, swap, fmt, std::string (), 
					     dummy, t2, doc);
	  
	  if (!is)
	    return false;
	  
	  lst.append(t2);
	}

      if (is)
	data = lst;
      else
	{
	  error ("load: failed to load list");
	  return false;
	}

    }
  else if (len == 0 )
    data = Cell (0, 0);
  else
    return false;
  
  return true;
}

#if defined (HAVE_HDF5)
bool
octave_list::save_hdf5 (hid_t loc_id, const char *name, bool save_as_floats)
{
  hid_t data_hid = -1;

  data_hid = H5Gcreate (loc_id, name, 0);
  if (data_hid < 0) return false;

  // recursively add each element of the list to this group
  octave_value_list lst = list_value ();

  for (int i = 0; i < lst.length (); ++i)
    {
      // should we use lst.name_tags () to label the elements?
      char s[20];
      sprintf (s, "_%d", i);
      bool retval2 = add_hdf5_data (data_hid, lst (i), s, "",
				    false, save_as_floats);
      if (! retval2)
	break;
    }

  H5Gclose (data_hid);

  return true;
}

bool
octave_list::load_hdf5 (hid_t loc_id,  const char *name,
			bool have_h5giterate_bug)
{
  bool retval = false;

  hdf5_callback_data dsub;

  herr_t retval2 = -1;
  octave_value_list lst;
  int current_item = 0;
#ifdef HAVE_H5GGET_NUM_OBJS
  hsize_t num_obj = 0;
  H5Gget_num_objs (loc_id, &num_obj);

  while (current_item < static_cast<int> (num_obj)
	 && (retval2 = H5Giterate (loc_id, name, &current_item,
				   hdf5_read_next_data, &dsub)) > 0)
#else
  while ((retval2 = H5Giterate (loc_id, name, &current_item,
				hdf5_read_next_data, &dsub)) > 0)
#endif
    {
      lst.append (dsub.tc);

      if (have_h5giterate_bug)
	current_item++;  // H5Giterate returned the last index processed
    }

  if (retval2 >= 0)
    {
      data = lst;
      retval = true;
    }
  
  return retval;
}
#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
