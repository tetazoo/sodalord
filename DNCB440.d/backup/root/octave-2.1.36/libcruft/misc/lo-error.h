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

#if !defined (octave_liboctave_error_h)
#define octave_liboctave_error_h 1

#ifdef __cplusplus
extern "C" {
#endif

extern void liboctave_fatal (const char *fmt, ...) GCC_ATTR_NORETURN;

extern void liboctave_warning (const char *fmt, ...);

typedef void (*liboctave_error_handler) (const char *, ...);

typedef void (*liboctave_warning_handler) (const char *, ...);

/* Would be nice to make these pointers private, but we want to share
   them among all the liboctave classes. */
extern liboctave_error_handler current_liboctave_error_handler;

extern liboctave_warning_handler current_liboctave_warning_handler;

extern void set_liboctave_error_handler (liboctave_error_handler f);

extern void set_liboctave_warning_handler (liboctave_warning_handler f);

#ifdef __cplusplus
}
#endif

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
