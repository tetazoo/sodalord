/*

Copyright (C) 2003 John W. Eaton

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

DEFNDBINOP_FN (el_and, bool, bool_matrix, bool, bool_array, mx_el_and)
DEFNDBINOP_FN (el_or, bool, bool_matrix, bool, bool_array, mx_el_or)

void
install_b_bm_ops (void)
{
  INSTALL_BINOP (op_el_and, octave_bool, octave_bool_matrix, el_and);
  INSTALL_BINOP (op_el_or, octave_bool, octave_bool_matrix, el_or);
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
