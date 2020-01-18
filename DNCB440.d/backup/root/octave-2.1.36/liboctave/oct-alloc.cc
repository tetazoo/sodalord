/*

Copyright (C) 1996, 1997 John W. Eaton

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

#if defined (__GNUG__)
#pragma implementation
#endif

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <new>

#include "oct-alloc.h"

void *
octave_allocator::alloc (size_t size)
{
  if (size != item_size)
    return ::new char [size];

  if (! head)
    {
      if (! grow ())
	return 0;
    }

  link *tmp = head;
  head = head->next;
  return tmp;
}

void
octave_allocator::free (void *p, size_t size)
{
  if (size != item_size)
    ::delete [] (static_cast<char *> (p));
  else
    {
      link *tmp = static_cast<link *> (p);
      tmp->next = head;
      head = tmp;
    }
}

// Return TRUE for successful allocation, FALSE otherwise.

bool
octave_allocator::grow (void)
{
  bool retval = true;

  char *start = new char [grow_size * item_size];

  if (start)
    {
      char *last = &start[(grow_size - 1) * item_size];

      char *p = start;
      while (p < last)
	{
	  char *next = p + item_size;
	  (X_CAST (link *, p)) -> next = X_CAST (link *, next);
	  p = next;
	}

      (X_CAST (link *, last)) -> next = 0;

      head = X_CAST (link *, start);
    }
  else
    {
      typedef void (*error_handler_function) (void);

      error_handler_function f = std::set_new_handler (0);
      std::set_new_handler (f);

      if (f)
	f ();

      retval = false;
    }

  return retval;
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
