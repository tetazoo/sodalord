#ifndef BISON_Y_TAB_H
# define BISON_Y_TAB_H

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


extern YYSTYPE yylval;

#endif /* not BISON_Y_TAB_H */
