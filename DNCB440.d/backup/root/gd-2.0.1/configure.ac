dnl Process this file with autoconf to produce a configure script.
AC_INIT(gd.c)
AM_INIT_AUTOMAKE(gd, 1.8.4)

dnl Checks for programs.
AC_PROG_CC
AC_ISC_POSIX
AM_PROG_LIBTOOL
AC_PROG_INSTALL
AC_PATH_X

dnl Set LDFLAGS and CPPFLAGS so that AC_CHECK_LIBS can find installed libs in --prefix dir
LDFLAGS="$LDFLAGS -L$libdir -L$x_libraries"
CPPFLAGS="$CPPFLAGS -I/usr/X11R6/include/freetype2 -I/usr/include/freetype2 -I$includedir -I$x_includes"

dnl Sometimes math libs are in libc, so no warning if libm not found
AC_CHECK_LIB(m,main)

dnl The libraries libz and libpng are required.
AC_CHECK_LIB(z,deflate,,AC_MSG_ERROR(libz not found.))
AC_CHECK_LIB(png,png_check_sig,,AC_MSG_ERROR(libpng not found.))

dnl User can select whether or not to support JPEG
AC_ARG_ENABLE(jpeg,
	[  --enable-jpeg           enable support for JPEG [default=no]],
	[ 
	  AC_CHECK_HEADERS(jpeglib.h,,AC_MSG_WARN(libgd will be built without support for JPEG.))
	  AC_CHECK_LIB(jpeg,jpeg_start_compress,,AC_MSG_WARN(libgd will be built without support for JPEG.))
	])

dnl User can select whether or not to support FreeType
AC_ARG_ENABLE(freetype,
	[  --enable-freetype       enable support for FreeType [default=no]],
	[ 
	  AC_CHECK_HEADERS(freetype/freetype.h,,AC_MSG_WARN(libgd will be built without Freetype support.))
	  AC_CHECK_LIB(freetype,FT_Init_FreeType,,AC_MSG_WARN(libgd will be built without Freetype support.))
	])

dnl User can select whether or not to support Xpm
AC_ARG_ENABLE(xpm,
	[  --enable-xpm            enable support for XPM [default=no]],
	[ 
	  AC_CHECK_HEADERS(X11/xpm.h,,AC_MSG_WARN(libgd will be built without support for XPM images.))
	  AC_CHECK_LIB(Xpm,XpmCreateImageFromData,
	      		   [
			       LIBS="$LIBS -lX11 -lXpm"
			       AC_DEFINE(HAVE_LIBXPM)
			    ],
	                    AC_MSG_WARN(libgd will be built without support for XPM images.),
                            -lX11)
	])

dnl Check for required header files
AC_HEADER_STDC
AC_CHECK_HEADERS(malloc.h unistd.h)
AC_CHECK_HEADERS(zlib.h,,AC_MSG_ERROR(zlib.h not found.))
AC_CHECK_HEADERS(png.h,,AC_MSG_ERROR(png.h not found.))

dnl Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST

AC_OUTPUT(Makefile)
