## Process this file with automake to produce Makefile.in

ACLOCAL_AMFLAGS		= -I meta/autotools
AUTOMAKE_OPTIONS	= foreign
EXTRA_DIST		= INSTALL			\
			  meta/slackware/slack-desc.in
dist_doc_DATA		= README COPYING
AM_CFLAGS		= $(MMUX_CFLAGS) -I$(srcdir)/src
AM_ETAGSFLAGS		= \
	$(CCEXCEPTIONS_HEADER)		\
	$(CCMEMORY_HEADER)		\
	--regex='{c}/"\\_<\\(ccname_\\(?:alloc\\|delete\\|final\\|i\\(?:face_\\(?:method\\(?:_type\\)?\\|new\\(?:_type\\)?\\|table\\(?:_type\\)?\\)\\|nit\\)\\|method\\(?:_type\\)?\\|new\\|\\(?:releas\\|tabl\\(?:e_typ\\)?\\)e\\)\\)\\_>"/'

## --------------------------------------------------------------------

EXTRA_DIST		+= meta/scripts/ccstructs.pc.in
pkgconfigdir		= $(libdir)/pkgconfig
nodist_pkgconfig_DATA	= meta/scripts/ccstructs.pc

## --------------------------------------------------------------------

AM_MAKEINFOFLAGS	= --no-split
AM_MAKEINFOHTMLFLAGS	= --split=node -c WORDS_IN_PAGE=0 \
	-c PRE_BODY_CLOSE="<p>This document describes version <tt>$(PACKAGE_VERSION)</tt> of <em>$(PACKAGE_NAME)</em>.</p>"

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
	src/ccstructs-exception-handlers.c	\
	src/ccstructs-pathname-representation.c

if WANTS_CCNAMES
include_HEADERS		+= src/ccnames.h
endif


#### tests

check_PROGRAMS	= \
	tests/version			\
	tests/dtor-interface		\
	tests/exception-handlers	\
	tests/writable-interface	\
	tests/serialisable-interface	\
	tests/pathname-interface

if MMUX_TESTING_ENABLED
TESTS				= $(check_PROGRAMS)
endif

ccstructs_tests_cppflags	= -I$(srcdir)/src $(CCEXCEPTIONS_CFLAGS) $(CCMEMORY_CFLAGS) $(CCTESTS_CFLAGS)
ccstructs_tests_ldadd		= libccstructs.la $(CCEXCEPTIONS_LIBS) $(CCMEMORY_LIBS) $(CCTESTS_LIBS)

## --------------------------------------------------------------------

tests_version_CPPFLAGS			= $(ccstructs_tests_cppflags)
tests_version_LDADD			= $(ccstructs_tests_ldadd)

tests_dtor_interface_CPPFLAGS		= $(ccstructs_tests_cppflags)
tests_dtor_interface_LDADD		= $(ccstructs_tests_ldadd)

tests_exception_handlers_CPPFLAGS	= $(ccstructs_tests_cppflags)
tests_exception_handlers_LDADD		= $(ccstructs_tests_ldadd)

tests_writable_interface_CPPFLAGS	= $(ccstructs_tests_cppflags)
tests_writable_interface_LDADD		= $(ccstructs_tests_ldadd)

tests_serialisable_interface_CPPFLAGS	= $(ccstructs_tests_cppflags)
tests_serialisable_interface_LDADD	= $(ccstructs_tests_ldadd)

tests_pathname_interface_CPPFLAGS	= $(ccstructs_tests_cppflags)
tests_pathname_interface_LDADD		= $(ccstructs_tests_ldadd)

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


#### examples
#
# The example programs use CCTests to drive the code.
#

if MMUX_TESTING_ENABLED
noinst_PROGRAMS	=					\
	examples/test-struct-no-methods	\
	examples/test-struct-with-methods
endif

ccstructs_examples_cppflags	= -I$(srcdir)/src -I$(srcdir)/examples $(CCTESTS_CFLAGS)
ccstructs_examples_ldadd	= libccstructs.la $(CCTESTS_LIBS)

.PHONY: examples

examples: $(noinst_PROGRAMS)
	-examples/test-struct-no-methods
	-examples/test-struct-with-methods

## --------------------------------------------------------------------

examples_test_struct_no_methods_SOURCES =	\
	examples/printable-interface.h		\
	examples/struct-no-methods.h		\
	examples/struct-no-methods.c		\
	examples/test-struct-no-methods.c

examples_test_struct_no_methods_CPPFLAGS	= $(ccstructs_examples_cppflags)
examples_test_struct_no_methods_LDADD		= $(ccstructs_examples_ldadd) -lm

$(examples_test_struct_no_methods_OBJECTS): libccstructs.la

## --------------------------------------------------------------------

examples_test_struct_with_methods_SOURCES =	\
	examples/printable-interface.h		\
	examples/struct-with-methods.h		\
	examples/struct-with-methods.c		\
	examples/test-struct-with-methods.c

examples_test_struct_with_methods_CPPFLAGS	= $(ccstructs_examples_cppflags)
examples_test_struct_with_methods_LDADD		= $(ccstructs_examples_ldadd) -lm

$(examples_test_struct_with_methods_OBJECTS): libccstructs.la


#### Valgrind analysis
#
# First do this:
#
#   make clean
#   make CFLAGS='-O0 -g' all check
#
# To use this rule on the file "tests/standard-allocator" we do:
#
#   make valgrind file=standard-allocator
#

VALGRIND_PROGRAM	= valgrind
VALGRIND_FLAGS		= --leak-check=yes --track-origins=yes
VALGRIND_FULL_FLAGS	= $(VALGRIND_FLAGS) --leak-check=full --show-leak-kinds=all

.PHONY: valgrind valgrind-full

valgrind:
	for f in $(builddir)/tests/$(file) ; \
	do $(LIBTOOL) --mode=execute $(VALGRIND_PROGRAM) $(VALGRIND_FLAGS) $$f ; \
	done

valgrind-full:
	for f in $(builddir)/tests/$(file) ; \
	do $(LIBTOOL) --mode=execute $(VALGRIND_PROGRAM) $(VALGRIND_FULL_FLAGS) $$f ; \
	done


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
# environment variables.

.PHONY: clang-static-analysis

clang-static-analysis:
	scan-build make CXXFLAGS='-std=c++11'

### end of file
