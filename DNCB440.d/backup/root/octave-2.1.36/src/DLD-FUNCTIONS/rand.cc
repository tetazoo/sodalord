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

#include <ctime>

#include <string>

#include "f77-fcn.h"
#include "lo-mappers.h"

#include "defun-dld.h"
#include "error.h"
#include "gripes.h"
#include "oct-obj.h"
#include "unwind-prot.h"
#include "utils.h"

// Possible distributions of random numbers.  This was handled with an
// enum, but unwind_protecting that doesn't work so well.
#define uniform_dist 1
#define normal_dist 2

// Current distribution of random numbers.
static int current_distribution = uniform_dist;

// Has the seed been set yet?
static int initialized = 0;

extern "C"
{
  int F77_FUNC (dgennor, DGENNOR) (const double&, const double&,
				  double&);

  int F77_FUNC (dgenunf, DGENUNF) (const double&, const double&,
				  double&);

  int F77_FUNC (setall, SETALL) (const int&, const int&);

  int F77_FUNC (getsd, GETSD) (int&, int&);

  int F77_FUNC (setsd, SETSD) (const int&, const int&);

  int F77_FUNC (setcgn, SETCGN) (const int&);
}

static double
curr_rand_seed (void)
{
  union d2i { double d; int i[2]; };
  union d2i u;
  F77_XFCN (getsd, GETSD, (u.i[0], u.i[1]));
  return u.d;
}

static int
force_to_fit_range (int i, int lo, int hi)
{
  assert (hi > lo && lo >= 0 && hi > lo);

  i = i > 0 ? i : -i;

  if (i < lo)
    i = lo;
  else if (i > hi)
    i = i % hi;

  return i;
}

static void
set_rand_seed (double val)
{
  union d2i { double d; int i[2]; };
  union d2i u;
  u.d = val;
  int i0 = force_to_fit_range (u.i[0], 1, 2147483563);
  int i1 = force_to_fit_range (u.i[1], 1, 2147483399);
  F77_XFCN (setsd, SETSD, (i0, i1));
}

static const char *
curr_rand_dist (void)
{
  if (current_distribution == uniform_dist)
    return "uniform";
  else if (current_distribution == normal_dist)
    return "normal";
  else
    {
      panic_impossible ();
      return 0;
    }
}

// Make the random number generator give us a different sequence every
// time we start octave unless we specifically set the seed.  The
// technique used below will cycle monthly, but it it does seem to
// work ok to give fairly different seeds each time Octave starts.

static void
do_initialization (void)
{
  time_t now;
  struct tm *tm;
 
  time (&now);
  tm = localtime (&now);
 
  int hour = tm->tm_hour + 1;
  int minute = tm->tm_min + 1;
  int second = tm->tm_sec + 1;

  int s0 = tm->tm_mday * hour * minute * second;
  int s1 = hour * minute * second;

  s0 = force_to_fit_range (s0, 1, 2147483563);
  s1 = force_to_fit_range (s1, 1, 2147483399);

  F77_XFCN (setall, SETALL, (s0, s1));

  initialized = 1;
}

