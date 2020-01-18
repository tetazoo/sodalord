/*

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

#if defined (HAVE_FFTW3)

#include <iostream>
#include <vector>

#include "lo-error.h"
#include "oct-fftw.h"
#include "quit.h"

// Helper class to create and cache fftw plans for both 1d and
// 2d. This implementation uses FFTW_ESTIMATE to create the plans,
// which in theory is suboptimal, but provides quite reasonable
// performance.

// Also note that if FFTW_ESTIMATE is not used the planner in FFTW3
// destroys the input and output arrays. So with the form of the
// current code we definitely want FFTW_ESTIMATE!! However, we use any
// wsidom that is available, either in a FFTW3 system wide file or as
// supplied by the user.

// XXX FIXME XXX -- if we can ensure 16 byte alignment in Array<T>
// (<T> *data) the FFTW3 can use SIMD instructions for further
// acceleration.

// Note that it is profitable to store the FFTW3 plans, for small
// ffts.

class
octave_fftw_planner
{
public:

  octave_fftw_planner (void);

  fftw_plan create_plan (int dir, const int rank, const dim_vector dims, 
			 int howmany, int stride, int dist, 
			 const Complex *in, Complex *out);

  fftw_plan create_plan (const int rank, const dim_vector dims, 
			 int howmany, int stride, int dist, 
			 const double *in, Complex *out);

private:

  int plan_flags;

  // XXX FIXME XXX -- perhaps this should be split into two classes?

  // Plan for fft and ifft of complex values
  fftw_plan plan[2];

  // dist
  int d[2];

  // stride
  int s[2];

  // rank
  int r[2];

  // howmany
  int h[2];

  // dims
  dim_vector n[2];

  bool simd_align[2];


  // Plan for fft of real values
  fftw_plan rplan;

  // dist
  int rd;

  // stride
  int rs;

  // rank
  int rr;

  // howmany
  int rh;

  // dims
  dim_vector rn;

  bool rsimd_align;
};

octave_fftw_planner::octave_fftw_planner (void)
{
  plan_flags = FFTW_ESTIMATE;

  plan[0] = plan[1] = 0;
  d[0] = d[1] = s[0] = s[1] = r[0] = r[1] = h[0] = h[1] = 0;
  simd_align[0] = simd_align[1] = false;
  n[0] = n[1] = dim_vector ();

  rplan = 0;
  rd = rs = rr = rh = 0;
  rsimd_align = false;
  rn = dim_vector ();

  // If we have a system wide wisdom file, import it.
  fftw_import_system_wisdom ();
}

#define CHECK_SIMD_ALIGNMENT(x) \
  ((reinterpret_cast<ptrdiff_t> (x)) & 0xF == 0)

fftw_plan
octave_fftw_planner::create_plan (int dir, const int rank,
				  const dim_vector dims, int howmany,
				  int stride, int dist, 
				  const Complex *in, Complex *out)
{
  int which = (dir == FFTW_FORWARD) ? 0 : 1;
  fftw_plan *cur_plan_p = &plan[which];
  bool create_new_plan = false;
  bool ioalign = CHECK_SIMD_ALIGNMENT (in) && CHECK_SIMD_ALIGNMENT (out);

  // Don't create a new plan if we have a non SIMD plan already but
  // can do SIMD.  This prevents endlessly recreating plans if we
  // change the alignment.

  if (plan[which] == 0 || d[which] != dist || s[which] != stride
      || r[which] != rank || h[which] != howmany
      || ((ioalign != simd_align[which]) ? !ioalign : false))
    create_new_plan = true;
  else
    {
      // We still might not have the same shape of array.

      for (int i = 0; i < rank; i++)
	if (dims(i) != n[which](i))
	  {
	    create_new_plan = true;
	    break;
	  }
    }

  if (create_new_plan)
    {
      d[which] = dist;
      s[which] = stride;
      r[which] = rank;
      h[which] = howmany;
      simd_align[which] = ioalign;
      n[which] = dims;

      if (ioalign)
	plan_flags &= ~FFTW_UNALIGNED;
      else
	plan_flags |= FFTW_UNALIGNED;

      if (*cur_plan_p)
	fftw_destroy_plan (*cur_plan_p);

      // Note reversal of dimensions for column major storage in FFTW.

      OCTAVE_LOCAL_BUFFER (int, tmp, rank);

      for (int i = 0, j = rank-1; i < rank; i++, j--)
	tmp[i] = dims(j);

      *cur_plan_p =
	fftw_plan_many_dft (rank, tmp, howmany,
	      reinterpret_cast<fftw_complex *> (const_cast<Complex *> (in)),
	      0, stride, dist, reinterpret_cast<fftw_complex *> (out),
	      0, stride, dist, dir, plan_flags);

      if (*cur_plan_p == 0)
	(*current_liboctave_error_handler) ("Error creating fftw plan");
    }

  return *cur_plan_p;
}
 
fftw_plan
octave_fftw_planner::create_plan (const int rank, const dim_vector dims, 
				  int howmany, int stride, int dist, 
				  const double *in, Complex *out)
{
  fftw_plan *cur_plan_p = &rplan;
  bool create_new_plan = false;
  bool ioalign = CHECK_SIMD_ALIGNMENT (in) && CHECK_SIMD_ALIGNMENT (out);

  // Don't create a new plan if we have a non SIMD plan already but
  // can do SIMD.  This prevents endlessly recreating plans if we
  // change the alignment.

  if (rplan == 0 || rd != dist || rs != stride || rr != rank
      || rh != howmany || ((ioalign != rsimd_align) ? !ioalign : false))
    create_new_plan = true;
  else
    {
      // We still might not have the same shape of array.

      for (int i = 0; i < rank; i++)
	if (dims(i) != rn(i))
	  {
	    create_new_plan = true;
	    break;
	  }
    }

  if (create_new_plan)
    {
      rd = dist;
      rs = stride;
      rr = rank;
      rh = howmany;
      rsimd_align = ioalign;
      rn = dims;

      if (ioalign)
	plan_flags &= ~FFTW_UNALIGNED;
      else
	plan_flags |= FFTW_UNALIGNED;

      if (*cur_plan_p)
	fftw_destroy_plan (*cur_plan_p);

      // Note reversal of dimensions for column major storage in FFTW.

      OCTAVE_LOCAL_BUFFER (int, tmp, rank);

      for (int i = 0, j = rank-1; i < rank; i++, j--)
	tmp[i] = dims(j);

      *cur_plan_p =
	fftw_plan_many_dft_r2c (rank, tmp, howmany,
	      (const_cast<double *> (in)),
	      0, stride, dist, reinterpret_cast<fftw_complex *> (out),
	      0, stride, dist, plan_flags);

      if (*cur_plan_p == 0)
	(*current_liboctave_error_handler) ("Error creating fftw plan");
    }

  return *cur_plan_p;
}

static octave_fftw_planner fftw_planner;

static inline void
convert_packcomplex_1d (Complex *out, size_t nr, size_t nc,
			int stride, int dist)
{
  OCTAVE_QUIT;

  // Fill in the missing data.

  for (size_t i = 0; i < nr; i++)
    for (size_t j = nc/2+1; j < nc; j++)
      out[j*stride + i*dist] = conj(out[(nc - j)*stride + i*dist]);

  OCTAVE_QUIT;
}

static inline void
convert_packcomplex_Nd (Complex *out, const dim_vector &dv)
{
  size_t nc = dv(0);
  size_t nr = dv(1);
  size_t np = (dv.length () > 2 ? dv.numel () / nc / nr : 1);
  size_t nrp = nr * np;
  Complex *ptr1, *ptr2;

  OCTAVE_QUIT;

  // Create space for the missing elements.

  for (size_t i = 0; i < nrp; i++)
    {
      ptr1 = out + i * (nc/2 + 1) + nrp*((nc-1)/2);
      ptr2 = out + i * nc;
      for (size_t j = 0; j < nc/2+1; j++)
	*ptr2++ = *ptr1++;
    }

  OCTAVE_QUIT;

  // Fill in the missing data for the rank = 2 case directly for speed.

  for (size_t i = 0; i < np; i++)
    {
      for (size_t j = 1; j < nr; j++)
	for (size_t k = nc/2+1; k < nc; k++)
	  out[k + (j + i*nr)*nc] = conj(out[nc - k + ((i+1)*nr - j)*nc]);

      for (size_t j = nc/2+1; j < nc; j++)
	out[j + i*nr*nc] = conj(out[(i*nr+1)*nc - j]);
    }

  OCTAVE_QUIT;

  // Now do the permutations needed for rank > 2 cases.

  size_t jstart = dv(0) * dv(1);
  size_t kstep = dv(0);
  size_t nel = dv.numel ();

  for (int inner = 2; inner < dv.length (); inner++) 
    {
      size_t jmax = jstart * dv(inner);
      for (size_t i = 0; i < nel; i+=jmax)
	for (size_t j = jstart, jj = jmax-jstart; j < jj; 
	     j+=jstart, jj-=jstart)
	  for (size_t k = 0; k < jstart; k+= kstep)
	    for (size_t l = nc/2+1; l < nc; l++)
	      {
		Complex tmp = out[i+ j + k + l];
		out[i + j + k + l] =  out[i + jj + k + l];
		out[i + jj + k + l] = tmp;
	      }
      jstart = jmax;
    }

  OCTAVE_QUIT;
}

int
octave_fftw::fft (const double *in, Complex *out, size_t npts, 
		  size_t nsamples, int stride, int dist)
{
  dist = (dist < 0 ? npts : dist);

  dim_vector dv (npts);
  fftw_plan plan = fftw_planner.create_plan (1, dv, nsamples, stride, dist,
					     in, out);

  fftw_execute_dft_r2c (plan, (const_cast<double *>(in)),
			reinterpret_cast<fftw_complex *> (out));

  // Need to create other half of the transform.

  convert_packcomplex_1d (out, nsamples, npts, stride, dist);

  return 0;
}

int
octave_fftw::fft (const Complex *in, Complex *out, size_t npts, 
		  size_t nsamples, int stride, int dist)
{
  dist = (dist < 0 ? npts : dist);

  dim_vector dv (npts);
  fftw_plan plan = fftw_planner.create_plan (FFTW_FORWARD, 1, dv, nsamples,
					     stride, dist, in, out);

  fftw_execute_dft (plan, 
	reinterpret_cast<fftw_complex *> (const_cast<Complex *>(in)),
	reinterpret_cast<fftw_complex *> (out));

  return 0;
}

int
octave_fftw::ifft (const Complex *in, Complex *out, size_t npts, 
		   size_t nsamples, int stride, int dist)
{
  dist = (dist < 0 ? npts : dist);

  dim_vector dv (npts);
  fftw_plan plan = fftw_planner.create_plan (FFTW_BACKWARD, 1, dv, nsamples,
					     stride, dist, in, out);

  fftw_execute_dft (plan, 
	reinterpret_cast<fftw_complex *> (const_cast<Complex *>(in)),
	reinterpret_cast<fftw_complex *> (out));

  const Complex scale = npts;
  for (size_t j = 0; j < nsamples; j++)
    for (size_t i = 0; i < npts; i++)
      out[i*stride + j*dist] /= scale;

  return 0;
}

int
octave_fftw::fftNd (const double *in, Complex *out, const int rank, 
		    const dim_vector &dv)
{
  int dist = 1;
  for (int i = 0; i < rank; i++)
    dist *= dv(i);

  // Fool with the position of the start of the output matrix, so that
  // creating other half of the matrix won't cause cache problems.

  int offset = (dv.numel () / dv(0)) * ((dv(0) - 1) / 2); 
  
  fftw_plan plan = fftw_planner.create_plan (rank, dv, 1, 1, dist,
					     in, out + offset);

  fftw_execute_dft_r2c (plan, (const_cast<double *>(in)),
			reinterpret_cast<fftw_complex *> (out+ offset));

  // Need to create other half of the transform.

  convert_packcomplex_Nd (out, dv);

  return 0;
}

int
octave_fftw::fftNd (const Complex *in, Complex *out, const int rank, 
		    const dim_vector &dv)
{
  int dist = 1;
  for (int i = 0; i < rank; i++)
    dist *= dv(i);

  fftw_plan plan = fftw_planner.create_plan (FFTW_FORWARD, rank, dv, 1, 1,
					     dist, in, out);

  fftw_execute_dft (plan, 
	reinterpret_cast<fftw_complex *> (const_cast<Complex *>(in)),
	reinterpret_cast<fftw_complex *> (out));

  return 0;
}

int
octave_fftw::ifftNd (const Complex *in, Complex *out, const int rank, 
		     const dim_vector &dv)
{
  int dist = 1;
  for (int i = 0; i < rank; i++)
    dist *= dv(i);

  fftw_plan plan = fftw_planner.create_plan (FFTW_BACKWARD, rank, dv, 1, 1,
					     dist, in, out);

  fftw_execute_dft (plan, 
	reinterpret_cast<fftw_complex *> (const_cast<Complex *>(in)),
	reinterpret_cast<fftw_complex *> (out));

  const size_t npts = dv.numel ();
  const Complex scale = npts;
  for (size_t i = 0; i < npts; i++)
    out[i] /= scale;

  return 0;
}

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/

