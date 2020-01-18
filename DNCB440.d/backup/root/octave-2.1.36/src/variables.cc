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

#include <cstdio>
#include <cstring>

#include <string>

#include "file-stat.h"
#include "oct-env.h"
#include "glob-match.h"
#include "str-vec.h"

#include <defaults.h>
#include "defun.h"
#include "dirfns.h"
#include "error.h"
#include "gripes.h"
#include "help.h"
#include "input.h"
#include "lex.h"
#include "oct-map.h"
#include "oct-obj.h"
#include "ov.h"
#include "pager.h"
#include "parse.h"
#include "symtab.h"
#include "toplev.h"
#include "unwind-prot.h"
#include "utils.h"
#include "variables.h"

// Should Octave always check to see if function files have changed
// since they were last compiled?
static int Vignore_function_time_stamp;

// Symbol table for symbols at the top level.
symbol_table *top_level_sym_tab = 0;

// Symbol table for the current scope.
symbol_table *curr_sym_tab = 0;

// Symbol table for global symbols.
symbol_table *global_sym_tab = 0;

// Initialization.

// Create the initial symbol tables and set the current scope at the
// top level.

void
initialize_symbol_tables (void)
{
  if (! global_sym_tab)
    global_sym_tab = new symbol_table (2048);

  if (! top_level_sym_tab)
    top_level_sym_tab = new symbol_table (4096);

  curr_sym_tab = top_level_sym_tab;
}

// Attributes of variables and functions.

// Is this variable a builtin?

bool
is_builtin_variable (const std::string& name)
{
  symbol_record *sr = global_sym_tab->lookup (name);
  return (sr && sr->is_builtin_variable ());
}

// Is this a text-style function?

bool
is_text_function_name (const std::string& s)
{
  symbol_record *sr = global_sym_tab->lookup (s);
  return (sr && sr->is_text_function ());
}

// Is this a built-in function?

bool
is_builtin_function_name (const std::string& s)
{
  symbol_record *sr = global_sym_tab->lookup (s);
  return (sr && sr->is_builtin_function ());
}

// Is this a mapper function?

bool
is_mapper_function_name (const std::string& s)
{
  symbol_record *sr = global_sym_tab->lookup (s);
  return (sr && sr->is_mapper_function ());
}

// Is this function globally in this scope?

bool
is_globally_visible (const std::string& name)
{
  symbol_record *sr = curr_sym_tab->lookup (name);
  return (sr && sr->is_linked_to_global ());
}

// Is this octave_value a valid function?

octave_function *
is_valid_function (const std::string& fcn_name, const std::string& warn_for, bool warn)
{
  octave_function *ans = 0;

  symbol_record *sr = 0;

  if (! fcn_name.empty ())
    {
      sr = global_sym_tab->lookup (fcn_name, true);

      lookup (sr, false);
    }

  if (sr)
    {
      octave_value tmp = sr->def ();
      ans = tmp.function_value (true);
    }

  if (! sr || ! ans || ! sr->is_function ())
    {
      if (warn)
	error ("%s: the symbol `%s' is not valid as a function",
	       warn_for.c_str (), fcn_name.c_str ());
      ans = 0;
    }

  return ans;
}

octave_function *
is_valid_function (const octave_value& arg, const std::string& warn_for, bool warn)
{
  octave_function *ans = 0;

  std::string fcn_name;

  if (arg.is_string ())
    fcn_name = arg.string_value ();

  if (! error_state)
    ans = is_valid_function (fcn_name, warn_for, warn);
  else if (warn)
    error ("%s: expecting function name as argument", warn_for.c_str ());

  return ans;
}

octave_function *
extract_function (const octave_value& arg, const std::string& warn_for,
		  const std::string& fname, const std::string& header,
		  const std::string& trailer)
{
  octave_function *retval = 0;

  retval = is_valid_function (arg, warn_for, 0);

  if (! retval)
    {
      std::string s = arg.string_value ();

      std::string cmd = header;
      cmd.append (s);
      cmd.append (trailer);

      if (! error_state)
	{
	  int parse_status;

	  eval_string (cmd, true, parse_status);

	  if (parse_status == 0)
	    {
	      retval = is_valid_function (fname, warn_for, 0);
      
	      if (! retval)
		{
		  error ("%s: `%s' is not valid as a function",
			 warn_for.c_str (), fname.c_str ());
		  return retval;
		}
	    }
	  else
	    error ("%s: `%s' is not valid as a function",
		   warn_for.c_str (), fname.c_str ());
	}
      else
	error ("%s: expecting first argument to be a string",
	       warn_for.c_str ());
    }

  return retval;
}

