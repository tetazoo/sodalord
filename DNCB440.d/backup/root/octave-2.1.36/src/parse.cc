/* A Bison parser, made from parse.y
   by GNU bison 1.32.  */

#define YYBISON 1  /* Identify Bison output.  */

# define	ADD_EQ	257
# define	SUB_EQ	258
# define	MUL_EQ	259
# define	DIV_EQ	260
# define	LEFTDIV_EQ	261
# define	EMUL_EQ	262
# define	EDIV_EQ	263
# define	ELEFTDIV_EQ	264
# define	AND_EQ	265
# define	OR_EQ	266
# define	LSHIFT_EQ	267
# define	RSHIFT_EQ	268
# define	LSHIFT	269
# define	RSHIFT	270
# define	EXPR_AND_AND	271
# define	EXPR_OR_OR	272
# define	EXPR_AND	273
# define	EXPR_OR	274
# define	EXPR_NOT	275
# define	EXPR_LT	276
# define	EXPR_LE	277
# define	EXPR_EQ	278
# define	EXPR_NE	279
# define	EXPR_GE	280
# define	EXPR_GT	281
# define	LEFTDIV	282
# define	EMUL	283
# define	EDIV	284
# define	ELEFTDIV	285
# define	EPLUS	286
# define	EMINUS	287
# define	QUOTE	288
# define	TRANSPOSE	289
# define	PLUS_PLUS	290
# define	MINUS_MINUS	291
# define	POW	292
# define	EPOW	293
# define	NUM	294
# define	IMAG_NUM	295
# define	STRUCT_ELT	296
# define	NAME	297
# define	END	298
# define	PLOT	299
# define	TEXT	300
# define	STYLE	301
# define	AXES_TAG	302
# define	FOR	303
# define	WHILE	304
# define	DO	305
# define	UNTIL	306
# define	IF	307
# define	ELSEIF	308
# define	ELSE	309
# define	SWITCH	310
# define	CASE	311
# define	OTHERWISE	312
# define	BREAK	313
# define	CONTINUE	314
# define	FUNC_RET	315
# define	UNWIND	316
# define	CLEANUP	317
# define	TRY	318
# define	CATCH	319
# define	GLOBAL	320
# define	STATIC	321
# define	END_OF_INPUT	322
# define	LEXICAL_ERROR	323
# define	FCN	324
# define	ELLIPSIS	325
# define	ALL_VA_ARGS	326
# define	USING	327
# define	TITLE	328
# define	WITH	329
# define	AXES	330
# define	COLON	331
# define	OPEN_BRACE	332
# define	CLOSE_BRACE	333
# define	CLEAR	334
# define	UNARY	335

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


