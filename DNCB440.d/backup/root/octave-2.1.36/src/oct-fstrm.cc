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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <cerrno>
#include <cstring>

#include "error.h"
#include "oct-fstrm.h"

octave_stream
octave_fstream::create (const std::string& nm_arg, std::ios::openmode arg_md,
			oct_mach_info::float_format flt_fmt)
{
  return octave_stream (new octave_fstream (nm_arg, arg_md, flt_fmt));
}

octave_fstream::octave_fstream (const std::string& nm_arg,
				std::ios::openmode arg_md,
				oct_mach_info::float_format flt_fmt)
  : octave_base_stream (arg_md, flt_fmt), nm (nm_arg)
{

#if CXX_ISO_COMPLIANT_LIBRARY

  fs.open (nm.c_str (), arg_md);

#else
  // Override default protection of 0664 so that umask will appear to
  // do the right thing.

  fs.open (nm.c_str (), arg_md, 0666);

#endif

  if (! fs)
    {
      using namespace std;

      error (strerror (errno));
    }
}

// Position a stream at OFFSET relative to ORIGIN.

int
octave_fstream::seek (std::streamoff offset, std::ios::seekdir origin)
{
  int retval = -1;

  if (! fs.bad ())
    {
      fs.clear ();

      std::filebuf *fb = fs.rdbuf ();

      if (fb)
	{
	  fb->pubseekoff (offset, origin);
	  retval = fs.bad () ? -1 : 0;
	}
    }

  return retval;
}

// Return current stream position.

long
octave_fstream::tell (void) const
{
  long retval = -1;

  if (fs)
    {
      std::filebuf *fb = fs.rdbuf ();
      retval = static_cast<long> (fb->pubseekoff (0, std::ios::cur));
    }

  return retval;
}

// Return non-zero if EOF has been reached on this stream.

bool
octave_fstream::eof (void) const
{
  return fs.eof ();
}

void
octave_fstream::do_close (void)
{
  fs.close ();
}

std::istream *
octave_fstream::input_stream (void)
{
  std::istream *retval = 0;

  if (mode () & std::ios::in)
    retval = &fs;

  return retval;
}

std::ostream *
octave_fstream::output_stream (void)
{
  std::ostream *retval = 0;

  if (mode () & std::ios::out)
    retval = &fs;

  return retval;
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
