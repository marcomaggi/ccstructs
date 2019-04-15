/*
  Part of: CCStructs
  Contents: tests for the pathname trait
  Date: Tue Oct  9, 2018

  Abstract

	This    program   tests    the   file    system   pathname    representataion
	"ccstructs_pathname_t"   and   the   associated  trait   implementation   for
	"ccstructs_pathname_T".

  Copyright (C) 2018, 2019 Marco Maggi <marco.maggi-ipsu@poste.it>

  This is free software; you can redistribute  it and/or modify it under the terms of
  the GNU Lesser General Public License as published by the Free Software Foundation;
  either version 3.0 of the License, or (at your option) any later version.

  This library  is distributed in the  hope that it  will be useful, but  WITHOUT ANY
  WARRANTY; without  even the implied  warranty of  MERCHANTABILITY or FITNESS  FOR A
  PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License along with
  this library; if not, write to the Free Software Foundation, Inc., 59 Temple Place,
  Suite 330, Boston, MA 02111-1307 USA.
*/


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "ccstructs.h"
#include <cctests.h>


/** --------------------------------------------------------------------
 ** Pathname representation: embedded instance construction.
 ** ----------------------------------------------------------------- */

void
test_1_1 (cce_destination_t upper_L)
/* Initialise  an  embedded  instance  of "ccstructs_pathname_t"  with  the  pathname
   representation from an ASCIIZ C string. */
{
  static char const *		P = "/path/to/file.ext";
  cce_location_t		L[1];
  ccstructs_pathname_t		ptn[1];
  ccstructs_clean_handler_t	ptn_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccname_init(ccstructs_pathname_t, from_chars)(L, ptn, P);
    ccstructs_init_and_register_handler(L, ptn_H, ccname_trait_new(ccstructs_dtor_T, ccstructs_pathname_t)(ptn));
    {
      ccstructs_dumpable_T	W = ccname_trait_new(ccstructs_dumpable_T, ccstructs_pathname_t)(ptn);
      ccstructs_dumpable_dump(L, W);
    }
    {
      ccstructs_pathname_T	I   = ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)(ptn);
      ccmem_asciiz_t		rep = ccstructs_pathname_asciiz(L, I);
      cctests_assert_equal_size(L, strlen(P), rep.len);
      cctests_assert_asciiz(L, P, rep.ptr);
    }
    cce_run_body_handlers(L);
  }
}

/* ------------------------------------------------------------------ */

void
test_1_2 (cce_destination_t upper_L)
/* Initialise  an  embedded  instance  of "ccstructs_pathname_t"  with  the  pathname
   representation from an ASCIIZ memory block. */
{
  static char const *		P = "/path/to/file.ext";
  ccmem_asciiz_t		B = ccmem_new_asciiz_from_str((char *)P);
  cce_location_t		L[1];
  ccstructs_pathname_t		ptn[1];
  ccstructs_clean_handler_t	ptn_H[1];

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); }
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccname_init(ccstructs_pathname_t, from_asciiz)(L, ptn, B);
    ccstructs_init_and_register_handler(L, ptn_H, ccname_trait_new(ccstructs_dtor_T, ccstructs_pathname_t)(ptn));
    {
      ccstructs_dumpable_T	W = ccname_trait_new(ccstructs_dumpable_T, ccstructs_pathname_t)(ptn);
      ccstructs_dumpable_dump(L, W);
    }
    {
      ccstructs_pathname_T	I   = ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)(ptn);
      ccmem_asciiz_t		rep = ccstructs_pathname_asciiz(L, I);
      cctests_assert_equal_size(L, strlen(P), rep.len);
      cctests_assert_asciiz(L, P, rep.ptr);
    }
    cce_run_body_handlers(L);
  }
}

/* ------------------------------------------------------------------ */

