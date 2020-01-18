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

#if !defined (octave_Matrix_int_h)
#define octave_Matrix_int_h 1

#if defined (__GNUG__) && defined (USE_PRAGMA_INTERFACE_IMPLEMENTATION)
#pragma interface
#endif

#include "MArray2.h"
#include "MDiagArray2.h"

#include "mx-defs.h"
#include "mx-op-defs.h"

#include "data-conv.h"
#include "mach-info.h"

class
Matrix : public MArray2<double>
{
public:

  typedef void (*solve_singularity_handler) (double rcond);

  Matrix (void) : MArray2<double> () { }

  Matrix (int r, int c) : MArray2<double> (r, c) { }

  Matrix (int r, int c, double val) : MArray2<double> (r, c, val) { }

  Matrix (const Matrix& a) : MArray2<double> (a) { }

  Matrix (const MArray2<double>& a) : MArray2<double> (a) { }

  explicit Matrix (const RowVector& rv);

  explicit Matrix (const ColumnVector& cv);

  explicit Matrix (const DiagMatrix& a);

  explicit Matrix (const boolMatrix& a);

  explicit Matrix (const charMatrix& a);

  Matrix& operator = (const Matrix& a)
    {
      MArray2<double>::operator = (a);
      return *this;
    }

  bool operator == (const Matrix& a) const;
  bool operator != (const Matrix& a) const;

  bool is_symmetric (void) const;

  // destructive insert/delete/reorder operations

  Matrix& insert (const Matrix& a, int r, int c);
  Matrix& insert (const RowVector& a, int r, int c);
  Matrix& insert (const ColumnVector& a, int r, int c);
  Matrix& insert (const DiagMatrix& a, int r, int c);

  Matrix& fill (double val);
  Matrix& fill (double val, int r1, int c1, int r2, int c2);

  Matrix append (const Matrix& a) const;
  Matrix append (const RowVector& a) const;
  Matrix append (const ColumnVector& a) const;
  Matrix append (const DiagMatrix& a) const;

  Matrix stack (const Matrix& a) const;
  Matrix stack (const RowVector& a) const;
  Matrix stack (const ColumnVector& a) const;
  Matrix stack (const DiagMatrix& a) const;

  friend Matrix real (const ComplexMatrix& a);
  friend Matrix imag (const ComplexMatrix& a);

  Matrix transpose (void) const { return MArray2<double>::transpose (); }

  // resize is the destructive equivalent for this one

  Matrix extract (int r1, int c1, int r2, int c2) const;

  Matrix extract_n (int r1, int c1, int nr, int nc) const;

  // extract row or column i.

  RowVector row (int i) const;
  RowVector row (char *s) const;

  ColumnVector column (int i) const;
  ColumnVector column (char *s) const;

  Matrix inverse (void) const;
  Matrix inverse (int& info) const;
  Matrix inverse (int& info, double& rcond, int force = 0, 
		  int calc_cond = 1) const;

  Matrix pseudo_inverse (double tol = 0.0) const;

  ComplexMatrix fourier (void) const;
  ComplexMatrix ifourier (void) const;

  ComplexMatrix fourier2d (void) const;
  ComplexMatrix ifourier2d (void) const;

  DET determinant (void) const;
  DET determinant (int& info) const;
  DET determinant (int& info, double& rcond, int calc_cond = 1) const;

  Matrix solve (const Matrix& b) const;
  Matrix solve (const Matrix& b, int& info) const;
  Matrix solve (const Matrix& b, int& info, double& rcond) const;
  Matrix solve (const Matrix& b, int& info, double& rcond,
		solve_singularity_handler sing_handler) const;

  ComplexMatrix solve (const ComplexMatrix& b) const;
  ComplexMatrix solve (const ComplexMatrix& b, int& info) const;
  ComplexMatrix solve (const ComplexMatrix& b, int& info, double& rcond) const;
  ComplexMatrix solve (const ComplexMatrix& b, int& info, double& rcond,
		       solve_singularity_handler sing_handler) const;

  ColumnVector solve (const ColumnVector& b) const;
  ColumnVector solve (const ColumnVector& b, int& info) const;
  ColumnVector solve (const ColumnVector& b, int& info, double& rcond) const;
  ColumnVector solve (const ColumnVector& b, int& info, double& rcond,
		      solve_singularity_handler sing_handler) const;

  ComplexColumnVector solve (const ComplexColumnVector& b) const;
  ComplexColumnVector solve (const ComplexColumnVector& b, int& info) const;
  ComplexColumnVector solve (const ComplexColumnVector& b, int& info,
			     double& rcond) const;
  ComplexColumnVector solve (const ComplexColumnVector& b, int& info,
			     double& rcond,
			     solve_singularity_handler sing_handler) const;

  Matrix lssolve (const Matrix& b) const;
  Matrix lssolve (const Matrix& b, int& info) const;
  Matrix lssolve (const Matrix& b, int& info, int& rank) const;

  ComplexMatrix lssolve (const ComplexMatrix& b) const;
  ComplexMatrix lssolve (const ComplexMatrix& b, int& info) const;
  ComplexMatrix lssolve (const ComplexMatrix& b, int& info,
			 int& rank) const;

  ColumnVector lssolve (const ColumnVector& b) const;
  ColumnVector lssolve (const ColumnVector& b, int& info) const;
  ColumnVector lssolve (const ColumnVector& b, int& info, int& rank) const;

  ComplexColumnVector lssolve (const ComplexColumnVector& b) const;
  ComplexColumnVector lssolve (const ComplexColumnVector& b, int& info) const;
  ComplexColumnVector lssolve (const ComplexColumnVector& b, int& info,
			       int& rank) const;

  Matrix expm (void) const;

  Matrix& operator += (const DiagMatrix& a);
  Matrix& operator -= (const DiagMatrix& a);

  // unary operations

  boolMatrix operator ! (void) const;

  // column vector by row vector -> matrix operations

  friend Matrix operator * (const ColumnVector& a, const RowVector& b);

  // other operations

  Matrix map (d_d_Mapper f) const;
  boolMatrix map (b_d_Mapper f) const;

  Matrix& apply (d_d_Mapper f);

  bool any_element_is_negative (bool = false) const;
  bool any_element_is_inf_or_nan (void) const;
  bool all_elements_are_int_or_inf_or_nan (void) const;
  bool all_integers (double& max_val, double& min_val) const;
  bool too_large_for_float (void) const;
 
  boolMatrix all (int dim = -1) const;
  boolMatrix any (int dim = -1) const;

  Matrix cumprod (int dim = -1) const;
  Matrix cumsum (int dim = -1) const;
  Matrix prod (int dim = -1) const;
  Matrix sum (int dim = -1) const;
  Matrix sumsq (int dim = -1) const;
  Matrix abs (void) const;

  ColumnVector diag (void) const;
  ColumnVector diag (int k) const;

  ColumnVector row_min (void) const;
  ColumnVector row_max (void) const;

  ColumnVector row_min (Array<int>& index) const;
  ColumnVector row_max (Array<int>& index) const;

  RowVector column_min (void) const;
  RowVector column_max (void) const;

  RowVector column_min (Array<int>& index) const;
  RowVector column_max (Array<int>& index) const;

  // i/o

  friend std::ostream& operator << (std::ostream& os, const Matrix& a);
  friend std::istream& operator >> (std::istream& is, Matrix& a);

  int read (std::istream& is, int nr, int nc, oct_data_conv::data_type dt,
	    int skip, oct_mach_info::float_format flt_fmt);

  int write (std::ostream& os, oct_data_conv::data_type dt, int skip,
	     oct_mach_info::float_format flt_fmt);

  static double resize_fill_value (void) { return 0; }

private:

  Matrix (double *d, int r, int c) : MArray2<double> (d, r, c) { }
};

extern Matrix Givens (double, double);

extern Matrix Sylvester (const Matrix&, const Matrix&, const Matrix&);

extern Matrix operator * (const Matrix& a, const Matrix& b);

extern Matrix min (double d, const Matrix& m);
extern Matrix min (const Matrix& m, double d);
extern Matrix min (const Matrix& a, const Matrix& b);

extern Matrix max (double d, const Matrix& m);
extern Matrix max (const Matrix& m, double d);
extern Matrix max (const Matrix& a, const Matrix& b);

MS_CMP_OP_DECLS (Matrix, double)
MS_BOOL_OP_DECLS (Matrix, double)

SM_CMP_OP_DECLS (double, Matrix)
SM_BOOL_OP_DECLS (double, Matrix)

MM_CMP_OP_DECLS (Matrix, Matrix)
MM_BOOL_OP_DECLS (Matrix, Matrix)

MARRAY_FORWARD_DEFS (MArray2, Matrix, double)

template <class T>
void read_int (std::istream& is, bool swap_bytes, T& val);

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
