#
# Makefile for octave's scripts/statistics/tests directory
#
# John W. Eaton
# jwe@bevo.che.wisc.edu
# University of Wisconsin-Madison
# Department of Chemical Engineering

TOPDIR = ../../..

script_sub_dir = statistics/tests

srcdir = .
top_srcdir = ../..


include $(TOPDIR)/Makeconf

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644

SOURCES = *.m

DISTFILES = Makefile.in $(SOURCES)

FCN_FILES = $(wildcard $(srcdir)/*.m)
FCN_FILES_NO_DIR = $(notdir $(FCN_FILES))

BINDISTFILES = $(FCN_FILES)

all:
.PHONY: all

install install-strip:
	$(do-script-install)
.PHONY: install install-strip

uninstall:
	$(do-script-uninstall)
.PHONY: uninstall

clean:
.PHONY: clean

tags: $(SOURCES)
	ctags $(SOURCES)

TAGS: $(SOURCES)
	etags $(SOURCES)

mostlyclean: clean
.PHONY: mostlyclean

distclean: clean
	rm -f Makefile
.PHONY: distclean

maintainer-clean: distclean
	rm -f tags TAGS
.PHONY: maintainer-clean

dist:
	ln $(DISTFILES) ../../../`cat ../../../.fname`/scripts/$(script_sub_dir)
.PHONY: dist

bin-dist:
	ln $(BINDISTFILES) ../../../`cat ../../../.fname`/scripts/$(script_sub_dir)
.PHONY: bin-dist