void
test_1_3 (cce_destination_t upper_L)
/* Initialise  an  embedded  instance  of "ccstructs_pathname_t"  with  the  pathname
   representation from an ASCII memory block. */
{
  static char const *		P = "/path/to/file.ext";
  ccmem_ascii_t			B = ccmem_new_ascii_from_str((char *)P);
  cce_location_t		L[1];
  ccstructs_pathname_t		ptn[1];
  ccstructs_clean_handler_t	ptn_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccname_init(ccstructs_pathname_t, from_ascii)(L, ptn, B);
    ccstructs_init_and_register_handler(L, ptn_H, ccname_trait_new(ccstructs_dtor_T, ccstructs_pathname_t)(ptn));
    {
      ccstructs_dumpable_T	W = ccname_trait_new(ccstructs_dumpable_T, ccstructs_pathname_t)(ptn);
      ccstructs_dumpable_dump(L, W);
    }
    {
      ccstructs_pathname_T	I   = ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)(ptn);
      ccmem_asciiz_t		rep = ccstructs_pathname_asciiz(L, I);
      cctests_assert_equal_size(L, strlen(P), rep.len);
      cctests_assert_asciiz(L, P, rep.ptr);
    }
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Pathname representation: standalone instance construction.
 ** ----------------------------------------------------------------- */

void
test_2_1 (cce_destination_t upper_L)
/* Initialise  a  standalone instance  of  "ccstructs_pathname_t"  with the  pathname
   representation from an ASCIIZ C string. */
{
  static char const *		P = "/path/to/file.ext";
  cce_location_t		L[1];
  ccstructs_pathname_t const *	ptn;
  ccstructs_clean_handler_t	ptn_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ptn = ccname_new(ccstructs_pathname_t, from_chars)(L, P);
    ccstructs_init_and_register_handler(L, ptn_H, ccname_trait_new(ccstructs_dtor_T, ccstructs_pathname_t)(ptn));
    {
      ccstructs_dumpable_T	W = ccname_trait_new(ccstructs_dumpable_T, ccstructs_pathname_t)(ptn);
      ccstructs_dumpable_dump(L, W);
    }
    {
      ccstructs_pathname_T	I   = ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)(ptn);
      ccmem_asciiz_t		rep = ccstructs_pathname_asciiz(L, I);
      cctests_assert_equal_size(L, strlen(P), rep.len);
      cctests_assert_asciiz(L, P, rep.ptr);
    }
    cce_run_body_handlers(L);
  }
}

/* ------------------------------------------------------------------ */

void
test_2_2 (cce_destination_t upper_L)
/* Initialise  a  standalone instance  of  "ccstructs_pathname_t"  with the  pathname
   representation from an ASCIIZ memory block. */
{
  static char const *		P = "/path/to/file.ext";
  ccmem_asciiz_t		B = ccmem_new_asciiz_from_str((char *)P);
  cce_location_t		L[1];
  ccstructs_pathname_t const *	ptn;
  ccstructs_clean_handler_t	ptn_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ptn = ccname_new(ccstructs_pathname_t, from_asciiz)(L, B);
    ccstructs_init_and_register_handler(L, ptn_H, ccname_trait_new(ccstructs_dtor_T, ccstructs_pathname_t)(ptn));
    {
      ccstructs_dumpable_T	W = ccname_trait_new(ccstructs_dumpable_T, ccstructs_pathname_t)(ptn);
      ccstructs_dumpable_dump(L, W);
    }
    {
      ccstructs_pathname_T	I   = ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)(ptn);
      ccmem_asciiz_t		rep = ccstructs_pathname_asciiz(L, I);
      cctests_assert_equal_size(L, strlen(P), rep.len);
      cctests_assert_asciiz(L, P, rep.ptr);
    }
    cce_run_body_handlers(L);
  }
}

/* ------------------------------------------------------------------ */

void
test_2_3 (cce_destination_t upper_L)
/* Initialise  a  standalone instance  of  "ccstructs_pathname_t"  with the  pathname
   representation from an ASCII memory block. */
{
  static char const *		P = "/path/to/file.ext";
  ccmem_ascii_t			B = ccmem_new_ascii_from_str((char *)P);
  cce_location_t		L[1];
  ccstructs_pathname_t const *	ptn;
  ccstructs_clean_handler_t	ptn_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ptn = ccname_new(ccstructs_pathname_t, from_ascii)(L, B);
    ccstructs_init_and_register_handler(L, ptn_H, ccname_trait_new(ccstructs_dtor_T, ccstructs_pathname_t)(ptn));
    {
      ccstructs_dumpable_T	W = ccname_trait_new(ccstructs_dumpable_T, ccstructs_pathname_t)(ptn);
      ccstructs_dumpable_dump(L, W);
    }
    {
      ccstructs_pathname_T	I   = ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)(ptn);
      ccmem_asciiz_t		rep = ccstructs_pathname_asciiz(L, I);
      cctests_assert_equal_size(L, strlen(P), rep.len);
      cctests_assert_asciiz(L, P, rep.ptr);
    }
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Pathname representation: serialise/deserialise traits.
 ** ----------------------------------------------------------------- */

