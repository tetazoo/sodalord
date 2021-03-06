#
# Makefile for octave's liboctave directory
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
INSTALL_DATA = ${INSTALL} -m 644

LIBOCTAVE_LFLAGS = -L../libcruft -L../readline -L../kpathsea \
	-L../glob -L. $(RLD_FLAG)

LIBOCTAVE_LIBS = -lcruft -lreadline -lkpathsea -lglob

MATRIX_INC := Array.h Array2.h Array3.h ArrayN.h DiagArray2.h Array-flags.h \
	Array-idx.h Array2-idx.h Array3-idx.h ArrayN-idx.h MArray-defs.h \
	MArray.h MArray2.h MDiagArray2.h Matrix.h \
	base-lu.h mx-base.h mx-op-defs.h mx-defs.h mx-ext.h \
	CColVector.h CDiagMatrix.h CMatrix.h CRowVector.h CmplxAEPBAL.h \
	CmplxCHOL.h CmplxDET.h CmplxHESS.h CmplxLU.h CmplxQR.h \
	CmplxQRP.h CmplxSCHUR.h CmplxSVD.h EIG.h boolMatrix.h chMatrix.h \
	dColVector.h dDiagMatrix.h dMatrix.h dRowVector.h dbleAEPBAL.h \
	dbleCHOL.h dbleDET.h dbleHESS.h dbleLU.h dbleQR.h \
	dbleQRP.h dbleSCHUR.h dbleSVD.h

MX_OP_INC := mx-cdm-cm.h mx-cdm-cs.h mx-cdm-dm.h mx-cdm-m.h \
	mx-cdm-s.h mx-cm-cdm.h mx-cm-dm.h mx-cm-m.h mx-cm-s.h \
	mx-cs-cdm.h mx-cs-dm.h mx-cs-m.h mx-dm-cdm.h mx-dm-cm.h \
	mx-dm-cs.h mx-dm-m.h mx-dm-s.h mx-m-cdm.h mx-m-cm.h \
	mx-m-cs.h mx-m-dm.h mx-s-cdm.h mx-s-cm.h mx-s-dm.h

VX_OP_INC := vx-ccv-s.h vx-crv-s.h vx-cs-cv.h vx-cs-rv.h vx-cv-cs.h \
	vx-rv-cs.h vx-s-ccv.h vx-s-crv.h \
	vx-rv-crv.h vx-cv-ccv.h vx-crv-rv.h vx-ccv-cv.h

INCLUDES := Bounds.h CollocWt.h DAE.h DAEFunc.h DASPK.h DASSL.h FEGrid.h \
	LinConst.h LP.h LPsolve.h LSODE.h NLConst.h NLEqn.h NLFunc.h \
	NLP.h ODE.h ODEFunc.h Objective.h QP.h Quad.h Range.h base-de.h \
	base-min.h byte-swap.h cmd-edit.h cmd-hist.h data-conv.h \
	dir-ops.h file-ops.h file-stat.h getopt.h glob-match.h \
	idx-vector.h lo-ieee.h lo-mappers.h lo-specfun.h lo-sysdep.h \
	lo-utils.h mach-info.h oct-alloc.h oct-cmplx.h oct-env.h \
	oct-fftw.h oct-getopt.h oct-group.h oct-kpse.h oct-passwd.h \
	oct-rl-edit.h oct-rl-hist.h oct-shlib.h oct-syscalls.h oct-time.h \
	pathlen.h pathsearch.h prog-args.h statdefs.h str-vec.h sun-utils.h \
	sysdir.h systime.h syswait.h \
	$(MATRIX_INC) \
	$(MX_OP_INC) \
	$(VX_OP_INC)

TEMPLATE_SRC := Array.cc Array2.cc Array3.cc ArrayN.cc DiagArray2.cc \
	MArray.cc MArray2.cc MDiagArray2.cc base-lu.cc

TI_SRC := Array-C.cc Array-b.cc Array-ch.cc Array-i.cc Array-d.cc \
	Array-s.cc Array-str.cc Array-idx-vec.cc \
	MArray-C.cc MArray-ch.cc MArray-i.cc MArray-d.cc MArray-s.cc

MATRIX_SRC := Array-flags.cc CColVector.cc CDiagMatrix.cc CMatrix.cc \
	CRowVector.cc CmplxAEPBAL.cc CmplxCHOL.cc CmplxDET.cc \
	CmplxHESS.cc CmplxLU.cc CmplxQR.cc CmplxQRP.cc CmplxSCHUR.cc \
	CmplxSVD.cc EIG.cc MArray-misc.cc boolMatrix.cc chMatrix.cc \
	dColVector.cc dDiagMatrix.cc dMatrix.cc dRowVector.cc \
	dbleAEPBAL.cc dbleCHOL.cc dbleDET.cc dbleHESS.cc dbleLU.cc \
	dbleQR.cc dbleQRP.cc dbleSCHUR.cc dbleSVD.cc

