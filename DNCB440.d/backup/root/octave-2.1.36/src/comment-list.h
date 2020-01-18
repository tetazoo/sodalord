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

#if !defined (octave_comment_list_h)
#define octave_comment_list_h 1

#if defined (__GNUG__)
#pragma interface
#endif

#include <string>

#include <SLList.h>

extern std::string get_comment_text (void);

extern char *get_comment_text_c_str (void);

extern void save_comment_text (const std::string& text);

class
octave_comment_elt
{
public:

  enum comment_type
  {
    unknown,
    block,
    end_of_line,
    doc_string,
    copyright
  };

  octave_comment_elt (const std::string& s = std::string (),
		      comment_type t = unknown)
    : txt (s), typ (t) { }

  octave_comment_elt (const octave_comment_elt& oc)
    : txt (oc.txt), typ (oc.typ) { }

  octave_comment_elt& operator = (const octave_comment_elt& oc)
    {
      if (this != &oc)
	{
	  txt = oc.txt;
	  typ = oc.typ;
	}

      return *this;
    }

  std::string text (void) const { return txt; }

  comment_type type (void) const { return typ; }

  ~octave_comment_elt (void) { }

private:

  // The text of the comment.
  std::string txt;

  // The type of comment.
  comment_type typ;
};

class
octave_comment_list : public SLList<octave_comment_elt>
{
public:

  octave_comment_list (void) { }

  ~octave_comment_list (void) { }

  void append
    (const std::string& s,
     octave_comment_elt::comment_type t = octave_comment_elt::unknown)
    {
      SLList<octave_comment_elt>::append (octave_comment_elt (s, t));
    }

  octave_comment_list (const octave_comment_list& ocb)
    : SLList<octave_comment_elt> (ocb) { }

  octave_comment_list& operator = (const octave_comment_list& ocb)
    {
      if (this != &ocb)
	SLList<octave_comment_elt>::operator = (ocb);

      return *this;
    }
};

class
octave_comment_buffer
{
public:

  octave_comment_buffer (void)
    : comment_list (new octave_comment_list) { }
  
  static bool instance_ok (void);

  static void append
    (const std::string& s,
     octave_comment_elt::comment_type t = octave_comment_elt::unknown);

  static octave_comment_list *get_comment (void);

private:

  void do_append (const std::string& s, octave_comment_elt::comment_type t);

  octave_comment_list *do_get_comment (void);

  octave_comment_list *comment_list;

  static octave_comment_buffer *instance;
};

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
