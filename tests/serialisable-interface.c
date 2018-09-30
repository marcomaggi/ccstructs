/*
  Part of: CCStructs
  Contents: tests for the serialisable interface
  Date: Sep 30, 2018

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
 ** Serialisable interface: fwrite method.
 ** ----------------------------------------------------------------- */

typedef struct one_one_t		one_one_t;
typedef struct serialised_one_one_t	serialised_one_one_t;

struct one_one_t {
  bool	alpha;
  bool	beta;
};

struct serialised_one_one_t {
  bool	alpha;
  bool	beta;
};

static size_t
one_one_serialisable_iface_minimum_size_method (ccstructs_serialisable_I I CCSTRUCTS_UNUSED)
{
  return sizeof(serialised_one_one_t);
}

static ccmem_block_t
one_one_serialisable_iface_to_block_method (cce_destination_t L CCSTRUCTS_UNUSED, ccstructs_serialisable_I I, ccmem_block_t B)
{
  CCSTRUCTS_PC(one_one_t const, S, ccstructs_serialisable_self(I));
  CCSTRUCTS_PC(serialised_one_one_t, W, B.ptr);
  ccmem_block_t	N = {
    .ptr	= B.ptr + sizeof(serialised_one_one_t),
    .len	= B.len - sizeof(serialised_one_one_t)
  };

  W->alpha	= S->alpha;
  W->beta	= S->beta;
  return N;
}

static ccmem_block_t
one_one_serialisable_iface_from_block_method (cce_destination_t L CCSTRUCTS_UNUSED, ccstructs_serialisable_I I, ccmem_block_t B)
{
  CCSTRUCTS_PC(one_one_t, S, ccstructs_serialisable_self(I));
  CCSTRUCTS_PC(serialised_one_one_t const, W, B.ptr);
  ccmem_block_t	N = {
    .ptr	= B.ptr + sizeof(serialised_one_one_t),
    .len	= B.len - sizeof(serialised_one_one_t)
  };

  S->alpha	= W->alpha;
  S->beta	= W->beta;
  return N;
}

static ccstructs_serialisable_I_methods_t const one_one_serialisable_iface_methods = {
  .minimum_size	= one_one_serialisable_iface_minimum_size_method,
  .to_block	= one_one_serialisable_iface_to_block_method,
  .from_block	= one_one_serialisable_iface_from_block_method
};

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccstructs_serialisable_I
one_one_new_iface_serialisable (one_one_t * S)
{
  return ccstructs_new_serialisable((ccstructs_core_t *)S, &one_one_serialisable_iface_methods);
}

void
test_1_1 (cce_destination_t upper_L)
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    one_one_t	S = {
      .alpha	= 1,
      .beta	= 2
    };
    one_one_t	R;

    uint8_t	buf[256];
    ccmem_block_t	B = {
      .ptr	= buf,
      .len	= 256
    };
    ccmem_block_t	N;
    ccstructs_serialisable_I	IS = one_one_new_iface_serialisable(&S);
    ccstructs_serialisable_I	IR = one_one_new_iface_serialisable(&R);

    N = ccstructs_serialisable_to_block(L, IS, B);
    cctests_assert_equal_size    (L, N.len, B.len - sizeof(serialised_one_one_t));
    cctests_assert_equal_pointer (L, N.ptr, B.ptr + sizeof(serialised_one_one_t));

    N = ccstructs_serialisable_from_block(L, IR, B);
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
  cctests_init("tests serialisable interface");
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
