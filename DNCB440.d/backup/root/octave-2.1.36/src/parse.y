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

// Parser for Octave.

// C decarations.

%{
#define YYDEBUG 1

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <cassert>
#include <cstdio>

#ifdef YYBYACC
#include <cstdlib>
#endif

#include <strstream.h>

#include "Matrix.h"
#include "cmd-edit.h"
#include "cmd-hist.h"
#include "file-ops.h"
#include "file-stat.h"
#include "oct-time.h"

#include "comment-list.h"
#include "defun.h"
#include "dynamic-ld.h"
#include "error.h"
#include "input.h"
#include "lex.h"
#include "oct-hist.h"
#include "ov-usr-fcn.h"
#include "toplev.h"
#include "pager.h"
#include "parse.h"
#include "pt-all.h"
#include "symtab.h"
#include "token.h"
#include "unwind-prot.h"
#include "utils.h"
#include "variables.h"

// TRUE means we print 
static bool Vdefault_eval_print_flag = true;

// If TRUE, generate a warning for the assignment in things like
//
//   octave> if (a = 2 < n)
//
// but not
//
//   octave> if ((a = 2) < n)
//
static bool Vwarn_assign_as_truth_value;

// If TRUE, generate a warning for variable swich labels.
static bool Vwarn_variable_switch_label;

// If TRUE, generate warning if declared function name disagrees with
// the name of the file in which it is defined.
static bool Vwarn_function_name_clash;

// TRUE means warn about function files that have time stamps in the future.
bool Vwarn_future_time_stamp;

// If TRUE, generate warning if a statement in a function is not
// terminated with a semicolon.  Useful for checking functions that
// should only produce output using explicit printing statements.
static bool Vwarn_missing_semicolon;

// Temporary symbol table pointer used to cope with bogus function syntax.
symbol_table *tmp_local_sym_tab = 0;

// The current input line number.
int input_line_number = 0;

// The column of the current token.
int current_input_column = 1;

// Buffer for help text snagged from function files.
std::string help_buf;

// Buffer for comments appearing before a function statement.
static std::string fcn_comment_header;

// TRUE means we are using readline.
// (--no-line-editing)
bool line_editing = true;

// TRUE means we printed messages about reading startup files.
bool reading_startup_message_printed = false;

// TRUE means input is coming from startup file.
bool input_from_startup_file = false;

// TRUE means that input is coming from a file that was named on
// the command line.
bool input_from_command_line_file = true;

// TRUE means that we are in the process of evaluating a function
// body.  The parser might be called in that case if we are looking at
// an eval() statement.
bool evaluating_function_body = false;

// Keep track of symbol table information when parsing functions.
static symbol_table *symtab_context = 0;

// Forward declarations for some functions defined at the bottom of
// the file.

// Generic error messages.
static void
yyerror (const char *s);

// Error mesages for mismatched end tokens.
static void
end_error (const char *type, token::end_tok_type ettype, int l, int c);

// Check to see that end tokens are properly matched.
static bool
end_token_ok (token *tok, token::end_tok_type expected);

// Maybe print a warning if an assignment expression is used as the
// test in a logical expression.
static void
maybe_warn_assign_as_truth_value (tree_expression *expr);

// Maybe print a warning about switch labels that aren't constants.
static void
maybe_warn_variable_switch_label (tree_expression *expr);

// Create a plot command.
static tree_plot_command *
make_plot_command (token *tok, plot_limits *range, subplot_list *list);

// Finish building a range.
static tree_expression *
finish_colon_expression (tree_colon_expression *e);

// Build a constant.
static tree_constant *
make_constant (int op, token *tok_val);

// Build a binary expression.
static tree_expression *
make_binary_op (int op, tree_expression *op1, token *tok_val,
		tree_expression *op2);

// Build a boolean expression.
static tree_expression *
make_boolean_op (int op, tree_expression *op1, token *tok_val,
		 tree_expression *op2);

// Build a prefix expression.
static tree_expression *
make_prefix_op (int op, tree_expression *op1, token *tok_val);

// Build a postfix expression.
static tree_expression *
make_postfix_op (int op, tree_expression *op1, token *tok_val);

// Build an unwind-protect command.
static tree_command *
make_unwind_command (token *unwind_tok, tree_statement_list *body,
		     tree_statement_list *cleanup, token *end_tok,
		     octave_comment_list *lc, octave_comment_list *mc);

// Build a try-catch command.
static tree_command *
make_try_command (token *try_tok, tree_statement_list *body,
		  tree_statement_list *cleanup, token *end_tok,
		  octave_comment_list *lc, octave_comment_list *mc);

// Build a while command.
static tree_command *
make_while_command (token *while_tok, tree_expression *expr,
		    tree_statement_list *body, token *end_tok,
		    octave_comment_list *lc);

// Build a do-until command.
static tree_command *
make_do_until_command (token *do_tok, tree_statement_list *body,
		       tree_expression *expr, octave_comment_list *lc);

// Build a for command.
static tree_command *
make_for_command (token *for_tok, tree_argument_list *lhs,
		  tree_expression *expr, tree_statement_list *body,
		  token *end_tok, octave_comment_list *lc);

// Build a break command.
static tree_command *
make_break_command (token *break_tok);

// Build a continue command.
static tree_command *
make_continue_command (token *continue_tok);

// Build a return command.
static tree_command *
make_return_command (token *return_tok);

// Start an if command.
static tree_if_command_list *
start_if_command (tree_expression *expr, tree_statement_list *list);

// Finish an if command.
static tree_if_command *
finish_if_command (token *if_tok, tree_if_command_list *list,
		   token *end_tok, octave_comment_list *lc);

// Build an elseif clause.
static tree_if_clause *
make_elseif_clause (tree_expression *expr, tree_statement_list *list,
		    octave_comment_list *lc);

// Finish a switch command.
static tree_switch_command *
finish_switch_command (token *switch_tok, tree_expression *expr,
		       tree_switch_case_list *list, token *end_tok,
		       octave_comment_list *lc);

// Build a switch case.
static tree_switch_case *
make_switch_case (tree_expression *expr, tree_statement_list *list,
		  octave_comment_list *lc);

// Build an assignment to a variable.
static tree_expression *
make_assign_op (int op, tree_argument_list *lhs, token *eq_tok,
		tree_expression *rhs);

// Begin defining a function.
static octave_user_function *
start_function (tree_parameter_list *param_list, tree_statement_list *body);

// Do most of the work for defining a function.
static octave_user_function *
frob_function (tree_identifier *id, octave_user_function *fcn);

// Finish defining a function.
static octave_user_function *
finish_function (tree_identifier *id, octave_user_function *fcn,
		 octave_comment_list *lc);

// Finish defining a function a different way.
static octave_user_function *
finish_function (tree_parameter_list *ret_list,
		 octave_user_function *fcn, octave_comment_list *lc);

// Reset state after parsing function.
static void
recover_from_parsing_function (void);

// Make an index expression.
static tree_index_expression *
make_index_expression (tree_expression *expr, tree_argument_list *args);

// Make an indirect reference expression.
static tree_indirect_ref *
make_indirect_ref (tree_expression *expr, const std::string&);

// Make a declaration command.
static tree_decl_command *
make_decl_command (int tok, token *tok_val, tree_decl_init_list *lst);

// Finish building a matrix list.
static tree_expression *
finish_matrix (tree_matrix *m);

// Finish building a cell list.
static tree_expression *
finish_cell (tree_cell *c);

// Maybe print a warning.  Duh.
static void
maybe_warn_missing_semi (tree_statement_list *);

// Set the print flag for a statement based on the separator type.
static void
set_stmt_print_flag (tree_statement_list *, char, bool);

#define ABORT_PARSE \
  do \
    { \
      global_command = 0; \
      yyerrok; \
      if (interactive || forced_interactive) \
	YYACCEPT; \
      else \
	YYABORT; \
    } \
  while (0)

%}

// Bison declarations.

%union
{
  // The type of the basic tokens returned by the lexer.
  token *tok_val;

  // Comment strings that we need to deal with mid-rule.
  octave_comment_list *comment_type;

  // Types for the nonterminals we generate.
  char sep_type;
  tree *tree_type;
  tree_matrix *tree_matrix_type;
  tree_cell *tree_cell_type;
  tree_expression *tree_expression_type;
  tree_constant *tree_constant_type;
  tree_identifier *tree_identifier_type;
  tree_index_expression *tree_index_expression_type;
  tree_colon_expression *tree_colon_expression_type;
  tree_argument_list *tree_argument_list_type;
  tree_parameter_list *tree_parameter_list_type;
  tree_command *tree_command_type;
  tree_if_command *tree_if_command_type;
  tree_if_clause *tree_if_clause_type;
  tree_if_command_list *tree_if_command_list_type;
  tree_switch_command *tree_switch_command_type;
  tree_switch_case *tree_switch_case_type;
  tree_switch_case_list *tree_switch_case_list_type;
  tree_decl_elt *tree_decl_elt_type;
  tree_decl_init_list *tree_decl_init_list_type;
  tree_decl_command *tree_decl_command_type;
  tree_statement *tree_statement_type;
  tree_statement_list *tree_statement_list_type;
  tree_plot_command *tree_plot_command_type;
  subplot *subplot_type;
  subplot_list *subplot_list_type;
  plot_limits *plot_limits_type;
  plot_range *plot_range_type;
  subplot_using *subplot_using_type;
  subplot_style *subplot_style_type;
  subplot_axes *subplot_axes_type;
  octave_user_function *octave_user_function_type;
}

// Tokens with line and column information.
%token <tok_val> '=' ':' '-' '+' '*' '/'
%token <tok_val> ADD_EQ SUB_EQ MUL_EQ DIV_EQ LEFTDIV_EQ 
%token <tok_val> EMUL_EQ EDIV_EQ ELEFTDIV_EQ AND_EQ OR_EQ
%token <tok_val> LSHIFT_EQ RSHIFT_EQ LSHIFT RSHIFT
%token <tok_val> EXPR_AND_AND EXPR_OR_OR
%token <tok_val> EXPR_AND EXPR_OR EXPR_NOT
%token <tok_val> EXPR_LT EXPR_LE EXPR_EQ EXPR_NE EXPR_GE EXPR_GT
%token <tok_val> LEFTDIV EMUL EDIV ELEFTDIV EPLUS EMINUS
%token <tok_val> QUOTE TRANSPOSE
%token <tok_val> PLUS_PLUS MINUS_MINUS POW EPOW
%token <tok_val> NUM IMAG_NUM
%token <tok_val> STRUCT_ELT
%token <tok_val> NAME
%token <tok_val> END
%token <tok_val> PLOT
%token <tok_val> TEXT STYLE AXES_TAG
%token <tok_val> FOR WHILE DO UNTIL
%token <tok_val> IF ELSEIF ELSE
%token <tok_val> SWITCH CASE OTHERWISE
%token <tok_val> BREAK CONTINUE FUNC_RET
%token <tok_val> UNWIND CLEANUP
%token <tok_val> TRY CATCH
%token <tok_val> GLOBAL STATIC

// Other tokens.
%token END_OF_INPUT LEXICAL_ERROR
%token FCN ELLIPSIS ALL_VA_ARGS
%token USING TITLE WITH AXES COLON OPEN_BRACE CLOSE_BRACE CLEAR

