/*
  Part of: CCStructs
  Contents: tests for the built-in "pathname" interfaces
  Date: Tue Oct  9, 2018

  Abstract



  Copyright (C) 2018 Marco Maggi <marco.maggi-ipsu@poste.it>

  This is free software; you  can redistribute it and/or modify it under
  the terms of the GNU Lesser General Public License as published by the
  Free Software  Foundation; either version  3.0 of the License,  or (at
  your option) any later version.

  This library  is distributed in the  hope that it will  be useful, but
  WITHOUT   ANY  WARRANTY;   without  even   the  implied   warranty  of
  MERCHANTABILITY  or FITNESS  FOR A  PARTICULAR PURPOSE.   See  the GNU
  Lesser General Public License for more details.

  You  should have  received a  copy of  the GNU  Lesser  General Public
  License along  with this library; if  not, write to  the Free Software
  Foundation, Inc.,  59 Temple Place,  Suite 330, Boston,  MA 02111-1307
  USA.

*/


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "ccstructs.h"
#include <cctests.h>


/** --------------------------------------------------------------------
 ** Pathname interface: static ASCIIZ strings.
 ** ----------------------------------------------------------------- */

void
test_1_1 (cce_destination_t upper_L)
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    static char const *		ptn = "/path/to/file.ext";
    ccstructs_pathname_I	I = ccstructs_new_pathname_from_static_string(ptn);

    cctests_assert_equal_size(L, strlen(ptn), ccstructs_pathname_length(L, I));
    cctests_assert_asciiz(L, ptn, ccstructs_pathname_pointer(L, I));
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Pathname interface: dynamic ASCIIZ strings.
 ** ----------------------------------------------------------------- */

void
test_2_1 (cce_destination_t upper_L)
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    char const *		ptn = "/path/to/file.ext";
    ccstructs_pathname_I	I = ccstructs_new_pathname_from_dynamic_string(ptn);

    cctests_assert_equal_size(L, strlen(ptn), ccstructs_pathname_length(L, I));
    cctests_assert_asciiz(L, ptn, ccstructs_pathname_pointer(L, I));
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Pathname interface: static ASCIIZ structs.
 ** ----------------------------------------------------------------- */

void
test_3_1 (cce_destination_t upper_L)
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccmem_asciiz_t		S = ccmem_new_asciiz_from_str("/path/to/file.ext");
    ccstructs_pathname_I	I = ccstructs_new_pathname_from_static_asciiz(&S);

    cctests_assert_equal_size(L, S.len, ccstructs_pathname_length(L, I));
    cctests_assert_asciiz(L, S.ptr, ccstructs_pathname_pointer(L, I));
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Pathname interface: dynamic ASCIIZ structs.
 ** ----------------------------------------------------------------- */

void
test_4_1 (cce_destination_t upper_L)
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccmem_asciiz_t		S = ccmem_new_asciiz_from_str("/path/to/file.ext");
    ccstructs_pathname_I	I = ccstructs_new_pathname_from_dynamic_asciiz(&S);

    cctests_assert_equal_size(L, S.len, ccstructs_pathname_length(L, I));
    cctests_assert_asciiz(L, S.ptr, ccstructs_pathname_pointer(L, I));
    cce_run_body_handlers(L);
  }
}


int
main (void)
{
  cctests_init("tests pathname interface");
  {
    cctests_begin_group("interface for static ASCIIZ strings");
    {
      cctests_run(test_1_1);
    }
    cctests_end_group();

    cctests_begin_group("interface for dynamic ASCIIZ strings");
    {
      cctests_run(test_2_1);
    }
    cctests_end_group();

    cctests_begin_group("interface for static ASCIIZ structs");
    {
      cctests_run(test_3_1);
    }
    cctests_end_group();

    cctests_begin_group("interface for dynamic ASCIIZ structs");
    {
      cctests_run(test_4_1);
    }
    cctests_end_group();
  }
  cctests_final();
}

/* end of file */
