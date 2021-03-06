/*
  Part of: CCStructs
  Contents: tests for the serialise trait
  Date: Sep 30, 2018

  Abstract



  Copyright (C) 2018, 2019, 2020 Marco Maggi <mrc.mgg@gmail.com>

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
 ** Serialise trait.
 ** ----------------------------------------------------------------- */

typedef struct one_one_t		one_one_t;
typedef struct serialised_one_one_t	serialised_one_one_t;

/* The struct type to be serialised. */
struct one_one_t {
  int	alpha;
  int	beta;
};

/* The layout of a serialised "one_one_t". */
struct serialised_one_one_t {
  int	alpha;
  int	beta;
};

/* ------------------------------------------------------------------ */

static ccname_trait_method_type(ccstructs_serialiser_T, required_size) ccname_trait_method(ccstructs_serialiser_T, one_one_t, required_size);
static ccname_trait_method_type(ccstructs_serialiser_T, write)         ccname_trait_method(ccstructs_serialiser_T, one_one_t, write);

/* Trait  table  of  methods.    Implementation  of  "ccstructs_serialiser_T"  for
   "one_one_t". */
static ccname_trait_table_type(ccstructs_serialiser_T) const ccname_trait_table(ccstructs_serialiser_T, one_one_t) = {
  .required_size	= ccname_trait_method(ccstructs_serialiser_T, one_one_t, required_size),
  .write	= ccname_trait_method(ccstructs_serialiser_T, one_one_t, write),
};

size_t
ccname_trait_method(ccstructs_serialiser_T, one_one_t, required_size) (ccstructs_serialiser_T I CCLIB_UNUSED)
/* Return the minimum number of bytes  required to hold the serialised representation
   of "serialised_one_one_t".*/
{
  return sizeof(serialised_one_one_t);
}

ccmem_block_t
ccname_trait_method(ccstructs_serialiser_T, one_one_t,
		    write) (cce_destination_t L CCLIB_UNUSED, ccstructs_serialiser_T I, ccmem_block_t B)
/* Trait  method implementation.   Serialise an  instance of  "one_one_t" in  the
   memory block "B". */
{
  CCLIB_PC(one_one_t const, S, ccstructs_serialiser_self(I));
  CCLIB_PC(serialised_one_one_t, W, B.ptr);
  ccmem_block_t	N = {
    .ptr	= B.ptr + sizeof(serialised_one_one_t),
    .len	= B.len - sizeof(serialised_one_one_t)
  };

  W->alpha	= S->alpha;
  W->beta	= S->beta;
  return N;
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline ccstructs_serialiser_T
ccname_trait_new(ccstructs_serialiser_T, one_one_t) (one_one_t * S)
/* Trait  constructor.   Build  an   instance  of  "ccstructs_serialiser_t"  as
   implemented by "one_one_t". */
{
  return ccname_new(ccstructs_serialiser_T)(ccstructs_core(S), &ccname_trait_table(ccstructs_serialiser_T, one_one_t));
}

/* ------------------------------------------------------------------ */

static ccname_trait_method_type(ccstructs_deserialiser_T, read)          ccname_trait_method(ccstructs_deserialiser_T, one_one_t, read);

/* Trait  table  of  methods.    Implementation  of  "ccstructs_deserialiser_T"  for
   "one_one_t". */
static ccname_trait_table_type(ccstructs_deserialiser_T) const ccname_trait_table(ccstructs_deserialiser_T, one_one_t) = {
  .read		= ccname_trait_method(ccstructs_deserialiser_T, one_one_t, read)
};

ccmem_block_t
ccname_trait_method(ccstructs_deserialiser_T, one_one_t, read)
  (cce_destination_t L CCLIB_UNUSED, ccstructs_deserialiser_T I, ccmem_block_t B)
/* Trait method  implementation.  Dedeserialise  an instance of  "one_one_t" from
   the memory block "B". */
{
  CCLIB_PC(one_one_t, S, ccstructs_deserialiser_self(I));
  CCLIB_PC(serialised_one_one_t const, W, B.ptr);
  ccmem_block_t	N = {
    .ptr	= B.ptr + sizeof(serialised_one_one_t),
    .len	= B.len - sizeof(serialised_one_one_t)
  };

  S->alpha	= W->alpha;
  S->beta	= W->beta;
  return N;
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline ccstructs_deserialiser_T
ccname_trait_new(ccstructs_deserialiser_T, one_one_t) (one_one_t * S)
/* Trait  constructor.   Build  an   instance  of  "ccstructs_deserialiser_t"  as
   implemented by "one_one_t". */
{
  return ccname_new(ccstructs_deserialiser_T)(ccstructs_core(S), &ccname_trait_table(ccstructs_deserialiser_T, one_one_t));
}

/* ------------------------------------------------------------------ */

void
test_1_1 (cce_destination_t upper_L)
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    one_one_t			S = {
      .alpha	= 1,
      .beta	= 2
    };
    one_one_t			R;

    uint8_t			buf[256];
    ccmem_block_t		B = { .ptr = buf, .len = 256 };
    ccmem_block_t		N;
    ccstructs_serialiser_T	IS = ccname_trait_new(ccstructs_serialiser_T,   one_one_t)(&S);
    ccstructs_deserialiser_T	ID = ccname_trait_new(ccstructs_deserialiser_T, one_one_t)(&R);

    N = ccstructs_serialiser_write(L, IS, B);
    cctests_assert_equal_size    (L, N.len, B.len - sizeof(serialised_one_one_t));
    cctests_assert_equal_pointer (L, N.ptr, B.ptr + sizeof(serialised_one_one_t));

    N = ccstructs_deserialiser_read(L, ID, B);
    cctests_assert_equal_size    (L, N.len, B.len - sizeof(serialised_one_one_t));
    cctests_assert_equal_pointer (L, N.ptr, B.ptr + sizeof(serialised_one_one_t));
    cctests_assert_equal_int(L, S.alpha, R.alpha);
    cctests_assert_equal_int(L, S.beta,  R.beta);

    cce_run_body_handlers(L);
  }
}


int
main (void)
{
  cctests_init("tests serialise trait");
  {
    cctests_begin_group("serialise to buffer method");
    {
      cctests_run(test_1_1);
    }
    cctests_end_group();
  }
  cctests_final();
}

/* end of file */
