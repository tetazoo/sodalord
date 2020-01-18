## Copyright (C) 1998 Auburn University.  All rights reserved.
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
## @deftypefn {Function File} {[@var{tvals}, @var{plist}] =} dre (@var{sys}, @var{q}, @var{r}, @var{qf}, @var{t0}, @var{tf}, @var{ptol}, @var{maxits});
## Solve the differential Riccati equation
## @ifinfo
## @example
##   -d P/dt = A'P + P A - P B inv(R) B' P + Q
##   P(tf) = Qf
## @end example
## @end ifinfo
## @iftex
## @tex
## $$ -{dP \over dt} = A^T P+PA-PBR^{-1}B^T P+Q $$
## $$ P(t_f) = Qf $$
## @end tex
## @end iftex
## for the LTI system sys.  Solution of standard LTI
## state feedback optimization
## @ifinfo
## @example
##   min \int_@{t_0@}^@{t_f@} x' Q x + u' R u dt + x(t_f)' Qf x(t_f)
## @end example
## @end ifinfo
## @iftex
## @tex
## $$ \min \int_{t_0}^{t_f} x^T Q x + u^T R u dt + x(t_f)^T Qf x(t_f) $$
## @end tex
## @end iftex
## optimal input is
## @ifinfo
## @example
##   u = - inv(R) B' P(t) x
## @end example
## @end ifinfo
## @iftex
## @tex
## $$ u = - R^{-1} B^T P(t) x $$
## @end tex
## @end iftex
## @strong{Inputs}
## @table @var
## @item sys
## continuous time system data structure
## @item q
## state integral penalty
## @item r
## input integral penalty
## @item qf
## state terminal penalty
## @item t0
## @itemx tf
## limits on the integral
## @item ptol
## tolerance (used to select time samples; see below); default = 0.1
## @item maxits
## number of refinement iterations (default=10)
## @end table
## @strong{Outputs}
## @table @var
## @item tvals
## time values at which @var{p}(@var{t}) is computed
## @item plist
## list values of @var{p}(@var{t}); nth (@var{plist}, @var{ii})
## is @var{p}(@var{tvals}(@var{ii})).
##
## @item tvals
## @example
## is selected so that || nth(Plist,ii) - nth(Plist,ii-1) || < Ptol
## for ii=2:length(tvals)
## @end example
## @end table
## @end deftypefn

function [tvals, Plist] = dre (sys, Q, R, Qf, t0, tf, Ptol, maxits)

  if(nargin < 6 | nargin > 8 | nargout != 2)
    usage("[tvals,Plist] = dre(sys,Q,R,Qf,t0,tf{,Ptol})");
  elseif(!is_struct(sys))
    error("sys must be a system data structure")
  elseif(is_digital(sys))
    error("sys must be a continuous time system")
  elseif(!is_matrix(Q) | !is_matrix(R) | !is_matrix(Qf))
    error("Q, R, and Qf must be matrices.");
  elseif(!is_scalar(t0) | !is_scalar(tf))
    error("t0 and tf must be scalars")
  elseif(t0 >= tf)              error("t0=%e >= tf=%e",t0,tf);
  elseif(nargin == 6)           Ptol = 0.1;
  elseif(!is_scalar(Ptol))      error("Ptol must be a scalar");
  elseif(Ptol <= 0)             error("Ptol must be positive");
  endif

  if(nargin < 8) maxits = 10;
  elseif(!is_scalar(maxits))    error("maxits must be a scalar");
  elseif(maxits <= 0)           error("maxits must be positive");
  endif
  maxits = ceil(maxits);

  [aa,bb] = sys2ss(sys);
  nn = sysdimensions(sys,"cst");
  mm = sysdimensions(sys,"in");
  pp = sysdimensions(sys,"out");

  if(size(Q) != [nn, nn])
    error("Q(%dx%d); sys has %d states",rows(Q),columns(Q),nn);
  elseif(size(Qf) != [nn, nn])
    error("Qf(%dx%d); sys has %d states",rows(Qf),columns(Qf),nn);
  elseif(size(R) != [mm, mm])
    error("R(%dx%d); sys has %d inputs",rows(R),columns(R),mm);
  endif

  ## construct Hamiltonian matrix
  H = [aa , -(bb/R)*bb' ; -Q, -aa'];

  ## select time step to avoid numerical overflow
  fast_eig = max(abs(eig(H)));
  tc = log(10)/fast_eig;
  nst = ceil((tf-t0)/tc);
  tvals = -linspace(-tf,-t0,nst);
  Plist = list(Qf);
  In = eye(nn);
  n1 = nn+1;
  n2 = nn+nn;
  done = 0;
  while(!done)
    done = 1;      # assume this pass will do the job
    ## sort time values in reverse order
    tvals = -sort(-tvals);
    tvlen = length(tvals);
    maxerr = 0;
    ## compute new values of P(t); recompute old values just in case
    for ii=2:tvlen
      uv_i_minus_1 = [ In ; nth(Plist,ii-1) ];
      delta_t = tvals(ii-1) - tvals(ii);
      uv = expm(-H*delta_t)*uv_i_minus_1;
      Qi = uv(n1:n2,1:nn)/uv(1:nn,1:nn);
      Plist(ii) = (Qi+Qi')/2;
      ## check error
      Perr = norm(nth(Plist,ii) - nth(Plist,ii-1))/norm(nth(Plist,ii));
      maxerr = max(maxerr,Perr);
      if(Perr > Ptol)
        new_t = mean(tvals([ii,ii-1]));
        tvals = [tvals, new_t];
        done = 0;
      endif
    endfor

    ## check number of iterations
    maxits = maxits - 1;
    done = done+(maxits==0);
  endwhile
  if(maxerr > Ptol)
    warning("dre: \n\texiting with%4d points, max rel chg. =%e, Ptol=%e\n", ...
          tvlen,maxerr,Ptol);
    tvals = tvals(1:length(Plist));
  endif

endfunction
