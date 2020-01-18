// defaults.h.in
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

#if !defined (octave_defaults_h)
#define octave_defaults_h 1

#include <string>

#include "pathsearch.h"

#ifndef OCTAVE_CANONICAL_HOST_TYPE
#define OCTAVE_CANONICAL_HOST_TYPE "i686-pc-linux-gnu"
#endif

#ifndef OCTAVE_DEFAULT_PAGER
#define OCTAVE_DEFAULT_PAGER "less"
#endif

#ifndef OCTAVE_ARCHLIBDIR
#define OCTAVE_ARCHLIBDIR "/usr/local/libexec/octave/2.1.57/exec/i686-pc-linux-gnu"
#endif

#ifndef OCTAVE_BINDIR
#define OCTAVE_BINDIR "/usr/local/bin"
#endif

#ifndef OCTAVE_DATADIR
#define OCTAVE_DATADIR "/usr/local/share"
#endif

#ifndef OCTAVE_EXEC_PREFIX
#define OCTAVE_EXEC_PREFIX "/usr/local"
#endif

#ifndef OCTAVE_FCNFILEDIR
#define OCTAVE_FCNFILEDIR "/usr/local/share/octave/2.1.57/m"
#endif

#ifndef OCTAVE_FCNFILEPATH
#define OCTAVE_FCNFILEPATH ".:/usr/local/libexec/octave/2.1.57/site/oct/i686-pc-linux-gnu//:/usr/local/libexec/octave/site/oct/api-v8/i686-pc-linux-gnu//:/usr/local/libexec/octave/site/oct/i686-pc-linux-gnu//:/usr/local/share/octave/2.1.57/site/m//:/usr/local/share/octave/site/api-v8/m//:/usr/local/share/octave/site/m//:/usr/local/libexec/octave/2.1.57/oct/i686-pc-linux-gnu//:/usr/local/share/octave/2.1.57/m//"
#endif

#ifndef OCTAVE_IMAGEDIR
#define OCTAVE_IMAGEDIR "/usr/local/share/octave/2.1.57/imagelib"
#endif

#ifndef OCTAVE_IMAGEPATH
#define OCTAVE_IMAGEPATH ".:/usr/local/share/octave/2.1.57/imagelib//"
#endif

#ifndef OCTAVE_INCLUDEDIR
#define OCTAVE_INCLUDEDIR "/usr/local/include"
#endif

#ifndef OCTAVE_INFODIR
#define OCTAVE_INFODIR "/usr/local/info"
#endif

#ifndef OCTAVE_INFOFILE
#define OCTAVE_INFOFILE "/usr/local/info/octave.info"
#endif

#ifndef OCTAVE_LIBDIR
#define OCTAVE_LIBDIR "/usr/local/lib"
#endif

#ifndef OCTAVE_LIBEXECDIR
#define OCTAVE_LIBEXECDIR "/usr/local/libexec"
#endif

#ifndef OCTAVE_LIBEXECDIR
#define OCTAVE_LIBEXECDIR "/usr/local/libexec"
#endif

#ifndef OCTAVE_LOCALAPIFCNFILEDIR
#define OCTAVE_LOCALAPIFCNFILEDIR "/usr/local/share/octave/site/api-v8/m"
#endif

#ifndef OCTAVE_LOCALAPIOCTFILEDIR
#define OCTAVE_LOCALAPIOCTFILEDIR "/usr/local/libexec/octave/site/oct/api-v8/i686-pc-linux-gnu"
#endif

#ifndef OCTAVE_LOCALARCHLIBDIR
#define OCTAVE_LOCALARCHLIBDIR "/usr/local/libexec/octave/site/exec/i686-pc-linux-gnu"
#endif

#ifndef OCTAVE_LOCALFCNFILEDIR
#define OCTAVE_LOCALFCNFILEDIR "/usr/local/share/octave/site/m"
#endif

