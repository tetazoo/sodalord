## Copyright (C) 1993, 1994, 1995 Auburn University.  All rights reserved.
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
## @deftypefn {Function File} {} are (@var{a}, @var{b}, @var{c}, @var{opt})
## Solve the algebraic Riccati equation
## @iftex
## @tex
## $$
## A^TX + XA - XBX + C = 0
## $$
## @end tex
## @end iftex
## @ifinfo
## @example
## a' * x + x * a - x * b * x + c = 0
## @end example
## @end ifinfo
##
## @strong{Inputs}
## @noindent
## for identically dimensioned square matrices
## @table @var
## @item a
## @var{n}x@var{n} matrix.
## @item b
##   @var{n}x@var{n} matrix or @var{n}x@var{m} matrix; in the latter case
##   @var{b} is replaced by @math{b:=b*b'}.
## @item c
##   @var{n}x@var{n} matrix or @var{p}x@var{m} matrix; in the latter case
##   @var{c} is replaced by @math{c:=c'*c}.
## @item opt
## (optional argument; default = @code{"B"}):
## String option passed to @code{balance} prior to ordered Schur decomposition.
## @end table
##
## @strong{Outputs}
## @var{x}: solution of the ARE.
##
## @strong{Method}
## Laub's Schur method (IEEE Transactions on
## Automatic Control, 1979) is applied to the appropriate Hamiltonian
## matrix.
##
## @end deftypefn
## @seealso{balance and dare}

## Author: A. S. Hodel <a.s.hodel@eng.auburn.edu>
## Created: August 1993

function x = are (a, b, c, opt)

  if (nargin == 3 || nargin == 4)
    if (nargin == 4)
      if (! (strcmp (opt, "N") || strcmp (opt, "P") ...
             || strcmp (opt, "S") || strcmp (opt, "B") ...
             || strcmp (opt, "n") || strcmp (opt, "p") ...
             || strcmp (opt, "s") || strcmp (opt, "b")))
        warning ("are: opt has an invalid value; setting to B");
        opt = "B";
      endif
    else
      opt = "B";
    endif
    if ((n = is_square(a)) == 0)
      error ("are: a is not square");
    endif

    if (is_controllable(a,b) == 0)
      warning ("are: a, b are not controllable");
    endif
    if ((m = is_square (b)) == 0)
      b = b * b';
      m = rows (b);
    endif
    if (is_observable (a, c) == 0)
      warning ("are: a,c are not observable");
    endif
    if ((p = is_square (c)) == 0)
      c = c' * c;
      p = rows (c);
    endif
    if (n != m || n != p)
      error ("are: a, b, c not conformably dimensioned.");
    endif

## Should check for controllability/observability here
## use Boley-Golub (Syst. Contr. Letters, 1984) method, not the
##
##                     n-1
## rank ([ B A*B ... A^   *B]) method

    [d, h] = balance ([a, -b; -c, -a'], opt);
    [u, s] = schur (h, "A");
    u = d * u;
    n1 = n + 1;
    n2 = 2 * n;
    x = u (n1:n2, 1:n) / u (1:n, 1:n);
  else
    usage ("x = are (a, b, c)")
  endif

endfunction
