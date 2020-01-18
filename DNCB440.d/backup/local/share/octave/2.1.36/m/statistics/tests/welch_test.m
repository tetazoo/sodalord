## Copyright (C) 1995, 1996, 1997  Kurt Hornik
##
## This file is part of Octave.
##
## Octave is free software; you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2, or (at your option)
## any later version.
##
## Octave is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with Octave; see the file COPYING.  If not, write to the Free
## Software Foundation, 59 Temple Place - Suite 330, Boston, MA
## 02111-1307, USA.

## -*- texinfo -*-
## @deftypefn {Function File} {[@var{pval}, @var{t}, @var{df}] =} welch_test (@var{x}, @var{y}, @var{alt})
## For two samples @var{x} and @var{y} from normal distributions with
## unknown means and unknown and not necessarily equal variances,
## perform a Welch test of the null hypothesis of equal means.
## Under the null, the test statistic t approximately follows a Student
## distribution with df degrees of freedom.
##
## With the optional argument string @var{alt}, the alternative of
## interest can be selected.  If @var{alt} is @code{"!="} or
## @code{"<>"}, the null is tested against the two-sided alternative
## @code{mean (@var{x}) != @var{m}}.  If @var{alt} is @code{">"}, the
## one-sided alternative mean(x) > @var{m} is considered.  Similarly for
## @code{"<"}, the one-sided alternative mean(x) < @var{m} is
## considered.  The default is the two-sided case.
##
## The p-value of the test is returned in @var{pval}.
##
## If no output argument is given, the p-value of the test is displayed.
## @end deftypefn

## Author: KH <Kurt.Hornik@ci.tuwien.ac.at>
## Description: Welch two-sample t test

function [pval, t, df] = welch_test (x, y, alt)

  if ((nargin < 2) || (nargin > 3))
    usage ("[pval, t, df] = welch_test (x, y, alt)");
  endif

  if (! (is_vector (x) && is_vector (y)))
    error ("welch_test: both x and y must be vectors");
  endif

  n_x  = length (x);
  n_y  = length (y);
  mu_x = sum (x) / n_x;
  mu_y = sum (y) / n_y;
  v_x  = sumsq (x - mu_x) / (n_x * (n_x - 1));
  v_y  = sumsq (y - mu_y) / (n_y * (n_y - 1));
  c    = v_x / (v_x + v_y);
  df   = 1 / (c^2 / (n_x - 1) + (1 - c)^2 / (n_y - 1));
  t    = (mu_x - mu_y) / sqrt (v_x + v_y);
  cdf  = t_cdf (t, df);

  if (nargin == 2)
    alt  = "!=";
  endif

  if (! isstr (alt))
    error ("welch_test: alt must be a string");
  endif
  if (strcmp (alt, "!=") || strcmp (alt, "<>"))
    pval = 2 * min (cdf, 1 - cdf);
  elseif (strcmp (alt, ">"))
    pval = 1 - cdf;
  elseif (strcmp (alt, "<"))
    pval = cdf;
  else
    error ("welch_test: option %s not recognized", alt);
  endif

  if (nargout == 0)
    printf ("  pval: %g\n", pval);
  endif

endfunction
