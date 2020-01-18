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
## @deftypefn {Function File} {[@var{a}, @var{b}, @var{c}, @var{d}, @var{tsam}, @var{n}, @var{nz}, @var{stname}, @var{inname}, @var{outname}, @var{yd}] =} sys2ss (@var{sys})
## Extract state space representation from system data structure.
##
## @strong{Inputs}
## @var{sys} system data structure
##
## @strong{Outputs}
## @table @var
## @item a
## @itemx b
## @itemx c
## @itemx d
## state space matrices for sys
##
## @item tsam
## sampling time of sys (0 if continuous)
##
## @item n
## @itemx nz
## number of continuous, discrete states (discrete states come
## last in state vector @var{x})
##
## @item stname
## @itemx inname
## @itemx outname
## signal names (lists of strings);  names of states,
## inputs, and outputs, respectively
##
## @item yd
## binary vector; @var{yd}(@var{ii}) is 1 if output @var{y}(@var{ii})$
## is discrete (sampled); otherwise  @var{yd}(@var{ii}) 0.
##
## @end table
## A warning massage is printed if the system is a mixed
## continuous and discrete system
##
## @strong{Example}
## @example
## octave:1> sys=tf2sys([1 2],[3 4 5]);
## octave:2> [a,b,c,d] = sys2ss(sys)
## a =
##    0.00000   1.00000
##   -1.66667  -1.33333
## b =
##   0
##   1
## c = 0.66667  0.33333
## d = 0
## @end example
## @end deftypefn

## Author: David Clem
## Created: August 19, 1994
## Updates by John Ingram July 14, 1996

function [a, b, c, d, tsam, n, nz, stname, inname, outname, yd] = sys2ss (sys)

  if(nargin != 1)
    usage("[a,b,c,d,tsam,n,nz,stname,inname,outname,yd] = sys2ss(sys)")
  endif

  if (nargout > 11)
    warning(["sys2ss: ",num2str(nargout)," out arguments exceeds max=11"])
    usage("[a,b,c,d,tsam,n,nz,stname,inname,outname,yd] = sys2ss(sys)")
  endif

  if( ! isstruct(sys) )
    error("input argument must be a system data structure");
  endif

  sys = sysupdate(sys,"ss");        # make sure state space data is there
  [n,nz,m,p] = sysdimensions(sys);
  [stname,inname,outname,yd] = sysgetsignals(sys);
  tsam = sysgettsam(sys);

  cont = sum(yd == 0) + n;
  dig = sum(yd != 0) + nz + tsam;
  if(cont*dig)
    warning("sys2ss: input system is mixed continuous/discrete");
  endif

  a = sys.a;
  b = sys.b;
  c = sys.c;
  d = sys.d;

endfunction

