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

#if !defined (octave_ops_h)
#define octave_ops_h 1

extern void install_ops (void);

#define INSTALL_UNOP(op, t, f) \
  octave_value_typeinfo::register_unary_op \
    (octave_value::op, t::static_type_id (), oct_unop_ ## f);

#define INSTALL_NCUNOP(op, t, f) \
  octave_value_typeinfo::register_non_const_unary_op \
    (octave_value::op, t::static_type_id (), oct_unop_ ## f);

#define INSTALL_BINOP(op, t1, t2, f) \
  octave_value_typeinfo::register_binary_op \
    (octave_value::op, t1::static_type_id (), t2::static_type_id (), \
     oct_binop_ ## f);

#define INSTALL_ASSIGNOP(op, t1, t2, f) \
  octave_value_typeinfo::register_assign_op \
    (octave_value::op, t1::static_type_id (), t2::static_type_id (), \
     oct_assignop_ ## f);

#define INSTALL_ASSIGNANYOP(op, t1, f) \
  octave_value_typeinfo::register_assignany_op \
    (octave_value::op, t1::static_type_id (), oct_assignop_ ## f);

#define INSTALL_ASSIGNCONV(t1, t2, tr) \
  octave_value_typeinfo::register_pref_assign_conv \
    (t1::static_type_id (), t2::static_type_id (), tr::static_type_id ());

#define INSTALL_WIDENOP(t1, t2, f) \
  octave_value_typeinfo::register_widening_op \
    (t1::static_type_id (), t2::static_type_id (), oct_conv_ ## f);

#define BOOL_OP1(xt, xn, get_x, yt, yn, get_y) \
  xt xn = get_x; \
  yt yn = get_y;

#define BOOL_OP2(x) \
  int nr = x.rows (); \
  int nc = x.columns ();

#define BOOL_OP3(test) \
  boolMatrix retval (nr, nc); \
  for (int j = 0; j < nc; j++) \
    for (int i = 0; i < nr; i++) \
      retval (i, j) = test; \
  return retval;

#define SC_MX_BOOL_OP(st, sn, get_s, mt, mn, get_m, test, empty_result) \
  do \
    { \
      BOOL_OP1 (st, sn, get_s, mt, mn, get_m) \
      BOOL_OP2 (mn) \
      if (nr == 0 || nc == 0) \
        return empty_result; \
      BOOL_OP3 (test) \
    } \
  while (0)

#define MX_SC_BOOL_OP(mt, mn, get_m, st, sn, get_s, test, empty_result) \
  do \
    { \
      BOOL_OP1 (mt, mn, get_m, st, sn, get_s) \
      BOOL_OP2 (mn) \
      if (nr == 0 || nc == 0) \
        return empty_result; \
      BOOL_OP3 (test) \
    } \
  while (0)

#define MX_MX_BOOL_OP(m1t, m1n, get_m1, m2t, m2n, get_m2, test, op, \
		      one_empty_result, two_empty_result) \
  do \
    { \
      BOOL_OP1 (m1t, m1n, get_m1, m2t, m2n, get_m2) \
      int m1_nr = m1n.rows (); \
      int m1_nc = m1n.cols (); \
      int m2_nr = m2n.rows (); \
      int m2_nc = m2n.cols (); \
      if (m1_nr == m2_nr && m1_nc == m2_nc) \
	{ \
	  if (m1_nr == 0 && m1_nc == 0) \
	    return two_empty_result; \
	  else \
	    { \
	      BOOL_OP2 (m1n) \
	      BOOL_OP3 (test) \
	    } \
	} \
      else \
	{ \
	  if ((m1_nr == 0 && m1_nc == 0) || (m2_nr == 0 && m2_nc == 0)) \
	    return one_empty_result; \
	  else \
	    { \
	      gripe_nonconformant ("operator " op, m1_nr, m1_nc, \
				   m2_nr, m2_nc); \
	      return boolMatrix (); \
	    } \
	} \
    } \
  while (0)

#define CAST_UNOP_ARG(t) \
  t v = DYNAMIC_CAST (t, a);

#define CAST_BINOP_ARGS(t1, t2) \
  t1 v1 = DYNAMIC_CAST (t1, a1); \
  t2 v2 = DYNAMIC_CAST (t2, a2);

#define CAST_CONV_ARG(t) \
  t v = DYNAMIC_CAST (t, a);

#define ASSIGNOPDECL(name) \
  static octave_value \
  oct_assignop_ ## name (octave_value& a1, \
			 const octave_value_list& idx, \
			 const octave_value& a2)

#define DEFASSIGNOP(name, t1, t2) \
  ASSIGNOPDECL (name)

#define DEFASSIGNOP_FN(name, t1, t2, f) \
  ASSIGNOPDECL (name) \
  { \
    CAST_BINOP_ARGS (octave_ ## t1&, const octave_ ## t2&); \
 \
    v1.f (idx, v2.t1 ## _value ()); \
    return octave_value (); \
  }

#define DEFASSIGNANYOP_FN(name, t1, f) \
  ASSIGNOPDECL (name) \
  { \
    octave_ ## t1& v1 = DYNAMIC_CAST (octave_ ## t1&, a1); \
 \
    v1.f (idx, a2); \
    return octave_value (); \
  }

#define CONVDECL(name) \
  static octave_value * \
  oct_conv_ ## name (const octave_value& a)

#define CONVDECLX(name) \
  static octave_value * \
  oct_conv_ ## name (const octave_value&)

#define DEFCONV(name, from, to) \
  CONVDECL (name)

#define UNOPDECL(name, a) \
  static octave_value \
  oct_unop_ ## name (const octave_value& a)

#define DEFUNOPX(name, t) \
  UNOPDECL (name, , )

#define DEFUNOP(name, t) \
  UNOPDECL (name, a)

#define DEFUNOP_OP(name, t, op) \
  UNOPDECL (name, a) \
  { \
    CAST_UNOP_ARG (const octave_ ## t&); \
    return octave_value (op v.t ## _value ()); \
  }

// XXX FIXME XXX -- in some cases, the constructor isn't necessary.

#define DEFUNOP_FN(name, t, f) \
  UNOPDECL (name, a) \
  { \
    CAST_UNOP_ARG (const octave_ ## t&); \
    return octave_value (f (v.t ## _value ())); \
  }

#define DEFNCUNOP_METHOD(name, t, method) \
  static void \
  oct_unop_ ## name (octave_value& a) \
  { \
    CAST_UNOP_ARG (octave_ ## t&); \
    v.method (); \
  }

#define BINOPDECL(name, a1, a2) \
  static octave_value \
  oct_binop_ ## name (const octave_value& a1, const octave_value& a2)

#define DEFBINOPX(name, t1, t2) \
  BINOPDECL (name, , )

#define DEFBINOP(name, t1, t2) \
  BINOPDECL (name, a1, a2)

#define DEFBINOP_OP(name, t1, t2, op) \
  BINOPDECL (name, a1, a2) \
  { \
    CAST_BINOP_ARGS (const octave_ ## t1&, const octave_ ## t2&); \
    return octave_value \
      (v1.t1 ## _value () op v2.t2 ## _value ()); \
  }

// XXX FIXME XXX -- in some cases, the constructor isn't necessary.

#define DEFBINOP_FN(name, t1, t2, f) \
  BINOPDECL (name, a1, a2) \
  { \
    CAST_BINOP_ARGS (const octave_ ## t1&, const octave_ ## t2&); \
    return octave_value (f (v1.t1 ## _value (), v2.t2 ## _value ())); \
  }

#define BINOP_NONCONFORMANT(msg) \
  gripe_nonconformant (msg, \
		       a1.rows (), a1.columns (), \
		       a2.rows (), a2.columns ()); \
  return octave_value ()

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
