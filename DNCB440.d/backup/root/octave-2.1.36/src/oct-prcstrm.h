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

#if !defined (octave_octave_procstream_h)
#define octave_octave_procstream_h 1

#include "oct-stdstrm.h"

// XXX FIXME XXX -- why don't these classes use iprocstream and
// oprocstream, which in turn use the octave_procbuf class?

class
octave_iprocstream : public octave_istdiostream
{
public:

  octave_iprocstream (const std::string& n,
		      std::ios::openmode arg_md = std::ios::in,
		      oct_mach_info::float_format flt_fmt =
		      oct_mach_info::native);

  static octave_stream
  create (const std::string& n, std::ios::openmode arg_md = std::ios::in,
	  oct_mach_info::float_format flt_fmt = oct_mach_info::native);

protected:

  ~octave_iprocstream (void);

private:

  // No copying!

  octave_iprocstream (const octave_iprocstream&);

  octave_iprocstream& operator = (const octave_iprocstream&);
};

class
octave_oprocstream : public octave_ostdiostream
{
public:

  octave_oprocstream (const std::string& n,
		      std::ios::openmode arg_md = std::ios::out,
		      oct_mach_info::float_format flt_fmt =
		      oct_mach_info::native);

  static octave_stream
  create (const std::string& n, std::ios::openmode arg_md = std::ios::out,
	  oct_mach_info::float_format flt_fmt = oct_mach_info::native);

protected:

  ~octave_oprocstream (void);

private:

  // No copying!

  octave_oprocstream (const octave_oprocstream&);

  octave_oprocstream& operator = (const octave_oprocstream&);
};

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