string_vector
get_struct_elts (const std::string& text)
{
  int n = 1;

  size_t pos = 0;

  size_t len = text.length ();

  while ((pos = text.find ('.', pos)) != NPOS)
    {
      if (++pos == len)
	break;

      n++;
    }

  string_vector retval (n);

  pos = 0;

  for (int i = 0; i < n; i++)
    {
      size_t len = text.find ('.', pos);

      if (len != NPOS)
	len -= pos;

      retval[i] = text.substr (pos, len);

      if (len != NPOS)
	pos += len + 1;
    }

  return retval;
}

string_vector
generate_struct_completions (const std::string& text, std::string& prefix, std::string& hint)
{
  string_vector names;

  size_t pos = text.rfind ('.');

  std::string id;
  string_vector elts;

  if (pos == NPOS)
    {
      hint = text;
      prefix = text;
      elts.resize (1, text);
    }
  else
    {
      if (pos == text.length ())
	hint = "";
      else
	hint = text.substr (pos+1);

      prefix = text.substr (0, pos);

      elts = get_struct_elts (prefix);
    }

  id = elts[0];

  symbol_record *sr = curr_sym_tab->lookup (id);

  if (! sr)
    sr = global_sym_tab->lookup (id);

  if (sr && sr->is_defined ())
    {
      octave_value tmp = sr->def ();

      // XXX FIXME XXX -- make this work for all types that can do
      // structure reference operations.
      if (tmp.is_map ())
	{
	  for (int i = 1; i < elts.length (); i++)
	    {
	      tmp = tmp.do_struct_elt_index_op (elts[i], true);

	      if (! tmp.is_map ())
		break;
	    }

	  if (tmp.is_map ())
	    {
	      Octave_map m = tmp.map_value ();

	      names = m.make_name_list ();
	    }
	}
    }

  return names;
}

bool
looks_like_struct (const std::string& text)
{
  bool retval = true;

  string_vector elts = get_struct_elts (text);

  std::string id = elts[0];

  symbol_record *sr = curr_sym_tab->lookup (id);

  if (! sr)
    sr = global_sym_tab->lookup (id);

  if (sr && sr->is_defined ())
    {
      octave_value tmp = sr->def ();

      // XXX FIXME XXX -- should this work for all types that can do
      // structure reference operations?

      if (tmp.is_map ())
	{
	  for (int i = 1; i < elts.length (); i++)
	    {
	      tmp = tmp.do_struct_elt_index_op (elts[i], true);

	      if (! tmp.is_map ())
		{
		  retval = false;
		  break;
		}
	    }
	}
      else
	retval = false;
    }
  else
    retval = false;

  return retval;	
}

DEFUN (is_global, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} is_global (@var{name})\n\
Return 1 if @var{name} is globally visible.  Otherwise, return 0.  For\n\
example,\n\
\n\
@example\n\
@group\n\
global x\n\
is_global (\"x\")\n\
     @result{} 1\n\
@end group\n\
@end example\n\
@end deftypefn")
{
  octave_value_list retval = 0.0;

  int nargin = args.length ();

  if (nargin != 1)
    {
      print_usage ("is_global");
      return retval;
    }

  std::string name = args(0).string_value ();

  if (error_state)
    {
      error ("is_global: expecting std::string argument");
      return retval;
    }

  symbol_record *sr = curr_sym_tab->lookup (name);

  retval = static_cast<double> (sr && sr->is_linked_to_global ());

  return retval;
}

