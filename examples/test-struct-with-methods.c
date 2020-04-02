/*
  Part of: CCStructs
  Contents: test file for sample struct with embedded methods table
  Date: Thu Dec 27, 2018

  Abstract

	This test program checks the behaviour of the API of the struct "my_coords_t"
	and shows how to use the implemented traits.

	The "struct-with-methods"  example shows  how to implement  a struct  using a
	methods table for  the struct-specific trait constructors:  every instance of
	the struct type holds a pointer to a struct implementing a methods table.

  Copyright (C) 2018, 2019, 2020 Marco Maggi <marco.maggi-ipsu@poste.it>

  The author  hereby grant permission to  use, copy, modify, distribute,  and license
  this  software  and its  documentation  for  any  purpose, provided  that  existing
  copyright  notices are  retained in  all copies  and that  this notice  is included
  verbatim in  any distributions. No  written agreement,  license, or royalty  fee is
  required for  any of the  authorized uses.  Modifications  to this software  may be
  copyrighted by  their authors  and need  not follow  the licensing  terms described
  here, provided that the  new terms are clearly indicated on the  first page of each
  file where they apply.

  IN NO  EVENT SHALL THE AUTHOR  OR DISTRIBUTORS BE  LIABLE TO ANY PARTY  FOR DIRECT,
  INDIRECT, SPECIAL, INCIDENTAL,  OR CONSEQUENTIAL DAMAGES ARISING OUT OF  THE USE OF
  THIS SOFTWARE,  ITS DOCUMENTATION, OR ANY  DERIVATIVES THEREOF, EVEN IF  THE AUTHOR
  HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  THE AUTHOR  AND DISTRIBUTORS SPECIFICALLY  DISCLAIM ANY WARRANTIES,  INCLUDING, BUT
  NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
  PURPOSE, AND NON-INFRINGEMENT.  THIS SOFTWARE IS  PROVIDED ON AN "AS IS" BASIS, AND
  THE AUTHOR  AND DISTRIBUTORS  HAVE NO OBLIGATION  TO PROVIDE  MAINTENANCE, SUPPORT,
  UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
*/


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "struct-with-methods.h"
#include <cctests.h>
#include <stdio.h>
#include <stdlib.h>


/** --------------------------------------------------------------------
 ** Flagging handlers.
 ** ----------------------------------------------------------------- */

/* This handler is used to signal that the "clean" handlers have been executed. */
static void
flag_clean_handler (cce_condition_t const * C CCLIB_UNUSED, cce_clean_handler_t const * H CCLIB_UNUSED)
{
  fprintf(stderr, "%-35s: clean handler fired\n", __func__);
}

void
flag_register_clean_handler (cce_destination_t L, cce_clean_handler_t * H)
{
  cce_init_and_register_handler(L, H, flag_clean_handler, cce_resource_pointer(NULL));
}

/* ------------------------------------------------------------------ */

/* This handler is used to signal that the "error" handlers have been executed. */
static void
flag_error_handler (cce_condition_t const * C CCLIB_UNUSED, cce_error_handler_t const * H CCLIB_UNUSED)
{
  fprintf(stderr, "%-35s: error handler fired\n", __func__);
}

void
flag_register_error_handler (cce_destination_t L, cce_error_handler_t * H)
{
  cce_init_and_register_handler(L, H, flag_error_handler, cce_resource_pointer(NULL));
}


/** --------------------------------------------------------------------
 ** Allocation on the stack, dtor handlers.
 ** ----------------------------------------------------------------- */