MX_OP_SRC := mx-cdm-cm.cc mx-cdm-cs.cc mx-cdm-dm.cc mx-cdm-m.cc \
	mx-cdm-s.cc mx-cm-cdm.cc mx-cm-dm.cc mx-cm-m.cc mx-cm-s.cc \
	mx-cs-cdm.cc mx-cs-dm.cc mx-cs-m.cc mx-dm-cdm.cc mx-dm-cm.cc \
	mx-dm-cs.cc mx-dm-m.cc mx-dm-s.cc mx-m-cdm.cc mx-m-cm.cc \
	mx-m-cs.cc mx-m-dm.cc mx-s-cdm.cc mx-s-cm.cc mx-s-dm.cc

VX_OP_SRC := vx-ccv-s.cc vx-crv-s.cc vx-cs-cv.cc vx-cs-rv.cc vx-cv-cs.cc \
	vx-rv-cs.cc vx-s-ccv.cc vx-s-crv.cc \
	vx-rv-crv.cc vx-cv-ccv.cc vx-crv-rv.cc vx-ccv-cv.cc

LIBOCTAVE_CXX_SOURCES := Bounds.cc CollocWt.cc DAE.cc DASPK.cc \
	DASSL.cc FEGrid.cc LinConst.cc LPsolve.cc LSODE.cc \
	NLEqn.cc Quad.cc Range.cc data-conv.cc dir-ops.cc \
	file-ops.cc file-stat.cc glob-match.cc idx-vector.cc \
	lo-ieee.cc lo-mappers.cc lo-specfun.cc lo-sysdep.cc \
	lo-utils.cc mach-info.cc oct-alloc.cc oct-env.cc \
	oct-fftw.cc oct-group.cc oct-passwd.cc oct-shlib.cc \
	oct-syscalls.cc oct-time.cc prog-args.cc str-vec.cc \
	$(TEMPLATE_SRC) \
	$(TI_SRC) \
	$(MATRIX_SRC) \
	$(MX_OP_SRC) \
	$(VX_OP_SRC)

LIBOCTAVE_C_SOURCES := f2c-main.c filemode.c getopt.c getopt1.c \
	lo-cutils.c mkdir.c oct-getopt.c rename.c rmdir.c strftime.c \
	strptime.c tempname.c tempnam.c

LIBOCTAVE_SOURCES := $(LIBOCTAVE_CXX_SOURCES) $(LIBOCTAVE_C_SOURCES)

LIBOCT_READLINE_CXX_SOURCES := cmd-edit.cc cmd-hist.cc

LIBOCT_READLINE_C_SOURCES := oct-rl-edit.c oct-rl-hist.c

LIBOCT_READLINE_SOURCES := $(LIBOCT_READLINE_CXX_SOURCES) $(LIBOCT_READLINE_C_SOURCES)

LIBOCT_PATHSEARCH_CXX_SOURCES := pathsearch.cc

LIBOCT_PATHSEARCH_C_SOURCES := oct-kpse.c

LIBOCT_PATHSEARCH_SOURCES := \
	$(LIBOCT_PATHSEARCH_C_SOURCES) $(LIBOCT_PATHSEARCH_CXX_SOURCES)

SOURCES := \
	$(LIBOCTAVE_SOURCES) \
	$(LIBOCT_READLINE_SOURCES) \
	$(LIBOCT_PATHSEARCH_SOURCES)

EXTRAS := mx-inlines.cc

INCLUDES_FOR_INSTALL := $(INCLUDES) $(TEMPLATE_SRC) $(EXTRAS)

DISTFILES := Makefile.in ChangeLog $(SOURCES) $(INCLUDES) $(EXTRAS)

ifeq ($(SHARED_LIBS), true)
  BINDISTLIBS = liboctave/liboctave
  BINDISTFILES = liboctave.$(SHLEXT_VER)
endif

MAKEDEPS_1 := $(patsubst %.cc, %.d, $(SOURCES))
MAKEDEPS := $(patsubst %.c, %.d, $(MAKEDEPS_1))

LIBOCTAVE_OBJECTS := \
	$(LIBOCTAVE_CXX_SOURCES:.cc=.o) \
	$(LIBOCTAVE_C_SOURCES:.c=.o)

LIBOCT_READLINE_OBJECTS := \
	$(LIBOCT_READLINE_CXX_SOURCES:.cc=.o) \
	$(LIBOCT_READLINE_C_SOURCES:.c=.o)

LIBOCT_PATHSEARCH_OBJECTS := \
	$(LIBOCT_PATHSEARCH_CXX_SOURCES:.cc=.o) \
	$(LIBOCT_PATHSEARCH_C_SOURCES:.c=.o)