DEFUN (exist, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} exist (@var{name})\n\
Return 1 if the name exists as a variable, 2 if the name (after\n\
appending @samp{.m}) is a function file in the path, 3 if the name is a\n\
@samp{.oct} file in the path, 5 if the name is a built-in function, or\n\
6 is the name is a built-in constant.  Otherwise, return 0.\n\
\n\
This function also returns 2 if a regular file called @var{name}\n\
exists in Octave's @code{LOADPATH}.  If you want information about\n\
other types of files, you should use some combination of the functions\n\
@code{file_in_path} and @code{stat} instead.\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin != 1)
    {
      print_usage ("exist");
      return retval;
    }

  std::string name = args(0).string_value ();

  if (error_state)
    {
      error ("exist: expecting std::string argument");
      return retval;
    }

  std::string struct_elts;
  std::string symbol_name = name;

  size_t pos = name.find ('.');

  if (pos != NPOS && pos > 0)
    {
      struct_elts = name.substr (pos+1);
      symbol_name = name.substr (0, pos);
    }

  symbol_record *sr = curr_sym_tab->lookup (symbol_name);
  if (! (sr && (sr->is_defined ()
		|| (curr_sym_tab != top_level_sym_tab))))
    sr = global_sym_tab->lookup (symbol_name);

  retval = 0.0;

  if (sr && sr->is_variable () && sr->is_defined ())
    {
      if (struct_elts.empty () || sr->is_map_element (struct_elts))
	retval = 1.0;
    }
  else if (sr && sr->is_builtin_function ())
    {
      retval = 5.0;
    }
  else if (sr && sr->is_builtin_constant ())
    {
      retval = 6.0;
    }
  else if (sr && sr->is_user_function ())
    {
      retval = 2.0;
    }
  else
    {
      std::string path = fcn_file_in_path (name);

      if (path.length () > 0)
	{
	  retval = 2.0;
	}
      else
	{
	  path = oct_file_in_path (name);

	  if (path.length () > 0)
	    {
	      retval = 3.0;
	    }
	  else
	    {
	      std::string file_name = file_in_path (name, "");

	      if (! file_name.empty ())
		{
		  file_stat fs (file_name);

		  if (fs && fs.is_reg ())
		    retval = 2.0;
		}
	    }
	}
    }

  return retval;
}

// Is there a corresponding function file that is newer than the
// symbol definition?

static bool
symbol_out_of_date (symbol_record *sr)
{
  bool retval = false;

  if (Vignore_function_time_stamp != 2 && sr)
    {
      octave_value ans = sr->def ();

      octave_function *tmp = ans.function_value (true);

      if (tmp)
	{
	  std::string ff = tmp->fcn_file_name ();

	  if (! (ff.empty ()
		 || (Vignore_function_time_stamp
		     && tmp->is_system_fcn_file ())))
	    {
	      if (tmp->time_checked () < Vlast_prompt_time)
		{
		  time_t tp = tmp->time_parsed ();

		  std::string fname;

		  if (tmp->is_dld_function ())
		    fname = ff;
		  else
		    fname = fcn_file_in_path (ff);

		  tmp->mark_fcn_file_up_to_date (octave_time ());

		  file_stat fs (fname);

		  if (fs && fs.is_newer (tp))
		    retval = true;
		}
	    }
	}
    }

  return retval;
}

bool
lookup (symbol_record *sym_rec, bool exec_script)
{
  bool script_executed = false;

  if (! sym_rec->is_linked_to_global ())
    {
      if (sym_rec->is_defined ())
	{
	  if (sym_rec->is_function () && symbol_out_of_date (sym_rec))
	    script_executed = load_fcn_from_file (sym_rec, exec_script);
	}
      else if (! sym_rec->is_formal_parameter ())
	{
	  link_to_builtin_or_function (sym_rec);

	  if (! sym_rec->is_defined ())
	    script_executed = load_fcn_from_file (sym_rec, exec_script);
	  else if (sym_rec->is_function () && symbol_out_of_date (sym_rec))
	    script_executed = load_fcn_from_file (sym_rec, exec_script);
	}
    }

  return script_executed;
}

// Get the symbol record for the given name that is visible in the
// current scope.  Reread any function definitions that appear to be
// out of date.  If a function is available in a file but is not
// currently loaded, this will load it and insert the name in the
// current symbol table.

symbol_record *
lookup_by_name (const std::string& nm, bool exec_script)
{
  symbol_record *sym_rec = curr_sym_tab->lookup (nm, true);

  lookup (sym_rec, exec_script);

  return sym_rec;
}

