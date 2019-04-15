/*
  Part of: CCStructs
  Contents: tests for the pathname representation
  Date: Apr 14, 2019

  Abstract

	This    program   tests    the   file    system   pathname    representataion
	"ccstructs_pathname_t".

  Copyright (C) 2019 Marco Maggi <marco.maggi-ipsu@poste.it>

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
  ccstructs_clean_handler_t	ptn_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccstructs_pathname_t const *	ptn = ccname_new(ccstructs_pathname_t, from_chars)(L, P);
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
  ccstructs_clean_handler_t	ptn_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccstructs_pathname_t const *	ptn = ccname_new(ccstructs_pathname_t, from_asciiz)(L, B);
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
  ccstructs_clean_handler_t	ptn_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccstructs_pathname_t const *	ptn = ccname_new(ccstructs_pathname_t, from_ascii)(L, B);
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
 ** Pathname representation: embedded instance guarded construction.
 ** ----------------------------------------------------------------- */

void
test_3_1 (cce_destination_t upper_L)
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
    ccname_init(ccstructs_pathname_t, from_chars, guarded, clean)(L, ptn_H, ptn, P);
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
test_3_2 (cce_destination_t upper_L)
/* Initialise  an  embedded  instance  of "ccstructs_pathname_t"  with  the  pathname
   representation from an ASCIIZ memory block. */
{
  static char const *		P = "/path/to/file.ext";
  ccmem_asciiz_t		B = ccmem_new_asciiz_from_str((char *)P);
  cce_location_t		L[1];
  ccstructs_pathname_t		ptn[1];
  ccstructs_clean_handler_t	ptn_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccname_init(ccstructs_pathname_t, from_asciiz, guarded, clean)(L, ptn_H, ptn, B);
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
test_3_3 (cce_destination_t upper_L)
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
    ccname_init(ccstructs_pathname_t, from_ascii, guarded, clean)(L, ptn_H, ptn, B);
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
 ** Pathname representation: standalone instance guarded construction.
 ** ----------------------------------------------------------------- */

void
test_4_1 (cce_destination_t upper_L)
/* Initialise  a  standalone instance  of  "ccstructs_pathname_t"  with the  pathname
   representation from an ASCIIZ C string. */
{
  static char const *		P = "/path/to/file.ext";
  cce_location_t		L[1];
  ccstructs_clean_handler_t	ptn_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccstructs_pathname_t const *	ptn = ccname_new(ccstructs_pathname_t, from_chars, guarded, clean)(L, ptn_H, P);
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
test_4_2 (cce_destination_t upper_L)
/* Initialise  a  standalone instance  of  "ccstructs_pathname_t"  with the  pathname
   representation from an ASCIIZ memory block. */
{
  static char const *		P = "/path/to/file.ext";
  ccmem_asciiz_t		B = ccmem_new_asciiz_from_str((char *)P);
  cce_location_t		L[1];
  ccstructs_clean_handler_t	ptn_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccstructs_pathname_t const *	ptn = ccname_new(ccstructs_pathname_t, from_asciiz, guarded, clean)(L, ptn_H, B);
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
test_4_3 (cce_destination_t upper_L)
/* Initialise  a  standalone instance  of  "ccstructs_pathname_t"  with the  pathname
   representation from an ASCII memory block. */
{
  static char const *		P = "/path/to/file.ext";
  ccmem_ascii_t			B = ccmem_new_ascii_from_str((char *)P);
  cce_location_t		L[1];
  ccstructs_clean_handler_t	ptn_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccstructs_pathname_t const * ptn = ccname_new(ccstructs_pathname_t, from_ascii, guarded, clean)(L, ptn_H, B);
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
 ** Pathname representation: embedded instance guarded construction with error handler and exception.
 ** ----------------------------------------------------------------- */

void
test_5_1 (cce_destination_t upper_L)
/* Initialise  an  embedded  instance  of "ccstructs_pathname_t"  with  the  pathname
   representation from an ASCIIZ C string. */
{
  static char const *		P = "/path/to/file.ext";
  cce_location_t		L[1];
  ccstructs_pathname_t		ptn[1];
  ccstructs_error_handler_t	ptn_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccname_init(ccstructs_pathname_t, from_chars, guarded, error)(L, ptn_H, ptn, P);
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
    cce_raise(L, cctests_condition_new_signal_1());
  }
}

/* ------------------------------------------------------------------ */

void
test_5_2 (cce_destination_t upper_L)
/* Initialise  an  embedded  instance  of "ccstructs_pathname_t"  with  the  pathname
   representation from an ASCIIZ memory block. */
{
  static char const *		P = "/path/to/file.ext";
  ccmem_asciiz_t		B = ccmem_new_asciiz_from_str((char *)P);
  cce_location_t		L[1];
  ccstructs_pathname_t		ptn[1];
  ccstructs_error_handler_t	ptn_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccname_init(ccstructs_pathname_t, from_asciiz, guarded, error)(L, ptn_H, ptn, B);
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
    cce_raise(L, cctests_condition_new_signal_1());
  }
}

/* ------------------------------------------------------------------ */

void
test_5_3 (cce_destination_t upper_L)
/* Initialise  an  embedded  instance  of "ccstructs_pathname_t"  with  the  pathname
   representation from an ASCII memory block. */
{
  static char const *		P = "/path/to/file.ext";
  ccmem_ascii_t			B = ccmem_new_ascii_from_str((char *)P);
  cce_location_t		L[1];
  ccstructs_pathname_t		ptn[1];
  ccstructs_error_handler_t	ptn_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccname_init(ccstructs_pathname_t, from_ascii, guarded, error)(L, ptn_H, ptn, B);
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
    cce_raise(L, cctests_condition_new_signal_1());
  }
}


/** --------------------------------------------------------------------
 ** Pathname representation: standalone instance guarded construction with error handler and exception.
 ** ----------------------------------------------------------------- */

void
test_6_1 (cce_destination_t upper_L)
/* Initialise  a  standalone instance  of  "ccstructs_pathname_t"  with the  pathname
   representation from an ASCIIZ C string. */
{
  static char const *		P = "/path/to/file.ext";
  cce_location_t		L[1];
  ccstructs_error_handler_t	ptn_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccstructs_pathname_t const * ptn = ccname_new(ccstructs_pathname_t, from_chars, guarded, error)(L, ptn_H, P);
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
    cce_raise(L, cctests_condition_new_signal_1());
  }
}