void
test_3_1 (cce_destination_t upper_L)
/* Use pathname structs allocated on the stack. */
{
  static char const *		P = "/path/to/file.ext";
  cce_location_t		L[1];
  ccstructs_clean_handler_t	A_H[1], B_H[1];
  ccmem_clean_handler_t		M_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccstructs_pathname_t	A[1];
    ccstructs_pathname_t	B[1];
    ccmem_block_t		M, M_leftover;

    /* Build the struct to be serialised. */
    ccname_init(ccstructs_pathname_t, from_chars)(L, A, P);
    ccstructs_init_and_register_handler(L, A_H, ccname_trait_new(ccstructs_dtor_T, ccstructs_pathname_t)(A));

    {
      /* Build the "serialise" trait. */
      ccstructs_serialiser_T IS = ccname_trait_new(ccstructs_serialiser_T, ccstructs_pathname_t)(A);

      /* Allocate memory for the serialisation. */
      M = ccmem_block_malloc_guarded(L, M_H, ccmem_standard_allocator, ccstructs_serialiser_required_size(IS));

      /* Serialise the struct. */
      M_leftover = ccstructs_serialiser_write(L, IS, M);
    }

    {
      /* Build a struct to be target of deserialisation. */
      ccname_init(ccstructs_pathname_t, deserialisable)(B);
      ccstructs_init_and_register_handler(L, B_H, ccname_trait_new(ccstructs_dtor_T, ccstructs_pathname_t)(B));

      /* Build the "deserialise" trait. */
      ccstructs_deserialiser_T ID = ccname_trait_new(ccstructs_deserialiser_T, ccstructs_pathname_t)(B);

      /* Deserialise the struct. */
      M_leftover = ccstructs_deserialiser_read(L, ID, M);

      /* Check the deserialisation results. */
      {
	ccstructs_pathname_T	IA = ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)(A);
	ccstructs_pathname_T	IB = ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)(B);
	ccmem_asciiz_t		rep_A = ccstructs_pathname_asciiz(L, IA);
	ccmem_asciiz_t		rep_B = ccstructs_pathname_asciiz(L, IB);

	cctests_assert_equal_size(L, rep_A.len, rep_B.len);
	cctests_assert_asciiz(L, rep_A.ptr, rep_B.ptr);
	cctests_assert(L, M_leftover.ptr > M.ptr);
	cctests_assert(L, M_leftover.len < M.len);
      }
    }
    cce_run_body_handlers(L);
  }
}

void
test_3_2 (cce_destination_t upper_L)
/* Use pathname structs allocated on the heap. */
{
  static char const *		P = "/path/to/file.ext";
  cce_location_t		L[1];
  ccstructs_pathname_t const	*A;
  ccstructs_pathname_t		*B;
  ccstructs_clean_handler_t	A_H[1], B_H[1];
  ccmem_block_t			M, M_leftover;
  ccmem_clean_handler_t		M_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    /* Build the struct to be serialised. */
    A = ccname_new(ccstructs_pathname_t, from_chars)(L, P);
    ccstructs_init_and_register_handler(L, A_H, ccname_trait_new(ccstructs_dtor_T, ccstructs_pathname_t)(A));

    {
      /* Build the "serialise" trait. */
      ccstructs_serialiser_T IS = ccname_trait_new(ccstructs_serialiser_T, ccstructs_pathname_t)(A);

      /* Allocate memory for the serialisation. */
      M = ccmem_block_malloc_guarded(L, M_H, ccmem_standard_allocator, ccstructs_serialiser_required_size(IS));

      /* Serialise the struct. */
      M_leftover = ccstructs_serialiser_write(L, IS, M);
    }

    {
      /* Build a struct to be target of deserialisation. */
      B = ccname_new(ccstructs_pathname_t, deserialisable)(L);
      ccstructs_init_and_register_handler(L, B_H, ccname_trait_new(ccstructs_dtor_T, ccstructs_pathname_t)(B));

      /* Build the "deserialise" trait. */
      ccstructs_deserialiser_T ID = ccname_trait_new(ccstructs_deserialiser_T, ccstructs_pathname_t)(B);

      /* Deserialise the struct. */
      M_leftover = ccstructs_deserialiser_read(L, ID, M);

      /* Check the deserialisation results. */
      {
	ccstructs_pathname_T	IA = ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)(A);
	ccstructs_pathname_T	IB = ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)(B);
	ccmem_asciiz_t		rep_A = ccstructs_pathname_asciiz(L, IA);
	ccmem_asciiz_t		rep_B = ccstructs_pathname_asciiz(L, IB);

	cctests_assert_equal_size(L, rep_A.len, rep_B.len);
	cctests_assert_asciiz(L, rep_A.ptr, rep_B.ptr);
	cctests_assert(L, M_leftover.ptr > M.ptr);
	cctests_assert(L, M_leftover.len < M.len);
      }
    }
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Pathname trait: constructor and dumpable trait.
 ** ----------------------------------------------------------------- */

