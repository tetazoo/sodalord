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

#if !defined (octave_boolNDArray_h)
#define octave_boolNDArray_h 1

#if defined (__GNUG__) && defined (USE_PRAGMA_INTERFACE_IMPLEMENTATION)
#pragma interface
#endif

#include "ArrayN.h"
#include "CMatrix.h"

#include "mx-defs.h"
#include "mx-op-defs.h"

#include "data-conv.h"
#include "mach-info.h"

#include "boolMatrix.h"

class
boolNDArray : public ArrayN<bool>
{
public:
  
  boolNDArray (void) : ArrayN<bool> () { }

  boolNDArray (const dim_vector& dv) : ArrayN<bool> (dv) { }

  boolNDArray (const dim_vector& dv, const bool& val)
    : ArrayN<bool> (dv, val) { }
  
  boolNDArray (const boolNDArray& a) : ArrayN<bool> (a) { }

  boolNDArray (const boolMatrix& a) : ArrayN<bool> (a) { }

  boolNDArray (const Array2<bool>& a) : ArrayN<bool> (a) { }

  boolNDArray (const ArrayN<bool>& a) : ArrayN<bool> (a) { }

  boolNDArray& operator = (const boolNDArray& a)
    {
      ArrayN<bool>::operator = (a);
      return *this;
    }

  // unary operations

  boolNDArray operator ! (void) const;

  // XXX FIXME XXX -- this is not quite the right thing.

  boolNDArray all (int dim = -1) const;
  boolNDArray any (int dim = -1) const;

  boolMatrix matrix_value (void) const;

  boolNDArray squeeze (void) const { return ArrayN<bool>::squeeze (); }

  static void increment_index (Array<int>& ra_idx,
			       const dim_vector& dimensions,
			       int start_dimension = 0);

  static int compute_index (Array<int>& ra_idx,
			    const dim_vector& dimensions);

  // i/o

  // friend std::ostream& operator << (std::ostream& os, const NDArray& a);
  // friend std::istream& operator >> (std::istream& is, NDArray& a);

  static bool resize_fill_value (void) { return false; }

  //  bool all_elements_are_real (void) const;
  //  bool all_integers (double& max_val, double& min_val) const;

private:

  boolNDArray (bool *d, dim_vector& dv) : ArrayN<bool> (d, dv) { }
};

NDND_BOOL_OP_DECLS (boolNDArray, boolNDArray)
NDND_CMP_OP_DECLS (boolNDArray, boolNDArray)

NDS_BOOL_OP_DECLS (boolNDArray, bool)
NDS_CMP_OP_DECLS (boolNDArray, bool)

SND_BOOL_OP_DECLS (bool, boolNDArray)
SND_CMP_OP_DECLS (bool, boolNDArray)

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
