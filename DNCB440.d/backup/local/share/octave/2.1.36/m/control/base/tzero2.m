## Copyright (C) 1993 Auburn University.  All rights reserved.
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
## @deftypefn {Function File} {} tzero2 (@var{a}, @var{b}, @var{c}, @var{d}, @var{bal})
## Compute the transmission zeros of a, b, c, d.
##
## bal = balancing option (see balance); default is "B".
##
## Needs to incorporate @code{mvzero} algorithm to isolate finite zeros; use
## @code{tzero} instead.
## @end deftypefn

## Author: A. S. Hodel <a.s.hodel@eng.auburn.edu>
## Created: August 1993

function zr = tzero2 (a, b, c, d, bal)

  if (nargin == 4)
    bal = "B";
  elseif (nargin != 5)
    error ("tzero: invalid number of arguments");
  endif

  [n, m, p] = abcddim (a, b, c, d);

  if (n > 0 && m > 0 && p > 0)
    if (m != p)
      fprintf (stderr, "tzero: number of inputs,outputs differ.  squaring up");
      if (p > m)
        fprintf (stderr, "       by padding b and d with zeros.");
        b = [b, (zeros (n, p-m))];
        d = [d, (zeros (p, p-m))];
        m = p;
      else
        fprintf (stderr, "       by padding c and d with zeros.");
        c = [c; (zeros (m-p, n))];
        d = [d; (zeros (m-p, m))];
        p = m;
      endif
      fprintf (stderr, "This is a kludge.  Try again with SISO system.");
    endif
    ab = [-a, -b; c, d];
    bb = [(eye (n)), (zeros (n, m)); (zeros (p, n)), (zeros (p, m))];
    [ab,bb] = balance (ab, bb);
    zr = -qz (ab, bb);
  else
    error ("tzero: a, b, c, d not compatible.  exiting");
  endif

endfunction
