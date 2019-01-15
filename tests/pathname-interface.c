/*
  Part of: CCStructs
  Contents: tests for the pathname interface
  Date: Tue Oct  9, 2018

  Abstract

	This    program   tests    the   file    system   pathname    representataion
	"ccstructs_pathname_t"  and  the   associated  interface  implementation  for
	"ccstructs_pathname_I".

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
    ccstructs_clean_handler_init(L, ptn_H, ccname_iface_new(ccstructs_dtor_I, ccstructs_pathname_t)(ptn));
    {
      ccstructs_dumpable_I	W = ccname_iface_new(ccstructs_dumpable_I, ccstructs_pathname_t)(ptn);
      ccstructs_dumpable_dump(L, W);
    }
    {
      ccstructs_pathname_I	I   = ccname_iface_new(ccstructs_pathname_I, ccstructs_pathname_t)(ptn);
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
    ccstructs_clean_handler_init(L, ptn_H, ccname_iface_new(ccstructs_dtor_I, ccstructs_pathname_t)(ptn));
    {
      ccstructs_dumpable_I	W = ccname_iface_new(ccstructs_dumpable_I, ccstructs_pathname_t)(ptn);
      ccstructs_dumpable_dump(L, W);
    }
    {
      ccstructs_pathname_I	I   = ccname_iface_new(ccstructs_pathname_I, ccstructs_pathname_t)(ptn);
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
    ccstructs_clean_handler_init(L, ptn_H, ccname_iface_new(ccstructs_dtor_I, ccstructs_pathname_t)(ptn));
    {
      ccstructs_dumpable_I	W = ccname_iface_new(ccstructs_dumpable_I, ccstructs_pathname_t)(ptn);
      ccstructs_dumpable_dump(L, W);
    }
    {
      ccstructs_pathname_I	I   = ccname_iface_new(ccstructs_pathname_I, ccstructs_pathname_t)(ptn);
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
    ccstructs_clean_handler_init(L, ptn_H, ccname_iface_new(ccstructs_dtor_I, ccstructs_pathname_t)(ptn));
    {
      ccstructs_dumpable_I	W = ccname_iface_new(ccstructs_dumpable_I, ccstructs_pathname_t)(ptn);
      ccstructs_dumpable_dump(L, W);
    }
    {
      ccstructs_pathname_I	I   = ccname_iface_new(ccstructs_pathname_I, ccstructs_pathname_t)(ptn);
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
    ccstructs_clean_handler_init(L, ptn_H, ccname_iface_new(ccstructs_dtor_I, ccstructs_pathname_t)(ptn));
    {
      ccstructs_dumpable_I	W = ccname_iface_new(ccstructs_dumpable_I, ccstructs_pathname_t)(ptn);
      ccstructs_dumpable_dump(L, W);
    }
    {
      ccstructs_pathname_I	I   = ccname_iface_new(ccstructs_pathname_I, ccstructs_pathname_t)(ptn);
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
    ccstructs_clean_handler_init(L, ptn_H, ccname_iface_new(ccstructs_dtor_I, ccstructs_pathname_t)(ptn));
    {
      ccstructs_dumpable_I	W = ccname_iface_new(ccstructs_dumpable_I, ccstructs_pathname_t)(ptn);
      ccstructs_dumpable_dump(L, W);
    }
    {
      ccstructs_pathname_I	I   = ccname_iface_new(ccstructs_pathname_I, ccstructs_pathname_t)(ptn);
      ccmem_asciiz_t		rep = ccstructs_pathname_asciiz(L, I);
      cctests_assert_equal_size(L, strlen(P), rep.len);
      cctests_assert_asciiz(L, P, rep.ptr);
    }
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Pathname representation: serialise/deserialise interfaces.
 ** ----------------------------------------------------------------- */

