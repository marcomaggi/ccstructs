## Process this file with automake to produce Makefile.in

ACLOCAL_AMFLAGS		= -I meta/autotools
AUTOMAKE_OPTIONS	= foreign
EXTRA_DIST		= INSTALL			\
			  meta/slackstuff/config.in	\
			  meta/slackware/slack-desc.in
dist_doc_DATA		= README COPYING
AM_CFLAGS		= -I$(srcdir)/src $(AX_CFLAGS)

## --------------------------------------------------------------------

EXTRA_DIST		+= meta/scripts/ccstructs.pc.in
pkgconfigdir		= $(libdir)/pkgconfig
nodist_pkgconfig_DATA	= meta/scripts/ccstructs.pc

## --------------------------------------------------------------------

AM_MAKEINFOFLAGS	= --no-split

info_TEXINFOS		= doc/ccstructs.texi
doc_ccstructs_TEXINFOS	= \
	doc/macros.texi		\
	doc/lgpl-3.0.texi	\
	doc/fdl-1.3.texi


#### libraries

ccstructs_CURRENT	= @ccstructs_VERSION_INTERFACE_CURRENT@
ccstructs_REVISION	= @ccstructs_VERSION_INTERFACE_REVISION@
ccstructs_AGE		= @ccstructs_VERSION_INTERFACE_AGE@

include_HEADERS		= src/ccstructs.h

lib_LTLIBRARIES			= libccstructs.la
libccstructs_la_CPPFLAGS	= $(CCEXCEPTIONS_CFLAGS) $(CCMEMORY_CFLAGS)
libccstructs_la_LDFLAGS		= -version-info $(ccstructs_CURRENT):$(ccstructs_REVISION):$(ccstructs_AGE) \
				  $(CCEXCEPTIONS_LIBS) $(CCMEMORY_LIBS)
libccstructs_la_SOURCES		= \
	src/ccstructs.h				\
	src/ccstructs-internals.h		\
	src/ccstructs-version.c			\
	src/ccstructs-exception-handlers.c


#### tests

check_PROGRAMS	= \
	tests/version

if MMUX_TESTING_ENABLED
TESTS				= $(check_PROGRAMS)
endif

ccstructs_tests_cppflags	= -I$(srcdir)/src $(CCEXCEPTIONS_CFLAGS) $(CCMEMORY_CFLAGS) $(CCTESTS_CFLAGS)
ccstructs_tests_ldadd		= libccstructs.la $(CCEXCEPTIONS_LIBS) $(CCMEMORY_LIBS) $(CCTESTS_LIBS)

## --------------------------------------------------------------------

tests_version_CPPFLAGS		= $(ccstructs_tests_cppflags)
tests_version_LDADD		= $(ccstructs_tests_ldadd)

## --------------------------------------------------------------------

installcheck-local: $(TESTS)
	@for f in $(TESTS); do $(builddir)/$$f; done


#### testing under GDB

$(builddir)/.gdbinit:
	ln -sv "$(top_srcdir)/gdbinit" "$(builddir)/.gdbinit"

# This rule is meant to be used as:
#
#   $ make all gdb-test FILE=tests/inspection CFLAGS='-g'
#
# after having created an appropriate file "$(top_srcdir)/.gdbinit".
#
gdb-test: $(builddir)/.gdbinit
	libtool --mode=execute gdb $$FILE


#### Static analysis with Clang's Static Analyzer
#
# See the documentation for the command line tool at:
#
#    <http://clang-analyzer.llvm.org/scan-build.html>
#
# To run the tool we must do:
#
#    $ make clean
#    $ make clang-static-analysis
#
# The  program  "scan-build"  works  by  overriding  the  CC  and  CXX
# environment variables.  Automake defines CXX as:
#
#    CXX = g++ -std=c++11
#
# so we override CXXFLAGS to include the language specification.
#

.PHONY: clang-static-analysis

clang-static-analysis:
	scan-build make CXXFLAGS='-std=c++11'

### end of file
