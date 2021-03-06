// oct-conf.h.in
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

#if !defined (octave_conf_h)
#define octave_conf_h 1

#ifndef OCTAVE_CONF_ALL_CFLAGS
#define OCTAVE_CONF_ALL_CFLAGS "-I. -I.. -I../liboctave -I../src -I../libcruft/misc  -I../glob -I../glob -DHAVE_CONFIG_H -mieee-fp -Wall -W -Wshadow -g -O2"
#endif

#ifndef OCTAVE_CONF_ALL_CXXFLAGS
#define OCTAVE_CONF_ALL_CXXFLAGS "-I. -I.. -I../liboctave -I../src -I../libcruft/misc  -I../glob -I../glob -DHAVE_CONFIG_H -mieee-fp -Wall -W -Wshadow -g -O2"
#endif

#ifndef OCTAVE_CONF_ALL_FFLAGS
#define OCTAVE_CONF_ALL_FFLAGS "-O"
#endif

#ifndef OCTAVE_CONF_ALL_LDFLAGS
#define OCTAVE_CONF_ALL_LDFLAGS "-L..  -fPIC "
#endif

#ifndef OCTAVE_CONF_ARFLAGS
#define OCTAVE_CONF_ARFLAGS "rc "
#endif

#ifndef OCTAVE_CONF_AR
#define OCTAVE_CONF_AR "ar"
#endif

#ifndef OCTAVE_CONF_BLAS_LIBS
#define OCTAVE_CONF_BLAS_LIBS ""
#endif

#ifndef OCTAVE_CONF_CC
#define OCTAVE_CONF_CC "gcc"
#endif

#ifndef OCTAVE_CONF_CC_VERSION
#define OCTAVE_CONF_CC_VERSION "3.2.2 20030222 (Red Hat Linux 3.2.2-5)"
#endif

#ifndef OCTAVE_CONF_CFLAGS
#define OCTAVE_CONF_CFLAGS "-g -O2"
#endif

#ifndef OCTAVE_CONF_CPICFLAG
#define OCTAVE_CONF_CPICFLAG "-fPIC"
#endif

#ifndef OCTAVE_CONF_CPPFLAGS
#define OCTAVE_CONF_CPPFLAGS ""
#endif

#ifndef OCTAVE_CONF_CXXCPP
#define OCTAVE_CONF_CXXCPP "g++ -E"
#endif

#ifndef OCTAVE_CONF_CXXFLAGS
#define OCTAVE_CONF_CXXFLAGS "-g -O2"
#endif

#ifndef OCTAVE_CONF_CXXPICFLAG
#define OCTAVE_CONF_CXXPICFLAG "-fPIC"
#endif

#ifndef OCTAVE_CONF_CXX
#define OCTAVE_CONF_CXX "g++"
#endif

#ifndef OCTAVE_CONF_CXX_VERSION
#define OCTAVE_CONF_CXX_VERSION "3.2.2"
#endif

#ifndef OCTAVE_CONF_DEFAULT_PAGER
#define OCTAVE_CONF_DEFAULT_PAGER "less"
#endif

