/*

Copyright (C) 2001 Ben Sapp

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

#if !defined (octave_tree_bp_h)
#define octave_tree_bp_h 1

#if defined (__GNUG__) && defined (USE_PRAGMA_INTERFACE_IMPLEMENTATION)
#pragma interface
#endif

#include "input.h"
#include "ov-usr-fcn.h"
#include "pt-walk.h"
#include "pt-pr-code.h"
#include "toplev.h"

class tree;

class
tree_breakpoint : public tree_walker
{
 public:

  enum action { set = 1, clear = 2, list = 3 };

  tree_breakpoint (int l, action a)
    : line (l), act (a), found (false), bp_list () { }

  ~tree_breakpoint (void) { }

  bool success (void) const { return found; }

  void visit_argument_list (tree_argument_list&);

  void visit_binary_expression (tree_binary_expression&);

  void visit_break_command (tree_break_command&);

  void visit_colon_expression (tree_colon_expression&);

  void visit_continue_command (tree_continue_command&);

  void visit_decl_command (tree_decl_command&);

  void visit_decl_elt (tree_decl_elt&);

  void visit_decl_init_list (tree_decl_init_list&);  

  void visit_while_command (tree_while_command&);

  void visit_do_until_command (tree_do_until_command&);

  void visit_simple_for_command (tree_simple_for_command&);

  void visit_complex_for_command (tree_complex_for_command&);

  void visit_octave_user_function (octave_user_function&);

  void visit_octave_user_function_header (octave_user_function&);

  void visit_octave_user_function_trailer (octave_user_function&);

  void visit_identifier (tree_identifier&);

  void visit_if_clause (tree_if_clause&);

  void visit_if_command (tree_if_command&);

  void visit_if_command_list (tree_if_command_list&);

  void visit_index_expression (tree_index_expression&);

  void visit_matrix (tree_matrix&);

  void visit_cell (tree_cell&);

  void visit_multi_assignment (tree_multi_assignment&);

  void visit_no_op_command (tree_no_op_command&);

  void visit_constant (tree_constant&);

  void visit_fcn_handle (tree_fcn_handle&);

  void visit_parameter_list (tree_parameter_list&);

  void visit_plot_command (tree_plot_command&);

  void visit_plot_limits (plot_limits&);

  void visit_plot_range (plot_range&);

  void visit_postfix_expression (tree_postfix_expression&);

  void visit_prefix_expression (tree_prefix_expression&);

  void visit_return_command (tree_return_command&);

  void visit_return_list (tree_return_list&);

  void visit_simple_assignment (tree_simple_assignment&);

  void visit_statement (tree_statement&);

  void visit_statement_list (tree_statement_list&);

  void visit_subplot (subplot&);

  void visit_subplot_axes (subplot_axes&);

  void visit_subplot_list (subplot_list&);

  void visit_subplot_style (subplot_style&);

  void visit_subplot_using (subplot_using&);

  void visit_switch_case (tree_switch_case&);

  void visit_switch_case_list (tree_switch_case_list&);

  void visit_switch_command (tree_switch_command&);

  void visit_try_catch_command (tree_try_catch_command&);

  void visit_unwind_protect_command (tree_unwind_protect_command&);

  octave_value_list get_list (void) { return bp_list; }
  
  int get_line (void) { return line; }

 private:

  void take_action (tree &tr);

  // Statement line number we are looking for.
  int line;

  // What to do.
  action act;

  // Have we already found the line?
  bool found;

  // List of breakpoint line numbers.
  octave_value_list bp_list;

  // No copying!

  tree_breakpoint (const tree_breakpoint&);

  tree_breakpoint& operator = (const tree_breakpoint&);
};

// TRUE means SIGINT should put us in the debugger at the next
// available breakpoint.
extern bool octave_debug_on_interrupt_state;

#define MAYBE_DO_BREAKPOINT \
  do \
    { \
      if (octave_debug_on_interrupt_state \
	  || (tree::break_next && tree::last_line == 0) \
	  || (tree::break_next \
	      && curr_function == tree::break_function \
	      && tree::last_line != line ()) \
	  || is_breakpoint ()) \
        { \
          octave_debug_on_interrupt_state = false; \
 \
          tree::break_next = false; \
 \
          if (curr_function) \
            octave_stdout << curr_function->name () << ": ";  \
 \
          octave_stdout << "line " << line () << ", " \
			<< "column " << column () \
			<< std::endl; \
 \
          tree_print_code tpc (octave_stdout); \
          this->accept (tpc); \
 \
          octave_stdout << std::endl; \
 \
          tree::break_statement = this; \
 \
          do_keyboard (); \
        } \
    } \
  while (0)

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