/* ------------------------------------------------------------------ */

void
test_6_2 (cce_destination_t upper_L)
/* Initialise  a  standalone instance  of  "ccstructs_pathname_t"  with the  pathname
   representation from an ASCIIZ memory block. */
{
  static char const *		P = "/path/to/file.ext";
  ccmem_asciiz_t		B = ccmem_new_asciiz_from_str((char *)P);
  cce_location_t		L[1];
  ccstructs_error_handler_t	ptn_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccstructs_pathname_t const * ptn = ccname_new(ccstructs_pathname_t, from_asciiz, guarded, error)(L, ptn_H, B);
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
    cce_raise(L, cctests_condition_new_signal_1());
  }
}

/* ------------------------------------------------------------------ */

void
test_6_3 (cce_destination_t upper_L)
/* Initialise  a  standalone instance  of  "ccstructs_pathname_t"  with the  pathname
   representation from an ASCII memory block. */
{
  static char const *		P = "/path/to/file.ext";
  ccmem_ascii_t			B = ccmem_new_ascii_from_str((char *)P);
  cce_location_t		L[1];
  ccstructs_error_handler_t	ptn_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccstructs_pathname_t const * ptn = ccname_new(ccstructs_pathname_t, from_ascii, guarded, error)(L, ptn_H, B);
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
    cce_raise(L, cctests_condition_new_signal_1());
  }
}


/** --------------------------------------------------------------------
 ** Pathname representation: embedded instance guarded construction, copy constructor.
 ** ----------------------------------------------------------------- */

void
test_7_1 (cce_destination_t upper_L)
/* Initialise  an  embedded  instance  of "ccstructs_pathname_t"  with  the  pathname
   representation from an ASCIIZ C string. */
{
  static char const *		P = "/path/to/file.ext";
  cce_location_t		L[1];
  ccstructs_pathname_t		ptn[1], ptn_copy[1];
  ccstructs_clean_handler_t	ptn_H[1], ptn_copy_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccname_init(ccstructs_pathname_t, from_chars, guarded, clean)(L, ptn_H, ptn, P);
    ccname_init(ccstructs_pathname_t, copy,       guarded, clean)(L, ptn_copy_H, ptn_copy, ptn);
    {
      ccstructs_dumpable_T	W = ccname_trait_new(ccstructs_dumpable_T, ccstructs_pathname_t)(ptn_copy);
      ccstructs_dumpable_dump(L, W);
    }
    {
      ccstructs_pathname_T	I   = ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)(ptn_copy);
      ccmem_asciiz_t		rep = ccstructs_pathname_asciiz(L, I);
      cctests_assert_equal_size(L, strlen(P), rep.len);
      cctests_assert_asciiz(L, P, rep.ptr);
    }
    cce_run_body_handlers(L);
  }
}