#ifndef OCTAVE_CONF_DEFS
#define OCTAVE_CONF_DEFS "-DPACKAGE_NAME=\"\" -DPACKAGE_TARNAME=\"\" -DPACKAGE_VERSION=\"\" -DPACKAGE_STRING=\"\" -DPACKAGE_BUGREPORT=\"\" -DOCTAVE_SOURCE=1 -DSTDC_HEADERS=1 -DHAVE_SYS_TYPES_H=1 -DHAVE_SYS_STAT_H=1 -DHAVE_STDLIB_H=1 -DHAVE_STRING_H=1 -DHAVE_MEMORY_H=1 -DHAVE_STRINGS_H=1 -DHAVE_INTTYPES_H=1 -DHAVE_STDINT_H=1 -DHAVE_UNISTD_H=1 -DSEPCHAR=1 -DSEPCHAR_STR=\":\" -D__NO_MATH_INLINES=1 -DCXX_NEW_FRIEND_TEMPLATE_DECL=1 -DCXX_ISO_COMPLIANT_LIBRARY=1 -DCXX_ABI=gnu_v3 -DHAVE_LIBM=1 -DF77_FUNC(name,NAME)=name ## _ -DF77_FUNC_(name,NAME)=name ## __ -DHAVE_GETHOSTNAME=1 -DHAVE_GETPWNAM=1 -DHAVE_DEV_T=1 -DHAVE_INO_T=1 -DHAVE_NLINK_T=1 -DHAVE_NLINK_T=1 -DHAVE_LONG_LONG_INT=1 -DHAVE_UNSIGNED_LONG_LONG_INT=1 -DHAVE_SIGSET_T=1 -DHAVE_SIG_ATOMIC_T=1 -DSIZEOF_SHORT=2 -DSIZEOF_INT=4 -DSIZEOF_LONG=4 -DSIZEOF_LONG_LONG=8 -DHAVE_ALLOCA_H=1 -DHAVE_ALLOCA=1 -DNPOS=std::string::npos -DHAVE_PLACEMENT_DELETE=1 -DHAVE_DYNAMIC_AUTO_ARRAYS=1 -DSTDC_HEADERS=1 -DHAVE_DIRENT_H=1 -DTIME_WITH_SYS_TIME=1 -DHAVE_SYS_WAIT_H=1 -DHAVE_ASSERT_H=1 -DHAVE_CURSES_H=1 -DHAVE_DLFCN_H=1 -DHAVE_FCNTL_H=1 -DHAVE_FLOAT_H=1 -DHAVE_GRP_H=1 -DHAVE_LIMITS_H=1 -DHAVE_MEMORY_H=1 -DHAVE_NCURSES_H=1 -DHAVE_POLL_H=1 -DHAVE_PWD_H=1 -DHAVE_STDLIB_H=1 -DHAVE_STRING_H=1 -DHAVE_SYS_IOCTL_H=1 -DHAVE_SYS_PARAM_H=1 -DHAVE_SYS_POLL_H=1 -DHAVE_SYS_RESOURCE_H=1 -DHAVE_SYS_SELECT_H=1 -DHAVE_SYS_STAT_H=1 -DHAVE_SYS_TIME_H=1 -DHAVE_SYS_TIMES_H=1 -DHAVE_SYS_TYPES_H=1 -DHAVE_SYS_UTSNAME_H=1 -DHAVE_TERMCAP_H=1 -DHAVE_UNISTD_H=1 -DHAVE_VARARGS_H=1 -DHAVE_SSTREAM=1 -DHAVE_TERMIO_H=1 -DHAVE_SGTTY_H=1 -DHAVE_GLOB_H=1 -DHAVE_FNMATCH_H=1 -DHAVE_ATEXIT=1 -DHAVE_BASENAME=1 -DHAVE_BCOPY=1 -DHAVE_BZERO=1 -DHAVE_DUP2=1 -DHAVE_ENDGRENT=1 -DHAVE_ENDPWENT=1 -DHAVE_EXECVP=1 -DHAVE_FCNTL=1 -DHAVE_FORK=1 -DHAVE_GETCWD=1 -DHAVE_GETEGID=1 -DHAVE_GETEUID=1 -DHAVE_GETGID=1 -DHAVE_GETGRENT=1 -DHAVE_GETGRGID=1 -DHAVE_GETGRNAM=1 -DHAVE_GETPGRP=1 -DHAVE_GETPID=1 -DHAVE_GETPPID=1 -DHAVE_GETPWENT=1 -DHAVE_GETPWUID=1 -DHAVE_GETTIMEOFDAY=1 -DHAVE_GETUID=1 -DHAVE_GETWD=1 -DHAVE_KILL=1 -DHAVE_LINK=1 -DHAVE_LOCALTIME_R=1 -DHAVE_LSTAT=1 -DHAVE_MEMMOVE=1 -DHAVE_MKDIR=1 -DHAVE_MKFIFO=1 -DHAVE_MKSTEMP=1 -DHAVE_ON_EXIT=1 -DHAVE_PIPE=1 -DHAVE_POLL=1 -DHAVE_PUTENV=1 -DHAVE_RAISE=1 -DHAVE_READLINK=1 -DHAVE_RENAME=1 -DHAVE_RINDEX=1 -DHAVE_RMDIR=1 -DHAVE_SELECT=1 -DHAVE_SETGRENT=1 -DHAVE_SETPWENT=1 -DHAVE_SETVBUF=1 -DHAVE_SIGACTION=1 -DHAVE_SIGLONGJMP=1 -DHAVE_SIGPENDING=1 -DHAVE_SIGPROCMASK=1 -DHAVE_SIGSUSPEND=1 -DHAVE_STAT=1 -DHAVE_STRCASECMP=1 -DHAVE_STRDUP=1 -DHAVE_STRERROR=1 -DHAVE_STRFTIME=1 -DHAVE_STRNCASECMP=1 -DHAVE_STRPTIME=1 -DHAVE_SYMLINK=1 -DHAVE_TEMPNAM=1 -DHAVE_UMASK=1 -DHAVE_UNLINK=1 -DHAVE_USLEEP=1 -DHAVE_VFPRINTF=1 -DHAVE_VSPRINTF=1 -DHAVE_VSNPRINTF=1 -DHAVE_WAITPID=1 -DHAVE_TIMEVAL=1 -DHAVE_FINITE=1 -DHAVE_ISNAN=1 -DHAVE_ISINF=1 -DHAVE_COPYSIGN=1 -DHAVE_ACOSH=1 -DHAVE_ASINH=1 -DHAVE_ATANH=1 -DHAVE_ERF=1 -DHAVE_ERFC=1 -DHAVE_STRUCT_STAT_ST_BLKSIZE=1 -DHAVE_STRUCT_STAT_ST_BLOCKS=1 -DHAVE_STRUCT_STAT_ST_RDEV=1 -DHAVE_STRUCT_TM_TM_ZONE=1 -DHAVE_TM_ZONE=1 -DUSE_READLINE=1 -DEXCEPTION_IN_MATH=1 -DRETSIGTYPE=void -DSYS_SIGLIST_DECLARED=1 -DHAVE_SYS_SIGLIST=1 -DHAVE_POSIX_SIGNALS=1 -DHAVE_GETRUSAGE=1 -DHAVE_TIMES=1 -DYYTEXT_POINTER=1 -DGNUPLOT_BINARY=\"gnuplot\" -DGNUPLOT_HAS_FRAMES="
#endif

