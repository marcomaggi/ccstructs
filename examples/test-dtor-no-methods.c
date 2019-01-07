/*
  Part of: CCStructs
  Contents: test file for sample struct without embedded methods table
  Date: Thu Dec 27, 2018

  Abstract

	This test program checks the behaviour  of the API of the struct
	"my_coords_t" and shows how to use the implemented interfaces.

	The "dtor-no-methods"  example shows  how to implement  a struct
	using  no  methods  table   for  the  struct-specific  interface
	constructors.

  Copyright (C) 2018, 2019 Marco Maggi <marco.maggi-ipsu@poste.it>

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
#include "dtor-no-methods.h"


/** --------------------------------------------------------------------
 ** Flagging handlers.
 ** ----------------------------------------------------------------- */

/* This handler  is used to signal  that the "clean" handlers  have been
   executed. */
static void
flag_clean_handler (cce_condition_t const * C CCSTRUCTS_UNUSED, cce_handler_t * H CCSTRUCTS_UNUSED)
{
  fprintf(stderr, "%-35s: clean handler fired\n", __func__);
}

void
flag_register_clean_handler (cce_destination_t L, cce_clean_handler_t * H)
{
  H->handler.function	= flag_clean_handler;
  cce_register_clean_handler(L, H);
}

/* ------------------------------------------------------------------ */

/* This handler  is used to signal  that the "error" handlers  have been
   executed. */
static void
flag_error_handler (cce_condition_t const * C CCSTRUCTS_UNUSED, cce_handler_t * H CCSTRUCTS_UNUSED)
{
  fprintf(stderr, "%-35s: error handler fired\n", __func__);
}

void
flag_register_error_handler (cce_destination_t L, cce_error_handler_t * H)
{
  H->handler.function	= flag_error_handler;
  cce_register_error_handler(L, H);
}


/** --------------------------------------------------------------------
 ** Allocation on the stack, no handlers.
 ** ----------------------------------------------------------------- */