octave_value
get_global_value (const std::string& nm)
{
  octave_value retval;

  symbol_record *sr = global_sym_tab->lookup (nm);

  if (sr)
    {
      octave_value sr_def = sr->def ();

      if (sr_def.is_undefined ())
	error ("get_global_by_name: undefined symbol `%s'", nm.c_str ());
      else
	retval = sr_def;
    }
  else
    error ("get_global_by_name: unknown symbol `%s'", nm.c_str ());

  return retval;
}

void
set_global_value (const std::string& nm, const octave_value& val)
{
  symbol_record *sr = global_sym_tab->lookup (nm, true);

  if (sr)
    sr->define (val);
  else
    panic_impossible ();
}

// Variable values.

// Look for the given name in the global symbol table.  If it refers
// to a string, return a new copy.  If not, return 0;

std::string
builtin_string_variable (const std::string& name)
{
  symbol_record *sr = global_sym_tab->lookup (name);

  // It is a prorgramming error to look for builtins that aren't.

  assert (sr);

  std::string retval;

  octave_value val = sr->def ();

  if (! error_state && val.is_string ())
    retval = val.string_value ();

  return retval;
}

// Look for the given name in the global symbol table.  If it refers
// to a real scalar, place the value in d and return 1.  Otherwise,
// return 0.

int
builtin_real_scalar_variable (const std::string& name, double& d)
{
  int status = 0;
  symbol_record *sr = global_sym_tab->lookup (name);

  // It is a prorgramming error to look for builtins that aren't.

  assert (sr);

  octave_value val = sr->def ();

  if (! error_state && val.is_scalar_type ())
    {
      d = val.double_value ();
      status = 1;
    }

  return status;
}

// Look for the given name in the global symbol table.

octave_value
builtin_any_variable (const std::string& name)
{
  symbol_record *sr = global_sym_tab->lookup (name);

  // It is a prorgramming error to look for builtins that aren't.

  assert (sr);

  return sr->def ();
}

// Global stuff and links to builtin variables and functions.

// Make the definition of the symbol record sr be the same as the
// definition of the global variable of the same name, creating it if
// it doesn't already exist.

void
link_to_global_variable (symbol_record *sr)
{
  if (! sr->is_linked_to_global ())
    {
      sr->mark_as_linked_to_global ();

      if (! error_state)
	{
	  std::string nm = sr->name ();

	  symbol_record *gsr = global_sym_tab->lookup (nm, true);

	  // There must be a better way to do this.   XXX FIXME XXX

	  if (sr->is_variable ())
	    gsr->define (sr->def ());

	  // Make sure this symbol is a variable.

	  if (! gsr->is_variable ())
	    gsr->define (octave_value ());

	  sr->alias (gsr, 1);
	}
    }
}

// Make the definition of the symbol record sr be the same as the
// definition of the builtin variable of the same name.

// Make the definition of the symbol record sr be the same as the
// definition of the builtin variable, constant, or function, or user
// function of the same name, provided that the name has not been used
// as a formal parameter.

void
link_to_builtin_or_function (symbol_record *sr)
{
  symbol_record *tmp_sym = global_sym_tab->lookup (sr->name ());

  if (tmp_sym
      && (tmp_sym->is_builtin_variable ()
	  || tmp_sym->is_builtin_constant ()
	  || tmp_sym->is_function ())
      && ! tmp_sym->is_formal_parameter ())
    sr->alias (tmp_sym);
}

// Force a link to a function in the current symbol table.  This is
// used just after defining a function to avoid different behavior
// depending on whether or not the function has been evaluated after
// being defined.
//
// Return without doing anything if there isn't a function with the
// given name defined in the global symbol table.

void
force_link_to_function (const std::string& id_name)
{
  symbol_record *gsr = global_sym_tab->lookup (id_name, true);
  if (gsr->is_function ())
    {
      curr_sym_tab->clear (id_name);
      symbol_record *csr = curr_sym_tab->lookup (id_name, true);
      csr->alias (gsr);
    }
}

