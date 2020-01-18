/*

Copyright (C) 2001 Cai Jianming

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
#include "ov-bool.h"
#include "ov-bool-mat.h"
#include "ov-typeinfo.h"
#include "ops.h"
#include "xdiv.h"
#include "xpow.h"

// bool matrix by bool ops.

DEFNDBINOP_FN (el_and, bool_matrix, bool, bool_array, bool, mx_el_and)
DEFNDBINOP_FN (el_or, bool_matrix, bool, bool_array, bool, mx_el_or)

DEFNDASSIGNOP_FN (assign, bool_matrix, bool, bool_array, assign)

void
install_bm_b_ops (void)
{
  INSTALL_BINOP (op_el_and, octave_bool_matrix, octave_bool, el_and);
  INSTALL_BINOP (op_el_or, octave_bool_matrix, octave_bool, el_or);

  INSTALL_ASSIGNOP (op_asn_eq, octave_bool_matrix, octave_bool, assign);
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