// Nonterminals we construct.
%type <comment_type> stash_comment function_beg
%type <sep_type> sep_no_nl opt_sep_no_nl sep opt_sep
%type <tree_type> input
%type <tree_constant_type> constant magic_colon
%type <tree_matrix_type> matrix_rows matrix_rows1
%type <tree_cell_type> cell_rows cell_rows1
%type <tree_expression_type> title matrix cell
%type <tree_expression_type> primary_expr postfix_expr prefix_expr binary_expr
%type <tree_expression_type> simple_expr colon_expr assign_expr expression
%type <tree_identifier_type> identifier
%type <octave_user_function_type> function1 function2 function3
%type <tree_index_expression_type> word_list_cmd
%type <tree_colon_expression_type> colon_expr1
%type <tree_argument_list_type> arg_list word_list assign_lhs
%type <tree_argument_list_type> cell_or_matrix_row
%type <tree_parameter_list_type> param_list param_list1
%type <tree_parameter_list_type> return_list return_list1
%type <tree_command_type> command select_command loop_command
%type <tree_command_type> jump_command except_command function
%type <tree_if_command_type> if_command
%type <tree_if_clause_type> elseif_clause else_clause
%type <tree_if_command_list_type> if_cmd_list1 if_cmd_list
%type <tree_switch_command_type> switch_command
%type <tree_switch_case_type> switch_case default_case
%type <tree_switch_case_list_type> case_list1 case_list
%type <tree_decl_elt_type> decl2
%type <tree_decl_init_list_type> decl1
%type <tree_decl_command_type> declaration
%type <tree_statement_type> statement
%type <tree_statement_list_type> simple_list simple_list1 list list1
%type <tree_statement_list_type> opt_list input1 function4
%type <tree_plot_command_type> plot_command 
%type <subplot_type> plot_command2 plot_options
%type <subplot_list_type> plot_command1
%type <plot_limits_type> ranges
%type <plot_range_type> ranges1 
%type <subplot_using_type> using using1 
%type <subplot_style_type> style
%type <subplot_axes_type> axes

// Precedence and associativity.
%left ';' ',' '\n'
%right '=' ADD_EQ SUB_EQ MUL_EQ DIV_EQ LEFTDIV_EQ EMUL_EQ EDIV_EQ ELEFTDIV_EQ OR_EQ AND_EQ LSHIFT_EQ RSHIFT_EQ
%left EXPR_AND_AND EXPR_OR_OR
%left EXPR_AND EXPR_OR
%left EXPR_LT EXPR_LE EXPR_EQ EXPR_NE EXPR_GE EXPR_GT
%left LSHIFT RSHIFT
%left ':'
%left '-' '+' EPLUS EMINUS
%left '*' '/' LEFTDIV EMUL EDIV ELEFTDIV
%left QUOTE TRANSPOSE
%left UNARY PLUS_PLUS MINUS_MINUS EXPR_NOT
%right POW EPOW
%left '(' '.' '{'

// Where to start.
%start input

%%

// ==============================
// Statements and statement lists
// ==============================

input		: input1
		  {
		    global_command = $1;
		    promptflag = 1;
		    YYACCEPT;
		  }
		| simple_list parse_error
		  { ABORT_PARSE; }
		| parse_error
		  { ABORT_PARSE; }
		;

input1		: '\n'
		  { $$ = 0; }
		| END_OF_INPUT
		  {
		    parser_end_of_input = 1;
		    $$ = 0;
		  }
		| simple_list
		  { $$ = $1; }
		| simple_list '\n'
		  { $$ = $1; }
		| simple_list END_OF_INPUT
		  { $$ = $1; }
		;

simple_list	: simple_list1 opt_sep_no_nl
		  {
		    set_stmt_print_flag ($1, $2, false);
		    $$ = $1;
		  }
		;

simple_list1	: statement
		  { $$ = new tree_statement_list ($1); }
		| simple_list1 sep_no_nl statement
		  {
		    set_stmt_print_flag ($1, $2, false);
		    $1->append ($3);
		    $$ = $1;
		  }
		;

opt_list	: // empty
		  { $$ = new tree_statement_list (); }
		| list
		  { $$ = $1; }
		;

list		: list1 opt_sep
		  {
		    set_stmt_print_flag ($1, $2, true);
		    $$ = $1;
		  }
		;

list1		: statement
		  {
		    lexer_flags.beginning_of_function = false;
		    $$ = new tree_statement_list ($1);
		  }
		| list1 sep statement
		  {
		    set_stmt_print_flag ($1, $2, true);
		    $1->append ($3);
		    $$ = $1;
		  }
		;

statement	: expression
		  {
		    octave_comment_list *comment
		      = octave_comment_buffer::get_comment ();

		    $$ = new tree_statement ($1, comment);
		  }
		| command
		  {
		    octave_comment_list *comment
		      = octave_comment_buffer::get_comment ();

		    $$ = new tree_statement ($1, comment);
		  }
		| PLOT CLEAR
		  {
		    symbol_record *sr = lookup_by_name ("clearplot", 0);
		    tree_identifier *id = new tree_identifier (sr);

		    octave_comment_list *comment
		      = octave_comment_buffer::get_comment ();

		    $$ = new tree_statement (id, comment);
		  }
		;

// ===========
// Expressions
// ===========

identifier	: NAME
		  {
		    $$ = new tree_identifier
		      ($1->sym_rec (), $1->line (), $1->column ());
		  }
		;

constant	: NUM
		  { $$ = make_constant (NUM, $1); }
		| IMAG_NUM
		  { $$ = make_constant (IMAG_NUM, $1); }
		| TEXT
		  { $$ = make_constant (TEXT, $1); }
		;

in_matrix_or_assign_lhs
		: // empty
		  { lexer_flags.looking_at_matrix_or_assign_lhs = true; }
		;

matrix		: '[' ']'
		  { $$ = new tree_constant (octave_value (Matrix ())); }
		| '[' ';' ']'
		  { $$ = new tree_constant (octave_value (Matrix ())); }
		| '[' in_matrix_or_assign_lhs matrix_rows ']'
		  {
		    $$ = finish_matrix ($3);
		    lexer_flags.looking_at_matrix_or_assign_lhs = false;
		  }
		;

matrix_rows	: matrix_rows1
		  { $$ = $1; }
		| matrix_rows1 ';'	// Ignore trailing semicolon.
		  { $$ = $1; }
		;

matrix_rows1	: cell_or_matrix_row
		  { $$ = new tree_matrix ($1); }
		| matrix_rows1 ';' cell_or_matrix_row
		  {
		    $1->append ($3);
		    $$ = $1;
		  }
		;

cell		: '{' '}'
		  { $$ = new tree_constant (octave_value (Matrix ())); }
		| '{' ';' '}'
		  { $$ = new tree_constant (octave_value (Matrix ())); }
		| '{' cell_rows '}'
		  { $$ = finish_cell ($2); }
		;

cell_rows	: cell_rows1
		  { $$ = $1; }
		| cell_rows1 ';'	// Ignore trailing semicolon.
		  { $$ = $1; }
		;

cell_rows1	: cell_or_matrix_row
		  { $$ = new tree_cell ($1); }
		| cell_rows1 ';' cell_or_matrix_row
		  {
		    $1->append ($3);
		    $$ = $1;
		  }
		;

cell_or_matrix_row
		: arg_list
		  { $$ = $1; }
		| arg_list ','	// Ignore trailing comma.
		  { $$ = $1; }
		;

primary_expr	: identifier
		  { $$ = $1; }
		| constant
		  { $$ = $1; }
		| matrix
		  { $$ = $1; }
		| cell
		  { $$ = $1; }
		| '(' expression ')'
		  { $$ = $2->mark_in_parens (); }
		;

magic_colon	: ':'
		  {
		    octave_value tmp (octave_value::magic_colon_t);
		    $$ = new tree_constant (tmp);
		  }
		;

arg_list	: expression
		  { $$ = new tree_argument_list ($1); }
		| magic_colon
		  { $$ = new tree_argument_list ($1); }
		| ALL_VA_ARGS
		  {
		    octave_value tmp (octave_value::all_va_args_t);
		    tree_constant *all_va_args = new tree_constant (tmp);
		    $$ = new tree_argument_list (all_va_args);
		  }
		| arg_list ',' magic_colon
		  {
		    $1->append ($3);
		    $$ = $1;
		  }
		| arg_list ',' expression
		  {
		    $1->append ($3);
		    $$ = $1;
		  }
		| arg_list ',' ALL_VA_ARGS
		  {
		    octave_value tmp (octave_value::all_va_args_t);
		    tree_constant *all_va_args = new tree_constant (tmp);
		    $1->append (all_va_args);
		    $$ = $1;
		  }
		;

parsing_indir	: // empty
		  { lexer_flags.looking_at_indirect_ref = true; }
		;

postfix_expr	: primary_expr
		  { $$ = $1; }
		| postfix_expr '(' ')'
		  { $$ = make_index_expression ($1, 0); }
		| postfix_expr '(' arg_list ')'
		  { $$ = make_index_expression ($1, $3); }
		| postfix_expr '{' arg_list '}'
		  { $$ = make_index_expression ($1, $3); }
		| postfix_expr PLUS_PLUS
		  { $$ = make_postfix_op (PLUS_PLUS, $1, $2); }
		| postfix_expr MINUS_MINUS
		  { $$ = make_postfix_op (MINUS_MINUS, $1, $2); }
		| postfix_expr QUOTE
		  { $$ = make_postfix_op (QUOTE, $1, $2); }
		| postfix_expr TRANSPOSE
		  { $$ = make_postfix_op (TRANSPOSE, $1, $2); }
		| postfix_expr '.' parsing_indir STRUCT_ELT
		  { $$ = make_indirect_ref ($1, $4->text ()); }
		;

prefix_expr	: postfix_expr
		  { $$ = $1; }
		| binary_expr
		  { $$ = $1; }
		| PLUS_PLUS prefix_expr %prec UNARY
		  { $$ = make_prefix_op (PLUS_PLUS, $2, $1); }
		| MINUS_MINUS prefix_expr %prec UNARY
		  { $$ = make_prefix_op (MINUS_MINUS, $2, $1); }
		| EXPR_NOT prefix_expr %prec UNARY
		  { $$ = make_prefix_op (EXPR_NOT, $2, $1); }
		| '+' prefix_expr %prec UNARY
		  { $$ = $2; }
		| '-' prefix_expr %prec UNARY
		  { $$ = make_prefix_op ('-', $2, $1); }
		;

binary_expr	: prefix_expr POW prefix_expr
		  { $$ = make_binary_op (POW, $1, $2, $3); }
		| prefix_expr EPOW prefix_expr
		  { $$ = make_binary_op (EPOW, $1, $2, $3); }
		| prefix_expr '+' prefix_expr
		  { $$ = make_binary_op ('+', $1, $2, $3); }
		| prefix_expr '-' prefix_expr
		  { $$ = make_binary_op ('-', $1, $2, $3); }
		| prefix_expr '*' prefix_expr
		  { $$ = make_binary_op ('*', $1, $2, $3); }
		| prefix_expr '/' prefix_expr
		  { $$ = make_binary_op ('/', $1, $2, $3); }
		| prefix_expr EPLUS prefix_expr
		  { $$ = make_binary_op ('+', $1, $2, $3); }
		| prefix_expr EMINUS prefix_expr
		  { $$ = make_binary_op ('-', $1, $2, $3); }
		| prefix_expr EMUL prefix_expr
		  { $$ = make_binary_op (EMUL, $1, $2, $3); }
		| prefix_expr EDIV prefix_expr
		  { $$ = make_binary_op (EDIV, $1, $2, $3); }
		| prefix_expr LEFTDIV prefix_expr
		  { $$ = make_binary_op (LEFTDIV, $1, $2, $3); }
		| prefix_expr ELEFTDIV prefix_expr
		  { $$ = make_binary_op (ELEFTDIV, $1, $2, $3); }
		;

colon_expr	: colon_expr1
		  { $$ = finish_colon_expression ($1); }
		;

colon_expr1	: prefix_expr
		  { $$ = new tree_colon_expression ($1); }
		| colon_expr1 ':' prefix_expr
		  {
		    if (! ($$ = $1->append ($3)))
		      ABORT_PARSE;
		  }
		;