void
test_4_1 (cce_destination_t upper_L)
/* Build a pathname trait; check the pointer and length. */
{
  static char const *		P = "/path/to/file.ext";
  cce_location_t		L[1];
  ccstructs_pathname_t const *	ptn;
  ccstructs_clean_handler_t	ptn_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ptn = ccname_new(ccstructs_pathname_t, from_chars)(L, P);
    ccstructs_init_and_register_handler(L, ptn_H, ccname_trait_new(ccstructs_dtor_T, ccstructs_pathname_t)(ptn));
    {
      ccstructs_pathname_T	I = ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)(ptn);
      ccmem_asciiz_t		rep = ccstructs_pathname_asciiz(L, I);

      cctests_assert_equal_size(L, strlen(P), rep.len);
      cctests_assert_asciiz(L, P, rep.ptr);
      cctests_assert(L, false == ccstructs_pathname_is_static(I));
      {
	ccstructs_dumpable_T	W = ccname_trait_new(ccstructs_dumpable_T, ccstructs_pathname_T)(L, I);
	ccstructs_dumpable_dump(L, W);
      }
    }
    cce_run_body_handlers(L);
  }
}

void
test_4_2 (cce_destination_t upper_L)
/* Build a  pathname trait; check the  pointer and length.  Destroy  the pathname
   instance through the trait destructor. */
{
  static char const *		P = "/path/to/file.ext";
  cce_location_t		L[1];
  ccstructs_pathname_t const *	ptn;
  ccstructs_clean_handler_t	ptn_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ptn = ccname_new(ccstructs_pathname_t, from_chars)(L, P);
    {
      ccstructs_pathname_T	I = ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)(ptn);
      ccstructs_init_and_register_handler(L, ptn_H, ccname_trait_new(ccstructs_dtor_T, ccstructs_pathname_T)(I));
      {
	ccstructs_dumpable_T	W = ccname_trait_new(ccstructs_dumpable_T, ccstructs_pathname_T)(L, I);
	ccstructs_dumpable_dump(L, W);
      }
      {
	ccmem_asciiz_t		rep = ccstructs_pathname_asciiz(L, I);
	cctests_assert_equal_size(L, strlen(P), rep.len);
	cctests_assert_asciiz(L, P, rep.ptr);
	cctests_assert(L, false == ccstructs_pathname_is_static(I));
      }
    }
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Pathname trait: serialise/deserialise traits.
 ** ----------------------------------------------------------------- */

