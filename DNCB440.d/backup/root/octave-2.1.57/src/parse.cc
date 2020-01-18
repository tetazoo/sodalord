/* A Bison parser, made by GNU Bison 1.875a.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0

/* If NAME_PREFIX is specified substitute the variables and functions
   names.  */
#define yyparse octave_parse
#define yylex   octave_lex
#define yyerror octave_error
#define yylval  octave_lval
#define yychar  octave_char
#define yydebug octave_debug
#define yynerrs octave_nerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ADD_EQ = 258,
     SUB_EQ = 259,
     MUL_EQ = 260,
     DIV_EQ = 261,
     LEFTDIV_EQ = 262,
     POW_EQ = 263,
     EMUL_EQ = 264,
     EDIV_EQ = 265,
     ELEFTDIV_EQ = 266,
     EPOW_EQ = 267,
     AND_EQ = 268,
     OR_EQ = 269,
     LSHIFT_EQ = 270,
     RSHIFT_EQ = 271,
     LSHIFT = 272,
     RSHIFT = 273,
     EXPR_AND_AND = 274,
     EXPR_OR_OR = 275,
     EXPR_AND = 276,
     EXPR_OR = 277,
     EXPR_NOT = 278,
     EXPR_LT = 279,
     EXPR_LE = 280,
     EXPR_EQ = 281,
     EXPR_NE = 282,
     EXPR_GE = 283,
     EXPR_GT = 284,
     LEFTDIV = 285,
     EMUL = 286,
     EDIV = 287,
     ELEFTDIV = 288,
     EPLUS = 289,
     EMINUS = 290,
     QUOTE = 291,
     TRANSPOSE = 292,
     PLUS_PLUS = 293,
     MINUS_MINUS = 294,
     POW = 295,
     EPOW = 296,
     NUM = 297,
     IMAG_NUM = 298,
     STRUCT_ELT = 299,
     NAME = 300,
     END = 301,
     PLOT = 302,
     STRING = 303,
     STYLE = 304,
     AXES_TAG = 305,
     FOR = 306,
     WHILE = 307,
     DO = 308,
     UNTIL = 309,
     IF = 310,
     ELSEIF = 311,
     ELSE = 312,
     SWITCH = 313,
     CASE = 314,
     OTHERWISE = 315,
     BREAK = 316,
     CONTINUE = 317,
     FUNC_RET = 318,
     UNWIND = 319,
     CLEANUP = 320,
     TRY = 321,
     CATCH = 322,
     GLOBAL = 323,
     STATIC = 324,
     FCN_HANDLE = 325,
     END_OF_INPUT = 326,
     LEXICAL_ERROR = 327,
     FCN = 328,
     VARARGIN = 329,
     VARARGOUT = 330,
     ALL_VA_ARGS = 331,
     USING = 332,
     TITLE = 333,
     WITH = 334,
     AXES = 335,
     COLON = 336,
     OPEN_BRACE = 337,
     CLOSE_BRACE = 338,
     CLEAR = 339,
     UNARY = 340
   };
#endif
#define ADD_EQ 258
#define SUB_EQ 259
#define MUL_EQ 260
#define DIV_EQ 261
#define LEFTDIV_EQ 262
#define POW_EQ 263
#define EMUL_EQ 264
#define EDIV_EQ 265
#define ELEFTDIV_EQ 266
#define EPOW_EQ 267
#define AND_EQ 268
#define OR_EQ 269
#define LSHIFT_EQ 270
#define RSHIFT_EQ 271
#define LSHIFT 272
#define RSHIFT 273
#define EXPR_AND_AND 274
#define EXPR_OR_OR 275
#define EXPR_AND 276
#define EXPR_OR 277
#define EXPR_NOT 278
#define EXPR_LT 279
#define EXPR_LE 280
#define EXPR_EQ 281
#define EXPR_NE 282
#define EXPR_GE 283
#define EXPR_GT 284
#define LEFTDIV 285
#define EMUL 286
#define EDIV 287
#define ELEFTDIV 288
#define EPLUS 289
#define EMINUS 290
#define QUOTE 291
#define TRANSPOSE 292
#define PLUS_PLUS 293
#define MINUS_MINUS 294
#define POW 295
#define EPOW 296
#define NUM 297
#define IMAG_NUM 298
#define STRUCT_ELT 299
#define NAME 300
#define END 301
#define PLOT 302
#define STRING 303
#define STYLE 304
#define AXES_TAG 305
#define FOR 306
#define WHILE 307
#define DO 308
#define UNTIL 309
#define IF 310
#define ELSEIF 311
#define ELSE 312
#define SWITCH 313
#define CASE 314
#define OTHERWISE 315
#define BREAK 316
#define CONTINUE 317
#define FUNC_RET 318
#define UNWIND 319
#define CLEANUP 320
#define TRY 321
#define CATCH 322
#define GLOBAL 323
#define STATIC 324
#define FCN_HANDLE 325
#define END_OF_INPUT 326
#define LEXICAL_ERROR 327
#define FCN 328
#define VARARGIN 329
#define VARARGOUT 330
#define ALL_VA_ARGS 331
#define USING 332
#define TITLE 333
#define WITH 334
#define AXES 335
#define COLON 336
#define OPEN_BRACE 337
#define CLOSE_BRACE 338
#define CLEAR 339
#define UNARY 340




/* Copy the first part of user declarations.  */
#line 27 "parse.y"

#define YYDEBUG 1

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <cassert>
#include <cstdio>

#ifdef YYBYACC
#include <cstdlib>
#endif

#include "Cell.h"
#include "Matrix.h"
#include "cmd-edit.h"
#include "cmd-hist.h"
#include "file-ops.h"
#include "file-stat.h"
#include "lo-sstream.h"
#include "oct-env.h"
#include "oct-time.h"
#include "quit.h"

#include "comment-list.h"
#include "defaults.h"
#include "defun.h"
#include "dirfns.h"
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

// If TRUE, generate warning about the meaning of code changing due to
// changes in precedence levels for various ops (typically for Matlab
// compatibility).
static bool Vwarn_precedence_change;

// Temporary symbol table pointer used to cope with bogus function syntax.
symbol_table *tmp_local_sym_tab = 0;

// The current input line number.
int input_line_number = 0;

// The column of the current token.
int current_input_column = 1;

// Buffer for help text snagged from function files.
std::stack<std::string> help_buf;

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

// Keep a count of how many END tokens we expect.
int end_tokens_expected = 0;

// Keep track of symbol table information when parsing functions.
std::stack<symbol_table*> symtab_context;

// Name of parent function when parsing function files that might
// contain nested functions.
std::string parent_function_name;

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

// Build a function handle.
static tree_fcn_handle *
make_fcn_handle (token *tok_val);

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
make_index_expression (tree_expression *expr,
		       tree_argument_list *args, char type);

// Make an indirect reference expression.
static tree_index_expression *
make_indirect_ref (tree_expression *expr, const std::string&);

