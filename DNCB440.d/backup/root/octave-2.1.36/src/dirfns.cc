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

#include <cerrno>
#include <cstdio>
#include <cstddef>
#include <cstdlib>
#include <cstring>

#include <strstream>
#include <string>

#ifdef HAVE_UNISTD_H
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#include <unistd.h>
#endif

#include "file-ops.h"
#include "file-stat.h"
#include "glob-match.h"
#include "oct-env.h"
#include "str-vec.h"

#include "defun.h"
#include "dir-ops.h"
#include "dirfns.h"
#include "error.h"
#include "gripes.h"
#include "oct-obj.h"
#include "pager.h"
#include "procstream.h"
#include "pt-plot.h"
#include "sysdep.h"
#include "toplev.h"
#include "unwind-prot.h"
#include "utils.h"
#include "variables.h"

// XXX FIXME XXX -- changing the plotter directory should be handled
// by registering a function for octave_env::chdir to call so that
// this function can be eliminated.

static int
octave_change_to_directory (const std::string& newdir)
{
  int cd_ok = octave_env::chdir (newdir);

  if (cd_ok)
    do_external_plotter_cd (newdir);
  else
    {
      using namespace std;

      error ("%s: %s", newdir.c_str (), strerror (errno));
    }

  return cd_ok;
}

DEFUN_TEXT (cd, args, ,
  "-*- texinfo -*-\n\
@deffn {Command} cd dir\n\
@deffnx {Command} chdir dir\n\
Change the current working directory to @var{dir}.  If @var{dir} is\n\
omitted, the current directory is changed to the users home\n\
directory.  For example,\n\
\n\
@example\n\
cd ~/octave\n\
@end example\n\
\n\
@noindent\n\
Changes the current working directory to @file{~/octave}.  If the\n\
directory does not exist, an error message is printed and the working\n\
directory is not changed.\n\
@end deffn")
{
  octave_value_list retval;

  int argc = args.length () + 1;

  string_vector argv = args.make_argv ("cd");

  if (error_state)
    return retval;

  if (argc > 1)
    {
      std::string dirname = file_ops::tilde_expand (argv[1]);

      if (dirname.length () > 0
	  && ! octave_change_to_directory (dirname))
	{
	  return retval;
	}
    }
  else
    {
      std::string home_dir = octave_env::get_home_directory ();

      if (home_dir.empty () || ! octave_change_to_directory (home_dir))
	return retval;
    }

  return retval;
}

DEFALIAS (chdir, cd);

// Get a directory listing.

static void
cleanup_iprocstream (void *p)
{
  delete static_cast <iprocstream *> (p);
}

DEFUN_TEXT (ls, args, ,
  "-*- texinfo -*-\n\
@deffn {Command} ls options\n\
@deffnx {Command} dir options\n\
List directory contents.  For example,\n\
\n\
@example\n\
ls -l\n\
     @print{} total 12\n\
     @print{} -rw-r--r--   1 jwe  users  4488 Aug 19 04:02 foo.m\n\
     @print{} -rw-r--r--   1 jwe  users  1315 Aug 17 23:14 bar.m\n\
@end example\n\
\n\
The @code{dir} and @code{ls} commands are implemented by calling your\n\
system's directory listing command, so the available options may vary\n\
from system to system.\n\
@end deffn")
{
  octave_value_list retval;

  int argc = args.length () + 1;

  string_vector argv = args.make_argv ("ls");

  if (error_state)
    return retval;

  std::ostrstream ls_buf;

  ls_buf << "ls -C ";
  for (int i = 1; i < argc; i++)
    ls_buf << file_ops::tilde_expand (argv[i]) << " ";

  ls_buf << std::ends;
  char *ls_command = ls_buf.str ();

  iprocstream *cmd = new iprocstream (ls_command);

  delete [] ls_command;

  unwind_protect::add (cleanup_iprocstream, cmd);

  // XXX FIXME XXX -- sometimes, the subprocess hasn't written
  // anything before we try to read from the procstream.  The kluge
  // below (simply waiting and trying again) is ugly, but it seems to
  // work, at least most of the time.  It could probably still fail if
  // the subprocess hasn't started writing after the snooze.  Isn't
  // there a better way?  If there is, you should also fix the code
  // for the system function in toplev.cc.

  if (cmd && *cmd)
    {
      char ch;

      if (cmd->get (ch))
        octave_stdout << ch;
      else
        {
          cmd->clear ();

          octave_usleep (100);
        }

      while (cmd->get (ch))
        octave_stdout << ch;
    }
  else
    error ("couldn't start process for ls!");

  unwind_protect::run ();

  return retval;
}

DEFALIAS (dir, ls);

DEFUN (pwd, , nargout,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} pwd ()\n\
Return the current working directory.\n\
@end deftypefn")
{
  octave_value_list retval;

  std::string directory = octave_env::getcwd ();

  if (directory.empty ())
    warning ("pwd: can't find working directory!");
  else
    {
      if (nargout == 0)
	octave_stdout << directory << "\n";
      else
	retval = directory;
    }

  return retval;
}

