## Copyright (C) 1996, 1997 John W. Eaton
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
## @deftypefn {Function File} {} perror (@var{name}, @var{num})
## Print the error message for function @var{name} corresponding to the
## error number @var{num}.  This function is intended to be used to print
## useful error messages for those functions that return numeric error
## codes.
## @end deftypefn
## @seealso{strerror}

## Author: jwe

function perror (name, err)

  if (nargin != 2)
    usage ("perror (name, err)");
  else
    printf (strerror (name, err));
  endif

endfunction