DEFUN (document, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} document (@var{symbol}, @var{text})\n\
Set the documentation string for @var{symbol} to @var{text}.\n\
@end deftypefn")
{
  octave_value retval;

  int nargin = args.length ();

  if (nargin == 2)
    {
      std::string name = args(0).string_value ();

      if (! error_state)
	{
	  std::string help = args(1).string_value ();

	  if (! error_state)
	    {
	      if (is_builtin_variable (name)
		  || is_text_function_name (name)
		  || is_mapper_function_name (name)
		  || is_builtin_function_name (name))
		error ("document: can't redefine help for built-in variables and functions");
	      else
		{
		  symbol_record *sym_rec = curr_sym_tab->lookup (name);

		  if (sym_rec)
		    sym_rec->document (help);
		  else
		    error ("document: no such symbol `%s'", name.c_str ());
		}
	    }
	}
    }
  else
    print_usage ("document");

  return retval;
}

static octave_value_list
do_who (int argc, const string_vector& argv)
{
  octave_value_list retval;

  bool show_builtins = false;
  bool show_functions = false;
  bool show_variables = false;
  bool show_verbose = false;

  std::string my_name = argv[0];

  int i;
  for (i = 1; i < argc; i++)
    {
      if (argv[i] == "-all" || argv[i] == "-a")
	{
	  show_builtins = true;
	  show_functions = true;
	  show_variables = true;
	}
      else if (argv[i] == "-builtins" || argv[i] == "-b")
	show_builtins = true;
      else if (argv[i] == "-functions" || argv[i] == "-f")
	show_functions = true;
      else if (argv[i] == "-long" || argv[i] == "-l")
	show_verbose = true;
      else if (argv[i] == "-variables" || argv[i] == "-v")
	show_variables = true;
      else if (argv[i][0] == '-')
	warning ("%s: unrecognized option `%s'", my_name.c_str (),
		 argv[i].c_str ());
      else
	break;
    }

  // If no options were specified to select the type of symbol to
  // display, then set defaults.

  if (! (show_builtins || show_functions || show_variables))
    {
      show_functions = (curr_sym_tab == top_level_sym_tab);
      show_variables = true;
    }

  int npats = argc - i;
  string_vector pats (npats);
  for (int j = 0; j < npats; j++)
    pats[j] = argv[i+j];

  // If the user specified -l and nothing else, show variables.  If
  // evaluating this at the top level, also show functions.

  if (show_verbose && ! (show_builtins || show_functions || show_variables))
    {
      show_functions = (curr_sym_tab == top_level_sym_tab);
      show_variables = 1;
    }

  int pad_after = 0;

  if (show_builtins)
    {
      pad_after += global_sym_tab->maybe_list
	("*** built-in constants:", pats, octave_stdout,
	 show_verbose, symbol_record::BUILTIN_CONSTANT, SYMTAB_ALL_SCOPES);

      pad_after += global_sym_tab->maybe_list
	("*** built-in variables:", pats, octave_stdout,
	 show_verbose, symbol_record::BUILTIN_VARIABLE, SYMTAB_ALL_SCOPES);

      pad_after += global_sym_tab->maybe_list
	("*** built-in functions:", pats, octave_stdout,
	 show_verbose, symbol_record::BUILTIN_FUNCTION, SYMTAB_ALL_SCOPES);
    }

  if (show_functions)
    {
      pad_after += global_sym_tab->maybe_list
	("*** currently compiled functions:", pats,
	 octave_stdout, show_verbose, symbol_record::USER_FUNCTION,
	 SYMTAB_ALL_SCOPES);
    }

  if (show_variables)
    {
      pad_after += curr_sym_tab->maybe_list
	("*** local user variables:", pats, octave_stdout,
	 show_verbose, symbol_record::USER_VARIABLE, SYMTAB_LOCAL_SCOPE);

      pad_after += curr_sym_tab->maybe_list
	("*** globally visible user variables:", pats,
	 octave_stdout, show_verbose, symbol_record::USER_VARIABLE,
	 SYMTAB_GLOBAL_SCOPE);
    }

  if (pad_after)
    octave_stdout << "\n";

  return retval;
}

