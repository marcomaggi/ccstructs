dnl @configure_input@
dnl

AC_PREREQ([2.69])
AC_INIT([CCStructs],[0.1.0-devel.0],
  [marco.maggi-ipsu@poste.it],
  [ccstructs],[http://github.com/marcomaggi/ccstructs])
dnl This is the revision number of this configure.ac
AC_REVISION([0.1])
AC_COPYRIGHT([Copyright (c) 2018 Marco Maggi <marco.maggi-ipsu@poste.it>

This program is free software: you  can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by
the Free  Software Foundation, either version  3 of the License,  or (at
your option) any later version.

This program  is distributed  in the  hope that it  will be  useful, but
WITHOUT   ANY   WARRANTY;  without   even   the   implied  warranty   of
MERCHANTABILITY  or  FITNESS FOR  A  PARTICULAR  PURPOSE.  See  the  GNU
General Public License for more details.

You should have received a copy  of the GNU General Public License along
with this program.  If not, see <http://www.gnu.org/licenses/>.
])
AC_CONFIG_SRCDIR([src/])
AC_CONFIG_MACRO_DIR([meta/autotools])
AC_CONFIG_AUX_DIR([meta/autotools])
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE([foreign dist-xz no-dist-gzip subdir-objects])
AM_MAINTAINER_MODE

AM_PROG_AR
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_MKDIR_P

LT_PREREQ([2.4])
LT_INIT

dnl page
#### libraries interface version

MMUX_LIBTOOL_LIBRARY_VERSIONS([ccstructs],1,0,0)

dnl This is the version stored in the pkg-config data file.
AC_SUBST([CCSTRUCTS_PKG_CONFIG_VERSION],[0.1])

AS_VAR_SET([SLACKSTUFF_PACKAGE_VERSION],[0.1d0.0])
AC_SUBST([SLACKSTUFF_PACKAGE_VERSION])

dnl page
#### basic system inspection

MMUX_CHECK_TARGET_OS

AC_LANG([C])
MMUX_LANG_C11
AC_SUBST(AX_CFLAGS)

AM_PROG_AS
AM_PROG_CC_C_O
AC_HEADER_STDC
AC_CHECK_HEADERS([assert.h stdint.h strings.h stddef.h])

AC_CACHE_SAVE

dnl page
#### checks for library functions

dnl AC_FUNC_MALLOC
dnl AC_FUNC_MEMCMP
dnl AC_CHECK_FUNCS([memmove memset strerror])
dnl AC_CHECK_FUNCS([mmap munmap msync mremap madvise mlock munlock mlockall munlockall mprotect])
dnl AC_CHECK_FUNCS([getenv])

dnl AC_CACHE_SAVE

dnl page
#### external libraries

MMUX_CHECK_PKG_CONFIG_MACROS
PKG_CHECK_MODULES([CCEXCEPTIONS],[ccexceptions >= 0.8.0])
PKG_CHECK_MODULES([CCMEMORY],[ccmemory >= 0.2.0])
PKG_CHECK_MODULES([CCTESTS],[cctests >= 0.3.0],,[AC_MSG_WARN([package CCTests not found])])

AM_CONDITIONAL([MMUX_TESTING_ENABLED],[test -n "$CCTESTS_LIBS"])

AC_CACHE_SAVE

dnl page
#### finish

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile]
   [meta/scripts/ccstructs.pc]
   [meta/slackstuff/config]
   [meta/slackware/slack-desc])
AC_OUTPUT

### end of file
# Local Variables:
# mode: autoconf
# page-delimiter: "^dnl page"
# End:
