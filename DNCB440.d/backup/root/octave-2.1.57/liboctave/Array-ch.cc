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

// Instantiate Arrays of char values.

#include "Array.h"
#include "Array.cc"

INSTANTIATE_ARRAY_AND_ASSIGN (char);

INSTANTIATE_ARRAY_CAT (char);

#include "Array2.h"

template class Array2<char>;

#include "ArrayN.h"
#include "ArrayN.cc"

template class ArrayN<char>;

template std::ostream& operator << (std::ostream&, const ArrayN<char>&);

#include "DiagArray2.h"
#include "DiagArray2.cc"

template class DiagArray2<char>;

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