DEFUN_TEXT (who, args, ,
  "-*- texinfo -*-\n\
@deffn {Command} who options pattern @dots{}\n\
@deffnx {Command} whos options pattern @dots{}\n\
List currently defined symbols matching the given patterns.  The\n\
following are valid options.  They may be shortened to one character but\n\
may not be combined.\n\
\n\
@table @code\n\
@item -all\n\
List all currently defined symbols.\n\
\n\
@item -builtins\n\
List built-in variables and functions.  This includes all currently\n\
compiled function files, but does not include all function files that\n\
are in the @code{LOADPATH}.\n\
\n\
@item -functions\n\
List user-defined functions.\n\
\n\
@item -long\n\
Print a long listing including the type and dimensions of any symbols.\n\
The symbols in the first column of output indicate whether it is\n\
possible to redefine the symbol, and whether it is possible for it to be\n\
cleared.\n\
\n\
@item -variables\n\
List user-defined variables.\n\
@end table\n\
\n\
Valid patterns are the same as described for the @code{clear} command\n\
above.  If no patterns are supplied, all symbols from the given category\n\
are listed.  By default, only user defined functions and variables\n\
visible in the local scope are displayed.\n\
\n\
The command @kbd{whos} is equivalent to @kbd{who -long}.\n\
@end deffn")
{
  octave_value_list retval;

  int argc = args.length () + 1;

  string_vector argv = args.make_argv ("who");

  if (error_state)
    return retval;

  retval = do_who (argc, argv);

  return retval;
}

DEFUN_TEXT (whos, args, ,
  "-*- texinfo -*-\n\
@deffn {Command} whos options pattern @dots{}\n\
See who.\n\
@end deffn")
{
  octave_value_list retval;

  int nargin = args.length ();

  octave_value_list tmp_args;
  for (int i = nargin; i > 0; i--)
    tmp_args(i) = args(i-1);
  tmp_args(0) = "-long";

  int argc = tmp_args.length () + 1;

  string_vector argv = tmp_args.make_argv ("whos");

  if (error_state)
    return retval;

  retval = do_who (argc, argv);

  return retval;
}

// Defining variables.

void
bind_ans (const octave_value& val, bool print)
{
  static symbol_record *sr = global_sym_tab->lookup ("ans", true);

  if (val.is_defined ())
    {
      sr->define (val);

      if (print)
	val.print_with_name (octave_stdout, "ans");
    }
}

// Give a global constant a definition.  This will insert the symbol
// in the global table if necessary.

// How is this different than install_builtin_constant?  Are both
// functions needed?

void
bind_builtin_constant (const std::string& name, const octave_value& val,
		       bool protect, bool eternal, const std::string& help)
{
  symbol_record *sym_rec = global_sym_tab->lookup (name, true);
  sym_rec->unprotect ();

  std::string tmp_help = help.empty () ? sym_rec->help () : help;

  sym_rec->define_builtin_const (val);

  sym_rec->document (tmp_help);

  if (protect)
    sym_rec->protect ();

  if (eternal)
    sym_rec->make_eternal ();
}

// Give a global variable a definition.  This will insert the symbol
// in the global table if necessary.

// How is this different than install_builtin_variable?  Are both
// functions needed?

void
bind_builtin_variable (const std::string& varname, const octave_value& val,
		       bool protect, bool eternal,
		       symbol_record::change_function chg_fcn,
		       const std::string& help)
{
  symbol_record *sr = global_sym_tab->lookup (varname, true);

  // It is a programming error for a builtin symbol to be missing.
  // Besides, we just inserted it, so it must be there.

  assert (sr);

  sr->unprotect ();

  // Must do this before define, since define will call the special
  // variable function only if it knows about it, and it needs to, so
  // that user prefs can be properly initialized.

  if (chg_fcn)
    sr->set_change_function (chg_fcn);

  sr->define_builtin_var (val);

  if (protect)
    sr->protect ();

  if (eternal)
    sr->make_eternal ();

  sr->document (help);
}

// Deleting names from the symbol tables.

static inline bool
var_matches_any_pattern (const std::string& nm,
			 const string_vector& argv, int argc, int idx)
{
  bool retval = false;

  for (int k = idx; k < argc; k++)
    {
      std::string patstr = argv[k];

      if (! patstr.empty ())
	{
	  glob_match pattern (patstr);

	  if (pattern.match (nm))
	    {
	      retval = true;
	      break;
	    }
	}
    }

  return retval;
}

