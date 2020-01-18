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
## @deftypefn {Function File} {} empirical_cdf (@var{x}, @var{data})
## For each element of @var{x}, compute the cumulative distribution
## function (CDF) at @var{x} of the empirical distribution obtained from
## the univariate sample @var{data}.
## @end deftypefn

## Author: KH <Kurt.Hornik@ci.tuwien.ac.at>
## Description: CDF of the empirical distribution

function cdf = empirical_cdf (x, data)

  if (! is_vector (data))
    error ("empirical_cdf: data must be a vector");
  endif

  cdf = discrete_cdf (x, data, ones (size (data)) / length (data));

endfunction