void
test_1_1 (cce_destination_t upper_L)
/* Allocate the struct instance on the stack,  then destroy it with a "clean" handler
   using the trait "ccstructs_dtor_T". */
{
  cce_location_t		L[1];
  cce_clean_handler_t		FC_H[1];
  cce_error_handler_t		FE_H[1];
  my_coords_t			A[1];
  ccstructs_clean_handler_t	A_H[1];
  my_printable_T		PA;

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccname_init(my_coords_t, rec)(A, 1.0, 2.0);
    ccstructs_init_and_register_handler(L, A_H, ccname_trait_new(ccstructs_dtor_T, my_coords_t)(A));

    flag_register_clean_handler(L, FC_H);
    flag_register_error_handler(L, FE_H);

    PA = ccname_trait_new(my_printable_T, my_coords_t)(A);
    my_printable_print_rec(L, PA, stderr);
    cce_run_body_handlers(L);
  }
}

void
test_1_2 (cce_destination_t upper_L)
/* Allocate the struct instance on the stack, then destroy it with an "error" handler
   using the trait "ccstructs_dtor_T". */
{
  cce_location_t		L[1];
  cce_clean_handler_t		FC_H[1];
  cce_error_handler_t		FE_H[1];
  my_coords_t			A[1];
  ccstructs_error_handler_t	A_H[1];
  my_printable_T		PA;

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccname_init(my_coords_t, rec)(A, 1.0, 2.0);
    ccstructs_init_and_register_handler(L, A_H, ccname_trait_new(ccstructs_dtor_T, my_coords_t)(A));

    flag_register_clean_handler(L, FC_H);
    flag_register_error_handler(L, FE_H);

    PA = ccname_trait_new(my_printable_T, my_coords_t)(A);
    my_printable_print_rec(L, PA, stderr);
    cce_raise(L, cctests_condition_new_signal_1());
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Allocation on the heap, dtor handlers.
 ** ----------------------------------------------------------------- */

void
test_2_1 (cce_destination_t upper_L)
/* Allocate the struct instance  on the heap, then destroy it  with a "clean" handler
   using the "ccstructs_dtor_T" trait. */
{
  cce_location_t		L[1];
  cce_clean_handler_t		FC_H[1];
  cce_error_handler_t		FE_H[1];
  my_coords_t const *		A;
  ccstructs_clean_handler_t	A_H[1];
  my_printable_T		PA;

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    A = ccname_new(my_coords_t, rec)(L, 1.0, 2.0);
    ccstructs_init_and_register_handler(L, A_H, ccname_trait_new(ccstructs_dtor_T, my_coords_t)(A));

    flag_register_clean_handler(L, FC_H);
    flag_register_error_handler(L, FE_H);

    PA = ccname_trait_new(my_printable_T, my_coords_t)(A);
    my_printable_print_rec(L, PA, stderr);
    cce_run_body_handlers(L);
  }
}

