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

#if !defined (octave_f77_fcn_h)
#define octave_f77_fcn_h 1

#include "quit.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Hack to stringize macro results. */
#define xSTRINGIZE(x) #x
#define STRINGIZE(x) xSTRINGIZE(x)

/* How to print an error for the F77_XFCN macro. */

#define F77_XFCN_ERROR(f, F) \
  (*current_liboctave_error_handler) \
    ("exception encountered in Fortran subroutine %s", \
     STRINGIZE (F77_FUNC (f, F)))

/* This can be used to call a Fortran subroutine that might call
   XSTOPX.  XSTOPX will call lonjmp with current_context.  Once back
   here, we'll restore the previous context and return.  We may also
   end up here if an interrupt is processed when the Fortran
   subroutine is called.  In that case, we resotre the context and go
   to the top level.  The error_state should be checked immediately
   after this macro is used. */

#define F77_XFCN(f, F, args) \
  do \
    { \
      octave_jmp_buf saved_context; \
      f77_exception_encountered = 0; \
      octave_save_current_context ((char *) saved_context); \
      if (octave_set_current_context) \
	{ \
          octave_restore_current_context ((char *) saved_context); \
	  if (f77_exception_encountered) \
	    F77_XFCN_ERROR (f, F); \
          else if (octave_allocation_error) \
            octave_throw_bad_alloc (); \
          else \
            octave_throw_interrupt_exception (); \
	} \
      else \
        { \
	  octave_interrupt_immediately++; \
	  F77_FUNC (f, F) args; \
	  octave_interrupt_immediately--; \
          octave_restore_current_context ((char *) saved_context); \
        } \
    } \
  while (0)

/* So we can check to see if an exception has occurred. */
extern int f77_exception_encountered;

#if !defined (F77_FCN)
#define F77_FCN(f, F) F77_FUNC (f, F)
#endif

#if defined (F77_USES_CRAY_CALLING_CONVENTION)

#include <fortran.h>
#define F77_CHAR_ARG(x) octave_make_cray_ftn_ch_dsc (x, strlen (x))
#define F77_CONST_CHAR_ARG(x) \
  octave_make_cray_const_ftn_ch_dsc (x, strlen (x))
#define F77_CHAR_ARG2(x, l) octave_make_cray_ftn_ch_dsc (x, l)
#define F77_CONST_CHAR_ARG2(x, l) octave_make_cray_const_ftn_ch_dsc (x, l)
#define F77_CXX_STRING_ARG(x) \
  octave_make_cray_const_ftn_ch_dsc (x.c_str (), x.length ())
#define F77_CHAR_ARG_LEN(l)
#define F77_CHAR_ARG_DECL octave_cray_ftn_ch_dsc
#define F77_CONST_CHAR_ARG_DECL octave_cray_ftn_ch_dsc
#define F77_CHAR_ARG_LEN_DECL
#define F77_RET_T int
#define F77_RETURN(retval) return retval;

/* XXX FIXME XXX -- these should work for SV1 or Y-MP systems but will
   need to be changed for others.  */

typedef union
{
  const char *const_ptr;
  char *ptr;
  struct
  {
    unsigned off : 6;
    unsigned len : 26;
    unsigned add : 32;
  } mask;
} octave_cray_descriptor;

typedef void *octave_cray_ftn_ch_dsc;

#ifdef __cplusplus
#define OCTAVE_F77_FCN_INLINE inline
#else
#define OCTAVE_F77_FCN_INLINE
#endif

static OCTAVE_F77_FCN_INLINE octave_cray_ftn_ch_dsc
octave_make_cray_ftn_ch_dsc (char *ptr_arg, unsigned long len_arg)
{
  octave_cray_descriptor desc;
  desc.ptr = ptr_arg;
  desc.mask.len = len_arg << 3;
  return *((octave_cray_ftn_ch_dsc *) &desc);
}

static OCTAVE_F77_FCN_INLINE octave_cray_ftn_ch_dsc
octave_make_cray_const_ftn_ch_dsc (const char *ptr_arg, unsigned long len_arg)
{
  octave_cray_descriptor desc;
  desc.const_ptr = ptr_arg;
  desc.mask.len = len_arg << 3;
  return *((octave_cray_ftn_ch_dsc *) &desc);
}

#ifdef __cplusplus
#undef OCTAVE_F77_FCN_INLINE
#endif

#elif defined (F77_USES_VISUAL_FORTRAN_CALLING_CONVENTION)

#define F77_CHAR_ARG(x) x, strlen (x)
#define F77_CONST_CHAR_ARG(x) F77_CHAR_ARG (x)
#define F77_CHAR_ARG2(x, l) x, l
#define F77_CONST_CHAR_ARG2(x, l) F77_CHAR_ARG2 (x, l)
#define F77_CXX_STRING_ARG(x) F77_CONST_CHAR_ARG2 (x.c_str (), x.length ())
#define F77_CHAR_ARG_LEN(l)
#define F77_CHAR_ARG_DECL char *, int
#define F77_CONST_CHAR_ARG_DECL const char *, int
#define F77_CHAR_ARG_LEN_DECL
#define F77_RET_T void
#define F77_RETURN(retval)

#else

/* Assume f2c-compatible calling convention.  */

#define F77_CHAR_ARG(x) x
#define F77_CONST_CHAR_ARG(x) F77_CHAR_ARG (x)
#define F77_CHAR_ARG2(x, l) x
#define F77_CONST_CHAR_ARG2(x, l) F77_CHAR_ARG2 (x, l)
#define F77_CXX_STRING_ARG(x) F77_CONST_CHAR_ARG2 (x.c_str (), x.length ())
#define F77_CHAR_ARG_LEN(l) , (long) l
#define F77_CHAR_ARG_DECL char *
#define F77_CONST_CHAR_ARG_DECL const char *
#define F77_CHAR_ARG_LEN_DECL , long
#define F77_RET_T int
#define F77_RETURN(retval) return retval;

#endif

extern F77_RET_T
F77_FUNC (xstopx, XSTOPX) (F77_CONST_CHAR_ARG_DECL
			   F77_CHAR_ARG_LEN_DECL) GCC_ATTR_NORETURN;

#ifdef __cplusplus
}
#endif

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
