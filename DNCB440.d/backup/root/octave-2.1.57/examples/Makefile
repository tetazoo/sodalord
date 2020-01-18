#
# Makefile for octave's examples directory
#
# John W. Eaton
# jwe@bevo.che.wisc.edu
# University of Wisconsin-Madison
# Department of Chemical Engineering

TOPDIR = ..

srcdir = .
top_srcdir = ..


include $(TOPDIR)/Makeconf

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_SCRIPT = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644

SCRIPTS = info-emacs-info info-emacs-octave-help

SOURCES = hello.cc oregonator.m oregonator.cc make_int.cc

DISTFILES = Makefile.in $(SOURCES) $(SCRIPTS)

BINDISTFILES = $(addprefix $(srcdir)/, $(SCRIPTS))

SUBDIRS = 

DISTSUBDIRS = 

all:
.PHONY: all

install install-strip:
	for f in $(SCRIPTS); do \
	  $(INSTALL_SCRIPT) $(srcdir)/$$f $(DESTDIR)$(archlibdir)/$$f; \
	done
.PHONY: install install-strip

tags:
	ctags $(SOURCES)

TAGS: $(SOURCES)
	etags $(SOURCES)

clean mostlyclean:
.PHONY: clean mostlyclean

distclean:
	rm -f Makefile
.PHONY: distclean

maintainer-clean: distclean
	rm -f tags TAGS
.PHONY: maintainer-clean

dist:
	ln $(DISTFILES) ../`cat ../.fname`/examples
.PHONY: dist

bin-dist:
	if [ -n "$(BINDISTFILES)" ]; then \
	  ln $(BINDISTFILES) ../`cat ../.fname`/examples; \
	fi
.PHONY: bin-dist
