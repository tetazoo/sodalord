#
# Makefile for octave's emacs directory
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

EL_FILES = octave-hlp.el octave-inf.el octave-mod.el

SOURCES = $(EL_FILES) otags

DISTFILES = Makefile.in $(EL_FILES) otags NEWS TODO README

BINDISTFILES = $(addprefix $(srcdir)/, $(EL_FILES) otags NEWS TODO README)

all:
.PHONY: all

install install-strip:
	$(INSTALL_SCRIPT) otags $(bindir)/otags
.PHONY: install install-strip

uninstall:
	rm -f $(bindir)/otags
.PHONY: uninstall

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
	ln $(DISTFILES) ../`cat ../.fname`/emacs
.PHONY: dist

bin-dist:
	if [ -n "$(BINDISTFILES)" ]; then \
	  ln $(BINDISTFILES) ../`cat ../.fname`/emacs; \
	fi
.PHONY: bin-dist
