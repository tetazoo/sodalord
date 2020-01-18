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
## @deftypefn {Function File} {} rate (@var{n}, @var{p}, @var{v}, @var{l}, @var{method})
## Return the rate of return on an investment of present value @var{v} which
## pays @var{p} in @var{n} consecutive periods.
##
## The optional argument @var{l} may be used to specify an additional
## lump-sum payment made at the end of @var{n} periods.
##
## The optional string argument @var{method} may be used to specify
## whether payments are made at the end (@code{"e"}, default) or at the
## beginning (@code{"b"}) of each period.
## @end deftypefn
## @seealso{pv, pmt, nper, and npv}

## Author: KH <Kurt.Hornik@ci.tuwien.ac.at>
## Description: Rate of return of an investment

function r = rate (n, p, v, l, m)

  if ((nargin < 3) || (nargin > 5))
    usage ("rate (n, p, v, l, method)");
  endif

  if (! (is_scalar (n) && (n > 0)))
    error ("rate: n must be a positive scalar");
  elseif (! is_scalar (p))
    error ("rate: p must be a scalar");
  elseif (! is_scalar (v))
    error ("rate: p must be a scalar");
  endif

  if (nargin == 5)
    if (! isstr (m))
      error ("rate: `method' must be a string");
    endif
  elseif (nargin == 4)
    if (isstr (l))
      m = l;
      l = 0;
    else
      m = "e";
    endif
  else
    l = 0;
    m = "e";
  endif

  if (! is_scalar (l))
    error ("rate: l must be a scalar");
  endif

  [r, info] = fsolve (sprintf ("pv (x, %g, %g, %g, \"%s\") - %g",
			       n, p, l, m, v), 0);

endfunction
