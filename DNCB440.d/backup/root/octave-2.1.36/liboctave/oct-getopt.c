/*

Copyright (C) 2000 John W. Eaton

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

#include "getopt.h"

int
octave_getopt (int argc, char *const *argv, const char *optstring)
{
  return getopt (argc, argv, optstring);
}

int
octave_getopt_long (int argc, char *const *argv, const char *options,
		    const struct option *long_options, int *opt_index)
{
  return getopt_long (argc, argv, options, long_options, opt_index);
}


/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
