## Copyright (C) 1995, 1996, 1997  Friedrich Leisch
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
## @deftypefn {Function File} {} arma_rnd (@var{a}, @var{b}, @var{v}, @var{t}, @var{n})
## Return a simulation of the ARMA model
##
## @example
## x(n) = a(1) * x(n-1) + ... + a(k) * x(n-k)
##      + e(n) + b(1) * e(n-1) + ... + b(l) * e(n-l)
## @end example
##
## @noindent
## in which @var{k} is the length of vector @var{a}, @var{l} is the
## length of vector @var{b} and @var{e} is gaussian white noise with
## variance @var{v}.  The function returns a vector of length @var{t}.
##
## The optional parameter @var{n} gives the number of dummy
## @var{x}(@var{i}) used for initialization, i.e., a sequence of length
## @var{t}+@var{n} is generated and @var{x}(@var{n}+1:@var{t}+@var{n})
## is returned.  If @var{n} is omitted, @var{n} = 100 is used. 
## @end deftypefn

## Author: FL <Friedrich.Leisch@ci.tuwien.ac.at>
## Description: Simulate an ARMA process

function x = arma_rnd (a, b, v, t, n)

  unwind_protect
    orig_listelemok = empty_list_elements_ok;
    empty_list_elements_ok = "true";

    if (nargin == 4)
      n = 100;
    elseif (nargin == 5)
      if (!is_scalar (t))
        error ("arma_rnd: n must be a scalar");
      endif
    else
      usage ("arma_rnd (a, b, v, t, n)");
    endif

    if ((min (size (a)) > 1) || (min (size (b)) > 1))
      error ("arma_rnd: a and b must not be matrices");
    endif

    if (!is_scalar (t))
      error ("arma_rnd: t must be a scalar");
    endif

    ar = length (a);
    br = length (b);

    a = reshape (a, ar, 1);
    b = reshape (b, br, 1);

    a = [1; -a];                        # apply our notational convention
    b = [1; b];

    n = min (n, ar + br);

    e = sqrt (v) * randn (t + n, 1);

    x = filter (b, a, e);
    x = x(n + 1 : t + n);

  unwind_protect_cleanup

    empty_list_elements_ok = orig_listelemok;

  end_unwind_protect

endfunction