simple_expr	: colon_expr
		  { $$ = $1; }
		| simple_expr LSHIFT simple_expr
		  { $$ = make_binary_op (LSHIFT, $1, $2, $3); }
		| simple_expr RSHIFT simple_expr
		  { $$ = make_binary_op (RSHIFT, $1, $2, $3); }
		| simple_expr EXPR_LT simple_expr
		  { $$ = make_binary_op (EXPR_LT, $1, $2, $3); }
		| simple_expr EXPR_LE simple_expr
		  { $$ = make_binary_op (EXPR_LE, $1, $2, $3); }
		| simple_expr EXPR_EQ simple_expr
		  { $$ = make_binary_op (EXPR_EQ, $1, $2, $3); }
		| simple_expr EXPR_GE simple_expr
		  { $$ = make_binary_op (EXPR_GE, $1, $2, $3); }
		| simple_expr EXPR_GT simple_expr
		  { $$ = make_binary_op (EXPR_GT, $1, $2, $3); }
		| simple_expr EXPR_NE simple_expr
		  { $$ = make_binary_op (EXPR_NE, $1, $2, $3); }
		| simple_expr EXPR_AND simple_expr
		  { $$ = make_binary_op (EXPR_AND, $1, $2, $3); }
		| simple_expr EXPR_OR simple_expr
		  { $$ = make_binary_op (EXPR_OR, $1, $2, $3); }
		| simple_expr EXPR_AND_AND simple_expr
		  { $$ = make_boolean_op (EXPR_AND_AND, $1, $2, $3); }
		| simple_expr EXPR_OR_OR simple_expr
		  { $$ = make_boolean_op (EXPR_OR_OR, $1, $2, $3); }
		;

// Arrange for the lexer to return CLOSE_BRACE for `]' by looking ahead
// one token for an assignment op.

assign_lhs	: simple_expr
		  { $$ = new tree_argument_list ($1); }
		| '[' in_matrix_or_assign_lhs arg_list CLOSE_BRACE
		  {
		    $$ = $3;
		    lexer_flags.looking_at_matrix_or_assign_lhs = false;
		  }
		;

assign_expr	: assign_lhs '=' expression
		  { $$ = make_assign_op ('=', $1, $2, $3); }
		| assign_lhs ADD_EQ expression
		  { $$ = make_assign_op (ADD_EQ, $1, $2, $3); }
		| assign_lhs SUB_EQ expression
		  { $$ = make_assign_op (SUB_EQ, $1, $2, $3); }
		| assign_lhs MUL_EQ expression
		  { $$ = make_assign_op (MUL_EQ, $1, $2, $3); }
		| assign_lhs DIV_EQ expression
		  { $$ = make_assign_op (DIV_EQ, $1, $2, $3); }
		| assign_lhs LEFTDIV_EQ expression
		  { $$ = make_assign_op (LEFTDIV_EQ, $1, $2, $3); }
		| assign_lhs LSHIFT_EQ expression
		  { $$ = make_assign_op (LSHIFT_EQ, $1, $2, $3); }
		| assign_lhs RSHIFT_EQ expression
		  { $$ = make_assign_op (RSHIFT_EQ, $1, $2, $3); }
		| assign_lhs EMUL_EQ expression
		  { $$ = make_assign_op (EMUL_EQ, $1, $2, $3); }
		| assign_lhs EDIV_EQ expression
		  { $$ = make_assign_op (EDIV_EQ, $1, $2, $3); }
		| assign_lhs ELEFTDIV_EQ expression
		  { $$ = make_assign_op (ELEFTDIV_EQ, $1, $2, $3); }
		| assign_lhs AND_EQ expression
		  { $$ = make_assign_op (AND_EQ, $1, $2, $3); }
		| assign_lhs OR_EQ expression
		  { $$ = make_assign_op (OR_EQ, $1, $2, $3); }
		;

word_list_cmd	: identifier word_list
		  { $$ = make_index_expression ($1, $2); }
		;

word_list	: TEXT
		  {
		    tree_constant *tmp = make_constant (TEXT, $1);
		    $$ = new tree_argument_list (tmp);
		  }
		| word_list TEXT
		  {
		    tree_constant *tmp = make_constant (TEXT, $2);
		    $1->append (tmp);
		    $$ = $1;
		  }
		;

expression	: simple_expr
		  { $$ = $1; }
		| word_list_cmd
		  { $$ = $1; }
		| assign_expr
		  { $$ = $1; }
		;

// ================================================
// Commands, declarations, and function definitions
// ================================================

command		: declaration
		  { $$ = $1; }
		| select_command
		  { $$ = $1; }
		| loop_command
		  { $$ = $1; }
		| jump_command
		  { $$ = $1; }
		| except_command
		  { $$ = $1; }
		| function
		  { $$ = $1; }
		| plot_command
		  { $$ = $1; }
		;

// =====================
// Declaration statemnts
// =====================

declaration	: GLOBAL decl1
		  { $$ = make_decl_command (GLOBAL, $1, $2); }
		| STATIC decl1
		  { $$ = make_decl_command (STATIC, $1, $2); }
		;

decl1		: decl2
		  { $$ = new tree_decl_init_list ($1); }
		| decl1 decl2
		  {
		    $1->append ($2);
		    $$ = $1;
		  }
		;

decl2		: identifier
		  { $$ = new tree_decl_elt ($1); }
		| identifier '=' expression
		  { $$ = new tree_decl_elt ($1, $3); }
		;

// ====================
// Selection statements
// ====================

select_command	: if_command
		  { $$ = $1; }
		| switch_command
		  { $$ = $1; }
		;

// ============
// If statement
// ============

if_command	: IF stash_comment if_cmd_list END
		  {
		    if (! ($$ = finish_if_command ($1, $3, $4, $2)))
		      ABORT_PARSE;
		  }
		;

if_cmd_list	: if_cmd_list1
		  { $$ = $1; }
		| if_cmd_list1 else_clause
		  {
		    $1->append ($2);
		    $$ = $1;
		  }
		;

if_cmd_list1	: expression opt_sep opt_list
		  { $$ = start_if_command ($1, $3); }
		| if_cmd_list1 elseif_clause
		  {
		    $1->append ($2);
		    $$ = $1;
		  }
		;

elseif_clause	: ELSEIF stash_comment opt_sep expression opt_sep opt_list
		  { $$ = make_elseif_clause ($4, $6, $2); }
		;

else_clause	: ELSE stash_comment opt_sep opt_list
		  {
		    $$ = new tree_if_clause ($4, $2);
		  }
		;

// ================
// Switch statement
// ================

switch_command	: SWITCH stash_comment expression opt_sep case_list END
		  {
		    if (! ($$ = finish_switch_command ($1, $3, $5, $6, $2)))
		      ABORT_PARSE;
		  }
		;

case_list	: case_list1
		  { $$ = $1; }
		| case_list1 default_case
		  {
		    $1->append ($2);
		    $$ = $1;
		  }		
		;

case_list1	: switch_case
		  { $$ = new tree_switch_case_list ($1); }
		| case_list1 switch_case
		  {
		    $1->append ($2);
		    $$ = $1;
		  }
		;

switch_case	: CASE stash_comment opt_sep expression opt_sep list
		  { $$ = make_switch_case ($4, $6, $2); }
		;

default_case	: OTHERWISE stash_comment opt_sep opt_list
		  {
		    $$ = new tree_switch_case ($4, $2);
		  }
		;

// =======
// Looping
// =======

loop_command	: WHILE stash_comment expression opt_sep opt_list END
		  {
		    if (! ($$ = make_while_command ($1, $3, $5, $6, $2)))
		      ABORT_PARSE;
		  }
		| DO stash_comment opt_sep opt_list UNTIL expression
		  {
		    if (! ($$ = make_do_until_command ($1, $4, $6, $2)))
		      ABORT_PARSE;
		  }
		| FOR stash_comment assign_lhs '=' expression opt_sep opt_list END
		  {
		    if (! ($$ = make_for_command ($1, $3, $5, $7, $8, $2)))
		      ABORT_PARSE;
		  }
		;

// =======
// Jumping
// =======

jump_command	: BREAK
		  {
		    if (! ($$ = make_break_command ($1)))
		      ABORT_PARSE;
		  }
		| CONTINUE
		  {
		    if (! ($$ = make_continue_command ($1)))
		      ABORT_PARSE;
		  }
		| FUNC_RET
		  {
		    if (! ($$ = make_return_command ($1)))
		      ABORT_PARSE;
		  }
		;

// ==========
// Exceptions
// ==========

except_command	: UNWIND stash_comment opt_sep opt_list CLEANUP
		  stash_comment opt_sep opt_list END
		  {
		    if (! ($$ = make_unwind_command ($1, $4, $8, $9, $2, $6)))
		      ABORT_PARSE;
		  }
		| TRY stash_comment opt_sep opt_list CATCH
		  stash_comment opt_sep opt_list END
		  {
		    if (! ($$ = make_try_command ($1, $4, $8, $9, $2, $6)))
		      ABORT_PARSE;
		  }
		;

// ===========================================
// Some `subroutines' for function definitions
// ===========================================

save_symtab	: // empty
		  {
		    if (symtab_context)
		      panic_impossible ();

		    symtab_context = curr_sym_tab;
		  }
		;
		   
global_symtab	: // empty
		  { curr_sym_tab = global_sym_tab; }
		;

local_symtab	: // empty
		  { curr_sym_tab = tmp_local_sym_tab; }
		;

in_return_list	: // empty
		  { lexer_flags.looking_at_return_list = true; }
		;

parsed_fcn_name	: // empty
		  { lexer_flags.parsed_function_name = true; }
		;

// ===========================
// List of function parameters
// ===========================

param_list_beg	: '('
		  { lexer_flags.looking_at_parameter_list = true; }
		;

param_list_end	: ')'
		  { lexer_flags.looking_at_parameter_list = false; }
		;

param_list	: param_list_beg param_list_end
		  {
		    lexer_flags.quote_is_transpose = false;
		    $$ = 0;
		  }
		| param_list_beg ELLIPSIS param_list_end
		  {
		    lexer_flags.quote_is_transpose = false;
		    tree_parameter_list *tmp = new tree_parameter_list ();
		    tmp->mark_varargs_only ();
		    $$ = tmp;
		  }
		| param_list1 param_list_end
		  {
		    lexer_flags.quote_is_transpose = false;
		    $1->mark_as_formal_parameters ();
		    $$ = $1;
		  }
		| param_list1 ',' ELLIPSIS param_list_end
		  {
		    lexer_flags.quote_is_transpose = false;
		    $1->mark_as_formal_parameters ();
		    $1->mark_varargs ();
		    $$ = $1;
		  }
		;

param_list1	: param_list_beg identifier
		  { $$ = new tree_parameter_list ($2); }
		| param_list1 ',' identifier
		  {
		    $1->append ($3);
		    $$ = $1;
		  }
		| param_list_beg error
		  {
		    yyerror ("invalid parameter list");
		    $$ = 0;
		    ABORT_PARSE;
		  }
		| param_list1 ',' error
		  {
		    yyerror ("invalid parameter list");
		    $$ = 0;
		    ABORT_PARSE;
		  }
		;

// ===================================
// List of function return value names
// ===================================

return_list_beg	: '[' in_return_list local_symtab
		;

return_list	: return_list_beg return_list_end
		  {
		    lexer_flags.looking_at_return_list = false;
		    $$ = new tree_parameter_list ();
		  }
		| return_list_beg ELLIPSIS return_list_end
		  {
		    lexer_flags.looking_at_return_list = false;
		    tree_parameter_list *tmp = new tree_parameter_list ();
		    tmp->mark_varargs_only ();
		    $$ = tmp;
		  }
		| return_list_beg return_list1 return_list_end
		  {
		    lexer_flags.looking_at_return_list = false;
		    $$ = $2;
		  }
		| return_list_beg return_list1 ',' ELLIPSIS return_list_end
		  {
		    lexer_flags.looking_at_return_list = false;
		    $2->mark_varargs ();
		    $$ = $2;
		  }
		;

