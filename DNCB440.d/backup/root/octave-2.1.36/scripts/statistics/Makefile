#
# Makefile for octave's scripts/statistics directory
#
# John W. Eaton
# jwe@bevo.che.wisc.edu
# University of Wisconsin-Madison
# Department of Chemical Engineering

TOPDIR = ../..

script_sub_dir = statistics

srcdir = .
top_srcdir = ..


include $(TOPDIR)/Makeconf

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644

DISTFILES = Makefile.in

SUBDIRS = base distributions models tests

DISTSUBDIRS = $(SUBDIRS)

BINDISTSUBDIRS = $(SUBDIRS)

all: $(SUBDIRS)
.PHONY: all

$(SUBDIRS):
	$(MAKE) -C $@ all
.PHONY: $(SUBDIRS)

install install-strip uninstall clean mostlyclean distclean maintainer-clean::
	@$(subdir-for-command)
.PHONY: install install-strip uninstall
.PHONY: clean mostlyclean distclean maintainer-clean

tags TAGS:
	$(SUBDIR_FOR_COMMAND)

distclean::
	rm -f Makefile

maintainer-clean::
	rm -f tags TAGS Makefile

dist:
	ln $(DISTFILES) ../../`cat ../../.fname`/scripts/statistics
	for dir in $(DISTSUBDIRS); do mkdir ../../`cat ../../.fname`/scripts/statistics/$$dir; $(MAKE) -C $$dir $@; done
.PHONY: dist

bin-dist:
	for dir in $(BINDISTSUBDIRS); do mkdir ../../`cat ../../.fname`/scripts/statistics/$$dir; $(MAKE) -C $$dir $@; done
.PHONY: bin-dist
