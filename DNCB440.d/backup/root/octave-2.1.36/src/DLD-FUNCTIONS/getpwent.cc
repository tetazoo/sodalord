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

#include "oct-passwd.h"

#include "defun-dld.h"
#include "error.h"
#include "gripes.h"
#include "oct-map.h"
#include "ov.h"
#include "oct-obj.h"
#include "utils.h"

// Password file functions.  (Why not?)

static octave_value
mk_pw_map (const octave_passwd& pw)
{
  octave_value retval;

  if (pw)
    {
      Octave_map m;

      m ["name"] = pw.name ();
      m ["passwd"] = pw.passwd ();
      m ["uid"] = static_cast<double> (pw.uid ());
      m ["gid"] = static_cast<double> (pw.gid ());
      m ["gecos"] = pw.gecos ();
      m ["dir"] = pw.dir ();
      m ["shell"] = pw.shell ();

      retval = m;
    }
  else
    retval = 0.0;

  return retval;
}

DEFUN_DLD (getpwent, args, ,
 "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{pw_struct} = } getpwent ()\n\
Return a structure containing an entry from the password database,\n\
opening it if necessary. Once the end of the data has been reached,\n\
@code{getpwent} returns 0.\n\
@end deftypefn")
{
  octave_value_list retval;

  retval(1) = std::string ();
  retval(0) = 0.0;

  int nargin = args.length ();

  if (nargin == 0)
    {
      std::string msg;

      retval(0) = mk_pw_map (octave_passwd::getpwent (msg));
      retval(1) = msg;
    }
  else
    print_usage ("getpwent");

  return retval;
}

DEFUN_DLD (getpwuid, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{pw_struct} = } getpwuid (@var{uid}).\n\
Return a structure containing the first entry from the password database\n\
with the user ID @var{uid}.  If the user ID does not exist in the\n\
database, @code{getpwuid} returns 0.\n\
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
	      uid_t uid = static_cast<uid_t> (dval);

	      std::string msg;

	      retval(0) = mk_pw_map (octave_passwd::getpwuid (uid, msg));
	      retval(1) = msg;
	    }
	  else
	    error ("getpwuid: argument must be an integer");
	}
    }
  else
    print_usage ("getpwuid");

  return retval;
}

DEFUN_DLD (getpwnam, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{pw_struct} = } getpwnam (@var{name})\n\
Return a structure containing the first entry from the password database\n\
with the user name @var{name}.  If the user name does not exist in the\n\
database, @code{getpwname} returns 0.\n\
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

	  retval(0) = mk_pw_map (octave_passwd::getpwnam (s.c_str (), msg));
	  retval(1) = msg;
	}
    }
  else
    print_usage ("getpwnam");

  return retval;
}

DEFUN_DLD (setpwent, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} setpwent ()\n\
Return the internal pointer to the beginning of the password database.\n\
@end deftypefn")
{
  octave_value_list retval;

  retval(1) = std::string ();
  retval(0) = -1.0;

  int nargin = args.length ();

  if (nargin == 0)
    {
      std::string msg;

      retval(0) = static_cast<double> (octave_passwd::setpwent (msg));
      retval(1) = msg;
    }
  else
    print_usage ("setpwent");

  return retval;
}

DEFUN_DLD (endpwent, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} endpwent ()\n\
Close the password database.\n\
@end deftypefn")
{
  octave_value_list retval;

  retval(1) = std::string ();
  retval(0) = -1.0;

  int nargin = args.length ();

  if (nargin == 0)
    {
      std::string msg;

      retval(0) = static_cast<double> (octave_passwd::endpwent (msg));
      retval(1) = msg;
    }
  else
    print_usage ("endpwent");

  return retval;
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
