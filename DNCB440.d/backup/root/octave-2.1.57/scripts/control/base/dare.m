## Copyright (C) 1996, 1997 Auburn University.  All rights reserved.
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
## @deftypefn {Function File} {} dare (@var{a}, @var{b}, @var{q}, @var{r}, @var{opt})
##
## Return the solution, @var{x} of the discrete-time algebraic Riccati
## equation
## @iftex
## @tex
## $$
## A^TXA - X + A^TXB (R + B^TXB)^{-1} B^TXA + Q = 0
## $$
## @end tex
## @end iftex
## @ifinfo
## @example
## a' x a - x + a' x b (r + b' x b)^(-1) b' x a + q = 0
## @end example
## @end ifinfo
## @noindent
##
## @strong{Inputs}
## @table @var
## @item a
## @var{n} by @var{n}.
##
## @item b
## @var{n} by @var{m}.
##
## @item q
## @var{n} by @var{n}, symmetric positive semidefinite, or @var{p} by @var{n}.
## In the latter case @math{q:=q'*q} is used.
##
## @item r
## @var{m} by @var{m}, symmetric positive definite (invertible).
##
## @item opt
## (optional argument; default = @code{"B"}):
## String option passed to @code{balance} prior to ordered @var{QZ} decomposition.
## @end table
##
## @strong{Outputs}
## @var{x} solution of DARE.
##
## @strong{Method}
## Generalized eigenvalue approach (Van Dooren; SIAM J.
##  Sci. Stat. Comput., Vol 2) applied  to the appropriate symplectic pencil.
##
##  See also: Ran and Rodman, "Stable Hermitian Solutions of Discrete
##  Algebraic Riccati Equations," Mathematics of Control, Signals and
##  Systems, Vol 5, no 2 (1992)  pp 165-194.
##
## @end deftypefn
## @seealso{balance and are}

## Author: A. S. Hodel <a.s.hodel@eng.auburn.edu>
## Created: August 1993
## Adapted-By: jwe

function x = dare (a, b, q, r, opt)

  if (nargin == 4 | nargin == 5)
    if (nargin == 5)
      if (opt != "N" || opt != "P" || opt != "S" || opt != "B")
        warning ("dare: opt has an invalid value -- setting to B");
        opt = "B";
      endif
    else
      opt = "B";
    endif

    
    if ((p = issquare (q)) == 0)
      q = q'*q;
    endif

    ##Checking positive definiteness
    if (isdefinite(r)<=0)
      error("dare: r not positive definite");
    end
    if (isdefinite(q)<0)
      error("dare: q not positive semidefinite");
    end


    ## Check r dimensions.
    [n,m] = size(b);
    if ((m1 = issquare (r)) == 0)
      error ("dare: r is not square");
    elseif (m1 != m)
      error ("b,r are not conformable");
    endif

    s1 = [a, zeros(n) ; -q, eye(n)];
    s2 = [eye(n), (b/r)*b' ; zeros(n), a'];
    [c,d,s1,s2] = balance(s1,s2,opt);
    [aa,bb,u,lam] = qz(s1,s2,"S");
    u = d*u;
    n1 = n+1;
    n2 = 2*n;
    x = u (n1:n2, 1:n)/u(1:n, 1:n);
  else
    usage ("x = dare (a, b, q, r {,opt})");
  endif

endfunction
