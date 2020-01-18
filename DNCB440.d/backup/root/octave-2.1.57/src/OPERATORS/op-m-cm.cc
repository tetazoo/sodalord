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

#include "mx-m-cm.h"
#include "mx-cm-m.h"
#include "mx-nda-cnda.h"
#include "mx-cnda-nda.h"

#include "gripes.h"
#include "oct-obj.h"
#include "ov.h"
#include "ov-re-mat.h"
#include "ov-cx-mat.h"
#include "ov-typeinfo.h"
#include "ops.h"
#include "xdiv.h"
#include "xpow.h"

// matrix by complex matrix ops.

DEFNDBINOP_OP (add, matrix, complex_matrix, array, complex_array, +)
DEFNDBINOP_OP (sub, matrix, complex_matrix, array, complex_array, -)

DEFBINOP_OP (mul, matrix, complex_matrix, *)
DEFBINOP_FN (div, matrix, complex_matrix, xdiv)

DEFBINOPX (pow, matrix, complex_matrix)
{
  error ("can't do A ^ B for A and B both matrices");
  return octave_value ();
}

DEFBINOP_FN (ldiv, matrix, complex_matrix, xleftdiv)

DEFNDBINOP_FN (lt, matrix, complex_matrix, array, complex_array, mx_el_lt)
DEFNDBINOP_FN (le, matrix, complex_matrix, array, complex_array, mx_el_le)
DEFNDBINOP_FN (eq, matrix, complex_matrix, array, complex_array, mx_el_eq)
DEFNDBINOP_FN (ge, matrix, complex_matrix, array, complex_array, mx_el_ge)
DEFNDBINOP_FN (gt, matrix, complex_matrix, array, complex_array, mx_el_gt)
DEFNDBINOP_FN (ne, matrix, complex_matrix, array, complex_array, mx_el_ne)

DEFNDBINOP_FN (el_mul, matrix, complex_matrix, array, complex_array, product)
DEFNDBINOP_FN (el_div, matrix, complex_matrix, array, complex_array, quotient)
DEFNDBINOP_FN (el_pow, matrix, complex_matrix, array, complex_array, elem_xpow)

DEFBINOP (el_ldiv, matrix, complex_matrix)
{
  CAST_BINOP_ARGS (const octave_matrix&, const octave_complex_matrix&);

  return quotient (v2.complex_array_value (), v1.array_value ());
}

DEFNDBINOP_FN (el_and, matrix, complex_matrix, array, complex_array, mx_el_and)
DEFNDBINOP_FN (el_or,  matrix, complex_matrix, array, complex_array, mx_el_or)

DEFCONV (complex_matrix_conv, matrix, complex_matrix)
{
  CAST_CONV_ARG (const octave_matrix&);

  return new octave_complex_matrix (ComplexNDArray (v.array_value ()));
}

void
install_m_cm_ops (void)
{
  INSTALL_BINOP (op_add, octave_matrix, octave_complex_matrix, add);
  INSTALL_BINOP (op_sub, octave_matrix, octave_complex_matrix, sub);
  INSTALL_BINOP (op_mul, octave_matrix, octave_complex_matrix, mul);
  INSTALL_BINOP (op_div, octave_matrix, octave_complex_matrix, div);
  INSTALL_BINOP (op_pow, octave_matrix, octave_complex_matrix, pow);
  INSTALL_BINOP (op_ldiv, octave_matrix, octave_complex_matrix, ldiv);
  INSTALL_BINOP (op_lt, octave_matrix, octave_complex_matrix, lt);
  INSTALL_BINOP (op_le, octave_matrix, octave_complex_matrix, le);
  INSTALL_BINOP (op_eq, octave_matrix, octave_complex_matrix, eq);
  INSTALL_BINOP (op_ge, octave_matrix, octave_complex_matrix, ge);
  INSTALL_BINOP (op_gt, octave_matrix, octave_complex_matrix, gt);
  INSTALL_BINOP (op_ne, octave_matrix, octave_complex_matrix, ne);
  INSTALL_BINOP (op_el_mul, octave_matrix, octave_complex_matrix, el_mul);
  INSTALL_BINOP (op_el_div, octave_matrix, octave_complex_matrix, el_div);
  INSTALL_BINOP (op_el_pow, octave_matrix, octave_complex_matrix, el_pow);
  INSTALL_BINOP (op_el_ldiv, octave_matrix, octave_complex_matrix, el_ldiv);
  INSTALL_BINOP (op_el_and, octave_matrix, octave_complex_matrix, el_and);
  INSTALL_BINOP (op_el_or, octave_matrix, octave_complex_matrix, el_or);

  INSTALL_ASSIGNCONV (octave_matrix, octave_complex_matrix, octave_complex_matrix);

  INSTALL_WIDENOP (octave_matrix, octave_complex_matrix, complex_matrix_conv);
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
