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
## @deftypefn {Function File} {} probit (@var{p})
## For each component of @var{p}, return the probit (the quantile of the
## standard normal distribution) of @var{p}.
## @end deftypefn

## Written by KH <Kurt.Hornik@ci.tuwien.ac.at> on 1995/02/04
## Description: Probit transformation

function y = probit (p)

  if (nargin == 1)
    y = stdnormal_inv (p);
  else
    usage ("probit (p)");
  endif

endfunction
