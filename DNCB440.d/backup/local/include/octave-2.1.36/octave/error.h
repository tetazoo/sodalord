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

#if !defined (octave_error_h)
#define octave_error_h 1

#include <strstream>

#define panic_impossible() \
  panic ("impossible state reached in file `%s' at line %d", \
	 __FILE__, __LINE__)

extern void message (const char *name, const char *fmt, ...);
extern void usage (const char *fmt, ...);
extern void warning (const char *fmt, ...);
extern void error (const char *fmt, ...);
extern void parse_error (const char *fmt, ...);
extern void panic (const char *fmt, ...) GCC_ATTR_NORETURN;

// Current error state.
extern int error_state;

// Current warning state.
extern int warning_state;

// Tell the error handler whether to print messages, or just store
// them for later.  Used for handling errors in eval() and
// the `unwind_protect' statement.
extern bool buffer_error_messages;

// TRUE means error messages are turned off.
extern bool discard_error_messages;

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
