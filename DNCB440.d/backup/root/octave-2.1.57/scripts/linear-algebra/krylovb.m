## Copyright (C) 1993, 1998, 1999 A. Scottedward Hodel
##
## This file is part of Octave.
##
## Octave is free software; you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by the
## Free Software Foundation; either version 2, or (at your option) any
## later version.
##
## Octave is distributed in the hope that it will be useful, but WITHOUT
## ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
## FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
## for more details.
##
## You should have received a copy of the GNU General Public License
## along with Octave; see the file COPYING.  If not, write to the Free
## Software Foundation, 59 Temple Place, Suite 330, Boston, MA 02111 USA.

## -*- texinfo -*-
## @deftypefn {Function File} {[@var{u}, @var{ucols}] =} krylovb (@var{a}, @var{v}, @var{k}, @var{eps1}, @var{pflg})
## See @code{krylov}.
## @end deftypefn

function [Uret, Ucols] = krylovb (A, V, k, eps1, pflg)

  switch (nargin)
    case (3)
      [Uret, H, Ucols] = krylov (A, V, k);
    case (4)
      [Uret, H, Ucols] = krylov (A, V, k, eps1);
    case (5)
      [Uret, H, Ucols] = krylov (A, V, k, eps1, pflg);
    otherwise
      usage ("[Uret, Ucols] = krylovb (A, V, k ,eps1, pflg)");
  endswitch

endfunction