/* ------------------------------------------------------------------ */

void
test_7_2 (cce_destination_t upper_L)
/* Initialise  an  embedded  instance  of "ccstructs_pathname_t"  with  the  pathname
   representation from an ASCIIZ memory block. */
{
  static char const *		P = "/path/to/file.ext";
  ccmem_asciiz_t		B = ccmem_new_asciiz_from_str((char *)P);
  cce_location_t		L[1];
  ccstructs_pathname_t		ptn[1], ptn_copy[1];
  ccstructs_clean_handler_t	ptn_H[1], ptn_copy_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccname_init(ccstructs_pathname_t, from_asciiz, guarded, clean)(L, ptn_H, ptn, B);
    ccname_init(ccstructs_pathname_t, copy,       guarded, clean)(L, ptn_copy_H, ptn_copy, ptn);
    {
      ccstructs_dumpable_T	W = ccname_trait_new(ccstructs_dumpable_T, ccstructs_pathname_t)(ptn_copy);
      ccstructs_dumpable_dump(L, W);
    }
    {
      ccstructs_pathname_T	I   = ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)(ptn_copy);
      ccmem_asciiz_t		rep = ccstructs_pathname_asciiz(L, I);
      cctests_assert_equal_size(L, strlen(P), rep.len);
      cctests_assert_asciiz(L, P, rep.ptr);
    }
    cce_run_body_handlers(L);
  }
}

/* ------------------------------------------------------------------ */

void
test_7_3 (cce_destination_t upper_L)
/* Initialise  an  embedded  instance  of "ccstructs_pathname_t"  with  the  pathname
   representation from an ASCII memory block. */
{
  static char const *		P = "/path/to/file.ext";
  ccmem_ascii_t			B = ccmem_new_ascii_from_str((char *)P);
  cce_location_t		L[1];
  ccstructs_pathname_t		ptn[1], ptn_copy[1];
  ccstructs_clean_handler_t	ptn_H[1], ptn_copy_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccname_init(ccstructs_pathname_t, from_ascii, guarded, clean)(L, ptn_H, ptn, B);
    ccname_init(ccstructs_pathname_t, copy,       guarded, clean)(L, ptn_copy_H, ptn_copy, ptn);
    {
      ccstructs_dumpable_T	W = ccname_trait_new(ccstructs_dumpable_T, ccstructs_pathname_t)(ptn_copy);
      ccstructs_dumpable_dump(L, W);
    }
    {
      ccstructs_pathname_T	I   = ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)(ptn_copy);
      ccmem_asciiz_t		rep = ccstructs_pathname_asciiz(L, I);
      cctests_assert_equal_size(L, strlen(P), rep.len);
      cctests_assert_asciiz(L, P, rep.ptr);
    }
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Pathname representation: standalone instance guarded construction and copy constructors.
 ** ----------------------------------------------------------------- */

void
test_8_1 (cce_destination_t upper_L)
/* Initialise  a  standalone instance  of  "ccstructs_pathname_t"  with the  pathname
   representation from an ASCIIZ C string. */
{
  static char const *		P = "/path/to/file.ext";
  cce_location_t		L[1];
  ccstructs_clean_handler_t	ptn_H[1], ptn_copy_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccstructs_pathname_t const	*ptn, *ptn_copy;

    ptn      = ccname_new(ccstructs_pathname_t, from_chars, guarded, clean)(L, ptn_H, P);
    ptn_copy = ccname_new(ccstructs_pathname_t, copy,       guarded, clean)(L, ptn_copy_H, ptn);
    {
      ccstructs_dumpable_T	W = ccname_trait_new(ccstructs_dumpable_T, ccstructs_pathname_t)(ptn_copy);
      ccstructs_dumpable_dump(L, W);
    }
    {
      ccstructs_pathname_T	I   = ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)(ptn_copy);
      ccmem_asciiz_t		rep = ccstructs_pathname_asciiz(L, I);
      cctests_assert_equal_size(L, strlen(P), rep.len);
      cctests_assert_asciiz(L, P, rep.ptr);
    }
    cce_run_body_handlers(L);
  }
}

/* ------------------------------------------------------------------ */