ifeq ($(SHARED_LIBS), true)
  ifdef CXXPICFLAG
    LIBOCTAVE_PICOBJ := $(addprefix pic/, $(LIBOCTAVE_OBJECTS))
    LIBOCT_READLINE_PICOBJ := $(addprefix pic/, $(LIBOCT_READLINE_OBJECTS))
    LIBOCT_PATHSEARCH_PICOBJ := $(addprefix pic/, $(LIBOCT_PATHSEARCH_OBJECTS))
  else
    LIBOCTAVE_PICOBJ := $(LIBOCTAVE_OBJECTS)
    LIBOCT_READLINE_PICOBJ := $(LIBOCT_READLINE_OBJECTS)
    LIBOCT_PATHSEARCH_PICOBJ := $(LIBOCT_PATHSEARCH_OBJECTS)
  endif
endif

all: libraries
.PHONY: all

objects: $(OBJECTS)

stmp-pic: pic
	@if [ -f stmp-pic ]; then \
	  true; \
	else \
	  echo "touch stmp-pic"; \
	  touch stmp-pic; \
	fi

pic:
	@if [ -d pic ]; then \
	  true; \
	else \
	  echo "mkdir pic"; \
	  mkdir pic; \
	fi

ifeq ($(SHARED_LIBS), true)
  ifeq ($(STATIC_LIBS), true)
    libraries: \
	liboctave.$(LIBEXT) liboctave.$(SHLEXT) \
	liboct-readline.$(LIBEXT) liboct-readline.$(SHLEXT) \
	liboct-pathsearch.$(LIBEXT) liboct-pathsearch.$(SHLEXT)
  else
    libraries: \
	liboctave.$(SHLEXT) \
	liboct-readline.$(SHLEXT) \
	liboct-pathsearch.$(SHLEXT)
  endif
else
  ifeq ($(STATIC_LIBS), true)
    libraries: \
	liboctave.$(LIBEXT) \
	liboct-readline.$(LIBEXT) \
	liboct-pathsearch.$(LIBEXT)
  else
    libraries:
  endif
endif
.PHONY: libraries

liboctave.$(LIBEXT): $(LIBOCTAVE_OBJECTS)
	rm -f $@
	$(TEMPLATE_AR) $(TEMPLATE_ARFLAGS) $@ $^
	$(RANLIB) $@

liboctave.$(SHLEXT): liboctave.$(SHLEXT_VER)
	rm -f $@
	$(LN_S) $< $@

liboctave.$(SHLEXT_VER): $(LIBOCTAVE_PICOBJ)
	rm -f $@
	$(SH_LD) $(SH_LDFLAGS) $(SONAME_FLAGS) -o $@ $^

$(LIBOCTAVE_PICOBJ): stmp-pic

liboct-readline.$(LIBEXT): $(LIBOCT_READLINE_OBJECTS)
	rm -f $@
	$(TEMPLATE_AR) $(TEMPLATE_ARFLAGS) $@ $^
	$(RANLIB) $@

liboct-readline.$(SHLEXT): liboct-readline.$(SHLEXT_VER)
	rm -f $@
	$(LN_S) $< $@

liboct-readline.$(SHLEXT_VER): $(LIBOCT_READLINE_PICOBJ)
	rm -f $@
	$(SH_LD) $(SH_LDFLAGS) $(SONAME_FLAGS) -o $@ $^

$(LIBOCT_READLINE_PICOBJ): stmp-pic

liboct-pathsearch.$(LIBEXT): $(LIBOCT_PATHSEARCH_OBJECTS)
	rm -f $@
	$(TEMPLATE_AR) $(TEMPLATE_ARFLAGS) $@ $^
	$(RANLIB) $@

liboct-pathsearch.$(SHLEXT): liboct-pathsearch.$(SHLEXT_VER)
	rm -f $@
	$(LN_S) $< $@

liboct-pathsearch.$(SHLEXT_VER): $(LIBOCT_PATHSEARCH_PICOBJ)
	rm -f $@
	$(SH_LD) $(SH_LDFLAGS) $(SONAME_FLAGS) -o $@ $^

$(LIBOCT_PATHSEARCH_PICOBJ): stmp-pic

check: all
.PHONY: check

install: install-lib install-inc
.PHONY: install

install-strip:
	$(MAKE) INSTALL_PROGRAM="$(INSTALL_PROGRAM) -s" install
.PHONY: install-strip

