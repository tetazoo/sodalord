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

#include <cerrno>
#include <cstring>

#ifdef HAVE_UNISTD_H
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#include <unistd.h>
#endif

#include "file-stat.h"
#include "statdefs.h"

#if !defined (HAVE_LSTAT)
static inline int
lstat (const char *name, struct stat *buf)
{
  return stat (name, buf);
}
#endif

// XXX FIXME XXX -- the is_* and mode_as_string functions are only valid
// for initialized objects.  If called for an object that is not
// initialized, they should throw an exception.

bool
file_stat::is_blk (void) const
{
#ifdef S_ISBLK
  return S_ISBLK (fs_mode);
#else
  return false;
#endif
}

bool
file_stat::is_chr (void) const
{
#ifdef S_ISCHR
  return S_ISCHR (fs_mode);
#else
  return false;
#endif
}

bool
file_stat::is_dir (void) const
{ 
#ifdef S_ISDIR
  return S_ISDIR (fs_mode);
#else
  return false;
#endif
}

bool
file_stat::is_fifo (void) const
{ 
#ifdef S_ISFIFO
  return S_ISFIFO (fs_mode);
#else
  return false;
#endif
}

bool
file_stat::is_lnk (void) const
{ 
#ifdef S_ISLNK
  return S_ISLNK (fs_mode);
#else
  return false;
#endif
}

bool
file_stat::is_reg (void) const
{ 
#ifdef S_ISREG
  return S_ISREG (fs_mode);
#else
  return false;
#endif
}

bool
file_stat::is_sock (void) const
{ 
#ifdef S_ISSOCK
  return S_ISSOCK (fs_mode);
#else
  return false;
#endif
}

extern "C" void mode_string (unsigned short, char *);

std::string
file_stat::mode_as_string (void) const
{
  char buf[11];

  mode_string (fs_mode, buf);

  buf[10] = '\0';

  return std::string (buf);
}

// Has FILE been modified since TIME?  Returns 1 for yes, 0 for no,
// and -1 for any error.

int
file_stat::is_newer (const std::string& file, const octave_time& time)
{
  file_stat fs (file);

  return fs ? fs.is_newer (time) : -1;
}

// Private stuff:

void
file_stat::update_internal (bool force)
{
  if (! initialized || force)
    {
      initialized = false;
      fail = false;

      const char *cname = file_name.c_str ();

      struct stat buf;

      int status = follow_links ? stat (cname, &buf) : lstat (cname, &buf);

      if (status < 0)
	{
	  using namespace std;

	  fail = true;
	  errmsg = strerror (errno);
	}
      else
	{
	  fs_mode = buf.st_mode;
	  fs_ino = buf.st_ino;
	  fs_dev = buf.st_dev;
	  fs_nlink = buf.st_nlink;
	  fs_uid = buf.st_uid;
	  fs_gid = buf.st_gid;
	  fs_size = buf.st_size;
	  fs_atime = buf.st_atime;
	  fs_mtime = buf.st_mtime;
	  fs_ctime = buf.st_ctime;

#if defined (HAVE_STRUCT_STAT_ST_RDEV)
	  fs_rdev = buf.st_rdev;
#endif

#if defined (HAVE_STRUCT_STAT_ST_BLKSIZE)
	  fs_blksize = buf.st_blksize;
#endif

#if defined (HAVE_STRUCT_STAT_ST_BLOCKS)
	  fs_blocks = buf.st_blocks;
#endif
	}

      initialized = true;
    }
}

void
file_stat::copy (const file_stat& fs)
{
  file_name = fs.file_name;
  follow_links = fs.follow_links;
  initialized = fs.initialized;
  fail = fs.fail;
  errmsg = fs.errmsg;
  fs_mode = fs.fs_mode;
  fs_ino = fs.fs_ino;
  fs_dev = fs.fs_dev;
  fs_nlink = fs.fs_nlink;
  fs_uid = fs.fs_uid;
  fs_gid = fs.fs_gid;
  fs_size = fs.fs_size;
  fs_atime = fs.fs_atime;
  fs_mtime = fs.fs_mtime;
  fs_ctime = fs.fs_ctime;

#if defined (HAVE_STRUCT_STAT_ST_RDEV)
  fs_rdev = fs.fs_rdev;
#endif

#if defined (HAVE_STRUCT_STAT_ST_BLKSIZE)
  fs_blksize = fs.fs_blksize;
#endif

#if defined (HAVE_STRUCT_STAT_ST_BLOCKS)
  fs_blocks = fs.fs_blocks;
#endif
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