#line 324 "parse.y"
#ifndef YYSTYPE
typedef union
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
} yystype;
# define YYSTYPE yystype
#endif
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		399
#define	YYFLAG		-32768
#define	YYNTBASE	98

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 335 ? yytranslate[x] : 186)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      89,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      91,    97,     7,     6,    88,     5,    92,     8,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     4,    87,
       2,     3,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    94,     2,    95,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    93,     2,    96,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    90
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     2,     5,     7,     9,    11,    13,    16,    19,
      22,    24,    28,    29,    31,    34,    36,    40,    42,    44,
      47,    49,    51,    53,    55,    56,    59,    63,    68,    70,
      73,    75,    79,    82,    86,    90,    92,    95,    97,   101,
     103,   106,   108,   110,   112,   114,   118,   120,   122,   124,
     126,   130,   134,   138,   139,   141,   145,   150,   155,   158,
     161,   164,   167,   172,   174,   176,   179,   182,   185,   188,
     191,   195,   199,   203,   207,   211,   215,   219,   223,   227,
     231,   235,   239,   241,   243,   247,   249,   253,   257,   261,
     265,   269,   273,   277,   281,   285,   289,   293,   297,   299,
     304,   308,   312,   316,   320,   324,   328,   332,   336,   340,
     344,   348,   352,   356,   359,   361,   364,   366,   368,   370,
     372,   374,   376,   378,   380,   382,   384,   387,   390,   392,
     395,   397,   401,   403,   405,   410,   412,   415,   419,   422,
     429,   434,   441,   443,   446,   448,   451,   458,   463,   470,
     477,   486,   488,   490,   492,   502,   512,   513,   514,   515,
     516,   517,   519,   521,   524,   528,   531,   536,   539,   543,
     546,   550,   554,   557,   561,   565,   571,   573,   577,   580,
     585,   588,   592,   596,   600,   605,   608,   610,   614,   616,
     618,   620,   623,   626,   630,   632,   635,   639,   645,   650,
     655,   659,   662,   664,   668,   670,   673,   675,   677,   679,
     681,   684,   687,   690,   693,   696,   698,   701,   704,   708,
     711,   714,   718,   723,   724,   726,   728,   730,   732,   735,
     738,   739,   741,   743,   745,   747,   750,   753,   756,   757
};
static const short yyrhs[] =
{
      99,     0,   100,   181,     0,   181,     0,    89,     0,    74,
       0,   100,     0,   100,    89,     0,   100,    74,     0,   101,
     183,     0,   105,     0,   101,   182,   105,     0,     0,   103,
       0,   104,   185,     0,   105,     0,   104,   184,   105,     0,
     130,     0,   131,     0,    51,    86,     0,    49,     0,    46,
       0,    47,     0,    52,     0,     0,    94,    95,     0,    94,
      87,    95,     0,    94,   108,   110,    95,     0,   111,     0,
     111,    87,     0,   115,     0,   111,    87,   115,     0,    93,
      96,     0,    93,    87,    96,     0,    93,   113,    96,     0,
     114,     0,   114,    87,     0,   115,     0,   114,    87,   115,
       0,   118,     0,   118,    88,     0,   106,     0,   107,     0,
     109,     0,   112,     0,    91,   130,    97,     0,     4,     0,
     130,     0,   117,     0,    78,     0,   118,    88,   117,     0,
     118,    88,   130,     0,   118,    88,    78,     0,     0,   116,
       0,   120,    91,    97,     0,   120,    91,   118,    97,     0,
     120,    93,   118,    96,     0,   120,    42,     0,   120,    43,
       0,   120,    40,     0,   120,    41,     0,   120,    92,   119,
      48,     0,   120,     0,   122,     0,    42,   121,     0,    43,
     121,     0,    27,   121,     0,     6,   121,     0,     5,   121,
       0,   121,    44,   121,     0,   121,    45,   121,     0,   121,
       6,   121,     0,   121,     5,   121,     0,   121,     7,   121,
       0,   121,     8,   121,     0,   121,    38,   121,     0,   121,
      39,   121,     0,   121,    35,   121,     0,   121,    36,   121,
       0,   121,    34,   121,     0,   121,    37,   121,     0,   124,
       0,   121,     0,   124,     4,   121,     0,   123,     0,   125,
      21,   125,     0,   125,    22,   125,     0,   125,    28,   125,
       0,   125,    29,   125,     0,   125,    30,   125,     0,   125,
      32,   125,     0,   125,    33,   125,     0,   125,    31,   125,
       0,   125,    25,   125,     0,   125,    26,   125,     0,   125,
      23,   125,     0,   125,    24,   125,     0,   125,     0,    94,
     108,   118,    85,     0,   126,     3,   130,     0,   126,     9,
     130,     0,   126,    10,   130,     0,   126,    11,   130,     0,
     126,    12,   130,     0,   126,    13,   130,     0,   126,    19,
     130,     0,   126,    20,   130,     0,   126,    14,   130,     0,
     126,    15,   130,     0,   126,    16,   130,     0,   126,    17,
     130,     0,   126,    18,   130,     0,   106,   129,     0,    52,
       0,   129,    52,     0,   125,     0,   128,     0,   127,     0,
     132,     0,   135,     0,   146,     0,   147,     0,   148,     0,
     163,     0,   169,     0,    72,   133,     0,    73,   133,     0,
     134,     0,   133,   134,     0,   106,     0,   106,     3,   130,
       0,   136,     0,   141,     0,    59,   180,   137,    50,     0,
     138,     0,   138,   140,     0,   130,   185,   102,     0,   138,
     139,     0,    60,   180,   185,   130,   185,   102,     0,    61,
     180,   185,   102,     0,    62,   180,   130,   185,   142,    50,
       0,   143,     0,   143,   145,     0,   144,     0,   143,   144,
       0,    63,   180,   185,   130,   185,   103,     0,    64,   180,
     185,   102,     0,    56,   180,   130,   185,   102,    50,     0,
      57,   180,   185,   102,    58,   130,     0,    55,   180,   126,
       3,   130,   185,   102,    50,     0,    65,     0,    66,     0,
      67,     0,    68,   180,   185,   102,    69,   180,   185,   102,
      50,     0,    70,   180,   185,   102,    71,   180,   185,   102,
      50,     0,     0,     0,     0,     0,     0,    91,     0,    97,
       0,   154,   155,     0,   154,    77,   155,     0,   157,   155,
       0,   157,    88,    77,   155,     0,   154,   106,     0,   157,
      88,   106,     0,   154,     1,     0,   157,    88,     1,     0,
      94,   152,   151,     0,   158,   161,     0,   158,    77,   161,
       0,   158,   160,   161,     0,   158,   160,    88,    77,   161,
       0,   106,     0,   160,    88,   106,     0,   150,    95,     0,
     149,    76,   180,   150,     0,   162,   165,     0,   162,   106,
     164,     0,   162,   159,   164,     0,   150,     3,   165,     0,
     106,   151,   153,   166,     0,   156,   167,     0,   167,     0,
     185,   102,   168,     0,    50,     0,    74,     0,    51,     0,
      51,   170,     0,    51,   172,     0,    51,   170,   172,     0,
     171,     0,   171,   171,     0,   171,   171,   171,     0,    84,
     130,    83,   130,    85,     0,    84,    83,   130,    85,     0,
      84,   130,    83,    85,     0,    84,    83,    85,     0,    84,
      85,     0,   173,     0,   172,    88,   173,     0,   130,     0,
     130,   174,     0,   176,     0,   178,     0,   179,     0,   175,
       0,   174,   176,     0,   174,   178,     0,   174,   179,     0,
     174,   175,     0,    82,    54,     0,   177,     0,   177,   130,
       0,    79,   130,     0,   177,    83,   130,     0,    80,   130,
       0,    81,    53,     0,    81,    53,   130,     0,    81,    53,
     130,   130,     0,     0,    75,     0,     1,     0,    88,     0,
      87,     0,   182,    88,     0,   182,    87,     0,     0,   182,
       0,    88,     0,    87,     0,    89,     0,   184,    88,     0,
     184,    87,     0,   184,    89,     0,     0,   184,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   462,   468,   470,   474,   476,   481,   483,   485,   489,
     496,   498,   506,   508,   512,   519,   524,   532,   539,   546,
     562,   569,   571,   573,   578,   582,   584,   586,   593,   595,
     599,   601,   608,   610,   612,   616,   618,   622,   624,   632,
     634,   638,   640,   642,   644,   646,   650,   657,   659,   661,
     667,   672,   677,   686,   690,   692,   694,   696,   698,   700,
     702,   704,   706,   710,   712,   714,   716,   718,   720,   722,
     726,   728,   730,   732,   734,   736,   738,   740,   742,   744,
     746,   748,   752,   756,   758,   765,   767,   769,   771,   773,
     775,   777,   779,   781,   783,   785,   787,   789,   796,   798,
     805,   807,   809,   811,   813,   815,   817,   819,   821,   823,
     825,   827,   829,   833,   837,   842,   850,   852,   854,   862,
     864,   866,   868,   870,   872,   874,   882,   884,   888,   890,
     897,   899,   907,   909,   917,   924,   926,   933,   935,   942,
     946,   956,   963,   965,   972,   974,   981,   985,   995,  1000,
    1005,  1016,  1021,  1026,  1037,  1043,  1055,  1064,  1068,  1072,
    1076,  1084,  1088,  1092,  1097,  1104,  1110,  1119,  1121,  1126,
    1132,  1144,  1147,  1152,  1159,  1164,  1172,  1174,  1181,  1188,
    1192,  1198,  1204,  1212,  1216,  1223,  1225,  1229,  1233,  1243,
    1254,  1259,  1264,  1269,  1276,  1278,  1280,  1284,  1286,  1288,
    1290,  1292,  1296,  1298,  1305,  1307,  1311,  1316,  1321,  1326,
    1331,  1339,  1347,  1355,  1365,  1372,  1377,  1384,  1389,  1393,
    1397,  1399,  1401,  1409,  1413,  1415,  1418,  1420,  1422,  1424,
    1428,  1430,  1434,  1436,  1438,  1440,  1442,  1444,  1448,  1450
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "'='", "':'", "'-'", "'+'", "'*'", "'/'", 
  "ADD_EQ", "SUB_EQ", "MUL_EQ", "DIV_EQ", "LEFTDIV_EQ", "EMUL_EQ", 
  "EDIV_EQ", "ELEFTDIV_EQ", "AND_EQ", "OR_EQ", "LSHIFT_EQ", "RSHIFT_EQ", 
  "LSHIFT", "RSHIFT", "EXPR_AND_AND", "EXPR_OR_OR", "EXPR_AND", "EXPR_OR", 
  "EXPR_NOT", "EXPR_LT", "EXPR_LE", "EXPR_EQ", "EXPR_NE", "EXPR_GE", 
  "EXPR_GT", "LEFTDIV", "EMUL", "EDIV", "ELEFTDIV", "EPLUS", "EMINUS", 
  "QUOTE", "TRANSPOSE", "PLUS_PLUS", "MINUS_MINUS", "POW", "EPOW", "NUM", 
  "IMAG_NUM", "STRUCT_ELT", "NAME", "END", "PLOT", "TEXT", "STYLE", 
  "AXES_TAG", "FOR", "WHILE", "DO", "UNTIL", "IF", "ELSEIF", "ELSE", 
  "SWITCH", "CASE", "OTHERWISE", "BREAK", "CONTINUE", "FUNC_RET", 
  "UNWIND", "CLEANUP", "TRY", "CATCH", "GLOBAL", "STATIC", "END_OF_INPUT", 
  "LEXICAL_ERROR", "FCN", "ELLIPSIS", "ALL_VA_ARGS", "USING", "TITLE", 
  "WITH", "AXES", "COLON", "OPEN_BRACE", "CLOSE_BRACE", "CLEAR", "';'", 
  "','", "'\\n'", "UNARY", "'('", "'.'", "'{'", "'['", "']'", "'}'", 
  "')'", "input", "input1", "simple_list", "simple_list1", "opt_list", 
  "list", "list1", "statement", "identifier", "constant", 
  "in_matrix_or_assign_lhs", "matrix", "matrix_rows", "matrix_rows1", 
  "cell", "cell_rows", "cell_rows1", "cell_or_matrix_row", "primary_expr", 
  "magic_colon", "arg_list", "parsing_indir", "postfix_expr", 
  "prefix_expr", "binary_expr", "colon_expr", "colon_expr1", 
  "simple_expr", "assign_lhs", "assign_expr", "word_list_cmd", 
  "word_list", "expression", "command", "declaration", "decl1", "decl2", 
  "select_command", "if_command", "if_cmd_list", "if_cmd_list1", 
  "elseif_clause", "else_clause", "switch_command", "case_list", 
  "case_list1", "switch_case", "default_case", "loop_command", 
  "jump_command", "except_command", "save_symtab", "global_symtab", 
  "local_symtab", "in_return_list", "parsed_fcn_name", "param_list_beg", 
  "param_list_end", "param_list", "param_list1", "return_list_beg", 
  "return_list", "return_list1", "return_list_end", "function_beg", 
  "function", "function1", "function2", "function3", "function4", 
  "function_end", "plot_command", "ranges", "ranges1", "plot_command1", 
  "plot_command2", "plot_options", "axes", "using", "using1", "title", 
  "style", "stash_comment", "parse_error", "sep_no_nl", "opt_sep_no_nl", 
  "sep", "opt_sep", NULL
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    98,    98,    98,    99,    99,    99,    99,    99,   100,
     101,   101,   102,   102,   103,   104,   104,   105,   105,   105,
     106,   107,   107,   107,   108,   109,   109,   109,   110,   110,
     111,   111,   112,   112,   112,   113,   113,   114,   114,   115,
     115,   116,   116,   116,   116,   116,   117,   118,   118,   118,
     118,   118,   118,   119,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   121,   121,   121,   121,   121,   121,   121,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   123,   124,   124,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   126,   126,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   128,   129,   129,   130,   130,   130,   131,
     131,   131,   131,   131,   131,   131,   132,   132,   133,   133,
     134,   134,   135,   135,   136,   137,   137,   138,   138,   139,
     140,   141,   142,   142,   143,   143,   144,   145,   146,   146,
     146,   147,   147,   147,   148,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   156,   156,   156,   157,   157,   157,
     157,   158,   159,   159,   159,   159,   160,   160,   161,   162,
     163,   163,   163,   164,   165,   166,   166,   167,   168,   168,
     169,   169,   169,   169,   170,   170,   170,   171,   171,   171,
     171,   171,   172,   172,   173,   173,   174,   174,   174,   174,
     174,   174,   174,   174,   175,   176,   176,   177,   177,   178,
     179,   179,   179,   180,   181,   181,   182,   182,   182,   182,
     183,   183,   184,   184,   184,   184,   184,   184,   185,   185
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     1,     2,     1,     1,     1,     1,     2,     2,     2,
       1,     3,     0,     1,     2,     1,     3,     1,     1,     2,
       1,     1,     1,     1,     0,     2,     3,     4,     1,     2,
       1,     3,     2,     3,     3,     1,     2,     1,     3,     1,
       2,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       3,     3,     3,     0,     1,     3,     4,     4,     2,     2,
       2,     2,     4,     1,     1,     2,     2,     2,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     1,     1,     3,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     4,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     1,     2,
       1,     3,     1,     1,     4,     1,     2,     3,     2,     6,
       4,     6,     1,     2,     1,     2,     6,     4,     6,     6,
       8,     1,     1,     1,     9,     9,     0,     0,     0,     0,
       0,     1,     1,     2,     3,     2,     4,     2,     3,     2,
       3,     3,     2,     3,     3,     5,     1,     3,     2,     4,
       2,     3,     3,     3,     4,     2,     1,     3,     1,     1,
       1,     2,     2,     3,     1,     2,     3,     5,     4,     4,
       3,     2,     1,     3,     1,     2,     1,     1,     1,     1,
       2,     2,     2,     2,     2,     1,     2,     2,     3,     2,
       2,     3,     4,     0,     1,     1,     1,     1,     2,     2,
       0,     1,     1,     1,     1,     2,     2,     2,     0,     1
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       0,   225,     0,     0,     0,     0,     0,    21,    22,    20,
     190,    23,   223,   223,   223,   223,   223,   151,   152,   153,
     223,   223,     0,     0,     5,   224,     4,     0,     0,    24,
       1,     0,   230,    10,    41,    42,    43,    44,    54,    63,
      83,    64,    85,    82,   116,     0,   118,   117,    17,    18,
     119,   120,   132,   133,   121,   122,   123,     0,     0,   124,
     125,     3,    24,    41,    69,    68,    67,    65,    66,     0,
      19,   204,   191,   194,   192,   202,     0,     0,   238,     0,
       0,   238,   238,   130,   126,   128,   127,     0,    46,    49,
       0,    32,     0,    35,    37,    48,    39,    47,     0,    25,
       0,     8,     7,     2,   227,   226,   231,     9,   114,   113,
      60,    61,    58,    59,     0,    53,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   223,   159,   158,   157,   157,
     180,     0,     0,   201,     0,     0,     0,     0,     0,   205,
     209,   206,   215,   207,   208,   193,   195,     0,    98,     0,
     238,   233,   232,   234,   239,    12,   238,     0,   135,   238,
      12,    12,     0,   129,    45,    33,    34,    36,    40,    26,
       0,    28,    30,    39,   229,   228,    11,   115,    55,     0,
       0,     0,    73,    72,    74,    75,    80,    78,    79,    81,
      76,    77,    70,    71,    84,    86,    87,    96,    97,    94,
      95,    88,    89,    90,    93,    91,    92,   100,   101,   102,
     103,   104,   105,   108,   109,   110,   111,   112,   106,   107,
     157,   158,     0,   160,   181,   157,   176,     0,   157,   172,
     182,   200,     0,     0,   217,   219,   220,   214,   213,   210,
     211,   212,     0,   216,   196,   203,     0,    12,   236,   235,
     237,     0,    13,   238,    15,    12,   134,   223,   223,   138,
     136,     0,     0,     0,   131,    38,    52,    50,    51,    27,
      29,    99,     0,    56,    62,    57,   179,   171,     0,   238,
     173,   178,     0,   174,   198,   199,     0,   221,   218,   238,
       0,     0,   239,    14,   137,   238,   238,   223,     0,   142,
     144,   223,   223,    31,   158,   183,   161,     0,   238,     0,
     184,   186,    12,   157,   177,   197,   222,    12,   148,   149,
      16,     0,    12,   238,   141,   223,   145,   143,   238,   238,
     169,     0,   162,   167,   163,   185,     0,   165,     0,   175,
       0,   238,   140,     0,   238,    12,    12,   164,   170,     0,
     168,   188,   189,   187,   150,    12,   238,    12,     0,     0,
     166,   139,   156,   147,   154,   155,   146,     0,     0,     0
};

static const short yydefgoto[] =
{
     397,    30,    31,    32,   281,   282,   283,   284,    34,    35,
     100,    36,   200,   201,    37,    92,    93,   202,    38,    95,
      96,   210,    39,    40,    41,    42,    43,    44,    45,    46,
      47,   109,    48,    49,    50,    84,    85,    51,    52,   187,
     188,   289,   290,    53,   328,   329,   330,   357,    54,    55,
      56,    57,   257,   253,   251,   309,   337,   364,   338,   339,
     158,   159,   258,   259,    58,    59,   254,   160,   340,   341,
     383,    60,    72,    73,    74,    75,   169,   170,   171,   172,
     173,   174,    76,    61,   106,   107,   184,   342
};

