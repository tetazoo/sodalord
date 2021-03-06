/*

Copyright (C) 2003 John W. Eaton

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

#include <signal.h>
#include <string.h>

#include "quit.h"

octave_jmp_buf current_context;

void
octave_save_current_context (void *save_buf)
{
  memcpy (save_buf, current_context, sizeof (octave_jmp_buf));
}

void
octave_restore_current_context (void *save_buf)
{
  memcpy (current_context, save_buf, sizeof (octave_jmp_buf));
}

void
octave_jump_to_enclosing_context (void)
{
#if defined (OCTAVE_HAVE_SIG_JUMP)
  siglongjmp (current_context, 1);
#else
  longjmp (current_context, 1);
#endif
}

/* Allow us to save the signal mask and then restore it to the most
   recently saved value.  This is necessary when using the POSIX
   signal handling interface on some systems calling longjmp out of
   the signal handler to get to the top level on an interrupt doesn't
   restore the original signal mask.  Alternatively, we could use
   sigsetjmp/siglongjmp, but saving and restoring the signal mask
   ourselves works ok and seems simpler just now.  */

#if defined (HAVE_POSIX_SIGNALS)
static sigset_t octave_signal_mask;
#endif

void
octave_save_signal_mask (void)
{
#if defined (HAVE_POSIX_SIGNALS)
  sigprocmask (0, 0, &octave_signal_mask);
#endif
}

void
octave_restore_signal_mask (void)
{
#if defined (HAVE_POSIX_SIGNALS)
  sigprocmask (SIG_SETMASK, &octave_signal_mask, 0);
#endif
}

sig_atomic_t octave_interrupt_immediately = 0;

sig_atomic_t octave_interrupt_state = 0;

sig_atomic_t octave_allocation_error = 0;

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
