/*
  Part of: CCStructs
  Contents: test file for sample struct
  Date: Thu Dec 27, 2018

  Abstract

	This test program checks the behaviour  of the API of the struct
	"my_alpha_t" and shows how to use the implemented interfaces.

  Copyright (C) 2018 Marco Maggi <marco.maggi-ipsu@poste.it>

  The author hereby  grant permission to use,  copy, modify, distribute,
  and  license this  software  and its  documentation  for any  purpose,
  provided that  existing copyright notices  are retained in  all copies
  and that  this notice  is included verbatim  in any  distributions. No
  written agreement, license, or royalty fee  is required for any of the
  authorized uses.  Modifications to this software may be copyrighted by
  their authors and need not  follow the licensing terms described here,
  provided that the new terms are clearly indicated on the first page of
  each file where they apply.

  IN NO  EVENT SHALL THE AUTHOR  OR DISTRIBUTORS BE LIABLE  TO ANY PARTY
  FOR  DIRECT, INDIRECT, SPECIAL,  INCIDENTAL, OR  CONSEQUENTIAL DAMAGES
  ARISING OUT  OF THE  USE OF THIS  SOFTWARE, ITS DOCUMENTATION,  OR ANY
  DERIVATIVES  THEREOF, EVEN  IF THE  AUTHOR  HAVE BEEN  ADVISED OF  THE
  POSSIBILITY OF SUCH DAMAGE.

  THE  AUTHOR  AND DISTRIBUTORS  SPECIFICALLY  DISCLAIM ANY  WARRANTIES,
  INCLUDING,   BUT   NOT  LIMITED   TO,   THE   IMPLIED  WARRANTIES   OF
  MERCHANTABILITY,    FITNESS   FOR    A    PARTICULAR   PURPOSE,    AND
  NON-INFRINGEMENT.  THIS  SOFTWARE IS PROVIDED  ON AN "AS  IS" BASIS,
  AND  THE  AUTHOR  AND  DISTRIBUTORS  HAVE  NO  OBLIGATION  TO  PROVIDE
  MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

*/


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include <cctests.h>
#include <stdio.h>
#include <stdlib.h>
#include "dtors-with-methods.h"


/** --------------------------------------------------------------------
 ** Allocation on the stack.
 ** ----------------------------------------------------------------- */

void
test_1_1 (cce_destination_t upper_L)
/* Allocate the  struct on the stack,  then finalise it using  the clean
   handler. */
{
  cce_location_t	L[1];
  my_alpha_t		A[1];
  cce_clean_handler_t	A_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    my_init_alpha(A, 1.0, 2.0, 3.0);
    my_alpha_register_clean_handler_final(L, A_H, A);
    my_print_alpha(L, stderr, A);
    cce_run_body_handlers(L);
  }
}

void
test_1_2 (cce_destination_t upper_L)
/* Allocate the  struct on the stack,  then finalise it using  the error
   handler. */
{
  cce_location_t	L[1];
  my_alpha_t		A[1];
  cce_error_handler_t	A_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    my_init_alpha(A, 1.0, 2.0, 3.0);
    my_alpha_register_error_handler_final(L, A_H, A);
    my_print_alpha(L, stderr, A);
    cce_raise(L, cctests_condition_new_signal_1());
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Allocation on the heap.
 ** ----------------------------------------------------------------- */

void
test_2_1 (cce_destination_t upper_L)
/* Allocate the  struct on the  heap, then  finalise it using  the clean
   handler. */
{
  cce_location_t	L[1];
  my_alpha_t const *	A;
  cce_clean_handler_t	A_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    A = my_new_alpha(L, 1.0, 2.0, 3.0);
    my_alpha_register_clean_handler_delete(L, A_H, A);
    my_print_alpha(L, stderr, A);
    cce_run_body_handlers(L);
  }
}

void
test_2_2 (cce_destination_t upper_L)
/* Allocate the  struct on the  heap, then  finalise it using  the error
   handler. */
{
  cce_location_t	L[1];
  my_alpha_t const *	A;
  cce_error_handler_t	A_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    A = my_new_alpha(L, 1.0, 2.0, 3.0);
    my_alpha_register_error_handler_final(L, A_H, A);
    my_print_alpha(L, stderr, A);
    cce_raise(L, cctests_condition_new_signal_1());
    cce_run_body_handlers(L);
  }
}


int
main (void)
{
  cctests_init("tests for my_alpha_t");
  {
    cctests_begin_group("allocation on the stack");
    {
      cctests_run(test_1_1);
      cctests_run(test_1_2);
    }
    cctests_end_group();

    cctests_begin_group("allocation on the heap");
    {
      cctests_run(test_2_1);
      cctests_run(test_2_2);
    }
    cctests_end_group();
  }
  cctests_final();
}

/* end of file */