static const short yypact[] =
{
     362,-32768,   887,   887,   887,   887,   887,-32768,-32768,-32768,
     779,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,    24,    24,-32768,-32768,-32768,   942,   443,    -1,
  -32768,    70,   -39,-32768,   -24,-32768,-32768,-32768,-32768,     0,
     965,-32768,-32768,    76,  1028,   367,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,    34,   -36,-32768,
  -32768,-32768,    -1,-32768,    52,    52,    52,    52,    52,   793,
  -32768,   -47,   942,    58,    64,-32768,   942,   942,   -21,   942,
     942,   -21,   -21,    80,    24,-32768,    24,    61,-32768,-32768,
      65,-32768,    68,    75,-32768,-32768,    72,-32768,    78,-32768,
     498,-32768,-32768,-32768,-32768,-32768,   614,-32768,-32768,   113,
  -32768,-32768,-32768,-32768,   435,-32768,   498,   887,   887,   887,
     887,   887,   887,   887,   887,   887,   887,   887,   887,   887,
     887,   887,   887,   887,   887,   887,   887,   887,   887,   887,
     887,   887,   942,   942,   942,   942,   942,   942,   942,   942,
     942,   942,   942,   942,   942,-32768,-32768,   163,   -26,-32768,
  -32768,   498,   805,-32768,    84,   942,   942,   115,   116,   -47,
  -32768,-32768,   861,-32768,-32768,    64,    58,   942,   549,   171,
     -21,-32768,-32768,-32768,    17,   669,   -21,   127,    41,   -21,
     669,   669,   942,-32768,-32768,-32768,-32768,   498,   506,-32768,
      85,    92,-32768,   -38,-32768,-32768,-32768,-32768,-32768,   -61,
     130,     7,    18,    18,    52,    52,    52,    52,    52,    52,
      18,    18,    52,    52,   965,-32768,-32768,   228,   228,   283,
     283,    91,    91,    91,    91,    91,    91,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,   178,-32768,-32768,-32768,-32768,    87,    95,-32768,
  -32768,-32768,   101,   874,-32768,-32768,   942,-32768,-32768,-32768,
  -32768,-32768,   942,-32768,-32768,-32768,   942,   669,-32768,-32768,
  -32768,   131,-32768,   -21,-32768,   669,-32768,-32768,-32768,-32768,
  -32768,   125,   134,   133,-32768,-32768,-32768,-32768,-32768,-32768,
     498,-32768,   506,-32768,-32768,-32768,-32768,-32768,    24,    66,
  -32768,-32768,   -18,-32768,-32768,-32768,   120,   942,-32768,   -21,
     156,   942,   559,-32768,-32768,   -21,   -21,-32768,   157,    83,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,    11,   -21,   -59,
  -32768,-32768,   669,-32768,-32768,-32768,-32768,   669,-32768,-32768,
  -32768,   942,   669,   -21,-32768,-32768,-32768,-32768,   -21,   -21,
  -32768,   111,-32768,-32768,-32768,-32768,    23,-32768,    -5,-32768,
     159,   -21,-32768,   942,   -21,   669,   669,-32768,-32768,   111,
  -32768,-32768,-32768,-32768,-32768,   669,   -21,   669,   160,   161,
  -32768,-32768,   724,-32768,-32768,-32768,-32768,   212,   226,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,-32768,-32768,  -101,  -165,-32768,     5,    -2,-32768,
     166,-32768,-32768,-32768,-32768,-32768,-32768,   -22,-32768,  -161,
     -70,-32768,-32768,    73,-32768,-32768,-32768,   158,   153,-32768,
  -32768,-32768,    71,-32768,-32768,   207,     1,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,   -98,-32768,-32768,-32768,
  -32768,-32768,  -141,   -16,-32768,-32768,-32768,  -322,-32768,-32768,
  -32768,-32768,-32768,  -236,-32768,-32768,    79,   -69,-32768,   -96,
  -32768,-32768,-32768,   -62,   168,    67,-32768,    86,    93,-32768,
      96,    98,    -6,   214,-32768,-32768,   -31,   -17
};


#define	YYLAST		1061


static const short yytable[] =
{
      63,    63,    63,    63,    63,    33,    94,    77,    78,    79,
      80,   176,   360,     9,    81,    82,   252,   367,   252,   310,
      83,    83,   313,     9,   378,   119,   120,   302,   108,   366,
     203,     9,   165,   166,   167,   168,   303,   297,   362,   377,
     110,   111,   112,   113,   209,   381,   211,   301,   104,   105,
     198,   255,   121,   122,   123,   124,   157,   390,   156,   343,
       9,   185,   127,   128,   190,   191,   181,   182,   183,   382,
      -6,     1,     9,     9,    63,    64,    65,    66,    67,    68,
     129,    71,    83,   192,    83,   193,    98,   193,   361,   292,
     293,   114,   115,   116,    99,   302,   127,   128,    87,    97,
     379,   287,   288,   305,   278,   279,   280,   369,   362,   306,
     155,   206,   130,   131,   274,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
     164,   297,    69,    71,   101,    25,   327,   355,   180,   250,
     186,   189,   177,   181,   182,   183,   256,   336,   194,   102,
     198,   195,   197,   277,   196,   207,  -157,   263,   266,   285,
     267,    97,   291,   199,   276,   295,   320,   286,   304,   300,
     299,   308,   311,   312,   324,    97,   314,    97,   327,   321,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   331,   332,   345,   348,   354,   362,   384,
     394,   395,   398,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   399,   396,   161,   179,
      86,   356,    97,   262,   178,   307,   264,   265,   260,   335,
     175,   368,   365,   273,   275,   103,   370,     0,    71,   130,
     131,   372,   322,   134,   135,   268,   136,   137,   138,   139,
     140,   141,   269,   294,     0,   270,   323,   271,    97,   298,
       0,     0,     0,     0,   388,   389,     0,     0,   333,     0,
       0,   325,   326,     0,   391,     0,   393,     0,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
       0,     0,   347,     0,   130,   131,   334,     0,   351,   352,
     344,   136,   137,   138,   139,   140,   141,     0,     0,     0,
       0,   353,     0,     0,     0,   358,   359,   350,     0,     0,
       0,     0,     0,     0,   316,   363,   373,   317,     0,     0,
       0,   375,   376,   318,     0,     0,     0,   319,     0,   374,
       0,     0,     0,     0,   385,     0,     0,   387,     0,     0,
       0,     0,     0,     1,   380,     0,     0,     2,     3,   392,
     142,    97,     0,   298,     0,     0,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   346,     4,
       0,     0,   349,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     5,     6,     0,     0,     7,     8,
       0,     9,     0,    10,    11,     0,     0,    12,    13,    14,
       0,    15,   371,     0,    16,     0,     0,    17,    18,    19,
      20,     0,    21,     0,    22,    23,    24,    25,  -156,    88,
       2,     3,     0,     0,   386,     0,     0,    88,     2,     3,
       0,    26,     0,    27,     0,    28,    29,     0,     0,     0,
       0,     0,     4,     0,     0,     0,     0,     0,     0,     0,
       4,     0,     0,     0,     0,     0,     0,     5,     6,     0,
       0,     7,     8,     0,     9,     5,     6,    11,     0,     7,
       8,     0,     9,     0,     0,    11,     0,     0,     0,     0,
       0,     0,    88,     2,     3,     0,     0,     0,     0,     0,
      88,     2,     3,    89,     0,     0,     0,     0,     0,     0,
       0,    89,     0,     0,     0,     4,    27,     0,    28,    29,
      90,     0,   208,     4,    27,     0,    28,    29,     0,    91,
       5,     6,     0,     0,     7,     8,     0,     9,     5,     6,
      11,     0,     7,     8,     0,     9,     0,     0,    11,     0,
       0,     0,     0,     0,     2,     3,     0,     0,     0,     0,
     130,   131,   132,   133,   134,   135,    89,   136,   137,   138,
     139,   140,   141,     0,   296,     0,     4,     0,     0,    27,
       0,    28,    29,     0,     0,     0,     0,    27,     0,    28,
      29,     5,     6,     0,     0,     7,     8,     0,     9,     0,
      10,    11,     0,     0,    12,    13,    14,     0,    15,     2,
       3,    16,     0,     0,    17,    18,    19,    20,     0,    21,
       0,    22,    23,     0,     0,  -156,     0,     0,     0,     0,
       0,     4,     0,     0,     0,     0,   278,   279,   280,     0,
      27,     0,    28,    29,     0,     0,     5,     6,     0,     0,
       7,     8,     0,     9,     0,    10,    11,     0,     0,    12,
      13,    14,     0,    15,     2,     3,    16,     0,     0,    17,
      18,    19,    20,     0,    21,     0,    22,    23,     0,     0,
    -156,     0,     0,     0,     0,     0,     4,     0,     0,     0,
       0,   204,   205,     0,     0,    27,     0,    28,    29,     0,
       0,     5,     6,     0,     0,     7,     8,     0,     9,     0,
      10,    11,     0,     0,    12,    13,    14,     0,    15,     2,
       3,    16,     0,     0,    17,    18,    19,    20,     0,    21,
       0,    22,    23,     0,     0,  -156,     0,     0,     0,     0,
       0,     4,     0,     0,     0,     0,     0,     0,     0,     0,
      27,     0,    28,    29,     0,     0,     5,     6,     0,     0,
       7,     8,     0,     9,     0,    10,    11,     0,     0,    12,
      13,    14,     0,    15,     2,     3,    16,     0,     0,    17,
      18,    19,    20,     0,    21,     0,    22,    23,     2,     3,
       0,     0,     0,     0,     0,     0,     4,     0,     0,     0,
       2,     3,     0,     0,     0,    27,     0,    28,    29,     0,
       4,     5,     6,     0,     0,     7,     8,     0,     9,     0,
       0,    11,     4,     0,     0,     5,     6,     0,     0,     7,
       8,     0,     9,     0,     0,    11,     0,     5,     6,     0,
       0,     7,     8,     0,     9,     0,     0,    11,     0,     0,
       0,     0,     0,    69,     0,    70,     2,     3,     0,     0,
      27,     0,    28,    29,     0,     0,   162,     0,   163,     2,
       3,     0,     0,     0,    27,     0,    28,    29,     4,     0,
     261,     0,     2,     3,     0,     0,    27,     0,    28,    29,
       0,     4,     0,     5,     6,     0,     0,     7,     8,     0,
       9,     0,     0,    11,     4,     0,     5,     6,     0,     0,
       7,     8,     0,     9,     0,     0,    11,     0,     0,     5,
       6,     0,     0,     7,     8,     0,     9,     0,     0,    11,
       0,     0,     0,     0,   272,     0,     0,     2,     3,     0,
       0,     0,    27,     0,    28,    29,     0,     0,     0,   315,
       0,     0,     0,     0,     0,    27,     0,    28,    29,     4,
     117,   118,   119,   120,     0,     0,     0,     0,    27,     0,
      28,    62,     0,     0,     5,     6,     0,     0,     7,     8,
       0,     9,     0,     0,    11,     0,     0,     0,     0,   121,
     122,   123,   124,   125,   126,     0,     0,     0,     0,   127,
     128,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -98,     0,    27,     0,    28,    29,   -98,   -98,   -98,
     -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,   130,
     131,   132,   133,   134,   135,     0,   136,   137,   138,   139,
     140,   141
};