return_list1	: identifier
		  { $$ = new tree_parameter_list ($1); }
		| return_list1 ',' identifier
		  {
		    $1->append ($3);
		    $$ = $1;
		  }
		;

return_list_end	: global_symtab ']'
		;

// ===================
// Function definition
// ===================

function_beg	: save_symtab FCN stash_comment global_symtab
		  { $$ = $3; }
		;

function	: function_beg function2
		  {
		    $2->stash_leading_comment ($1);
		    recover_from_parsing_function ();
		    $$ = 0;
		  }
		| function_beg identifier function1
		  {
		    finish_function ($2, $3, $1);
		    recover_from_parsing_function ();
		    $$ = 0;
		  }
		| function_beg return_list function1
		  {
		    finish_function ($2, $3, $1);
		    recover_from_parsing_function ();
		    $$ = 0;
		  }
		;

function1	: global_symtab '=' function2
		  { $$ = $3; }
		;

function2	: identifier local_symtab parsed_fcn_name function3
		  {
		    if (! ($$ = frob_function ($1, $4)))
		      ABORT_PARSE;
		  }
		;

function3	: param_list function4
		  { $$ = start_function ($1, $2); }
		| function4
		  { $$ = start_function (0, $1); }
		;

function4	: opt_sep opt_list function_end
		  { $$ = $2; }
		;

function_end	: END
		  {
		    if (end_token_ok ($1, token::function_end))
		      {
			if (reading_fcn_file)
			  check_for_garbage_after_fcn_def ();
		      }
		    else
		      ABORT_PARSE;
		  }
		| END_OF_INPUT
		  {
		    if (! (reading_fcn_file || reading_script_file))
		      YYABORT;
		  }
		;

// ========
// Plotting
// ========

plot_command	: PLOT
		  {
		    if (! ($$ = make_plot_command ($1, 0, 0)))
		      ABORT_PARSE;
		  }
		| PLOT ranges
		  {
		    if (! ($$ = make_plot_command ($1, $2, 0)))
		      ABORT_PARSE;
		  }
		| PLOT plot_command1
		  {
		    if (! ($$ = make_plot_command ($1, 0, $2)))
		      ABORT_PARSE;
		  }
		| PLOT ranges plot_command1
		  {
		    if (! ($$ = make_plot_command ($1, $2, $3)))
		      ABORT_PARSE;
		  }
		;

ranges		: ranges1
		  { $$ = new plot_limits ($1); }
		| ranges1 ranges1
		  { $$ = new plot_limits ($1, $2); }
		| ranges1 ranges1 ranges1
		  { $$ = new plot_limits ($1, $2, $3); }
		;

ranges1		: OPEN_BRACE expression COLON expression CLOSE_BRACE
		  { $$ = new plot_range ($2, $4); }
		| OPEN_BRACE COLON expression CLOSE_BRACE
		  { $$ = new plot_range (0, $3); }
		| OPEN_BRACE expression COLON CLOSE_BRACE
		  { $$ = new plot_range ($2, 0); }
		| OPEN_BRACE COLON CLOSE_BRACE
		  { $$ = new plot_range (); }
		| OPEN_BRACE CLOSE_BRACE
		  { $$ = new plot_range (); }
		;

plot_command1	: plot_command2
		  { $$ = new subplot_list ($1); }
		| plot_command1 ',' plot_command2
		  {
		    $1->append ($3);
		    $$ = $1;
		  }
		;

plot_command2	: expression
		  { $$ = new subplot ($1); }
		| expression plot_options
		  { $$ = $2->add_data ($1); }
		;

plot_options	: using
		  {
		    subplot *tmp = new subplot ();
		    $$ = tmp->add_clause ($1);
		  }
		| title
		  {
		    subplot *tmp = new subplot ();
		    $$ = tmp->add_clause ($1);
		  }
		| style
		  {
		    subplot *tmp = new subplot ();
		    $$ = tmp->add_clause ($1);
		  }
		| axes
		  {
		    subplot *tmp = new subplot ();
		    $$ = tmp->add_clause ($1);
		  }
		| plot_options using
		  {
		    if (! ($$ = $1->add_clause ($2)))
		      {
			yyerror ("only one using option may be specified");
			ABORT_PARSE;
		      }
		  }
		| plot_options title
		  {
		    if (! ($$ = $1->add_clause ($2)))
		      {
			yyerror ("only one title option my be specified");
			ABORT_PARSE;
		      }
		  }
		| plot_options style
		  {
		    if (! ($$ = $1->add_clause ($2)))
		      {
			yyerror ("only one style option my be specified");
			ABORT_PARSE;
		      }
		  }
		| plot_options axes
		  {
		    if (! ($$ = $1->add_clause ($2)))
		      {
			yyerror ("only one axes option may be specified");
			ABORT_PARSE;
		      }
		  }
		;

axes		: AXES AXES_TAG
		  {
		    lexer_flags.in_plot_axes = false;
		    $$ = new subplot_axes ($2->text ());
		  }
		;

using		: using1
		  {
		    lexer_flags.in_plot_using = false;
		    $$ = $1;
		  }
		| using1 expression
		  {
		    lexer_flags.in_plot_using = false;
		    $$ = $1->set_format ($2);
		  }
		;

using1		: USING expression
		  {
		    subplot_using *tmp = new subplot_using ();
		    $$ = tmp->add_qualifier ($2);
		  }
		| using1 COLON expression
		  { $$ = $1->add_qualifier ($3); }
		;

title		: TITLE expression
		  { $$ = $2; }
		;

style		: WITH STYLE
		  { $$ = new subplot_style ($2->text ()); }
		| WITH STYLE expression
		  { $$ = new subplot_style ($2->text (), $3); }
		| WITH STYLE expression expression
		  { $$ = new subplot_style ($2->text (), $3, $4); }
		;

// =============
// Miscellaneous
// =============

stash_comment	: // empty
		  { $$ = octave_comment_buffer::get_comment (); }
		;

parse_error	: LEXICAL_ERROR
		  { yyerror ("parse error"); }
		| error
		;

sep_no_nl	: ','
		  { $$ = ','; }
		| ';'
		  { $$ = ';'; }
		| sep_no_nl ','
		  { $$ = $1; }
		| sep_no_nl ';'
		  { $$ = $1; }
		;

opt_sep_no_nl	: // empty
		  { $$ = 0; }
		| sep_no_nl
		  { $$ = $1; }
		;

sep		: ','
		  { $$ = ','; }
		| ';'
		  { $$ = ';'; }
		| '\n'
		  { $$ = '\n'; }
		| sep ','
		  { $$ = $1; }
		| sep ';'
		  { $$ = $1; }
		| sep '\n'
		  { $$ = $1; }
		;

opt_sep		: // empty
		  { $$ = 0; }
		| sep
		  { $$ = $1; }
		;

%%

// Generic error messages.

static void
yyerror (const char *s)
{
  int err_col = current_input_column - 1;

  std::ostrstream output_buf;

  if (reading_fcn_file || reading_script_file)
    output_buf << "parse error near line " << input_line_number
	       << " of file " << curr_fcn_file_full_name;
  else
    output_buf << "parse error:";

  if (s && strcmp (s, "parse error") != 0)
    output_buf << "\n\n  " << s;

  output_buf << "\n\n";

  if (! current_input_line.empty ())
    {
      size_t len = current_input_line.length ();

      if (current_input_line[len-1] == '\n')
        current_input_line.resize (len-1);

// Print the line, maybe with a pointer near the error token.

      output_buf << ">>> " << current_input_line << "\n";

      if (err_col == 0)
	err_col = len;

      for (int i = 0; i < err_col + 3; i++)
	output_buf << " ";

      output_buf << "^";
    }

  output_buf << "\n" << std::ends;

  char *msg = output_buf.str ();

  parse_error ("%s", msg);

  delete [] msg;
}

// Error mesages for mismatched end tokens.

static void
end_error (const char *type, token::end_tok_type ettype, int l, int c)
{
  static const char *fmt
    = "`%s' command matched by `%s' near line %d column %d";

  switch (ettype)
    {
    case token::simple_end:
      error (fmt, type, "end", l, c);
      break;

    case token::for_end:
      error (fmt, type, "endfor", l, c);
      break;

    case token::function_end:
      error (fmt, type, "endfunction", l, c);
      break;

    case token::if_end:
      error (fmt, type, "endif", l, c);
      break;

    case token::switch_end:
      error (fmt, type, "endswitch", l, c); 
      break;

    case token::while_end:
      error (fmt, type, "endwhile", l, c); 
      break;

    case token::unwind_protect_end:
      error (fmt, type, "end_unwind_protect", l, c); 
      break;

    default:
      panic_impossible ();
      break;
    }
}

// Check to see that end tokens are properly matched.

static bool
end_token_ok (token *tok, token::end_tok_type expected)
{
  bool retval = true;

  token::end_tok_type ettype = tok->ettype ();

  if (ettype != expected && ettype != token::simple_end)
    {
      retval = false;

      yyerror ("parse error");

      int l = tok->line ();
      int c = tok->column ();

      switch (expected)
	{
	case token::for_end:
	  end_error ("for", ettype, l, c);
	  break;

	case token::function_end:
	  end_error ("function", ettype, l, c);
	  break;

	case token::if_end:
	  end_error ("if", ettype, l, c);
	  break;

	case token::try_catch_end:
	  end_error ("try", ettype, l, c);
	  break;

	case token::switch_end:
	  end_error ("switch", ettype, l, c);
	  break;

	case token::unwind_protect_end:
	  end_error ("unwind_protect", ettype, l, c);
	  break;

	case token::while_end:
	  end_error ("while", ettype, l, c);
	  break;

	default:
	  panic_impossible ();
	  break;
	}
    }

  return retval;
}

// Maybe print a warning if an assignment expression is used as the
// test in a logical expression.

static void
maybe_warn_assign_as_truth_value (tree_expression *expr)
{
  if (Vwarn_assign_as_truth_value
      && expr->is_assignment_expression ()
      && expr->paren_count () < 2)
    {
      warning ("suggest parenthesis around assignment used as truth value");
    }
}

// Maybe print a warning about switch labels that aren't constants.

static void
maybe_warn_variable_switch_label (tree_expression *expr)
{
  if (Vwarn_variable_switch_label && ! expr->is_constant ())
    {
      warning ("variable switch label");
    }
}

// Create a plot command.

static tree_plot_command *
make_plot_command (token *tok, plot_limits *range, subplot_list *list)
{
  if (range)
    {
      if (tok->pttype () == token::replot)
	{
	  yyerror ("cannot specify new ranges with replot");
	  return 0;
	}
    }
  else if (! list && tok->pttype () != token::replot)
    {
      yyerror ("must have something to plot");
      return 0;
    }

  lexer_flags.plotting = false;
  lexer_flags.past_plot_range = false;
  lexer_flags.in_plot_range = false;
  lexer_flags.in_plot_using = false;
  lexer_flags.in_plot_style = false;
  
  return new tree_plot_command (list, range, tok->pttype ());
}

