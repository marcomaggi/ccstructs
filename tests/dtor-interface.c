/*
  Part of: CCStructs
  Contents: tests for the dtor interface
  Date: Sep 24, 2018

  Abstract



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
 ** Dtor interface for embedded struct.
 ** ----------------------------------------------------------------- */

typedef struct one_t	one_t;

struct one_t {
  void *	pointer;
};

void
ccname_init(one_t) (cce_destination_t upper_L, one_t * S)
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    S->pointer = ccmem_std_malloc(L, 256);
    memset(S->pointer, 123, 256);
    cce_run_body_handlers(L);
  }
}

void
ccname_final(one_t) (one_t * S)
{
  ccmem_free(ccmem_standard_allocator, S->pointer);
}

/* ------------------------------------------------------------------ */

static ccstructs_core_destructor_fun_t	one_destructor;

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccstructs_dtor_I
ccname_iface_new(ccstructs_dtor_I, one_t) (one_t const * const S)
{
  return ccname_new(ccstructs_dtor_I)(ccstructs_core(S), one_destructor);
}

void
one_destructor (ccstructs_core_t * self)
{
  CCSTRUCTS_PC(one_t, S, self);

  ccname_final(one_t)(S);
  if (1) { fprintf(stderr, "%s: finalised by dtor\n", __func__); }
}

/* ------------------------------------------------------------------ */

void
test_1_1 (cce_destination_t upper_L)
/* Call the dtor delete function. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    one_t	S = {
      .pointer	= ccmem_malloc(L, ccmem_standard_allocator, 256)
    };
    ccstructs_dtor_I	I = ccname_iface_new(ccstructs_dtor_I, one_t)(&S);

    memset(S.pointer, 123, 256);
    ccstructs_dtor_destroy(I);
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Dtor interface for standalone struct.
 ** ----------------------------------------------------------------- */

typedef struct two_t	two_t;

struct two_t {
  void *	pointer;
};

two_t *
ccname_new(two_t) (cce_destination_t upper_L)
{
  cce_location_t	L[1];
  ccmem_error_handler_t	S_H[1];
  two_t *		S;

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    S          = ccmem_std_malloc_guarded(L, S_H, sizeof(two_t));
    S->pointer = ccmem_std_malloc(L, 256);
    memset(S->pointer, 123, 256);
    cce_run_body_handlers(L);
  }
  return S;
}

void
ccname_delete(two_t) (two_t * S)
{
  ccmem_free(ccmem_standard_allocator, S->pointer);
  ccmem_free(ccmem_standard_allocator, S);
}

/* ------------------------------------------------------------------ */

static ccstructs_core_destructor_fun_t	two_destructor;

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccstructs_dtor_I
ccname_iface_new(ccstructs_dtor_I, two_t) (two_t const * const S)
{
  return ccname_new(ccstructs_dtor_I)(ccstructs_core(S), two_destructor);
}

void
two_destructor (ccstructs_core_t * self)
{
  CCSTRUCTS_PC(two_t, S, self);

  ccname_delete(two_t)(S);
  if (1) { fprintf(stderr, "%s: deleted by dtor\n", __func__); }
}

/* ------------------------------------------------------------------ */

void
test_2_1 (cce_destination_t upper_L)
/* Call the dtor delete function. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    two_t *		S = ccname_new(two_t)(L);
    ccstructs_dtor_I	I = ccname_iface_new(ccstructs_dtor_I, two_t)(S);
    ccstructs_dtor_destroy(I);
    cce_run_body_handlers(L);
  }
}


int
main (void)
{
  cctests_init("tests dtor interface");
  {
    cctests_begin_group("embedded struct");
    {
      cctests_run(test_1_1);
    }
    cctests_end_group();

    cctests_begin_group("standalone struct");
    {
      cctests_run(test_2_1);
    }
    cctests_end_group();
  }
  cctests_final();
}

/* end of file */