static const short yycheck[] =
{
       2,     3,     4,     5,     6,     0,    28,    13,    14,    15,
      16,    73,     1,    49,    20,    21,   157,   339,   159,   255,
      22,    23,   258,    49,     1,     7,     8,    88,    52,    88,
     100,    49,    79,    80,    81,    82,    97,   198,    97,   361,
      40,    41,    42,    43,   114,    50,   116,    85,    87,    88,
      88,    77,    34,    35,    36,    37,    58,   379,    94,    77,
      49,    78,    44,    45,    81,    82,    87,    88,    89,    74,
       0,     1,    49,    49,    76,     2,     3,     4,     5,     6,
       4,    10,    84,     3,    86,    84,    87,    86,    77,   190,
     191,    91,    92,    93,    95,    88,    44,    45,    27,    28,
      77,    60,    61,    96,    87,    88,    89,   343,    97,   250,
      76,   106,    21,    22,   176,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
      69,   302,    84,    72,    74,    75,    63,    64,    77,   155,
      79,    80,    88,    87,    88,    89,   158,    91,    97,    89,
      88,    96,    87,   180,    96,    52,     3,    83,    53,   186,
      54,   100,   189,    95,     3,   197,   277,    50,    48,    87,
      95,     3,    95,    88,   285,   114,    85,   116,    63,    58,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,    69,    71,    85,    50,    50,    97,    50,
      50,    50,     0,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,     0,   392,    62,    76,
      23,   329,   161,   162,    76,   251,   165,   166,   159,   308,
      72,   342,   338,   172,   177,    31,   347,    -1,   177,    21,
      22,   352,   283,    25,    26,   169,    28,    29,    30,    31,
      32,    33,   169,   192,    -1,   169,   283,   169,   197,   198,
      -1,    -1,    -1,    -1,   375,   376,    -1,    -1,   300,    -1,
      -1,   287,   288,    -1,   385,    -1,   387,    -1,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
      -1,    -1,   319,    -1,    21,    22,   308,    -1,   325,   326,
     312,    28,    29,    30,    31,    32,    33,    -1,    -1,    -1,
      -1,   327,    -1,    -1,    -1,   331,   332,   322,    -1,    -1,
      -1,    -1,    -1,    -1,   263,   337,   353,   266,    -1,    -1,
      -1,   358,   359,   272,    -1,    -1,    -1,   276,    -1,   355,
      -1,    -1,    -1,    -1,   371,    -1,    -1,   374,    -1,    -1,
      -1,    -1,    -1,     1,   366,    -1,    -1,     5,     6,   386,
       3,   300,    -1,   302,    -1,    -1,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,   317,    27,
      -1,    -1,   321,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    42,    43,    -1,    -1,    46,    47,
      -1,    49,    -1,    51,    52,    -1,    -1,    55,    56,    57,
      -1,    59,   351,    -1,    62,    -1,    -1,    65,    66,    67,
      68,    -1,    70,    -1,    72,    73,    74,    75,    76,     4,
       5,     6,    -1,    -1,   373,    -1,    -1,     4,     5,     6,
      -1,    89,    -1,    91,    -1,    93,    94,    -1,    -1,    -1,
      -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      27,    -1,    -1,    -1,    -1,    -1,    -1,    42,    43,    -1,
      -1,    46,    47,    -1,    49,    42,    43,    52,    -1,    46,
      47,    -1,    49,    -1,    -1,    52,    -1,    -1,    -1,    -1,
      -1,    -1,     4,     5,     6,    -1,    -1,    -1,    -1,    -1,
       4,     5,     6,    78,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    78,    -1,    -1,    -1,    27,    91,    -1,    93,    94,
      87,    -1,    97,    27,    91,    -1,    93,    94,    -1,    96,
      42,    43,    -1,    -1,    46,    47,    -1,    49,    42,    43,
      52,    -1,    46,    47,    -1,    49,    -1,    -1,    52,    -1,
      -1,    -1,    -1,    -1,     5,     6,    -1,    -1,    -1,    -1,
      21,    22,    23,    24,    25,    26,    78,    28,    29,    30,
      31,    32,    33,    -1,    78,    -1,    27,    -1,    -1,    91,
      -1,    93,    94,    -1,    -1,    -1,    -1,    91,    -1,    93,
      94,    42,    43,    -1,    -1,    46,    47,    -1,    49,    -1,
      51,    52,    -1,    -1,    55,    56,    57,    -1,    59,     5,
       6,    62,    -1,    -1,    65,    66,    67,    68,    -1,    70,
      -1,    72,    73,    -1,    -1,    76,    -1,    -1,    -1,    -1,
      -1,    27,    -1,    -1,    -1,    -1,    87,    88,    89,    -1,
      91,    -1,    93,    94,    -1,    -1,    42,    43,    -1,    -1,
      46,    47,    -1,    49,    -1,    51,    52,    -1,    -1,    55,
      56,    57,    -1,    59,     5,     6,    62,    -1,    -1,    65,
      66,    67,    68,    -1,    70,    -1,    72,    73,    -1,    -1,
      76,    -1,    -1,    -1,    -1,    -1,    27,    -1,    -1,    -1,
      -1,    87,    88,    -1,    -1,    91,    -1,    93,    94,    -1,
      -1,    42,    43,    -1,    -1,    46,    47,    -1,    49,    -1,
      51,    52,    -1,    -1,    55,    56,    57,    -1,    59,     5,
       6,    62,    -1,    -1,    65,    66,    67,    68,    -1,    70,
      -1,    72,    73,    -1,    -1,    76,    -1,    -1,    -1,    -1,
      -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      91,    -1,    93,    94,    -1,    -1,    42,    43,    -1,    -1,
      46,    47,    -1,    49,    -1,    51,    52,    -1,    -1,    55,
      56,    57,    -1,    59,     5,     6,    62,    -1,    -1,    65,
      66,    67,    68,    -1,    70,    -1,    72,    73,     5,     6,
      -1,    -1,    -1,    -1,    -1,    -1,    27,    -1,    -1,    -1,
       5,     6,    -1,    -1,    -1,    91,    -1,    93,    94,    -1,
      27,    42,    43,    -1,    -1,    46,    47,    -1,    49,    -1,
      -1,    52,    27,    -1,    -1,    42,    43,    -1,    -1,    46,
      47,    -1,    49,    -1,    -1,    52,    -1,    42,    43,    -1,
      -1,    46,    47,    -1,    49,    -1,    -1,    52,    -1,    -1,
      -1,    -1,    -1,    84,    -1,    86,     5,     6,    -1,    -1,
      91,    -1,    93,    94,    -1,    -1,    83,    -1,    85,     5,
       6,    -1,    -1,    -1,    91,    -1,    93,    94,    27,    -1,
      85,    -1,     5,     6,    -1,    -1,    91,    -1,    93,    94,
      -1,    27,    -1,    42,    43,    -1,    -1,    46,    47,    -1,
      49,    -1,    -1,    52,    27,    -1,    42,    43,    -1,    -1,
      46,    47,    -1,    49,    -1,    -1,    52,    -1,    -1,    42,
      43,    -1,    -1,    46,    47,    -1,    49,    -1,    -1,    52,
      -1,    -1,    -1,    -1,    83,    -1,    -1,     5,     6,    -1,
      -1,    -1,    91,    -1,    93,    94,    -1,    -1,    -1,    85,
      -1,    -1,    -1,    -1,    -1,    91,    -1,    93,    94,    27,
       5,     6,     7,     8,    -1,    -1,    -1,    -1,    91,    -1,
      93,    94,    -1,    -1,    42,    43,    -1,    -1,    46,    47,
      -1,    49,    -1,    -1,    52,    -1,    -1,    -1,    -1,    34,
      35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,    44,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,    -1,    91,    -1,    93,    94,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    -1,    28,    29,    30,    31,
      32,    33
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison/bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001 Free Software Foundation, Inc.

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

/* This is the parser code that is written into each bison parser when
   the %semantic_parser declaration is not specified in the grammar.
   It was written by Richard Stallman by simplifying the hairy parser
   used when %semantic_parser is specified.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

#ifdef __cplusplus
# define YYSTD(x) std::x
#else
# define YYSTD(x) x
#endif

#if ! defined (yyoverflow) || defined (YYERROR_VERBOSE)

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
#  define YYSIZE_T YYSTD (size_t)
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#    define YYSIZE_T YYSTD (size_t)
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
#  ifdef __cplusplus
#   include <cstdlib> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T std::size_t
#  else
#   ifdef __STDC__
#    include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#    define YYSIZE_T size_t
#   endif
#  endif
#  define YYSTACK_ALLOC YYSTD (malloc)
#  define YYSTACK_FREE YYSTD (free)
# endif

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
# if YYLSP_NEEDED
  YYLTYPE yyls;
# endif
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# if YYLSP_NEEDED
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAX)
# else
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)
# endif

/* Relocate the TYPE STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Type, Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	yymemcpy ((char *) yyptr, (char *) (Stack),			\
		  yysize * (YYSIZE_T) sizeof (Type));			\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (Type) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif /* ! defined (yyoverflow) || defined (YYERROR_VERBOSE) */


#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# ifdef __cplusplus
#  include <cstddef> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T std::size_t
# else
#  ifdef __STDC__
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
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
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");			\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).

   When YYLLOC_DEFAULT is run, CURRENT is set the location of the
   first token.  By default, to implement support for ranges, extend
   its range to the last symbol.  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)       	\
   Current.last_line   = Rhs[N].last_line;	\
   Current.last_column = Rhs[N].last_column;
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#if YYPURE
# if YYLSP_NEEDED
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, &yylloc, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval, &yylloc)
#  endif
# else /* !YYLSP_NEEDED */
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval)
#  endif
# endif /* !YYLSP_NEEDED */
#else /* !YYPURE */
# define YYLEX			yylex ()
#endif /* !YYPURE */


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  ifdef __cplusplus
#   include <cstdio>  /* INFRINGES ON USER NAME SPACE */
#  else
#   include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYFPRINTF YYSTD (fprintf)
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)
/* Nonzero means print parse trace. [The following comment makes no
   sense to me.  Could someone clarify it?  --akim] Since this is
   uninitialized, it does not stop multiple parsers from coexisting.
   */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
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

#if ! defined (yyoverflow) && ! defined (yymemcpy)
# if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#  define yymemcpy __builtin_memcpy
# else				/* not GNU C or C++ */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
#  if defined (__STDC__) || defined (__cplusplus)
yymemcpy (char *yyto, const char *yyfrom, YYSIZE_T yycount)
#  else
yymemcpy (yyto, yyfrom, yycount)
     char *yyto;
     const char *yyfrom;
     YYSIZE_T yycount;
#  endif
{
  register const char *yyf = yyfrom;
  register char *yyt = yyto;
  register YYSIZE_T yyi = yycount;

  while (yyi-- != 0)
    *yyt++ = *yyf++;
}
# endif
#endif

#ifdef YYERROR_VERBOSE

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
#endif

#line 341 "/usr/share/bison/bison.simple"


/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# ifdef __cplusplus
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else /* !__cplusplus */
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif /* !__cplusplus */
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
int yyparse (void *);
# else
int yyparse (void);
# endif
#endif

/* YY_DECL_VARIABLES -- depending whether we use a pure parser,
   variables are global, or local to YYPARSE.  */

#define YY_DECL_NON_LSP_VARIABLES			\
/* The lookahead symbol.  */				\
int yychar;						\
							\
/* The semantic value of the lookahead symbol. */	\
YYSTYPE yylval;						\
							\
/* Number of parse errors so far.  */			\
int yynerrs;

#if YYLSP_NEEDED
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES			\
						\
/* Location data for the lookahead symbol.  */	\
YYLTYPE yylloc;
#else
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES
#endif


/* If nonreentrant, generate the variables here. */

#if !YYPURE
YY_DECL_VARIABLES
#endif  /* !YYPURE */

int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  /* If reentrant, generate the variables here. */
#if YYPURE
  YY_DECL_VARIABLES
#endif  /* !YYPURE */

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack. */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

#if YYLSP_NEEDED
  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
#endif