void
test_3_1 (cce_destination_t upper_L)
/* Use pathname structs allocted on the stack. */
{
  static char const *		P = "/path/to/file.ext";
  cce_location_t		L[1];
  ccstructs_pathname_t		A[1];
  ccstructs_pathname_t		B[1];
  ccstructs_clean_handler_t	A_H[1], B_H[1];
  ccmem_block_t			M, M_leftover;
  ccmem_clean_handler_t		M_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    /* Build the struct to be serialised. */
    ccname_init(ccstructs_pathname_t, from_chars)(L, A, P);
    ccstructs_handler_init(L, A_H, ccname_iface_new(ccstructs_dtor_I, ccstructs_pathname_t)(A));

    {
      /* Build the "serialise" interface. */
      ccstructs_serialise_I IS = ccname_iface_new(ccstructs_serialise_I, ccstructs_pathname_t)(A);

      /* Allocate memory for the serialisation. */
      M = ccmem_block_malloc_guarded(L, M_H, ccmem_standard_allocator, ccstructs_serialise_required_size(IS));

      /* Serialise the struct. */
      M_leftover = ccstructs_serialise_write(L, IS, M);
    }

    {
      /* Build a struct to be target of deserialisation. */
      ccname_init(ccstructs_pathname_t, deserialisable)(B);
      ccstructs_handler_init(L, B_H, ccname_iface_new(ccstructs_dtor_I, ccstructs_pathname_t)(B));

      /* Build the "deserialise" interface. */
      ccstructs_deserialise_I ID = ccname_iface_new(ccstructs_deserialise_I, ccstructs_pathname_t)(B);

      /* Deserialise the struct. */
      M_leftover = ccstructs_deserialise_read(L, ID, M);

      /* Check the deserialisation results. */
      {
	ccstructs_pathname_I	IA = ccname_iface_new(ccstructs_pathname_I, ccstructs_pathname_t)(A);
	ccstructs_pathname_I	IB = ccname_iface_new(ccstructs_pathname_I, ccstructs_pathname_t)(B);
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
/* Use pathname structs allocted on the heap. */
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
    ccstructs_handler_init(L, A_H, ccname_iface_new(ccstructs_dtor_I, ccstructs_pathname_t)(A));

    {
      /* Build the "serialise" interface. */
      ccstructs_serialise_I IS = ccname_iface_new(ccstructs_serialise_I, ccstructs_pathname_t)(A);

      /* Allocate memory for the serialisation. */
      M = ccmem_block_malloc_guarded(L, M_H, ccmem_standard_allocator, ccstructs_serialise_required_size(IS));

      /* Serialise the struct. */
      M_leftover = ccstructs_serialise_write(L, IS, M);
    }

    {
      /* Build a struct to be target of deserialisation. */
      B = ccname_new(ccstructs_pathname_t, deserialisable)(L);
      ccstructs_handler_init(L, B_H, ccname_iface_new(ccstructs_dtor_I, ccstructs_pathname_t)(B));

      /* Build the "deserialise" interface. */
      ccstructs_deserialise_I ID = ccname_iface_new(ccstructs_deserialise_I, ccstructs_pathname_t)(B);

      /* Deserialise the struct. */
      M_leftover = ccstructs_deserialise_read(L, ID, M);

      /* Check the deserialisation results. */
      {
	ccstructs_pathname_I	IA = ccname_iface_new(ccstructs_pathname_I, ccstructs_pathname_t)(A);
	ccstructs_pathname_I	IB = ccname_iface_new(ccstructs_pathname_I, ccstructs_pathname_t)(B);
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
 ** Pathname interface.
 ** ----------------------------------------------------------------- */

void
test_4_1 (cce_destination_t upper_L)
/* Build a pathname interface; check the pointer and length. */
{
  static char const *		P = "/path/to/file.ext";
  cce_location_t		L[1];
  ccstructs_pathname_t const *	ptn;
  ccstructs_clean_handler_t	ptn_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ptn = ccname_new(ccstructs_pathname_t, from_chars)(L, P);
    ccstructs_clean_handler_init(L, ptn_H, ccname_iface_new(ccstructs_dtor_I, ccstructs_pathname_t)(ptn));
    {
      ccstructs_dumpable_I	W = ccname_iface_new(ccstructs_dumpable_I, ccstructs_pathname_t)(ptn);
      ccstructs_dumpable_dump(L, W);
    }

    {
      ccstructs_pathname_I	I = ccname_iface_new(ccstructs_pathname_I, ccstructs_pathname_t)(ptn);
      ccmem_asciiz_t		rep = ccstructs_pathname_asciiz(L, I);

      cctests_assert_equal_size(L, strlen(P), rep.len);
      cctests_assert_asciiz(L, P, rep.ptr);
      cctests_assert(L, false == ccstructs_pathname_is_static(I));
    }
    cce_run_body_handlers(L);
  }
}

void
test_4_2 (cce_destination_t upper_L)
/* Build a  pathname interface; check the  pointer and length.  Destroy  the pathname
   instance through the interface destructor. */
{
  static char const *		P = "/path/to/file.ext";
  cce_location_t		L[1];
  ccstructs_pathname_t const *	ptn;
  ccstructs_clean_handler_t	ptn_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ptn = ccname_new(ccstructs_pathname_t, from_chars)(L, P);
    ccstructs_pathname_I	I = ccname_iface_new(ccstructs_pathname_I, ccstructs_pathname_t)(ptn);
    ccstructs_clean_handler_init(L, ptn_H, ccname_iface_new(ccstructs_dtor_I, ccstructs_pathname_I)(I));
    {
      ccstructs_dumpable_I	W = ccname_iface_new(ccstructs_dumpable_I, ccstructs_pathname_t)(ptn);
      ccstructs_dumpable_dump(L, W);
    }
    {
      ccmem_asciiz_t		rep = ccstructs_pathname_asciiz(L, I);
      cctests_assert_equal_size(L, strlen(P), rep.len);
      cctests_assert_asciiz(L, P, rep.ptr);
      cctests_assert(L, false == ccstructs_pathname_is_static(I));
    }
    cce_run_body_handlers(L);
  }
}


int
main (void)
{
  cctests_init("tests pathname interface");
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

    cctests_begin_group("pathname representation, serialisable interface");
    {
      cctests_run(test_3_1);
      cctests_run(test_3_2);
    }
    cctests_end_group();

    cctests_begin_group("pathname representation, pathname interface");
    {
      cctests_run(test_4_1);
      cctests_run(test_4_2);
    }
    cctests_end_group();
  }
  cctests_final();
}

/* end of file */
