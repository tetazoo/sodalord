## Copyright (C) 1996, 1997  Kurt Hornik
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
## @deftypefn {Function File} {[@var{pval}, @var{tsq}] =} hotelling_test_2 (@var{x}, @var{y})
## For two samples @var{x} from multivariate normal distributions with
## the same number of variables (columns), unknown means and unknown
## equal covariance matrices, test the null hypothesis @code{mean
## (@var{x}) == mean (@var{y})}.
##
## Hotelling's two-sample T^2 is returned in @var{tsq}.  Under the null,
##
## @example
## (n_x+n_y-p-1) T^2 / (p(n_x+n_y-2))
## @end example
##
## @noindent
## has an F distribution with @math{p} and @math{n_x+n_y-p-1} degrees of
## freedom, where @math{n_x} and @math{n_y} are the sample sizes and
## @math{p} is the number of variables.
##
## The p-value of the test is returned in @var{pval}.
##
## If no output argument is given, the p-value of the test is displayed.
## @end deftypefn

## Author: KH <Kurt.Hornik@ci.tuwien.ac.at>
## Description: Compare means of two multivariate normals

function [pval, Tsq] = hotelling_test_2 (x, y)

  if (nargin != 2)
    usage ("hotelling_test_2 (x, y)");
  endif

  if (isvector (x))
    n_x = length (x);
    if (! isvector (y))
      error ("hotelling_test_2: if x is a vector, y must also be a vector");
    else
      n_y = length (y);
      p   = 1;
    endif
  elseif (ismatrix (x))
    [n_x, p] = size (x);
    [n_y, q] = size (y);
    if (p != q)
      error ("hotelling_test_2: x and y must have the same number of columns");
    endif
  else
    error ("hotelling_test_2: x and y must be matrices (or vectors)");
  endif

  d    = mean (x) - mean (y);
  S    = ((n_x - 1) * cov (x) + (n_y - 1) * cov (y)) / (n_x + n_y - 2);
  Tsq  = (n_x * n_y / (n_x + n_y)) * d * (S \ d');
  pval = 1 - f_cdf ((n_x + n_y - p - 1) * Tsq / (p * (n_x + n_y - 2)),
                    p, n_x + n_y - p - 1);

  if (nargout == 0)
    printf ("  pval: %g\n", pval);
  endif

endfunction