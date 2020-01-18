## Process this file with automake to produce Makefile.in

AUTOMAKE_OPTIONS = 1.3

# library interface 2.0, gd release 2.0.1
libgd_la_LDFLAGS = -version-info 2:0

lib_LTLIBRARIES = libgd.la

include_HEADERS = gd.h	 gdcache.h  gdfontl.h	gdfonts.h \
		gd_io.h  gdfontg.h  gdfontmb.h	gdfontt.h

libgd_la_SOURCES = gd.c		  gd_io.c	gd_topal.c  gdfonts.c \
	gd_io_dp.c	gd_wbmp.c   gdfontt.c	   \
	gd_io_file.c	gdcache.c   gdft.c \
	gd_io_ss.c	gdhelpers.c    gdxpm.c \
	gd_jpeg.c	gdfontg.c   gdkanji.c \
	gd_gd.c		  gd_png.c	gdfontl.c   \
	gd_gd2.c	  gd_ss.c	gdfontmb.c  gdtables.c \
	wbmp.c

bin_PROGRAMS = pngtogd webpng pngtogd2 gdtopng gd2topng gd2copypal \
	gdparttopng gd2time 

noinst_PROGRAMS = gddemo testac gdtest gdtestft

gddemo_SOURCES = gddemo.c gd.h gdfonts.h gdfontg.h
gddemo_LDADD = libgd.la

testac_SOURCES = testac.c gd.h
testac_LDADD = libgd.la

pngtogd_SOURCES = pngtogd.c gd.h
pngtogd_LDADD = libgd.la

webpng_SOURCES = webpng.c gd.h
webpng_LDADD = libgd.la

pngtogd2_SOURCES = pngtogd2.c gd.h
pngtogd2_LDADD = libgd.la

gdtopng_SOURCES = gdtopng.c gd.h
gdtopng_LDADD = libgd.la

gd2topng_SOURCES = gd2topng.c gd.h
gd2topng_LDADD = libgd.la

gd2copypal_SOURCES = gd2copypal.c gd.h
gd2copypal_LDADD = libgd.la

gdparttopng_SOURCES = gdparttopng.c gd.h
gdparttopng_LDADD = libgd.la

gdtest_SOURCES = gdtest.c gd.h
gdtest_LDADD = libgd.la

gd2time_SOURCES = gd2time.c gd.h
gd2time_LDADD = libgd.la

gdtestft_SOURCES = gdtestft.c gd.h
gdtestft_LDADD = libgd.la

EXTRA_DIST = demoin.png index.html test/*

CLEANFILES = demoout.png