DEFUN (readdir, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {[@var{files}, @var{err}, @var{msg}] =} readdir (@var{dir})\n\
Return names of the files in the directory @var{dir} as an array of\n\
strings.  If an error occurs, return an empty matrix in @var{files}.\n\
\n\
If successful, @var{err} is 0 and @var{msg} is an empty string.\n\
Otherwise, @var{err} is nonzero and @var{msg} contains a\n\
system-dependent error message.\n\
@end deftypefn")
{
  octave_value_list retval;

  retval(2) = std::string ();
  retval(1) = -1.0;
  retval(0) = Matrix ();

  if (args.length () == 1)
    {
      std::string dirname = args(0).string_value ();

      if (error_state)
	gripe_wrong_type_arg ("readdir", args(0));
      else
	{
	  dir_entry dir (file_ops::tilde_expand (dirname));

	  if (dir)
	    {
	      string_vector dirlist = dir.read ();
	      retval(0) = dirlist.qsort ();
	      retval(1) = 0.0;
	    }
	  else
	    {
	      retval(2) = dir.error ();
	    }
	}
    }
  else
    print_usage ("readdir");

  return retval;
}

// XXX FIXME XXX -- should probably also allow second arg to specify
// mode.

DEFUN (mkdir, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {[@var{err}, @var{msg}] =} mkdir (@var{dir})\\n\
Create a directory named @var{dir}.\n\
\n\
If successful, @var{err} is 0 and @var{msg} is an empty string.\n\
Otherwise, @var{err} is nonzero and @var{msg} contains a\n\
system-dependent error message.\n\
@end deftypefn")
{
  octave_value_list retval;

  retval(1) = std::string ();
  retval(0) = -1.0;

  if (args.length () == 1)
    {
      std::string dirname = args(0).string_value ();

      if (error_state)
	gripe_wrong_type_arg ("mkdir", args(0));
      else
	{
	  std::string msg;

	  int status = file_ops::mkdir (file_ops::tilde_expand (dirname),
					0777, msg);

	  retval(0) = static_cast<double> (status);

	  if (status < 0)
	    retval(1) = msg;
	}
    }
  else
    print_usage ("mkdir");

  return retval;
}

DEFUN (rmdir, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {[@var{err}, @var{msg}] =} rmdir (@var{dir})\n\
Remove the directory named @var{dir}.\n\
\n\
If successful, @var{err} is 0 and @var{msg} is an empty string.\n\
Otherwise, @var{err} is nonzero and @var{msg} contains a\n\
system-dependent error message.\n\
@end deftypefn")
{
  octave_value_list retval;

  retval(1) = std::string ();
  retval(0) = -1.0;

  if (args.length () == 1)
    {
      std::string dirname = args(0).string_value ();

      if (error_state)
	gripe_wrong_type_arg ("rmdir", args(0));
      else
	{
	  std::string msg;

	  int status = file_ops::rmdir (file_ops::tilde_expand (dirname), msg);

	  retval(0) = static_cast<double> (status);

	  if (status < 0)
	    retval(1) = msg;
	}
    }
  else
    print_usage ("rmdir");

  return retval;
}

DEFUN (link, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {[@var{err}, @var{msg}] =} link (@var{old}, @var{new})\n\
Create a new link (also known as a hard link) to an existing file.\n\
\n\
If successful, @var{err} is 0 and @var{msg} is an empty string.\n\
Otherwise, @var{err} is nonzero and @var{msg} contains a\n\
system-dependent error message.\n\
@end deftypefn")
{
  octave_value_list retval;

  retval(1) = std::string ();
  retval(0) = -1.0;

  if (args.length () == 2)
    {
      std::string from = args(0).string_value ();

      if (error_state)
	gripe_wrong_type_arg ("link", args(0));
      else
	{
	  std::string to = args(1).string_value ();

	  if (error_state)
	    gripe_wrong_type_arg ("link", args(1));
	  else
	    {
	      std::string msg;

	      int status = file_ops::link (from, to, msg);

	      retval(0) = static_cast<double> (status);

	      if (status < 0)
		retval(1) = msg;
	    }
	}
    }
  else
    print_usage ("link");

  return retval;
}

DEFUN (symlink, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {[@var{err}, @var{msg}] =} symlink (@var{old}, @var{new})\n\
Create a symbolic link @var{new} which contains the string @var{old}.\n\
\n\
If successful, @var{err} is 0 and @var{msg} is an empty string.\n\
Otherwise, @var{err} is nonzero and @var{msg} contains a\n\
system-dependent error message.\n\
@end deftypefn")
{
  octave_value_list retval;

  retval(1) = std::string ();
  retval(0) = -1.0;

  if (args.length () == 2)
    {
      std::string from = args(0).string_value ();

      if (error_state)
	gripe_wrong_type_arg ("symlink", args(0));
      else
	{
	  std::string to = args(1).string_value ();

	  if (error_state)
	    gripe_wrong_type_arg ("symlink", args(1));
	  else
	    {
	      std::string msg;

	      int status = file_ops::symlink (from, to, msg);

	      retval(0) = static_cast<double> (status);

	      if (status < 0)
		retval(1) = msg;
	    }
	}
    }
  else
    print_usage ("symlink");

  return retval;
}

DEFUN (readlink, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {[@var{result}, @var{err}, @var{msg}] =} symlink (@var{symlink})\n\
Read the value of the symbolic link @var{symlink}.\n\
\n\
If successful, @var{result} contains the contents of the symbolic link\n\
@var{symlink}, @var{err} is 0 and @var{msg} is an empty string.\n\
Otherwise, @var{err} is nonzero and @var{msg} contains a\n\
system-dependent error message.\n\
@end deftypefn")
{
  octave_value_list retval;

  retval(2) = std::string ();
  retval(1) = -1.0;
  retval(0) = std::string ();

  if (args.length () == 1)
    {
      std::string symlink = args(0).string_value ();

      if (error_state)
	gripe_wrong_type_arg ("readlink", args(0));
      else
	{
	  std::string result;
	  std::string msg;

	  int status = file_ops::readlink (symlink, result, msg);

	  retval(0) = result;

	  retval(1) = static_cast<double> (status);

	  if (status < 0)
	    retval(2) = msg;
	}
    }
  else
    print_usage ("readlink");

  return retval;
}

DEFUN (rename, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {[@var{err}, @var{msg}] =} rename (@var{old}, @var{new})\n\
Change the name of file @var{old} to @var{new}.\n\
\n\
If successful, @var{err} is 0 and @var{msg} is an empty string.\n\
Otherwise, @var{err} is nonzero and @var{msg} contains a\n\
system-dependent error message.\n\
@end deftypefn")
{
  octave_value_list retval;

  retval(1) = std::string ();
  retval(0) = -1.0;

  if (args.length () == 2)
    {
      std::string from = args(0).string_value ();

      if (error_state)
	gripe_wrong_type_arg ("rename", args(0));
      else
	{
	  std::string to = args(1).string_value ();

	  if (error_state)
	    gripe_wrong_type_arg ("rename", args(1));
	  else
	    {
	      std::string msg;

	      int status = file_ops::rename (from, to, msg);

	      retval(0) = static_cast<double> (status);

	      if (status < 0)
		retval(1) = msg;
	    }
	}
    }
  else
    print_usage ("rename");

  return retval;
}

DEFUN (glob, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} glob (@var{pattern})\n\
Given an array of strings in @var{pattern}, return the list of file\n\
names that match any of them, or an empty string if no patterns match.\n\
Tilde expansion is performed on each of the patterns before looking for\n\
matching file names.  For example,\n\
\n\
@example\n\
@group\n\
glob (\"/vm*\")\n\
     @result{} \"/vmlinuz\"\n\
@end group\n\
@end example\n\
\n\
Note that multiple values are returned in a string matrix with the fill\n\
character set to ASCII NUL.\n\
@end deftypefn")
{
  octave_value retval;

  if (args.length () == 1)
    {
      string_vector pat = args(0).all_strings ();

      if (error_state)
	gripe_wrong_type_arg ("glob", args(0));
      else
	{
	  glob_match pattern (file_ops::tilde_expand (pat));

	  string_vector list = pattern.glob ();

	  if (list.empty ())
	    retval = "";
	  else
	    retval = list;
	}
    }
  else
    print_usage ("glob");

  return retval;
}

DEFUN (fnmatch, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} fnmatch (@var{pattern}, @var{string})\n\
Return 1 or zero for each element of @var{string} that matches any of\n\
the elements of the string array @var{pattern}, using the rules of\n\
filename pattern matching.  For example,\n\
\n\
@example\n\
@group\n\
fnmatch (\"a*b\", [\"ab\"; \"axyzb\"; \"xyzab\"])\n\
     @result{} [ 1; 1; 0 ]\n\
@end group\n\
@end example\n\
@end deftypefn")
{
  octave_value retval;

  if (args.length () == 2)
    {
      string_vector pat = args(0).all_strings ();
      string_vector str = args(1).all_strings ();

      if (error_state)
	gripe_wrong_type_arg ("fnmatch", args(0));
      else
	{
	  glob_match pattern (file_ops::tilde_expand (pat));

	  Array<bool> tmp = pattern.match (str);

	  int n = tmp.length ();

	  ColumnVector result (n);

	  for (int i = 0; i < n; i++)
	    result(i) = tmp(i);

	  retval = result;
	}
    }
  else
    print_usage ("fnmatch");

  return retval;
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
