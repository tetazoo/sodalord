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

// Instantiate Lists of various values.

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "SLList.h"
#include "SLList.cc"

#include "ov.h"
#include "pt-arg-list.h"
#include "pt-decl.h"
#include "pt-select.h"
#include "pt-stmt.h"

template class SLNode<tree_argument_list *>;
template class SLList<tree_argument_list *>;

template class SLNode<tree_statement *>;
template class SLList<tree_statement *>;

template class SLNode<tree_if_clause *>;
template class SLList<tree_if_clause *>;

template class SLList<tree_switch_case *>;
template class SLNode<tree_switch_case *>;

template class SLList<tree_decl_elt *>;
template class SLNode<tree_decl_elt *>;

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