void
test_5_1 (cce_destination_t upper_L)
/* Use pathname structs allocted on the stack. */
{
  static char const *		P = "/path/to/file.ext";
  cce_location_t		L[1];
  ccstructs_pathname_t		A[1], B[1];
  ccstructs_pathname_T		IA, IB;
  ccstructs_clean_handler_t	A_H[1], B_H[1];
  ccmem_block_t			M, M_leftover;
  ccmem_clean_handler_t		M_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    /* Build the struct to be serialised. */
    ccname_init(ccstructs_pathname_t, from_chars)(L, A, P);
    IA = ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)(A);
    ccstructs_init_and_register_handler(L, A_H, ccname_trait_new(ccstructs_dtor_T, ccstructs_pathname_T)(IA));

    {
      /* Build the "serialise" trait. */
      ccstructs_serialiser_T IS = ccname_trait_new(ccstructs_serialiser_T, ccstructs_pathname_T)(L, IA);

      /* Allocate memory for the serialisation. */
      M = ccmem_block_malloc_guarded(L, M_H, ccmem_standard_allocator, ccstructs_serialiser_required_size(IS));

      /* Serialise the struct. */
      M_leftover = ccstructs_serialiser_write(L, IS, M);
    }

    {
      /* Build a struct to be target of deserialisation. */
      ccname_init(ccstructs_pathname_t, deserialisable)(B);
      IB = ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)(B);
      ccstructs_init_and_register_handler(L, B_H, ccname_trait_new(ccstructs_dtor_T, ccstructs_pathname_T)(IB));

      /* Build the "deserialise" trait. */
      ccstructs_deserialiser_T ID = ccname_trait_new(ccstructs_deserialiser_T, ccstructs_pathname_T)(L, IB);

      /* Deserialise the struct. */
      M_leftover = ccstructs_deserialiser_read(L, ID, M);

      /* Check the deserialisation results. */
      {
	ccmem_asciiz_t		rep_A = ccstructs_pathname_asciiz(L, IA);
	ccmem_asciiz_t		rep_B = ccstructs_pathname_asciiz(L, IB);

	cctests_assert_equal_size(L, rep_A.len, rep_B.len);
	cctests_assert_asciiz(L, rep_A.ptr, rep_B.ptr);
	cctests_assert(L, M_leftover.ptr > M.ptr);
	cctests_assert(L, M_leftover.len < M.len);
      }
    }
    cce_run_body_handlers(L);
  }
}

void
test_5_2 (cce_destination_t upper_L)
/* Use pathname structs allocted on the heap. */
{
  static char const *		P = "/path/to/file.ext";
  cce_location_t		L[1];
  ccstructs_pathname_t const	*A;
  ccstructs_pathname_t		*B;
  ccstructs_pathname_T		IA, IB;
  ccstructs_clean_handler_t	A_H[1], B_H[1];
  ccmem_block_t			M, M_leftover;
  ccmem_clean_handler_t		M_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    /* Build the struct to be serialised. */
    A  = ccname_new(ccstructs_pathname_t, from_chars)(L, P);
    IA = ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)(A);
    ccstructs_init_and_register_handler(L, A_H, ccname_trait_new(ccstructs_dtor_T, ccstructs_pathname_T)(IA));

    {
      /* Build the "serialise" trait. */
      ccstructs_serialiser_T IS = ccname_trait_new(ccstructs_serialiser_T, ccstructs_pathname_T)(L, IA);

      /* Allocate memory for the serialisation. */
      M = ccmem_block_malloc_guarded(L, M_H, ccmem_standard_allocator, ccstructs_serialiser_required_size(IS));

      /* Serialise the struct. */
      M_leftover = ccstructs_serialiser_write(L, IS, M);
    }

    {
      /* Build a struct to be target of deserialisation. */
      B  = ccname_new(ccstructs_pathname_t, deserialisable)(L);
      IB = ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)(B);
      ccstructs_init_and_register_handler(L, B_H, ccname_trait_new(ccstructs_dtor_T, ccstructs_pathname_T)(IB));

      /* Build the "deserialise" trait. */
      ccstructs_deserialiser_T ID = ccname_trait_new(ccstructs_deserialiser_T, ccstructs_pathname_T)(L, IB);

      /* Deserialise the struct. */
      M_leftover = ccstructs_deserialiser_read(L, ID, M);

      /* Check the deserialisation results. */
      {
	ccmem_asciiz_t		rep_A = ccstructs_pathname_asciiz(L, IA);
	ccmem_asciiz_t		rep_B = ccstructs_pathname_asciiz(L, IB);

	cctests_assert_equal_size(L, rep_A.len, rep_B.len);
	cctests_assert_asciiz(L, rep_A.ptr, rep_B.ptr);
	cctests_assert(L, M_leftover.ptr > M.ptr);
	cctests_assert(L, M_leftover.len < M.len);
      }
    }
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Pathname trait: predicates.
 ** ----------------------------------------------------------------- */

void
test_6_1 (cce_destination_t upper_L)
/* Build a pathname trait; check the results of the implemented predicates. */
{
  static char const *		P = "/path/to/file.ext";
  cce_location_t		L[1];
  ccstructs_pathname_t const *	ptn;
  ccstructs_pathname_T		ptn_TP;
  ccstructs_clean_handler_t	ptn_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ptn    = ccname_new(ccstructs_pathname_t, from_chars)(L, P);
    ptn_TP = ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)(ptn);
    ccstructs_init_and_register_handler(L, ptn_H, ccname_trait_new(ccstructs_dtor_T, ccstructs_pathname_T)(ptn_TP));

    cctests_assert(L, false == ccstructs_pathname_is_static(ptn_TP));
    cctests_assert(L, true  == ccstructs_pathname_is_absolute(L, ptn_TP));
    cctests_assert(L, false == ccstructs_pathname_is_relative(L, ptn_TP));
    cce_run_body_handlers(L);
  }
}