#ifndef OCTAVE_CONF_DLFCN_INCFLAGS
#define OCTAVE_CONF_DLFCN_INCFLAGS ""
#endif

#ifndef OCTAVE_CONF_DL_LD
#define OCTAVE_CONF_DL_LD "g++"
#endif

#ifndef OCTAVE_CONF_DL_LDFLAGS
#define OCTAVE_CONF_DL_LDFLAGS "-shared"
#endif

#ifndef OCTAVE_CONF_EXEEXT
#define OCTAVE_CONF_EXEEXT ""
#endif

#ifndef OCTAVE_CONF_F2CFLAGS
#define OCTAVE_CONF_F2CFLAGS ""
#endif

#ifndef OCTAVE_CONF_F2C
#define OCTAVE_CONF_F2C ""
#endif

#ifndef OCTAVE_CONF_F77
#define OCTAVE_CONF_F77 "g77"
#endif

#ifndef OCTAVE_CONF_FC
#define OCTAVE_CONF_FC "g77"
#endif

#ifndef OCTAVE_CONF_FFLAGS
#define OCTAVE_CONF_FFLAGS "-O"
#endif

#ifndef OCTAVE_CONF_FFTW_LIBS
#define OCTAVE_CONF_FFTW_LIBS ""
#endif

#ifndef OCTAVE_CONF_FLIBS
#define OCTAVE_CONF_FLIBS "-L/usr/lib/gcc-lib/i386-redhat-linux/3.2.2 -L/usr/lib/gcc-lib/i386-redhat-linux/3.2.2/../../.. -lfrtbegin -lg2c -lm -lgcc_s"
#endif

#ifndef OCTAVE_CONF_FPICFLAG
#define OCTAVE_CONF_FPICFLAG "-fPIC"
#endif

#ifndef OCTAVE_CONF_GLOB_INCFLAGS
#define OCTAVE_CONF_GLOB_INCFLAGS "-I../glob -I../glob"
#endif

#ifndef OCTAVE_CONF_INCFLAGS
#define OCTAVE_CONF_INCFLAGS "-I. -I.. -I../liboctave -I../src -I../libcruft/misc  -I../glob -I../glob"
#endif

#ifndef OCTAVE_CONF_LDFLAGS
#define OCTAVE_CONF_LDFLAGS ""
#endif

#ifndef OCTAVE_CONF_LD_CXX
#define OCTAVE_CONF_LD_CXX "g++"
#endif

