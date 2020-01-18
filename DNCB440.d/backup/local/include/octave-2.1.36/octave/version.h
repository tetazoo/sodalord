/*

Copyright (C) 1996, 1997, 1998 John W. Eaton

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

#if !defined (octave_version_h)
#define octave_version_h 1

#define OCTAVE_VERSION "2.1.36"

#define OCTAVE_COPYRIGHT \
  "Copyright (C) 1996, 1997, 1998, 1999, 2000, 2001, 2002 John W. Eaton."

#define OCTAVE_NAME_AND_VERSION \
  "GNU Octave, version " OCTAVE_VERSION " (" OCTAVE_CANONICAL_HOST_TYPE ")"

#define OCTAVE_COPYING_STATEMENT \
  "This is free software; see the source code for copying conditions."

#define OCTAVE_WARRANTY_STATEMENT \
  "There is ABSOLUTELY NO WARRANTY; not even for MERCHANTIBILITY or\n\
FITNESS FOR A PARTICULAR PURPOSE."

#define OCTAVE_BUGS_STATEMENT \
  "Report bugs to <bug-octave@bevo.che.wisc.edu>."

#define OCTAVE_NAME_VERSION_AND_COPYRIGHT \
  OCTAVE_NAME_AND_VERSION ".\n" \
  OCTAVE_COPYRIGHT

#define OCTAVE_NAME_VERSION_COPYRIGHT_COPYING_AND_WARRANTY \
  OCTAVE_NAME_VERSION_AND_COPYRIGHT "\n" \
  OCTAVE_COPYING_STATEMENT "\n" \
  OCTAVE_WARRANTY_STATEMENT

#define X_OCTAVE_NAME_VERSION_COPYRIGHT_COPYING_WARRANTY_AND_BUGS(ARG) \
  OCTAVE_NAME_VERSION_COPYRIGHT_COPYING_AND_WARRANTY \
  ARG \
  "\n\n" \
  OCTAVE_BUGS_STATEMENT

#define OCTAVE_NAME_VERSION_COPYRIGHT_COPYING_WARRANTY_AND_BUGS \
  X_OCTAVE_NAME_VERSION_COPYRIGHT_COPYING_WARRANTY_AND_BUGS ("")

#define OCTAVE_STARTUP_MESSAGE \
  X_OCTAVE_NAME_VERSION_COPYRIGHT_COPYING_WARRANTY_AND_BUGS \
    ("  For details, type `warranty'.")

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
