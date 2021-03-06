#
# Makefile for octave's libcruft/misc directory
#
# John W. Eaton
# jwe@bevo.che.wisc.edu
# University of Wisconsin-Madison
# Department of Chemical Engineering

TOPDIR = ../..

srcdir = .
top_srcdir = ../..


SPECIAL_SRC := machar.c f77-extern.cc f77-fcn.c lo-error.c cquit.c quit.cc

DEP_1 := $(patsubst %.c, %.d, $(SPECIAL_SRC))
MAKEDEPS := $(patsubst %.cc, %.d, $(DEP_1))

SPECIAL_INCLUDE := f77-fcn.h lo-error.h quit.h

SPECIAL:= d1mach-tst.for $(SPECIAL_SRC) $(SPECIAL_INCLUDE)

SPECIAL_DEPEND := machar.o f77-extern.o f77-fcn.o lo-error.o quit.o

EXTERNAL_DISTFILES = $(DISTFILES)

include $(TOPDIR)/Makeconf

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644

INCLUDES := f77-fcn.h lo-error.h quit.h

ifeq ($(SHARED_LIBS), true)
  ifdef CPICFLAG
    CPICDEP := pic/machar.o pic/f77-fcn.o
  endif
  ifdef CXXPICFLAG
    CXXPICDEP := pic/f77-extern.o pic/lo-error.o pic/quit.o
  endif
  SPECIAL_PICDEPEND := $(CPICDEP) $(CXXPICDEP)
endif

include ../Makerules

install install-strip::
	$(top_srcdir)/mkinstalldirs $(DESTDIR)$(octincludedir)/octave
	for f in $(INCLUDES); do \
	  rm -f $(DESTDIR)$(octincludedir)/octave/$$f; \
	  $(INSTALL_DATA) $(srcdir)/$$f $(DESTDIR)$(octincludedir)/octave/$$f; \
	done
	$(mk-includedir-link)

uninstall::
	for f in $(INCLUDES); do rm -f $(DESTDIR)$(octincludedir)/octave/$$f; done

# Don't optimize.

XCC = $(patsubst -O%, , $(CC))
XALL_CFLAGS = $(patsubst -O%, , $(ALL_CFLAGS))

machar.o: $(srcdir)/machar.c
	$(XCC) -c $(CPPFLAGS) $(XALL_CFLAGS) -DDP $<

pic/machar.o: $(srcdir)/machar.c
	$(XCC) -c $(CPPFLAGS) $(CPICFLAG) $(XALL_CFLAGS) -DDP $< -o $@

ifndef omit_deps
-include $(MAKEDEPS)
endif
