/*
  Part of: CCStructs
  Contents: test for version functions
  Date: Apr 30, 2018

  Abstract

	Test file for version functions.

  Copyright (C) 2018 Marco Maggi <mrc.mgg@gmail.com>

  See the COPYING file.
*/

#include <ccstructs.h>
#include <stdio.h>
#include <stdlib.h>

int
main (int argc CCSTRUCTS_UNUSED, const char *const argv[] CCSTRUCTS_UNUSED)
{
  printf("version number string: %s\n", ccstructs_version_string());
  printf("libtool version number: %d:%d:%d\n",
	 ccstructs_version_interface_current(),
	 ccstructs_version_interface_revision(),
	 ccstructs_version_interface_age());
  exit(EXIT_SUCCESS);
}

/* end of file */