void
test_2_2 (cce_destination_t upper_L)
/* Allocate the struct on the heap, then destroy it with an "error" handler using the
   "ccstructs_dtor_T" trait. */
{
  cce_location_t		L[1];
  cce_clean_handler_t		FC_H[1];
  cce_error_handler_t		FE_H[1];
  my_coords_t const *		A;
  ccstructs_error_handler_t	A_H[1];
  my_printable_T		PA;

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    A = ccname_new(my_coords_t, rec)(L, 1.0, 2.0);
    ccstructs_init_and_register_handler(L, A_H, ccname_trait_new(ccstructs_dtor_T, my_coords_t)(A));

    flag_register_clean_handler(L, FC_H);
    flag_register_error_handler(L, FE_H);

    PA = ccname_trait_new(my_printable_T, my_coords_t)(A);
    my_printable_print_rec(L, PA, stderr);
    cce_raise(L, cctests_condition_new_signal_1());
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Trait "my_printable_T".
 ** ----------------------------------------------------------------- */

void
test_3_1 (cce_destination_t upper_L)
{
  cce_location_t		L[1];
  my_coords_t const *		A;
  ccstructs_clean_handler_t	A_H[1];
  my_printable_T		PA;

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    A = ccname_new(my_coords_t, rec)(L, 1.0, 2.0);
    ccstructs_init_and_register_handler(L, A_H, ccname_trait_new(ccstructs_dtor_T, my_coords_t)(A));

    PA = ccname_trait_new(my_printable_T, my_coords_t)(A);

    my_printable_print_rec(L, PA, stdout);
    my_printable_print_pol(L, PA, stdout);
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Trait "ccstructs_dumpable_T".
 ** ----------------------------------------------------------------- */

void
test_4_1 (cce_destination_t upper_L)
{
  cce_location_t		L[1];
  my_coords_t const *		A;
  ccstructs_clean_handler_t	A_H[1];
  ccstructs_dumpable_T		WA;

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    A = ccname_new(my_coords_t, rec)(L, 1.0, 2.0);
    ccstructs_init_and_register_handler(L, A_H, ccname_trait_new(ccstructs_dtor_T, my_coords_t)(A));

    WA = ccname_trait_new(ccstructs_dumpable_T, my_coords_t)(A);

    ccstructs_dumpable_dump(L, WA);
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Traits "ccstructs_serialiserd_T" and "ccstructs_deserialiser_T".
 ** ----------------------------------------------------------------- */

void
test_5_1 (cce_destination_t upper_L)
{
  cce_location_t		L[1];
  my_coords_t const		*A;
  my_coords_t			*B;
  ccstructs_clean_handler_t	A_H[1], B_H[1];
  ccmem_block_t			M, M_leftover;
  ccmem_clean_handler_t		M_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    /* Build the struct to be serialised. */
    A = ccname_new(my_coords_t, rec)(L, 1.0, 2.0);
    ccstructs_init_and_register_handler(L, A_H, ccname_trait_new(ccstructs_dtor_T, my_coords_t)(A));

    {
      /* Build the "serialise" trait. */
      ccstructs_serialiser_T IS = ccname_trait_new(ccstructs_serialiser_T, my_coords_t)(A);

      /* Allocate memory for the serialisation. */
      M = ccmem_block_malloc_guarded(L, M_H, ccmem_standard_allocator, ccstructs_serialiser_required_size(IS));

      /* Serialise the struct. */
      M_leftover = ccstructs_serialiser_write(L, IS, M);
    }

    {
      /* Build a struct to be target of deserialisation. */
      B = ccname_new(my_coords_t, deserialisable)(L);
      ccstructs_init_and_register_handler(L, B_H, ccname_trait_new(ccstructs_dtor_T, my_coords_t)(B));

      /* Build the "deserialise" trait. */
      ccstructs_deserialiser_T ID = ccname_trait_new(ccstructs_deserialiser_T, my_coords_t)(B);

      /* Deserialise the struct. */
      M_leftover = ccstructs_deserialiser_read(L, ID, M);

      /* Check the deserialisation results. */
      cctests_assert_equal_double(L, A->X, B->X);
      cctests_assert_equal_double(L, A->Y, B->Y);
      cctests_assert(L, M_leftover.ptr > M.ptr);
      cctests_assert(L, M_leftover.len < M.len);
    }
    cce_run_body_handlers(L);
  }
}


int
main (void)
{
  cctests_init("tests for traits on struct with methods table in the subject struct");
  {
    cctests_begin_group("allocation on the stack, dtor handlers from methods table");
    {
      cctests_run(test_1_1);
      cctests_run(test_1_2);
    }
    cctests_end_group();

    cctests_begin_group("allocation on the heap, dtor handlers from methods table");
    {
      cctests_run(test_2_1);
      cctests_run(test_2_2);
    }
    cctests_end_group();

    cctests_begin_group("printable trait");
    {
      cctests_run(test_3_1);
    }
    cctests_end_group();

    cctests_begin_group("dumpable trait");
    {
      cctests_run(test_4_1);
    }
    cctests_end_group();

    cctests_begin_group("serialise/deserialise trait");
    {
      cctests_run(test_5_1);
    }
    cctests_end_group();
  }
  cctests_final();
}

/* end of file */