#ifndef OCTAVE_LOCALFCNFILEPATH
#define OCTAVE_LOCALFCNFILEPATH "/usr/local/share/octave/2.1.57/site/m//:/usr/local/share/octave/site/api-v8/m//:/usr/local/share/octave/site/m//"
#endif

#ifndef OCTAVE_LOCALOCTFILEDIR
#define OCTAVE_LOCALOCTFILEDIR "/usr/local/libexec/octave/site/oct/i686-pc-linux-gnu"
#endif

#ifndef OCTAVE_LOCALOCTFILEPATH
#define OCTAVE_LOCALOCTFILEPATH "/usr/local/libexec/octave/2.1.57/site/oct/i686-pc-linux-gnu//:/usr/local/libexec/octave/site/oct/api-v8/i686-pc-linux-gnu//:/usr/local/libexec/octave/site/oct/i686-pc-linux-gnu//"
#endif

#ifndef OCTAVE_LOCALSTARTUPFILEDIR
#define OCTAVE_LOCALSTARTUPFILEDIR ""
#endif

#ifndef OCTAVE_LOCALVERARCHLIBDIR
#define OCTAVE_LOCALVERARCHLIBDIR "/usr/local/libexec/octave/2.1.57/site/exec/i686-pc-linux-gnu"
#endif

#ifndef OCTAVE_LOCALVERFCNFILEDIR
#define OCTAVE_LOCALVERFCNFILEDIR "/usr/local/share/octave/2.1.57/site/m"
#endif

#ifndef OCTAVE_LOCALVEROCTFILEDIR
#define OCTAVE_LOCALVEROCTFILEDIR "/usr/local/libexec/octave/2.1.57/site/oct/i686-pc-linux-gnu"
#endif

#ifndef OCTAVE_MAN1DIR
#define OCTAVE_MAN1DIR "/usr/local/man/man1"
#endif

#ifndef OCTAVE_MAN1EXT
#define OCTAVE_MAN1EXT ".1"
#endif

#ifndef OCTAVE_MANDIR
#define OCTAVE_MANDIR "/usr/local/man"
#endif

#ifndef OCTAVE_OCTFILEDIR
#define OCTAVE_OCTFILEDIR "/usr/local/libexec/octave/2.1.57/oct/i686-pc-linux-gnu"
#endif

#ifndef OCTAVE_OCTINCLUDEDIR
#define OCTAVE_OCTINCLUDEDIR "/usr/local/include/octave-2.1.57"
#endif

#ifndef OCTAVE_OCTLIBDIR
#define OCTAVE_OCTLIBDIR "/usr/local/lib/octave-2.1.57"
#endif

#ifndef OCTAVE_PREFIX
#define OCTAVE_PREFIX "/usr/local"
#endif

#ifndef OCTAVE_STARTUPFILEDIR
#define OCTAVE_STARTUPFILEDIR "/usr/local/share/octave/2.1.57/m/startup"
#endif

extern std::string Voctave_home;

extern std::string Vbin_dir;
extern std::string Vinfo_dir;
extern std::string Vdata_dir;
extern std::string Vlibexec_dir;
extern std::string Varch_lib_dir;
extern std::string Vlocal_arch_lib_dir;
extern std::string Vlocal_ver_arch_lib_dir;
extern std::string Vfcn_file_dir;

// The path that will be searched for programs that we execute.
// (--exec-path path)
extern std::string Vexec_path;

// And the cached directory path corresponding to Vload_path.
extern dir_path Vload_path_dir_path;

// Name of the editor to be invoked by the edit_history command.
extern std::string Veditor;

extern std::string Vimagepath;

extern std::string Vlocal_site_defaults_file;
extern std::string Vsite_defaults_file;

// Name of the FFTW wisdom program.
extern std::string Vfftw_wisdom_prog;

extern void execute_default_pkg_add_files (void);

extern std::string maybe_add_default_load_path (const std::string& pathstring);

extern void install_defaults (void);

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; page-delimiter: "^/\\*" ***
;;; End: ***
*/
