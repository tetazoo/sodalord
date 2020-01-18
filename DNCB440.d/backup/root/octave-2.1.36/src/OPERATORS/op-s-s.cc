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

#include "gripes.h"
#include "ov.h"
#include "ov-scalar.h"
#include "ov-re-mat.h"
#include "ov-typeinfo.h"
#include "ops.h"
#include "xdiv.h"
#include "xpow.h"

// scalar unary ops.

DEFUNOP_OP (not, scalar, !)
DEFUNOP_OP (uminus, scalar, -)
DEFUNOP_OP (transpose, scalar, /* no-op */)
DEFUNOP_OP (hermitian, scalar, /* no-op */)

DEFNCUNOP_METHOD (incr, scalar, increment)
DEFNCUNOP_METHOD (decr, scalar, decrement)

// scalar by scalar ops.

DEFBINOP_OP (add, scalar, scalar, +)
DEFBINOP_OP (sub, scalar, scalar, -)
DEFBINOP_OP (mul, scalar, scalar, *)

DEFBINOP (div, scalar, scalar)
{
  CAST_BINOP_ARGS (const octave_scalar&, const octave_scalar&);

  double d = v2.double_value ();

  if (d == 0.0)
    gripe_divide_by_zero ();

  return octave_value (v1.double_value () / d);
}

DEFBINOP_FN (pow, scalar, scalar, xpow)

DEFBINOP (ldiv, scalar, scalar)
{
  CAST_BINOP_ARGS (const octave_scalar&, const octave_scalar&);

  double d = v1.double_value ();

  if (d == 0.0)
    gripe_divide_by_zero ();

  return octave_value (v2.double_value () / d);
}

DEFBINOP_OP (lt, scalar, scalar, <)
DEFBINOP_OP (le, scalar, scalar, <=)
DEFBINOP_OP (eq, scalar, scalar, ==)
DEFBINOP_OP (ge, scalar, scalar, >=)
DEFBINOP_OP (gt, scalar, scalar, >)
DEFBINOP_OP (ne, scalar, scalar, !=)

DEFBINOP_OP (el_mul, scalar, scalar, *)

DEFBINOP (el_div, scalar, scalar)
{
  CAST_BINOP_ARGS (const octave_scalar&, const octave_scalar&);

  double d = v2.double_value ();

  if (d == 0.0)
    gripe_divide_by_zero ();

  return octave_value (v1.double_value () / d);
}

DEFBINOP_FN (el_pow, scalar, scalar, xpow)

DEFBINOP (el_ldiv, scalar, scalar)
{
  CAST_BINOP_ARGS (const octave_scalar&, const octave_scalar&);

  double d = v1.double_value ();

  if (d == 0.0)
    gripe_divide_by_zero ();

  return octave_value (v2.double_value () / d);
}

DEFBINOP_OP (el_and, scalar, scalar, &&)
DEFBINOP_OP (el_or, scalar, scalar, ||)

DEFCONV (matrix_conv, scalar, matrix)
{
  CAST_CONV_ARG (const octave_scalar&);

  return new octave_matrix (v.matrix_value ());
}

void
install_s_s_ops (void)
{
  INSTALL_UNOP (op_not, octave_scalar, not);
  INSTALL_UNOP (op_uminus, octave_scalar, uminus);
  INSTALL_UNOP (op_transpose, octave_scalar, transpose);
  INSTALL_UNOP (op_hermitian, octave_scalar, hermitian);

  INSTALL_NCUNOP (op_incr, octave_scalar, incr);
  INSTALL_NCUNOP (op_decr, octave_scalar, decr);

  INSTALL_BINOP (op_add, octave_scalar, octave_scalar, add);
  INSTALL_BINOP (op_sub, octave_scalar, octave_scalar, sub);
  INSTALL_BINOP (op_mul, octave_scalar, octave_scalar, mul);
  INSTALL_BINOP (op_div, octave_scalar, octave_scalar, div);
  INSTALL_BINOP (op_pow, octave_scalar, octave_scalar, pow);
  INSTALL_BINOP (op_ldiv, octave_scalar, octave_scalar, ldiv);
  INSTALL_BINOP (op_lt, octave_scalar, octave_scalar, lt);
  INSTALL_BINOP (op_le, octave_scalar, octave_scalar, le);
  INSTALL_BINOP (op_eq, octave_scalar, octave_scalar, eq);
  INSTALL_BINOP (op_ge, octave_scalar, octave_scalar, ge);
  INSTALL_BINOP (op_gt, octave_scalar, octave_scalar, gt);
  INSTALL_BINOP (op_ne, octave_scalar, octave_scalar, ne);
  INSTALL_BINOP (op_el_mul, octave_scalar, octave_scalar, el_mul);
  INSTALL_BINOP (op_el_div, octave_scalar, octave_scalar, el_div);
  INSTALL_BINOP (op_el_pow, octave_scalar, octave_scalar, el_pow);
  INSTALL_BINOP (op_el_ldiv, octave_scalar, octave_scalar, el_ldiv);
  INSTALL_BINOP (op_el_and, octave_scalar, octave_scalar, el_and);
  INSTALL_BINOP (op_el_or, octave_scalar, octave_scalar, el_or);

  INSTALL_ASSIGNCONV (octave_scalar, octave_scalar, octave_matrix);

  INSTALL_WIDENOP (octave_scalar, octave_matrix, matrix_conv);
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
