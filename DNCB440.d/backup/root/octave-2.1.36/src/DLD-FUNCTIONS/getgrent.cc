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

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

#include "oct-group.h"

#include "defun-dld.h"
#include "error.h"
#include "gripes.h"
#include "oct-map.h"
#include "ov.h"
#include "oct-obj.h"
#include "utils.h"

// Group file functions.  (Why not?)

static octave_value
mk_gr_map (const octave_group& gr)
{
  octave_value retval;

  if (gr)
    {
      Octave_map m;

      m ["name"] = gr.name ();
      m ["passwd"] = gr.passwd ();
      m ["gid"] = static_cast<double> (gr.gid ());
      m ["mem"] = gr.mem ();

      retval = m;
    }
  else
    retval = 0.0;

  return retval;
}

DEFUN_DLD (getgrent, args, ,
 "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{grp_struct} =} getgrent ()\n\
Return an entry from the group database, opening it if necessary.\n\
Once the end of the data has been reached, @code{getgrent} returns 0.\n\
@end deftypefn")
{
  octave_value_list retval;

  retval(1) = std::string ();
  retval(0) = 0.0;

  int nargin = args.length ();

  if (nargin == 0)
    {
      std::string msg;

      retval(0) = mk_gr_map (octave_group::getgrent (msg));
      retval(1) = msg;
    }
  else
    print_usage ("getgrent");

  return retval;
}

DEFUN_DLD (getgrgid, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{grp_struct} =} getgrgid (@var{gid}).\n\
Return the first entry from the group database with the group ID\n\
@var{gid}.  If the group ID does not exist in the database,\n\
@code{getgrgid} returns 0.\n\
@end deftypefn")
{
  octave_value_list retval;

  retval(1) = std::string ();
  retval(0) = 0.0;

  int nargin = args.length ();

  if (nargin == 1)
    {
      double dval = args(0).double_value ();

      if (! error_state)
	{
	  if (D_NINT (dval) == dval)
	    {
	      gid_t gid = static_cast<gid_t> (dval);

	      std::string msg;

	      retval(0) = mk_gr_map (octave_group::getgrgid (gid, msg));
	      retval(1) = msg;
	    }
	  else
	    error ("getgrgid: argument must be an integer");
	}
    }
  else
    print_usage ("getgrgid");

  return retval;
}

DEFUN_DLD (getgrnam, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{grp_struct} =} getgrnam (@var{name})\n\
Return the first entry from the group database with the group name\n\
@var{name}.  If the group name does not exist in the database,\n\
@code{getgrname} returns 0.\n\
@end deftypefn")
{
  octave_value_list retval;

  retval(1) = std::string ();
  retval(0) = 0.0;

  int nargin = args.length ();

  if (nargin == 1)
    {
      std::string s = args(0).string_value ();

      if (! error_state)
	{
	  std::string msg;

	  retval(0) = mk_gr_map (octave_group::getgrnam (s.c_str (), msg));
	  retval(1) = msg;
	}
    }
  else
    print_usage ("getgrnam");

  return retval;
}

DEFUN_DLD (setgrent, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} setgrent ()\n\
Return the internal pointer to the beginning of the group database.\n\
@end deftypefn")
{
  octave_value_list retval;

  retval(1) = std::string ();
  retval(0) = -1.0;

  int nargin = args.length ();

  if (nargin == 0)
    {
      std::string msg;

      retval(0) = static_cast<double> (octave_group::setgrent (msg));
      retval(1) = msg;
    }
  else
    print_usage ("setgrent");

  return retval;
}

DEFUN_DLD (endgrent, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} endgrent ()\n\
Close the group database.\n\
@end deftypefn")
{
  octave_value_list retval;

  retval(1) = std::string ();
  retval(0) = -1.0;

  int nargin = args.length ();

  if (nargin == 0)
    {
      std::string msg;

      retval(0) = static_cast<double> (octave_group::endgrent (msg));
      retval(1) = msg;
    }
  else
    print_usage ("endgrent");

  return retval;
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
