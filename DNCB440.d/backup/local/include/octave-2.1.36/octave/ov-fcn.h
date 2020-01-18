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

#if !defined (octave_function_h)
#define octave_function_h 1

#if defined (__GNUG__)
#pragma interface
#endif

#include <string>

#include "oct-time.h"
#include "str-vec.h"

#include "oct-alloc.h"
#include "ov-base.h"
#include "ov-typeinfo.h"

class tree_walker;

// Functions.

class
octave_function : public octave_base_value
{
public:

  octave_function (const octave_function& f)
    : octave_base_value (), my_name (f.my_name), doc (f.doc) { }

  ~octave_function (void) { }

  // This should only be called for derived types.

  octave_function *clone (void);

  bool is_defined (void) const { return true; }

  bool is_function (void) const { return true; }

  virtual bool is_dynamically_loaded_function (void) const { return false; }

  virtual bool is_system_fcn_file (void) const { return false; }

  virtual std::string fcn_file_name (void) const { return std::string (); }

  virtual void mark_fcn_file_up_to_date (const octave_time&) { }

  virtual octave_time time_parsed (void) const
    { return octave_time (static_cast<time_t> (0)); }

  virtual octave_time time_checked (void) const
    { return octave_time (static_cast<time_t> (0)); }

  std::string name (void) const { return my_name; }

  std::string doc_string (void) const { return doc; }

  virtual void unload (void) { }

  virtual void accept (tree_walker&) { }

protected:

  octave_function (const std::string& nm, const std::string& ds)
    : my_name (nm), doc (ds) { }

  // The name of this function.
  std::string my_name;

  // The help text for this function.
  std::string doc;

private:

  octave_function (void);

  DECLARE_OCTAVE_ALLOCATOR
};

#endif

/*
;; Local Variables: ***
;; mode: C++ ***
;; End: ***
*/
