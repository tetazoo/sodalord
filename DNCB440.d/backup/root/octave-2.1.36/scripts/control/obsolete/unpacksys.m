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

## [a,b,c,d] = unpacksys(sys)
## Obsolete.  Use sys2ss instead.

## Author: David Clem
## Created: August 19, 1994

function [a, b, c, d] = unpacksys (syst)

  warning("unpacksys obsolete; calling sys2ss");
  [a,b,c,d] = sys2ss(syst);

endfunction

