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

#if !defined (octave_str_vec_h)
#define octave_str_vec_h 1

#include <iostream>
#include <string>

#include "Array.h"

class
string_vector : public Array<std::string>
{
public:

  string_vector (void) : Array<std::string> () { }

  explicit string_vector (int n) : Array<std::string> (n) { }

  string_vector (const char *s) : Array<std::string> (1, s) { }

  string_vector (const std::string& s) : Array<std::string> (1, s) { }

  string_vector (const string_vector& s) : Array<std::string> (s) { }

  string_vector (const char * const *s);

  string_vector (const char * const *s, int n);

  string_vector& operator = (const string_vector& s)
  {
    if (this != &s)
      Array<std::string>::operator = (s);

    return *this;
  }

  ~string_vector (void) { }

  int empty (void) const { return length () == 0; }

  int max_length (void) const
  {
    int n = length ();
    int longest = 0;

    for (int i = 0; i < n; i++)
      {
	int tmp = elem(i).length ();

	if (tmp > longest)
	  longest = tmp;
      }

    return longest;
  }

  std::string& operator[] (int i) { return Array<std::string>::elem (i); }

  std::string operator[] (int i) const { return Array<std::string>::elem (i); }

  static int compare (const void *a_arg, const void *b_arg);

  string_vector& qsort (bool make_uniq = false)
  {
    Array<std::string>::qsort (compare);

    if (make_uniq)
      uniq ();

    return *this;
  }

  string_vector& uniq (void);

  string_vector& append (const std::string& s);

  string_vector& append (const string_vector& sv);

  char **c_str_vec (void) const;

  static void delete_c_str_vec (const char * const*);

  std::ostream& list_in_columns (std::ostream&) const;
};

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
