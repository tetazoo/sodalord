/* c-auto.h.  Generated by configure.  */
/* c-auto.in.  Generated from configure.in by autoheader.  */
/* acconfig.h -- used by autoheader when generating c-auto.in.

   If you're thinking of editing acconfig.h to fix a configuration
   problem, don't. Edit the c-auto.h file created by configure,
   instead.  Even better, fix configure to give the right answer.  */

/* kpathsea: the version string. */
#define KPSEVERSION "kpathsea version 3.2"
/* web2c: the version string. */
#define WEB2CVERSION "REPLACE-WITH-WEB2CVERSION"

/* kpathsea/configure.in tests for these functions with
   kb_AC_KLIBTOOL_REPLACE_FUNCS, and naturally Autoheader doesn't know
   about that macro.  Since the shared library stuff is all preliminary
   anyway, I decided not to change Autoheader, but rather to hack them
   in here.  */
#define HAVE_BASENAME 1
#define HAVE_PUTENV 1
#define HAVE_STRCASECMP 1
#define HAVE_STRTOL 1
#define HAVE_STRSTR 1


/* Define if your compiler understands prototypes.  */
#define HAVE_PROTOTYPES 1

/* Define if your putenv doesn't waste space when the same environment
   variable is assigned more than once, with different (malloced)
   values.  This is true only on NetBSD/FreeBSD, as far as I know. See
   xputenv.c.  */
/* #undef SMART_PUTENV */

/* Define if getcwd if implemented using fork or vfork.  Let me know
   if you have to add this by hand because configure failed to detect
   it. */
/* #undef GETCWD_FORKS */

/* Define if you are using GNU libc or otherwise have global variables
   `program_invocation_name' and `program_invocation_short_name'.  */
#define HAVE_PROGRAM_INVOCATION_NAME 1

/* Define if you get clashes concerning wchar_t, between X's include
   files and system includes.  */
/* #undef FOIL_X_WCHAR_T */

/* tex: Define to enable --ipc.  */
/* #undef IPC */

/* all: Define to enable running scripts when missing input files.  */
#define MAKE_TEX_MF_BY_DEFAULT 1
#define MAKE_TEX_PK_BY_DEFAULT 1
#define MAKE_TEX_TEX_BY_DEFAULT 0
#define MAKE_TEX_TFM_BY_DEFAULT 1
#define MAKE_OMEGA_OFM_BY_DEFAULT 1
#define MAKE_OMEGA_OCP_BY_DEFAULT 1

/* web2c: Define if gcc asm needs _ on external symbols.  */
/* #undef ASM_NEEDS_UNDERSCORE */

/* web2c: Define when using system-specific files for arithmetic.  */
/* #undef ASM_SCALED_FRACTION */

/* web2c: Define to enable HackyInputFileNameForCoreDump.tex.  */
/* #undef FUNNY_CORE_DUMP */

/* web2c: Define to disable architecture-independent dump files.
   Faster on LittleEndian architectures.  */
/* #undef NO_DUMP_SHARE */

/* web2c: Default editor for interactive `e' option. */
#define EDITOR "vi +%d %s"

/* web2c: Window system support for Metafont. */
/* #undef EPSFWIN */
/* #undef HP2627WIN */
/* #undef MFTALKWIN */
/* #undef NEXTWIN */
/* #undef REGISWIN */
/* #undef SUNWIN */
/* #undef TEKTRONIXWIN */
/* #undef UNITERMWIN */
/* #undef X11WIN */

/* xdvik: Define if you have SIGIO, F_SETOWN, and FASYNC.  */
/* #undef HAVE_SIGIO */

/* xdvik: Define to avoid using any toolkit (and consequently omit lots
   of features).  */
/* #undef NOTOOL */

/* Define to 1 if the `closedir' function returns void instead of `int'. */
/* #undef CLOSEDIR_VOID */

/* Define to 1 if you have the <assert.h> header file. */
#define HAVE_ASSERT_H 1

/* Define to 1 if you have the `basename' function. */
#define HAVE_BASENAME 1

/* Define to 1 if you have the `bcopy' function. */
#define HAVE_BCOPY 1

/* Define to 1 if you have the <dirent.h> header file, and it defines `DIR'.
   */
#define HAVE_DIRENT_H 1

/* Define to 1 if you have the <float.h> header file. */
#define HAVE_FLOAT_H 1

/* Define to 1 if you have the `getcwd' function. */
#define HAVE_GETCWD 1

/* Define to 1 if you have the `getwd' function. */
#define HAVE_GETWD 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the <ndir.h> header file, and it defines `DIR'. */
/* #undef HAVE_NDIR_H */

/* Define to 1 if you have the `putenv' function. */
#define HAVE_PUTENV 1

/* Define to 1 if you have the <pwd.h> header file. */
#define HAVE_PWD_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strcasecmp' function. */
#define HAVE_STRCASECMP 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strstr' function. */
#define HAVE_STRSTR 1

/* Define to 1 if you have the `strtol' function. */
#define HAVE_STRTOL 1

/* Define to 1 if you have the <sys/dir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_DIR_H */

/* Define to 1 if you have the <sys/ndir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_NDIR_H */

/* Define to 1 if you have the <sys/param.h> header file. */
#define HAVE_SYS_PARAM_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME ""

/* Define to the full name and version of this package. */
#define PACKAGE_STRING ""

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME ""

/* Define to the version of this package. */
#define PACKAGE_VERSION ""

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */