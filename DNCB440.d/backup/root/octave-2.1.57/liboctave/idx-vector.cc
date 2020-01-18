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

#include <cstdlib>

#include <iostream>

#include "Range.h"
#include "boolNDArray.h"
#include "dColVector.h"
#include "dNDArray.h"

#include "idx-vector.h"
#include "lo-error.h"
#include "lo-mappers.h"

#define IDX_VEC_REP idx_vector::idx_vector_rep

IDX_VEC_REP::idx_vector_rep (const IDX_VEC_REP& a)
  : data (0), len (a.len), num_zeros (a.num_zeros), num_ones (a.num_ones),
    max_val (a.max_val), min_val (a.min_val),
    frozen_at_z_len (a.frozen_at_z_len), frozen_len (a.frozen_len),
    colon (a.colon), one_zero (a.one_zero), initialized (a.initialized),
    frozen (a.frozen), colon_equiv_checked (a.colon_equiv_checked),
    colon_equiv (a.colon_equiv), orig_dims (a.orig_dims)
{
  if (len > 0)
    {
      data = new int [len];
      for (int i = 0; i < len; i++)
	data[i] = a.data[i];
    }
}

static inline int
tree_to_mat_idx (double x, bool& conversion_error)
{
  int retval = -1;

  conversion_error = false;

  if (D_NINT (x) != x)
    {
      (*current_liboctave_error_handler)
	("expecting integer index, found %f", x);

      conversion_error = true;
    }
  else
    retval = static_cast<int> (x - 1);

  return retval;
}

static inline int
tree_to_mat_idx (int i)
{
  return i - 1;
}

static inline bool
idx_is_inf_or_nan (double x)
{
  bool retval = false;

  if (xisnan (x))
    {
      (*current_liboctave_error_handler) ("NaN invalid as index");
      retval = true;
    }
  else if (xisinf (x))
    {
      (*current_liboctave_error_handler) ("Inf invalid as index");
      retval = true;
    }

  return retval;
}

IDX_VEC_REP::idx_vector_rep (const ColumnVector& v)
  : data (0), len (v.length ()), num_zeros (0), num_ones (0), max_val (0),
    min_val (0), count (1), frozen_at_z_len (0), frozen_len (0),
    colon (0), one_zero (0), initialized (0), frozen (0),
    colon_equiv_checked (0), colon_equiv (0), orig_dims (len, 1)
{
  if (len == 0)
    {
      initialized = 1;
      return;
    }
  else
    {
      data = new int [len];

      bool conversion_error = false;

      for (int i = 0; i < len; i++)
	{
	  double d = v.elem (i);

	  if (idx_is_inf_or_nan (d))
	    return;
	  else
	    data[i] = tree_to_mat_idx (d, conversion_error);

	  if (conversion_error)
	    return;
	}
    }

  init_state ();
}

IDX_VEC_REP::idx_vector_rep (const NDArray& nda)
  : data (0), len (nda.length ()), num_zeros (0), num_ones (0),
    max_val (0), min_val (0), count (1), frozen_at_z_len (0),
    frozen_len (0), colon (0), one_zero (0), initialized (0),
    frozen (0), colon_equiv_checked (0), colon_equiv (0),
    orig_dims (nda.dims ())
{
  if (len == 0)
    {
      initialized = 1;
      return;
    }
  else
    {
      int k = 0;
      data = new int [len];

      bool conversion_error = false;

      for (int i = 0; i < len; i++)
	{
	  double d = nda.elem (i);

	  if (idx_is_inf_or_nan (d))
	    return;
	  else
	    data[k++] = tree_to_mat_idx (d, conversion_error);

	  if (conversion_error)
	    return;
	}
    }

  init_state ();
}

IDX_VEC_REP::idx_vector_rep (const Range& r)
  : data (0), len (r.nelem ()), num_zeros (0), num_ones (0),
    max_val (0), min_val (0), count (1), frozen_at_z_len (0),
    frozen_len (0), colon (0), one_zero (0), initialized (0),
    frozen (0), colon_equiv_checked (0), colon_equiv (0),
    orig_dims (1, len)
{
  if (len < 0)
    {
      (*current_liboctave_error_handler) ("invalid range used as index");
      return;
    }
  else if (len == 0)
    {
      initialized = 1;
      return;
    }

  double b = r.base ();
  double step = r.inc ();

  data = new int [len];

  bool conversion_error = false;

  for (int i = 0; i < len; i++)
    {
      double val = b + i * step;

      if (idx_is_inf_or_nan (val))
	return;
      else
	data[i] = tree_to_mat_idx (val, conversion_error);

      if (conversion_error)
	return;
    }

  init_state ();
}

