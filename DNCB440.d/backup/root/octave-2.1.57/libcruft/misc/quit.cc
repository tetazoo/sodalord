/*

Copyright (C) 2002 John W. Eaton

This file is part of Octave.

Octave is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2, or (at your option) any
later version.

Octave is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with Octave; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <cstring>

#include <new>

#include "quit.h"

void (*octave_interrupt_hook) (void) = 0;
void (*octave_bad_alloc_hook) (void) = 0;

void
octave_throw_interrupt_exception (void)
{
  if (octave_interrupt_hook)
    octave_interrupt_hook ();
    
  throw octave_interrupt_exception ();
}

void
octave_throw_bad_alloc (void)
{
  if (octave_bad_alloc_hook)
    octave_bad_alloc_hook ();
    
  throw std::bad_alloc ();
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
