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

#if !defined (octave_oct_alloc_h)
#define octave_oct_alloc_h 1

class
octave_allocator
{
public:

  octave_allocator (size_t item_sz, int grow_sz = 256)
    : head (0), grow_size (grow_sz),
      item_size (item_sz > sizeof (link *) ? item_sz : sizeof (link *))
  { }

  // Get an object from the free list, possibly increasing the size of
  // the free list.
  void *alloc (size_t size);

  // Put objects back on the free list.
  void free (void *p, size_t size);

private:

  // Structure for internal free list management.
  struct link { link *next; };

  // Front of the free list.
  link *head;

  // How many objects to get each time we call the global operator new.
  int grow_size;

  // The size of each item on the list (or, if that is smaller than
  // the size of list*, the size of list*.
  size_t item_size;

  // How to grow the free list.
  bool grow (void);
};

#define DECLARE_OCTAVE_ALLOCATOR \
  public: \
    void *operator new (size_t size) { return allocator.alloc (size); } \
    void operator delete (void *p, size_t size) { allocator.free (p, size); } \
  private: \
    static octave_allocator allocator;

#define DEFINE_OCTAVE_ALLOCATOR(t) \
  octave_allocator t::allocator (sizeof (t))

#define DEFINE_OCTAVE_ALLOCATOR2(t, s) \
  octave_allocator t::allocator (sizeof (t), s)

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
