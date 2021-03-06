#
# Makefile for octave's scripts directory
#
# John W. Eaton
# jwe@bevo.che.wisc.edu
# University of Wisconsin-Madison
# Department of Chemical Engineering

TOPDIR = ..

script_sub_dir = .

srcdir = .
top_srcdir = .


include $(TOPDIR)/Makeconf

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644

SOURCES = # *.m

ALL_M_FILES1 := $(shell find $(srcdir) -name '*.m' -print)
ALL_M_FILES := $(patsubst $(srcdir)/%, %, $(ALL_M_FILES1))

DISTFILES = Makefile.in ChangeLog $(SOURCES) configure.in \
	configure mkinstalldirs mkdoc mkpkgadd gethelp.cc \
	skip-autoheader DOCSTRINGS

SUBDIRS = audio control deprecated elfun finance general image io \
	linear-algebra miscellaneous plot polynomial quaternion \
	set signal specfun special-matrix startup statistics \
	strings time

DISTSUBDIRS = $(SUBDIRS)

BINDISTSUBDIRS = $(SUBDIRS)

FCN_FILES = # $(wildcard $(srcdir)/*.m)
FCN_FILES_NO_DIR = # $(notdir $(FCN_FILES))

all: $(SUBDIRS) DOCSTRINGS
.PHONY: all

$(SUBDIRS):
	$(MAKE) -C $@ all
.PHONY: $(SUBDIRS)

DOCSTRINGS: gethelp$(BUILD_EXEEXT) mkdoc $(ALL_M_FILES)
	$(srcdir)/mkdoc $(srcdir) > $@.t
	mv $@.t $@

gethelp$(BUILD_EXEEXT): gethelp.cc
	$(BUILD_CXX) $(BUILD_CXXFLAGS) -o $@ $^ $(BUILD_LDFLAGS)

install install-strip uninstall clean mostlyclean distclean maintainer-clean::
	@$(subdir-for-command)
.PHONY: install install-strip uninstall
.PHONY: clean mostlyclean distclean maintainer-clean

install install-strip::
	ls -LR $(DESTDIR)$(datadir)/octave > $(DESTDIR)$(datadir)/octave/ls-R
	ls -LR $(DESTDIR)$(libexecdir)/octave > $(DESTDIR)$(libexecdir)/octave/ls-R

uninstall::
	rm -f $(DESTDIR)$(datadir)/octave/ls-R $(DESTDIR)$(libexecdir)/octave/ls-R

tags TAGS:: $(SOURCES)
	$(SUBDIR_FOR_COMMAND)

tags::
	ctags $(SOURCES)

TAGS:: $(SOURCES)
	etags $(SOURCES)

clean::
	rm -f gethelp$(BUILD_EXEEXT)

distclean::
	rm -f gethelp$(BUILD_EXEEXT)
	rm -f Makefile config.log config.status DOCSTRINGS
	-rm -rf autom4te.cache

maintainer-clean::
	rm -f gethelp$(BUILD_EXEEXT)
	rm -f Makefile config.log config.status DOCSTRINGS
	rm -f tags TAGS configure
	-rm -rf autom4te.cache

dist:
	ln $(DISTFILES) ../`cat ../.fname`/scripts
	for dir in $(DISTSUBDIRS); do mkdir ../`cat ../.fname`/scripts/$$dir; $(MAKE) -C $$dir $@; done
.PHONY: dist

bin-dist:
	for dir in $(BINDISTSUBDIRS); do mkdir ../`cat ../.fname`/scripts/$$dir; $(MAKE) -C $$dir $@; done
.PHONY: bin-dist
