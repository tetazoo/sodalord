## Copyright (C) 1996 Auburn University.  All rights reserved.
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
## @deftypefn {Function File} {} tzero (@var{a}, @var{b}, @var{c}, @var{d}, @var{opt})
## @deftypefnx {Function File} {} tzero (@var{sys}, @var{opt})
## Compute transmission zeros of a continuous
## @example
## .
## x = Ax + Bu
## y = Cx + Du
## @end example
## or discrete
## @example
## x(k+1) = A x(k) + B u(k)
## y(k)   = C x(k) + D u(k)
## @end example
## system.
## @strong{Outputs}
## @table @var
## @item zer
##  transmission zeros of the system
## @item gain
## leading coefficient (pole-zero form) of SISO transfer function
## returns gain=0 if system is multivariable
## @end table
## @strong{References}
## @enumerate
## @item Emami-Naeini and Van Dooren, Automatica, 1982.
## @item Hodel, "Computation of Zeros with Balancing," 1992 Lin. Alg. Appl.
## @end enumerate
## @end deftypefn

## Author: R. Bruce Tenison <btenison@eng.auburn.edu>
## Created: July 4, 1994
## A. S. Hodel Aug 1995: allow for MIMO and system data structures

function [zer, gain] = tzero (A, B, C, D)

  ## get A,B,C,D and Asys variables, regardless of initial form
  if(nargin == 4)
    Asys = ss(A,B,C,D);
  elseif( (nargin == 1) && (! isstruct(A)))
    usage("[zer,gain] = tzero(A,B,C,D) or zer = tzero(Asys)");
  elseif(nargin != 1)
    usage("[zer,gain] = tzero(A,B,C,D) or zer = tzero(Asys)");
  else
    Asys = A;
    [A,B,C,D] = sys2ss(Asys);
  endif

  Ao = Asys;                    # save for leading coefficient
  siso = is_siso(Asys);
  digital = is_digital(Asys);   # check if it's mixed or not

  ## see if it's a gain block
  if(isempty(A))
    zer = [];
    gain = D;
    return;
  endif

  ## First, balance the system via the zero computation generalized eigenvalue
  ## problem balancing method (Hodel and Tiller, Linear Alg. Appl., 1992)

  Asys = __zgpbal__ (Asys); [A,B,C,D] = sys2ss(Asys);   # balance coefficients
  meps = 2*eps*norm ([A, B; C, D], "fro");
  Asys = zgreduce(Asys,meps);  [A, B, C, D] = sys2ss(Asys); # ENVD algorithm
  if(!isempty(A))
    ## repeat with dual system
    Asys = ss(A', C', B', D');   Asys = zgreduce(Asys,meps);

    ## transform back
    [A,B,C,D] = sys2ss(Asys);    Asys = ss(A', C', B', D');
  endif

  zer = [];                     # assume none
  [A,B,C,D] = sys2ss(Asys);
  if( !isempty(C) )
    [W,r,Pi] = qr([C, D]');
    [nonz,ztmp] = zgrownorm(r,meps);
    if(nonz)
      ## We can now solve the generalized eigenvalue problem.
      [pp,mm] = size(D);
      nn = rows(A);
      Afm = [A , B ; C, D] * W';
      Bfm = [eye(nn), zeros(nn,mm); zeros(pp,nn+mm)]*W';

      jdx = (mm+1):(mm+nn);
      Af = Afm(1:nn,jdx);
      Bf = Bfm(1:nn,jdx);
      zer = qz(Af,Bf);
    endif
  endif

  mz = length(zer);
  [A,B,C,D] = sys2ss(Ao);               # recover original system
  ## compute leading coefficient
  if ( (nargout == 2) && siso)
    n = rows(A);
    if ( mz == n)
      gain = D;
    elseif ( mz < n )
      gain = C*(A^(n-1-mz))*B;
    endif
  else
    gain = [];
  endif
endfunction