static tree_expression *
fold (tree_binary_expression *e)
{
  tree_expression *retval = e;

  unwind_protect::begin_frame ("fold_binary_expression");

  unwind_protect_int (error_state);

  unwind_protect_bool (discard_error_messages);
  discard_error_messages = true;

  tree_expression *op1 = e->lhs ();
  tree_expression *op2 = e->rhs ();

  if (op1->is_constant () && op2->is_constant ())
    {
      octave_value tmp = e->rvalue ();

      if (! (error_state || warning_state))
	{
	  tree_constant *tc_retval = new tree_constant (tmp);

	  std::ostrstream buf;

	  tree_print_code tpc (buf);

	  e->accept (tpc);

	  buf << std::ends;

	  char *s = buf.str ();

	  tc_retval->stash_original_text (s);

	  delete [] s;

	  delete e;

	  retval = tc_retval;
	}
    }

  unwind_protect::run_frame ("fold_binary_expression");

  return retval;
}

static tree_expression *
fold (tree_unary_expression *e)
{
  tree_expression *retval = e;

  unwind_protect::begin_frame ("fold_unary_expression");

  unwind_protect_int (error_state);

  unwind_protect_bool (discard_error_messages);
  discard_error_messages = true;

  tree_expression *op = e->operand ();

  if (op->is_constant ())
    {
      octave_value tmp = e->rvalue ();

      if (! (error_state || warning_state))
	{
	  tree_constant *tc_retval = new tree_constant (tmp);

	  std::ostrstream buf;

	  tree_print_code tpc (buf);

	  e->accept (tpc);

	  buf << std::ends;

	  char *s = buf.str ();

	  tc_retval->stash_original_text (s);

	  delete [] s;

	  delete e;

	  retval = tc_retval;
	}
    }

  unwind_protect::run_frame ("fold_unary_expression");

  return retval;
}

// Finish building a range.

static tree_expression *
finish_colon_expression (tree_colon_expression *e)
{
  tree_expression *retval = e;

  unwind_protect::begin_frame ("finish_colon_expression");

  unwind_protect_int (error_state);

  unwind_protect_bool (discard_error_messages);
  discard_error_messages = true;

  tree_expression *base = e->base ();
  tree_expression *limit = e->limit ();
  tree_expression *incr = e->increment ();

  if (base)
    {
      if (limit)
	{
	  if (base->is_constant () && limit->is_constant ()
	      && (! incr || (incr && incr->is_constant ())))
	    {
	      octave_value tmp = e->rvalue ();

	      if (! (error_state || warning_state))
		{
		  tree_constant *tc_retval = new tree_constant (tmp);

		  std::ostrstream buf;

		  tree_print_code tpc (buf);

		  e->accept (tpc);

		  buf << std::ends;

		  char *s = buf.str ();

		  tc_retval->stash_original_text (s);

		  delete [] s;

		  delete e;

		  retval = tc_retval;
		}
	    }
	}
      else
	{
	  e->preserve_base ();
	  delete e;

	  // XXX FIXME XXX -- need to attempt constant folding here
	  // too (we need a generic way to do that).
	  retval = base;
	}
    }

  unwind_protect::run_frame ("finish_colon_expression");

  return retval;
}

// Make a constant.

static tree_constant *
make_constant (int op, token *tok_val)
{
  int l = tok_val->line ();
  int c = tok_val->column ();

  tree_constant *retval = 0;

  switch (op)
    {
    case NUM:
      {
	octave_value tmp (tok_val->number ());
	retval = new tree_constant (tmp, l, c);
	retval->stash_original_text (tok_val->text_rep ());
      }
      break;

    case IMAG_NUM:
      {
	octave_value tmp (Complex (0.0, tok_val->number ()));
	retval = new tree_constant (tmp, l, c);
	retval->stash_original_text (tok_val->text_rep ());
      }
      break;

    case TEXT:
      {
	octave_value tmp (tok_val->text ());
	retval = new tree_constant (tmp, l, c);
      }
      break;

    default:
      panic_impossible ();
      break;
    }

  return retval;
}

// Build a binary expression.

static tree_expression *
make_binary_op (int op, tree_expression *op1, token *tok_val,
		tree_expression *op2)
{
  octave_value::binary_op t = octave_value::unknown_binary_op;

  switch (op)
    {
    case POW:
      t = octave_value::op_pow;
      break;

    case EPOW:
      t = octave_value::op_el_pow;
      break;

    case '+':
      t = octave_value::op_add;
      break;

    case '-':
      t = octave_value::op_sub;
      break;

    case '*':
      t = octave_value::op_mul;
      break;

    case '/':
      t = octave_value::op_div;
      break;

    case EMUL:
      t = octave_value::op_el_mul;
      break;

    case EDIV:
      t = octave_value::op_el_div;
      break;

    case LEFTDIV:
      t = octave_value::op_ldiv;
      break;

    case ELEFTDIV:
      t = octave_value::op_el_ldiv;
      break;

    case LSHIFT:
      t = octave_value::op_lshift;
      break;

    case RSHIFT:
      t = octave_value::op_rshift;
      break;

    case EXPR_LT:
      t = octave_value::op_lt;
      break;

    case EXPR_LE:
      t = octave_value::op_le;
      break;

    case EXPR_EQ:
      t = octave_value::op_eq;
      break;

    case EXPR_GE:
      t = octave_value::op_ge;
      break;

    case EXPR_GT:
      t = octave_value::op_gt;
      break;

    case EXPR_NE:
      t = octave_value::op_ne;
      break;

    case EXPR_AND:
      t = octave_value::op_el_and;
      break;

    case EXPR_OR:
      t = octave_value::op_el_or;
      break;

    default:
      panic_impossible ();
      break;
    }

  int l = tok_val->line ();
  int c = tok_val->column ();

  tree_binary_expression *e
    = new tree_binary_expression (op1, op2, l, c, t);

  return fold (e);
}

// Build a boolean expression.

static tree_expression *
make_boolean_op (int op, tree_expression *op1, token *tok_val,
		 tree_expression *op2)
{
  tree_boolean_expression::type t;

  switch (op)
    {
    case EXPR_AND_AND:
      t = tree_boolean_expression::bool_and;
      break;

    case EXPR_OR_OR:
      t = tree_boolean_expression::bool_or;
      break;

    default:
      panic_impossible ();
      break;
    }

  int l = tok_val->line ();
  int c = tok_val->column ();

  tree_boolean_expression *e
    = new tree_boolean_expression (op1, op2, l, c, t);

  return fold (e);
}

// Build a prefix expression.

static tree_expression *
make_prefix_op (int op, tree_expression *op1, token *tok_val)
{
  octave_value::unary_op t = octave_value::unknown_unary_op;

  switch (op)
    {
    case EXPR_NOT:
      t = octave_value::op_not;
      break;

    case '-':
      t = octave_value::op_uminus;
      break;

    case PLUS_PLUS:
      t = octave_value::op_incr;
      break;

    case MINUS_MINUS:
      t = octave_value::op_decr;
      break;

    default:
      panic_impossible ();
      break;
    }

  int l = tok_val->line ();
  int c = tok_val->column ();

  tree_prefix_expression *e
    = new tree_prefix_expression (op1, l, c, t);

  return fold (e);
}

// Build a postfix expression.

static tree_expression *
make_postfix_op (int op, tree_expression *op1, token *tok_val)
{
  octave_value::unary_op t = octave_value::unknown_unary_op;

  switch (op)
    {
    case QUOTE:
      t = octave_value::op_hermitian;
      break;

    case TRANSPOSE:
      t = octave_value::op_transpose;
      break;

    case PLUS_PLUS:
      t = octave_value::op_incr;
      break;

    case MINUS_MINUS:
      t = octave_value::op_decr;
      break;

    default:
      panic_impossible ();
      break;
    }

  int l = tok_val->line ();
  int c = tok_val->column ();

  tree_postfix_expression *e
    = new tree_postfix_expression (op1, l, c, t);

  return fold (e);
}

// Build an unwind-protect command.

static tree_command *
make_unwind_command (token *unwind_tok, tree_statement_list *body,
		     tree_statement_list *cleanup, token *end_tok,
		     octave_comment_list *lc, octave_comment_list *mc)
{
  tree_command *retval = 0;

  if (end_token_ok (end_tok, token::unwind_protect_end))
    {
      octave_comment_list *tc = octave_comment_buffer::get_comment ();

      int l = unwind_tok->line ();
      int c = unwind_tok->column ();

      retval = new tree_unwind_protect_command (body, cleanup,
						lc, mc, tc, l, c);
    }

  return retval;
}

// Build a try-catch command.

static tree_command *
make_try_command (token *try_tok, tree_statement_list *body,
		  tree_statement_list *cleanup, token *end_tok,
		  octave_comment_list *lc, octave_comment_list *mc)
{
  tree_command *retval = 0;

  if (end_token_ok (end_tok, token::try_catch_end))
    {
      octave_comment_list *tc = octave_comment_buffer::get_comment ();

      int l = try_tok->line ();
      int c = try_tok->column ();

      retval = new tree_try_catch_command (body, cleanup,
					   lc, mc, tc, l, c);
    }

  return retval;
}

// Build a while command.

static tree_command *
make_while_command (token *while_tok, tree_expression *expr,
		    tree_statement_list *body, token *end_tok,
		    octave_comment_list *lc)
{
  tree_command *retval = 0;

  maybe_warn_assign_as_truth_value (expr);

  if (end_token_ok (end_tok, token::while_end))
    {
      octave_comment_list *tc = octave_comment_buffer::get_comment ();

      lexer_flags.looping--;

      int l = while_tok->line ();
      int c = while_tok->column ();

      retval = new tree_while_command (expr, body, lc, tc, l, c);
    }

  return retval;
}

// Build a do-until command.

static tree_command *
make_do_until_command (token *do_tok, tree_statement_list *body,
		       tree_expression *expr, octave_comment_list *lc)
{
  tree_command *retval = 0;

  maybe_warn_assign_as_truth_value (expr);

  octave_comment_list *tc = octave_comment_buffer::get_comment ();

  lexer_flags.looping--;

  int l = do_tok->line ();
  int c = do_tok->column ();

  retval = new tree_do_until_command (expr, body, lc, tc, l, c);

  return retval;
}

// Build a for command.

static tree_command *
make_for_command (token *for_tok, tree_argument_list *lhs,
		  tree_expression *expr, tree_statement_list *body,
		  token *end_tok, octave_comment_list *lc)
{
  tree_command *retval = 0;

  if (end_token_ok (end_tok, token::for_end))
    {
      octave_comment_list *tc = octave_comment_buffer::get_comment ();

      lexer_flags.looping--;

      int l = for_tok->line ();
      int c = for_tok->column ();

      if (lhs->length () == 1)
	{
	  tree_expression *tmp = lhs->remove_front ();

	  retval = new tree_simple_for_command (tmp, expr, body,
						lc, tc, l, c);

	  delete lhs;
	}
      else
	retval = new tree_complex_for_command (lhs, expr, body,
					       lc, tc, l, c);
    }

  return retval;
}

// Build a break command.

static tree_command *
make_break_command (token *break_tok)
{
  tree_command *retval = 0;

  int l = break_tok->line ();
  int c = break_tok->column ();

  if (lexer_flags.looping || lexer_flags.defining_func
      || reading_script_file || evaluating_function_body
      || evaluating_looping_command)
    retval = new tree_break_command (l, c);
  else
    retval = new tree_no_op_command ("break", l, c);

  return retval;
}

// Build a continue command.

static tree_command *
make_continue_command (token *continue_tok)
{
  tree_command *retval = 0;

  int l = continue_tok->line ();
  int c = continue_tok->column ();

  if (lexer_flags.looping || evaluating_looping_command)
    retval = new tree_continue_command (l, c);
  else
    retval = new tree_no_op_command ("continue", l, c);

  return retval;
}

// Build a return command.

static tree_command *
make_return_command (token *return_tok)
{
  tree_command *retval = 0;

  int l = return_tok->line ();
  int c = return_tok->column ();

  if (lexer_flags.defining_func || reading_script_file
      || evaluating_function_body)
    retval = new tree_return_command (l, c);
  else
    retval = new tree_no_op_command ("return", l, c);

  return retval;
}