#ifndef OCTAVE_CONF_LD_STATIC_FLAG
#define OCTAVE_CONF_LD_STATIC_FLAG ""
#endif

#ifndef OCTAVE_CONF_LEXLIB
#define OCTAVE_CONF_LEXLIB ""
#endif

#ifndef OCTAVE_CONF_LEX
#define OCTAVE_CONF_LEX "flex"
#endif

#ifndef OCTAVE_CONF_LFLAGS
#define OCTAVE_CONF_LFLAGS "-t -I"
#endif

#ifndef OCTAVE_CONF_LIBCRUFT
#define OCTAVE_CONF_LIBCRUFT "../libcruft/libcruft.a"
#endif

#ifndef OCTAVE_CONF_LIBDLFCN
#define OCTAVE_CONF_LIBDLFCN ""
#endif

#ifndef OCTAVE_CONF_LIBEXT
#define OCTAVE_CONF_LIBEXT "a"
#endif

#ifndef OCTAVE_CONF_LIBFLAGS
#define OCTAVE_CONF_LIBFLAGS "-L.."
#endif

#ifndef OCTAVE_CONF_LIBGLOB
#define OCTAVE_CONF_LIBGLOB "../glob/glob.o ../glob/fnmatch.o"
#endif

#ifndef OCTAVE_CONF_LIBOCTAVE
#define OCTAVE_CONF_LIBOCTAVE "../liboctave/liboctave.a"
#endif

#ifndef OCTAVE_CONF_LIBOCTINTERP
#define OCTAVE_CONF_LIBOCTINTERP "../src/liboctinterp.a"
#endif

#ifndef OCTAVE_CONF_LIBPLPLOT
#define OCTAVE_CONF_LIBPLPLOT ""
#endif

#ifndef OCTAVE_CONF_LIBREADLINE
#define OCTAVE_CONF_LIBREADLINE "-lreadline"
#endif

#ifndef OCTAVE_CONF_LIBS
#define OCTAVE_CONF_LIBS "-lreadline  -lncurses -lm "
#endif

#ifndef OCTAVE_CONF_LN_S
#define OCTAVE_CONF_LN_S "ln -s"
#endif

#ifndef OCTAVE_CONF_MKOCTFILE_DL_LDFLAGS
#define OCTAVE_CONF_MKOCTFILE_DL_LDFLAGS "-shared"
#endif

#ifndef OCTAVE_CONF_MKOCTFILE_INCFLAGS
#define OCTAVE_CONF_MKOCTFILE_INCFLAGS "-I/usr/local/include/octave-2.1.57 -I/usr/local/include/octave-2.1.57/octave -I/usr/local/include"
#endif

#ifndef OCTAVE_CONF_MKOCTFILE_LFLAGS
#define OCTAVE_CONF_MKOCTFILE_LFLAGS "-L/usr/local/lib/octave-2.1.57"
#endif

#ifndef OCTAVE_CONF_RANLIB
#define OCTAVE_CONF_RANLIB "ranlib"
#endif

#ifndef OCTAVE_CONF_RDYNAMIC_FLAG
#define OCTAVE_CONF_RDYNAMIC_FLAG ""
#endif

#ifndef OCTAVE_CONF_RLD_FLAG
#define OCTAVE_CONF_RLD_FLAG "-Wl,-rpath -Wl,/usr/local/lib/octave-2.1.57"
#endif

#ifndef OCTAVE_CONF_RUNTEST
#define OCTAVE_CONF_RUNTEST ""
#endif

#ifndef OCTAVE_CONF_SED
#define OCTAVE_CONF_SED "/bin/sed"
#endif

#ifndef OCTAVE_CONF_SHARED_LIBS
#define OCTAVE_CONF_SHARED_LIBS "false"
#endif

#ifndef OCTAVE_CONF_SHLEXT
#define OCTAVE_CONF_SHLEXT "so"
#endif

#ifndef OCTAVE_CONF_SHLEXT_VER
#define OCTAVE_CONF_SHLEXT_VER "so.2.1.57"
#endif

#ifndef OCTAVE_CONF_SH_LD
#define OCTAVE_CONF_SH_LD "g++"
#endif

#ifndef OCTAVE_CONF_SH_LDFLAGS
#define OCTAVE_CONF_SH_LDFLAGS "-shared"
#endif

#ifndef OCTAVE_CONF_SONAME_FLAGS
#define OCTAVE_CONF_SONAME_FLAGS "-Wl,-soname -Wl,oct-conf.h"
#endif