void
test_6_2 (cce_destination_t upper_L)
/* Build  a pathname  trait; check  the results  of the  unimplemented predicate:
   is_normalised. */
{
  cce_location_t	L[1];
  volatile bool		flag = false;

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    {
      static char const *		P = "/path/to/file.ext";
      cce_location_t			lower_L[1];
      ccstructs_pathname_t const *	ptn;
      ccstructs_pathname_T		ptn_TP;
      ccstructs_clean_handler_t		ptn_H[1];

      if (cce_location(lower_L)) {
	if (cce_condition_is_unimplemented(cce_condition(lower_L))) {
	  flag = true;
	  cce_run_catch_handlers_final(lower_L);
	} else {
	  cce_run_catch_handlers_raise(lower_L, L);
	}
      } else {
	ptn    = ccname_new(ccstructs_pathname_t, from_chars)(lower_L, P);
	ptn_TP = ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)(ptn);
	ccstructs_init_and_register_handler(lower_L, ptn_H, ccname_trait_new(ccstructs_dtor_T, ccstructs_pathname_T)(ptn_TP));

	cctests_assert(lower_L, ccstructs_pathname_is_normalised(lower_L, ptn_TP));
	cce_run_body_handlers(lower_L);
      }
    }
    cctests_assert(L, flag);
    cce_run_body_handlers(L);
  }
}

void
test_6_3 (cce_destination_t upper_L)
/* Build  a pathname  trait; check  the results  of the  unimplemented predicate:
   is_realpath. */
{
  cce_location_t	L[1];
  volatile bool		flag = false;

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    {
      static char const *		P = "/path/to/file.ext";
      cce_location_t			lower_L[1];
      ccstructs_pathname_t const *	ptn;
      ccstructs_pathname_T		ptn_TP;
      ccstructs_clean_handler_t		ptn_H[1];

      if (cce_location(lower_L)) {
	if (cce_condition_is_unimplemented(cce_condition(lower_L))) {
	  flag = true;
	  cce_run_catch_handlers_final(lower_L);
	} else {
	  cce_run_catch_handlers_raise(lower_L, L);
	}
      } else {
	ptn    = ccname_new(ccstructs_pathname_t, from_chars)(lower_L, P);
	ptn_TP = ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)(ptn);
	ccstructs_init_and_register_handler(lower_L, ptn_H, ccname_trait_new(ccstructs_dtor_T, ccstructs_pathname_T)(ptn_TP));

	cctests_assert(lower_L, ccstructs_pathname_is_realpath(lower_L, ptn_TP));
	cce_run_body_handlers(lower_L);
      }
    }
    cctests_assert(L, flag);
    cce_run_body_handlers(L);
  }
}


int
main (void)
{
  cctests_init("tests pathname trait");
  {
    cctests_begin_group("pathname representation embedded constructors");
    {
      cctests_run(test_1_1);
      cctests_run(test_1_2);
      cctests_run(test_1_3);
    }
    cctests_end_group();

    cctests_begin_group("pathname representation standalone constructors");
    {
      cctests_run(test_2_1);
      cctests_run(test_2_2);
      cctests_run(test_2_3);
    }
    cctests_end_group();

    cctests_begin_group("pathname representation, serialiser/deserialiser traits");
    {
      cctests_run(test_3_1);
      cctests_run(test_3_2);
    }
    cctests_end_group();

    cctests_begin_group("pathname representation, pathname trait: constructor, destructor and dumpable trait");
    {
      cctests_run(test_4_1);
      cctests_run(test_4_2);
    }
    cctests_end_group();

    cctests_begin_group("pathname representation, pathname trait: serialiser/deserialiser traits");
    {
      cctests_run(test_5_1);
      cctests_run(test_5_2);
    }
    cctests_end_group();

    cctests_begin_group("pathname representation, pathname trait: predicates");
    {
      cctests_run(test_6_1);
      cctests_run(test_6_2);
      cctests_run(test_6_3);
    }
    cctests_end_group();
  }
  cctests_final();
}

/* end of file */