void
test_8_2 (cce_destination_t upper_L)
/* Initialise  a  standalone instance  of  "ccstructs_pathname_t"  with the  pathname
   representation from an ASCIIZ memory block. */
{
  static char const *		P = "/path/to/file.ext";
  ccmem_asciiz_t		B = ccmem_new_asciiz_from_str((char *)P);
  cce_location_t		L[1];
  ccstructs_clean_handler_t	ptn_H[1], ptn_copy_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccstructs_pathname_t const	*ptn, *ptn_copy;

    ptn      = ccname_new(ccstructs_pathname_t, from_asciiz, guarded, clean)(L, ptn_H, B);
    ptn_copy = ccname_new(ccstructs_pathname_t, copy,        guarded, clean)(L, ptn_copy_H, ptn);
    {
      ccstructs_dumpable_T	W = ccname_trait_new(ccstructs_dumpable_T, ccstructs_pathname_t)(ptn_copy);
      ccstructs_dumpable_dump(L, W);
    }
    {
      ccstructs_pathname_T	I   = ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)(ptn_copy);
      ccmem_asciiz_t		rep = ccstructs_pathname_asciiz(L, I);
      cctests_assert_equal_size(L, strlen(P), rep.len);
      cctests_assert_asciiz(L, P, rep.ptr);
    }
    cce_run_body_handlers(L);
  }
}

/* ------------------------------------------------------------------ */

void
test_8_3 (cce_destination_t upper_L)
/* Initialise  a  standalone instance  of  "ccstructs_pathname_t"  with the  pathname
   representation from an ASCII memory block. */
{
  static char const *		P = "/path/to/file.ext";
  ccmem_ascii_t			B = ccmem_new_ascii_from_str((char *)P);
  cce_location_t		L[1];
  ccstructs_clean_handler_t	ptn_H[1], ptn_copy_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccstructs_pathname_t const	*ptn, *ptn_copy;

    ptn      = ccname_new(ccstructs_pathname_t, from_ascii, guarded, clean)(L, ptn_H, B);
    ptn_copy = ccname_new(ccstructs_pathname_t, copy,       guarded, clean)(L, ptn_copy_H, ptn);
    {
      ccstructs_dumpable_T	W = ccname_trait_new(ccstructs_dumpable_T, ccstructs_pathname_t)(ptn_copy);
      ccstructs_dumpable_dump(L, W);
    }
    {
      ccstructs_pathname_T	I   = ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)(ptn_copy);
      ccmem_asciiz_t		rep = ccstructs_pathname_asciiz(L, I);
      cctests_assert_equal_size(L, strlen(P), rep.len);
      cctests_assert_asciiz(L, P, rep.ptr);
    }
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Pathname representation: embedded instance guarded construction and copy contructors with error handler and exception.
 ** ----------------------------------------------------------------- */

void
test_9_1 (cce_destination_t upper_L)
/* Initialise  an  embedded  instance  of "ccstructs_pathname_t"  with  the  pathname
   representation from an ASCIIZ C string. */
{
  static char const *		P = "/path/to/file.ext";
  cce_location_t		L[1];
  ccstructs_pathname_t		ptn[1], ptn_copy[1];
  ccstructs_error_handler_t	ptn_H[1], ptn_copy_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccname_init(ccstructs_pathname_t, from_chars, guarded, error)(L, ptn_H, ptn, P);
    ccname_init(ccstructs_pathname_t, copy,       guarded, error)(L, ptn_copy_H, ptn_copy, ptn);
    {
      ccstructs_dumpable_T	W = ccname_trait_new(ccstructs_dumpable_T, ccstructs_pathname_t)(ptn_copy);
      ccstructs_dumpable_dump(L, W);
    }
    {
      ccstructs_pathname_T	I   = ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)(ptn_copy);
      ccmem_asciiz_t		rep = ccstructs_pathname_asciiz(L, I);
      cctests_assert_equal_size(L, strlen(P), rep.len);
      cctests_assert_asciiz(L, P, rep.ptr);
    }
    cce_raise(L, cctests_condition_new_signal_1());
  }
}

/* ------------------------------------------------------------------ */

