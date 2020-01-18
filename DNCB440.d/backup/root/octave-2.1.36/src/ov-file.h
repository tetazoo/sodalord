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

#if !defined (octave_file_h)
#define octave_file_h 1

#if defined (__GNUG__)
#pragma interface
#endif

#include <cstdlib>

#include <iostream>
#include <string>

#include "oct-alloc.h"
#include "oct-stream.h"
#include "ov-base.h"
#include "ov-typeinfo.h"

class tree_walker;
class octave_stream;
class octave_value;
class octave_value_list;

// Lists.

class
octave_file : public octave_base_value
{
public:

  octave_file (void)
    : octave_base_value (), stream (), number (-1) { }

  octave_file (const octave_stream& s, int n)
    : octave_base_value (), stream (s), number (n) { }

  octave_file (const octave_file& f)
    : octave_base_value (), stream (f.stream), number (f.number) { }

  ~octave_file (void) { }

  octave_value *clone (void) { return new octave_file (*this); }

  type_conv_fcn numeric_conversion_function (void) const;

  double double_value (bool) const { return static_cast<double> (number); }

  double scalar_value (bool) const { return static_cast<double> (number); }

  octave_stream stream_value (void) const { return stream; }

  int stream_number (void) const { return number; }

  bool is_defined (void) const { return true; }

  bool is_stream (void) const { return true; }

  void print (std::ostream& os, bool pr_as_read_syntax = false) const;

  void print_raw (std::ostream& os, bool pr_as_read_syntax = false) const;

  bool print_name_tag (std::ostream& os, const std::string& name) const;

private:

  // The stream object.
  octave_stream stream;

  // The number of the beast.
  int number;

  DECLARE_OV_TYPEID_FUNCTIONS_AND_DATA

  DECLARE_OCTAVE_ALLOCATOR
};

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