void
test_1_1 (cce_destination_t upper_L)
/* Allocate the  struct on the stack,  then destroy it with  the "final"
   function. */
{
  cce_location_t	L[1];
  my_coords_t		A[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccname_init(my_coords_t)(A, 1.0, 2.0, 3.0);
    /* If  this  call  raises  an  exception: we  may  have  a  resource
       leakage. */
    my_print_coords(L, stderr, A);
    ccname_final(my_coords_t)(A);
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Allocation on the heap, no handlers.
 ** ----------------------------------------------------------------- */

void
test_2_1 (cce_destination_t upper_L)
/* Allocate the  struct on the heap,  then destroy it with  the "delete"
   function. */
{
  cce_location_t	L[1];
  my_coords_t const *	A;

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    A = ccname_new(my_coords_t)(L, 1.0, 2.0, 3.0);
    /* If  this  call  raises  an  exception: we  may  have  a  resource
       leakage. */
    my_print_coords(L, stderr, A);
    ccname_delete(my_coords_t)(A);
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Allocation on the stack, plain handler destructors.
 ** ----------------------------------------------------------------- */

void
test_3_1 (cce_destination_t upper_L)
/* Allocate the struct on the stack, then destroy with a "clean" handler
   using the "final" function. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	FC_H[1];
  cce_error_handler_t	FE_H[1];
  my_coords_t		A[1];
  cce_clean_handler_t	A_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccname_init(my_coords_t)(A, 1.0, 2.0, 3.0);
    my_coords_register_clean_handler_final(L, A_H, A);

    flag_register_clean_handler(L, FC_H);
    flag_register_error_handler(L, FE_H);

    my_print_coords(L, stderr, A);
    cce_run_body_handlers(L);
  }
}

void
test_3_2 (cce_destination_t upper_L)
/* Allocate the  struct on the  stack, then  destroy it with  an "error"
   handler using the "final" function. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	FC_H[1];
  cce_error_handler_t	FE_H[1];
  my_coords_t		A[1];
  cce_error_handler_t	A_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccname_init(my_coords_t)(A, 1.0, 2.0, 3.0);
    my_coords_register_error_handler_final(L, A_H, A);

    flag_register_clean_handler(L, FC_H);
    flag_register_error_handler(L, FE_H);

    my_print_coords(L, stderr, A);
    cce_raise(L, cctests_condition_new_signal_1());
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Allocation on the heap, plain handler destructors.
 ** ----------------------------------------------------------------- */

void
test_4_1 (cce_destination_t upper_L)
/* Allocate  the struct  on the  heap, then  destroy it  with a  "clean"
   handler usin the "delete" function. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	FC_H[1];
  cce_error_handler_t	FE_H[1];
  my_coords_t const *	A;
  cce_clean_handler_t	A_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    A = ccname_new(my_coords_t)(L, 1.0, 2.0, 3.0);
    my_coords_register_clean_handler_delete(L, A_H, A);

    flag_register_clean_handler(L, FC_H);
    flag_register_error_handler(L, FE_H);

    my_print_coords(L, stderr, A);
    cce_run_body_handlers(L);
  }
}

void
test_4_2 (cce_destination_t upper_L)
/* Allocate the  struct on  the heap,  then destroy  it with  an "error"
   handler using the "delete" function. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	FC_H[1];
  cce_error_handler_t	FE_H[1];
  my_coords_t const *	A;
  cce_error_handler_t	A_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    A = ccname_new(my_coords_t)(L, 1.0, 2.0, 3.0);
    my_coords_register_error_handler_delete(L, A_H, A);

    flag_register_clean_handler(L, FC_H);
    flag_register_error_handler(L, FE_H);

    my_print_coords(L, stderr, A);
    cce_raise(L, cctests_condition_new_signal_1());
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Allocation on the stack, "ccstructs_dtor_I" handlers.
 ** ----------------------------------------------------------------- */

void
test_5_1 (cce_destination_t upper_L)
/* Allocate the  struct on  the stack,  then destroy  it with  a "clean"
   handler using the "embedded" "ccstructs_dtor_I" interface. */
{
  cce_location_t		L[1];
  cce_clean_handler_t		FC_H[1];
  cce_error_handler_t		FE_H[1];
  my_coords_t			A[1];
  ccstructs_clean_handler_t	A_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccname_init(my_coords_t)(A, 1.0, 2.0, 3.0);
    ccstructs_handler_init(L, A_H, ccname_iface_new(ccstructs_dtor_I, my_coords_t, embedded)(A));

    flag_register_clean_handler(L, FC_H);
    flag_register_error_handler(L, FE_H);

    my_print_coords(L, stderr, A);
    cce_run_body_handlers(L);
  }
}

void
test_5_2 (cce_destination_t upper_L)
/* Allocate the  struct on the  stack, then  destroy it with  an "error"
   handler using the "embedded" "ccstructs_dtor_I" interface. */
{
  cce_location_t		L[1];
  cce_clean_handler_t		FC_H[1];
  cce_error_handler_t		FE_H[1];
  my_coords_t			A[1];
  ccstructs_error_handler_t	A_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccname_init(my_coords_t)(A, 1.0, 2.0, 3.0);
    ccstructs_handler_init(L, A_H, ccname_iface_new(ccstructs_dtor_I, my_coords_t, embedded)(A));

    flag_register_clean_handler(L, FC_H);
    flag_register_error_handler(L, FE_H);

    my_print_coords(L, stderr, A);
    cce_raise(L, cctests_condition_new_signal_1());
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Allocation on the heap, "ccstructs_dtor_I" handlers.
 ** ----------------------------------------------------------------- */

void
test_6_1 (cce_destination_t upper_L)
/* Allocate  the struct  on the  heap, then  destroy it  with a  "clean"
   handler using the "standalone" "ccstructs_dtor_I" interface. */
{
  cce_location_t		L[1];
  cce_clean_handler_t		FC_H[1];
  cce_error_handler_t		FE_H[1];
  my_coords_t const *		A;
  ccstructs_clean_handler_t	A_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    A = ccname_new(my_coords_t)(L, 1.0, 2.0, 3.0);
    ccstructs_handler_init(L, A_H, ccname_iface_new(ccstructs_dtor_I, my_coords_t, standalone)(A));

    flag_register_clean_handler(L, FC_H);
    flag_register_error_handler(L, FE_H);

    my_print_coords(L, stderr, A);
    cce_run_body_handlers(L);
  }
}

void
test_6_2 (cce_destination_t upper_L)
/* Allocate the  struct on  the heap,  then destroy  it with  an "error"
   handler using the "standalone" "ccstructs_dtor_I" interface. */
{
  cce_location_t		L[1];
  cce_clean_handler_t		FC_H[1];
  cce_error_handler_t		FE_H[1];
  my_coords_t const *		A;
  ccstructs_error_handler_t	A_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    A = ccname_new(my_coords_t)(L, 1.0, 2.0, 3.0);
    ccstructs_handler_init(L, A_H, ccname_iface_new(ccstructs_dtor_I, my_coords_t, standalone)(A));

    flag_register_clean_handler(L, FC_H);
    flag_register_error_handler(L, FE_H);

    my_print_coords(L, stderr, A);
    cce_raise(L, cctests_condition_new_signal_1());
    cce_run_body_handlers(L);
  }
}


int
main (void)
{
  cctests_init("tests for dtor interface on struct without methods table in the subject struct");
  {
    cctests_begin_group("allocation on the stack, no handlers");
    {
      cctests_run(test_1_1);
    }
    cctests_end_group();

    cctests_begin_group("allocation on the heap, no handlers");
    {
      cctests_run(test_2_1);
    }
    cctests_end_group();

    cctests_begin_group("allocation on the stack, plain handler destructors");
    {
      cctests_run(test_3_1);
      cctests_run(test_3_2);
    }
    cctests_end_group();

    cctests_begin_group("allocation on the heap, plain handler destructors");
    {
      cctests_run(test_4_1);
      cctests_run(test_4_2);
    }
    cctests_end_group();

    cctests_begin_group("allocation on the stack, dtor handlers");
    {
      cctests_run(test_5_1);
      cctests_run(test_5_2);
    }
    cctests_end_group();

    cctests_begin_group("allocation on the heap, dtor handlers");
    {
      cctests_run(test_6_1);
      cctests_run(test_6_2);
    }
    cctests_end_group();
  }
  cctests_final();
}

/* end of file */
