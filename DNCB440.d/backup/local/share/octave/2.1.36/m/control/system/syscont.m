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
## @deftypefn {Function File} {[@var{csys}, @var{acd}, @var{ccd}] =} syscont (@var{sys})
## Extract the purely continuous subsystem of an input system.
##
## @strong{Inputs}
## @var{sys} is a system data structure
##
## @strong{Outputs}
## @table @var
## @item csys
## is the purely continuous input/output connections of @var{sys}
## @item acd
## @itemx ccd
## connections from discrete states to continuous states,
## discrete states to continuous outputs, respectively.
##
## returns @var{csys} empty if no continuous/continous path exists
## @end table
## @end deftypefn

## Author: John Ingram <ingraje@eng.auburn.edu>
## Created: August 1996

function [csys, Acd, Ccd] = syscont (sys)

  save_empty = empty_list_elements_ok;
  empty_list_elements_ok = 1;

  if (nargin != 1)
    usage("[csys,Acd,Ccd,Dcd] = syscont(sys)");
  elseif (!is_struct(sys))
    error("sys must be in system data structure form");
  endif

  sys = sysupdate (sys, "ss");
  [n_tot, st_c, st_d, y_c, y_d] = __syscont_disc__ (sys);        # get ranges

  ## assume there's nothing there; build partitions as appropriate
  Acc = Acd = Bcc = Ccc = Ccd = Dcc = [];

  if(isempty(st_c) & isempty(y_c))
    error("syscont: expecting continous states and/or continous outputs");
  elseif (isempty(st_c))
    warning("syscont: no continuous states");
  elseif(isempty(y_c))
    warning("syscont: no continuous outputs");
  endif

  [sys_a, sys_b, sys_c, sys_d ] = sys2ss(sys);
  [sys_stname, sys_inname, sys_outname] = sysgetsignals(sys);
  [sys_n, sys_nz, sys_m, sys_p] = sysdimensions(sys);
  if(!isempty(st_c))
    Acc = sys_a(st_c,st_c);
    stname = sys_stname(st_c);
    Bcc = sys_b(st_c,:);
    Ccc = sys_c(y_c,st_c);
    Acd = sys_a(st_c,st_d);
  else
    stname=[];
  endif
  outname = sys_outname(y_c);
  Dcc = sys_d(y_c,:);
  Ccd = sys_c(y_c,st_d);
  inname = sys_inname;

  csys = ss2sys(Acc,Bcc,Ccc,Dcc,0,sys_n,0,stname,inname,outname);

  empty_list_elements_ok = save_empty;

endfunction
