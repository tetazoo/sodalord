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

/*

The functions listed below were adapted from similar functions from
GNU Bash, the Bourne Again SHell, copyright (C) 1987, 1989, 1991 Free
Software Foundation, Inc.

  do_history         edit_history_readline
  do_edit_history    edit_history_add_hist

*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <cstdlib>
#include <cstring>

#include <string>

#include <fstream>

#ifdef HAVE_UNISTD_H
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#include <unistd.h>
#endif

#include "cmd-hist.h"
#include "file-ops.h"
#include "lo-mappers.h"
#include "oct-env.h"
#include "str-vec.h"

#include <defaults.h>
#include "defun.h"
#include "error.h"
#include "gripes.h"
#include "input.h"
#include "oct-hist.h"
#include "oct-obj.h"
#include "pager.h"
#include "parse.h"
#include "sighandlers.h"
#include "sysdep.h"
#include "toplev.h"
#include "unwind-prot.h"
#include "utils.h"
#include "variables.h"

// TRUE means input is coming from temporary history file.
bool input_from_tmp_history_file = false;

// Where history is saved.
static std::string Vhistory_file;

// The number of lines to keep in the history file.
static int Vhistory_size;

// TRUE if we are saving history.
bool Vsaving_history = true;

// Get some default values, possibly reading them from the
// environment.

int
default_history_size (void)
{
  int size = 1024;

  std::string env_size = octave_env::getenv ("OCTAVE_HISTSIZE");

  if (! env_size.empty ())
    {
      int val;

      if (sscanf (env_size.c_str (), "%d", &val) == 1)
	size = val > 0 ? val : 0;
    }

  return size;
}

std::string
default_history_file (void)
{
  std::string file;

  std::string env_file = octave_env::getenv ("OCTAVE_HISTFILE");

  if (! env_file.empty ())
    {
      std::fstream f (env_file.c_str (), (std::ios::in | std::ios::out));

      if (f)
	{
	  file = env_file;
	  f.close ();
	}
    }

  if (file.empty ())
    {
      std::string home_dir = octave_env::get_home_directory ();

      if (! home_dir.empty ())
	{
	  file = home_dir;
	  file.append ("/.octave_hist");
	}
      else
	file = ".octave_hist";
    }

  return file;
}

// Display, save, or load history.  Stolen and modified from bash.
//
// Arg of -w FILENAME means write file, arg of -r FILENAME
// means read file, arg of -q means don't number lines.  Arg of N
// means only display that many items. 

static void
do_history (int argc, const string_vector& argv)
{
  int numbered_output = 1;

  int i;
  for (i = 1; i < argc; i++)
    {
      std::string option = argv[i];

      if (option == "-r" || option == "-w" || option == "-a"
	  || option == "-n")
	{
	  if (i < argc - 1)
	    {
	      std::string file = file_ops::tilde_expand (argv[i+1]);
	      command_history::set_file (file);
	    }

	  if (option == "-a")
	    // Append `new' lines to file.
	    command_history::append ();

	  else if (option == "-w")
	    // Write entire history.
	    command_history::write ();

	  else if (option == "-r")
	    // Read entire file.
	    command_history::read ();

	  else if (option == "-n")
	    // Read `new' history from file.
	    command_history::read_range ();

	  else
	    panic_impossible ();

	  return;
	}
      else if (argv[i] == "-q")
	numbered_output = 0;
      else if (argv[i] == "--")
	{
	  i++;
	  break;
	}
      else
	break;
    }

  int limit = -1;

  if (i < argc)
    {
      if (sscanf (argv[i].c_str (), "%d", &limit) != 1)
        {
	  if (argv[i][0] == '-')
	    error ("history: unrecognized option `%s'", argv[i].c_str ());
	  else
	    error ("history: bad non-numeric arg `%s'", argv[i].c_str ());

	  return;
        }

      if (limit < 0)
	limit = -limit;
    }

  string_vector hlist = command_history::list (limit, numbered_output);

  int len = hlist.length ();

  for (i = 0; i < len; i++)
    octave_stdout << hlist[i] << "\n";
}

// Read the edited history lines from STREAM and return them
// one at a time.  This can read unlimited length lines.  The
// caller should free the storage.

static char *
edit_history_readline (std::fstream& stream)
{
  char c;
  int line_len = 128;
  int lindex = 0;
  char *line = new char [line_len];
  line[0] = '\0';

  while (stream.get (c))
    {
      if (lindex + 2 >= line_len)
	{
	  char *tmp_line = new char [line_len += 128];
	  strcpy (tmp_line, line);
	  delete [] line;
	  line = tmp_line;
	}

      if (c == '\n')
	{
	  line[lindex++] = '\n';
	  line[lindex++] = '\0';
	  return line;
	}
      else
	line[lindex++] = c;
    }

  if (! lindex)
    {
      delete [] line;
      return 0;
    }

  if (lindex + 2 >= line_len)
    {
      char *tmp_line = new char [lindex+3];
      strcpy (tmp_line, line);
      delete [] line;
      line = tmp_line;
    }

  // Finish with newline if none in file.

  line[lindex++] = '\n';
  line[lindex++] = '\0';
  return line;
}

// Use `command' to replace the last entry in the history list, which,
// by this time, is `run_history blah...'.  The intent is that the
// new command becomes the history entry, and that `fc' should never
// appear in the history list.  This way you can do `run_history' to
// your heart's content.

static void
edit_history_repl_hist (const std::string& command)
{
  if (! command.empty ())
    {
      string_vector hlist = command_history::list ();

      int len = hlist.length ();

      if (len > 0)
	{
	  int i = len - 1;

	  std::string histent = command_history::get_entry (i);

	  if (! histent.empty ())
	    {
	      std::string cmd = command;

	      int cmd_len = cmd.length ();

	      if (cmd[cmd_len - 1] == '\n')
		cmd.resize (cmd_len - 1);

	      if (! cmd.empty ())
		command_history::replace_entry (i, cmd);
	    }
	}
    }
}

static void
edit_history_add_hist (const std::string& line)
{
  if (! line.empty ())
    {
      std::string tmp = line;

      int len = tmp.length ();
	
      if (len > 0 && tmp[len-1] == '\n')
	tmp.resize (len - 1);

      if (! tmp.empty ())
	command_history::add (tmp);
    }
}

static std::string
mk_tmp_hist_file (int argc, const string_vector& argv,
		  int insert_curr, const char *warn_for) 
{
  std::string retval;

  string_vector hlist = command_history::list ();

  int hist_count = hlist.length ();

  // The current command line is already part of the history list by
  // the time we get to this point.  Delete it from the list.

  hist_count -= 2;

  if (! insert_curr)
    command_history::remove (hist_count);

  hist_count--;

  // If no numbers have been specified, the default is to edit the
  // last command in the history list.

  int hist_end = hist_count;
  int hist_beg = hist_count;
  int reverse = 0;

  // Process options.

  int usage_error = 0;
  if (argc == 3)
    {
      if (sscanf (argv[1].c_str (), "%d", &hist_beg) != 1
	  || sscanf (argv[2].c_str (), "%d", &hist_end) != 1)
	usage_error = 1;
      else
	{
	  hist_beg--;
	  hist_end--;
	}
    }
  else if (argc == 2)
    {
      if (sscanf (argv[1].c_str (), "%d", &hist_beg) != 1)
	usage_error = 1;
      else
	{
	  hist_beg--;
	  hist_end = hist_beg;
	}
    }

  if (hist_beg < 0 || hist_end < 0 || hist_beg > hist_count
      || hist_end > hist_count)
    {
      error ("%s: history specification out of range", warn_for);
      return retval;
    }

  if (usage_error)
    {
      usage ("%s [first] [last]", warn_for);
      return retval;
    }

  if (hist_end < hist_beg)
    {
      int t = hist_end;
      hist_end = hist_beg;
      hist_beg = t;
      reverse = 1;
    }

  std::string name = file_ops::tempnam ("", "oct-");

  std::fstream file (name.c_str (), std::ios::out);

  if (! file)
    {
      error ("%s: couldn't open temporary file `%s'", warn_for,
	     name.c_str ());
      return retval;
    }

  if (reverse)
    {
      for (int i = hist_end; i >= hist_beg; i--)
	file << hlist[i] << "\n";
    }
  else
    {
      for (int i = hist_beg; i <= hist_end; i++)
	file << hlist[i] << "\n";
    }

  file.close ();

  return name;
}

static void
do_edit_history (int argc, const string_vector& argv)
{
  std::string name = mk_tmp_hist_file (argc, argv, 0, "edit_history");

  if (name.empty ())
    return;

  // Call up our favorite editor on the file of commands.

  std::string cmd = Veditor;
  cmd.append (" \"");
  cmd.append (name);
  cmd.append ("\"");

  // Ignore interrupts while we are off editing commands.  Should we
  // maybe avoid using system()?

  volatile octave_interrupt_handler old_interrupt_handler
    = octave_ignore_interrupts ();

  system (cmd.c_str ());

  octave_set_interrupt_handler (old_interrupt_handler);

  // Write the commands to the history file since parse_and_execute
  // disables command line history while it executes.

  std::fstream file (name.c_str (), std::ios::in);

  char *line;
  int first = 1;
  while ((line = edit_history_readline (file)) != 0)
    {
      // Skip blank lines.

      if (line[0] == '\n')
	{
	  delete [] line;
	  continue;
	}

      if (first)
	{
	  first = 0;
	  edit_history_repl_hist (line);
	}
      else
	edit_history_add_hist (line);
    }

  file.close ();

  // Turn on command echo, so the output from this will make better
  // sense.

  unwind_protect::begin_frame ("do_edit_history");

  unwind_protect_int (Vecho_executing_commands);
  unwind_protect_bool (input_from_tmp_history_file);

  Vecho_executing_commands = ECHO_CMD_LINE;
  input_from_tmp_history_file = true;

  parse_and_execute (name);

  unwind_protect::run_frame ("do_edit_history");

  // Delete the temporary file.  Should probably be done with an
  // unwind_protect.

  unlink (name.c_str ());
}

static void
do_run_history (int argc, const string_vector& argv)
{
  std::string name = mk_tmp_hist_file (argc, argv, 1, "run_history");

  if (name.empty ())
    return;

  // Turn on command echo so the output from this will make better
  // sense.

  unwind_protect::begin_frame ("do_run_history");

  unwind_protect_int (Vecho_executing_commands);
  unwind_protect_bool (input_from_tmp_history_file);

  Vecho_executing_commands = ECHO_CMD_LINE;
  input_from_tmp_history_file = true;

  parse_and_execute (name);

  unwind_protect::run_frame ("do_run_history");

  // Delete the temporary file.

  // XXX FIXME XXX -- should probably be done using an unwind_protect.

  unlink (name.c_str ());
}

DEFCMD (edit_history, args, ,
  "-*- texinfo -*-\n\
@deffn {Command} edit_history options\n\
If invoked with no arguments, @code{edit_history} allows you to edit the\n\
history list using the editor named by the variable @code{EDITOR}.  The\n\
commands to be edited are first copied to a temporary file.  When you\n\
exit the editor, Octave executes the commands that remain in the file.\n\
It is often more convenient to use @code{edit_history} to define functions \n\
rather than attempting to enter them directly on the command line.\n\
By default, the block of commands is executed as soon as you exit the\n\
editor.  To avoid executing any commands, simply delete all the lines\n\
from the buffer before exiting the editor.\n\
\n\
The @code{edit_history} command takes two optional arguments specifying\n\
the history numbers of first and last commands to edit.  For example,\n\
the command\n\
\n\
@example\n\
edit_history 13\n\
@end example\n\
\n\
@noindent\n\
extracts all the commands from the 13th through the last in the history\n\
list.  The command\n\
\n\
@example\n\
edit_history 13 169\n\
@end example\n\
\n\
@noindent\n\
only extracts commands 13 through 169.  Specifying a larger number for\n\
the first command than the last command reverses the list of commands\n\
before placing them in the buffer to be edited.  If both arguments are\n\
omitted, the previous command in the history list is used.\n\
@end deffn")
{
  octave_value_list retval;

  int argc = args.length () + 1;

  string_vector argv = args.make_argv ("edit_history");

  if (error_state)
    return retval;

  do_edit_history (argc, argv);

  return retval;
}

DEFCMD (history, args, ,
  "-*- texinfo -*-\n\
@deffn {Command} history options\n\
If invoked with no arguments, @code{history} displays a list of commands\n\
that you have executed.  Valid options are:\n\
\n\
@table @code\n\
@item -w @var{file}\n\
Write the current history to the file @var{file}.  If the name is\n\
omitted, use the default history file (normally @file{~/.octave_hist}).\n\
\n\
@item -r @var{file}\n\
Read the file @var{file}, replacing the current history list with its\n\
contents.  If the name is omitted, use the default history file\n\
(normally @file{~/.octave_hist}).\n\
\n\
@item @var{n}\n\
Only display the most recent @var{n} lines of history.\n\
\n\
@item -q\n\
Don't number the displayed lines of history.  This is useful for cutting\n\
and pasting commands if you are using the X Window System.\n\
@end table\n\
\n\
For example, to display the five most recent commands that you have\n\
typed without displaying line numbers, use the command\n\
@kbd{history -q 5}.\n\
@end deffn")
{
  octave_value_list retval;

  int argc = args.length () + 1;

  string_vector argv = args.make_argv ("history");

  if (error_state)
    return retval;

  do_history (argc, argv);

  return retval;
}

DEFCMD (run_history, args, ,
  "-*- texinfo -*-\n\
@deffn {Command} run_history [first] [last]\n\
Similar to @code{edit_history}, except that the editor is not invoked,\n\
and the commands are simply executed as they appear in the history list.\n\
@end deffn")
{
  octave_value_list retval;

  int argc = args.length () + 1;

  string_vector argv = args.make_argv ("run_history");

  if (error_state)
    return retval;

  do_run_history (argc, argv);

  return retval;
}

static int
history_size (void)
{
  double val;
  if (builtin_real_scalar_variable ("history_size", val)
      && ! xisnan (val))
    {
      int ival = NINT (val);
      if (ival >= 0 && ival == val)
	{
	  Vhistory_size = ival;
	  command_history::set_size (ival);
	  return 0;
	}
    }
  gripe_invalid_value_specified ("history_size");
  return -1;
}

static int
history_file (void)
{
  int status = 0;

  std::string s = builtin_string_variable ("history_file");

  if (s.empty ())
    {
      gripe_invalid_value_specified ("history_file");
      status = -1;
    }
  else
    {
      Vhistory_file = s;
      command_history::set_file (file_ops::tilde_expand (s));
    }

  return status;
}

static int
saving_history (void)
{
  Vsaving_history = check_preference ("saving_history");

  command_history::ignore_entries (! Vsaving_history);

  return 0;
}

void
symbols_of_oct_hist (void)
{
  DEFVAR (history_file, default_history_file (), history_file,
    "-*- texinfo -*-\n\
@defvr {Built-in Variable} history_file\n\
This variable specifies the name of the file used to store command\n\
history.  The default value is @code{\"~/.octave_hist\"}, but may be\n\
overridden by the environment variable @code{OCTAVE_HISTFILE}.\n\
@end defvr");

  double tmp_hist_size = default_history_size ();

  DEFVAR (history_size, tmp_hist_size, history_size,
    "-*- texinfo -*-\n\
@defvr {Built-in Variable} history_size\n\
This variable specifies how many entries to store in the history file.\n\
The default value is @code{1024}, but may be overridden by the\n\
environment variable @code{OCTAVE_HISTSIZE}.\n\
@end defvr");

  DEFVAR (saving_history, true, saving_history,
    "-*- texinfo -*-\n\
@defvr {Built-in Variable} saving_history\n\
If the value of @code{saving_history} is nonzero, command entered\n\
on the command line are saved in the file specified by the variable\n\
@code{history_file}.\n\
@end defvr");
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