#if YYLSP_NEEDED
# define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
# define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  YYSIZE_T yystacksize = YYINITDEPTH;


  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
#if YYLSP_NEEDED
  YYLTYPE yyloc;
#endif

  /* When reducing, the number of symbols on the RHS of the reduced
     rule. */
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
#if YYLSP_NEEDED
  yylsp = yyls;
#endif
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

  if (yyssp >= yyss + yystacksize - 1)
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
	   data in use in that stack, in bytes.  */
# if YYLSP_NEEDED
	YYLTYPE *yyls1 = yyls;
	/* This used to be a conditional around just the two extra args,
	   but that might be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
# else
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);
# endif
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (short, yyss);
	YYSTACK_RELOCATE (YYSTYPE, yyvs);
# if YYLSP_NEEDED
	YYSTACK_RELOCATE (YYLTYPE, yyls);
# endif
# undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
#if YYLSP_NEEDED
      yylsp = yyls + yysize - 1;
#endif

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyssp >= yyss + yystacksize - 1)
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
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

#if YYDEBUG
     /* We have to keep this `#if YYDEBUG', since we use variables
	which are defined only if `YYDEBUG' is set.  */
      if (yydebug)
	{
	  YYFPRINTF (stderr, "Next token is %d (%s",
		     yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise
	     meaning of a token, for further debugging info.  */
# ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
# endif
	  YYFPRINTF (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

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

     Otherwise, the following line sets YYVAL to the semantic value of
     the lookahead token.  This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

#if YYLSP_NEEDED
  /* Similarly for the default location.  Let the user run additional
     commands if for instance locations are ranges.  */
  yyloc = yylsp[1-yylen];
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
#endif

#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] > 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif

  switch (yyn) {

case 1:
#line 463 "parse.y"
{
		    global_command = yyvsp[0].tree_statement_list_type;
		    promptflag = 1;
		    YYACCEPT;
		  }
    break;
case 2:
#line 469 "parse.y"
{ ABORT_PARSE; }
    break;
case 3:
#line 471 "parse.y"
{ ABORT_PARSE; }
    break;
case 4:
#line 475 "parse.y"
{ yyval.tree_statement_list_type = 0; }
    break;
case 5:
#line 477 "parse.y"
{
		    parser_end_of_input = 1;
		    yyval.tree_statement_list_type = 0;
		  }
    break;
case 6:
#line 482 "parse.y"
{ yyval.tree_statement_list_type = yyvsp[0].tree_statement_list_type; }
    break;
case 7:
#line 484 "parse.y"
{ yyval.tree_statement_list_type = yyvsp[-1].tree_statement_list_type; }
    break;
case 8:
#line 486 "parse.y"
{ yyval.tree_statement_list_type = yyvsp[-1].tree_statement_list_type; }
    break;
case 9:
#line 490 "parse.y"
{
		    set_stmt_print_flag (yyvsp[-1].tree_statement_list_type, yyvsp[0].sep_type, false);
		    yyval.tree_statement_list_type = yyvsp[-1].tree_statement_list_type;
		  }
    break;
case 10:
#line 497 "parse.y"
{ yyval.tree_statement_list_type = new tree_statement_list (yyvsp[0].tree_statement_type); }
    break;
case 11:
#line 499 "parse.y"
{
		    set_stmt_print_flag (yyvsp[-2].tree_statement_list_type, yyvsp[-1].sep_type, false);
		    yyvsp[-2].tree_statement_list_type->append (yyvsp[0].tree_statement_type);
		    yyval.tree_statement_list_type = yyvsp[-2].tree_statement_list_type;
		  }
    break;
case 12:
#line 507 "parse.y"
{ yyval.tree_statement_list_type = new tree_statement_list (); }
    break;
case 13:
#line 509 "parse.y"
{ yyval.tree_statement_list_type = yyvsp[0].tree_statement_list_type; }
    break;
case 14:
#line 513 "parse.y"
{
		    set_stmt_print_flag (yyvsp[-1].tree_statement_list_type, yyvsp[0].sep_type, true);
		    yyval.tree_statement_list_type = yyvsp[-1].tree_statement_list_type;
		  }
    break;
case 15:
#line 520 "parse.y"
{
		    lexer_flags.beginning_of_function = false;
		    yyval.tree_statement_list_type = new tree_statement_list (yyvsp[0].tree_statement_type);
		  }
    break;
case 16:
#line 525 "parse.y"
{
		    set_stmt_print_flag (yyvsp[-2].tree_statement_list_type, yyvsp[-1].sep_type, true);
		    yyvsp[-2].tree_statement_list_type->append (yyvsp[0].tree_statement_type);
		    yyval.tree_statement_list_type = yyvsp[-2].tree_statement_list_type;
		  }
    break;
case 17:
#line 533 "parse.y"
{
		    octave_comment_list *comment
		      = octave_comment_buffer::get_comment ();

		    yyval.tree_statement_type = new tree_statement (yyvsp[0].tree_expression_type, comment);
		  }
    break;
case 18:
#line 540 "parse.y"
{
		    octave_comment_list *comment
		      = octave_comment_buffer::get_comment ();

		    yyval.tree_statement_type = new tree_statement (yyvsp[0].tree_command_type, comment);
		  }
    break;
case 19:
#line 547 "parse.y"
{
		    symbol_record *sr = lookup_by_name ("clearplot", 0);
		    tree_identifier *id = new tree_identifier (sr);

		    octave_comment_list *comment
		      = octave_comment_buffer::get_comment ();

		    yyval.tree_statement_type = new tree_statement (id, comment);
		  }
    break;
case 20:
#line 563 "parse.y"
{
		    yyval.tree_identifier_type = new tree_identifier
		      (yyvsp[0].tok_val->sym_rec (), yyvsp[0].tok_val->line (), yyvsp[0].tok_val->column ());
		  }
    break;
case 21:
#line 570 "parse.y"
{ yyval.tree_constant_type = make_constant (NUM, yyvsp[0].tok_val); }
    break;
case 22:
#line 572 "parse.y"
{ yyval.tree_constant_type = make_constant (IMAG_NUM, yyvsp[0].tok_val); }
    break;
case 23:
#line 574 "parse.y"
{ yyval.tree_constant_type = make_constant (TEXT, yyvsp[0].tok_val); }
    break;
case 24:
#line 579 "parse.y"
{ lexer_flags.looking_at_matrix_or_assign_lhs = true; }
    break;
case 25:
#line 583 "parse.y"
{ yyval.tree_expression_type = new tree_constant (octave_value (Matrix ())); }
    break;
case 26:
#line 585 "parse.y"
{ yyval.tree_expression_type = new tree_constant (octave_value (Matrix ())); }
    break;
case 27:
#line 587 "parse.y"
{
		    yyval.tree_expression_type = finish_matrix (yyvsp[-1].tree_matrix_type);
		    lexer_flags.looking_at_matrix_or_assign_lhs = false;
		  }
    break;
case 28:
#line 594 "parse.y"
{ yyval.tree_matrix_type = yyvsp[0].tree_matrix_type; }
    break;
case 29:
#line 596 "parse.y"
{ yyval.tree_matrix_type = yyvsp[-1].tree_matrix_type; }
    break;
case 30:
#line 600 "parse.y"
{ yyval.tree_matrix_type = new tree_matrix (yyvsp[0].tree_argument_list_type); }
    break;
case 31:
#line 602 "parse.y"
{
		    yyvsp[-2].tree_matrix_type->append (yyvsp[0].tree_argument_list_type);
		    yyval.tree_matrix_type = yyvsp[-2].tree_matrix_type;
		  }
    break;
case 32:
#line 609 "parse.y"
{ yyval.tree_expression_type = new tree_constant (octave_value (Matrix ())); }
    break;
case 33:
#line 611 "parse.y"
{ yyval.tree_expression_type = new tree_constant (octave_value (Matrix ())); }
    break;
case 34:
#line 613 "parse.y"
{ yyval.tree_expression_type = finish_cell (yyvsp[-1].tree_cell_type); }
    break;
case 35:
#line 617 "parse.y"
{ yyval.tree_cell_type = yyvsp[0].tree_cell_type; }
    break;
case 36:
#line 619 "parse.y"
{ yyval.tree_cell_type = yyvsp[-1].tree_cell_type; }
    break;
case 37:
#line 623 "parse.y"
{ yyval.tree_cell_type = new tree_cell (yyvsp[0].tree_argument_list_type); }
    break;
case 38:
#line 625 "parse.y"
{
		    yyvsp[-2].tree_cell_type->append (yyvsp[0].tree_argument_list_type);
		    yyval.tree_cell_type = yyvsp[-2].tree_cell_type;
		  }
    break;
case 39:
#line 633 "parse.y"
{ yyval.tree_argument_list_type = yyvsp[0].tree_argument_list_type; }
    break;
case 40:
#line 635 "parse.y"
{ yyval.tree_argument_list_type = yyvsp[-1].tree_argument_list_type; }
    break;
case 41:
#line 639 "parse.y"
{ yyval.tree_expression_type = yyvsp[0].tree_identifier_type; }
    break;
case 42:
#line 641 "parse.y"
{ yyval.tree_expression_type = yyvsp[0].tree_constant_type; }
    break;
case 43:
#line 643 "parse.y"
{ yyval.tree_expression_type = yyvsp[0].tree_expression_type; }
    break;
case 44:
#line 645 "parse.y"
{ yyval.tree_expression_type = yyvsp[0].tree_expression_type; }
    break;
case 45:
#line 647 "parse.y"
{ yyval.tree_expression_type = yyvsp[-1].tree_expression_type->mark_in_parens (); }
    break;
case 46:
#line 651 "parse.y"
{
		    octave_value tmp (octave_value::magic_colon_t);
		    yyval.tree_constant_type = new tree_constant (tmp);
		  }
    break;
case 47:
#line 658 "parse.y"
{ yyval.tree_argument_list_type = new tree_argument_list (yyvsp[0].tree_expression_type); }
    break;
case 48:
#line 660 "parse.y"
{ yyval.tree_argument_list_type = new tree_argument_list (yyvsp[0].tree_constant_type); }
    break;
case 49:
#line 662 "parse.y"
{
		    octave_value tmp (octave_value::all_va_args_t);
		    tree_constant *all_va_args = new tree_constant (tmp);
		    yyval.tree_argument_list_type = new tree_argument_list (all_va_args);
		  }
    break;
case 50:
#line 668 "parse.y"
{
		    yyvsp[-2].tree_argument_list_type->append (yyvsp[0].tree_constant_type);
		    yyval.tree_argument_list_type = yyvsp[-2].tree_argument_list_type;
		  }
    break;
case 51:
#line 673 "parse.y"
{
		    yyvsp[-2].tree_argument_list_type->append (yyvsp[0].tree_expression_type);
		    yyval.tree_argument_list_type = yyvsp[-2].tree_argument_list_type;
		  }
    break;
case 52:
#line 678 "parse.y"
{
		    octave_value tmp (octave_value::all_va_args_t);
		    tree_constant *all_va_args = new tree_constant (tmp);
		    yyvsp[-2].tree_argument_list_type->append (all_va_args);
		    yyval.tree_argument_list_type = yyvsp[-2].tree_argument_list_type;
		  }
    break;
case 53:
#line 687 "parse.y"
{ lexer_flags.looking_at_indirect_ref = true; }
    break;
case 54:
#line 691 "parse.y"
{ yyval.tree_expression_type = yyvsp[0].tree_expression_type; }
    break;
case 55:
#line 693 "parse.y"
{ yyval.tree_expression_type = make_index_expression (yyvsp[-2].tree_expression_type, 0); }
    break;
case 56:
#line 695 "parse.y"
{ yyval.tree_expression_type = make_index_expression (yyvsp[-3].tree_expression_type, yyvsp[-1].tree_argument_list_type); }
    break;
case 57:
#line 697 "parse.y"
{ yyval.tree_expression_type = make_index_expression (yyvsp[-3].tree_expression_type, yyvsp[-1].tree_argument_list_type); }
    break;
case 58:
#line 699 "parse.y"
{ yyval.tree_expression_type = make_postfix_op (PLUS_PLUS, yyvsp[-1].tree_expression_type, yyvsp[0].tok_val); }
    break;
case 59:
#line 701 "parse.y"
{ yyval.tree_expression_type = make_postfix_op (MINUS_MINUS, yyvsp[-1].tree_expression_type, yyvsp[0].tok_val); }
    break;
case 60:
#line 703 "parse.y"
{ yyval.tree_expression_type = make_postfix_op (QUOTE, yyvsp[-1].tree_expression_type, yyvsp[0].tok_val); }
    break;
case 61:
#line 705 "parse.y"
{ yyval.tree_expression_type = make_postfix_op (TRANSPOSE, yyvsp[-1].tree_expression_type, yyvsp[0].tok_val); }
    break;
case 62:
#line 707 "parse.y"
{ yyval.tree_expression_type = make_indirect_ref (yyvsp[-3].tree_expression_type, yyvsp[0].tok_val->text ()); }
    break;
case 63:
#line 711 "parse.y"
{ yyval.tree_expression_type = yyvsp[0].tree_expression_type; }
    break;
case 64:
#line 713 "parse.y"
{ yyval.tree_expression_type = yyvsp[0].tree_expression_type; }
    break;
case 65:
#line 715 "parse.y"
{ yyval.tree_expression_type = make_prefix_op (PLUS_PLUS, yyvsp[0].tree_expression_type, yyvsp[-1].tok_val); }
    break;
case 66:
#line 717 "parse.y"
{ yyval.tree_expression_type = make_prefix_op (MINUS_MINUS, yyvsp[0].tree_expression_type, yyvsp[-1].tok_val); }
    break;
case 67:
#line 719 "parse.y"
{ yyval.tree_expression_type = make_prefix_op (EXPR_NOT, yyvsp[0].tree_expression_type, yyvsp[-1].tok_val); }
    break;
case 68:
#line 721 "parse.y"
{ yyval.tree_expression_type = yyvsp[0].tree_expression_type; }
    break;
case 69:
#line 723 "parse.y"
{ yyval.tree_expression_type = make_prefix_op ('-', yyvsp[0].tree_expression_type, yyvsp[-1].tok_val); }
    break;
case 70:
#line 727 "parse.y"
{ yyval.tree_expression_type = make_binary_op (POW, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 71:
#line 729 "parse.y"
{ yyval.tree_expression_type = make_binary_op (EPOW, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 72:
#line 731 "parse.y"
{ yyval.tree_expression_type = make_binary_op ('+', yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 73:
#line 733 "parse.y"
{ yyval.tree_expression_type = make_binary_op ('-', yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 74:
#line 735 "parse.y"
{ yyval.tree_expression_type = make_binary_op ('*', yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 75:
#line 737 "parse.y"
{ yyval.tree_expression_type = make_binary_op ('/', yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 76:
#line 739 "parse.y"
{ yyval.tree_expression_type = make_binary_op ('+', yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 77:
#line 741 "parse.y"
{ yyval.tree_expression_type = make_binary_op ('-', yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 78:
#line 743 "parse.y"
{ yyval.tree_expression_type = make_binary_op (EMUL, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 79:
#line 745 "parse.y"
{ yyval.tree_expression_type = make_binary_op (EDIV, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 80:
#line 747 "parse.y"
{ yyval.tree_expression_type = make_binary_op (LEFTDIV, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 81:
#line 749 "parse.y"
{ yyval.tree_expression_type = make_binary_op (ELEFTDIV, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 82:
#line 753 "parse.y"
{ yyval.tree_expression_type = finish_colon_expression (yyvsp[0].tree_colon_expression_type); }
    break;
case 83:
#line 757 "parse.y"
{ yyval.tree_colon_expression_type = new tree_colon_expression (yyvsp[0].tree_expression_type); }
    break;
case 84:
#line 759 "parse.y"
{
		    if (! (yyval.tree_colon_expression_type = yyvsp[-2].tree_colon_expression_type->append (yyvsp[0].tree_expression_type)))
		      ABORT_PARSE;
		  }
    break;
case 85:
#line 766 "parse.y"
{ yyval.tree_expression_type = yyvsp[0].tree_expression_type; }
    break;
case 86:
#line 768 "parse.y"
{ yyval.tree_expression_type = make_binary_op (LSHIFT, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 87:
#line 770 "parse.y"
{ yyval.tree_expression_type = make_binary_op (RSHIFT, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 88:
#line 772 "parse.y"
{ yyval.tree_expression_type = make_binary_op (EXPR_LT, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 89:
#line 774 "parse.y"
{ yyval.tree_expression_type = make_binary_op (EXPR_LE, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 90:
#line 776 "parse.y"
{ yyval.tree_expression_type = make_binary_op (EXPR_EQ, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 91:
#line 778 "parse.y"
{ yyval.tree_expression_type = make_binary_op (EXPR_GE, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 92:
#line 780 "parse.y"
{ yyval.tree_expression_type = make_binary_op (EXPR_GT, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 93:
#line 782 "parse.y"
{ yyval.tree_expression_type = make_binary_op (EXPR_NE, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 94:
#line 784 "parse.y"
{ yyval.tree_expression_type = make_binary_op (EXPR_AND, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 95:
#line 786 "parse.y"
{ yyval.tree_expression_type = make_binary_op (EXPR_OR, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 96:
#line 788 "parse.y"
{ yyval.tree_expression_type = make_boolean_op (EXPR_AND_AND, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 97:
#line 790 "parse.y"
{ yyval.tree_expression_type = make_boolean_op (EXPR_OR_OR, yyvsp[-2].tree_expression_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 98:
#line 797 "parse.y"
{ yyval.tree_argument_list_type = new tree_argument_list (yyvsp[0].tree_expression_type); }
    break;
case 99:
#line 799 "parse.y"
{
		    yyval.tree_argument_list_type = yyvsp[-1].tree_argument_list_type;
		    lexer_flags.looking_at_matrix_or_assign_lhs = false;
		  }
    break;
case 100:
#line 806 "parse.y"
{ yyval.tree_expression_type = make_assign_op ('=', yyvsp[-2].tree_argument_list_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 101:
#line 808 "parse.y"
{ yyval.tree_expression_type = make_assign_op (ADD_EQ, yyvsp[-2].tree_argument_list_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 102:
#line 810 "parse.y"
{ yyval.tree_expression_type = make_assign_op (SUB_EQ, yyvsp[-2].tree_argument_list_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 103:
#line 812 "parse.y"
{ yyval.tree_expression_type = make_assign_op (MUL_EQ, yyvsp[-2].tree_argument_list_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 104:
#line 814 "parse.y"
{ yyval.tree_expression_type = make_assign_op (DIV_EQ, yyvsp[-2].tree_argument_list_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 105:
#line 816 "parse.y"
{ yyval.tree_expression_type = make_assign_op (LEFTDIV_EQ, yyvsp[-2].tree_argument_list_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 106:
#line 818 "parse.y"
{ yyval.tree_expression_type = make_assign_op (LSHIFT_EQ, yyvsp[-2].tree_argument_list_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 107:
#line 820 "parse.y"
{ yyval.tree_expression_type = make_assign_op (RSHIFT_EQ, yyvsp[-2].tree_argument_list_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 108:
#line 822 "parse.y"
{ yyval.tree_expression_type = make_assign_op (EMUL_EQ, yyvsp[-2].tree_argument_list_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 109:
#line 824 "parse.y"
{ yyval.tree_expression_type = make_assign_op (EDIV_EQ, yyvsp[-2].tree_argument_list_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 110:
#line 826 "parse.y"
{ yyval.tree_expression_type = make_assign_op (ELEFTDIV_EQ, yyvsp[-2].tree_argument_list_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 111:
#line 828 "parse.y"
{ yyval.tree_expression_type = make_assign_op (AND_EQ, yyvsp[-2].tree_argument_list_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 112:
#line 830 "parse.y"
{ yyval.tree_expression_type = make_assign_op (OR_EQ, yyvsp[-2].tree_argument_list_type, yyvsp[-1].tok_val, yyvsp[0].tree_expression_type); }
    break;
case 113:
#line 834 "parse.y"
{ yyval.tree_index_expression_type = make_index_expression (yyvsp[-1].tree_identifier_type, yyvsp[0].tree_argument_list_type); }
    break;
case 114:
#line 838 "parse.y"
{
		    tree_constant *tmp = make_constant (TEXT, yyvsp[0].tok_val);
		    yyval.tree_argument_list_type = new tree_argument_list (tmp);
		  }
    break;
case 115:
#line 843 "parse.y"
{
		    tree_constant *tmp = make_constant (TEXT, yyvsp[0].tok_val);
		    yyvsp[-1].tree_argument_list_type->append (tmp);
		    yyval.tree_argument_list_type = yyvsp[-1].tree_argument_list_type;
		  }
    break;
case 116:
#line 851 "parse.y"
{ yyval.tree_expression_type = yyvsp[0].tree_expression_type; }
    break;
case 117:
#line 853 "parse.y"
{ yyval.tree_expression_type = yyvsp[0].tree_index_expression_type; }
    break;
case 118:
#line 855 "parse.y"
{ yyval.tree_expression_type = yyvsp[0].tree_expression_type; }
    break;
case 119:
#line 863 "parse.y"
{ yyval.tree_command_type = yyvsp[0].tree_decl_command_type; }
    break;
case 120:
#line 865 "parse.y"
{ yyval.tree_command_type = yyvsp[0].tree_command_type; }
    break;
case 121:
#line 867 "parse.y"
{ yyval.tree_command_type = yyvsp[0].tree_command_type; }
    break;
case 122:
#line 869 "parse.y"
{ yyval.tree_command_type = yyvsp[0].tree_command_type; }
    break;
case 123:
#line 871 "parse.y"
{ yyval.tree_command_type = yyvsp[0].tree_command_type; }
    break;
case 124:
#line 873 "parse.y"
{ yyval.tree_command_type = yyvsp[0].tree_command_type; }
    break;
case 125:
#line 875 "parse.y"
{ yyval.tree_command_type = yyvsp[0].tree_plot_command_type; }
    break;
case 126:
#line 883 "parse.y"
{ yyval.tree_decl_command_type = make_decl_command (GLOBAL, yyvsp[-1].tok_val, yyvsp[0].tree_decl_init_list_type); }
    break;
case 127:
#line 885 "parse.y"
{ yyval.tree_decl_command_type = make_decl_command (STATIC, yyvsp[-1].tok_val, yyvsp[0].tree_decl_init_list_type); }
    break;
case 128:
#line 889 "parse.y"
{ yyval.tree_decl_init_list_type = new tree_decl_init_list (yyvsp[0].tree_decl_elt_type); }
    break;
case 129:
#line 891 "parse.y"
{
		    yyvsp[-1].tree_decl_init_list_type->append (yyvsp[0].tree_decl_elt_type);
		    yyval.tree_decl_init_list_type = yyvsp[-1].tree_decl_init_list_type;
		  }
    break;
case 130:
#line 898 "parse.y"
{ yyval.tree_decl_elt_type = new tree_decl_elt (yyvsp[0].tree_identifier_type); }
    break;
case 131:
#line 900 "parse.y"
{ yyval.tree_decl_elt_type = new tree_decl_elt (yyvsp[-2].tree_identifier_type, yyvsp[0].tree_expression_type); }
    break;
case 132:
#line 908 "parse.y"
{ yyval.tree_command_type = yyvsp[0].tree_if_command_type; }
    break;
case 133:
#line 910 "parse.y"
{ yyval.tree_command_type = yyvsp[0].tree_switch_command_type; }
    break;
case 134:
#line 918 "parse.y"
{
		    if (! (yyval.tree_if_command_type = finish_if_command (yyvsp[-3].tok_val, yyvsp[-1].tree_if_command_list_type, yyvsp[0].tok_val, yyvsp[-2].comment_type)))
		      ABORT_PARSE;
		  }
    break;
case 135:
#line 925 "parse.y"
{ yyval.tree_if_command_list_type = yyvsp[0].tree_if_command_list_type; }
    break;
case 136:
#line 927 "parse.y"
{
		    yyvsp[-1].tree_if_command_list_type->append (yyvsp[0].tree_if_clause_type);
		    yyval.tree_if_command_list_type = yyvsp[-1].tree_if_command_list_type;
		  }
    break;
case 137:
#line 934 "parse.y"
{ yyval.tree_if_command_list_type = start_if_command (yyvsp[-2].tree_expression_type, yyvsp[0].tree_statement_list_type); }
    break;
case 138:
#line 936 "parse.y"
{
		    yyvsp[-1].tree_if_command_list_type->append (yyvsp[0].tree_if_clause_type);
		    yyval.tree_if_command_list_type = yyvsp[-1].tree_if_command_list_type;
		  }
    break;
case 139:
#line 943 "parse.y"
{ yyval.tree_if_clause_type = make_elseif_clause (yyvsp[-2].tree_expression_type, yyvsp[0].tree_statement_list_type, yyvsp[-4].comment_type); }
    break;
case 140:
#line 947 "parse.y"
{
		    yyval.tree_if_clause_type = new tree_if_clause (yyvsp[0].tree_statement_list_type, yyvsp[-2].comment_type);
		  }
    break;
case 141:
#line 957 "parse.y"
{
		    if (! (yyval.tree_switch_command_type = finish_switch_command (yyvsp[-5].tok_val, yyvsp[-3].tree_expression_type, yyvsp[-1].tree_switch_case_list_type, yyvsp[0].tok_val, yyvsp[-4].comment_type)))
		      ABORT_PARSE;
		  }
    break;
case 142:
#line 964 "parse.y"
{ yyval.tree_switch_case_list_type = yyvsp[0].tree_switch_case_list_type; }
    break;
case 143:
#line 966 "parse.y"
{
		    yyvsp[-1].tree_switch_case_list_type->append (yyvsp[0].tree_switch_case_type);
		    yyval.tree_switch_case_list_type = yyvsp[-1].tree_switch_case_list_type;
		  }
    break;
case 144:
#line 973 "parse.y"
{ yyval.tree_switch_case_list_type = new tree_switch_case_list (yyvsp[0].tree_switch_case_type); }
    break;
case 145:
#line 975 "parse.y"
{
		    yyvsp[-1].tree_switch_case_list_type->append (yyvsp[0].tree_switch_case_type);
		    yyval.tree_switch_case_list_type = yyvsp[-1].tree_switch_case_list_type;
		  }
    break;
case 146:
#line 982 "parse.y"
{ yyval.tree_switch_case_type = make_switch_case (yyvsp[-2].tree_expression_type, yyvsp[0].tree_statement_list_type, yyvsp[-4].comment_type); }
    break;
case 147:
#line 986 "parse.y"
{
		    yyval.tree_switch_case_type = new tree_switch_case (yyvsp[0].tree_statement_list_type, yyvsp[-2].comment_type);
		  }
    break;
case 148:
#line 996 "parse.y"
{
		    if (! (yyval.tree_command_type = make_while_command (yyvsp[-5].tok_val, yyvsp[-3].tree_expression_type, yyvsp[-1].tree_statement_list_type, yyvsp[0].tok_val, yyvsp[-4].comment_type)))
		      ABORT_PARSE;
		  }
    break;
case 149:
#line 1001 "parse.y"
{
		    if (! (yyval.tree_command_type = make_do_until_command (yyvsp[-5].tok_val, yyvsp[-2].tree_statement_list_type, yyvsp[0].tree_expression_type, yyvsp[-4].comment_type)))
		      ABORT_PARSE;
		  }
    break;
case 150:
#line 1006 "parse.y"
{
		    if (! (yyval.tree_command_type = make_for_command (yyvsp[-7].tok_val, yyvsp[-5].tree_argument_list_type, yyvsp[-3].tree_expression_type, yyvsp[-1].tree_statement_list_type, yyvsp[0].tok_val, yyvsp[-6].comment_type)))
		      ABORT_PARSE;
		  }
    break;
case 151:
#line 1017 "parse.y"
{
		    if (! (yyval.tree_command_type = make_break_command (yyvsp[0].tok_val)))
		      ABORT_PARSE;
		  }
    break;
case 152:
#line 1022 "parse.y"
{
		    if (! (yyval.tree_command_type = make_continue_command (yyvsp[0].tok_val)))
		      ABORT_PARSE;
		  }
    break;
case 153:
#line 1027 "parse.y"
{
		    if (! (yyval.tree_command_type = make_return_command (yyvsp[0].tok_val)))
		      ABORT_PARSE;
		  }
    break;
case 154:
#line 1039 "parse.y"
{
		    if (! (yyval.tree_command_type = make_unwind_command (yyvsp[-8].tok_val, yyvsp[-5].tree_statement_list_type, yyvsp[-1].tree_statement_list_type, yyvsp[0].tok_val, yyvsp[-7].comment_type, yyvsp[-3].comment_type)))
		      ABORT_PARSE;
		  }
    break;
case 155:
#line 1045 "parse.y"
{
		    if (! (yyval.tree_command_type = make_try_command (yyvsp[-8].tok_val, yyvsp[-5].tree_statement_list_type, yyvsp[-1].tree_statement_list_type, yyvsp[0].tok_val, yyvsp[-7].comment_type, yyvsp[-3].comment_type)))
		      ABORT_PARSE;
		  }
    break;
case 156:
#line 1056 "parse.y"
{
		    if (symtab_context)
		      panic_impossible ();

		    symtab_context = curr_sym_tab;
		  }
    break;
case 157:
#line 1065 "parse.y"
{ curr_sym_tab = global_sym_tab; }
    break;
case 158:
#line 1069 "parse.y"
{ curr_sym_tab = tmp_local_sym_tab; }
    break;
case 159:
#line 1073 "parse.y"
{ lexer_flags.looking_at_return_list = true; }
    break;
case 160:
#line 1077 "parse.y"
{ lexer_flags.parsed_function_name = true; }
    break;
case 161:
#line 1085 "parse.y"
{ lexer_flags.looking_at_parameter_list = true; }
    break;
case 162:
#line 1089 "parse.y"
{ lexer_flags.looking_at_parameter_list = false; }
    break;
case 163:
#line 1093 "parse.y"
{
		    lexer_flags.quote_is_transpose = false;
		    yyval.tree_parameter_list_type = 0;
		  }
    break;
case 164:
#line 1098 "parse.y"
{
		    lexer_flags.quote_is_transpose = false;
		    tree_parameter_list *tmp = new tree_parameter_list ();
		    tmp->mark_varargs_only ();
		    yyval.tree_parameter_list_type = tmp;
		  }
    break;
case 165:
#line 1105 "parse.y"
{
		    lexer_flags.quote_is_transpose = false;
		    yyvsp[-1].tree_parameter_list_type->mark_as_formal_parameters ();
		    yyval.tree_parameter_list_type = yyvsp[-1].tree_parameter_list_type;
		  }
    break;
case 166:
#line 1111 "parse.y"
{
		    lexer_flags.quote_is_transpose = false;
		    yyvsp[-3].tree_parameter_list_type->mark_as_formal_parameters ();
		    yyvsp[-3].tree_parameter_list_type->mark_varargs ();
		    yyval.tree_parameter_list_type = yyvsp[-3].tree_parameter_list_type;
		  }
    break;
case 167:
#line 1120 "parse.y"
{ yyval.tree_parameter_list_type = new tree_parameter_list (yyvsp[0].tree_identifier_type); }
    break;
case 168:
#line 1122 "parse.y"
{
		    yyvsp[-2].tree_parameter_list_type->append (yyvsp[0].tree_identifier_type);
		    yyval.tree_parameter_list_type = yyvsp[-2].tree_parameter_list_type;
		  }
    break;
case 169:
#line 1127 "parse.y"
{
		    yyerror ("invalid parameter list");
		    yyval.tree_parameter_list_type = 0;
		    ABORT_PARSE;
		  }
    break;
case 170:
#line 1133 "parse.y"
{
		    yyerror ("invalid parameter list");
		    yyval.tree_parameter_list_type = 0;
		    ABORT_PARSE;
		  }
    break;
case 172:
#line 1148 "parse.y"
{
		    lexer_flags.looking_at_return_list = false;
		    yyval.tree_parameter_list_type = new tree_parameter_list ();
		  }
    break;
case 173:
#line 1153 "parse.y"
{
		    lexer_flags.looking_at_return_list = false;
		    tree_parameter_list *tmp = new tree_parameter_list ();
		    tmp->mark_varargs_only ();
		    yyval.tree_parameter_list_type = tmp;
		  }
    break;
case 174:
#line 1160 "parse.y"
{
		    lexer_flags.looking_at_return_list = false;
		    yyval.tree_parameter_list_type = yyvsp[-1].tree_parameter_list_type;
		  }
    break;
case 175:
#line 1165 "parse.y"
{
		    lexer_flags.looking_at_return_list = false;
		    yyvsp[-3].tree_parameter_list_type->mark_varargs ();
		    yyval.tree_parameter_list_type = yyvsp[-3].tree_parameter_list_type;
		  }
    break;
case 176:
#line 1173 "parse.y"
{ yyval.tree_parameter_list_type = new tree_parameter_list (yyvsp[0].tree_identifier_type); }
    break;
case 177:
#line 1175 "parse.y"
{
		    yyvsp[-2].tree_parameter_list_type->append (yyvsp[0].tree_identifier_type);
		    yyval.tree_parameter_list_type = yyvsp[-2].tree_parameter_list_type;
		  }
    break;
case 179:
#line 1189 "parse.y"
{ yyval.comment_type = yyvsp[-1].comment_type; }
    break;
case 180:
#line 1193 "parse.y"
{
		    yyvsp[0].octave_user_function_type->stash_leading_comment (yyvsp[-1].comment_type);
		    recover_from_parsing_function ();
		    yyval.tree_command_type = 0;
		  }
    break;
case 181:
#line 1199 "parse.y"
{
		    finish_function (yyvsp[-1].tree_identifier_type, yyvsp[0].octave_user_function_type, yyvsp[-2].comment_type);
		    recover_from_parsing_function ();
		    yyval.tree_command_type = 0;
		  }
    break;
case 182:
#line 1205 "parse.y"
{
		    finish_function (yyvsp[-1].tree_parameter_list_type, yyvsp[0].octave_user_function_type, yyvsp[-2].comment_type);
		    recover_from_parsing_function ();
		    yyval.tree_command_type = 0;
		  }
    break;
case 183:
#line 1213 "parse.y"
{ yyval.octave_user_function_type = yyvsp[0].octave_user_function_type; }
    break;
case 184:
#line 1217 "parse.y"
{
		    if (! (yyval.octave_user_function_type = frob_function (yyvsp[-3].tree_identifier_type, yyvsp[0].octave_user_function_type)))
		      ABORT_PARSE;
		  }
    break;
case 185:
#line 1224 "parse.y"
{ yyval.octave_user_function_type = start_function (yyvsp[-1].tree_parameter_list_type, yyvsp[0].tree_statement_list_type); }
    break;
case 186:
#line 1226 "parse.y"
{ yyval.octave_user_function_type = start_function (0, yyvsp[0].tree_statement_list_type); }
    break;
case 187:
#line 1230 "parse.y"
{ yyval.tree_statement_list_type = yyvsp[-1].tree_statement_list_type; }
    break;
case 188:
#line 1234 "parse.y"
{
		    if (end_token_ok (yyvsp[0].tok_val, token::function_end))
		      {
			if (reading_fcn_file)
			  check_for_garbage_after_fcn_def ();
		      }
		    else
		      ABORT_PARSE;
		  }
    break;
case 189:
#line 1244 "parse.y"
{
		    if (! (reading_fcn_file || reading_script_file))
		      YYABORT;
		  }
    break;
case 190:
#line 1255 "parse.y"
{
		    if (! (yyval.tree_plot_command_type = make_plot_command (yyvsp[0].tok_val, 0, 0)))
		      ABORT_PARSE;
		  }
    break;
case 191:
#line 1260 "parse.y"
{
		    if (! (yyval.tree_plot_command_type = make_plot_command (yyvsp[-1].tok_val, yyvsp[0].plot_limits_type, 0)))
		      ABORT_PARSE;
		  }
    break;
case 192:
#line 1265 "parse.y"
{
		    if (! (yyval.tree_plot_command_type = make_plot_command (yyvsp[-1].tok_val, 0, yyvsp[0].subplot_list_type)))
		      ABORT_PARSE;
		  }
    break;
case 193:
#line 1270 "parse.y"
{
		    if (! (yyval.tree_plot_command_type = make_plot_command (yyvsp[-2].tok_val, yyvsp[-1].plot_limits_type, yyvsp[0].subplot_list_type)))
		      ABORT_PARSE;
		  }
    break;
case 194:
#line 1277 "parse.y"
{ yyval.plot_limits_type = new plot_limits (yyvsp[0].plot_range_type); }
    break;
case 195:
#line 1279 "parse.y"
{ yyval.plot_limits_type = new plot_limits (yyvsp[-1].plot_range_type, yyvsp[0].plot_range_type); }
    break;
case 196:
#line 1281 "parse.y"
{ yyval.plot_limits_type = new plot_limits (yyvsp[-2].plot_range_type, yyvsp[-1].plot_range_type, yyvsp[0].plot_range_type); }
    break;
case 197:
#line 1285 "parse.y"
{ yyval.plot_range_type = new plot_range (yyvsp[-3].tree_expression_type, yyvsp[-1].tree_expression_type); }
    break;
case 198:
#line 1287 "parse.y"
{ yyval.plot_range_type = new plot_range (0, yyvsp[-1].tree_expression_type); }
    break;
case 199:
#line 1289 "parse.y"
{ yyval.plot_range_type = new plot_range (yyvsp[-2].tree_expression_type, 0); }
    break;
case 200:
#line 1291 "parse.y"
{ yyval.plot_range_type = new plot_range (); }
    break;
case 201:
#line 1293 "parse.y"
{ yyval.plot_range_type = new plot_range (); }
    break;
case 202:
#line 1297 "parse.y"
{ yyval.subplot_list_type = new subplot_list (yyvsp[0].subplot_type); }
    break;
case 203:
#line 1299 "parse.y"
{
		    yyvsp[-2].subplot_list_type->append (yyvsp[0].subplot_type);
		    yyval.subplot_list_type = yyvsp[-2].subplot_list_type;
		  }
    break;
case 204:
#line 1306 "parse.y"
{ yyval.subplot_type = new subplot (yyvsp[0].tree_expression_type); }
    break;
case 205:
#line 1308 "parse.y"
{ yyval.subplot_type = yyvsp[0].subplot_type->add_data (yyvsp[-1].tree_expression_type); }
    break;
case 206:
#line 1312 "parse.y"
{
		    subplot *tmp = new subplot ();
		    yyval.subplot_type = tmp->add_clause (yyvsp[0].subplot_using_type);
		  }
    break;
case 207:
#line 1317 "parse.y"
{
		    subplot *tmp = new subplot ();
		    yyval.subplot_type = tmp->add_clause (yyvsp[0].tree_expression_type);
		  }
    break;
case 208:
#line 1322 "parse.y"
{
		    subplot *tmp = new subplot ();
		    yyval.subplot_type = tmp->add_clause (yyvsp[0].subplot_style_type);
		  }
    break;
case 209:
#line 1327 "parse.y"
{
		    subplot *tmp = new subplot ();
		    yyval.subplot_type = tmp->add_clause (yyvsp[0].subplot_axes_type);
		  }
    break;
case 210:
#line 1332 "parse.y"
{
		    if (! (yyval.subplot_type = yyvsp[-1].subplot_type->add_clause (yyvsp[0].subplot_using_type)))
		      {
			yyerror ("only one using option may be specified");
			ABORT_PARSE;
		      }
		  }
    break;
case 211:
#line 1340 "parse.y"
{
		    if (! (yyval.subplot_type = yyvsp[-1].subplot_type->add_clause (yyvsp[0].tree_expression_type)))
		      {
			yyerror ("only one title option my be specified");
			ABORT_PARSE;
		      }
		  }
    break;
case 212:
#line 1348 "parse.y"
{
		    if (! (yyval.subplot_type = yyvsp[-1].subplot_type->add_clause (yyvsp[0].subplot_style_type)))
		      {
			yyerror ("only one style option my be specified");
			ABORT_PARSE;
		      }
		  }
    break;
case 213:
#line 1356 "parse.y"
{
		    if (! (yyval.subplot_type = yyvsp[-1].subplot_type->add_clause (yyvsp[0].subplot_axes_type)))
		      {
			yyerror ("only one axes option may be specified");
			ABORT_PARSE;
		      }
		  }
    break;
case 214:
#line 1366 "parse.y"
{
		    lexer_flags.in_plot_axes = false;
		    yyval.subplot_axes_type = new subplot_axes (yyvsp[0].tok_val->text ());
		  }
    break;
case 215:
#line 1373 "parse.y"
{
		    lexer_flags.in_plot_using = false;
		    yyval.subplot_using_type = yyvsp[0].subplot_using_type;
		  }
    break;
case 216:
#line 1378 "parse.y"
{
		    lexer_flags.in_plot_using = false;
		    yyval.subplot_using_type = yyvsp[-1].subplot_using_type->set_format (yyvsp[0].tree_expression_type);
		  }
    break;
case 217:
#line 1385 "parse.y"
{
		    subplot_using *tmp = new subplot_using ();
		    yyval.subplot_using_type = tmp->add_qualifier (yyvsp[0].tree_expression_type);
		  }
    break;
case 218:
#line 1390 "parse.y"
{ yyval.subplot_using_type = yyvsp[-2].subplot_using_type->add_qualifier (yyvsp[0].tree_expression_type); }
    break;
case 219:
#line 1394 "parse.y"
{ yyval.tree_expression_type = yyvsp[0].tree_expression_type; }
    break;
case 220:
#line 1398 "parse.y"
{ yyval.subplot_style_type = new subplot_style (yyvsp[0].tok_val->text ()); }
    break;
case 221:
#line 1400 "parse.y"
{ yyval.subplot_style_type = new subplot_style (yyvsp[-1].tok_val->text (), yyvsp[0].tree_expression_type); }
    break;
case 222:
#line 1402 "parse.y"
{ yyval.subplot_style_type = new subplot_style (yyvsp[-2].tok_val->text (), yyvsp[-1].tree_expression_type, yyvsp[0].tree_expression_type); }
    break;
case 223:
#line 1410 "parse.y"
{ yyval.comment_type = octave_comment_buffer::get_comment (); }
    break;
case 224:
#line 1414 "parse.y"
{ yyerror ("parse error"); }
    break;
case 226:
#line 1419 "parse.y"
{ yyval.sep_type = ','; }
    break;
case 227:
#line 1421 "parse.y"
{ yyval.sep_type = ';'; }
    break;
case 228:
#line 1423 "parse.y"
{ yyval.sep_type = yyvsp[-1].sep_type; }
    break;
case 229:
#line 1425 "parse.y"
{ yyval.sep_type = yyvsp[-1].sep_type; }
    break;
case 230:
#line 1429 "parse.y"
{ yyval.sep_type = 0; }
    break;
case 231:
#line 1431 "parse.y"
{ yyval.sep_type = yyvsp[0].sep_type; }
    break;
case 232:
#line 1435 "parse.y"
{ yyval.sep_type = ','; }
    break;
case 233:
#line 1437 "parse.y"
{ yyval.sep_type = ';'; }
    break;
case 234:
#line 1439 "parse.y"
{ yyval.sep_type = '\n'; }
    break;
case 235:
#line 1441 "parse.y"
{ yyval.sep_type = yyvsp[-1].sep_type; }
    break;
case 236:
#line 1443 "parse.y"
{ yyval.sep_type = yyvsp[-1].sep_type; }
    break;
case 237:
#line 1445 "parse.y"
{ yyval.sep_type = yyvsp[-1].sep_type; }
    break;
case 238:
#line 1449 "parse.y"
{ yyval.sep_type = 0; }
    break;
case 239:
#line 1451 "parse.y"
{ yyval.sep_type = yyvsp[0].sep_type; }
    break;
}

#line 727 "/usr/share/bison/bison.simple"


  yyvsp -= yylen;
  yyssp -= yylen;
#if YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;
#if YYLSP_NEEDED
  *++yylsp = yyloc;
#endif

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[YYTRANSLATE (yychar)]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[YYTRANSLATE (yychar)]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx)
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
	    yyerror ("parse error; also virtual memory exhausted");
	}
      else
#endif /* defined (YYERROR_VERBOSE) */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*--------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action |
`--------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;
      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;


/*-------------------------------------------------------------------.
| yyerrdefault -- current state does not do anything special for the |
| error token.                                                       |
`-------------------------------------------------------------------*/
yyerrdefault:
#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */

  /* If its default is to accept any token, ok.  Otherwise pop it.  */
  yyn = yydefact[yystate];
  if (yyn)
    goto yydefault;
#endif


/*---------------------------------------------------------------.
| yyerrpop -- pop the current state because it cannot handle the |
| error token                                                    |
`---------------------------------------------------------------*/
yyerrpop:
  if (yyssp == yyss)
    YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#if YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "Error: state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

/*--------------.
| yyerrhandle.  |
`--------------*/
yyerrhandle:
  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

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

/*---------------------------------------------.
| yyoverflowab -- parser overflow comes here.  |
`---------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}
#line 1454 "parse.y"


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