static octave_value_list
do_rand (const octave_value_list& args, int nargin)
{
  octave_value_list retval;

  volatile int n = 0;
  volatile int m = 0;

  if (nargin == 0)
    {
      n = 1;
      m = 1;

      goto gen_matrix;
    }
  else if (nargin == 1)
    {
      octave_value tmp = args(0);

      if (tmp.is_string ())
	{
	  std::string s_arg = tmp.string_value ();

	  if (s_arg == "dist")
	    {
	      retval(0) = curr_rand_dist ();
	    }
	  else if (s_arg == "seed")
	    {
	      retval(0) = curr_rand_seed ();
	    }
	  else if (s_arg == "uniform")
	    {
	      current_distribution = uniform_dist;

	      F77_XFCN (setcgn, SETCGN, (uniform_dist));
	    }
	  else if (s_arg == "normal")
	    {
	      current_distribution = normal_dist;

	      F77_XFCN (setcgn, SETCGN, (normal_dist));
	    }
	  else
	    error ("rand: unrecognized string argument");
	}
      else if (tmp.is_scalar_type ())
	{
	  double dval = tmp.double_value ();

	  if (xisnan (dval))
	    {
	      error ("rand: NaN is invalid a matrix dimension");
	    }
	  else
	    {
	      m = n = NINT (tmp.double_value ());

	      if (! error_state)
		goto gen_matrix;
	    }
	}
      else if (tmp.is_range ())
	{
	  Range r = tmp.range_value ();
	  n = 1;
	  m = r.nelem ();
	  goto gen_matrix;
	}
      else if (tmp.is_matrix_type ())
	{
	  // XXX FIXME XXX -- this should probably use the function
	  // from data.cc.

	  Matrix a = args(0).matrix_value ();

	  if (error_state)
	    return retval;

	  n = a.rows ();
	  m = a.columns ();

	  if (n == 1 && m == 2)
	    {
	      n = NINT (a (0, 0));
	      m = NINT (a (0, 1));
	    }
	  else if (n == 2 && m == 1)
	    {
	      n = NINT (a (0, 0));
	      m = NINT (a (1, 0));
	    }
	  else
	    warning ("rand (A): use rand (size (A)) instead");

	  goto gen_matrix;
	}
      else
	{
	  gripe_wrong_type_arg ("rand", tmp);
	  return retval;
	}
    }
  else if (nargin == 2)
    {
      if (args(0).is_string ())
	{
	  if (args(0).string_value () == "seed")
	    {
	      double d = args(1).double_value ();

	      if (! error_state)
		set_rand_seed (d);
	    }
	  else
	    error ("rand: unrecognized string argument");
	}
      else
	{
	  double dval = args(0).double_value ();

	  if (xisnan (dval))
	    {
	      error ("rand: NaN is invalid as a matrix dimension");
	    }
	  else
	    {
	      n = NINT (dval);

	      if (! error_state)
		{
		  m = NINT (args(1).double_value ());

		  if (! error_state)
		    goto gen_matrix;
		}
	    }
	}
    }

  return retval;

 gen_matrix:

  if (n == 0 || m == 0)
    {
      Matrix m;
      retval.resize (1, m);
    }
  else if (n > 0 && m > 0)
    {
      Matrix rand_mat (n, m);

      for (volatile int j = 0; j < m; j++)
	for (volatile int i = 0; i < n; i++)
	  {
	    double val;
	    switch (current_distribution)
	      {
	      case uniform_dist:
		F77_XFCN (dgenunf, DGENUNF, (0.0, 1.0, val));
		rand_mat (i, j) = val;
		break;

	      case normal_dist:
		F77_XFCN (dgennor, DGENNOR, (0.0, 1.0, val));
		rand_mat (i, j) = val;
		break;

	      default:
		panic_impossible ();
		break;
	      }
	  }

      retval(0) = rand_mat;
    }
  else
    error ("rand: invalid negative argument");

  return retval;
}

DEFUN_DLD (rand, args, nargout,
  "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} rand (@var{x})\n\
@deftypefnx {Loadable Function} {} rand (@var{n}, @var{m})\n\
@deftypefnx {Loadable Function} {} rand (@code{\"seed\"}, @var{x})\n\
Return a matrix with random elements uniformly distributed on the\n\
interval (0, 1).  The arguments are handled the same as the arguments\n\
for @code{eye}.  In\n\
addition, you can set the seed for the random number generator using the\n\
form\n\
\n\
@example\n\
rand (\"seed\", @var{x})\n\
@end example\n\
\n\
@noindent\n\
where @var{x} is a scalar value.  If called as\n\
\n\
@example\n\
rand (\"seed\")\n\
@end example\n\
\n\
@noindent\n\
@code{rand} returns the current value of the seed.\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin > 2 || nargout > 1)
    print_usage ("rand");
  else
    {
      if (! initialized)
	do_initialization ();

      retval = do_rand (args, nargin);
    }

  return retval;
}

static void
reset_rand_generator (void *)
{
  F77_XFCN (setcgn, SETCGN, (current_distribution));
}

DEFUN_DLD (randn, args, nargout,
  "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} randn (@var{x})\n\
@deftypefnx {Loadable Function} {} randn (@var{n}, @var{m})\n\
@deftypefnx {Loadable Function} {} randn (@code{\"seed\"}, @var{x})\n\
Return a matrix with normally distributed random elements.  The\n\
arguments are handled the same as the arguments for @code{eye}.  In\n\
addition, you can set the seed for the random number generator using the\n\
form\n\
\n\
@example\n\
randn (\"seed\", @var{x})\n\
@end example\n\
\n\
@noindent\n\
where @var{x} is a scalar value.  If called as\n\
\n\
@example\n\
randn (\"seed\")\n\
@end example\n\
\n\
@noindent\n\
@code{randn} returns the current value of the seed.\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin > 2 || nargout > 1)
    print_usage ("randn");
  else
    {
      if (! initialized)
	do_initialization ();

      unwind_protect::begin_frame ("randn");

      // This relies on the fact that elements are popped from the
      // unwind stack in the reverse of the order they are pushed
      // (i.e. current_distribution will be reset before calling
      // reset_rand_generator()).

      unwind_protect::add (reset_rand_generator, 0);
      unwind_protect_int (current_distribution);

      current_distribution = normal_dist;

      F77_XFCN (setcgn, SETCGN, (normal_dist));

      retval = do_rand (args, nargin);

      unwind_protect::run_frame ("randn");
    }

  return retval;
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