DEFUN_TEXT (clear, args, ,
  "-*- texinfo -*-\n\
@deffn {Command} clear [-x] pattern @dots{}\n\
Delete the names matching the given patterns from the symbol table.  The\n\
pattern may contain the following special characters:\n\
@table @code\n\
@item ?\n\
Match any single character.\n\
\n\
@item *\n\
Match zero or more characters.\n\
\n\
@item [ @var{list} ]\n\
Match the list of characters specified by @var{list}.  If the first\n\
character is @code{!} or @code{^}, match all characters except those\n\
specified by @var{list}.  For example, the pattern @samp{[a-zA-Z]} will\n\
match all lower and upper case alphabetic characters.\n\
@end table\n\
\n\
For example, the command\n\
\n\
@example\n\
clear foo b*r\n\
@end example\n\
\n\
@noindent\n\
clears the name @code{foo} and all names that begin with the letter\n\
@code{b} and end with the letter @code{r}.\n\
\n\
If @code{clear} is called without any arguments, all user-defined\n\
variables (local and global) are cleared from the symbol table.  If\n\
@code{clear} is called with at least one argument, only the visible\n\
names matching the arguments are cleared.  For example, suppose you have\n\
defined a function @code{foo}, and then hidden it by performing the\n\
assignment @code{foo = 2}.  Executing the command @kbd{clear foo} once\n\
will clear the variable definition and restore the definition of\n\
@code{foo} as a function.  Executing @kbd{clear foo} a second time will\n\
clear the function definition.\n\
\n\
With -x, clear the variables that don't match the patterns.\n\
\n\
This command may not be used within a function body.\n\
@end deffn")
{
  octave_value_list retval;

  int argc = args.length () + 1;

  string_vector argv = args.make_argv ("clear");

  if (error_state)
    return retval;

  // Always clear the local table, but don't clear currently compiled
  // functions unless we are at the top level.  (Allowing that to
  // happen inside functions would result in pretty odd behavior...)

  bool clear_user_functions = (curr_sym_tab == top_level_sym_tab);

  if (argc == 1)
    {
      curr_sym_tab->clear ();
      global_sym_tab->clear (clear_user_functions);
    }
  else
    {
      int exclusive = 0;

      int idx = 1;

      if (argc > 1)
	{
	  if (argv[idx] == "-x")
	    {
	      idx++;
	      exclusive = 1;
	    }
	}

      string_vector lvars;
      string_vector gvars;
      string_vector fcns;

      if (argc > 0)
	{
	  string_vector tmp;

	  lvars = curr_sym_tab->name_list
	    (tmp, false, SYMTAB_VARIABLES, SYMTAB_LOCAL_SCOPE);

	  gvars = curr_sym_tab->name_list
	    (tmp, false, SYMTAB_VARIABLES, SYMTAB_GLOBAL_SCOPE);

	  fcns = global_sym_tab->name_list
	    (tmp, false,
	     symbol_record::USER_FUNCTION|symbol_record::DLD_FUNCTION,
	     SYMTAB_ALL_SCOPES);
	}

      // XXX FIXME XXX -- this needs to be optimized to avoid the
      // pattern matching code if the string doesn't contain any
      // globbing patterns.

      if (exclusive)
	{
	  int lcount = lvars.length ();

	  for (int i = 0; i < lcount; i++)
	    {
	      std::string nm = lvars[i];

	      if (! var_matches_any_pattern (nm, argv, argc, idx))
		curr_sym_tab->clear (nm);
	    }

	  int gcount = gvars.length ();

	  for (int i = 0; i < gcount; i++)
	    {
	      std::string nm = gvars[i];

	      if (! var_matches_any_pattern (nm, argv, argc, idx))
		{
		  int count = curr_sym_tab->clear (nm);

		  if (count > 0)
		    global_sym_tab->clear (nm, clear_user_functions);
		}
	    }

	  int fcount = fcns.length ();

	  for (int i = 0; i < fcount; i++)
	    {
	      std::string nm = fcns[i];

	      if (! var_matches_any_pattern (nm, argv, argc, idx))
		{
		  curr_sym_tab->clear (nm);

		  global_sym_tab->clear (nm, clear_user_functions);
		}
	    }
	}
      else
	{
	  for (int k = idx; k < argc; k++)
	    {
	      std::string patstr = argv[k];

	      if (! patstr.empty ())
		{
		  glob_match pattern (patstr);

		  int lcount = lvars.length ();

		  for (int i = 0; i < lcount; i++)
		    {
		      std::string nm = lvars[i];

		      if (pattern.match (nm))
			curr_sym_tab->clear (nm);
		    }

		  int gcount = gvars.length ();

		  for (int i = 0; i < gcount; i++)
		    {
		      std::string nm = gvars[i];

		      if (pattern.match (nm))
			{
			  int count = curr_sym_tab->clear (nm);

			  if (count > 0)
			    global_sym_tab->clear (nm, clear_user_functions);
			}
		    }

		  int fcount = fcns.length ();

		  for (int i = 0; i < fcount; i++)
		    {
		      std::string nm = fcns[i];

		      if (pattern.match (nm))
			{
			  curr_sym_tab->clear (nm);

			  global_sym_tab->clear (nm, clear_user_functions);
			}
		    }
		}
	    }
	}
    }

  return retval;
}