#ifndef OCTAVE_CONF_STATIC_LIBS
#define OCTAVE_CONF_STATIC_LIBS "true"
#endif

#ifndef OCTAVE_CONF_UGLY_DEFS
#define OCTAVE_CONF_UGLY_DEFS "-DPACKAGE_NAME=\"\" -DPACKAGE_TARNAME=\"\" -DPACKAGE_VERSION=\"\" -DPACKAGE_STRING=\"\" -DPACKAGE_BUGREPORT=\"\" -DOCTAVE_SOURCE=1 -DSTDC_HEADERS=1 -DHAVE_SYS_TYPES_H=1 -DHAVE_SYS_STAT_H=1 -DHAVE_STDLIB_H=1 -DHAVE_STRING_H=1 -DHAVE_MEMORY_H=1 -DHAVE_STRINGS_H=1 -DHAVE_INTTYPES_H=1 -DHAVE_STDINT_H=1 -DHAVE_UNISTD_H=1 -DSEPCHAR=1 -DSEPCHAR_STR=\":\" -D__NO_MATH_INLINES=1 -DCXX_NEW_FRIEND_TEMPLATE_DECL=1 -DCXX_ISO_COMPLIANT_LIBRARY=1 -DCXX_ABI=gnu_v3 -DHAVE_LIBM=1 -DF77_FUNC(name,NAME)=name ## _ -DF77_FUNC_(name,NAME)=name ## __ -DHAVE_GETHOSTNAME=1 -DHAVE_GETPWNAM=1 -DHAVE_DEV_T=1 -DHAVE_INO_T=1 -DHAVE_NLINK_T=1 -DHAVE_NLINK_T=1 -DHAVE_LONG_LONG_INT=1 -DHAVE_UNSIGNED_LONG_LONG_INT=1 -DHAVE_SIGSET_T=1 -DHAVE_SIG_ATOMIC_T=1 -DSIZEOF_SHORT=2 -DSIZEOF_INT=4 -DSIZEOF_LONG=4 -DSIZEOF_LONG_LONG=8 -DHAVE_ALLOCA_H=1 -DHAVE_ALLOCA=1 -DNPOS=std::string::npos -DHAVE_PLACEMENT_DELETE=1 -DHAVE_DYNAMIC_AUTO_ARRAYS=1 -DSTDC_HEADERS=1 -DHAVE_DIRENT_H=1 -DTIME_WITH_SYS_TIME=1 -DHAVE_SYS_WAIT_H=1 -DHAVE_ASSERT_H=1 -DHAVE_CURSES_H=1 -DHAVE_DLFCN_H=1 -DHAVE_FCNTL_H=1 -DHAVE_FLOAT_H=1 -DHAVE_GRP_H=1 -DHAVE_LIMITS_H=1 -DHAVE_MEMORY_H=1 -DHAVE_NCURSES_H=1 -DHAVE_POLL_H=1 -DHAVE_PWD_H=1 -DHAVE_STDLIB_H=1 -DHAVE_STRING_H=1 -DHAVE_SYS_IOCTL_H=1 -DHAVE_SYS_PARAM_H=1 -DHAVE_SYS_POLL_H=1 -DHAVE_SYS_RESOURCE_H=1 -DHAVE_SYS_SELECT_H=1 -DHAVE_SYS_STAT_H=1 -DHAVE_SYS_TIME_H=1 -DHAVE_SYS_TIMES_H=1 -DHAVE_SYS_TYPES_H=1 -DHAVE_SYS_UTSNAME_H=1 -DHAVE_TERMCAP_H=1 -DHAVE_UNISTD_H=1 -DHAVE_VARARGS_H=1 -DHAVE_SSTREAM=1 -DHAVE_TERMIO_H=1 -DHAVE_SGTTY_H=1 -DHAVE_GLOB_H=1 -DHAVE_FNMATCH_H=1 -DHAVE_ATEXIT=1 -DHAVE_BASENAME=1 -DHAVE_BCOPY=1 -DHAVE_BZERO=1 -DHAVE_DUP2=1 -DHAVE_ENDGRENT=1 -DHAVE_ENDPWENT=1 -DHAVE_EXECVP=1 -DHAVE_FCNTL=1 -DHAVE_FORK=1 -DHAVE_GETCWD=1 -DHAVE_GETEGID=1 -DHAVE_GETEUID=1 -DHAVE_GETGID=1 -DHAVE_GETGRENT=1 -DHAVE_GETGRGID=1 -DHAVE_GETGRNAM=1 -DHAVE_GETPGRP=1 -DHAVE_GETPID=1 -DHAVE_GETPPID=1 -DHAVE_GETPWENT=1 -DHAVE_GETPWUID=1 -DHAVE_GETTIMEOFDAY=1 -DHAVE_GETUID=1 -DHAVE_GETWD=1 -DHAVE_KILL=1 -DHAVE_LINK=1 -DHAVE_LOCALTIME_R=1 -DHAVE_LSTAT=1 -DHAVE_MEMMOVE=1 -DHAVE_MKDIR=1 -DHAVE_MKFIFO=1 -DHAVE_MKSTEMP=1 -DHAVE_ON_EXIT=1 -DHAVE_PIPE=1 -DHAVE_POLL=1 -DHAVE_PUTENV=1 -DHAVE_RAISE=1 -DHAVE_READLINK=1 -DHAVE_RENAME=1 -DHAVE_RINDEX=1 -DHAVE_RMDIR=1 -DHAVE_SELECT=1 -DHAVE_SETGRENT=1 -DHAVE_SETPWENT=1 -DHAVE_SETVBUF=1 -DHAVE_SIGACTION=1 -DHAVE_SIGLONGJMP=1 -DHAVE_SIGPENDING=1 -DHAVE_SIGPROCMASK=1 -DHAVE_SIGSUSPEND=1 -DHAVE_STAT=1 -DHAVE_STRCASECMP=1 -DHAVE_STRDUP=1 -DHAVE_STRERROR=1 -DHAVE_STRFTIME=1 -DHAVE_STRNCASECMP=1 -DHAVE_STRPTIME=1 -DHAVE_SYMLINK=1 -DHAVE_TEMPNAM=1 -DHAVE_UMASK=1 -DHAVE_UNLINK=1 -DHAVE_USLEEP=1 -DHAVE_VFPRINTF=1 -DHAVE_VSPRINTF=1 -DHAVE_VSNPRINTF=1 -DHAVE_WAITPID=1 -DHAVE_TIMEVAL=1 -DHAVE_FINITE=1 -DHAVE_ISNAN=1 -DHAVE_ISINF=1 -DHAVE_COPYSIGN=1 -DHAVE_ACOSH=1 -DHAVE_ASINH=1 -DHAVE_ATANH=1 -DHAVE_ERF=1 -DHAVE_ERFC=1 -DHAVE_STRUCT_STAT_ST_BLKSIZE=1 -DHAVE_STRUCT_STAT_ST_BLOCKS=1 -DHAVE_STRUCT_STAT_ST_RDEV=1 -DHAVE_STRUCT_TM_TM_ZONE=1 -DHAVE_TM_ZONE=1 -DUSE_READLINE=1 -DEXCEPTION_IN_MATH=1 -DRETSIGTYPE=void -DSYS_SIGLIST_DECLARED=1 -DHAVE_SYS_SIGLIST=1 -DHAVE_POSIX_SIGNALS=1 -DHAVE_GETRUSAGE=1 -DHAVE_TIMES=1 -DYYTEXT_POINTER=1 -DGNUPLOT_BINARY=\"gnuplot\" -DGNUPLOT_HAS_FRAMES="
#endif

#ifndef OCTAVE_CONF_ENABLE_DYNAMIC_LINKING
#define OCTAVE_CONF_ENABLE_DYNAMIC_LINKING "false"
#endif

#ifndef OCTAVE_CONF_XTRA_CFLAGS
#define OCTAVE_CONF_XTRA_CFLAGS "-mieee-fp"
#endif

#ifndef OCTAVE_CONF_XTRA_CXXFLAGS
#define OCTAVE_CONF_XTRA_CXXFLAGS "-mieee-fp"
#endif

#ifndef OCTAVE_CONF_YACC
#define OCTAVE_CONF_YACC "bison -y"
#endif

#ifndef OCTAVE_CONF_YFLAGS
#define OCTAVE_CONF_YFLAGS "-dv"
#endif

#ifndef OCTAVE_CONF_config_opts
#define OCTAVE_CONF_config_opts ""
#endif

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; page-delimiter: "^/\\*" ***
;;; End: ***
*/
