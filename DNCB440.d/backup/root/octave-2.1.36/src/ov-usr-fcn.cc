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

#include "str-vec.h"

#include <defaults.h>
#include "defun.h"
#include "error.h"
#include "input.h"
#include "oct-obj.h"
#include "ov-usr-fcn.h"
#include "ov.h"
#include "pager.h"
#include "pt-jump.h"
#include "pt-misc.h"
#include "pt-pr-code.h"
#include "pt-stmt.h"
#include "pt-walk.h"
#include "symtab.h"
#include "toplev.h"
#include "unwind-prot.h"
#include "utils.h"
#include "parse.h"
#include "variables.h"

// If TRUE, variables returned from functions have default values even
// if they are not explicitly initialized.
static bool Vdefine_all_return_values;

// Maximum nesting level for functions called recursively.
static int Vmax_recursion_depth;

// If TRUE, the last computed value is returned from functions that
// don't actually define any return variables.
static bool Vreturn_last_computed_value;

// User defined functions.

DEFINE_OCTAVE_ALLOCATOR (octave_user_function);

DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_user_function,
				     "user-defined function");

// Ugh.  This really needs to be simplified (code/data?
// extrinsic/intrinsic state?).

octave_user_function::octave_user_function
  (tree_parameter_list *pl, tree_parameter_list *rl,
   tree_statement_list *cl, symbol_table *st)
  : octave_function (std::string (), std::string ()),
    param_list (pl), ret_list (rl), cmd_list (cl),
    sym_tab (st), lead_comm (), trail_comm (),
    file_name (), fcn_name (),
    t_parsed (static_cast<time_t> (0)),
    t_checked (static_cast<time_t> (0)),
    system_fcn_file (false), call_depth (0),
    num_named_args (0), args_passed (), num_args_passed (0),
    curr_va_arg_number (0), vr_list (0), symtab_entry (0),
    argn_sr (0), nargin_sr (0), nargout_sr (0)
{
  install_automatic_vars ();

  if (param_list)
    {
      num_named_args = param_list->length ();
      curr_va_arg_number = num_named_args;
    }
}

octave_user_function::~octave_user_function (void)
{
  delete param_list;
  delete ret_list;
  delete sym_tab;
  delete cmd_list;
  delete vr_list;
  delete lead_comm;
  delete trail_comm;
}

octave_user_function *
octave_user_function::define_ret_list (tree_parameter_list *t)
{
  ret_list = t;

  if (ret_list && ret_list->takes_varargs ())
    vr_list = new tree_va_return_list;
 
  return this;
}

void
octave_user_function::stash_fcn_file_name (void)
{
  if (fcn_name.empty ())
    file_name = "";
  else
    file_name = fcn_file_in_path (fcn_name);
}

void
octave_user_function::mark_as_system_fcn_file (void)
{
  if (! file_name.empty ())
    {
      // We really should stash the whole path to the file we found,
      // when we looked it up, to avoid possible race conditions...
      // XXX FIXME XXX
      //
      // We probably also don't need to get the library directory
      // every time, but since this function is only called when the
      // function file is parsed, it probably doesn't matter that
      // much.

      std::string ff_name = fcn_file_in_path (file_name);

      if (Vfcn_file_dir == ff_name.substr (0, Vfcn_file_dir.length ()))
	system_fcn_file = 1;
    }
  else
    system_fcn_file = 0;
}

bool
octave_user_function::takes_varargs (void) const
{
  return (param_list && param_list->takes_varargs ());
}

octave_value
octave_user_function::octave_va_arg (void)
{
  octave_value retval;

  if (curr_va_arg_number < num_args_passed)
    retval = args_passed (curr_va_arg_number++);
  else
    ::error ("va_arg: error getting arg number %d -- only %d provided",
	     curr_va_arg_number + 1, num_args_passed);

  return retval;
}

octave_value_list
octave_user_function::octave_all_va_args (void)
{
  octave_value_list retval;

  int n = num_args_passed - num_named_args;

  if (n > 0)
    {
      retval.resize (n);

      int k = 0;
      for (int i = num_named_args; i < num_args_passed; i++)
	retval(k++) = args_passed(i);
    }

  return retval;
}

bool
octave_user_function::takes_var_return (void) const
{
  return (ret_list && ret_list->takes_varargs ());
}

void
octave_user_function::octave_vr_val (const octave_value& val)
{
  assert (vr_list);

  vr_list->append (val);
}

void
octave_user_function::stash_function_name (const std::string& s)
{
  fcn_name = s;
}

// For unwind protect.

static void
pop_symbol_table_context (void *table)
{
  symbol_table *tmp = static_cast<symbol_table *> (table);
  tmp->pop_context ();
}

static void
delete_vr_list (void *list)
{
  tree_va_return_list *tmp = static_cast<tree_va_return_list *> (list);
  tmp->clear ();
  delete tmp;
}

static void
clear_symbol_table (void *table)
{
  symbol_table *tmp = static_cast<symbol_table *> (table);
  tmp->clear ();
}

static void
clear_param_list (void *lst)
{
  tree_parameter_list *tmp = static_cast<tree_parameter_list *> (lst);

  if (tmp)
    tmp->clear ();
}

