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

#include "mx-cm-m.h"
#include "mx-m-cm.h"

#include "gripes.h"
#include "ov.h"
#include "ov-cx-mat.h"
#include "ov-re-mat.h"
#include "ov-typeinfo.h"
#include "ops.h"
#include "xdiv.h"
#include "xpow.h"

// complex matrix by matrix ops.

DEFBINOP_OP (add, complex_matrix, matrix, +)
DEFBINOP_OP (sub, complex_matrix, matrix, -)
DEFBINOP_OP (mul, complex_matrix, matrix, *)
DEFBINOP_FN (div, complex_matrix, matrix, xdiv)

DEFBINOPX (pow, complex_matrix, matrix)
{
  error ("can't do A ^ B for A and B both matrices");
  return octave_value ();
}

DEFBINOP_FN (ldiv, complex_matrix, matrix, xleftdiv)

DEFBINOP_FN (lt, complex_matrix, matrix, mx_el_lt)
DEFBINOP_FN (le, complex_matrix, matrix, mx_el_le)
DEFBINOP_FN (eq, complex_matrix, matrix, mx_el_eq)
DEFBINOP_FN (ge, complex_matrix, matrix, mx_el_ge)
DEFBINOP_FN (gt, complex_matrix, matrix, mx_el_gt)
DEFBINOP_FN (ne, complex_matrix, matrix, mx_el_ne)

DEFBINOP_FN (el_mul, complex_matrix, matrix, product)
DEFBINOP_FN (el_div, complex_matrix, matrix, quotient)
DEFBINOP_FN (el_pow, complex_matrix, matrix, elem_xpow)

DEFBINOP (el_ldiv, complex_matrix, matrix)
{
  CAST_BINOP_ARGS (const octave_complex_matrix&, const octave_matrix&);

  return quotient (v2.matrix_value (), v1.complex_matrix_value ());
}

DEFBINOP_FN (el_and, complex_matrix, matrix, mx_el_and)
DEFBINOP_FN (el_or, complex_matrix, matrix, mx_el_or)

DEFASSIGNOP_FN (assign, complex_matrix, matrix, assign)

void
install_cm_m_ops (void)
{
  INSTALL_BINOP (op_add, octave_complex_matrix, octave_matrix, add);
  INSTALL_BINOP (op_sub, octave_complex_matrix, octave_matrix, sub);
  INSTALL_BINOP (op_mul, octave_complex_matrix, octave_matrix, mul);
  INSTALL_BINOP (op_div, octave_complex_matrix, octave_matrix, div);
  INSTALL_BINOP (op_pow, octave_complex_matrix, octave_matrix, pow);
  INSTALL_BINOP (op_ldiv, octave_complex_matrix, octave_matrix, ldiv);
  INSTALL_BINOP (op_lt, octave_complex_matrix, octave_matrix, lt);
  INSTALL_BINOP (op_le, octave_complex_matrix, octave_matrix, le);
  INSTALL_BINOP (op_eq, octave_complex_matrix, octave_matrix, eq);
  INSTALL_BINOP (op_ge, octave_complex_matrix, octave_matrix, ge);
  INSTALL_BINOP (op_gt, octave_complex_matrix, octave_matrix, gt);
  INSTALL_BINOP (op_ne, octave_complex_matrix, octave_matrix, ne);
  INSTALL_BINOP (op_el_mul, octave_complex_matrix, octave_matrix, el_mul);
  INSTALL_BINOP (op_el_div, octave_complex_matrix, octave_matrix, el_div);
  INSTALL_BINOP (op_el_pow, octave_complex_matrix, octave_matrix, el_pow);
  INSTALL_BINOP (op_el_ldiv, octave_complex_matrix, octave_matrix, el_ldiv);
  INSTALL_BINOP (op_el_and, octave_complex_matrix, octave_matrix, el_and);
  INSTALL_BINOP (op_el_or, octave_complex_matrix, octave_matrix, el_or);

  INSTALL_ASSIGNOP (op_asn_eq, octave_complex_matrix, octave_matrix, assign);
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
