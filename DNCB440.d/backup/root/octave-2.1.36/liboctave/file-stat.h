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

#if !defined (octave_file_stat_h)
#define octave_file_stat_h 1

#include <string>

#include "oct-time.h"

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

class
file_stat
{
public:

  file_stat (const std::string& n = std::string (), bool fl = true)
    : file_name (n), follow_links (fl), initialized (false)
      {
	if (! file_name.empty ())
	  update_internal ();
      }

  file_stat (const file_stat& f) { copy (f); }

  file_stat& operator = (const file_stat& f)
    {
      if (this != &f)
	copy (f);

      return *this;
    }

  ~file_stat (void) { }

  void get_stats (bool force = false)
    {
      if (! initialized || force)
        update_internal (force);
    }

  void get_stats (const std::string& n, bool force = false)
    {
      if (n != file_name || ! initialized  || force)
	{
	  initialized = false;

	  file_name = n;

	  update_internal (force);
	}
    }

  // File status and info.  These should only be called for objects
  // that are already properly initialized.

  bool is_blk (void) const;
  bool is_chr (void) const;
  bool is_dir (void) const;
  bool is_fifo (void) const;
  bool is_lnk (void) const;
  bool is_reg (void) const;
  bool is_sock (void) const;

  ino_t ino (void) const { return fs_ino; }
  dev_t dev (void) const { return fs_dev; }

  nlink_t nlink (void) const { return fs_nlink; }

  uid_t uid (void) const { return fs_uid; }
  gid_t gid (void) const { return fs_gid; }

  off_t size (void) const { return fs_size; }

  octave_time atime (void) const { return fs_atime; }
  octave_time mtime (void) const { return fs_mtime; }
  octave_time ctime (void) const { return fs_ctime; }

#if defined (HAVE_STRUCT_STAT_ST_RDEV)
  dev_t rdev (void) const { return fs_rdev; }
#endif

#if defined (HAVE_STRUCT_STAT_ST_BLKSIZE)
  long blksize (void) const { return fs_blksize; }
#endif

#if defined (HAVE_STRUCT_STAT_ST_BLOCKS)
  long blocks (void) const { return fs_blocks; }
#endif

  std::string mode_as_string (void) const;

  bool ok (void) const { return initialized && ! fail; }

  operator bool () const { return ok (); }

  bool exists (void) const { return ok (); }

  std::string error (void) const { return ok () ? std::string () : errmsg; }

  // Has the file referenced by this object been modified since TIME?
  bool is_newer (const octave_time& time) const { return fs_mtime > time; }

  // It's nice to be able to hide the file_stat object if we don't
  // really care about it.
  static int is_newer (const std::string&, const octave_time&);

private:

  // Name of the file.
  std::string file_name;

  // TRUE means follow symbolic links to the ultimate file (stat).
  // FALSE means get information about the link itself (lstat).
  bool follow_links;

  // TRUE means we have already called stat.
  bool initialized;

  // TRUE means the stat for this file failed.
  bool fail;

  // If a failure occurs, this contains the system error text.
  std::string errmsg;

  // file type and permissions
  mode_t fs_mode;

  // serial number
  ino_t fs_ino;

  // device number
  dev_t fs_dev;

  // number of links
  nlink_t fs_nlink;

  // user ID of owner
  uid_t fs_uid;

  // group ID of owner
  gid_t fs_gid;

  // size in bytes, for regular files
  off_t fs_size;

  // time of last access
  octave_time fs_atime;

  // time of last modification
  octave_time fs_mtime;

  // time of last file status change
  octave_time fs_ctime;

#if defined (HAVE_STRUCT_STAT_ST_RDEV)
  // device number for special files
  dev_t fs_rdev;
#endif

#if defined (HAVE_STRUCT_STAT_ST_BLKSIZE)
  // best I/O block size
  long fs_blksize;
#endif

#if defined (HAVE_STRUCT_STAT_ST_BLOCKS)
  // number of 512-byte blocks allocated
  long fs_blocks;
#endif

  void update_internal (bool force = false);

  void copy (const file_stat&);
};

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