// Make an indirect reference expression with dynamic field name.
static tree_index_expression *
make_indirect_ref (tree_expression *expr, tree_expression *field);

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
      if (! symtab_context.empty ()) \
        { \
	  curr_sym_tab = symtab_context.top (); \
	  symtab_context.pop (); \
        } \
      if (interactive || forced_interactive) \
	YYACCEPT; \
      else \
	YYABORT; \
    } \
  while (0)



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 357 "parse.y"
typedef union YYSTYPE {
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
  tree_fcn_handle *tree_fcn_handle_type;
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
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 620 "y.tab.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 632 "y.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  104
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1050

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  102
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  92
/* YYNRULES -- Number of rules. */
#define YYNRULES  250
/* YYNRULES -- Number of states. */
#define YYNSTATES  417

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   340

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      93,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      95,   101,     7,     6,    92,     5,    96,     8,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     4,    91,
       2,     3,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    98,     2,    99,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    97,     2,   100,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      94
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    16,    19,
      22,    25,    27,    31,    32,    34,    37,    39,    43,    45,
      47,    50,    52,    54,    56,    58,    59,    62,    66,    71,
      73,    76,    78,    82,    85,    89,    93,    95,    98,   100,
     104,   106,   109,   111,   113,   115,   117,   119,   121,   125,
     127,   129,   131,   133,   137,   141,   145,   147,   148,   149,
     151,   156,   162,   167,   173,   178,   183,   188,   193,   199,
     207,   211,   213,   216,   219,   222,   225,   228,   232,   236,
     240,   244,   248,   252,   256,   260,   264,   268,   272,   276,
     278,   280,   284,   286,   290,   294,   298,   302,   306,   310,
     314,   318,   322,   326,   330,   334,   336,   341,   345,   349,
     353,   357,   361,   365,   369,   373,   377,   381,   385,   389,
     393,   397,   401,   404,   406,   409,   411,   413,   415,   417,
     419,   421,   423,   425,   427,   429,   432,   435,   437,   440,
     442,   446,   448,   450,   455,   457,   460,   464,   467,   474,
     479,   486,   487,   489,   492,   494,   497,   504,   509,   516,
     523,   532,   534,   536,   538,   548,   558,   559,   560,   561,
     562,   564,   566,   569,   573,   576,   581,   584,   588,   591,
     595,   599,   602,   606,   608,   612,   618,   620,   624,   627,
     632,   635,   639,   643,   647,   650,   653,   656,   658,   662,
     664,   666,   668,   671,   674,   678,   680,   683,   687,   693,
     698,   703,   707,   710,   712,   716,   718,   721,   723,   725,
     727,   729,   732,   735,   738,   741,   744,   746,   749,   752,
     756,   759,   762,   766,   771,   772,   774,   776,   778,   780,
     783,   786,   787,   789,   791,   793,   795,   798,   801,   804,
     805
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short yyrhs[] =
{
     103,     0,    -1,   104,    -1,   105,   189,    -1,   189,    -1,
      93,    -1,    77,    -1,   105,    -1,   105,    93,    -1,   105,
      77,    -1,   106,   191,    -1,   110,    -1,   106,   190,   110,
      -1,    -1,   108,    -1,   109,   193,    -1,   110,    -1,   109,
     192,   110,    -1,   138,    -1,   139,    -1,    53,    90,    -1,
      51,    -1,    48,    -1,    49,    -1,    54,    -1,    -1,    98,
      99,    -1,    98,    91,    99,    -1,    98,   113,   115,    99,
      -1,   116,    -1,   116,    91,    -1,   120,    -1,   116,    91,
     120,    -1,    97,   100,    -1,    97,    91,   100,    -1,    97,
     118,   100,    -1,   119,    -1,   119,    91,    -1,   120,    -1,
     119,    91,   120,    -1,   124,    -1,   124,    92,    -1,    76,
      -1,   111,    -1,   112,    -1,   121,    -1,   114,    -1,   117,
      -1,    95,   138,   101,    -1,     4,    -1,   138,    -1,   123,
      -1,    82,    -1,   124,    92,   123,    -1,   124,    92,   138,
      -1,   124,    92,    82,    -1,    96,    -1,    -1,    -1,   122,
      -1,   128,   126,    95,   101,    -1,   128,   126,    95,   124,
     101,    -1,   128,   126,    97,   100,    -1,   128,   126,    97,
     124,   100,    -1,   128,   126,    44,   127,    -1,   128,   126,
      45,   127,    -1,   128,   126,    42,   127,    -1,   128,   126,
      43,   127,    -1,   128,   126,   125,   127,    50,    -1,   128,
     126,   125,   127,    95,   138,   101,    -1,   128,   126,   127,
      -1,   130,    -1,    44,   129,    -1,    45,   129,    -1,    29,
     129,    -1,     6,   129,    -1,     5,   129,    -1,   129,    46,
     129,    -1,   129,    47,   129,    -1,   129,     6,   129,    -1,
     129,     5,   129,    -1,   129,     7,   129,    -1,   129,     8,
     129,    -1,   129,    40,   129,    -1,   129,    41,   129,    -1,
     129,    37,   129,    -1,   129,    38,   129,    -1,   129,    36,
     129,    -1,   129,    39,   129,    -1,   132,    -1,   129,    -1,
     132,     4,   129,    -1,   131,    -1,   133,    23,   133,    -1,
     133,    24,   133,    -1,   133,    30,   133,    -1,   133,    31,
     133,    -1,   133,    32,   133,    -1,   133,    34,   133,    -1,
     133,    35,   133,    -1,   133,    33,   133,    -1,   133,    27,
     133,    -1,   133,    28,   133,    -1,   133,    25,   133,    -1,
     133,    26,   133,    -1,   133,    -1,    98,   113,   124,    89,
      -1,   134,     3,   138,    -1,   134,     9,   138,    -1,   134,
      10,   138,    -1,   134,    11,   138,    -1,   134,    12,   138,
      -1,   134,    13,   138,    -1,   134,    14,   138,    -1,   134,
      21,   138,    -1,   134,    22,   138,    -1,   134,    15,   138,
      -1,   134,    16,   138,    -1,   134,    17,   138,    -1,   134,
      18,   138,    -1,   134,    19,   138,    -1,   134,    20,   138,
      -1,   111,   137,    -1,    54,    -1,   137,    54,    -1,   133,
      -1,   136,    -1,   135,    -1,   140,    -1,   143,    -1,   154,
      -1,   155,    -1,   156,    -1,   170,    -1,   177,    -1,    74,
     141,    -1,    75,   141,    -1,   142,    -1,   141,   142,    -1,
     111,    -1,   111,     3,   138,    -1,   144,    -1,   149,    -1,
      61,   188,   145,    52,    -1,   146,    -1,   146,   148,    -1,
     138,   193,   107,    -1,   146,   147,    -1,    62,   188,   193,
     138,   193,   107,    -1,    63,   188,   193,   107,    -1,    64,
     188,   138,   193,   150,    52,    -1,    -1,   151,    -1,   151,
     153,    -1,   152,    -1,   151,   152,    -1,    65,   188,   193,
     138,   193,   107,    -1,    66,   188,   193,   107,    -1,    58,
     188,   138,   193,   107,    52,    -1,    59,   188,   193,   107,
      60,   138,    -1,    57,   188,   134,     3,   138,   193,   107,
      52,    -1,    67,    -1,    68,    -1,    69,    -1,    70,   188,
     193,   107,    71,   188,   193,   107,    52,    -1,    72,   188,
     193,   107,    73,   188,   193,   107,    52,    -1,    -1,    -1,
      -1,    -1,    95,    -1,   101,    -1,   161,   162,    -1,   161,
      80,   162,    -1,   164,   162,    -1,   164,    92,    80,   162,
      -1,   161,   111,    -1,   164,    92,   111,    -1,   161,     1,
      -1,   164,    92,     1,    -1,    98,   160,   159,    -1,   165,
     168,    -1,   165,    81,   168,    -1,    81,    -1,   165,   167,
     168,    -1,   165,   167,    92,    81,   168,    -1,   111,    -1,
     167,    92,   111,    -1,   158,    99,    -1,   157,    79,   158,
     188,    -1,   169,   173,    -1,   169,   111,   171,    -1,   169,
     166,   171,    -1,   158,     3,   173,    -1,   111,   159,    -1,
     172,   174,    -1,   163,   175,    -1,   175,    -1,   193,   107,
     176,    -1,    52,    -1,    77,    -1,    53,    -1,    53,   178,
      -1,    53,   180,    -1,    53,   178,   180,    -1,   179,    -1,
     179,   179,    -1,   179,   179,   179,    -1,    88,   138,    87,
     138,    89,    -1,    88,    87,   138,    89,    -1,    88,   138,
      87,    89,    -1,    88,    87,    89,    -1,    88,    89,    -1,
     181,    -1,   180,    92,   181,    -1,   138,    -1,   138,   182,
      -1,   184,    -1,   186,    -1,   187,    -1,   183,    -1,   182,
     184,    -1,   182,   186,    -1,   182,   187,    -1,   182,   183,
      -1,    86,    56,    -1,   185,    -1,   185,   138,    -1,    83,
     138,    -1,   185,    87,   138,    -1,    84,   138,    -1,    85,
      55,    -1,    85,    55,   138,    -1,    85,    55,   138,   138,
      -1,    -1,    78,    -1,     1,    -1,    92,    -1,    91,    -1,
     190,    92,    -1,   190,    91,    -1,    -1,   190,    -1,    92,
      -1,    91,    -1,    93,    -1,   192,    92,    -1,   192,    91,
      -1,   192,    93,    -1,    -1,   192,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   499,   499,   505,   507,   511,   513,   518,   520,   522,
     526,   533,   535,   544,   545,   549,   556,   561,   569,   576,
     583,   599,   606,   608,   610,   616,   619,   621,   623,   630,
     632,   636,   638,   645,   647,   649,   653,   655,   659,   661,
     669,   671,   675,   679,   681,   683,   685,   687,   689,   693,
     700,   702,   704,   710,   715,   720,   729,   741,   745,   748,
     750,   755,   760,   765,   770,   772,   774,   776,   778,   780,
     784,   786,   788,   790,   792,   794,   796,   800,   802,   804,
     806,   808,   810,   812,   814,   816,   818,   820,   822,   826,
     830,   832,   839,   841,   843,   845,   847,   849,   851,   853,
     855,   857,   859,   861,   863,   870,   872,   879,   881,   883,
     885,   887,   889,   891,   893,   895,   897,   899,   901,   903,
     905,   907,   911,   915,   920,   928,   930,   932,   940,   942,
     944,   946,   948,   950,   952,   960,   962,   966,   968,   975,
     977,   985,   987,   995,  1002,  1004,  1011,  1013,  1020,  1024,
    1034,  1042,  1043,  1045,  1052,  1054,  1061,  1065,  1075,  1080,
    1085,  1096,  1101,  1106,  1117,  1123,  1136,  1140,  1144,  1148,
    1155,  1159,  1163,  1168,  1175,  1181,  1190,  1192,  1197,  1203,
    1215,  1218,  1223,  1230,  1237,  1242,  1250,  1252,  1259,  1266,
    1270,  1276,  1282,  1290,  1294,  1309,  1316,  1318,  1322,  1326,
    1331,  1346,  1351,  1356,  1361,  1368,  1370,  1372,  1376,  1378,
    1380,  1382,  1384,  1388,  1390,  1397,  1399,  1403,  1408,  1413,
    1418,  1423,  1431,  1439,  1447,  1457,  1464,  1469,  1476,  1481,
    1485,  1489,  1491,  1493,  1502,  1505,  1507,  1510,  1512,  1514,
    1516,  1521,  1522,  1526,  1528,  1530,  1532,  1534,  1536,  1541,
    1542
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "'='", "':'", "'-'", "'+'", "'*'", "'/'", 
  "ADD_EQ", "SUB_EQ", "MUL_EQ", "DIV_EQ", "LEFTDIV_EQ", "POW_EQ", 
  "EMUL_EQ", "EDIV_EQ", "ELEFTDIV_EQ", "EPOW_EQ", "AND_EQ", "OR_EQ", 
  "LSHIFT_EQ", "RSHIFT_EQ", "LSHIFT", "RSHIFT", "EXPR_AND_AND", 
  "EXPR_OR_OR", "EXPR_AND", "EXPR_OR", "EXPR_NOT", "EXPR_LT", "EXPR_LE", 
  "EXPR_EQ", "EXPR_NE", "EXPR_GE", "EXPR_GT", "LEFTDIV", "EMUL", "EDIV", 
  "ELEFTDIV", "EPLUS", "EMINUS", "QUOTE", "TRANSPOSE", "PLUS_PLUS", 
  "MINUS_MINUS", "POW", "EPOW", "NUM", "IMAG_NUM", "STRUCT_ELT", "NAME", 
  "END", "PLOT", "STRING", "STYLE", "AXES_TAG", "FOR", "WHILE", "DO", 
  "UNTIL", "IF", "ELSEIF", "ELSE", "SWITCH", "CASE", "OTHERWISE", "BREAK", 
  "CONTINUE", "FUNC_RET", "UNWIND", "CLEANUP", "TRY", "CATCH", "GLOBAL", 
  "STATIC", "FCN_HANDLE", "END_OF_INPUT", "LEXICAL_ERROR", "FCN", 
  "VARARGIN", "VARARGOUT", "ALL_VA_ARGS", "USING", "TITLE", "WITH", 
  "AXES", "COLON", "OPEN_BRACE", "CLOSE_BRACE", "CLEAR", "';'", "','", 
  "'\\n'", "UNARY", "'('", "'.'", "'{'", "'['", "']'", "'}'", "')'", 
  "$accept", "input", "input1", "simple_list", "simple_list1", "opt_list", 
  "list", "list1", "statement", "identifier", "constant", 
  "in_matrix_or_assign_lhs", "matrix", "matrix_rows", "matrix_rows1", 
  "cell", "cell_rows", "cell_rows1", "cell_or_matrix_row", "fcn_handle", 
  "primary_expr", "magic_colon", "arg_list", "indirect_ref_op", 
  "begin_obj_idx", "cancel_obj_idx", "postfix_expr", "prefix_expr", 
  "binary_expr", "colon_expr", "colon_expr1", "simple_expr", "assign_lhs", 
  "assign_expr", "word_list_cmd", "word_list", "expression", "command", 
  "declaration", "decl1", "decl2", "select_command", "if_command", 
  "if_cmd_list", "if_cmd_list1", "elseif_clause", "else_clause", 
  "switch_command", "case_list", "case_list1", "switch_case", 
  "default_case", "loop_command", "jump_command", "except_command", 
  "save_symtab", "function_symtab", "local_symtab", "in_return_list", 
  "param_list_beg", "param_list_end", "param_list", "param_list1", 
  "return_list_beg", "return_list", "return_list1", "return_list_end", 
  "function_beg", "function", "function1", "fcn_name", "function2", 
  "function3", "function4", "function_end", "plot_command", "ranges", 
  "ranges1", "plot_command1", "plot_command2", "plot_options", "axes", 
  "using", "using1", "title", "style", "stash_comment", "parse_error", 
  "sep_no_nl", "opt_sep_no_nl", "sep", "opt_sep", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,    61,    58,    45,    43,    42,    47,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,    59,    44,    10,   340,    40,    46,   123,    91,    93,
     125,    41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,   102,   103,   103,   103,   104,   104,   104,   104,   104,
     105,   106,   106,   107,   107,   108,   109,   109,   110,   110,
     110,   111,   112,   112,   112,   113,   114,   114,   114,   115,
     115,   116,   116,   117,   117,   117,   118,   118,   119,   119,
     120,   120,   121,   122,   122,   122,   122,   122,   122,   123,
     124,   124,   124,   124,   124,   124,   125,   126,   127,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     129,   129,   129,   129,   129,   129,   129,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   131,
     132,   132,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   134,   134,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   136,   137,   137,   138,   138,   138,   139,   139,
     139,   139,   139,   139,   139,   140,   140,   141,   141,   142,
     142,   143,   143,   144,   145,   145,   146,   146,   147,   148,
     149,   150,   150,   150,   151,   151,   152,   153,   154,   154,
     154,   155,   155,   155,   156,   156,   157,   158,   159,   160,
     161,   162,   163,   163,   163,   163,   164,   164,   164,   164,
     165,   166,   166,   166,   166,   166,   167,   167,   168,   169,
     170,   170,   170,   171,   172,   173,   174,   174,   175,   176,
     176,   177,   177,   177,   177,   178,   178,   178,   179,   179,
     179,   179,   179,   180,   180,   181,   181,   182,   182,   182,
     182,   182,   182,   182,   182,   183,   184,   184,   185,   185,
     186,   187,   187,   187,   188,   189,   189,   190,   190,   190,
     190,   191,   191,   192,   192,   192,   192,   192,   192,   193,
     193
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     2,     2,
       2,     1,     3,     0,     1,     2,     1,     3,     1,     1,
       2,     1,     1,     1,     1,     0,     2,     3,     4,     1,
       2,     1,     3,     2,     3,     3,     1,     2,     1,     3,
       1,     2,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     1,     3,     3,     3,     1,     0,     0,     1,
       4,     5,     4,     5,     4,     4,     4,     4,     5,     7,
       3,     1,     2,     2,     2,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     3,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     1,     2,     1,
       3,     1,     1,     4,     1,     2,     3,     2,     6,     4,
       6,     0,     1,     2,     1,     2,     6,     4,     6,     6,
       8,     1,     1,     1,     9,     9,     0,     0,     0,     0,
       1,     1,     2,     3,     2,     4,     2,     3,     2,     3,
       3,     2,     3,     1,     3,     5,     1,     3,     2,     4,
       2,     3,     3,     3,     2,     2,     2,     1,     3,     1,
       1,     1,     2,     2,     3,     1,     2,     3,     5,     4,
       4,     3,     2,     1,     3,     1,     2,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     1,     2,     2,     3,
       2,     2,     3,     4,     0,     1,     1,     1,     1,     2,
       2,     0,     1,     1,     1,     1,     2,     2,     2,     0,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,   236,     0,     0,     0,     0,     0,    22,    23,    21,
     201,    24,   234,   234,   234,   234,   234,   161,   162,   163,
     234,   234,     0,     0,    42,     6,   235,     5,     0,     0,
      25,     0,     2,     0,   241,    11,    43,    44,    46,    47,
      45,    59,    57,    90,    71,    92,    89,   125,     0,   127,
     126,    18,    19,   128,   129,   141,   142,   130,   131,   132,
       0,     0,   133,   134,     4,    25,    43,    76,    75,    74,
      72,    73,     0,    20,   215,   202,   205,   203,   213,     0,
       0,   249,     0,     0,   249,   249,   139,   135,   137,   136,
       0,    49,    52,     0,    33,     0,    36,    38,    51,    40,
      50,     0,    26,     0,     1,     9,     8,     3,   238,   237,
     242,    10,   123,   122,    58,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   167,   183,   169,   168,   167,
     167,   249,   190,     0,     0,   212,     0,     0,     0,     0,
       0,   216,   220,   217,   226,   218,   219,   204,   206,     0,
     105,     0,   249,   244,   243,   245,   250,    13,   249,     0,
     144,   249,    13,    13,     0,   138,    48,    34,    35,    37,
      41,    27,     0,    29,    31,    40,   240,   239,    12,   124,
      58,    58,    58,    58,     0,    56,     0,    58,    70,    80,
      79,    81,    82,    87,    85,    86,    88,    83,    84,    77,
      78,    91,    93,    94,   103,   104,   101,   102,    95,    96,
      97,   100,    98,    99,   107,   108,   109,   110,   111,   112,
     113,   116,   117,   118,   119,   120,   121,   114,   115,   234,
     168,     0,   194,   191,   167,   186,     0,   167,   181,   192,
     170,     0,   249,     0,   195,   197,    13,   211,     0,     0,
     228,   230,   231,   225,   224,   221,   222,   223,     0,   227,
     207,   214,     0,    13,   247,   246,   248,     0,    14,   249,
      16,    13,   143,   234,   234,   147,   145,   151,     0,     0,
     140,    39,    55,    53,    54,    28,    30,   106,    66,    67,
      64,    65,    60,     0,    62,     0,     0,   189,   180,     0,
     182,   188,     0,   184,   178,     0,   171,   176,   172,   196,
       0,   174,     0,   209,   210,     0,   232,   229,   249,     0,
       0,   250,    15,   146,   249,   249,   234,     0,   152,   154,
     234,   234,    32,     0,    61,    63,    68,     0,   168,   193,
     167,   187,   173,   179,     0,   177,   199,   200,   198,   208,
     233,    13,   158,   159,    17,     0,    13,   249,   150,   234,
     155,   153,   249,   249,     0,   185,   175,     0,   249,   149,
       0,   249,    13,    13,    69,   160,    13,   249,    13,     0,
       0,   148,    13,   157,   164,   165,   156
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,    31,    32,    33,    34,   297,   298,   299,   300,    36,
      37,   103,    38,   202,   203,    39,    95,    96,   204,    40,
      41,    98,    99,   217,   114,   218,    42,    43,    44,    45,
      46,    47,    48,    49,    50,   113,    51,    52,    53,    87,
      88,    54,    55,   189,   190,   305,   306,    56,   357,   358,
     359,   391,    57,    58,    59,    60,   266,   262,   260,   271,
     338,   272,   273,   159,   160,   267,   268,    61,    62,   263,
     161,   162,   274,   275,   378,    63,    75,    76,    77,    78,
     171,   172,   173,   174,   175,   176,    79,    64,   110,   111,
     186,   276
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -262
static const short yypact[] =
{
     398,  -262,   893,   893,   893,   893,   893,  -262,  -262,  -262,
     762,  -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,
    -262,  -262,    15,    15,  -262,  -262,  -262,  -262,   911,   434,
     -39,    22,  -262,    25,   -16,  -262,   -26,  -262,  -262,  -262,
    -262,  -262,  -262,   976,  -262,  -262,    97,  1015,   609,  -262,
    -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,
      41,   -34,  -262,  -262,  -262,   -39,  -262,    45,    45,    45,
      45,    45,   797,  -262,    -5,   911,    63,    60,  -262,   911,
     911,    54,   911,   911,    54,    54,   153,    15,  -262,    15,
      58,  -262,  -262,    61,  -262,    62,    69,  -262,  -262,    73,
    -262,    64,  -262,   501,  -262,  -262,  -262,  -262,  -262,  -262,
     668,  -262,  -262,   112,   -13,   893,   893,   893,   893,   893,
     893,   893,   893,   893,   893,   893,   893,   893,   893,   893,
     893,   893,   893,   893,   893,   893,   893,   893,   893,   893,
     911,   911,   911,   911,   911,   911,   911,   911,   911,   911,
     911,   911,   911,   911,   911,  -262,  -262,  -262,   164,   -31,
    -262,   -24,  -262,   501,   826,  -262,    81,   911,   911,   116,
     118,    -5,  -262,  -262,   856,  -262,  -262,    60,    63,   911,
      11,   169,    54,  -262,  -262,  -262,    57,   725,    54,   123,
      24,    54,   725,   725,   911,  -262,  -262,  -262,  -262,   501,
     556,  -262,    78,    89,  -262,   -35,  -262,  -262,  -262,  -262,
    -262,  -262,  -262,  -262,   284,  -262,   493,  -262,  -262,   263,
     263,    45,    45,    45,    45,    45,    45,   263,   263,    45,
      45,   976,  -262,  -262,   969,   385,   533,   225,    71,    71,
      71,    71,    71,    71,  -262,  -262,  -262,  -262,  -262,  -262,
    -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,
    -262,   179,  -262,  -262,  -262,  -262,    86,    95,  -262,  -262,
    -262,    10,    54,   -68,  -262,  -262,   725,  -262,    99,   882,
    -262,  -262,   911,  -262,  -262,  -262,  -262,  -262,   911,  -262,
    -262,  -262,   911,   725,  -262,  -262,  -262,   131,  -262,    54,
    -262,   725,  -262,  -262,  -262,  -262,  -262,   128,   125,   121,
    -262,  -262,  -262,  -262,  -262,  -262,   501,  -262,  -262,  -262,
    -262,  -262,  -262,   -52,  -262,   -37,   -36,  -262,  -262,    15,
    -262,  -262,   -30,  -262,  -262,    96,  -262,  -262,  -262,  -262,
      26,  -262,   -29,  -262,  -262,   109,   911,  -262,    54,   147,
     911,   611,  -262,  -262,    54,    54,  -262,   148,    39,  -262,
    -262,  -262,  -262,   556,  -262,  -262,  -262,   911,  -262,  -262,
    -262,  -262,  -262,  -262,    96,  -262,  -262,  -262,  -262,  -262,
    -262,   725,  -262,  -262,  -262,   911,   725,    54,  -262,  -262,
    -262,  -262,    54,    54,   100,  -262,  -262,   150,    54,  -262,
     911,    54,   725,   725,  -262,  -262,   725,    54,   725,   151,
     155,  -262,   725,  -262,  -262,  -262,  -262
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -262,  -262,  -262,  -262,  -262,   -14,  -262,  -262,     5,    94,
    -262,   140,  -262,  -262,  -262,  -262,  -262,  -262,   -23,  -262,
    -262,  -193,   -88,  -262,  -262,  -103,  -262,   119,  -262,  -262,
    -262,   186,   129,  -262,  -262,  -262,   -10,  -262,  -262,   227,
      40,  -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,
    -107,  -262,  -262,  -262,  -262,  -262,  -102,    -6,  -262,  -262,
    -261,  -262,  -262,  -262,  -262,  -262,  -251,  -262,  -262,   101,
    -262,   -65,  -262,    -9,  -262,  -262,  -262,   -66,   191,    88,
    -262,   102,   103,  -262,   104,   105,   -12,   235,  -262,  -262,
     -22,     4
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -168
static const short yytable[] =
{
      74,    80,    81,    82,    83,    35,    97,   313,    84,    85,
     178,   334,   341,   330,   366,   205,   333,     9,    90,   100,
       9,     9,   104,   376,   340,    -7,     1,   373,   112,   210,
     211,   212,   213,   336,   128,   129,   130,   131,   132,   133,
     363,   134,   135,   136,   137,   138,   139,   156,   377,   364,
     264,   370,   101,   259,   317,   363,   261,   200,   261,   367,
     102,     9,   166,   365,   157,    74,     9,   183,   184,   185,
     182,   270,   188,   191,   372,   108,   109,     9,   167,   168,
     169,   170,   214,   215,   216,   187,   303,   304,   192,   193,
     335,   125,   126,   100,   128,   129,    66,    66,    66,    66,
      66,   127,   105,    26,   356,   389,   374,   318,   319,   320,
     321,   336,   290,   396,   326,   208,    86,    86,   106,   395,
     155,    67,    68,    69,    70,    71,   323,   195,   325,   195,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   183,   184,   185,   294,   295,
     296,    72,   179,   100,   278,   158,   194,   280,   281,   196,
     199,   197,   198,   201,   289,   200,   209,  -167,   279,    74,
     313,   282,   292,    66,   283,   302,   311,   315,   308,   309,
     316,    86,   329,    86,   310,   331,   293,   332,   343,   100,
     314,   350,   301,   356,   361,   307,   360,   336,   379,   382,
     388,   404,   405,   414,   100,   163,   100,   415,   181,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   327,   128,   129,
      89,   390,   132,   265,   328,   134,   135,   136,   137,   138,
     139,   269,   342,   339,   369,   180,   177,   291,   107,   345,
     117,   118,   346,   284,   285,   286,   287,   351,   347,   349,
       0,     0,   348,     0,     0,     0,     0,   353,    91,     2,
       3,   354,   355,   362,     0,     0,     0,     0,     0,   119,
     120,   121,   122,   352,     0,     0,   100,     0,     0,   125,
     126,     0,     0,     4,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,     0,     0,     5,     6,
       0,     0,     7,     8,     0,     9,   380,     0,    11,     0,
     383,     0,     0,     0,   387,     0,     0,     0,   392,   393,
       0,     0,   381,   314,     0,     0,   384,   394,   385,   386,
      24,     0,     0,     0,     0,   337,    92,   397,     0,     0,
       0,     0,   399,     0,     0,   398,     0,   401,     0,    28,
       0,    29,    30,     0,     0,   322,     0,     0,   409,   410,
     407,   400,   411,     0,   413,     0,   402,   403,   416,     1,
       0,     0,   406,     2,     3,   408,     0,     0,   128,   129,
     130,   412,   132,   133,     0,   134,   135,   136,   137,   138,
     139,     0,     0,   368,     0,     0,   371,     4,     0,     0,
       0,     0,     0,     0,   375,     0,     0,     0,    91,     2,
       3,     0,     5,     6,     0,     0,     7,     8,     0,     9,
       0,    10,    11,     0,     0,    12,    13,    14,     0,    15,
       0,     0,    16,     4,     0,    17,    18,    19,    20,     0,
      21,     0,    22,    23,    24,    25,    26,  -166,     5,     6,
       0,     0,     7,     8,     0,     9,     0,     0,    11,     0,
       0,    27,     0,    28,     0,    29,    30,    91,     2,     3,
       0,     0,     0,     0,     0,    91,     2,     3,     0,     0,
      24,     0,     0,     0,     0,     0,    92,     0,     0,     0,
       0,     0,     4,     0,     0,    93,     0,     0,     0,    28,
       4,    29,    30,     0,    94,     0,     0,     5,     6,     0,
       0,     7,     8,     0,     9,     5,     6,    11,     0,     7,
       8,     0,     9,     0,     0,    11,   128,   129,     0,     0,
      91,     2,     3,   134,   135,   136,   137,   138,   139,    24,
       0,     0,     0,     0,     0,    92,     0,    24,     0,     0,
       0,     0,     0,    92,     0,     4,     0,     0,    28,     0,
      29,    30,     0,   324,     0,     0,    28,     0,    29,    30,
       5,     6,     0,     0,     7,     8,     0,     9,     0,     0,
      11,     0,   140,     0,     0,     0,     2,     3,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,    24,     0,     0,     0,     0,     0,   312,     0,
       4,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    28,     0,    29,    30,     5,     6,     0,     0,     7,
       8,     0,     9,     0,    10,    11,     0,     0,    12,    13,
      14,     0,    15,     2,     3,    16,     0,     0,    17,    18,
      19,    20,     0,    21,     0,    22,    23,    24,     0,     0,
    -166,     0,     0,     0,     0,     0,     0,     4,     0,     0,
       0,     0,   294,   295,   296,     0,    28,     0,    29,    30,
       0,     0,     5,     6,     0,     0,     7,     8,     0,     9,
       0,    10,    11,     0,     0,    12,    13,    14,     0,    15,
       2,     3,    16,     0,     0,    17,    18,    19,    20,     0,
      21,     0,    22,    23,    24,     0,     0,  -166,     0,     0,
       0,     0,     0,     0,     4,     0,     0,     0,     0,   206,
     207,     0,     0,    28,     0,    29,    30,     2,     3,     5,
       6,     0,     0,     7,     8,     0,     9,     0,    10,    11,
       0,     0,    12,    13,    14,     0,    15,     0,     0,    16,
       0,     4,    17,    18,    19,    20,     0,    21,     0,    22,
      23,    24,     2,     3,  -166,     0,     5,     6,     0,     0,
       7,     8,     0,     9,     0,     0,    11,     0,     0,     0,
      28,     0,    29,    30,     0,     0,     4,     0,     0,     0,
       0,     2,     3,     0,     0,     0,     0,     0,    24,     0,
       0,     5,     6,     0,     0,     7,     8,     0,     9,     0,
      72,    11,    73,     0,     0,     4,     0,    28,     0,    29,
      30,     2,     3,     0,     0,     0,     0,     0,     0,     0,
       5,     6,     0,    24,     7,     8,     0,     9,     0,     0,
      11,     0,     0,     0,   164,     4,   165,     2,     3,     0,
       0,     0,    28,     0,    29,    30,     0,     0,     2,     3,
       5,     6,    24,     0,     7,     8,     0,     9,     0,     0,
      11,     4,     0,     0,     0,   277,     2,     3,     0,     0,
       0,    28,     4,    29,    30,     0,     5,     6,     0,     0,
       7,     8,    24,     9,     0,     0,    11,     5,     6,     0,
       4,     7,     8,   288,     9,     0,     0,    11,     0,     0,
       0,    28,     0,    29,    30,     5,     6,     0,    24,     7,
       8,     0,     9,     0,     0,    11,     0,     0,     0,    24,
       0,   344,     0,     0,     0,     0,     0,    28,     0,    29,
      30,   115,   116,   117,   118,     0,     0,    24,    28,     0,
      29,    65,   128,   129,     0,     0,   132,   133,     0,   134,
     135,   136,   137,   138,   139,     0,    28,     0,    29,    30,
       0,     0,   119,   120,   121,   122,   123,   124,  -105,     0,
       0,     0,   125,   126,  -105,  -105,  -105,  -105,  -105,  -105,
    -105,  -105,  -105,  -105,  -105,  -105,  -105,  -105,   128,   129,
     130,   131,   132,   133,     0,   134,   135,   136,   137,   138,
     139
};

static const short yycheck[] =
{
      10,    13,    14,    15,    16,     0,    29,   200,    20,    21,
      76,     1,   273,   264,    50,   103,   267,    51,    28,    29,
      51,    51,     0,    52,    92,     0,     1,     1,    54,    42,
      43,    44,    45,   101,    23,    24,    25,    26,    27,    28,
      92,    30,    31,    32,    33,    34,    35,    81,    77,   101,
      81,    81,    91,   155,    89,    92,   158,    92,   160,    95,
      99,    51,    72,   100,    98,    75,    51,    91,    92,    93,
      80,    95,    82,    83,   335,    91,    92,    51,    83,    84,
      85,    86,    95,    96,    97,    81,    62,    63,    84,    85,
      80,    46,    47,   103,    23,    24,     2,     3,     4,     5,
       6,     4,    77,    78,    65,    66,    80,   210,   211,   212,
     213,   101,   178,   374,   217,   110,    22,    23,    93,   370,
      79,     2,     3,     4,     5,     6,   214,    87,   216,    89,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,    91,    92,    93,    91,    92,
      93,    88,    92,   163,   164,    61,     3,   167,   168,   101,
      91,   100,   100,    99,   174,    92,    54,     3,    87,   179,
     363,    55,     3,    79,    56,    52,   199,    99,   192,   193,
      91,    87,     3,    89,   194,    99,   182,    92,    89,   199,
     200,    60,   188,    65,    73,   191,    71,   101,    89,    52,
      52,   101,    52,    52,   214,    65,   216,    52,    79,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   259,    23,    24,
      23,   358,    27,   159,   260,    30,    31,    32,    33,    34,
      35,   160,   276,   272,   329,    79,    75,   179,    33,   279,
       7,     8,   282,   171,   171,   171,   171,   299,   288,   293,
      -1,    -1,   292,    -1,    -1,    -1,    -1,   301,     4,     5,
       6,   303,   304,   316,    -1,    -1,    -1,    -1,    -1,    36,
      37,    38,    39,   299,    -1,    -1,   316,    -1,    -1,    46,
      47,    -1,    -1,    29,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,    -1,    -1,    44,    45,
      -1,    -1,    48,    49,    -1,    51,   346,    -1,    54,    -1,
     350,    -1,    -1,    -1,   356,    -1,    -1,    -1,   360,   361,
      -1,    -1,   348,   363,    -1,    -1,   351,   367,   354,   355,
      76,    -1,    -1,    -1,    -1,   271,    82,   381,    -1,    -1,
      -1,    -1,   386,    -1,    -1,   385,    -1,   389,    -1,    95,
      -1,    97,    98,    -1,    -1,   101,    -1,    -1,   402,   403,
     400,   387,   406,    -1,   408,    -1,   392,   393,   412,     1,
      -1,    -1,   398,     5,     6,   401,    -1,    -1,    23,    24,
      25,   407,    27,    28,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,   329,    -1,    -1,   332,    29,    -1,    -1,
      -1,    -1,    -1,    -1,   340,    -1,    -1,    -1,     4,     5,
       6,    -1,    44,    45,    -1,    -1,    48,    49,    -1,    51,
      -1,    53,    54,    -1,    -1,    57,    58,    59,    -1,    61,
      -1,    -1,    64,    29,    -1,    67,    68,    69,    70,    -1,
      72,    -1,    74,    75,    76,    77,    78,    79,    44,    45,
      -1,    -1,    48,    49,    -1,    51,    -1,    -1,    54,    -1,
      -1,    93,    -1,    95,    -1,    97,    98,     4,     5,     6,
      -1,    -1,    -1,    -1,    -1,     4,     5,     6,    -1,    -1,
      76,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,
      -1,    -1,    29,    -1,    -1,    91,    -1,    -1,    -1,    95,
      29,    97,    98,    -1,   100,    -1,    -1,    44,    45,    -1,
      -1,    48,    49,    -1,    51,    44,    45,    54,    -1,    48,
      49,    -1,    51,    -1,    -1,    54,    23,    24,    -1,    -1,
       4,     5,     6,    30,    31,    32,    33,    34,    35,    76,
      -1,    -1,    -1,    -1,    -1,    82,    -1,    76,    -1,    -1,
      -1,    -1,    -1,    82,    -1,    29,    -1,    -1,    95,    -1,
      97,    98,    -1,   100,    -1,    -1,    95,    -1,    97,    98,
      44,    45,    -1,    -1,    48,    49,    -1,    51,    -1,    -1,
      54,    -1,     3,    -1,    -1,    -1,     5,     6,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    76,    -1,    -1,    -1,    -1,    -1,    82,    -1,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    95,    -1,    97,    98,    44,    45,    -1,    -1,    48,
      49,    -1,    51,    -1,    53,    54,    -1,    -1,    57,    58,
      59,    -1,    61,     5,     6,    64,    -1,    -1,    67,    68,
      69,    70,    -1,    72,    -1,    74,    75,    76,    -1,    -1,
      79,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,
      -1,    -1,    91,    92,    93,    -1,    95,    -1,    97,    98,
      -1,    -1,    44,    45,    -1,    -1,    48,    49,    -1,    51,
      -1,    53,    54,    -1,    -1,    57,    58,    59,    -1,    61,
       5,     6,    64,    -1,    -1,    67,    68,    69,    70,    -1,
      72,    -1,    74,    75,    76,    -1,    -1,    79,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,    91,
      92,    -1,    -1,    95,    -1,    97,    98,     5,     6,    44,
      45,    -1,    -1,    48,    49,    -1,    51,    -1,    53,    54,
      -1,    -1,    57,    58,    59,    -1,    61,    -1,    -1,    64,
      -1,    29,    67,    68,    69,    70,    -1,    72,    -1,    74,
      75,    76,     5,     6,    79,    -1,    44,    45,    -1,    -1,
      48,    49,    -1,    51,    -1,    -1,    54,    -1,    -1,    -1,
      95,    -1,    97,    98,    -1,    -1,    29,    -1,    -1,    -1,
      -1,     5,     6,    -1,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    44,    45,    -1,    -1,    48,    49,    -1,    51,    -1,
      88,    54,    90,    -1,    -1,    29,    -1,    95,    -1,    97,
      98,     5,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    45,    -1,    76,    48,    49,    -1,    51,    -1,    -1,
      54,    -1,    -1,    -1,    87,    29,    89,     5,     6,    -1,
      -1,    -1,    95,    -1,    97,    98,    -1,    -1,     5,     6,
      44,    45,    76,    -1,    48,    49,    -1,    51,    -1,    -1,
      54,    29,    -1,    -1,    -1,    89,     5,     6,    -1,    -1,
      -1,    95,    29,    97,    98,    -1,    44,    45,    -1,    -1,
      48,    49,    76,    51,    -1,    -1,    54,    44,    45,    -1,
      29,    48,    49,    87,    51,    -1,    -1,    54,    -1,    -1,
      -1,    95,    -1,    97,    98,    44,    45,    -1,    76,    48,
      49,    -1,    51,    -1,    -1,    54,    -1,    -1,    -1,    76,
      -1,    89,    -1,    -1,    -1,    -1,    -1,    95,    -1,    97,
      98,     5,     6,     7,     8,    -1,    -1,    76,    95,    -1,
      97,    98,    23,    24,    -1,    -1,    27,    28,    -1,    30,
      31,    32,    33,    34,    35,    -1,    95,    -1,    97,    98,
      -1,    -1,    36,    37,    38,    39,    40,    41,     3,    -1,
      -1,    -1,    46,    47,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    -1,    30,    31,    32,    33,    34,
      35
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     1,     5,     6,    29,    44,    45,    48,    49,    51,
      53,    54,    57,    58,    59,    61,    64,    67,    68,    69,
      70,    72,    74,    75,    76,    77,    78,    93,    95,    97,
      98,   103,   104,   105,   106,   110,   111,   112,   114,   117,
     121,   122,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   138,   139,   140,   143,   144,   149,   154,   155,   156,
     157,   169,   170,   177,   189,    98,   111,   129,   129,   129,
     129,   129,    88,    90,   138,   178,   179,   180,   181,   188,
     188,   188,   188,   188,   188,   188,   111,   141,   142,   141,
     138,     4,    82,    91,   100,   118,   119,   120,   123,   124,
     138,    91,    99,   113,     0,    77,    93,   189,    91,    92,
     190,   191,    54,   137,   126,     5,     6,     7,     8,    36,
      37,    38,    39,    40,    41,    46,    47,     4,    23,    24,
      25,    26,    27,    28,    30,    31,    32,    33,    34,    35,
       3,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    79,    81,    98,   111,   165,
     166,   172,   173,   113,    87,    89,   138,    83,    84,    85,
      86,   182,   183,   184,   185,   186,   187,   180,   179,    92,
     133,   134,   138,    91,    92,    93,   192,   193,   138,   145,
     146,   138,   193,   193,     3,   142,   101,   100,   100,    91,
      92,    99,   115,   116,   120,   124,    91,    92,   110,    54,
      42,    43,    44,    45,    95,    96,    97,   125,   127,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   158,
     160,   158,   159,   171,    81,   111,   158,   167,   168,   171,
      95,   161,   163,   164,   174,   175,   193,    89,   138,    87,
     138,   138,    55,    56,   183,   184,   186,   187,    87,   138,
     179,   181,     3,   193,    91,    92,    93,   107,   108,   109,
     110,   193,    52,    62,    63,   147,   148,   193,   107,   107,
     138,   120,    82,   123,   138,    99,    91,    89,   127,   127,
     127,   127,   101,   124,   100,   124,   127,   188,   159,     3,
     168,    99,    92,   168,     1,    80,   101,   111,   162,   175,
      92,   162,   107,    89,    89,   138,   138,   138,   138,   107,
      60,   192,   193,   107,   188,   188,    65,   150,   151,   152,
      71,    73,   120,    92,   101,   100,    50,    95,   111,   173,
      81,   111,   162,     1,    80,   111,    52,    77,   176,    89,
     138,   193,    52,   138,   110,   193,   193,   188,    52,    66,
     152,   153,   188,   188,   138,   168,   162,   107,   138,   107,
     193,   188,   193,   193,   101,    52,   193,   138,   193,   107,
     107,   107,   193,   107,    52,    52,   107
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylineno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylineno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 500 "parse.y"
    {
		    global_command = yyvsp[0].tree_statement_list_type;
		    promptflag = 1;
		    YYACCEPT;
		  }
    break;

  case 3:
#line 506 "parse.y"
    { ABORT_PARSE; }
    break;

  case 4:
#line 508 "parse.y"
    { ABORT_PARSE; }
    break;

  case 5:
#line 512 "parse.y"
    { yyval.tree_statement_list_type = 0; }
    break;

  case 6:
#line 514 "parse.y"
    {
		    parser_end_of_input = 1;
		    yyval.tree_statement_list_type = 0;
		  }
    break;

  case 7:
#line 519 "parse.y"
    { yyval.tree_statement_list_type = yyvsp[0].tree_statement_list_type; }
    break;

  case 8:
#line 521 "parse.y"
    { yyval.tree_statement_list_type = yyvsp[-1].tree_statement_list_type; }
    break;

  case 9:
#line 523 "parse.y"
    { yyval.tree_statement_list_type = yyvsp[-1].tree_statement_list_type; }
    break;

  case 10:
#line 527 "parse.y"
    {
		    set_stmt_print_flag (yyvsp[-1].tree_statement_list_type, yyvsp[0].sep_type, false);
		    yyval.tree_statement_list_type = yyvsp[-1].tree_statement_list_type;
		  }
    break;

  case 11:
#line 534 "parse.y"
    { yyval.tree_statement_list_type = new tree_statement_list (yyvsp[0].tree_statement_type); }
    break;

  case 12:
#line 536 "parse.y"
    {
		    set_stmt_print_flag (yyvsp[-2].tree_statement_list_type, yyvsp[-1].sep_type, false);
		    yyvsp[-2].tree_statement_list_type->append (yyvsp[0].tree_statement_type);
		    yyval.tree_statement_list_type = yyvsp[-2].tree_statement_list_type;
		  }
    break;

  case 13:
#line 544 "parse.y"
    { yyval.tree_statement_list_type = new tree_statement_list (); }
    break;

  case 14:
#line 546 "parse.y"
    { yyval.tree_statement_list_type = yyvsp[0].tree_statement_list_type; }
    break;

  case 15:
#line 550 "parse.y"
    {
		    set_stmt_print_flag (yyvsp[-1].tree_statement_list_type, yyvsp[0].sep_type, true);
		    yyval.tree_statement_list_type = yyvsp[-1].tree_statement_list_type;
		  }
    break;

  case 16:
#line 557 "parse.y"
    {
		    lexer_flags.beginning_of_function = false;
		    yyval.tree_statement_list_type = new tree_statement_list (yyvsp[0].tree_statement_type);
		  }
    break;

  case 17:
#line 562 "parse.y"
    {
		    set_stmt_print_flag (yyvsp[-2].tree_statement_list_type, yyvsp[-1].sep_type, true);
		    yyvsp[-2].tree_statement_list_type->append (yyvsp[0].tree_statement_type);
		    yyval.tree_statement_list_type = yyvsp[-2].tree_statement_list_type;
		  }
    break;

  case 18:
#line 570 "parse.y"
    {
		    octave_comment_list *comment
		      = octave_comment_buffer::get_comment ();

		    yyval.tree_statement_type = new tree_statement (yyvsp[0].tree_expression_type, comment);
		  }
    break;

  case 19:
#line 577 "parse.y"
    {
		    octave_comment_list *comment
		      = octave_comment_buffer::get_comment ();

		    yyval.tree_statement_type = new tree_statement (yyvsp[0].tree_command_type, comment);
		  }
    break;

  case 20:
#line 584 "parse.y"
    {
		    symbol_record *sr = lookup_by_name ("clearplot", 0);
		    tree_identifier *id = new tree_identifier (sr);

		    octave_comment_list *comment
		      = octave_comment_buffer::get_comment ();

		    yyval.tree_statement_type = new tree_statement (id, comment);
		  }
    break;

  case 21:
#line 600 "parse.y"
    {
		    yyval.tree_identifier_type = new tree_identifier
		      (yyvsp[0].tok_val->sym_rec (), yyvsp[0].tok_val->line (), yyvsp[0].tok_val->column ());
		  }
    break;

  case 22:
#line 607 "parse.y"
    { yyval.tree_constant_type = make_constant (NUM, yyvsp[0].tok_val); }
    break;

  case 23:
#line 609 "parse.y"
    { yyval.tree_constant_type = make_constant (IMAG_NUM, yyvsp[0].tok_val); }
    break;

  case 24:
#line 611 "parse.y"
    { yyval.tree_constant_type = make_constant (STRING, yyvsp[0].tok_val); }
    break;

  case 25:
#line 616 "parse.y"
    { lexer_flags.looking_at_matrix_or_assign_lhs = true; }
    break;

  case 26:
#line 620 "parse.y"
    { yyval.tree_expression_type = new tree_constant (octave_value (Matrix ())); }
    break;

  case 27:
#line 622 "parse.y"
    { yyval.tree_expression_type = new tree_constant (octave_value (Matrix ())); }
    break;

  case 28:
#line 624 "parse.y"
    {
		    yyval.tree_expression_type = finish_matrix (yyvsp[-1].tree_matrix_type);
		    lexer_flags.looking_at_matrix_or_assign_lhs = false;
		  }
    break;

  case 29:
#line 631 "parse.y"
    { yyval.tree_matrix_type = yyvsp[0].tree_matrix_type; }
    break;

  case 30:
#line 633 "parse.y"
    { yyval.tree_matrix_type = yyvsp[-1].tree_matrix_type; }
    break;

  case 31:
#line 637 "parse.y"
    { yyval.tree_matrix_type = new tree_matrix (yyvsp[0].tree_argument_list_type); }
    break;

  case 32:
#line 639 "parse.y"
    {
		    yyvsp[-2].tree_matrix_type->append (yyvsp[0].tree_argument_list_type);
		    yyval.tree_matrix_type = yyvsp[-2].tree_matrix_type;
		  }
    break;

  case 33:
#line 646 "parse.y"
    { yyval.tree_expression_type = new tree_constant (octave_value (Cell ())); }
    break;

  case 34:
#line 648 "parse.y"
    { yyval.tree_expression_type = new tree_constant (octave_value (Cell ())); }
    break;

  case 35:
#line 650 "parse.y"
    { yyval.tree_expression_type = finish_cell (yyvsp[-1].tree_cell_type); }
    break;

  case 36:
#line 654 "parse.y"
    { yyval.tree_cell_type = yyvsp[0].tree_cell_type; }
    break;

  case 37:
#line 656 "parse.y"
    { yyval.tree_cell_type = yyvsp[-1].tree_cell_type; }
    break;

  case 38:
#line 660 "parse.y"
    { yyval.tree_cell_type = new tree_cell (yyvsp[0].tree_argument_list_type); }
    break;

  case 39:
#line 662 "parse.y"
    {
		    yyvsp[-2].tree_cell_type->append (yyvsp[0].tree_argument_list_type);
		    yyval.tree_cell_type = yyvsp[-2].tree_cell_type;
		  }
    break;

  case 40:
#line 670 "parse.y"
    { yyval.tree_argument_list_type = yyvsp[0].tree_argument_list_type; }
    break;

  case 41:
#line 672 "parse.y"
    { yyval.tree_argument_list_type = yyvsp[-1].tree_argument_list_type; }
    break;

  case 42:
#line 676 "parse.y"
    { yyval.tree_fcn_handle_type = make_fcn_handle (yyvsp[0].tok_val); }
    break;

  case 43:
#line 680 "parse.y"
    { yyval.tree_expression_type = yyvsp[0].tree_identifier_type; }
    break;

  case 44:
#line 682 "parse.y"
    { yyval.tree_expression_type = yyvsp[0].tree_constant_type; }
    break;

  case 45:
#line 684 "parse.y"
    { yyval.tree_expression_type = yyvsp[0].tree_fcn_handle_type; }
    break;

  case 46:
#line 686 "parse.y"
    { yyval.tree_expression_type = yyvsp[0].tree_expression_type; }
    break;

  case 47:
#line 688 "parse.y"
    { yyval.tree_expression_type = yyvsp[0].tree_expression_type; }
    break;

  case 48:
#line 690 "parse.y"
    { yyval.tree_expression_type = yyvsp[-1].tree_expression_type->mark_in_parens (); }
    break;

  case 49:
#line 694 "parse.y"
    {
		    octave_value tmp (octave_value::magic_colon_t);
		    yyval.tree_constant_type = new tree_constant (tmp);
		  }
    break;

  case 50:
#line 701 "parse.y"
    { yyval.tree_argument_list_type = new tree_argument_list (yyvsp[0].tree_expression_type); }
    break;

  case 51:
#line 703 "parse.y"
    { yyval.tree_argument_list_type = new tree_argument_list (yyvsp[0].tree_constant_type); }
    break;

  case 52:
#line 705 "parse.y"
    {
		    octave_value tmp (octave_value::all_va_args_t);
		    tree_constant *all_va_args = new tree_constant (tmp);
		    yyval.tree_argument_list_type = new tree_argument_list (all_va_args);
		  }
    break;

  case 53:
#line 711 "parse.y"
    {
		    yyvsp[-2].tree_argument_list_type->append (yyvsp[0].tree_constant_type);
		    yyval.tree_argument_list_type = yyvsp[-2].tree_argument_list_type;
		  }
    break;

  case 54:
#line 716 "parse.y"
    {
		    yyvsp[-2].tree_argument_list_type->append (yyvsp[0].tree_expression_type);
		    yyval.tree_argument_list_type = yyvsp[-2].tree_argument_list_type;
		  }
    break;

  case 55:
#line 721 "parse.y"
    {
		    octave_value tmp (octave_value::all_va_args_t);
		    tree_constant *all_va_args = new tree_constant (tmp);
		    yyvsp[-2].tree_argument_list_type->append (all_va_args);
		    yyval.tree_argument_list_type = yyvsp[-2].tree_argument_list_type;
		  }
    break;

  case 56:
#line 730 "parse.y"
    { lexer_flags.looking_at_indirect_ref = true; }
    break;

  case 57:
#line 741 "parse.y"
    { lexer_flags.looking_at_object_index++; }
    break;

  case 58:
#line 745 "parse.y"
    { lexer_flags.looking_at_object_index--; }
    break;

  case 59:
#line 749 "parse.y"
    { yyval.tree_expression_type = yyvsp[0].tree_expression_type; }
    break;

  case 60:
#line 751 "parse.y"
    {
		    yyval.tree_expression_type = make_index_expression (yyvsp[-3].tree_expression_type, 0, '(');
		    lexer_flags.looking_at_object_index--;
		  }
    break;

  case 61:
#line 756 "parse.y"
    {
		    yyval.tree_expression_type = make_index_expression (yyvsp[-4].tree_expression_type, yyvsp[-1].tree_argument_list_type, '(');
		    lexer_flags.looking_at_object_index--;
		  }
    break;

  case 62:
#line 761 "parse.y"
    {
		    yyval.tree_expression_type = make_index_expression (yyvsp[-3].tree_expression_type, 0, '{');
		    lexer_flags.looking_at_object_index--;
		  }
    break;

  case 63:
#line 766 "parse.y"
    {
		    yyval.tree_expression_type = make_index_expression (yyvsp[-4].tree_expression_type, yyvsp[-1].tree_argument_list_type, '{');
		    lexer_flags.looking_at_object_index--;
		  }
    break;

  case 64:
#line 771 "parse.y"
    { yyval.tree_expression_type = make_postfix_op (PLUS_PLUS, yyvsp[-3].tree_expression_type, yyvsp[-1].tok_val); }
    break;

  case 65:
#line 773 "parse.y"
    { yyval.tree_expression_type = make_postfix_op (MINUS_MINUS, yyvsp[-3].tree_expression_type, yyvsp[-1].tok_val); }
    break;

  case 66:
#line 775 "parse.y"
    { yyval.tree_expression_type = make_postfix_op (QUOTE, yyvsp[-3].tree_expression_type, yyvsp[-1].tok_val); }
    break;

  case 67:
#line 777 "parse.y"
    { yyval.tree_expression_type = make_postfix_op (TRANSPOSE, yyvsp[-3].tree_expression_type, yyvsp[-1].tok_val); }
    break;

  case 68:
#line 779 "parse.y"
    { yyval.tree_expression_type = make_indirect_ref (yyvsp[-4].tree_expression_type, yyvsp[0].tok_val->text ()); }
    break;

  case 69:
#line 781 "parse.y"
    { yyval.tree_expression_type = make_indirect_ref (yyvsp[-6].tree_expression_type, yyvsp[-1].tree_expression_type); }
    break;

  case 70:
#line 785 "parse.y"
    { yyval.tree_expression_type = yyvsp[-2].tree_expression_type; }
    break;

  case 71:
#line 787 "parse.y"
    { yyval.tree_expression_type = yyvsp[0].tree_expression_type; }
    break;

  case 72:
#line 789 "parse.y"
    { yyval.tree_expression_type = make_prefix_op (PLUS_PLUS, yyvsp[0].tree_expression_type, yyvsp[-1].tok_val); }
    break;

  case 73:
#line 791 "parse.y"
    { yyval.tree_expression_type = make_prefix_op (MINUS_MINUS, yyvsp[0].tree_expression_type, yyvsp[-1].tok_val); }
    break;

  case 74:
#line 793 "parse.y"
    { yyval.tree_expression_type = make_prefix_op (EXPR_NOT, yyvsp[0].tree_expression_type, yyvsp[-1].tok_val); }
    break;

  case 75:
#line 795 "parse.y"
    { yyval.tree_expression_type = yyvsp[0].tree_expression_type; }
    break;

  case 76:
#line 797 "parse.y"
    { yyval.tree_expression_type = make_prefix_op ('-', yyvsp[0].tree_expression_type, yyvsp[-1].tok_val); }
    break;

  case 77:
#line 801 "parse.y"
    { yyval.tree_expression_type = make_binary_op (POW, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 78:
#line 803 "parse.y"
    { yyval.tree_expression_type = make_binary_op (EPOW, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 79:
#line 805 "parse.y"
    { yyval.tree_expression_type = make_binary_op ('+', yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 80:
#line 807 "parse.y"
    { yyval.tree_expression_type = make_binary_op ('-', yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 81:
#line 809 "parse.y"
    { yyval.tree_expression_type = make_binary_op ('*', yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 82:
#line 811 "parse.y"
    { yyval.tree_expression_type = make_binary_op ('/', yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 83:
#line 813 "parse.y"
    { yyval.tree_expression_type = make_binary_op ('+', yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 84:
#line 815 "parse.y"
    { yyval.tree_expression_type = make_binary_op ('-', yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 85:
#line 817 "parse.y"
    { yyval.tree_expression_type = make_binary_op (EMUL, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 86:
#line 819 "parse.y"
    { yyval.tree_expression_type = make_binary_op (EDIV, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 87:
#line 821 "parse.y"
    { yyval.tree_expression_type = make_binary_op (LEFTDIV, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 88:
#line 823 "parse.y"
    { yyval.tree_expression_type = make_binary_op (ELEFTDIV, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 89:
#line 827 "parse.y"
    { yyval.tree_expression_type = finish_colon_expression (yyvsp[0].tree_colon_expression_type); }
    break;

  case 90:
#line 831 "parse.y"
    { yyval.tree_colon_expression_type = new tree_colon_expression (yyvsp[0].tree_expression_type); }
    break;

  case 91:
#line 833 "parse.y"
    {
		    if (! (yyval.tree_colon_expression_type = yyvsp[-2].tree_colon_expression_type->append (yyvsp[0].tree_expression_type)))
		      ABORT_PARSE;
		  }
    break;

  case 92:
#line 840 "parse.y"
    { yyval.tree_expression_type = yyvsp[0].tree_expression_type; }
    break;

  case 93:
#line 842 "parse.y"
    { yyval.tree_expression_type = make_binary_op (LSHIFT, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 94:
#line 844 "parse.y"
    { yyval.tree_expression_type = make_binary_op (RSHIFT, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 95:
#line 846 "parse.y"
    { yyval.tree_expression_type = make_binary_op (EXPR_LT, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 96:
#line 848 "parse.y"
    { yyval.tree_expression_type = make_binary_op (EXPR_LE, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 97:
#line 850 "parse.y"
    { yyval.tree_expression_type = make_binary_op (EXPR_EQ, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 98:
#line 852 "parse.y"
    { yyval.tree_expression_type = make_binary_op (EXPR_GE, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 99:
#line 854 "parse.y"
    { yyval.tree_expression_type = make_binary_op (EXPR_GT, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 100:
#line 856 "parse.y"
    { yyval.tree_expression_type = make_binary_op (EXPR_NE, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 101:
#line 858 "parse.y"
    { yyval.tree_expression_type = make_binary_op (EXPR_AND, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 102:
#line 860 "parse.y"
    { yyval.tree_expression_type = make_binary_op (EXPR_OR, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 103:
#line 862 "parse.y"
    { yyval.tree_expression_type = make_boolean_op (EXPR_AND_AND, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 104:
#line 864 "parse.y"
    { yyval.tree_expression_type = make_boolean_op (EXPR_OR_OR, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 105:
#line 871 "parse.y"
    { yyval.tree_argument_list_type = new tree_argument_list (yyvsp[0].tree_expression_type); }
    break;

  case 106:
#line 873 "parse.y"
    {
		    yyval.tree_argument_list_type = yyvsp[-1].tree_argument_list_type;
		    lexer_flags.looking_at_matrix_or_assign_lhs = false;
		  }
    break;

  case 107:
#line 880 "parse.y"
    { yyval.tree_expression_type = make_assign_op ('=', yyvsp[-2].tree_argument_list_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 108:
#line 882 "parse.y"
    { yyval.tree_expression_type = make_assign_op (ADD_EQ, yyvsp[-2].tree_argument_list_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 109:
#line 884 "parse.y"
    { yyval.tree_expression_type = make_assign_op (SUB_EQ, yyvsp[-2].tree_argument_list_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 110:
#line 886 "parse.y"
    { yyval.tree_expression_type = make_assign_op (MUL_EQ, yyvsp[-2].tree_argument_list_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 111:
#line 888 "parse.y"
    { yyval.tree_expression_type = make_assign_op (DIV_EQ, yyvsp[-2].tree_argument_list_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 112:
#line 890 "parse.y"
    { yyval.tree_expression_type = make_assign_op (LEFTDIV_EQ, yyvsp[-2].tree_argument_list_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 113:
#line 892 "parse.y"
    { yyval.tree_expression_type = make_assign_op (POW_EQ, yyvsp[-2].tree_argument_list_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 114:
#line 894 "parse.y"
    { yyval.tree_expression_type = make_assign_op (LSHIFT_EQ, yyvsp[-2].tree_argument_list_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 115:
#line 896 "parse.y"
    { yyval.tree_expression_type = make_assign_op (RSHIFT_EQ, yyvsp[-2].tree_argument_list_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 116:
#line 898 "parse.y"
    { yyval.tree_expression_type = make_assign_op (EMUL_EQ, yyvsp[-2].tree_argument_list_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 117:
#line 900 "parse.y"
    { yyval.tree_expression_type = make_assign_op (EDIV_EQ, yyvsp[-2].tree_argument_list_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 118:
#line 902 "parse.y"
    { yyval.tree_expression_type = make_assign_op (ELEFTDIV_EQ, yyvsp[-2].tree_argument_list_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 119:
#line 904 "parse.y"
    { yyval.tree_expression_type = make_assign_op (EPOW_EQ, yyvsp[-2].tree_argument_list_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 120:
#line 906 "parse.y"
    { yyval.tree_expression_type = make_assign_op (AND_EQ, yyvsp[-2].tree_argument_list_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 121:
#line 908 "parse.y"
    { yyval.tree_expression_type = make_assign_op (OR_EQ, yyvsp[-2].tree_argument_list_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;

  case 122:
#line 912 "parse.y"
    { yyval.tree_index_expression_type = make_index_expression (yyvsp[-1].tree_identifier_type, yyvsp[0].tree_argument_list_type, '('); }
    break;

  case 123:
#line 916 "parse.y"
    {
		    tree_constant *tmp = make_constant (STRING, yyvsp[0].tok_val);
		    yyval.tree_argument_list_type = new tree_argument_list (tmp);
		  }
    break;

  case 124:
#line 921 "parse.y"
    {
		    tree_constant *tmp = make_constant (STRING, yyvsp[0].tok_val);
		    yyvsp[-1].tree_argument_list_type->append (tmp);
		    yyval.tree_argument_list_type = yyvsp[-1].tree_argument_list_type;
		  }
    break;

  case 125:
#line 929 "parse.y"
    { yyval.tree_expression_type = yyvsp[0].tree_expression_type; }
    break;

  case 126:
#line 931 "parse.y"
    { yyval.tree_expression_type = yyvsp[0].tree_index_expression_type; }
    break;

  case 127:
#line 933 "parse.y"
    { yyval.tree_expression_type = yyvsp[0].tree_expression_type; }
    break;

  case 128:
#line 941 "parse.y"
    { yyval.tree_command_type = yyvsp[0].tree_decl_command_type; }
    break;

  case 129:
#line 943 "parse.y"
    { yyval.tree_command_type = yyvsp[0].tree_command_type; }
    break;

  case 130:
#line 945 "parse.y"
    { yyval.tree_command_type = yyvsp[0].tree_command_type; }
    break;

  case 131:
#line 947 "parse.y"
    { yyval.tree_command_type = yyvsp[0].tree_command_type; }
    break;

  case 132:
#line 949 "parse.y"
    { yyval.tree_command_type = yyvsp[0].tree_command_type; }
    break;

  case 133:
#line 951 "parse.y"
    { yyval.tree_command_type = yyvsp[0].tree_command_type; }
    break;

  case 134:
#line 953 "parse.y"
    { yyval.tree_command_type = yyvsp[0].tree_plot_command_type; }
    break;

  case 135:
#line 961 "parse.y"
    { yyval.tree_decl_command_type = make_decl_command (GLOBAL, yyvsp[-1].tok_val, yyvsp[0].tree_decl_init_list_type); }
    break;

  case 136:
#line 963 "parse.y"
    { yyval.tree_decl_command_type = make_decl_command (STATIC, yyvsp[-1].tok_val, yyvsp[0].tree_decl_init_list_type); }
    break;

  case 137:
#line 967 "parse.y"
    { yyval.tree_decl_init_list_type = new tree_decl_init_list (yyvsp[0].tree_decl_elt_type); }
    break;

  case 138:
#line 969 "parse.y"
    {
		    yyvsp[-1].tree_decl_init_list_type->append (yyvsp[0].tree_decl_elt_type);
		    yyval.tree_decl_init_list_type = yyvsp[-1].tree_decl_init_list_type;
		  }
    break;

  case 139:
#line 976 "parse.y"
    { yyval.tree_decl_elt_type = new tree_decl_elt (yyvsp[0].tree_identifier_type); }
    break;

  case 140:
#line 978 "parse.y"
    { yyval.tree_decl_elt_type = new tree_decl_elt (yyvsp[-2].tree_identifier_type, yyvsp[0].tree_expression_type); }
    break;

  case 141:
#line 986 "parse.y"
    { yyval.tree_command_type = yyvsp[0].tree_if_command_type; }
    break;

  case 142:
#line 988 "parse.y"
    { yyval.tree_command_type = yyvsp[0].tree_switch_command_type; }
    break;

  case 143:
#line 996 "parse.y"
    {
		    if (! (yyval.tree_if_command_type = finish_if_command (yyvsp[-3].tok_val, yyvsp[-1].tree_if_command_list_type, yyvsp[0].tok_val, yyvsp[-2].comment_type)))
		      ABORT_PARSE;
		  }
    break;

  case 144:
#line 1003 "parse.y"
    { yyval.tree_if_command_list_type = yyvsp[0].tree_if_command_list_type; }
    break;

  case 145:
#line 1005 "parse.y"
    {
		    yyvsp[-1].tree_if_command_list_type->append (yyvsp[0].tree_if_clause_type);
		    yyval.tree_if_command_list_type = yyvsp[-1].tree_if_command_list_type;
		  }
    break;

  case 146:
#line 1012 "parse.y"
    { yyval.tree_if_command_list_type = start_if_command (yyvsp[-2].tree_expression_type, yyvsp[0].tree_statement_list_type); }
    break;

  case 147:
#line 1014 "parse.y"
    {
		    yyvsp[-1].tree_if_command_list_type->append (yyvsp[0].tree_if_clause_type);
		    yyval.tree_if_command_list_type = yyvsp[-1].tree_if_command_list_type;
		  }
    break;

  case 148:
#line 1021 "parse.y"
    { yyval.tree_if_clause_type = make_elseif_clause (yyvsp[-2].tree_expression_type, yyvsp[0].tree_statement_list_type, yyvsp[-4].comment_type); }
    break;

  case 149:
#line 1025 "parse.y"
    {
		    yyval.tree_if_clause_type = new tree_if_clause (yyvsp[0].tree_statement_list_type, yyvsp[-2].comment_type);
		  }
    break;

  case 150:
#line 1035 "parse.y"
    {
		    if (! (yyval.tree_switch_command_type = finish_switch_command (yyvsp[-5].tok_val, yyvsp[-3].tree_expression_type, yyvsp[-1].tree_switch_case_list_type, yyvsp[0].tok_val, yyvsp[-4].comment_type)))
		      ABORT_PARSE;
		  }
    break;

  case 151:
#line 1042 "parse.y"
    { yyval.tree_switch_case_list_type = new tree_switch_case_list (); }
    break;

  case 152:
#line 1044 "parse.y"
    { yyval.tree_switch_case_list_type = yyvsp[0].tree_switch_case_list_type; }
    break;

  case 153:
#line 1046 "parse.y"
    {
		    yyvsp[-1].tree_switch_case_list_type->append (yyvsp[0].tree_switch_case_type);
		    yyval.tree_switch_case_list_type = yyvsp[-1].tree_switch_case_list_type;
		  }
    break;

  case 154:
#line 1053 "parse.y"
    { yyval.tree_switch_case_list_type = new tree_switch_case_list (yyvsp[0].tree_switch_case_type); }
    break;

  case 155:
#line 1055 "parse.y"
    {
		    yyvsp[-1].tree_switch_case_list_type->append (yyvsp[0].tree_switch_case_type);
		    yyval.tree_switch_case_list_type = yyvsp[-1].tree_switch_case_list_type;
		  }
    break;

  case 156:
#line 1062 "parse.y"
    { yyval.tree_switch_case_type = make_switch_case (yyvsp[-2].tree_expression_type, yyvsp[0].tree_statement_list_type, yyvsp[-4].comment_type); }
    break;

  case 157:
#line 1066 "parse.y"
    {
		    yyval.tree_switch_case_type = new tree_switch_case (yyvsp[0].tree_statement_list_type, yyvsp[-2].comment_type);
		  }
    break;

  case 158:
#line 1076 "parse.y"
    {
		    if (! (yyval.tree_command_type = make_while_command (yyvsp[-5].tok_val, yyvsp[-3].tree_expression_type, yyvsp[-1].tree_statement_list_type, yyvsp[0].tok_val, yyvsp[-4].comment_type)))
		      ABORT_PARSE;
		  }
    break;

  case 159:
#line 1081 "parse.y"
    {
		    if (! (yyval.tree_command_type = make_do_until_command (yyvsp[-5].tok_val, yyvsp[-2].tree_statement_list_type, yyvsp[0].tree_expression_type, yyvsp[-4].comment_type)))
		      ABORT_PARSE;
		  }
    break;

  case 160:
#line 1086 "parse.y"
    {
		    if (! (yyval.tree_command_type = make_for_command (yyvsp[-7].tok_val, yyvsp[-5].tree_argument_list_type, yyvsp[-3].tree_expression_type, yyvsp[-1].tree_statement_list_type, yyvsp[0].tok_val, yyvsp[-6].comment_type)))
		      ABORT_PARSE;
		  }
    break;

  case 161:
#line 1097 "parse.y"
    {
		    if (! (yyval.tree_command_type = make_break_command (yyvsp[0].tok_val)))
		      ABORT_PARSE;
		  }
    break;

  case 162:
#line 1102 "parse.y"
    {
		    if (! (yyval.tree_command_type = make_continue_command (yyvsp[0].tok_val)))
		      ABORT_PARSE;
		  }
    break;

  case 163:
#line 1107 "parse.y"
    {
		    if (! (yyval.tree_command_type = make_return_command (yyvsp[0].tok_val)))
		      ABORT_PARSE;
		  }
    break;

  case 164:
#line 1119 "parse.y"
    {
		    if (! (yyval.tree_command_type = make_unwind_command (yyvsp[-8].tok_val, yyvsp[-5].tree_statement_list_type, yyvsp[-1].tree_statement_list_type, yyvsp[0].tok_val, yyvsp[-7].comment_type, yyvsp[-3].comment_type)))
		      ABORT_PARSE;
		  }
    break;

  case 165:
#line 1125 "parse.y"
    {
		    if (! (yyval.tree_command_type = make_try_command (yyvsp[-8].tok_val, yyvsp[-5].tree_statement_list_type, yyvsp[-1].tree_statement_list_type, yyvsp[0].tok_val, yyvsp[-7].comment_type, yyvsp[-3].comment_type)))
		      ABORT_PARSE;
		  }
    break;

  case 166:
#line 1136 "parse.y"
    { symtab_context.push (curr_sym_tab); }
    break;

  case 167:
#line 1140 "parse.y"
    { curr_sym_tab = fbi_sym_tab; }
    break;

  case 168:
#line 1144 "parse.y"
    { curr_sym_tab = tmp_local_sym_tab; }
    break;

  case 169:
#line 1148 "parse.y"
    { lexer_flags.looking_at_return_list = true; }
    break;

  case 170:
#line 1156 "parse.y"
    { lexer_flags.looking_at_parameter_list = true; }
    break;

  case 171:
#line 1160 "parse.y"
    { lexer_flags.looking_at_parameter_list = false; }
    break;

  case 172:
#line 1164 "parse.y"
    {
		    lexer_flags.quote_is_transpose = false;
		    yyval.tree_parameter_list_type = 0;
		  }
    break;

  case 173:
#line 1169 "parse.y"
    {
		    lexer_flags.quote_is_transpose = false;
		    tree_parameter_list *tmp = new tree_parameter_list ();
		    tmp->mark_varargs_only ();
		    yyval.tree_parameter_list_type = tmp;
		  }
    break;

  case 174:
#line 1176 "parse.y"
    {
		    lexer_flags.quote_is_transpose = false;
		    yyvsp[-1].tree_parameter_list_type->mark_as_formal_parameters ();
		    yyval.tree_parameter_list_type = yyvsp[-1].tree_parameter_list_type;
		  }
    break;

  case 175:
#line 1182 "parse.y"
    {
		    lexer_flags.quote_is_transpose = false;
		    yyvsp[-3].tree_parameter_list_type->mark_as_formal_parameters ();
		    yyvsp[-3].tree_parameter_list_type->mark_varargs ();
		    yyval.tree_parameter_list_type = yyvsp[-3].tree_parameter_list_type;
		  }
    break;

  case 176:
#line 1191 "parse.y"
    { yyval.tree_parameter_list_type = new tree_parameter_list (yyvsp[0].tree_identifier_type); }
    break;

  case 177:
#line 1193 "parse.y"
    {
		    yyvsp[-2].tree_parameter_list_type->append (yyvsp[0].tree_identifier_type);
		    yyval.tree_parameter_list_type = yyvsp[-2].tree_parameter_list_type;
		  }
    break;

  case 178:
#line 1198 "parse.y"
    {
		    yyerror ("invalid parameter list");
		    yyval.tree_parameter_list_type = 0;
		    ABORT_PARSE;
		  }
    break;

  case 179:
#line 1204 "parse.y"
    {
		    yyerror ("invalid parameter list");
		    yyval.tree_parameter_list_type = 0;
		    ABORT_PARSE;
		  }
    break;

  case 181:
#line 1219 "parse.y"
    {
		    lexer_flags.looking_at_return_list = false;
		    yyval.tree_parameter_list_type = new tree_parameter_list ();
		  }
    break;

  case 182:
#line 1224 "parse.y"
    {
		    lexer_flags.looking_at_return_list = false;
		    tree_parameter_list *tmp = new tree_parameter_list ();
		    tmp->mark_varargs_only ();
		    yyval.tree_parameter_list_type = tmp;
		  }
    break;

  case 183:
#line 1231 "parse.y"
    {
		    lexer_flags.looking_at_return_list = false;
		    tree_parameter_list *tmp = new tree_parameter_list ();
		    tmp->mark_varargs_only ();
		    yyval.tree_parameter_list_type = tmp;
		  }
    break;

  case 184:
#line 1238 "parse.y"
    {
		    lexer_flags.looking_at_return_list = false;
		    yyval.tree_parameter_list_type = yyvsp[-1].tree_parameter_list_type;
		  }
    break;

  case 185:
#line 1243 "parse.y"
    {
		    lexer_flags.looking_at_return_list = false;
		    yyvsp[-3].tree_parameter_list_type->mark_varargs ();
		    yyval.tree_parameter_list_type = yyvsp[-3].tree_parameter_list_type;
		  }
    break;

  case 186:
#line 1251 "parse.y"
    { yyval.tree_parameter_list_type = new tree_parameter_list (yyvsp[0].tree_identifier_type); }
    break;

  case 187:
#line 1253 "parse.y"
    {
		    yyvsp[-2].tree_parameter_list_type->append (yyvsp[0].tree_identifier_type);
		    yyval.tree_parameter_list_type = yyvsp[-2].tree_parameter_list_type;
		  }
    break;

  case 189:
#line 1267 "parse.y"
    { yyval.comment_type = yyvsp[0].comment_type; }
    break;

  case 190:
#line 1271 "parse.y"
    {
		    yyvsp[0].octave_user_function_type->stash_leading_comment (yyvsp[-1].comment_type);
		    recover_from_parsing_function ();
		    yyval.tree_command_type = 0;
		  }
    break;

  case 191:
#line 1277 "parse.y"
    {
		    finish_function (yyvsp[-1].tree_identifier_type, yyvsp[0].octave_user_function_type, yyvsp[-2].comment_type);
		    recover_from_parsing_function ();
		    yyval.tree_command_type = 0;
		  }
    break;

  case 192:
#line 1283 "parse.y"
    {
		    finish_function (yyvsp[-1].tree_parameter_list_type, yyvsp[0].octave_user_function_type, yyvsp[-2].comment_type);
		    recover_from_parsing_function ();
		    yyval.tree_command_type = 0;
		  }
    break;

  case 193:
#line 1291 "parse.y"
    { yyval.octave_user_function_type = yyvsp[0].octave_user_function_type; }
    break;

  case 194:
#line 1295 "parse.y"
    {
		    std::string id_name = yyvsp[-1].tree_identifier_type->name ();

		    if (reading_fcn_file
		        && ! lexer_flags.parsing_nested_function)
		      parent_function_name = (curr_fcn_file_name == id_name)
			? id_name : curr_fcn_file_name;

		    lexer_flags.parsed_function_name = true;

		    yyval.tree_identifier_type = yyvsp[-1].tree_identifier_type;
		  }
    break;

  case 195:
#line 1310 "parse.y"
    {
		    if (! (yyval.octave_user_function_type = frob_function (yyvsp[-1].tree_identifier_type, yyvsp[0].octave_user_function_type)))
		      ABORT_PARSE;
		  }
    break;

  case 196:
#line 1317 "parse.y"
    { yyval.octave_user_function_type = start_function (yyvsp[-1].tree_parameter_list_type, yyvsp[0].tree_statement_list_type); }
    break;

  case 197:
#line 1319 "parse.y"
    { yyval.octave_user_function_type = start_function (0, yyvsp[0].tree_statement_list_type); }
    break;

  case 198:
#line 1323 "parse.y"
    { yyval.tree_statement_list_type = yyvsp[-1].tree_statement_list_type; }
    break;

  case 199:
#line 1327 "parse.y"
    {
		    if (! end_token_ok (yyvsp[0].tok_val, token::function_end))
		      ABORT_PARSE;
		  }
    break;

  case 200:
#line 1332 "parse.y"
    {
		    if (lexer_flags.parsing_nested_function)
		      lexer_flags.parsing_nested_function = -1;

		    if (! (reading_fcn_file || reading_script_file
			   || get_input_from_eval_string))
		      YYABORT;
		  }
    break;

  case 201:
#line 1347 "parse.y"
    {
		    if (! (yyval.tree_plot_command_type = make_plot_command (yyvsp[0].tok_val, 0, 0)))
		      ABORT_PARSE;
		  }
    break;

  case 202:
#line 1352 "parse.y"
    {
		    if (! (yyval.tree_plot_command_type = make_plot_command (yyvsp[-1].tok_val, yyvsp[0].plot_limits_type, 0)))
		      ABORT_PARSE;
		  }
    break;

  case 203:
#line 1357 "parse.y"
    {
		    if (! (yyval.tree_plot_command_type = make_plot_command (yyvsp[-1].tok_val, 0, yyvsp[0].subplot_list_type)))
		      ABORT_PARSE;
		  }
    break;

  case 204:
#line 1362 "parse.y"
    {
		    if (! (yyval.tree_plot_command_type = make_plot_command (yyvsp[-2].tok_val, yyvsp[-1].plot_limits_type, yyvsp[0].subplot_list_type)))
		      ABORT_PARSE;
		  }
    break;

  case 205:
#line 1369 "parse.y"
    { yyval.plot_limits_type = new plot_limits (yyvsp[0].plot_range_type); }
    break;

  case 206:
#line 1371 "parse.y"
    { yyval.plot_limits_type = new plot_limits (yyvsp[-1].plot_range_type, yyvsp[0].plot_range_type); }
    break;

  case 207:
#line 1373 "parse.y"
    { yyval.plot_limits_type = new plot_limits (yyvsp[-2].plot_range_type, yyvsp[-1].plot_range_type, yyvsp[0].plot_range_type); }
    break;

  case 208:
#line 1377 "parse.y"
    { yyval.plot_range_type = new plot_range (yyvsp[-3].tree_expression_type, yyvsp[-1].tree_expression_type); }
    break;

  case 209:
#line 1379 "parse.y"
    { yyval.plot_range_type = new plot_range (0, yyvsp[-1].tree_expression_type); }
    break;

  case 210:
#line 1381 "parse.y"
    { yyval.plot_range_type = new plot_range (yyvsp[-2].tree_expression_type, 0); }
    break;

  case 211:
#line 1383 "parse.y"
    { yyval.plot_range_type = new plot_range (); }
    break;

  case 212:
#line 1385 "parse.y"
    { yyval.plot_range_type = new plot_range (); }
    break;

  case 213:
#line 1389 "parse.y"
    { yyval.subplot_list_type = new subplot_list (yyvsp[0].subplot_type); }
    break;

  case 214:
#line 1391 "parse.y"
    {
		    yyvsp[-2].subplot_list_type->append (yyvsp[0].subplot_type);
		    yyval.subplot_list_type = yyvsp[-2].subplot_list_type;
		  }
    break;

  case 215:
#line 1398 "parse.y"
    { yyval.subplot_type = new subplot (yyvsp[0].tree_expression_type); }
    break;

  case 216:
#line 1400 "parse.y"
    { yyval.subplot_type = yyvsp[0].subplot_type->add_data (yyvsp[-1].tree_expression_type); }
    break;

  case 217:
#line 1404 "parse.y"
    {
		    subplot *tmp = new subplot ();
		    yyval.subplot_type = tmp->add_clause (yyvsp[0].subplot_using_type);
		  }
    break;

  case 218:
#line 1409 "parse.y"
    {
		    subplot *tmp = new subplot ();
		    yyval.subplot_type = tmp->add_clause (yyvsp[0].tree_expression_type);
		  }
    break;

  case 219:
#line 1414 "parse.y"
    {
		    subplot *tmp = new subplot ();
		    yyval.subplot_type = tmp->add_clause (yyvsp[0].subplot_style_type);
		  }
    break;

  case 220:
#line 1419 "parse.y"
    {
		    subplot *tmp = new subplot ();
		    yyval.subplot_type = tmp->add_clause (yyvsp[0].subplot_axes_type);
		  }
    break;

  case 221:
#line 1424 "parse.y"
    {
		    if (! (yyval.subplot_type = yyvsp[-1].subplot_type->add_clause (yyvsp[0].subplot_using_type)))
		      {
			yyerror ("only one using option may be specified");
			ABORT_PARSE;
		      }
		  }
    break;

  case 222:
#line 1432 "parse.y"
    {
		    if (! (yyval.subplot_type = yyvsp[-1].subplot_type->add_clause (yyvsp[0].tree_expression_type)))
		      {
			yyerror ("only one title option my be specified");
			ABORT_PARSE;
		      }
		  }
    break;

  case 223:
#line 1440 "parse.y"
    {
		    if (! (yyval.subplot_type = yyvsp[-1].subplot_type->add_clause (yyvsp[0].subplot_style_type)))
		      {
			yyerror ("only one style option my be specified");
			ABORT_PARSE;
		      }
		  }
    break;

  case 224:
#line 1448 "parse.y"
    {
		    if (! (yyval.subplot_type = yyvsp[-1].subplot_type->add_clause (yyvsp[0].subplot_axes_type)))
		      {
			yyerror ("only one axes option may be specified");
			ABORT_PARSE;
		      }
		  }
    break;

  case 225:
#line 1458 "parse.y"
    {
		    lexer_flags.in_plot_axes = false;
		    yyval.subplot_axes_type = new subplot_axes (yyvsp[0].tok_val->text ());
		  }
    break;

  case 226:
#line 1465 "parse.y"
    {
		    lexer_flags.in_plot_using = false;
		    yyval.subplot_using_type = yyvsp[0].subplot_using_type;
		  }
    break;

  case 227:
#line 1470 "parse.y"
    {
		    lexer_flags.in_plot_using = false;
		    yyval.subplot_using_type = yyvsp[-1].subplot_using_type->set_format (yyvsp[0].tree_expression_type);
		  }
    break;

  case 228:
#line 1477 "parse.y"
    {
		    subplot_using *tmp = new subplot_using ();
		    yyval.subplot_using_type = tmp->add_qualifier (yyvsp[0].tree_expression_type);
		  }
    break;

  case 229:
#line 1482 "parse.y"
    { yyval.subplot_using_type = yyvsp[-2].subplot_using_type->add_qualifier (yyvsp[0].tree_expression_type); }
    break;

  case 230:
#line 1486 "parse.y"
    { yyval.tree_expression_type = yyvsp[0].tree_expression_type; }
    break;

  case 231:
#line 1490 "parse.y"
    { yyval.subplot_style_type = new subplot_style (yyvsp[0].tok_val->text ()); }
    break;

  case 232:
#line 1492 "parse.y"
    { yyval.subplot_style_type = new subplot_style (yyvsp[-1].tok_val->text (), yyvsp[0].tree_expression_type); }
    break;

  case 233:
#line 1494 "parse.y"
    { yyval.subplot_style_type = new subplot_style (yyvsp[-2].tok_val->text (), yyvsp[-1].tree_expression_type, yyvsp[0].tree_expression_type); }
    break;

  case 234:
#line 1502 "parse.y"
    { yyval.comment_type = octave_comment_buffer::get_comment (); }
    break;

  case 235:
#line 1506 "parse.y"
    { yyerror ("parse error"); }
    break;

  case 237:
#line 1511 "parse.y"
    { yyval.sep_type = ','; }
    break;

  case 238:
#line 1513 "parse.y"
    { yyval.sep_type = ';'; }
    break;

  case 239:
#line 1515 "parse.y"
    { yyval.sep_type = yyvsp[-1].sep_type; }
    break;

  case 240:
#line 1517 "parse.y"
    { yyval.sep_type = yyvsp[-1].sep_type; }
    break;

  case 241:
#line 1521 "parse.y"
    { yyval.sep_type = 0; }
    break;

  case 242:
#line 1523 "parse.y"
    { yyval.sep_type = yyvsp[0].sep_type; }
    break;

  case 243:
#line 1527 "parse.y"
    { yyval.sep_type = ','; }
    break;

  case 244:
#line 1529 "parse.y"
    { yyval.sep_type = ';'; }
    break;

  case 245:
#line 1531 "parse.y"
    { yyval.sep_type = '\n'; }
    break;

  case 246:
#line 1533 "parse.y"
    { yyval.sep_type = yyvsp[-1].sep_type; }
    break;

  case 247:
#line 1535 "parse.y"
    { yyval.sep_type = yyvsp[-1].sep_type; }
    break;

  case 248:
#line 1537 "parse.y"
    { yyval.sep_type = yyvsp[-1].sep_type; }
    break;

  case 249:
#line 1541 "parse.y"
    { yyval.sep_type = 0; }
    break;

  case 250:
#line 1543 "parse.y"
    { yyval.sep_type = yyvsp[0].sep_type; }
    break;


    }

/* Line 999 of yacc.c.  */
#line 3602 "y.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("syntax error, unexpected ") + 1;
	  yysize += yystrlen (yytname[yytype]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyss < yyssp)
	    {
	      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
	      yydestruct (yystos[*yyssp], yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval);
      yychar = YYEMPTY;

    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      yyvsp--;
      yystate = *--yyssp;

      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 1546 "parse.y"


// Generic error messages.

static void
yyerror (const char *s)
{
  int err_col = current_input_column - 1;

  OSSTREAM output_buf;

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

  output_buf << "\n" << OSSTREAM_ENDS;

  parse_error ("%s", OSSTREAM_C_STR (output_buf));

  OSSTREAM_FREEZE (output_buf);
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
  unwind_protect_int (warning_state);

  unwind_protect_bool (discard_error_messages);
  unwind_protect_bool (discard_warning_messages);

  discard_error_messages = true;
  discard_warning_messages = true;

  tree_expression *op1 = e->lhs ();
  tree_expression *op2 = e->rhs ();

  if (op1->is_constant () && op2->is_constant ())
    {
      octave_value tmp = e->rvalue ();

      if (! (error_state || warning_state))
	{
	  tree_constant *tc_retval = new tree_constant (tmp);

	  OSSTREAM buf;

	  tree_print_code tpc (buf);

	  e->accept (tpc);

	  buf << OSSTREAM_ENDS;

	  tc_retval->stash_original_text (OSSTREAM_STR (buf));

	  OSSTREAM_FREEZE (buf);

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
  unwind_protect_int (warning_state);

  unwind_protect_bool (discard_error_messages);
  unwind_protect_bool (discard_warning_messages);

  discard_error_messages = true;
  discard_warning_messages = true;

  tree_expression *op = e->operand ();

  if (op->is_constant ())
    {
      octave_value tmp = e->rvalue ();

      if (! (error_state || warning_state))
	{
	  tree_constant *tc_retval = new tree_constant (tmp);

	  OSSTREAM buf;

	  tree_print_code tpc (buf);

	  e->accept (tpc);

	  buf << OSSTREAM_ENDS;

	  tc_retval->stash_original_text (OSSTREAM_STR (buf));

	  OSSTREAM_FREEZE (buf);

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
  unwind_protect_int (warning_state);

  unwind_protect_bool (discard_error_messages);
  unwind_protect_bool (discard_warning_messages);

  discard_error_messages = true;
  discard_warning_messages = true;

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

		  OSSTREAM buf;

		  tree_print_code tpc (buf);

		  e->accept (tpc);

		  buf << OSSTREAM_ENDS;

		  tc_retval->stash_original_text (OSSTREAM_STR (buf));

		  OSSTREAM_FREEZE (buf);

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

    case STRING:
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

// Make a function handle.

static tree_fcn_handle *
make_fcn_handle (token *tok_val)
{
  int l = tok_val->line ();
  int c = tok_val->column ();

  tree_fcn_handle *retval = new tree_fcn_handle (tok_val->text (), l, c);

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
      if (Vwarn_precedence_change
          && op2->paren_count () == 0 && op2->is_binary_expression ())
        {
	  tree_binary_expression *e
	    = dynamic_cast<tree_binary_expression *> (op2);

	  if (e->op_type () == octave_value::op_el_and)
	    warning ("meaning may have changed due to change in precedence for & and | operators");
        }
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
      if (Vwarn_precedence_change
          && op2->paren_count () == 0 && op2->is_boolean_expression ())
        {
	  tree_boolean_expression *e
	    = dynamic_cast<tree_boolean_expression *> (op2);

	  if (e->op_type () == tree_boolean_expression::bool_and)
	    warning ("meaning may have changed due to change in precedence for && and || operators");
        }
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

    case POW_EQ:
      t = octave_value::op_pow_eq;
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

    case EPOW_EQ:
      t = octave_value::op_el_pow_eq;
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
      if (! lexer_flags.parsing_nested_function
          && curr_fcn_file_name != id_name)
	{
	  if (Vwarn_function_name_clash)
	    warning ("function name `%s' does not agree with function\
 file name `%s'", id_name.c_str (), curr_fcn_file_full_name.c_str ());

	  fbi_sym_tab->rename (id_name, curr_fcn_file_name);

	  if (error_state)
	    return 0;

	  id_name = id->name ();
	}

      octave_time now;

      fcn->stash_function_name (id_name);
      fcn->stash_fcn_file_name (curr_fcn_file_full_name);
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

  symbol_record *sr = fbi_sym_tab->lookup (id_name);

  if (sr)
    {
      fcn->stash_symtab_ptr (sr);

      if (lexer_flags.parsing_nested_function)
        fcn->mark_as_nested_function ();
    }
  else
    panic_impossible ();

  id->define (fcn, symbol_record::USER_FUNCTION);

  if (! help_buf.empty ())
    {
      id->document (help_buf.top ());
      help_buf.pop ();
    }

  if (lexer_flags.parsing_nested_function < 0)
    lexer_flags.parsing_nested_function = 0;

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
  if (symtab_context.empty ())
    panic_impossible ();

  curr_sym_tab = symtab_context.top ();
  symtab_context.pop ();

  lexer_flags.defining_func = false;
  lexer_flags.beginning_of_function = false;
  lexer_flags.parsed_function_name = false;
  lexer_flags.looking_at_return_list = false;
  lexer_flags.looking_at_parameter_list = false;
}

// Make an index expression.

static tree_index_expression *
make_index_expression (tree_expression *expr, tree_argument_list *args,
		       char type)
{
  tree_index_expression *retval = 0;

  int l = expr->line ();
  int c = expr->column ();

  expr->mark_postfix_indexed ();

  if (expr->is_index_expression ())
    {
      tree_index_expression *tmp = static_cast<tree_index_expression *> (expr);

      tmp->append (args, type);

      retval = tmp;
    }
  else
    retval = new tree_index_expression (expr, args, l, c, type);

  return retval;
}

// Make an indirect reference expression.

static tree_index_expression *
make_indirect_ref (tree_expression *expr, const std::string& elt)
{
  tree_index_expression *retval = 0;

  int l = expr->line ();
  int c = expr->column ();

  if (expr->is_index_expression ())
    {
      tree_index_expression *tmp = static_cast<tree_index_expression *> (expr);

      tmp->append (elt);

      retval = tmp;
    }
  else
    retval = new tree_index_expression (expr, elt, l, c);

  lexer_flags.looking_at_indirect_ref = false;

  return retval;
}

// Make an indirect reference expression with dynamic field name.

static tree_index_expression *
make_indirect_ref (tree_expression *expr, tree_expression *elt)
{
  tree_index_expression *retval = 0;

  int l = expr->line ();
  int c = expr->column ();

  if (expr->is_index_expression ())
    {
      tree_index_expression *tmp = static_cast<tree_index_expression *> (expr);

      tmp->append (elt);

      retval = tmp;
    }
  else
    retval = new tree_index_expression (expr, elt, l, c);

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
  unwind_protect_int (warning_state);

  unwind_protect_bool (discard_error_messages);
  unwind_protect_bool (discard_warning_messages);

  discard_error_messages = true;
  discard_warning_messages = true;

  if (m->all_elements_are_constant ())
    {
      octave_value tmp = m->rvalue ();

      if (! (error_state || warning_state))
	{
	  tree_constant *tc_retval = new tree_constant (tmp);

	  OSSTREAM buf;

	  tree_print_code tpc (buf);

	  m->accept (tpc);

	  buf << OSSTREAM_ENDS;

	  tc_retval->stash_original_text (OSSTREAM_STR (buf));

	  OSSTREAM_FREEZE (buf);

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
      tree_statement *tmp = t->back();

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
	tree_statement *tmp = list->back ();
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

	      OCTAVE_QUIT;

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

static int
text_getc (FILE *f)
{
  int c = getc (f);

  // Convert CRLF into just LF.

  if (c == '\r')
    {
      c = getc (f);

      if (c != '\n')
	{
	  ungetc (c, f);
	  c = '\r';
	}
    }

  return c;
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

  while ((c = text_getc (ffile)) != EOF)
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
		  if ((c = text_getc (ffile)) != EOF)
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
  unwind_protect_int (end_tokens_expected);
  unwind_protect_bool (reading_fcn_file);
  unwind_protect_bool (line_editing);
  unwind_protect_str (parent_function_name);

  input_line_number = 0;
  current_input_column = 1;
  end_tokens_expected = 0;
  reading_fcn_file = true;
  line_editing = false;
  parent_function_name = "";

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

	  std::string txt
	    = gobble_leading_white_space (ffile, true, true, true);

	  help_buf.push (txt);

	  octave_comment_buffer::append (txt);

	  // XXX FIXME XXX -- this should not be necessary.
	  gobble_leading_white_space (ffile, false, true, false);

	  int status = yyparse ();

	  if (status != 0)
	    {
	      error ("parse error while reading function file %s",
		     ff.c_str ());
	      fbi_sym_tab->clear (curr_fcn_file_name);
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

  string_vector names (2);

  names[0] = nm + ".oct";
  names[1] = nm + ".m";

  std::string file
   = octave_env::make_absolute (Vload_path_dir_path.find_first_of (names),
                                octave_env::getcwd ());

  int len = file.length ();

  if (len > 4 && file.substr (len-4, len-1) == ".oct")
    {
      if (octave_dynamic_loader::load (nm, file))
        force_link_to_function (nm);
    }
  else if (len > 2)
    {
      // These are needed by yyparse.

      unwind_protect::begin_frame ("load_fcn_from_file");

      unwind_protect_str (curr_fcn_file_name);
      unwind_protect_str (curr_fcn_file_full_name);

      curr_fcn_file_name = nm;
      curr_fcn_file_full_name = file;

      script_file_executed = parse_fcn_file (file, exec_script);

      if (! (error_state || script_file_executed))
	force_link_to_function (nm);

      unwind_protect::run_frame ("load_fcn_from_file");
    }

  return script_file_executed;
}

void
source_file (const std::string file_name)
{
  std::string file_full_name = file_ops::tilde_expand (file_name);

  unwind_protect::begin_frame ("source_file");

  unwind_protect_str (curr_fcn_file_name);
  unwind_protect_str (curr_fcn_file_full_name);

  curr_fcn_file_name = file_name;
  curr_fcn_file_full_name = file_full_name;

  parse_fcn_file (file_full_name, true, true);

  if (error_state)
    error ("source: error sourcing file `%s'",
	   file_full_name.c_str ());

  unwind_protect::run_frame ("source_file");
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
        source_file (file_name);
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

octave_value_list
feval (octave_function *fcn, const octave_value_list& args, int nargout)
{
  octave_value_list retval;

  if (fcn)
    retval = fcn->do_multi_index_op (nargout, args);

  return retval;
}

static octave_value_list
get_feval_args (const octave_value_list& args)
{
  int tmp_nargin = args.length () - 1;

  octave_value_list retval (tmp_nargin, octave_value ());

  for (int i = 0; i < tmp_nargin; i++)
    retval(i) = args(i+1);

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

      retval.stash_name_tags (tmp_arg_names);
    }

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

  int nargin = args.length ();

  if (nargin > 0)
    {
      octave_value f_arg = args(0);

      if (f_arg.is_string ())
        {
	  std::string name = f_arg.string_value ();

	  if (! error_state)
	    {
	      octave_value_list tmp_args = get_feval_args (args);

	      retval = feval (name, tmp_args, nargout);
	    }
	}
      else
	{
	  octave_function *fcn = f_arg.function_value ();

	  if (fcn)
	    {
	      octave_value_list tmp_args = get_feval_args (args);

	      retval = feval (fcn, tmp_args, nargout);
	    }
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
      reset_parser ();

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
      return octave_value (-1);
    }

  return eval_string (s, silent, parse_status, nargout);
}

DEFUN (eval, args, nargout,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} eval (@var{try}, @var{catch})\n\
Parse the string @var{try} and evaluate it as if it were an Octave\n\
program.  If that fails, evaluate the string @var{catch}.\n\
The string @var{try} is evaluated in the current context,\n\
so any results remain available after @code{eval} returns.\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin > 0)
    {
      unwind_protect::begin_frame ("Feval");

      if (nargin > 1)
	{
	  unwind_protect_int (buffer_error_messages);
	  buffer_error_messages++;
	}

      int parse_status = 0;

      octave_value_list tmp = eval_string (args(0), nargout > 0,
					   parse_status, nargout);

      if (nargout > 0)
	retval = tmp;

      if (nargin > 1 && (parse_status != 0 || error_state))
	{
	  error_state = 0;

	  // Set up for letting the user print any messages from
	  // errors that occurred in the first part of this eval().

	  buffer_error_messages--;

	  eval_string (args(1), 0, parse_status, nargout);

	  retval = octave_value_list ();
	}

      unwind_protect::run_frame ("Feval");
    }
  else
    print_usage ("eval");

  return retval;
}

DEFUN (assignin, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} assignin (@var{context}, @var{varname}, @var{value})\n\
Assign @var{value} to @var{varname} in context @var{context}, which\n\
may be either @code{\"base\"} or @code{\"caller\"}.\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin == 3)
    {
      std::string context = args(0).string_value ();

      if (! error_state)
        {
	  unwind_protect::begin_frame ("Fassignin");

	  unwind_protect_ptr (curr_sym_tab);

	  if (context == "caller")
	    curr_sym_tab = curr_caller_sym_tab;
	  else if (context == "base")
	    curr_sym_tab = top_level_sym_tab;
	  else
	    error ("assignin: context must be \"caller\" or \"base\"");

	  if (! error_state)
	    {
	      std::string nm = args(1).string_value ();

	      if (! error_state)
		{
		  if (valid_identifier (nm))
		    {
		      symbol_record *sr = curr_sym_tab->lookup (nm, true);

		      if (sr)
			{
			  tree_identifier *id = new tree_identifier (sr);
			  tree_constant *rhs = new tree_constant (args(2));
		      
			  tree_simple_assignment tsa (id, rhs);

			  tsa.rvalue ();
			}
		    }
		  else
		    error ("assignin: invalid variable name");
		}
	      else
		error ("assignin: expecting variable name as second argument");
	    }

	  unwind_protect::run_frame ("Fassignin");
	}
      else
        error ("assignin: expecting string as first argument");
    }
  else
    print_usage ("assignin");

  return retval;
}

DEFUN (evalin, args, nargout,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} evalin (@var{context}, @var{try}, @var{catch})\n\
Like @code{eval}, except that the expressions are evaluated in the\n\
context @var{context}, which may be either @code{\"caller\"} or\n\
@code{\"base\"}.\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin > 1)
    {
      std::string context = args(0).string_value ();

      if (! error_state)
        {
	  unwind_protect::begin_frame ("Fevalin");

	  unwind_protect_ptr (curr_sym_tab);

	  if (context == "caller")
	    curr_sym_tab = curr_caller_sym_tab;
	  else if (context == "base")
	    curr_sym_tab = top_level_sym_tab;
	  else
	    error ("evalin: context must be \"caller\" or \"base\"");

	  if (! error_state)
	    {
	      if (nargin > 2)
	        {
		  unwind_protect_int (buffer_error_messages);
		  buffer_error_messages++;
		}

	      int parse_status = 0;

	      octave_value_list tmp = eval_string (args(1), nargout > 0,
						   parse_status, nargout);

	      if (nargout > 0)
		retval = tmp;

	      if (nargin > 2 && (parse_status != 0 || error_state))
		{
		  error_state = 0;

		  // Set up for letting the user print any messages from
		  // errors that occurred in the first part of this eval().

		  buffer_error_messages--;

		  eval_string (args(2), 0, parse_status, nargout);

		  retval = octave_value_list ();
		}
	    }

	  unwind_protect::run_frame ("Fevalin");
	}
      else
        error ("evalin: expecting string as first argument");
    }
  else
    print_usage ("evalin");

  return retval;
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
warn_precedence_change (void)
{
  Vwarn_precedence_change = check_preference ("warn_precedence_change");

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
  DEFVAR (warn_assign_as_truth_value, true, warn_assign_as_truth_value,
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

  DEFVAR (warn_function_name_clash, true, warn_function_name_clash,
    "-*- texinfo -*-\n\
@defvr {Built-in Variable} warn_function_name_clash\n\
If the value of @code{warn_function_name_clash} is nonzero, a warning is\n\
issued when Octave finds that the name of a function defined in a\n\
function file differs from the name of the file.  (If the names\n\
disagree, the name declared inside the file is ignored.)  If the value\n\
is 0, the warning is omitted.  The default value is 1.\n\
@end defvr");

  DEFVAR (warn_future_time_stamp, true, warn_future_time_stamp,
    "-*- texinfo -*-\n\
@defvr {Built-in Variable} warn_future_time_stamp\n\
If the value of this variable is nonzero, Octave will print a warning\n\
if it finds a function file with a time stamp that is in the future.\n\
@end defvr");

  DEFVAR (warn_missing_semicolon, false, warn_missing_semicolon,
    "-*- texinfo -*-\n\
@defvr {Built-in Variable} warn_missing_semicolon\n\
If the value of this variable is nonzero, Octave will warn when\n\
statements in function definitions don't end in semicolons.  The default\n\
value is 0.\n\
@end defvr");

  DEFVAR (warn_precedence_change, true, warn_precedence_change,
    "-*- texinfo -*-\n\
@defvr {Built-in Variable} warn_precedence_change\n\
If the value of this variable is nonzero, Octave will warn about\n\
possible changes in the meaning of some code due to changes in\n\
precedence for some operators.  Precedence changes have typically\n\
been made for Matlab compatibility.  The default value is 1.\n\
@end defvr");

  DEFVAR (warn_variable_switch_label, false, warn_variable_switch_label,
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

