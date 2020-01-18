## Copyright (C) 1996, 1998 Auburn University.  All rights reserved.
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
## @deftypefn {Function File} {} tf2ss (@var{inputs})
## @format
## Conversion from tranfer function to state-space.
## The state space system
##       .
##       x = Ax + Bu
##       y = Cx + Du
##
## is obtained from a transfer function
##
##                 num(s)
##           G(s)=-------
##                 den(s)
##
## via the function call [a,b,c,d] = tf2ss(num,den).
## The vector 'den' must contain only one row, whereas the vector 'num'
## may contain as many rows as there are outputs of the system 'y'.
## The state space system matrices obtained from this function will be
## in controllable canonical form as described in "Modern Control Theory",
## [Brogan, 1991].
##
##
## @end format
## @end deftypefn

## Author: R. Bruce Tenison <btenison@eng.auburn.edu>
## Created: June 22, 1994
## mod A S Hodel July, Aug  1995

function [a, b, c, d] = tf2ss (num, den)

  if(nargin != 2)        error("tf2ss: wrong number of input arguments")
  elseif(isempty(num))   error("tf2ss: empty numerator");
  elseif(isempty(den))   error("tf2ss: empy denominator");
  elseif(!is_vector(num))
    error(sprintf("num(%dx%d) must be a vector",rows(num),columns(num)));
  elseif(!is_vector(den))
    error(sprintf("den(%dx%d) must be a vector",rows(den),columns(den)));
  endif

  ## strip leading zeros from num, den
  nz = find(num != 0);
  if(isempty(nz)) num = 0;
  else num = num(nz(1):length(num));         endif
  nz = find(den != 0);
  if(isempty(nz)) error("denominator is 0.");
  else den = den(nz(1):length(den));         endif

  ## force num, den to be row vectors
  num = vec(num)';        den = vec(den)';
  nn = length(num);       nd = length(den);
  if(nn > nd) error(sprintf("deg(num)=%d > deg(den)= %d",nn,nd)); endif

   ## Check sizes
   if (nd == 1)      a = []; b = []; c = []; d = num(:,1) / den(1);
   else
    ## Pad num so that length(num) = length(den)
    if (nd-nn > 0) num = [zeros(1,nd-nn), num]; endif

    ## Normalize the numerator and denominator vector w.r.t. the leading
    ## coefficient
    d1 = den(1);    num = num / d1;    den = den(2:nd)/d1;
    sw = nd-1:-1:1;

    ## Form the A matrix
    if(nd > 2)      a = [zeros(nd-2,1),eye(nd-2,nd-2);-den(sw)];
    else            a = -den(sw);                                endif

    ## Form the B matrix
    b = zeros(nd-1,1);           b(nd-1,1) = 1;

    ## Form the C matrix
    c = num(:,2:nd)-num(:,1)*den;        c = c(:,sw);

    ## Form the D matrix
    d = num(:,1);
  endif

endfunction