static void
restore_args_passed (void *fcn)
{
  octave_user_function *tmp = static_cast<octave_user_function *> (fcn);

  if (tmp)
    tmp->restore_args_passed ();
}

static void
unprotect_function (void *sr_arg)
{
  symbol_record *sr = static_cast<symbol_record *> (sr_arg);
  sr->unprotect ();
}

octave_value_list
octave_user_function::do_multi_index_op (int nargout,
					 const octave_value_list& args)
{
  octave_value_list retval;

  if (error_state)
    return retval;

  if (! cmd_list)
    return retval;

  int nargin = args.length ();

  unwind_protect::begin_frame ("func_eval");

  unwind_protect_int (call_depth);
  call_depth++;

  if (call_depth > Vmax_recursion_depth)
    {
      ::error ("max_recursion_limit exceeded");
      unwind_protect::run_frame ("func_eval");
      return retval;
    }

  if (symtab_entry && ! symtab_entry->is_read_only ())
    {
      symtab_entry->protect ();
      unwind_protect::add (unprotect_function, symtab_entry);
    }

  if (call_depth > 1)
    {
      sym_tab->push_context ();
      unwind_protect::add (pop_symbol_table_context, sym_tab);

      if (vr_list)
	{
	  // Push new vr_list.

	  unwind_protect_ptr (vr_list);
	  vr_list = new tree_va_return_list;

	  // Clear and delete the new one before restoring the old
	  // one.

	  unwind_protect::add (delete_vr_list, vr_list);
	}
    }

  if (vr_list)
    vr_list->clear ();

  // Force symbols to be undefined again when this function exits.

  unwind_protect::add (clear_symbol_table, sym_tab);

  // Save old and set current symbol table context, for
  // eval_undefined_error().

  unwind_protect_ptr (curr_sym_tab);
  curr_sym_tab = sym_tab;

  unwind_protect_ptr (curr_function);
  curr_function = this;

  // Save and restore args passed for recursive calls.

  save_args_passed (args);

  unwind_protect::add (::restore_args_passed, this);

  string_vector arg_names = args.name_tags ();

  unwind_protect_int (num_args_passed);
  num_args_passed = nargin;

  unwind_protect_int (curr_va_arg_number);

  curr_va_arg_number = num_named_args;

  if (param_list && ! param_list->varargs_only ())
    {
      param_list->define_from_arg_vector (args);
      if (error_state)
	goto abort;
    }

  // Force parameter list to be undefined when this function exits.
  // Doing so decrements the reference counts on the values of local
  // variables that are also named function parameters.

  unwind_protect::add (clear_param_list, param_list);

  // Force return list to be undefined when this function exits.
  // Doing so decrements the reference counts on the values of local
  // variables that are also named values returned by this function.

  unwind_protect::add (clear_param_list, ret_list);

  // The following code is in a separate scope to avoid warnings from
  // G++ about `goto abort' crossing the initialization of some
  // variables.

  {
    bind_automatic_vars (arg_names, nargin, nargout);

    bool echo_commands = (Vecho_executing_commands & ECHO_FUNCTIONS);

    if (echo_commands)
      print_code_function_header ();

    // Evaluate the commands that make up the function.

    unwind_protect_bool (evaluating_function_body);
    evaluating_function_body = true;

    octave_value_list tmp = cmd_list->eval ();

    octave_value last_computed_value;

    if (! tmp.empty ())
      last_computed_value = tmp(0);

    if (echo_commands)
      print_code_function_trailer ();

    if (tree_return_command::returning)
      tree_return_command::returning = 0;

    if (tree_break_command::breaking)
      tree_break_command::breaking--;

    if (error_state)
      {
	traceback_error ();
	goto abort;
      }
    
    // Copy return values out.

    if (ret_list)
      {
	if (Vdefine_all_return_values)
	  {
	    octave_value tmp = builtin_any_variable ("default_return_value");

	    if (tmp.is_defined ())
	      ret_list->initialize_undefined_elements (tmp);
	  }

	retval = ret_list->convert_to_const_vector (vr_list);
      }
    else if (Vreturn_last_computed_value)
      retval(0) = last_computed_value;
  }

 abort:
  unwind_protect::run_frame ("func_eval");

  return retval;
}

void
octave_user_function::traceback_error (void)
{
  if (error_state >= 0)
    error_state = -1;

  if (fcn_name.empty ())
    {
      if (file_name.empty ())
	::error ("called from `?unknown?'");
      else
	::error ("called from file `%s'", file_name.c_str ());
    }
  else
    {
      if (file_name.empty ())
	::error ("called from `%s'", fcn_name.c_str ());
      else 
	::error ("called from `%s' in file `%s'",
		 fcn_name.c_str (), file_name.c_str ());
    }
}

void
octave_user_function::accept (tree_walker& tw)
{
  tw.visit_octave_user_function (*this);
}

void
octave_user_function::print_code_function_header (void)
{
  tree_print_code tpc (octave_stdout, Vps4);

  tpc.visit_octave_user_function_header (*this);
}