IDX_VEC_REP::idx_vector_rep (double d)
  : data (0), len (1), num_zeros (0), num_ones (0),
    max_val (0), min_val (0), count (1), frozen_at_z_len (0),
    frozen_len (0), colon (0), one_zero (0), initialized (0),
    frozen (0), colon_equiv_checked (0), colon_equiv (0),
    orig_dims (1, 1)
{
  if (idx_is_inf_or_nan (d))
    return;
  else
    {
      data = new int [len];

      bool conversion_error = false;

      data[0] = tree_to_mat_idx (d, conversion_error);

      if (conversion_error)
	return;
    }

  init_state ();
}

IDX_VEC_REP::idx_vector_rep (int i)
  : data (0), len (1), num_zeros (0), num_ones (0),
    max_val (0), min_val (0), count (1), frozen_at_z_len (0),
    frozen_len (0), colon (0), one_zero (0), initialized (0),
    frozen (0), colon_equiv_checked (0), colon_equiv (0),
    orig_dims (1, 1)
{
  data = new int [len];

  data[0] = tree_to_mat_idx (i);

  init_state ();
}

IDX_VEC_REP::idx_vector_rep (char c)
  : data (0), len (0), num_zeros (0), num_ones (0),
    max_val (0), min_val (0), count (1), frozen_at_z_len (0),
    frozen_len (0), colon (1), one_zero (0), initialized (0),
    frozen (0), colon_equiv_checked (0), colon_equiv (0),
    orig_dims (0, 0)
{
  assert (c == ':');

  init_state ();
}

IDX_VEC_REP::idx_vector_rep (bool b)
  : data (0), len (1), num_zeros (0), num_ones (0),
    max_val (0), min_val (0), count (1), frozen_at_z_len (0),
    frozen_len (0), colon (0), one_zero (1), initialized (0),
    frozen (0), colon_equiv_checked (0), colon_equiv (0),
    orig_dims (1, 1)
{
  data = new int [len];

  data[0] = tree_to_mat_idx (b);

  init_state ();
}

IDX_VEC_REP::idx_vector_rep (const boolNDArray& bnda)
  : data (0), len (bnda.length ()), num_zeros (0), num_ones (0),
    max_val (0), min_val (0), count (1), frozen_at_z_len (0),
    frozen_len (0), colon (0), one_zero (1), initialized (0),
    frozen (0), colon_equiv_checked (0), colon_equiv (0),
    orig_dims (bnda.dims ())
{
  if (len == 0)
    {
      initialized = 1;
      return;
    }
  else
    {
      int k = 0;
      data = new int [len];

      for (int i = 0; i < len; i++)
	data[k++] = tree_to_mat_idx (bnda.elem (i));
    }

  init_state ();
}

IDX_VEC_REP&
IDX_VEC_REP::operator = (const IDX_VEC_REP& a)
{
  if (this != &a)
    {
      delete [] data;
      len = a.len;
      data = new int [len];
      for (int i = 0; i < len; i++)
	data[i] = a.data[i];

      num_zeros = a.num_zeros;
      num_ones = a.num_ones;
      max_val = a.max_val;
      min_val = a.min_val;
      frozen_at_z_len = a.frozen_at_z_len;
      frozen_len = a.frozen_len;
      colon = a.colon;
      one_zero = a.one_zero;
      initialized = a.initialized;
      frozen = a.frozen;
      colon_equiv_checked = a.colon_equiv_checked;
      colon_equiv = a.colon_equiv;
      orig_dims = a.orig_dims;
    }

  return *this;
}

void
IDX_VEC_REP::init_state (void)
{
  num_zeros = 0;
  num_ones = 0;

  if (colon)
    {
      min_val = 0;
      max_val = 0;
    }
  else
    {
      min_val = max_val = data[0];

      int i = 0;
      do
	{
	  if (data[i] == -1)
	    num_zeros++;
	  else if (data[i] == 0)
	    num_ones++;

	  if (data[i] > max_val)
	    max_val = data[i];

	  if (data[i] < min_val)
	    min_val = data[i];
	}
      while (++i < len);
    }

  initialized = 1;
}

void
IDX_VEC_REP::maybe_convert_one_zero_to_idx (int z_len)
{
  if (one_zero && (z_len == len || z_len == 0))
    {
      if (num_ones == 0)
	{
	  len = 0;
	  max_val = 0;
	  min_val = 0;
	  delete [] data;
	  data = 0;
	}
      else
	{
	  assert (num_ones + num_zeros == len);

	  int *new_data = new int [num_ones];
	  int k = 0;
	  for (int i = 0; i < len; i++)
	    if (data[i] == 0)
	      new_data[k++] = i;

	  delete [] data;
	  len = num_ones;
	  data = new_data;

	  min_val = max_val = data[0];

	  int i = 0;
	  do
	    {
	      if (data[i] > max_val)
		max_val = data[i];

	      if (data[i] < min_val)
		min_val = data[i];
	    }
	  while (++i < len);
	}
    }
}

