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

#if defined (__GNUG__)
#pragma implementation
#endif

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <cassert>

#include "error.h"
#include "ov.h"
#include "symtab.h"
#include "token.h"
#include "utils.h"

token::token (int l, int c)
{
  line_num = l;
  column_num = c;
  type_tag = generic_token;
}

token::token (const std::string& s, int l, int c)
{
  line_num = l;
  column_num = c;
  type_tag = string_token;
  str = new std::string (s);
}

token::token (double d, const std::string& s, int l, int c)
{
  line_num = l;
  column_num = c;
  type_tag = double_token;
  num = d;
  orig_text = s;
}

token::token (end_tok_type t, int l, int c)
{
  line_num = l;
  column_num = c;
  type_tag = ettype_token;
  et = t;
}

token::token (plot_tok_type t, int l, int c)
{
  line_num = l;
  column_num = c;
  type_tag = pttype_token;
  pt = t;
}

token::token (symbol_record *s, int l, int c)
{
  line_num = l;
  column_num = c;
  type_tag = sym_rec_token;
  sr = s;
}

token::~token (void)
{
  if (type_tag == string_token)
    delete str;
}

std::string
token::text (void)
{
  assert (type_tag == string_token);
  return *str;
}

double
token::number (void)
{
  assert (type_tag == double_token);
  return num;
}

token::end_tok_type
token::ettype (void)
{
  assert (type_tag == ettype_token);
  return et;
}

token::plot_tok_type
token::pttype (void)
{
  assert (type_tag == pttype_token);
  return pt;
}

symbol_record *
token::sym_rec (void)
{
  assert (type_tag == sym_rec_token);
  return sr;
}

std::string
token::text_rep (void)
{
  return orig_text;
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
