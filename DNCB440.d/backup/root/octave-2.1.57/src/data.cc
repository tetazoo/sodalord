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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <cfloat>
#include <cmath>

#include <string>

#include "lo-ieee.h"
#include "str-vec.h"
#include "quit.h"

#include "defun.h"
#include "error.h"
#include "gripes.h"
#include "ov.h"
#include "variables.h"
#include "oct-obj.h"
#include "utils.h"
#include "Cell.h"
#include "oct-map.h"

#define ANY_ALL(FCN) \
 \
  octave_value retval; \
 \
  int nargin = args.length (); \
 \
  if (nargin == 1 || nargin == 2) \
    { \
      int dim = (nargin == 1 ? -1 : args(1).int_value (true) - 1); \
 \
      if (! error_state) \
        { \
          if (dim >= -1) \
	    retval = args(0).FCN (dim); \
          else \
	    error (#FCN ": invalid dimension argument = %d", dim + 1); \
        } \
      else \
        error (#FCN ": expecting dimension argument to be an integer"); \
    } \
  else \
    print_usage (#FCN); \
 \
  return retval

DEFUN (all, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} all (@var{x}, @var{dim})\n\
The function @code{all} behaves like the function @code{any}, except\n\
that it returns true only if all the elements of a vector, or all the\n\
elements along dimension @var{dim} of a matrix, are nonzero.\n\
@end deftypefn")
{
  ANY_ALL (all);
}

DEFUN (any, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} any (@var{x}, @var{dim})\n\
For a vector argument, return 1 if any element of the vector is\n\
nonzero.\n\
\n\
For a matrix argument, return a row vector of ones and\n\
zeros with each element indicating whether any of the elements of the\n\
corresponding column of the matrix are nonzero.  For example,\n\
\n\
@example\n\
@group\n\
any (eye (2, 4))\n\
     @result{} [ 1, 1, 0, 0 ]\n\
@end group\n\
@end example\n\
\n\
If the optional argument @var{dim} is supplied, work along dimension\n\
@var{dim}.  For example,\n\
\n\
@example\n\
@group\n\
any (eye (2, 4), 2)\n\
     @result{} [ 1; 1 ]\n\
@end group\n\
@end example\n\
@end deftypefn")
{
  ANY_ALL (any);
}

// These mapping functions may also be useful in other places, eh?

typedef double (*d_dd_fcn) (double, double);

static Matrix
map_d_m (d_dd_fcn f, double x, const Matrix& y)
{
  int nr = y.rows ();
  int nc = y.columns ();

  Matrix retval (nr, nc);

  for (int j = 0; j < nc; j++)
    for (int i = 0; i < nr; i++)
      {
	OCTAVE_QUIT;
	retval (i, j) = f (x, y (i, j));
      }

  return retval;
}

static Matrix
map_m_d (d_dd_fcn f, const Matrix& x, double y)
{
  int nr = x.rows ();
  int nc = x.columns ();

  Matrix retval (nr, nc);

  for (int j = 0; j < nc; j++)
    for (int i = 0; i < nr; i++)
      {
	OCTAVE_QUIT;
	retval (i, j) = f (x (i, j), y);
      }

  return retval;
}

static Matrix
map_m_m (d_dd_fcn f, const Matrix& x, const Matrix& y)
{
  int x_nr = x.rows ();
  int x_nc = x.columns ();

  int y_nr = y.rows ();
  int y_nc = y.columns ();

  assert (x_nr == y_nr && x_nc == y_nc);

  Matrix retval (x_nr, x_nc);

  for (int j = 0; j < x_nc; j++)
    for (int i = 0; i < x_nr; i++)
      {
	OCTAVE_QUIT;
	retval (i, j) = f (x (i, j), y (i, j));
      }

  return retval;
}

DEFUN (atan2, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} atan2 (@var{y}, @var{x})\n\
Compute atan (@var{y} / @var{x}) for corresponding elements of @var{y}\n\
and @var{x}.  The result is in range -pi to pi.\n\
@end deftypefn")
{
  octave_value retval;

  int nargin = args.length ();

  if (nargin == 2 && args(0).is_defined () && args(1).is_defined ())
    {
      octave_value arg_y = args(0);
      octave_value arg_x = args(1);

      int y_nr = arg_y.rows ();
      int y_nc = arg_y.columns ();

      int x_nr = arg_x.rows ();
      int x_nc = arg_x.columns ();

      int arg_y_empty = empty_arg ("atan2", y_nr, y_nc);
      int arg_x_empty = empty_arg ("atan2", x_nr, x_nc);

      if (arg_y_empty > 0 && arg_x_empty > 0)
	return octave_value (Matrix ());
      else if (arg_y_empty || arg_x_empty)
	return retval;

      int y_is_scalar = (y_nr == 1 && y_nc == 1);
      int x_is_scalar = (x_nr == 1 && x_nc == 1);

      if (y_is_scalar && x_is_scalar)
	{
	  double y = arg_y.double_value ();

	  if (! error_state)
	    {
	      double x = arg_x.double_value ();

	      if (! error_state)
		retval = atan2 (y, x);
	    }
	}
      else if (y_is_scalar)
	{
	  double y = arg_y.double_value ();

	  if (! error_state)
	    {
	      Matrix x = arg_x.matrix_value ();

	      if (! error_state)
		retval = map_d_m (atan2, y, x);
	    }
	}
      else if (x_is_scalar)
	{
	  Matrix y = arg_y.matrix_value ();

	  if (! error_state)
	    {
	      double x = arg_x.double_value ();

	      if (! error_state)
		retval = map_m_d (atan2, y, x);
	    }
	}
      else if (y_nr == x_nr && y_nc == x_nc)
	{
	  Matrix y = arg_y.matrix_value ();

	  if (! error_state)
	    {
	      Matrix x = arg_x.matrix_value ();

	      if (! error_state)
		retval = map_m_m (atan2, y, x);
	    }
	}
      else
	error ("atan2: nonconformant matrices");
    }
  else
    print_usage ("atan2");

  return retval;
}

DEFUN (fmod, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} fmod (@var{x}, @var{y})\n\
Compute the floating point remainder of dividing @var{x} by @var{y}\n\
using the C library function @code{fmod}.  The result has the same\n\
sign as @var{x}.  If @var{y} is zero, the result implementation-defined.\n\
@end deftypefn")
{
  octave_value retval;

  int nargin = args.length ();

  if (nargin == 2 && args(0).is_defined () && args(1).is_defined ())
    {
      octave_value arg_x = args(0);
      octave_value arg_y = args(1);

      int y_nr = arg_y.rows ();
      int y_nc = arg_y.columns ();

      int x_nr = arg_x.rows ();
      int x_nc = arg_x.columns ();

      int arg_y_empty = empty_arg ("fmod", y_nr, y_nc);
      int arg_x_empty = empty_arg ("fmod", x_nr, x_nc);

      if (arg_y_empty > 0 && arg_x_empty > 0)
	return octave_value (Matrix ());
      else if (arg_y_empty || arg_x_empty)
	return retval;

      int y_is_scalar = (y_nr == 1 && y_nc == 1);
      int x_is_scalar = (x_nr == 1 && x_nc == 1);

      if (y_is_scalar && x_is_scalar)
	{
	  double y = arg_y.double_value ();

	  if (! error_state)
	    {
	      double x = arg_x.double_value ();

	      if (! error_state)
		retval = fmod (x, y);
	    }
	}
      else if (y_is_scalar)
	{
	  double y = arg_y.double_value ();

	  if (! error_state)
	    {
	      Matrix x = arg_x.matrix_value ();

	      if (! error_state)
		retval = map_m_d (fmod, x, y);
	    }
	}
      else if (x_is_scalar)
	{
	  Matrix y = arg_y.matrix_value ();

	  if (! error_state)
	    {
	      double x = arg_x.double_value ();

	      if (! error_state)
		retval = map_d_m (fmod, x, y);
	    }
	}
      else if (y_nr == x_nr && y_nc == x_nc)
	{
	  Matrix y = arg_y.matrix_value ();

	  if (! error_state)
	    {
	      Matrix x = arg_x.matrix_value ();

	      if (! error_state)
		retval = map_m_m (fmod, x, y);
	    }
	}
      else
	error ("fmod: nonconformant matrices");
    }
  else
    print_usage ("fmod");

  return retval;
}

#define DATA_REDUCTION(FCN) \
 \
  octave_value retval; \
 \
  int nargin = args.length (); \
 \
  if (nargin == 1 || nargin == 2) \
    { \
      octave_value arg = args(0); \
 \
      int dim = (nargin == 1 ? -1 : args(1).int_value (true) - 1); \
 \
      if (! error_state) \
	{ \
	  if (dim >= -1) \
	    { \
	      if (arg.is_real_type ()) \
		{ \
		  NDArray tmp = arg.array_value (); \
 \
		  if (! error_state) \
		    retval = tmp.FCN (dim); \
		} \
	      else if (arg.is_complex_type ()) \
		{ \
		  ComplexNDArray tmp = arg.complex_array_value (); \
 \
		  if (! error_state) \
		    retval = tmp.FCN (dim); \
		} \
	      else \
		{ \
		  gripe_wrong_type_arg (#FCN, arg); \
		  return retval; \
		} \
	    } \
	  else \
	    error (#FCN ": invalid dimension argument = %d", dim + 1); \
	} \
    } \
  else \
    print_usage (#FCN); \
 \
  return retval

DEFUN (cumprod, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} cumprod (@var{x}, @var{dim})\n\
Cumulative product of elements along dimension @var{dim}.  If\n\
@var{dim} is omitted, it defaults to 1 (column-wise cumulative\n\
products).\n\
@end deftypefn")
{
  DATA_REDUCTION (cumprod);
}

DEFUN (cumsum, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} cumsum (@var{x}, @var{dim})\n\
Cumulative sum of elements along dimension @var{dim}.  If @var{dim}\n\
is omitted, it defaults to 1 (column-wise cumulative sums).\n\
@end deftypefn")
{
  DATA_REDUCTION (cumsum);
}

// XXX FIXME XXX -- we could eliminate some duplicate code here with
// some template functions or macros.

static octave_value
make_diag (const Matrix& v, int k)
{
  int nr = v.rows ();
  int nc = v.columns ();
  assert (nc == 1 || nr == 1);

  octave_value retval;

  int roff = 0;
  int coff = 0;
  if (k > 0)
    {
      roff = 0;
      coff = k;
    }
  else if (k < 0)
    {
      roff = -k;
      coff = 0;
    }

  if (nr == 1)
    {
      int n = nc + std::abs (k);
      Matrix m (n, n, 0.0);
      for (int i = 0; i < nc; i++)
	m (i+roff, i+coff) = v (0, i);
      retval = m;
    }
  else
    {
      int n = nr + std::abs (k);
      Matrix m (n, n, 0.0);
      for (int i = 0; i < nr; i++)
	m (i+roff, i+coff) = v (i, 0);
      retval = m;
    }

  return retval;
}

static octave_value
make_diag (const ComplexMatrix& v, int k)
{
  int nr = v.rows ();
  int nc = v.columns ();
  assert (nc == 1 || nr == 1);

  octave_value retval;

  int roff = 0;
  int coff = 0;
  if (k > 0)
    {
      roff = 0;
      coff = k;
    }
  else if (k < 0)
    {
      roff = -k;
      coff = 0;
    }

  if (nr == 1)
    {
      int n = nc + std::abs (k);
      ComplexMatrix m (n, n, 0.0);
      for (int i = 0; i < nc; i++)
	m (i+roff, i+coff) = v (0, i);
      retval = m;
    }
  else
    {
      int n = nr + std::abs (k);
      ComplexMatrix m (n, n, 0.0);
      for (int i = 0; i < nr; i++)
	m (i+roff, i+coff) = v (i, 0);
      retval = m;
    }

  return retval;
}

static octave_value
make_diag (const octave_value& arg)
{
  octave_value retval;

  if (arg.is_real_type ())
    {
      Matrix m = arg.matrix_value ();

      if (! error_state)
	{
	  int nr = m.rows ();
	  int nc = m.columns ();

	  if (nr == 0 || nc == 0)
	    retval = Matrix ();
	  else if (nr == 1 || nc == 1)
	    retval = make_diag (m, 0);
	  else
	    {
	      ColumnVector v = m.diag ();
	      if (v.capacity () > 0)
		retval = v;
	    }
	}
      else
	gripe_wrong_type_arg ("diag", arg);
    }
  else if (arg.is_complex_type ())
    {
      ComplexMatrix cm = arg.complex_matrix_value ();

      if (! error_state)
	{
	  int nr = cm.rows ();
	  int nc = cm.columns ();

	  if (nr == 0 || nc == 0)
	    retval = Matrix ();
	  else if (nr == 1 || nc == 1)
	    retval = make_diag (cm, 0);
	  else
	    {
	      ComplexColumnVector v = cm.diag ();
	      if (v.capacity () > 0)
		retval = v;
	    }
	}
      else
	gripe_wrong_type_arg ("diag", arg);
    }
  else
    gripe_wrong_type_arg ("diag", arg);

  return retval;
}

static octave_value
make_diag (const octave_value& a, const octave_value& b)
{
  octave_value retval;

  int k = b.int_value ();

  if (error_state)
    {
      error ("diag: invalid second argument");      
      return retval;
    }

  if (a.is_real_type ())
    {
      Matrix m = a.matrix_value ();

      if (! error_state)
	{
	  int nr = m.rows ();
	  int nc = m.columns ();

	  if (nr == 1 || nc == 1)
	    retval = make_diag (m, k);
	  else if (nr == 0 || nc == 0)
	    retval = Matrix ();
	  else
	    {
	      ColumnVector d = m.diag (k);
	      retval = d;
	    }
	}
    }
  else if (a.is_complex_type ())
    {
      ComplexMatrix cm = a.complex_matrix_value ();

      if (! error_state)
	{
	  int nr = cm.rows ();
	  int nc = cm.columns ();

	  if (nr == 1 || nc == 1)
	    retval = make_diag (cm, k);
	  else if (nr == 0 || nc == 0)
	    retval = Matrix ();
	  else
	    {
	      ComplexColumnVector d = cm.diag (k);
	      retval = d;
	    }
	}
    }
  else
    gripe_wrong_type_arg ("diag", a);

  return retval;
}

DEFUN (diag, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} diag (@var{v}, @var{k})\n\
Return a diagonal matrix with vector @var{v} on diagonal @var{k}.  The\n\
second argument is optional.  If it is positive, the vector is placed on\n\
the @var{k}-th super-diagonal.  If it is negative, it is placed on the\n\
@var{-k}-th sub-diagonal.  The default value of @var{k} is 0, and the\n\
vector is placed on the main diagonal.  For example,\n\
\n\
@example\n\
@group\n\
diag ([1, 2, 3], 1)\n\
     @result{}  0  1  0  0\n\
         0  0  2  0\n\
         0  0  0  3\n\
         0  0  0  0\n\
@end group\n\
@end example\n\
@end deftypefn")
{
  octave_value retval;

  int nargin = args.length ();

  if (nargin == 1 && args(0).is_defined ())
    retval = make_diag (args(0));
  else if (nargin == 2 && args(0).is_defined () && args(1).is_defined ())
    retval = make_diag (args(0), args(1));
  else
    print_usage ("diag");

  return retval;
}

DEFUN (prod, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} prod (@var{x}, @var{dim})\n\
Product of elements along dimension @var{dim}.  If @var{dim} is\n\
omitted, it defaults to 1 (column-wise products).\n\
@end deftypefn")
{
  DATA_REDUCTION (prod);
}

static bool
cat_add_dims (dim_vector& dv_new, const dim_vector& dv_arg, int dim)
{
  // dv_arg is []

  if (dv_arg.all_zero ())
    return true;
  
  // dv_new is []

  if (dv_new.all_zero ())
    {
      dv_new = dv_arg;
      return true;
    }
  
  int n_new  = dv_new.length ();
  int n_args = dv_arg.length ();
  
  // Find the max and min value of n_new and n_args

  int n_max = n_new > n_args ? n_new : n_args;
  int n_min = n_new < n_args ? n_new : n_args;  

  // The elements of the dimension vectors can only differ
  // if the dim variable differs from the actual dimension
  // they differ.

  for (int i = 0; i < n_min; i++)
    {
      if (dv_new(i) != dv_arg(i) && dim != i)
	{
	  error ("cat: dimension mismatch");
	  return false;
	}
    }
  
  // Ditto.

  for (int i = n_min; i < n_max; i++)
    {
      if (n_new > n_min)
	{
	  if (dv_new(i) != 1 && dim != i)
	    {
	      error ("cat: dimension mismatch");
	      return false;
	    }
	}
      else 
	{
	  if (dv_arg(i) != 1 && dim != i)
	    {
	      error ("cat: dimension mismatch");
	      return false;
	    }
	}
    }

  // If we want to add the dimension vectors at a dimension
  // larger than both, then we need to set n_max to this number
  // so that we resize dv_new to the right dimension.

  n_max = n_max > (dim + 1) ? n_max : (dim + 1);
  
  // Resize dv_new to new the appropriate dimensions.

  if (n_max > n_new)
    {
      dv_new.resize (n_max);

      for (int i = n_new; i < n_max; i++)
	dv_new.elem (i) = 1;
    }
  
  // Larger or equal since dim has been decremented by one.

  if (dim >= n_args)
    dv_new.elem (dim) = dv_new.elem (dim)++;
  else
    dv_new.elem (dim) += dv_arg(dim);

  return true;
}

static octave_value
do_cat (const octave_value_list& args, std::string fname)
{
  octave_value retval;

  int n_args = args.length (); 

  if (n_args > 2)
    {
      int dim = args(0).int_value () - 1;

      if (error_state)
	{
	  error ("cat: expecting first argument to be a integer");
	  return retval;
	}
  
      if (dim >= 0)
	{
	  
	  dim_vector  dv = args(1).dims ();
  
	  for (int i = 2; i < args.length (); i++)
	    {
	      // add_dims constructs a dimension vector which holds the
	      // dimensions of the final array after concatenation.

	      if (! cat_add_dims (dv, args(i).dims (), dim))
		{
		  // Dimensions do not match. 
		  // cat_add_dims printed a error msg
		  return retval;
		}
	    }

	  NDArray cat_re;
	  ComplexNDArray cat_cx;
	  charNDArray cat_ch;
	  Cell cat_cell;
	  Octave_map cat_map;

	  // The final array can be of three types:
	  //
	  //       re cx ch c
	  // ----------------
	  // re   |re cx ch X
	  // cx   |cx cx X  X
	  // ch   |ch X  ch X
	  // cell |X  X  X  c
	  // (X means incompatible).

	  enum types { REAL, COMPLEX, CHAR, CELL, MAP} t;      

	  // Initialize t to right value
	  if (args(1).is_cell ())
	    {
	      t = CELL;
	      cat_cell = Cell (dv);
	    }
	  else if (args(1).is_map ())
	    {
	      error ("concatenation of structures is not yet implemented");
	      return retval;
	      // t = MAP;
	      // cat_map = Octave_map (dv);
	    }
	  else 
	    {
	      t = REAL;
	      cat_re = NDArray (dv, 0);
	    }
 
	  int idx = 0;
  
	  dim_vector dv_first = args(1).dims ();
      
	  // n_moves tells us how many times we need to
	  // visit each argument.
	  //
	  // If we are concatenating a 2x2x2 array with a 2x2x2 array
	  // along the second dimensions, we do two iterations
	  // trough the arguments and move 2x2 elements from each
	  // of the arguments into the resulting array on each iteration.
	  int n_moves = 1;

	  for (int i = dim + 1; i < dv_first.length (); i++)
	    n_moves *= dv_first(i);
      
	  for (int move = 0; move < n_moves ; move++)
	    {     
	      for (int i = 1; i < n_args; i++)
		{
		  octave_value tmp = args (i);

		  if (t == MAP)
		    {
		      error ("concatenation of structures is not yet implemented");
		      return retval;
		    }
		  else if (t == CELL)
		    {
		      if (! tmp.is_cell ())
			{
			  error ("cannot convert argument to cell");
			  return retval;
			}
		      else
			{
			  Cell ra_tmp = args(i).cell_value ();
	  
			  if (error_state)
			    return retval;

			  idx = cat_cell.cat (ra_tmp, dim, idx, move);
			}
		    }
		  else if (t == REAL)
		    {
		      if (tmp.is_complex_type ())
			{
			  cat_cx = ComplexNDArray (cat_re);		  
		  
			  ComplexNDArray ra_tmp = tmp.complex_array_value ();
	  
			  if (error_state)
			    return retval;

			  idx = cat_cx.cat (ra_tmp, dim, idx, move);

			  t = COMPLEX;
			}
		      else if (tmp.is_string ())
			{
			  // This is a hack to be able to convert a dNDArray
			  // to a chNDArray.

			  cat_ch = charNDArray (octave_value (cat_re).char_array_value ());	  
		  
			  charNDArray ra_tmp = tmp.char_array_value ();
	  
			  if (error_state)
			    return retval;

			  idx = cat_ch.cat (ra_tmp, dim, idx, move);
	
			  t = CHAR;
			}
		      else //if (tmp.is_real_type ())
			{ 
			  NDArray ra_tmp = tmp.array_value ();
	
			  if (error_state)
			    return retval;
		
			  idx = cat_re.cat (ra_tmp, dim, idx, move);
			}  
		    }
		  else if (t == COMPLEX)
		    {
		      ComplexNDArray ra_tmp = tmp.complex_array_value ();
	  
		      if (error_state)
			return retval;

		      idx = cat_cx.cat (ra_tmp, dim, idx, move);
		    }
		  else if (t == CHAR)
		    {
		      if (tmp.is_complex_type ())
			{
			  error ("cannot convert complex type to character type");
			  return retval;
			}
		      else
			{
			  charNDArray ra_tmp = tmp.char_array_value ();
	  
			  if (error_state)
			    return retval;

			  cat_ch.cat (ra_tmp, dim, idx, move);
			}
		    }
		}
	    }
      
	  if (t == REAL)
	    retval = octave_value (cat_re);
	  else if (t == COMPLEX)
	    retval = octave_value (cat_cx);
	  else if (t == CHAR)
	    retval = octave_value (cat_ch);
	  else if (t == CELL)
	    retval = octave_value (cat_cell);
	  else if (t == MAP)
	    retval = octave_value (cat_map);
	}
      else print_usage (fname);
    }
  else
    print_usage (fname);
 
  return retval;
}

DEFUN (horzcat, args, ,
       "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} horzcat (@var{array1}, @var{array2}, @dots{}, @var{arrayN})\n\
Return the horizontal concatenation of N-d array objects, @var{array1},\n\
@var{array2}, @dots{}, @var{arrayN} along dimension 2.\n\
@end deftypefn\n\
@seealso{cat and vertcat}")
{
  octave_value_list args_tmp = args;
  
  int dim = 2;
  
  octave_value d (dim);
  
  args_tmp.prepend (d);
  
  return do_cat (args_tmp, "horzcat");
}

DEFUN (vertcat, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} vertcat (@var{array1}, @var{array2}, @dots{}, @var{arrayN})\n\
Return the vertical concatenation of N-d array objects, @var{array1},\n\
@var{array2}, @dots{}, @var{arrayN} along dimension 1.\n\
@end deftypefn\n\
@seealso{cat and horzcat}")
{
  octave_value_list args_tmp = args;
  
  int dim = 1;
  
  octave_value d (dim);
  
  args_tmp.prepend (d);
  
  return do_cat (args_tmp, "vertcat");
}

DEFUN (cat, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} cat (@var{dim}, @var{array1}, @var{array2}, @dots{}, @var{arrayN})\n\
Return the concatenation of N-d array objects, @var{array1},\n\
@var{array2}, @dots{}, @var{arrayN} along dimension @var{dim}.\n\
\n\
@example\n\
@group\n\
A = ones (2, 2);\n\
B = zeros (2, 2);\n\
cat (2, A, B)\n\
@result{} ans =\n\
\n\
     1 1 0 0\n\
     1 1 0 0\n\
     1 1 0 0\n\
     1 1 0 0\n\
@end group\n\
@end example\n\
\n\
Alternatively, we can concatenate @var{A} and @var{B} along the\n\
second dimension the following way:\n\
\n\
@example\n\
@group\n\
[A, B].\n\
@end group\n\
@end example\n\
\n\
@var{dim} can be larger than the dimensions of the N-d array objects\n\
and the result will thus have @var{dim} dimensions as the\n\
following example shows:\n\
@example\n\
@group\n\
cat (4, ones(2, 2), zeros (2, 2))\n\
@result{} ans =\n\
\n\
   ans(:,:,1,1) =\n\
\n\
     1 1\n\
     1 1\n\
\n\
   ans(:,:,1,2) =\n\
     0 0\n\
     0 0\n\
@end group\n\
@end example\n\
\n\
@end deftypefn\n\
@seealso{horzcat and vertcat}")
{
  return do_cat (args, "cat");
}

static octave_value
do_permute (const octave_value_list& args, bool inv, const std::string& fname)
{
  octave_value retval;

  if (args.length () == 2 && args(1).length () == args(0).dims ().length ())
    {
      Array<int> vec = args(1).int_vector_value ();

      octave_value ret = args(0).permute (vec, inv);

      if (! error_state)
	retval = ret;
    }
  else
    print_usage (fname);

  return retval;
}

DEFUN (permute, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} permute (@var{a}, @var{perm})\n\
Return the generalized transpose for an N-d array object @var{a}.\n\
The permutation vector @var{perm} must contain the elements\n\
@code{1:ndims(a)} (in any order, but each element must appear just once).\n\
\n\
@end deftypefn\n\
@seealso{ipermute}")
{
  return do_permute (args, false, "permute");
}

DEFUN (ipermute, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} ipermute (@var{a}, @var{iperm})\n\
The inverse of the @code{permute} function.  The expression\n\
\n\
@example\n\
ipermute (permute (a, perm), perm)\n\
@end example\n\
returns the original array @var{a}.\n\
\n\
@end deftypefn\n\
@seealso{permute}")
{
  return do_permute (args, true, "ipermute");
}

DEFUN (length, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} length (@var{a})\n\
Return the `length' of the object @var{a}.  For matrix objects, the\n\
length is the number of rows or columns, whichever is greater (this\n\
odd definition is used for compatibility with Matlab).\n\
@end deftypefn")
{
  octave_value retval;

  if (args.length () == 1)
    {
      int len = args(0).length ();

      if (! error_state)
	retval = len;
    }
  else
    print_usage ("length");

  return retval;
}

DEFUN (ndims, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} ndims (@var{a})\n\
Returns the number of dimensions of array @var{a}.\n\
For any array, the result will always be larger than or equal to 2.\n\
Trailing singleton dimensions are not counted.\n\
@end deftypefn")
{
  octave_value retval;

  if (args.length () == 1)
    {
      int n_dims = args(0).ndims ();

      if (! error_state)
	retval = n_dims;
    }
  else
    print_usage ("ndims");

  return retval;
}

DEFUN (numel, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} numel (@var{a})\n\
Returns the number of elements in the object @var{a}.\n\
@end deftypefn")
{
  octave_value retval;

  if (args.length () == 1)
    {
      int numel = args(0).numel ();

      if (! error_state)
	{
	  if (numel < 0)
	    numel = 0;

	  retval = numel;
	}
    }
  else
    print_usage ("numel");

  return retval;
}

DEFUN (size, args, nargout,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} size (@var{a}, @var{n})\n\
Return the number rows and columns of @var{a}.\n\
\n\
With one input argument and one output argument, the result is returned\n\
in a row vector.  If there are multiple output arguments, the number of\n\
rows is assigned to the first, and the number of columns to the second,\n\
etc.  For example,\n\
\n\
@example\n\
@group\n\
size ([1, 2; 3, 4; 5, 6])\n\
     @result{} [ 3, 2 ]\n\
\n\
[nr, nc] = size ([1, 2; 3, 4; 5, 6])\n\
     @result{} nr = 3\n\
     @result{} nc = 2\n\
@end group\n\
@end example\n\
\n\
If given a second argument, @code{size} will return the size of the\n\
corresponding dimension.  For example\n\
\n\
@example\n\
size ([1, 2; 3, 4; 5, 6], 2)\n\
     @result{} 2\n\
@end example\n\
\n\
@noindent\n\
returns the number of columns in the given matrix.\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin == 1)
    {
      dim_vector dimensions = args(0).dims ();

      int ndims = dimensions.length ();

      Matrix m (1, ndims);

      if (nargout > 1)
	{
	  while (ndims--)
	    retval(ndims) = dimensions(ndims);
	}
      else
	{
	  for (int i = 0; i < ndims; i++)
	    m(0, i) = dimensions(i);

	  retval(0) = m;
	}
    }
  else if (nargin == 2 && nargout < 2)
    {
      int nd = args(1).int_value (true);

      if (error_state)
	error ("size: expecting scalar as second argument");
      else
	{
	  dim_vector dv = args(0).dims ();

	  if (nd > 0 && nd <= dv.length ())
	    retval(0) = dv(nd-1);
	  else
	    error ("size: requested dimension (= %d) out of range", nd);
	}
    }
  else
    print_usage ("size");

  return retval;
}

DEFUN (sum, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} sum (@var{x}, @var{dim})\n\
Sum of elements along dimension @var{dim}.  If @var{dim} is\n\
omitted, it defaults to 1 (column-wise sum).\n\
@end deftypefn")
{
  DATA_REDUCTION (sum);
}

DEFUN (sumsq, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} sumsq (@var{x}, @var{dim})\n\
Sum of squares of elements along dimension @var{dim}.  If @var{dim}\n\
is omitted, it defaults to 1 (column-wise sum of squares).\n\
\n\
This function is equivalent to computing\n\
@example\n\
sum (x .* conj (x), dim)\n\
@end example\n\
but it uses less memory and avoids calling conj if @var{x} is real.\n\
@end deftypefn")
{
  DATA_REDUCTION (sumsq);
}

DEFUN (isbool, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Functio} {} isbool (@var{x})\n\
Return true if @var{x} is a boolean object.\n\
@end deftypefn")
{
  octave_value retval;

  if (args.length () == 1)
    retval = args(0).is_bool_type ();
  else
    print_usage ("isbool");

  return retval;
}

DEFALIAS (islogical, isbool);

DEFUN (iscomplex, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} iscomplex (@var{x})\n\
Return true if @var{x} is a complex-valued numeric object.\n\
@end deftypefn")
{
  octave_value retval;

  if (args.length () == 1)
    retval = args(0).is_complex_type ();
  else
    print_usage ("iscomplex");

  return retval;
}

DEFUN (isreal, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} isreal (@var{x})\n\
Return true if @var{x} is a real-valued numeric object.\n\
@end deftypefn")
{
  octave_value retval;

  if (args.length () == 1)
    retval = args(0).is_real_type ();
  else
    print_usage ("isreal");

  return retval;
}

DEFUN (isempty, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} isempty (@var{a})\n\
Return 1 if @var{a} is an empty matrix (either the number of rows, or\n\
the number of columns, or both are zero).  Otherwise, return 0.\n\
@end deftypefn")
{
  octave_value retval = false;

  if (args.length () == 1)
    retval = args(0).is_empty ();
  else
    print_usage ("isempty");

  return retval;
}

DEFUN (isnumeric, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} isnumeric (@var{x})\n\
Return nonzero if @var{x} is a numeric object.\n\
@end deftypefn")
{
  octave_value retval;

  if (args.length () == 1)
    retval = args(0).is_numeric_type ();
  else
    print_usage ("isnumeric");

  return retval;
}

DEFUN (islist, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} islist (@var{x})\n\
Return nonzero if @var{x} is a list.\n\
@end deftypefn")
{
  octave_value retval;

  if (args.length () == 1)
    retval = args(0).is_list ();
  else
    print_usage ("islist");

  return retval;
}

DEFUN (ismatrix, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} ismatrix (@var{a})\n\
Return 1 if @var{a} is a matrix.  Otherwise, return 0.\n\
@end deftypefn")
{
  octave_value retval = false;

  if (args.length () == 1)
    {
      octave_value arg = args(0);

      if (arg.is_scalar_type () || arg.is_range ())
	retval = true;
      else if (arg.is_matrix_type ())
	retval = (arg.rows () >= 1 && arg.columns () >= 1);
    }
  else
    print_usage ("ismatrix");

  return retval;
}

static octave_value
fill_matrix (const octave_value_list& args, double val, const char *fcn)
{
  octave_value retval;

  int nargin = args.length ();

  int ndim = 0;
  int type = 0;

  dim_vector dims;
  
  // Check for type information.

  if (nargin > 0 && args(nargin-1).is_string ())
    {
      nargin--;

      // XXX FIXME XXX -- allow type of the resulting matrix to be
      // specified, e.g.
      //
      //   zeros(n1, n2, ..., 'real')
      //   zeros(n1, n2, ..., 'complex')
      //
      // type = get_type (args(nargin).string_value ());
    }

  // determine matrix dimension

  switch (nargin)
    {
    case 0:
      ndim = 0;
      type = 0;
      break;

    case 1:
      get_dimensions (args(0), fcn, dims);
      break;

    default:
      {
	dims.resize (nargin);

	for (int i = 0; i < nargin; i++)
	  {
	    dims(i) = args(i).is_empty () ? 0 : args(i).int_value ();

	    if (error_state)
	      {
		error ("%s: expecting scalar integer arguments", fcn);
		break;
	      }
	  }
      }
      break;
    }

  if (! error_state)
    {
      ndim = dims.length ();

      for (int i = ndim-1; i > 1; i--)
	{
	  if (dims(i) == 1)
	    ndim--;
	  else
	    break;
	}

      dims.resize (ndim);

      check_dimensions (dims, fcn);

      if (! error_state)
	{
	  // Construct either scalar, matrix or N-d array.

	  switch (ndim)
	    {
	    case 0:
	      retval = val;
	      break;

	    case 1:
	      retval = Matrix (dims(0), dims(0), val);
	      break;

	    case 2:
	      retval = Matrix (dims(0), dims(1), val);
	      break;

	    default:
	      retval = NDArray (dims, val);
	      break;
	    }
	}
    }

  return retval;
}

DEFUN (ones, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} ones (@var{x})\n\
@deftypefnx {Built-in Function} {} ones (@var{n}, @var{m})\n\
@deftypefnx {Built-in Function} {} ones (@var{n}, @var{m}, @var{k},...)\n\
Return a matrix or N-dimensional array whose elements are all 1.\n\
The arguments are handled the same as the arguments for @code{eye}.\n\
\n\
If you need to create a matrix whose values are all the same, you should\n\
use an expression like\n\
\n\
@example\n\
val_matrix = val * ones (n, m)\n\
@end example\n\
@end deftypefn")
{
  return fill_matrix (args, 1.0, "ones");
}

DEFUN (zeros, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} zeros (@var{x})\n\
@deftypefnx {Built-in Function} {} zeros (@var{n}, @var{m})\n\
@deftypefnx {Built-in Function} {} zeros (@var{n}, @var{m}, @var{k},...)\n\
Return a matrix or N-dimensional array whose elements are all 0.\n\
The arguments are handled the same as the arguments for @code{eye}.\n\
@end deftypefn")
{
  return fill_matrix (args, 0.0, "zeros");
}

DEFUN (eye, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} eye (@var{x})\n\
@deftypefnx {Built-in Function} {} eye (@var{n}, @var{m})\n\
Return an identity matrix.  If invoked with a single scalar argument,\n\
@code{eye} returns a square matrix with the dimension specified.  If you\n\
supply two scalar arguments, @code{eye} takes them to be the number of\n\
rows and columns.  If given a vector with two elements, @code{eye} uses\n\
the values of the elements as the number of rows and columns,\n\
respectively.  For example,\n\
\n\
@example\n\
@group\n\
eye (3)\n\
     @result{}  1  0  0\n\
         0  1  0\n\
         0  0  1\n\
@end group\n\
@end example\n\
\n\
The following expressions all produce the same result:\n\
\n\
@example\n\
@group\n\
eye (2)\n\
@equiv{}\n\
eye (2, 2)\n\
@equiv{}\n\
eye (size ([1, 2; 3, 4])\n\
@end group\n\
@end example\n\
\n\
For compatibility with @sc{Matlab}, calling @code{eye} with no arguments\n\
is equivalent to calling it with an argument of 1.\n\
@end deftypefn")
{
  octave_value retval;

  int nargin = args.length ();

  switch (nargin)
    {
    case 0:
      retval = 1.0;
      break;

    case 1:
      {
	int nr, nc;
	get_dimensions (args(0), "eye", nr, nc);

	if (! error_state)
	  retval = identity_matrix (nr, nc);
      }
      break;

    case 2:
      {
	int nr, nc;
	get_dimensions (args(0), args(1), "eye", nr, nc);

	if (! error_state)
	  retval = identity_matrix (nr, nc);
      }
      break;

    default:
      print_usage ("eye");
      break;
    }

  return retval;
}

DEFUN (linspace, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} linspace (@var{base}, @var{limit}, @var{n})\n\
Return a row vector with @var{n} linearly spaced elements between\n\
@var{base} and @var{limit}.  The number of elements, @var{n}, must be\n\
greater than 1.  The @var{base} and @var{limit} are always included in\n\
the range.  If @var{base} is greater than @var{limit}, the elements are\n\
stored in decreasing order.  If the number of points is not specified, a\n\
value of 100 is used.\n\
\n\
The @code{linspace} function always returns a row vector.\n\
@end deftypefn")
{
  octave_value retval;

  int nargin = args.length ();

  int npoints = 100;

  if (nargin != 2 && nargin != 3)
    {
      print_usage ("linspace");
      return retval;
    }

  if (nargin == 3)
    npoints = args(2).int_value ();

  if (! error_state)
    {
      octave_value arg_1 = args(0);
      octave_value arg_2 = args(1);

      if (arg_1.is_complex_type () || arg_2.is_complex_type ())
	{
	  Complex x1 = arg_1.complex_value ();
	  Complex x2 = arg_2.complex_value ();

	  if (! error_state)
	    {
	      ComplexRowVector rv = linspace (x1, x2, npoints);

	      if (! error_state)
		retval = rv;
	    }
	}
      else
	{
	  double x1 = arg_1.double_value ();
	  double x2 = arg_2.double_value ();

	  if (! error_state)
	    {
	      RowVector rv = linspace (x1, x2, npoints);

	      if (! error_state)
		retval = rv;
	    }
	}
    }
  else
    error ("linspace: expecting third argument to be an integer");

  return retval;
}

DEFUN (reshape, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Function File} {} reshape (@var{a}, @var{m}, @var{n}, @dots{})\n\
@deftypefnx {Function File} {} reshape (@var{a}, @var{siz})\n\
Return a matrix with the given dimensions whose elements are taken\n\
from the matrix @var{a}.  The elements of the matrix are access in\n\
column-major order (like Fortran arrays are stored).\n\
\n\
For example,\n\
\n\
@example\n\
@group\n\
reshape ([1, 2, 3, 4], 2, 2)\n\
     @result{}  1  3\n\
         2  4\n\
@end group\n\
@end example\n\
\n\
@noindent\n\
Note that the total number of elements in the original\n\
matrix must match the total number of elements in the new matrix.\n\
@end deftypefn")
{
  octave_value retval;

  int nargin = args.length ();

  Array<int> new_size;

  if (nargin == 2)
    new_size = args(1).int_vector_value ();
  else if (nargin > 2)
    {
      new_size.resize (nargin-1);

      for (int i = 1; i < nargin; i++)
	{
	  new_size(i-1) = args(i).int_value ();

	  if (error_state)
	    break;
	}
    }
  else
    {
      print_usage ("reshape");
      return retval;
    }

  if (error_state)
    {
      error ("reshape: invalid arguments");
      return retval;
    }

  // Remove trailing singletons in new_size, but leave at least 2
  // elements.

  int n = new_size.length ();

  while (n > 2)
    {
      if (new_size(n-1) == 1)
	n--;
      else
	break;
    }

  new_size.resize (n);

  if (n < 2)
    {
      error ("reshape: expecting size to be vector with at least 2 elements");
      return retval;
    }

  dim_vector new_dims;

  new_dims.resize (n);

  for (int i = 0; i < n; i++)
    new_dims(i) = new_size(i);

  octave_value arg = args(0);

  if (new_dims.numel () == arg.numel ())
    retval = (new_dims == arg.dims ()) ? arg : arg.reshape (new_dims);
  else
    error ("reshape: size mismatch");

  return retval;
}

DEFUN (squeeze, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} squeeze (@var{x})\n\
Remove singleton dimensions from @var{x} and return the result.\n\
@end deftypefn")
{
  octave_value retval;

  if (args.length () == 1)
    retval = args(0).squeeze ();
  else
    print_usage ("squeeze");    

  return retval;
}

void
symbols_of_data (void)
{

#define IMAGINARY_DOC_STRING "-*- texinfo -*-\n\
@defvr {Built-in Variable} I\n\
@defvrx {Built-in Variable} J\n\
@defvrx {Built-in Variable} i\n\
@defvrx {Built-in Variable} j\n\
A pure imaginary number, defined as\n\
@iftex\n\
@tex\n\
  $\\sqrt{-1}$.\n\
@end tex\n\
@end iftex\n\
@ifinfo\n\
  @code{sqrt (-1)}.\n\
@end ifinfo\n\
The @code{I} and @code{J} forms are true constants, and cannot be\n\
modified.  The @code{i} and @code{j} forms are like ordinary variables,\n\
and may be used for other purposes.  However, unlike other variables,\n\
they once again assume their special predefined values if they are\n\
cleared @xref{Status of Variables}.\n\
@end defvr"

#define INFINITY_DOC_STRING "-*- texinfo -*-\n\
@defvr {Built-in Variable} Inf\n\
@defvrx {Built-in Variable} inf\n\
Infinity.  This is the result of an operation like 1/0, or an operation\n\
that results in a floating point overflow.\n\
@end defvr"

#define NAN_DOC_STRING "-*- texinfo -*-\n\
@defvr {Built-in Variable} NaN\n\
@defvrx {Built-in Variable} nan\n\
Not a number.  This is the result of an operation like\n\
@iftex\n\
@tex\n\
$0/0$, or $\\infty - \\infty$,\n\
@end tex\n\
@end iftex\n\
@ifinfo\n\
0/0, or @samp{Inf - Inf},\n\
@end ifinfo\n\
or any operation with a NaN.\n\
\n\
Note that NaN always compares not equal to NaN.  This behavior is\n\
specified by the IEEE standard for floating point arithmetic.  To\n\
find NaN values, you must use the @code{isnan} function.\n\
@end defvr"

  DEFCONST (I, Complex (0.0, 1.0),
    IMAGINARY_DOC_STRING);

  DEFCONST (Inf, lo_ieee_inf_value (),
    INFINITY_DOC_STRING);

  DEFCONST (J, Complex (0.0, 1.0),
    IMAGINARY_DOC_STRING);

  DEFCONST (NA, lo_ieee_na_value (),
    "-*- texinfo -*-\n\
@defvr {Built-in Variable} NA\n\
Missing value.\n\
@end defvr");

  DEFCONST (NaN, lo_ieee_nan_value (),
    NAN_DOC_STRING);

#if defined (M_E)
  double e_val = M_E;
#else
  double e_val = exp (1.0);
#endif

  DEFCONST (e, e_val,
    "-*- texinfo -*-\n\
@defvr {Built-in Variable} e\n\
The base of natural logarithms.  The constant\n\
@iftex\n\
@tex\n\
 $e$\n\
@end tex\n\
@end iftex\n\
@ifinfo\n\
 @var{e}\n\
@end ifinfo\n\
 satisfies the equation\n\
@iftex\n\
@tex\n\
 $\\log (e) = 1$.\n\
@end tex\n\
@end iftex\n\
@ifinfo\n\
 @code{log} (@var{e}) = 1.\n\
@end ifinfo\n\
@end defvr");

  DEFCONST (eps, DBL_EPSILON,
    "-*- texinfo -*-\n\
@defvr {Built-in Variable} eps\n\
The machine precision.  More precisely, @code{eps} is the largest\n\
relative spacing between any two adjacent numbers in the machine's\n\
floating point system.  This number is obviously system-dependent.  On\n\
machines that support 64 bit IEEE floating point arithmetic, @code{eps}\n\
is approximately\n\
@ifinfo\n\
 2.2204e-16.\n\
@end ifinfo\n\
@iftex\n\
@tex\n\
 $2.2204\\times10^{-16}$.\n\
@end tex\n\
@end iftex\n\
@end defvr");

  DEFCONST (false, false,
    "-*- texinfo -*-\n\
@defvr {Built-in Variable} false\n\
Logical false value.\n\
@end defvr");

  DEFCONST (i, Complex (0.0, 1.0),
    IMAGINARY_DOC_STRING);

  DEFCONST (inf, lo_ieee_inf_value (),
    INFINITY_DOC_STRING);

  DEFCONST (j, Complex (0.0, 1.0),
    IMAGINARY_DOC_STRING);

  DEFCONST (nan, lo_ieee_nan_value (),
    NAN_DOC_STRING);

#if defined (M_PI)
  double pi_val = M_PI;
#else
  double pi_val = 4.0 * atan (1.0);
#endif

  DEFCONST (pi, pi_val,
    "-*- texinfo -*-\n\
@defvr {Built-in Variable} pi\n\
The ratio of the circumference of a circle to its diameter.\n\
Internally, @code{pi} is computed as @samp{4.0 * atan (1.0)}.\n\
@end defvr");

  DEFCONST (realmax, DBL_MAX,
    "-*- texinfo -*-\n\
@defvr {Built-in Variable} realmax\n\
The largest floating point number that is representable.  The actual\n\
value is system-dependent.  On machines that support 64-bit IEEE\n\
floating point arithmetic, @code{realmax} is approximately\n\
@ifinfo\n\
 1.7977e+308\n\
@end ifinfo\n\
@iftex\n\
@tex\n\
 $1.7977\\times10^{308}$.\n\
@end tex\n\
@end iftex\n\
@end defvr");

  DEFCONST (realmin, DBL_MIN,
    "-*- texinfo -*-\n\
@defvr {Built-in Variable} realmin\n\
The smallest normalized floating point number that is representable.\n\
The actual value is system-dependent.  On machines that support\n\
64-bit IEEE floating point arithmetic, @code{realmin} is approximately\n\
@ifinfo\n\
 2.2251e-308\n\
@end ifinfo\n\
@iftex\n\
@tex\n\
 $2.2251\\times10^{-308}$.\n\
@end tex\n\
@end iftex\n\
@end defvr");

  DEFCONST (true, true,
    "-*- texinfo -*-\n\
@defvr {Built-in Variable} true\n\
Logical true value.\n\
@end defvr");

}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