// Start an if command.

static tree_if_command_list *
start_if_command (tree_expression *expr, tree_statement_list *list)
{
  maybe_warn_assign_as_truth_value (expr);

  tree_if_clause *t = new tree_if_clause (expr, list);

  return new tree_if_command_list (t);
}

// Finish an if command.

static tree_if_command *
finish_if_command (token *if_tok, tree_if_command_list *list,
		   token *end_tok, octave_comment_list *lc)
{
  tree_if_command *retval = 0;

  if (end_token_ok (end_tok, token::if_end))
    {
      octave_comment_list *tc = octave_comment_buffer::get_comment ();

      int l = if_tok->line ();
      int c = if_tok->column ();

      retval = new tree_if_command (list, lc, tc, l, c);
    }

  return retval;
}

// Build an elseif clause.

static tree_if_clause *
make_elseif_clause (tree_expression *expr, tree_statement_list *list,
		    octave_comment_list *lc)
{
  maybe_warn_assign_as_truth_value (expr);

  return new tree_if_clause (expr, list, lc);
}

// Finish a switch command.

static tree_switch_command *
finish_switch_command (token *switch_tok, tree_expression *expr,
		       tree_switch_case_list *list, token *end_tok,
		       octave_comment_list *lc)
{
  tree_switch_command *retval = 0;

  if (end_token_ok (end_tok, token::switch_end))
    {
      octave_comment_list *tc = octave_comment_buffer::get_comment ();

      int l = switch_tok->line ();
      int c = switch_tok->column ();

      retval = new tree_switch_command (expr, list, lc, tc, l, c);
    }

  return retval;
}

// Build a switch case.

static tree_switch_case *
make_switch_case (tree_expression *expr, tree_statement_list *list,
		  octave_comment_list *lc)
{
  maybe_warn_variable_switch_label (expr);

  return new tree_switch_case (expr, list, lc);
}

// Build an assignment to a variable.

static tree_expression *
make_assign_op (int op, tree_argument_list *lhs, token *eq_tok,
		tree_expression *rhs)
{
  tree_expression *retval = 0;

  octave_value::assign_op t = octave_value::unknown_assign_op;

  switch (op)
    {
    case '=':
      t = octave_value::op_asn_eq;
      break;

    case ADD_EQ:
      t = octave_value::op_add_eq;
      break;

    case SUB_EQ:
      t = octave_value::op_sub_eq;
      break;

    case MUL_EQ:
      t = octave_value::op_mul_eq;
      break;

    case DIV_EQ:
      t = octave_value::op_div_eq;
      break;

    case LEFTDIV_EQ:
      t = octave_value::op_ldiv_eq;
      break;

    case LSHIFT_EQ:
      t = octave_value::op_lshift_eq;
      break;

    case RSHIFT_EQ:
      t = octave_value::op_rshift_eq;
      break;

    case EMUL_EQ:
      t = octave_value::op_el_mul_eq;
      break;

    case EDIV_EQ:
      t = octave_value::op_el_div_eq;
      break;

    case ELEFTDIV_EQ:
      t = octave_value::op_el_ldiv_eq;
      break;

    case AND_EQ:
      t = octave_value::op_el_and_eq;
      break;

    case OR_EQ:
      t = octave_value::op_el_or_eq;
      break;

    default:
      panic_impossible ();
      break;
    }

  int l = eq_tok->line ();
  int c = eq_tok->column ();

  if (lhs->length () == 1)
    {
      tree_expression *tmp = lhs->remove_front ();

      retval = new tree_simple_assignment (tmp, rhs, false, l, c, t);

      delete lhs;
    }
  else
    return new tree_multi_assignment (lhs, rhs, false, l, c, t);

  return retval;
}

// Begin defining a function.

static octave_user_function *
start_function (tree_parameter_list *param_list, tree_statement_list *body)
{
  body->mark_as_function_body ();

  // We'll fill in the return list later.

  octave_user_function *fcn
    = new octave_user_function (param_list, 0, body, curr_sym_tab);

  if (fcn)
    {
      octave_comment_list *tc = octave_comment_buffer::get_comment ();

      fcn->stash_trailing_comment (tc);
    }

  return fcn;
}

// Do most of the work for defining a function.

static octave_user_function *
frob_function (tree_identifier *id, octave_user_function *fcn)
{
  std::string id_name = id->name ();

  // If input is coming from a file, issue a warning if the name of
  // the file does not match the name of the function stated in the
  // file.  Matlab doesn't provide a diagnostic (it ignores the stated
  // name).

  fcn->stash_function_name (id_name);

  if (reading_fcn_file)
    {
      if (curr_fcn_file_name != id_name)
	{
	  if (Vwarn_function_name_clash)
	    warning ("function name `%s' does not agree with function\
 file name `%s'", id_name.c_str (), curr_fcn_file_full_name.c_str ());

	  global_sym_tab->rename (id_name, curr_fcn_file_name);

	  if (error_state)
	    return 0;

	  id_name = id->name ();
	}

      octave_time now;

      fcn->stash_function_name (id_name);
      fcn->stash_fcn_file_name ();
      fcn->stash_fcn_file_time (now);
      fcn->mark_as_system_fcn_file ();

      if (Vwarn_future_time_stamp)
	{
	  std::string nm = fcn->fcn_file_name ();

	  file_stat fs (nm);

	  if (fs && fs.is_newer (now))
	    warning ("time stamp for `%s' is in the future", nm.c_str ());
	}
    }
  else if (! (input_from_tmp_history_file || input_from_startup_file)
	   && reading_script_file
	   && curr_fcn_file_name == id_name)
    {
      warning ("function `%s' defined within script file `%s'",
	       id_name.c_str (), curr_fcn_file_full_name.c_str ());
    }

  top_level_sym_tab->clear (id_name);

  symbol_record *sr = global_sym_tab->lookup (id_name);

  if (sr)
    fcn->stash_symtab_ptr (sr);
  else
    panic_impossible ();

  id->define (fcn, symbol_record::USER_FUNCTION);

  id->document (help_buf);

  help_buf.resize (0);

  return fcn;
}

// Finish defining a function.

static octave_user_function *
finish_function (tree_identifier *id, octave_user_function *fcn,
		 octave_comment_list *lc)
{
  tree_parameter_list *tpl = new tree_parameter_list (id);

  tpl->mark_as_formal_parameters ();

  fcn->stash_leading_comment (lc);

  return fcn->define_ret_list (tpl);
}

// Finish defining a function a different way.

static octave_user_function *
finish_function (tree_parameter_list *ret_list,
		 octave_user_function *fcn, octave_comment_list *lc)
{
  ret_list->mark_as_formal_parameters ();

  fcn->stash_leading_comment (lc);

  return fcn->define_ret_list (ret_list);
}

static void
recover_from_parsing_function (void)
{
  if (! symtab_context)
    panic_impossible ();

  curr_sym_tab = symtab_context;
  symtab_context = 0;

  lexer_flags.defining_func = false;
  lexer_flags.beginning_of_function = false;
  lexer_flags.parsed_function_name = false;
  lexer_flags.looking_at_return_list = false;
  lexer_flags.looking_at_parameter_list = false;
}

// Make an index expression.

static tree_index_expression *
make_index_expression (tree_expression *expr, tree_argument_list *args)
{
  tree_index_expression *retval = 0;

  int l = expr->line ();
  int c = expr->column ();

  expr->mark_postfix_indexed ();

  retval =  new tree_index_expression (expr, args, l, c);

  return retval;
}

// Make an indirect reference expression.

static tree_indirect_ref *
make_indirect_ref (tree_expression *expr, const std::string& elt)
{
  tree_indirect_ref *retval = 0;

  int l = expr->line ();
  int c = expr->column ();

  retval = new tree_indirect_ref (expr, elt, l, c);

  lexer_flags.looking_at_indirect_ref = false;

  return retval;
}

// Make a declaration command.

static tree_decl_command *
make_decl_command (int tok, token *tok_val, tree_decl_init_list *lst)
{
  tree_decl_command *retval = 0;

  int l = tok_val->line ();
  int c = tok_val->column ();

  switch (tok)
    {
    case GLOBAL:
      retval = new tree_global_command (lst, l, c);
      break;

    case STATIC:
      if (lexer_flags.defining_func)
	retval = new tree_static_command (lst, l, c);
      else
	{
	  if (reading_script_file)
	    warning ("ignoring static declaration near line %d of file `%s'",
		     l, curr_fcn_file_full_name.c_str ());
	  else
	    warning ("ignoring static declaration near line %d", l);
	}
      break;

    default:
      panic_impossible ();
      break;
    }

  return retval;
}

// Finish building a matrix list.

static tree_expression *
finish_matrix (tree_matrix *m)
{
  tree_expression *retval = m;

  unwind_protect::begin_frame ("finish_matrix");

  unwind_protect_int (error_state);

  unwind_protect_bool (discard_error_messages);
  discard_error_messages = true;

  if (m->all_elements_are_constant ())
    {
      octave_value tmp = m->rvalue ();

      if (! (error_state || warning_state))
	{
	  tree_constant *tc_retval = new tree_constant (tmp);

	  std::ostrstream buf;

	  tree_print_code tpc (buf);

	  m->accept (tpc);

	  buf << std::ends;

	  char *s = buf.str ();

	  tc_retval->stash_original_text (s);

	  delete [] s;

	  delete m;

	  retval = tc_retval;
	}
    }

  unwind_protect::run_frame ("finish_matrix");

  return retval;
}

// Finish building a cell list.

static tree_expression *
finish_cell (tree_cell *c)
{
  // For now, this doesn't do anything.

  return c;
}

static void
maybe_warn_missing_semi (tree_statement_list *t)
{
  if (lexer_flags.defining_func && Vwarn_missing_semicolon)
    {
      tree_statement *tmp = t->rear();

      if (tmp->is_expression ())
	warning ("missing semicolon near line %d, column %d in file `%s'",
		 tmp->line (), tmp->column (),
		 curr_fcn_file_full_name.c_str ());
    }
}

static void
set_stmt_print_flag (tree_statement_list *list, char sep,
		     bool warn_missing_semi)
{
  switch (sep)
    {
    case ';':
      {
	tree_statement *tmp = list->rear ();
	tmp->set_print_flag (0);
      }
      break;

    case 0:
    case ',':
    case '\n':
      if (warn_missing_semi)
	maybe_warn_missing_semi (list);
      break;

    default:
      warning ("unrecognized separator type!");
      break;
    }
}

void
parse_and_execute (FILE *f)
{
  unwind_protect::begin_frame ("parse_and_execute");

  YY_BUFFER_STATE old_buf = current_buffer ();
  YY_BUFFER_STATE new_buf = create_buffer (f);

  unwind_protect::add (restore_input_buffer, old_buf);
  unwind_protect::add (delete_input_buffer, new_buf);

  switch_to_buffer (new_buf);

  unwind_protect_bool (line_editing);
  unwind_protect_bool (input_from_command_line_file);
  unwind_protect_bool (get_input_from_eval_string);
  unwind_protect_bool (parser_end_of_input);

  line_editing = false;
  input_from_command_line_file = false;
  get_input_from_eval_string = false;
  parser_end_of_input = false;

  unwind_protect_ptr (curr_sym_tab);

  int retval;
  do
    {
      reset_parser ();

      retval = yyparse ();

      if (retval == 0)
        {
          if (global_command)
	    {
	      global_command->eval ();

	      delete global_command;

	      global_command = 0;

	      bool quit = (tree_return_command::returning
			   || tree_break_command::breaking);

	      if (tree_return_command::returning)
		tree_return_command::returning = 0;

	      if (tree_break_command::breaking)
		tree_break_command::breaking--;

	      if (error_state)
		{
		  error ("near line %d of file `%s'", input_line_number,
			 curr_fcn_file_full_name.c_str ());

		  break;
		}

	      if (quit)
		break;
	    }
	  else if (parser_end_of_input)
	    break;
        }
    }
  while (retval == 0);

  unwind_protect::run_frame ("parse_and_execute");
}

