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

#if defined (__GNUG__) && defined (USE_PRAGMA_INTERFACE_IMPLEMENTATION)
#pragma implementation
#endif

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "gripes.h"
#include "oct-obj.h"
#include "ov.h"
#include "ov-cx-mat.h"
#include "ov-typeinfo.h"
#include "ops.h"
#include "xdiv.h"
#include "xpow.h"

// unary complex matrix ops.

DEFNDUNOP_OP (not, complex_matrix, complex_array, !)
DEFNDUNOP_OP (uminus, complex_matrix, complex_array, -)

DEFUNOP (transpose, complex_matrix)
{
  CAST_UNOP_ARG (const octave_complex_matrix&);

  if (v.ndims () > 2)
    {
      error ("transpose not defined for N-d objects");
      return octave_value ();
    }
  else
    return octave_value (v.complex_matrix_value().transpose ());
}

DEFUNOP (hermitian, complex_matrix)
{
  CAST_UNOP_ARG (const octave_complex_matrix&);

  if (v.ndims () > 2)
    {
      error ("complex-conjugate transpose not defined for N-d objects");
      return octave_value ();
    }
  else
    return octave_value (v.complex_matrix_value().hermitian ());
}

DEFNCUNOP_METHOD (incr, complex_matrix, increment)
DEFNCUNOP_METHOD (decr, complex_matrix, decrement)

// complex matrix by complex matrix ops.

DEFNDBINOP_OP (add, complex_matrix, complex_matrix, complex_array, complex_array, +)
DEFNDBINOP_OP (sub, complex_matrix, complex_matrix, complex_array, complex_array, -)

DEFBINOP_OP (mul, complex_matrix, complex_matrix, *)
DEFBINOP_FN (div, complex_matrix, complex_matrix, xdiv)

DEFBINOPX (pow, complex_matrix, complex_matrix)
{
  error ("can't do A ^ B for A and B both matrices");
  return octave_value ();
}

DEFBINOP_FN (ldiv, complex_matrix, complex_matrix, xleftdiv)

DEFNDBINOP_FN (lt, complex_matrix, complex_matrix, complex_array, complex_array, mx_el_lt)
DEFNDBINOP_FN (le, complex_matrix, complex_matrix, complex_array, complex_array, mx_el_le)
DEFNDBINOP_FN (eq, complex_matrix, complex_matrix, complex_array, complex_array, mx_el_eq)
DEFNDBINOP_FN (ge, complex_matrix, complex_matrix, complex_array, complex_array, mx_el_ge)
DEFNDBINOP_FN (gt, complex_matrix, complex_matrix, complex_array, complex_array, mx_el_gt)
DEFNDBINOP_FN (ne, complex_matrix, complex_matrix, complex_array, complex_array, mx_el_ne)

DEFNDBINOP_FN (el_mul, complex_matrix, complex_matrix, complex_array, complex_array, product)
DEFNDBINOP_FN (el_div, complex_matrix, complex_matrix, complex_array, complex_array, quotient)
DEFNDBINOP_FN (el_pow, complex_matrix, complex_matrix, complex_array, complex_array, elem_xpow)

DEFBINOP (el_ldiv, complex_matrix, complex_matrix)
{
  CAST_BINOP_ARGS (const octave_complex_matrix&, const octave_complex_matrix&);

  return octave_value (quotient (v2.complex_array_value (), v1.complex_array_value ()));
}

DEFNDBINOP_FN (el_and, complex_matrix, complex_matrix, complex_array, complex_array, mx_el_and)
DEFNDBINOP_FN (el_or,  complex_matrix, complex_matrix, complex_array, complex_array, mx_el_or)

DEFNDASSIGNOP_FN (assign, complex_matrix, complex_matrix, complex_array, assign)

void
install_cm_cm_ops (void)
{
  INSTALL_UNOP (op_not, octave_complex_matrix, not);
  INSTALL_UNOP (op_uminus, octave_complex_matrix, uminus);
  INSTALL_UNOP (op_transpose, octave_complex_matrix, transpose);
  INSTALL_UNOP (op_hermitian, octave_complex_matrix, hermitian);

  INSTALL_NCUNOP (op_incr, octave_complex_matrix, incr);
  INSTALL_NCUNOP (op_decr, octave_complex_matrix, decr);

  INSTALL_BINOP (op_add, octave_complex_matrix, octave_complex_matrix, add);
  INSTALL_BINOP (op_sub, octave_complex_matrix, octave_complex_matrix, sub);
  INSTALL_BINOP (op_mul, octave_complex_matrix, octave_complex_matrix, mul);
  INSTALL_BINOP (op_div, octave_complex_matrix, octave_complex_matrix, div);
  INSTALL_BINOP (op_pow, octave_complex_matrix, octave_complex_matrix, pow);
  INSTALL_BINOP (op_ldiv, octave_complex_matrix, octave_complex_matrix, ldiv);
  INSTALL_BINOP (op_lt, octave_complex_matrix, octave_complex_matrix, lt);
  INSTALL_BINOP (op_le, octave_complex_matrix, octave_complex_matrix, le);
  INSTALL_BINOP (op_eq, octave_complex_matrix, octave_complex_matrix, eq);
  INSTALL_BINOP (op_ge, octave_complex_matrix, octave_complex_matrix, ge);
  INSTALL_BINOP (op_gt, octave_complex_matrix, octave_complex_matrix, gt);
  INSTALL_BINOP (op_ne, octave_complex_matrix, octave_complex_matrix, ne);
  INSTALL_BINOP (op_el_mul, octave_complex_matrix, octave_complex_matrix, el_mul);
  INSTALL_BINOP (op_el_div, octave_complex_matrix, octave_complex_matrix, el_div);
  INSTALL_BINOP (op_el_pow, octave_complex_matrix, octave_complex_matrix, el_pow);
  INSTALL_BINOP (op_el_ldiv, octave_complex_matrix, octave_complex_matrix, el_ldiv);
  INSTALL_BINOP (op_el_and, octave_complex_matrix, octave_complex_matrix, el_and);
  INSTALL_BINOP (op_el_or, octave_complex_matrix, octave_complex_matrix, el_or);

  INSTALL_ASSIGNOP (op_asn_eq, octave_complex_matrix, octave_complex_matrix, assign);
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