int
IDX_VEC_REP::checkelem (int n) const
{
  if (n < 0 || n >= len)
    {
      (*current_liboctave_error_handler) ("idx-vector: index out of range");
      return 0;
    }

  return elem (n);
}

static inline int
intcmp (const void *ii, const void *jj)
{
  return (*(static_cast<const int *> (ii)) - *(static_cast<const int *> (jj)));
}

static inline void
sort_data (int *d, int l)
{
  qsort (d, l, sizeof (int), intcmp);
}

static inline int
make_uniq (int *d, int l)
{
  if (l < 2)
    return l;

  int k = 0;
  for (int ii = 1; ii < l; ii++)
    {
      if (d[ii] != d[k])
	{
	  k++;
	  d[k] = d[ii];
	}
    }
  return k+1;
}

static inline int *
copy_data (const int *d, int l)
{
  int *new_data = new int [l];

  for (int ii = 0; ii < l; ii++)
    new_data[ii] = d[ii];

  return new_data;
}

int
IDX_VEC_REP::is_colon_equiv (int n, int sort_uniq)
{
  if (! colon_equiv_checked)
    {
      if (colon)
	{
	  colon_equiv = 1;
	}
      else if (len > 1)
	{
	  if (one_zero)
	    {
	      colon_equiv = (len == n && ones_count () == n);
	    }
	  else if (sort_uniq)
	    {
	      int *tmp_data = copy_data (data, len);

	      sort_data (tmp_data, len);

	      int tmp_len = make_uniq (tmp_data, len);

	      colon_equiv = (tmp_len == n
			     && tmp_data[0] == 0
			     && tmp_data[tmp_len-1] == tmp_len - 1);

	      delete [] tmp_data;
	    }
	  else
	    {
	      if (len == n)
		{
		  colon_equiv = 1;

		  for (int ii = 0; ii < n; ii++)
		    if (data[ii] != ii)
		      {
			colon_equiv = 0;
			break;
		      }
		}
	    }
	}
      else
	colon_equiv = (len == n && (n == 0 || (n == 1 && data[0] == 0)));

      colon_equiv_checked = 1;
    }

  return colon_equiv;
}

void
IDX_VEC_REP::sort (bool uniq)
{
  if (len > 1)
    {
      sort_data (data, len);

      if (uniq)
	len = make_uniq (data, len);
    }
}

void
IDX_VEC_REP::shorten (int n)
{
  if (n > 0 && n <= len)
    len = n;
  else
    (*current_liboctave_error_handler)
      ("idx_vector::shorten: internal error!");
}

std::ostream&
IDX_VEC_REP::print (std::ostream& os) const
{
  for (int ii = 0; ii < len; ii++)
    os << data[ii] << "\n";
  return os;
}

int
IDX_VEC_REP::freeze (int z_len, const char *tag, bool resize_ok,
		     bool warn_resize)
{
  if (frozen)
    return frozen_len;

  frozen_len = -1;

  if (colon)
    frozen_len = z_len;
  else
    {
      if (len == 0)
	frozen_len = 0;
      else
	{
	  maybe_convert_one_zero_to_idx (z_len);

	  max_val = max ();
	  min_val = min ();

	  if (min_val < 0)
	    {
	      if (tag)
		(*current_liboctave_error_handler)
		  ("invalid %s index = %d", tag, min_val+1);
	      else
		(*current_liboctave_error_handler)
		  ("invalid index = %d", min_val+1);

	      initialized = 0;
	    }
	  else if (! resize_ok && max_val >= z_len)
	    {
	      if (tag)
		(*current_liboctave_error_handler)
		  ("invalid %s index = %d", tag, max_val+1);
	      else
		(*current_liboctave_error_handler)
		  ("invalid index = %d", max_val+1);

	      initialized = 0;
	    }
	  else
	    {
	      if (warn_resize && max_val >= z_len)
		{
		  if (tag)
		    (*current_liboctave_error_handler)
		      ("resizing object with %s index = %d out of bounds",
		       tag, max_val+1);
		  else
		    (*current_liboctave_error_handler)
		      ("resizing object with index = %d out of bounds",
		       max_val+1);
		}

	      frozen_len = length (z_len);
	    }
	}
    }

  frozen = 1;

  frozen_at_z_len = z_len ? z_len : len;

  return frozen_len;
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