static void
safe_fclose (void *f)
{
  // XXX FIXME XXX -- comments at the end of an input file are
  // discarded (otherwise, they would be appended to the next
  // statement, possibly from the command line or another file, which
  // can be quite confusing).

  octave_comment_buffer::get_comment ();

  if (f)
    fclose (static_cast<FILE *> (f));
}

void
parse_and_execute (const std::string& s, bool verbose, const char *warn_for)
{
  unwind_protect::begin_frame ("parse_and_execute_2");

  unwind_protect_bool (reading_script_file);
  unwind_protect_str (curr_fcn_file_full_name);

  reading_script_file = true;
  curr_fcn_file_full_name = s;

  FILE *f = get_input_from_file (s, 0);

  if (f)
    {
      unwind_protect::add (safe_fclose, f);

      unwind_protect_int (input_line_number);
      unwind_protect_int (current_input_column);

      input_line_number = 0;
      current_input_column = 1;

      if (verbose)
	{
	  std::cout << "reading commands from " << s << " ... ";
	  reading_startup_message_printed = true;
	  std::cout.flush ();
	}

      parse_and_execute (f);

      if (verbose)
	std::cout << "done." << std::endl;
    }
  else if (warn_for)
    error ("%s: unable to open file `%s'", warn_for, s.c_str ());

  unwind_protect::run_frame ("parse_and_execute_2");
}

static bool
looks_like_octave_copyright (const std::string& s)
{
  bool retval = false;

  std::string t = s.substr (0, 14);

  if (t == "Copyright (C) ")
    {
      size_t pos = s.find ('\n');

      if (pos != NPOS)
	{
	  pos = s.find ('\n', pos + 1);

	  if (pos != NPOS)
	    {
	      pos++;

	      t = s.substr (pos, 28);

	      if (t == "This file is part of Octave."
		  || t == "This program is free softwar")
		retval = true;
	    }
	}
    }

  return retval;
}

// Eat whitespace and comments from FFILE, returning the text of the
// comments read if it doesn't look like a copyright notice.  If
// IN_PARTS, consider each block of comments separately; otherwise,
// grab them all at once.  If UPDATE_POS is TRUE, line and column
// number information is updated.  If SAVE_COPYRIGHT is TRUE, then
// comments that are recognized as a copyright notice are saved in the
// comment buffer.

// XXX FIXME XXX -- grab_help_text() in lex.l duplicates some of this
// code!

static std::string
gobble_leading_white_space (FILE *ffile, bool in_parts,
			    bool update_pos, bool save_copyright)
{
  std::string help_txt;

  // TRUE means we have already seen the first block of comments.
  bool first_comments_seen = false;

  // TRUE means we are at the beginning of a comment block.
  bool begin_comment = false;

  // TRUE means we have already cached the help text.
  bool have_help_text = false;

  // TRUE means we are currently reading a comment block.
  bool in_comment = false;

  // TRUE means we should discard the first space from the input
  // (used to strip leading spaces from the help text).
  bool discard_space = true;

  int c;

  while ((c = getc (ffile)) != EOF)
    {
      if (update_pos)
	current_input_column++;

      if (begin_comment)
	{
	  if (c == '%' || c == '#')
	    continue;
	  else if (discard_space && c == ' ')
	    {
	      discard_space = false;
	      continue;
	    }
	  else
	    begin_comment = false;
	}

      if (in_comment)
	{
	  if (! have_help_text)
	    {
	      first_comments_seen = true;
	      help_txt += (char) c;
	    }

	  if (c == '\n')
	    {
	      if (update_pos)
		{
		  input_line_number++;
		  current_input_column = 0;
		}

	      in_comment = false;
	      discard_space = true;

	      if (in_parts)
		{
		  if ((c = getc (ffile)) != EOF)
		    {
		      if (update_pos)
			current_input_column--;
		      ungetc (c, ffile);
		      if (c == '\n')
			break;
		    }
		  else
		    break;
		}
	    }
	}
      else
	{
	  switch (c)
	    {
	    case ' ':
	    case '\t':
	      if (first_comments_seen)
		have_help_text = true;
	      break;

	    case '%':
	    case '#':
	      begin_comment = true;
	      in_comment = true;
	      break;

	    case '\n':
	      if (first_comments_seen)
		have_help_text = true;
	      if (update_pos)
		{
		  input_line_number++;
		  current_input_column = 0;
		}
	      continue;

	    case '\r':
	      c = getc (ffile);
	      if (update_pos)
		current_input_column++;
	      if (c == EOF)
		goto done;
	      else if (c == '\n')
		{
		  if (first_comments_seen)
		    have_help_text = true;
		  if (update_pos)
		    {
		      input_line_number++;
		      current_input_column = 0;
		    } 
		  continue;
		}

	      // Fall through...

	    default:
	      if (update_pos)
		current_input_column--;
	      ungetc (c, ffile);
	      goto done;
	    }
	}
    }

 done:

  if (! help_txt.empty ())
    {
      if (looks_like_octave_copyright (help_txt))
	{
	  if (save_copyright)
	    octave_comment_buffer::append (help_txt);

	  help_txt.resize (0);
	}

      if (in_parts && help_txt.empty ())
	help_txt = gobble_leading_white_space (ffile, in_parts,
					       update_pos, false);
    }

  return help_txt;
}

std::string
get_help_from_file (const std::string& path)
{
  std::string retval;

  if (! path.empty ())
    {
      FILE *fptr = fopen (path.c_str (), "r");

      if (fptr)
	{
	  unwind_protect::add (safe_fclose, (void *) fptr);

	  retval = gobble_leading_white_space (fptr, true, true, false);

	  unwind_protect::run ();
	}
    }

  return retval;
}

static int
is_function_file (FILE *ffile)
{
  int status = 0;

  long pos = ftell (ffile);

  gobble_leading_white_space (ffile, false, false, false);

  char buf [10];
  fgets (buf, 10, ffile);
  int len = strlen (buf);
  if (len > 8 && strncmp (buf, "function", 8) == 0
      && ! (isalnum (buf[8]) || buf[8] == '_'))
    status = 1;

  fseek (ffile, pos, SEEK_SET);

  return status;
}

static void
restore_command_history (void *)
{
  command_history::ignore_entries (! Vsaving_history);
}

static void
restore_input_stream (void *f)
{
  command_editor::set_input_stream (static_cast<FILE *> (f));
}

static void
clear_current_script_file_name (void *)
{
  bind_builtin_variable ("current_script_file_name", octave_value ());
}

static bool
parse_fcn_file (const std::string& ff, bool exec_script, bool force_script = false)
{
  unwind_protect::begin_frame ("parse_fcn_file");

  int script_file_executed = false;

  // Open function file and parse.

  bool old_reading_fcn_file_state = reading_fcn_file;

  FILE *in_stream = command_editor::get_input_stream ();

  unwind_protect::add (restore_input_stream, in_stream);

  unwind_protect_ptr (ff_instream);

  unwind_protect_int (input_line_number);
  unwind_protect_int (current_input_column);
  unwind_protect_bool (reading_fcn_file);
  unwind_protect_bool (line_editing);

  input_line_number = 0;
  current_input_column = 1;
  reading_fcn_file = true;
  line_editing = false;

  FILE *ffile = get_input_from_file (ff, 0);

  unwind_protect::add (safe_fclose, ffile);

  if (ffile)
    {
      // Check to see if this file defines a function or is just a
      // list of commands.

      if (! force_script && is_function_file (ffile))
	{
	  // XXX FIXME XXX -- we shouldn't need both the
	  // command_history object and the
	  // Vsaving_history variable...
	  command_history::ignore_entries ();

	  unwind_protect::add (restore_command_history, 0);

	  unwind_protect_int (Vecho_executing_commands);
	  unwind_protect_bool (Vsaving_history);
	  unwind_protect_bool (reading_fcn_file);
	  unwind_protect_bool (input_from_command_line_file);
	  unwind_protect_bool (get_input_from_eval_string);
	  unwind_protect_bool (parser_end_of_input);

	  Vecho_executing_commands = ECHO_OFF;
	  Vsaving_history = false;
	  reading_fcn_file = true;
	  input_from_command_line_file = false;
	  get_input_from_eval_string = false;
	  parser_end_of_input = false;

	  YY_BUFFER_STATE old_buf = current_buffer ();
	  YY_BUFFER_STATE new_buf = create_buffer (ffile);

	  unwind_protect::add (restore_input_buffer, (void *) old_buf);
	  unwind_protect::add (delete_input_buffer, (void *) new_buf);

	  switch_to_buffer (new_buf);

	  unwind_protect_ptr (curr_sym_tab);

	  reset_parser ();

	  help_buf = gobble_leading_white_space (ffile, true, true, true);

	  octave_comment_buffer::append (help_buf);

	  // XXX FIXME XXX -- this should not be necessary.
	  gobble_leading_white_space (ffile, false, true, false);

	  int status = yyparse ();

	  if (status != 0)
	    {
	      error ("parse error while reading function file %s",
		     ff.c_str ());
	      global_sym_tab->clear (curr_fcn_file_name);
	    }
	}
      else if (exec_script)
	{
	  // The value of `reading_fcn_file' will be restored to the
	  // proper value when we unwind from this frame.
	  reading_fcn_file = old_reading_fcn_file_state;

	  // XXX FIXME XXX -- we shouldn't need both the
	  // command_history object and the
	  // Vsaving_history variable...
	  command_history::ignore_entries ();

	  unwind_protect::add (restore_command_history, 0);

	  unwind_protect_bool (Vsaving_history);
	  unwind_protect_bool (reading_script_file);

	  Vsaving_history = false;
	  reading_script_file = true;

	  unwind_protect::add (clear_current_script_file_name, 0);

	  bind_builtin_variable ("current_script_file_name", ff);

	  parse_and_execute (ffile);

	  script_file_executed = true;
	}
    }
  else
    error ("no such file, `%s'", ff.c_str ());

  unwind_protect::run_frame ("parse_fcn_file");

  return script_file_executed;
}

bool
load_fcn_from_file (symbol_record *sym_rec, bool exec_script)
{
  bool script_file_executed = false;

  std::string nm = sym_rec->name ();

  if (octave_dynamic_loader::load (nm))
    {
      force_link_to_function (nm);
    }
  else
    {
      std::string ff = fcn_file_in_path (nm);

      // These are needed by yyparse.

      unwind_protect::begin_frame ("load_fcn_from_file");

      unwind_protect_str (curr_fcn_file_name);
      unwind_protect_str (curr_fcn_file_full_name);

      curr_fcn_file_name = nm;
      curr_fcn_file_full_name = ff;

      if (ff.length () > 0)
	script_file_executed = parse_fcn_file (ff, exec_script);

      if (! (error_state || script_file_executed))
	force_link_to_function (nm);

      unwind_protect::run_frame ("load_fcn_from_file");
    }

  return script_file_executed;
}

DEFUN (source, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} source (@var{file})\n\
Parse and execute the contents of @var{file}.  This is equivalent to\n\
executing commands from a script file, but without requiring the file to\n\
be named @file{@var{file}.m}.\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin == 1)
    {
      std::string file_name = args(0).string_value ();

      if (! error_state)
	{
	  std::string file_full_name = file_ops::tilde_expand (file_name);

	  unwind_protect::begin_frame ("Fsource");

	  unwind_protect_str (curr_fcn_file_name);
	  unwind_protect_str (curr_fcn_file_full_name);

	  curr_fcn_file_name = file_name;
	  curr_fcn_file_full_name = file_full_name;

	  parse_fcn_file (file_full_name, true, true);

	  if (error_state)
	    error ("source: error sourcing file `%s'",
		   file_full_name.c_str ());

	  unwind_protect::run_frame ("Fsource");
	}
      else
	error ("source: expecting file name as argument");
    }
  else
    print_usage ("source");

  return retval;
}