void
test_9_2 (cce_destination_t upper_L)
/* Initialise  an  embedded  instance  of "ccstructs_pathname_t"  with  the  pathname
   representation from an ASCIIZ memory block. */
{
  static char const *		P = "/path/to/file.ext";
  ccmem_asciiz_t		B = ccmem_new_asciiz_from_str((char *)P);
  cce_location_t		L[1];
  ccstructs_pathname_t		ptn[1], ptn_copy[1];
  ccstructs_error_handler_t	ptn_H[1], ptn_copy_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccname_init(ccstructs_pathname_t, from_asciiz, guarded, error)(L, ptn_H, ptn, B);
    ccname_init(ccstructs_pathname_t, copy,        guarded, error)(L, ptn_copy_H, ptn_copy, ptn);
    {
      ccstructs_dumpable_T	W = ccname_trait_new(ccstructs_dumpable_T, ccstructs_pathname_t)(ptn_copy);
      ccstructs_dumpable_dump(L, W);
    }
    {
      ccstructs_pathname_T	I   = ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)(ptn_copy);
      ccmem_asciiz_t		rep = ccstructs_pathname_asciiz(L, I);
      cctests_assert_equal_size(L, strlen(P), rep.len);
      cctests_assert_asciiz(L, P, rep.ptr);
    }
    cce_raise(L, cctests_condition_new_signal_1());
  }
}

/* ------------------------------------------------------------------ */

void
test_9_3 (cce_destination_t upper_L)
/* Initialise  an  embedded  instance  of "ccstructs_pathname_t"  with  the  pathname
   representation from an ASCII memory block. */
{
  static char const *		P = "/path/to/file.ext";
  ccmem_ascii_t			B = ccmem_new_ascii_from_str((char *)P);
  cce_location_t		L[1];
  ccstructs_pathname_t		ptn[1], ptn_copy[1];
  ccstructs_error_handler_t	ptn_H[1], ptn_copy_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccname_init(ccstructs_pathname_t, from_ascii, guarded, error)(L, ptn_H, ptn, B);
    ccname_init(ccstructs_pathname_t, copy,       guarded, error)(L, ptn_copy_H, ptn_copy, ptn);
    {
      ccstructs_dumpable_T	W = ccname_trait_new(ccstructs_dumpable_T, ccstructs_pathname_t)(ptn_copy);
      ccstructs_dumpable_dump(L, W);
    }
    {
      ccstructs_pathname_T	I   = ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)(ptn_copy);
      ccmem_asciiz_t		rep = ccstructs_pathname_asciiz(L, I);
      cctests_assert_equal_size(L, strlen(P), rep.len);
      cctests_assert_asciiz(L, P, rep.ptr);
    }
    cce_raise(L, cctests_condition_new_signal_1());
  }
}


/** --------------------------------------------------------------------
 ** Pathname representation: standalone instance guarded construction and copy constructors with error handler and exception.
 ** ----------------------------------------------------------------- */

void
test_10_1 (cce_destination_t upper_L)
/* Initialise  a  standalone instance  of  "ccstructs_pathname_t"  with the  pathname
   representation from an ASCIIZ C string. */
{
  static char const *		P = "/path/to/file.ext";
  cce_location_t		L[1];
  ccstructs_error_handler_t	ptn_H[1], ptn_copy_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccstructs_pathname_t const	*ptn, *ptn_copy;

    ptn      = ccname_new(ccstructs_pathname_t, from_chars, guarded, error)(L, ptn_H, P);
    ptn_copy = ccname_new(ccstructs_pathname_t, copy,       guarded, error)(L, ptn_copy_H, ptn);
    {
      ccstructs_dumpable_T	W = ccname_trait_new(ccstructs_dumpable_T, ccstructs_pathname_t)(ptn_copy);
      ccstructs_dumpable_dump(L, W);
    }
    {
      ccstructs_pathname_T	I   = ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)(ptn_copy);
      ccmem_asciiz_t		rep = ccstructs_pathname_asciiz(L, I);
      cctests_assert_equal_size(L, strlen(P), rep.len);
      cctests_assert_asciiz(L, P, rep.ptr);
    }
    cce_raise(L, cctests_condition_new_signal_1());
  }
}

/* ------------------------------------------------------------------ */