DEFUN (__dump_symtab_info__, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} __dump_symtab_info__ ()\n\
Print raw symbol table statistices.\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin == 1)
    {
      std::string arg = args(0).string_value ();

      if (arg == "global")
	global_sym_tab->print_stats ();
      else
	print_usage ("__dump_symtab_info__");
    }
  else if (nargin == 0)
    curr_sym_tab->print_stats ();
  else
    print_usage ("__dump_symtab_info__");

  return retval;
}

DEFUN (__dump_symbol_info__, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} __dump_symbol_info__ (@var{name})\n\
Print symbol table information for the symbol @var{name}.\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin == 1)
    {
      std::string symbol_name = args(0).string_value ();

      if (! error_state)
	{
	  symbol_record *sr = curr_sym_tab->lookup (symbol_name);

	  if (sr)
	    sr->dump_symbol_info ();
	  else
	    error ("__dymp_symbol_info__: symbol %s not found",
		   symbol_name.c_str ());
	}
      else
	print_usage ("__dump_symbol_info__");
    }
  else
    print_usage ("__dump_symbol_info__");

  return retval;
}

// XXX FIXME XXX -- some of these should do their own checking to be
// able to provide more meaningful warning or error messages.

static int
ignore_function_time_stamp (void)
{
  int pref = 0;

  std::string val = builtin_string_variable ("ignore_function_time_stamp");

  if (! val.empty ())
    {
      if (val == "all")
	pref = 2;
      else if (val == "system")
	pref = 1;
    }

  Vignore_function_time_stamp = pref;

  return 0;
}

// XXX FIXME XXX -- there still may be better places for some of these
// to be defined.

void
symbols_of_variables (void)
{
  DEFVAR (ans, , 0,
    "-*- texinfo -*-\n\
@defvr {Built-in Variable} ans\n\
This variable holds the most recently computed result that was not\n\
explicitly assigned to a variable.  For example, after the expression\n\
\n\
@example\n\
3^2 + 4^2\n\
@end example\n\
\n\
@noindent\n\
is evaluated, the value of @code{ans} is 25.\n\
@end defvr");

  DEFVAR (ignore_function_time_stamp, "system", ignore_function_time_stamp,
    "-*- texinfo -*-\n\
@defvr {Built-in Variable} ignore_function_time_stamp\n\
This variable can be used to prevent Octave from making the system call\n\
@code{stat} each time it looks up functions defined in function files.\n\
If @code{ignore_function_time_stamp} to @code{\"system\"}, Octave will not\n\
automatically recompile function files in subdirectories of\n\
@file{@var{octave-home}/lib/@var{version}} if they have changed since\n\
they were last compiled, but will recompile other function files in the\n\
@code{LOADPATH} if they change.  If set to @code{\"all\"}, Octave will not\n\
recompile any function files unless their definitions are removed with\n\
@code{clear}.  For any other value of @code{ignore_function_time_stamp},\n\
Octave will always check to see if functions defined in function files\n\
need to recompiled.  The default value of @code{ignore_function_time_stamp} is\n\
@code{\"system\"}.\n\
@end defvr");
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