void
octave_user_function::print_code_function_trailer (void)
{
  tree_print_code tpc (octave_stdout, Vps4);

  tpc.visit_octave_user_function_trailer (*this);
}

void
octave_user_function::install_automatic_vars (void)
{
  argn_sr = sym_tab->lookup ("argn", true);
  nargin_sr = sym_tab->lookup ("nargin", true);
  nargout_sr = sym_tab->lookup ("nargout", true);
}

void
octave_user_function::bind_automatic_vars
  (const string_vector& arg_names, int nargin, int nargout)
{
  if (! arg_names.empty ())
    argn_sr->define (arg_names);

  nargin_sr->define (static_cast<double> (nargin));
  nargout_sr->define (static_cast<double> (nargout));
}

DEFUNX ("va_arg", Fva_arg, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} va_arg ()\n\
Return the value of the next available argument and move the internal\n\
pointer to the next argument.  It is an error to call @code{va_arg}\n\
when ther eare no more arguments available, or in a function that\n\
has not been declared to take a variable number of parameters.\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin == 0)
    {
      if (curr_function)
	{
	  if (curr_function->takes_varargs ())
	    retval = curr_function->octave_va_arg ();
	  else
	    {
	      ::error ("va_arg only valid within function taking variable");
	      ::error ("number of arguments");
	    }
	}
      else
	::error ("va_arg only valid within function body");
    }
  else
    print_usage ("va_arg");

  return retval;
}

DEFUN (va_start, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} va_start ()\n\
Position an internal pointer to the first unnamed argument in\n\
functions that have been declared to accept a variable number of\n\
arguments.  It is an error to call @code{va_start} in a function\n\
that has not been declared to take a variable number of parameters.\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin == 0)
    {
      if (curr_function)
	{
	  if (curr_function->takes_varargs ())
	    curr_function->octave_va_start ();
	  else
	    {
	      ::error ("va_start only valid within function taking variable");
	      ::error ("number of arguments");
	    }
	}
      else
	::error ("va_start only valid within function body");
    }
  else
    print_usage ("va_start");

  return retval;
}

DEFUN (vr_val, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} vr_val (@var{x})\n\
Each time this function is called, it places the value of its argument\n\
at the end of the list of values to return from the current\n\
function.  Once @code{vr_val} has been called, there is no way to go\n\
back to the beginning of the list and rewrite any of the return\n\
values.  This function may only be called within functions that have\n\
been declared to return an unspecified number of output arguments.\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin == 1)
    {
      if (curr_function)
	{
	  if (curr_function->takes_var_return ())
	    curr_function->octave_vr_val (args(0));
	  else
	    {
	      ::error ("vr_val only valid within function declared to");
	      ::error ("produce a variable number of values");
	    }
	}
      else
	::error ("vr_val only valid within function body");
    }
  else
    print_usage ("vr_val");

  return retval;
}

static int
define_all_return_values (void)
{
  Vdefine_all_return_values = check_preference ("define_all_return_values");

  return 0;
}

static int
max_recursion_depth (void)
{
  Vmax_recursion_depth = check_preference ("max_recursion_depth");

  return 0;
}

static int
return_last_computed_value (void)
{
  Vreturn_last_computed_value
    = check_preference ("return_last_computed_value");

  return 0;
}

void
symbols_of_ov_usr_fcn (void)
{
  DEFVAR (default_return_value, Matrix (), 0,
    "-*- texinfo -*-\n\
@defvr {Built-in Variable} default_return_value\n\
The value given to otherwise uninitialized return values if\n\
@code{define_all_return_values} is nonzero.  The default value is\n\
@code{[]}.\n\
@end defvr");

  DEFVAR (define_all_return_values, 0.0, define_all_return_values,
    "-*- texinfo -*-\n\
@defvr {Built-in Variable} define_all_return_values\n\
If the value of @code{define_all_return_values} is nonzero, Octave\n\
will substitute the value specified by @code{default_return_value} for\n\
any return values that remain undefined when a function returns.  The\n\
default value is 0.\n\
@end defvr");

  DEFVAR (max_recursion_depth, 256.0, max_recursion_depth,
    "-*- texinfo -*-\n\
@defvr {Built-in Variable} max_recursion_depth\n\
Limit the number of times a function may be called recursively.\n\
If the limit is exceeded, an error message is printed and control\n\
returns to the top level.\n\
\n\
The default value is 256.\n\
@end defvr");

  DEFVAR (return_last_computed_value, 0.0, return_last_computed_value,
    "-*- texinfo -*-\n\
@defvr {Built-in Variable} return_last_computed_value\n\
If the value of @code{return_last_computed_value} is true, and a\n\
function is defined without explicitly specifying a return value, the\n\
function will return the value of the last expression.  Otherwise, no\n\
value will be returned.  The default value is 0.\n\
\n\
For example, the function\n\
\n\
@example\n\
function f ()\n\
  2 + 2;\n\
endfunction\n\
@end example\n\
\n\
@noindent\n\
will either return nothing, if the value of\n\
@code{return_last_computed_value} is 0, or 4, if the value of\n\
@code{return_last_computed_value} is nonzero.\n\
@end defvr");
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