void
test_10_2 (cce_destination_t upper_L)
/* Initialise  a  standalone instance  of  "ccstructs_pathname_t"  with the  pathname
   representation from an ASCIIZ memory block. */
{
  static char const *		P = "/path/to/file.ext";
  ccmem_asciiz_t		B = ccmem_new_asciiz_from_str((char *)P);
  cce_location_t		L[1];
  ccstructs_error_handler_t	ptn_H[1], ptn_copy_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccstructs_pathname_t const	*ptn, *ptn_copy;

    ptn      = ccname_new(ccstructs_pathname_t, from_asciiz, guarded, error)(L, ptn_H, B);
    ptn_copy = ccname_new(ccstructs_pathname_t, copy,        guarded, error)(L, ptn_copy_H, ptn);
    {
      ccstructs_dumpable_T	W = ccname_trait_new(ccstructs_dumpable_T, ccstructs_pathname_t)(ptn_copy);
      ccstructs_dumpable_dump(L, W);
    }
    {
      ccstructs_pathname_T	I   = ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)(ptn_copy);
      ccmem_asciiz_t		rep = ccstructs_pathname_asciiz(L, I);
      cctests_assert_equal_size(L, strlen(P), rep.len);
      cctests_assert_asciiz(L, P, rep.ptr);
    }
    cce_raise(L, cctests_condition_new_signal_1());
  }
}

/* ------------------------------------------------------------------ */

void
test_10_3 (cce_destination_t upper_L)
/* Initialise  a  standalone instance  of  "ccstructs_pathname_t"  with the  pathname
   representation from an ASCII memory block. */
{
  static char const *		P = "/path/to/file.ext";
  ccmem_ascii_t			B = ccmem_new_ascii_from_str((char *)P);
  cce_location_t		L[1];
  ccstructs_error_handler_t	ptn_H[1], ptn_copy_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccstructs_pathname_t const	*ptn, *ptn_copy;

    ptn      = ccname_new(ccstructs_pathname_t, from_ascii, guarded, error)(L, ptn_H, B);
    ptn_copy = ccname_new(ccstructs_pathname_t, copy,       guarded, error)(L, ptn_copy_H, ptn);
    {
      ccstructs_dumpable_T	W = ccname_trait_new(ccstructs_dumpable_T, ccstructs_pathname_t)(ptn_copy);
      ccstructs_dumpable_dump(L, W);
    }
    {
      ccstructs_pathname_T	I   = ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)(ptn_copy);
      ccmem_asciiz_t		rep = ccstructs_pathname_asciiz(L, I);
      cctests_assert_equal_size(L, strlen(P), rep.len);
      cctests_assert_asciiz(L, P, rep.ptr);
    }
    cce_raise(L, cctests_condition_new_signal_1());
  }
}


int
main (void)
{
  cctests_init("tests pathname representation");
  {
    cctests_begin_group("plain embedded constructors");
    {
      cctests_run(test_1_1);
      cctests_run(test_1_2);
      cctests_run(test_1_3);
    }
    cctests_end_group();

    cctests_begin_group("plain standalone constructors");
    {
      cctests_run(test_2_1);
      cctests_run(test_2_2);
      cctests_run(test_2_3);
    }
    cctests_end_group();

    cctests_begin_group("guarded embedded constructors");
    {
      cctests_run(test_3_1);
      cctests_run(test_3_2);
      cctests_run(test_3_3);
    }
    cctests_end_group();

    cctests_begin_group("guarded standalone constructors");
    {
      cctests_run(test_4_1);
      cctests_run(test_4_2);
      cctests_run(test_4_3);
    }
    cctests_end_group();

    cctests_begin_group("guarded embedded constructors with error handler and exception");
    {
      cctests_run(test_5_1);
      cctests_run(test_5_2);
      cctests_run(test_5_3);
    }
    cctests_end_group();

    cctests_begin_group("guarded standalone constructors with error handler and exception");
    {
      cctests_run(test_6_1);
      cctests_run(test_6_2);
      cctests_run(test_6_3);
    }
    cctests_end_group();

    cctests_begin_group("guarded embedded constructors and copy constructors");
    {
      cctests_run(test_7_1);
      cctests_run(test_7_2);
      cctests_run(test_7_3);
    }
    cctests_end_group();

    cctests_begin_group("guarded standalone constructors and copy constructors");
    {
      cctests_run(test_8_1);
      cctests_run(test_8_2);
      cctests_run(test_8_3);
    }
    cctests_end_group();

    cctests_begin_group("guarded embedded constructors and copy constructors with error handler and exception");
    {
      cctests_run(test_9_1);
      cctests_run(test_9_2);
      cctests_run(test_9_3);
    }
    cctests_end_group();

    cctests_begin_group("guarded standalone constructors and copy constructors with error handler and exception");
    {
      cctests_run(test_10_1);
      cctests_run(test_10_2);
      cctests_run(test_10_3);
    }
    cctests_end_group();

  }
  cctests_final();
}

/* end of file */
