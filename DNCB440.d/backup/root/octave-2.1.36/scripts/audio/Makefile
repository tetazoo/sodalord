#
# Makefile for octave's scripts/audio directory
#
# John W. Eaton
# jwe@bevo.che.wisc.edu
# University of Wisconsin-Madison
# Department of Chemical Engineering

TOPDIR = ../..

script_sub_dir = audio

srcdir = .
top_srcdir = ..


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
	$(top_srcdir)/mkinstalldirs $(fcnfiledir)/$(script_sub_dir)
	for f in $(FCN_FILES_NO_DIR); do \
	  rm -f $(fcnfiledir)/$(script_sub_dir)/$$f; \
	  $(INSTALL_DATA) $(srcdir)/$$f $(fcnfiledir)/$(script_sub_dir)/$$f; \
	done
.PHONY: install install-strip

uninstall:
	for f in $(FCN_FILES_NO_DIR); \
	  do rm -f $(fcnfiledir)/$(script_sub_dir)/$$f; \
	done
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
	ln $(DISTFILES) ../../`cat ../../.fname`/scripts/audio
.PHONY: dist

bin-dist:
	ln $(BINDISTFILES) ../../`cat ../../.fname`/scripts/audio
.PHONY: bin-dist