install-lib:
	$(top_srcdir)/mkinstalldirs $(octlibdir)
	if $(STATIC_LIBS); then \
	  rm -f $(octlibdir)/liboctave.$(LIBEXT); \
	  $(INSTALL_DATA) liboctave.$(LIBEXT) \
	    $(octlibdir)/liboctave.$(LIBEXT); \
	  $(RANLIB) $(octlibdir)/liboctave.$(LIBEXT); \
	    \
	  rm -f $(octlibdir)/liboct-readline.$(LIBEXT); \
	  $(INSTALL_DATA) liboct-readline.$(LIBEXT) \
	    $(octlibdir)/liboct-readline.$(LIBEXT); \
	  $(RANLIB) $(octlibdir)/liboct-readline.$(LIBEXT); \
	    \
	  rm -f $(octlibdir)/liboct-pathsearch.$(LIBEXT); \
	  $(INSTALL_DATA) liboct-pathsearch.$(LIBEXT) \
	    $(octlibdir)/liboct-pathsearch.$(LIBEXT); \
	  $(RANLIB) $(octlibdir)/liboct-pathsearch.$(LIBEXT); \
	fi
	if $(SHARED_LIBS); then \
	  rm -f $(octlibdir)/liboctave.$(SHLEXT_VER); \
	  $(INSTALL_PROGRAM) \
	    liboctave.$(SHLEXT_VER) $(octlibdir)/liboctave.$(SHLEXT_VER); \
	  ( cd $(octlibdir); \
	    rm -f liboctave.$(SHLEXT); \
	    $(LN_S) liboctave.$(SHLEXT_VER) liboctave.$(SHLEXT); ); \
	  rm -f $(octlibdir)/liboct-readline.$(SHLEXT_VER); \
	  $(INSTALL_PROGRAM) \
	    liboct-readline.$(SHLEXT_VER) \
	    $(octlibdir)/liboct-readline.$(SHLEXT_VER); \
	  ( cd $(octlibdir); \
	    rm -f liboct-readline.$(SHLEXT); \
	    $(LN_S) \
	      liboct-readline.$(SHLEXT_VER) liboct-readline.$(SHLEXT); ); \
	  rm -f $(octlibdir)/liboct-pathsearch.$(SHLEXT_VER); \
	  $(INSTALL_PROGRAM) \
	    liboct-pathsearch.$(SHLEXT_VER) \
	    $(octlibdir)/liboct-pathsearch.$(SHLEXT_VER); \
	  ( cd $(octlibdir); \
	    rm -f liboct-pathsearch.$(SHLEXT); \
	    $(LN_S) \
	      liboct-pathsearch.$(SHLEXT_VER) liboct-pathsearch.$(SHLEXT); ); \
	fi
.PHONY: install-lib

install-inc:
	$(top_srcdir)/mkinstalldirs $(octincludedir)/octave
	for f in $(INCLUDES_FOR_INSTALL); do \
	  rm -f $(octincludedir)/octave/$$f; \
	  $(INSTALL_DATA) $(srcdir)/$$f $(octincludedir)/octave/$$f; \
	done
.PHONY: install-inc

uninstall:
	rm -f $(octlibdir)/liboctave.$(LIBEXT)
	rm -f $(octlibdir)/liboctave.$(SHLEXT)
	rm -f $(octlibdir)/liboctave.$(SHLEXT_VER)
	rm -f $(octlibdir)/liboct-readline.$(LIBEXT)
	rm -f $(octlibdir)/liboct-readline.$(SHLEXT)
	rm -f $(octlibdir)/liboct-readline.$(SHLEXT_VER)
	rm -f $(octlibdir)/liboct-pathsearch.$(LIBEXT)
	rm -f $(octlibdir)/liboct-pathsearch.$(SHLEXT)
	rm -f $(octlibdir)/liboct-pathsearch.$(SHLEXT_VER)
	for f in $(INCLUDES); do rm -f $(octincludedir)/octave/$$f; done
.PHONY: uninstall

tags: $(SOURCES)
	ctags $(SOURCES)

TAGS: $(SOURCES)
	etags $(SOURCES)

clean:
	rm -f *.$(LIBEXT) *.o *.d pic/*.o
	-rmdir pic
	rm -f stmp-pic
	if $(SHARED_LIBS); then rm -f *.$(SHLEXT_VER) *.$(SHLEXT); fi
.PHONY: clean

mostlyclean: clean
.PHONY: mostlyclean

distclean: clean
	rm -f Makefile so_locations
.PHONY: distclean

maintainer-clean: distclean
	rm -f tags TAGS
.PHONY: maintainer-clean

dist:
	ln $(DISTFILES) ../`cat ../.fname`/liboctave
.PHONY: dist

bin-dist:
	if [ -n "$(BINDISTFILES)" ]; then \
	  ln $(BINDISTFILES) ../`cat ../.fname`/liboctave; \
	fi
	if [ -n "$(BINDISTLIBS)" ]; then \
	  echo $(BINDISTLIBS) >> ../`cat ../.fname`/LIBRARIES; \
	fi
.PHONY: bin-dist

ifndef omit_deps
-include $(MAKEDEPS)
endif