// Evaluate an Octave function (built-in or interpreted) and return
// the list of result values.  NAME is the name of the function to
// call.  ARGS are the arguments to the function.  NARGOUT is the
// number of output arguments expected. 

octave_value_list
feval (const std::string& name, const octave_value_list& args, int nargout)
{
  octave_value_list retval;

  octave_function *fcn = is_valid_function (name, "feval", 1);

  if (fcn)
    retval = fcn->do_multi_index_op (nargout, args);

  return retval;
}

// Evaluate an Octave function (built-in or interpreted) and return
// the list of result values.  The first element of ARGS should be a
// string containing the name of the function to call, then the rest
// are the actual arguments to the function.  NARGOUT is the number of
// output arguments expected.

octave_value_list
feval (const octave_value_list& args, int nargout)
{
  octave_value_list retval;

  if (args.length () > 0)
    {
      std::string name = args(0).string_value ();

      if (! error_state)
	{
	  int tmp_nargin = args.length () - 1;

	  octave_value_list tmp_args (tmp_nargin, octave_value ());

	  for (int i = 0; i < tmp_nargin; i++)
	    tmp_args(i) = args(i+1);

	  string_vector arg_names = args.name_tags ();

	  if (! arg_names.empty ())
	    {
	      // tmp_nargin and arg_names.length () - 1 may differ if
	      // we are passed all_va_args.

	      int n = arg_names.length () - 1;

	      int len = n > tmp_nargin ? tmp_nargin : n;

	      string_vector tmp_arg_names (len);

	      for (int i = 0; i < len; i++)
		tmp_arg_names(i) = arg_names(i+1);

	      tmp_args.stash_name_tags (tmp_arg_names);
	    }

	  retval = feval (name, tmp_args, nargout);
	}
    }

  return retval;
}

DEFUN (feval, args, nargout,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} feval (@var{name}, @dots{})\n\
Evaluate the function named @var{name}.  Any arguments after the first\n\
are passed on to the named function.  For example,\n\
\n\
@example\n\
feval (\"acos\", -1)\n\
     @result{} 3.1416\n\
@end example\n\
\n\
@noindent\n\
calls the function @code{acos} with the argument @samp{-1}.\n\
\n\
The function @code{feval} is necessary in order to be able to write\n\
functions that call user-supplied functions, because Octave does not\n\
have a way to declare a pointer to a function (like C) or to declare a\n\
special kind of variable that can be used to hold the name of a function\n\
(like @code{EXTERNAL} in Fortran).  Instead, you must refer to functions\n\
by name, and use @code{feval} to call them.\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin > 0)
    retval = feval (args, nargout);
  else
    print_usage ("feval");

  return retval;
}

octave_value_list
eval_string (const std::string& s, bool silent, int& parse_status, int nargout)
{
  octave_value_list retval;

  unwind_protect::begin_frame ("eval_string");

  unwind_protect_bool (get_input_from_eval_string);
  unwind_protect_bool (input_from_eval_string_pending);
  unwind_protect_bool (input_from_command_line_file);
  unwind_protect_bool (parser_end_of_input);
  unwind_protect_str (current_eval_string);

  get_input_from_eval_string = true;
  input_from_eval_string_pending = true;
  input_from_command_line_file = false;
  parser_end_of_input = false;
  current_eval_string = s;

  unwind_protect_ptr (global_command);

  YY_BUFFER_STATE old_buf = current_buffer ();
  YY_BUFFER_STATE new_buf = create_buffer (0);

  unwind_protect::add (restore_input_buffer, old_buf);
  unwind_protect::add (delete_input_buffer, new_buf);

  switch_to_buffer (new_buf);

  unwind_protect_ptr (curr_sym_tab);

  do
    {
      parse_status = yyparse ();

      tree_statement_list *command = global_command;

      if (parse_status == 0)
        {
	  if (command)
	    {
	      retval = command->eval (silent, nargout);

	      delete command;

	      command = 0;

	      if (error_state
		  || tree_return_command::returning
		  || tree_break_command::breaking
		  || tree_continue_command::continuing)
		break;
	    }
	  else if (parser_end_of_input)
	    break;
        }
    }
  while (parse_status == 0);

  unwind_protect::run_frame ("eval_string");

  return retval;
}

octave_value
eval_string (const std::string& s, bool silent, int& parse_status)
{
  octave_value retval;

  octave_value_list tmp = eval_string (s, silent, parse_status, 1);

  if (! tmp.empty ())
    retval = tmp(0);

  return retval;
}

static octave_value_list
eval_string (const octave_value& arg, bool silent, int& parse_status,
	     int nargout)
{
  std::string s = arg.string_value ();

  if (error_state)
    {
      error ("eval: expecting std::string argument");
      return -1.0;
    }

  return eval_string (s, silent, parse_status, nargout);
}

DEFUN (eval, args, nargout,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} eval (@var{try}, @var{catch})\n\
Parse the string @var{try} and evaluate it as if it were an Octave\n\
program, returning the last value computed.  If that fails, evaluate\n\
the string @var{catch}.  The string @var{try} is evaluated in the\n\
current context, so any results remain available after @code{eval}\n\
returns.  For example,\n\
\n\
@example\n\
@group\n\
eval (\"a = 13\")\n\
     @print{} a = 13\n\
     @result{} 13\n\
@end group\n\
@end example\n\
\n\
In this case, the value of the evaluated expression is printed and it is\n\
also returned returned from @code{eval}.  Just as with any other\n\
expression, you can turn printing off by ending the expression in a\n\
semicolon.  For example,\n\
\n\
@example\n\
eval (\"a = 13;\")\n\
     @result{} 13\n\
@end example\n\
\n\
In this example, the variable @code{a} has been given the value 13, but\n\
the value of the expression is not printed.  You can also turn off\n\
automatic printing for all expressions executed by @code{eval} using the\n\
variable @code{default_eval_print_flag}.\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin > 0)
    {
      unwind_protect::begin_frame ("Feval");

      if (nargin > 1)
	{
	  unwind_protect_bool (buffer_error_messages);
	  buffer_error_messages = true;
	}

      int parse_status = 0;

      retval = eval_string (args(0), ! Vdefault_eval_print_flag,
			    parse_status, nargout);

      if (nargin > 1 && (parse_status != 0 || error_state))
	{
	  error_state = 0;

	  // Set up for letting the user print any messages from
	  // errors that occurred in the first part of this eval().

	  buffer_error_messages = false;

	  bind_global_error_variable ();

	  unwind_protect::add (clear_global_error_variable, 0);

	  eval_string (args(1), 0, parse_status, nargout);

	  retval = octave_value_list ();
	}

      unwind_protect::run_frame ("Feval");
    }
  else
    print_usage ("eval");

  return retval;
}

static int
default_eval_print_flag (void)
{
  Vdefault_eval_print_flag = check_preference ("default_eval_print_flag");

  return 0;
}

static int
warn_assign_as_truth_value (void)
{
  Vwarn_assign_as_truth_value
    = check_preference ("warn_assign_as_truth_value");

  return 0;
}

static int
warn_function_name_clash (void)
{
  Vwarn_function_name_clash = check_preference ("warn_function_name_clash");

  return 0;
}

static int
warn_future_time_stamp (void)
{
  Vwarn_future_time_stamp = check_preference ("warn_future_time_stamp");

  return 0;
}

static int
warn_missing_semicolon (void)
{
  Vwarn_missing_semicolon = check_preference ("warn_missing_semicolon");

  return 0;
}

static int
warn_variable_switch_label (void)
{
  Vwarn_variable_switch_label
    = check_preference ("warn_variable_switch_label");

  return 0;
}

void
symbols_of_parse (void)
{
  DEFVAR (default_eval_print_flag, 1.0, default_eval_print_flag,
    "-*- texinfo -*-\n\
@defvr {Built-in Variable} default_eval_print_flag\n\
If the value of this variable is nonzero, Octave prints the results of\n\
commands executed by @code{eval} that do not end with semicolons.  If it\n\
is zero, automatic printing is suppressed.  The default value is 1.\n\
@end defvr");

  DEFVAR (warn_assign_as_truth_value, 1.0, warn_assign_as_truth_value,
    "-*- texinfo -*-\n\
@defvr {Built-in Variable} warn_assign_as_truth_value\n\
If the value of @code{warn_assign_as_truth_value} is nonzero, a\n\
warning is issued for statements like\n\
\n\
@example\n\
if (s = t)\n\
  ...\n\
@end example\n\
\n\
@noindent\n\
since such statements are not common, and it is likely that the intent\n\
was to write\n\
\n\
@example\n\
if (s == t)\n\
  ...\n\
@end example\n\
\n\
@noindent\n\
instead.\n\
\n\
There are times when it is useful to write code that contains\n\
assignments within the condition of a @code{while} or @code{if}\n\
statement.  For example, statements like\n\
\n\
@example\n\
while (c = getc())\n\
  ...\n\
@end example\n\
\n\
@noindent\n\
are common in C programming.\n\
\n\
It is possible to avoid all warnings about such statements by setting\n\
@code{warn_assign_as_truth_value} to 0, but that may also\n\
let real errors like\n\
\n\
@example\n\
if (x = 1)  # intended to test (x == 1)!\n\
  ...\n\
@end example\n\
\n\
@noindent\n\
slip by.\n\
\n\
In such cases, it is possible suppress errors for specific statements by\n\
writing them with an extra set of parentheses.  For example, writing the\n\
previous example as\n\
\n\
@example\n\
while ((c = getc()))\n\
  ...\n\
@end example\n\
\n\
@noindent\n\
will prevent the warning from being printed for this statement, while\n\
allowing Octave to warn about other assignments used in conditional\n\
contexts.\n\
\n\
The default value of @code{warn_assign_as_truth_value} is 1.\n\
@end defvr");

  DEFVAR (warn_function_name_clash, 1.0, warn_function_name_clash,
    "-*- texinfo -*-\n\
@defvr {Built-in Variable} warn_function_name_clash\n\
If the value of @code{warn_function_name_clash} is nonzero, a warning is\n\
issued when Octave finds that the name of a function defined in a\n\
function file differs from the name of the file.  (If the names\n\
disagree, the name declared inside the file is ignored.)  If the value\n\
is 0, the warning is omitted.  The default value is 1.\n\
@end defvr");

  DEFVAR (warn_future_time_stamp, 1.0, warn_future_time_stamp,
    "-*- texinfo -*-\n\
@defvr {Built-in Variable} warn_future_time_stamp\n\
If the value of this variable is nonzero, Octave will print a warning\n\
if it finds a function file with a time stamp that is in the future.\n\
@end defvr");

  DEFVAR (warn_missing_semicolon, 0.0, warn_missing_semicolon,
    "-*- texinfo -*-\n\
@defvr {Built-in Variable} warn_missing_semicolon\n\
If the value of this variable is nonzero, Octave will warn when\n\
statements in function definitions don't end in semicolons.  The default\n\
value is 0.\n\
@end defvr");

  DEFVAR (warn_variable_switch_label, 0.0, warn_variable_switch_label,
    "-*- texinfo -*-\n\
@defvr {Built-in Variable} warn_variable_switch_label\n\
If the value of this variable is nonzero, Octave will print a warning if\n\
a switch label is not a constant or constant expression\n\
@end defvr");

}

/*
;;; Local Variables: ***
;;; mode: text ***
;;; End: ***
*/
