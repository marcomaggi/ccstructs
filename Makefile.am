## Process this file with automake to produce Makefile.in

ACLOCAL_AMFLAGS		= -I meta/autotools
AUTOMAKE_OPTIONS	= foreign
EXTRA_DIST		= INSTALL			\
			  meta/slackware/slack-desc.in
dist_doc_DATA		= README COPYING
AM_CPPFLAGS		= -I$(srcdir)/src
AM_CFLAGS		= $(MMUX_CFLAGS)

## --------------------------------------------------------------------

nodist_pkgconfig_DATA	= meta/scripts/ccstructs.pc


#### documentation

AM_MAKEINFOFLAGS	= --no-split
AM_MAKEINFOHTMLFLAGS	= --split=node -c WORDS_IN_PAGE=0 \
	-c PRE_BODY_CLOSE="<p>This document describes version <tt>$(PACKAGE_VERSION)</tt> of <em>$(PACKAGE_NAME)</em>.</p>"

info_TEXINFOS		= doc/ccstructs.texi
doc_ccstructs_TEXINFOS	= \
	doc/macros.texi			\
	doc/overview-linking.texi	\
	doc/overview-ccnames.texi	\
	doc/overview-ccexceptions.texi	\
	doc/overview-ccmemory.texi	\
	doc/lgpl-3.0.texi		\
	doc/fdl-1.3.texi


#### libraries

ccstructs_CURRENT		= @ccstructs_VERSION_INTERFACE_CURRENT@
ccstructs_REVISION		= @ccstructs_VERSION_INTERFACE_REVISION@
ccstructs_AGE			= @ccstructs_VERSION_INTERFACE_AGE@
ccstructs_LINKER_VERSION	= -version-info $(ccstructs_CURRENT):$(ccstructs_REVISION):$(ccstructs_AGE)

include_HEADERS		= src/ccstructs.h src/ccnames.h

lib_LTLIBRARIES			= libccstructs.la
libccstructs_la_CPPFLAGS	= $(AM_CPPFLAGS)
libccstructs_la_CFLAGS		= $(AM_CFLAGS) $(CCEXCEPTIONS_CFLAGS) $(CCMEMORY_CFLAGS)
libccstructs_la_LDFLAGS		= $(ccstructs_LINKER_VERSION) $(AM_LDFLAGS) $(CCEXCEPTIONS_LIBS) $(CCMEMORY_LIBS)
libccstructs_la_SOURCES		= \
	src/ccstructs.h				\
	src/ccnames.h				\
	src/ccstructs-internals.h		\
	src/ccstructs-version.c			\
	src/ccstructs-exception-handlers.c	\
	src/ccstructs-pathname-representation.c


#### tests

check_PROGRAMS	= \
	tests/version			\
	tests/dtor-interface		\
	tests/exception-handlers	\
	tests/dumpable-interface	\
	tests/serialisable-interface	\
	tests/pathname-representation	\
	tests/pathname-interface

if MMUX_TESTING_ENABLED
TESTS				= $(check_PROGRAMS)
endif

ccstructs_tests_cppflags	= $(AM_CPPFLAGS)
ccstructs_tests_cflags		= $(AM_CFLAGS) $(CCEXCEPTIONS_CFLAGS) $(CCMEMORY_CFLAGS) $(CCTESTS_CFLAGS)
ccstructs_tests_ldadd		= $(AM_LDFLAGS) libccstructs.la $(CCEXCEPTIONS_LIBS) $(CCMEMORY_LIBS) $(CCTESTS_LIBS)

## --------------------------------------------------------------------

tests_version_CPPFLAGS			= $(ccstructs_tests_cppflags)
tests_version_CFLAGS			= $(ccstructs_tests_cflags)
tests_version_LDADD			= $(ccstructs_tests_ldadd)

tests_dtor_interface_CPPFLAGS		= $(ccstructs_tests_cppflags)
tests_dtor_interface_CFLAGS		= $(ccstructs_tests_cflags)
tests_dtor_interface_LDADD		= $(ccstructs_tests_ldadd)

tests_exception_handlers_CPPFLAGS	= $(ccstructs_tests_cppflags)
tests_exception_handlers_CFLAGS		= $(ccstructs_tests_cflags)
tests_exception_handlers_LDADD		= $(ccstructs_tests_ldadd)

tests_dumpable_interface_CPPFLAGS	= $(ccstructs_tests_cppflags)
tests_dumpable_interface_CFLAGS		= $(ccstructs_tests_cflags)
tests_dumpable_interface_LDADD		= $(ccstructs_tests_ldadd)

tests_serialisable_interface_CPPFLAGS	= $(ccstructs_tests_cppflags)
tests_serialisable_interface_CFLAGS	= $(ccstructs_tests_cflags)
tests_serialisable_interface_LDADD	= $(ccstructs_tests_ldadd)

tests_pathname_representation_CPPFLAGS	= $(ccstructs_tests_cppflags)
tests_pathname_representation_CFLAGS	= $(ccstructs_tests_cflags)
tests_pathname_representation_LDADD	= $(ccstructs_tests_ldadd)

tests_pathname_interface_CPPFLAGS	= $(ccstructs_tests_cppflags)
tests_pathname_interface_CFLAGS		= $(ccstructs_tests_cflags)
tests_pathname_interface_LDADD		= $(ccstructs_tests_ldadd)

## --------------------------------------------------------------------

installcheck-local: $(TESTS)
	@for f in $(TESTS); do $(builddir)/$$f; done


#### examples
#
# The example programs use CCTests to drive the code.
#

if MMUX_TESTING_ENABLED
noinst_PROGRAMS	=					\
	examples/test-struct-no-methods	\
	examples/test-struct-with-methods
endif

ccstructs_examples_cppflags	= $(AM_CPPFLAGS) -I$(srcdir)/examples
ccstructs_examples_cflags	= $(AM_CFLAGS) $(CCEXCEPTIONS_CFLAGS) $(CCMEMORY_CFLAGS) $(CCTESTS_CFLAGS)
ccstructs_examples_ldadd	= $(AM_LDFLAGS) libccstructs.la $(CCEXCEPTIONS_LIBS) $(CCMEMORY_LIBS) $(CCTESTS_LIBS)

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
examples_test_struct_no_methods_CFLAGS		= $(ccstructs_examples_cflags)
examples_test_struct_no_methods_LDADD		= $(ccstructs_examples_ldadd) -lm

$(examples_test_struct_no_methods_OBJECTS): libccstructs.la

## --------------------------------------------------------------------

examples_test_struct_with_methods_SOURCES =	\
	examples/printable-interface.h		\
	examples/struct-with-methods.h		\
	examples/struct-with-methods.c		\
	examples/test-struct-with-methods.c

examples_test_struct_with_methods_CPPFLAGS	= $(ccstructs_examples_cppflags)
examples_test_struct_with_methods_CFLAGS	= $(ccstructs_examples_cflags)
examples_test_struct_with_methods_LDADD		= $(ccstructs_examples_ldadd) -lm

$(examples_test_struct_with_methods_OBJECTS): libccstructs.la


#### common rules

include $(top_srcdir)/meta/automake/mmux-makefile-rules

### end of file
