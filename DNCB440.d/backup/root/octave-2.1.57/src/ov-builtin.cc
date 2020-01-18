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

#include "error.h"
#include "oct-obj.h"
#include "ov-builtin.h"
#include "ov.h"
#include "toplev.h"
#include "unwind-prot.h"

DEFINE_OCTAVE_ALLOCATOR (octave_builtin);

DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_builtin,
				     "built-in function",
				     "built-in function");

// Are any of the arguments `:'?

static bool
any_arg_is_magic_colon (const octave_value_list& args)
{
  int nargin = args.length ();

  for (int i = 0; i < nargin; i++)
    if (args(i).is_magic_colon ())
      return true;

  return false;
}

octave_value_list
octave_builtin::subsref (const std::string& type,
			 const std::list<octave_value_list>& idx,
			 int nargout)
{
  octave_value_list retval;

  switch (type[0])
    {
    case '(':
      retval = do_multi_index_op (nargout, idx.front ());
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

  // XXX FIXME XXX -- perhaps there should be an
  // octave_value_list::next_subsref member function?  See also
  // octave_user_function::subsref.
  //
  // XXX FIXME XXX -- Note that if a function call returns multiple
  // values, and there is further indexing to perform, then we are
  // ignoring all but the first value.  Is this really what we want to
  // do?  If it is not, then what should happen for stat("file").size,
  // for exmaple?

  if (idx.size () > 1)
    retval = retval(0).next_subsref (type, idx);

  return retval;
}

octave_value_list
octave_builtin::do_multi_index_op (int nargout, const octave_value_list& args)
{
  octave_value_list retval;

  if (error_state)
    return retval;

  if (any_arg_is_magic_colon (args))
    ::error ("invalid use of colon in function argument list");
  else
    {
      unwind_protect_ptr (curr_function);
      curr_function = this;

      retval = (*f) (args, nargout);

      unwind_protect::run ();
    }

  return retval;
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
