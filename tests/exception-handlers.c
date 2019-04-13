/*
  Part of: CCStructs
  Contents: tests for the exception handlers
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
 ** Exception handlers: empty release method.
 ** ----------------------------------------------------------------- */

typedef struct one_t	one_t;

struct one_t {
  void *	pointer;
};

/* ------------------------------------------------------------------ */
/* Destructors interface implementation. */

static void
ccname_iface_method(ccstructs_dtor_I, one_t, final) (ccstructs_dtor_I I)
{
  CCSTRUCTS_PC(one_t, S, ccstructs_dtor_self(I));

  ccmem_std_free(S->pointer);
  fprintf(stderr, "%s: final method for %p\n", __func__, (void *)S);
}

static void
ccname_iface_method(ccstructs_dtor_I, one_t, release) (ccstructs_dtor_I I)
{
  CCSTRUCTS_PC(one_t, S, ccstructs_dtor_self(I));

  fprintf(stderr, "%s: release method for %p\n", __func__, (void *)S);
}

static ccname_iface_table_type(ccstructs_dtor_I) const ccname_iface_table(ccstructs_dtor_I, one_t) = {
  .final	= ccname_iface_method(ccstructs_dtor_I, one_t, final),
  .release	= ccname_iface_method(ccstructs_dtor_I, one_t, release)
};

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccstructs_dtor_I
ccname_iface_new(ccstructs_dtor_I, one_t) (one_t * S)
{
  return ccname_new(ccstructs_dtor_I)(ccstructs_core(S), &ccname_iface_table(ccstructs_dtor_I, one_t));
}

/* ------------------------------------------------------------------ */

void
test_1_1 (cce_destination_t upper_L)
/* Destruction through clean handler. */
{
  cce_location_t		L[1];
  ccstructs_clean_handler_t	I_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    one_t	S = {
      .pointer	= ccmem_std_malloc(L, 256)
    };
    ccstructs_init_and_register_handler(L, I_H, ccname_iface_new(ccstructs_dtor_I, one_t)(&S));

    memset(S.pointer, 123, 256);
    cce_run_body_handlers(L);
  }
}

void
test_1_2 (cce_destination_t upper_L)
/* Destruction through error handler. */
{
  cce_location_t		L[1];
  ccstructs_error_handler_t	I_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    one_t	S = {
      .pointer	= ccmem_std_malloc(L, 256)
    };
    ccstructs_init_and_register_handler(L, I_H, ccname_iface_new(ccstructs_dtor_I, one_t)(&S));

    memset(S.pointer, 123, 256);
    cce_raise(L, cctests_condition_new_signal_1());
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Exception handlers: non-empty release method.
 ** ----------------------------------------------------------------- */

typedef struct two_t	two_t;

struct two_t {
  void *	pointer;
};

two_t *
ccname_new(two_t) (cce_destination_t upper_L, int init)
{
  cce_location_t	L[1];
  ccmem_error_handler_t	S_H[1];
  two_t *		S;

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    S		= ccmem_std_malloc_guarded(L, S_H, sizeof(two_t));
    S->pointer	= ccmem_std_malloc(L, 256);
    memset(S->pointer, init, 256);
    cce_run_body_handlers(L);
  }
  return S;
}

/* ------------------------------------------------------------------ */
/* Destructors interface implementation. */

static void
ccname_iface_method(ccstructs_dtor_I, two_t, final) (ccstructs_dtor_I I)
{
  CCSTRUCTS_PC(two_t, S, ccstructs_dtor_self(I));

  ccmem_std_free(S->pointer);
  fprintf(stderr, "%s: final method for %p\n", __func__, (void *)S);
}

static void
ccname_iface_method(ccstructs_dtor_I, two_t, release) (ccstructs_dtor_I I)
{
  CCSTRUCTS_PC(two_t, S, ccstructs_dtor_self(I));

  ccmem_std_free(S);
  fprintf(stderr, "%s: release method for %p\n", __func__, (void *)S);
}

static ccname_iface_table_type(ccstructs_dtor_I) const ccname_iface_table(ccstructs_dtor_I, two_t) = {
  .final	= ccname_iface_method(ccstructs_dtor_I, two_t, final),
  .release	= ccname_iface_method(ccstructs_dtor_I, two_t, release)
};

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccstructs_dtor_I
ccname_iface_new(ccstructs_dtor_I, two_t) (two_t * S)
{
  return ccname_new(ccstructs_dtor_I)(ccstructs_core(S), &ccname_iface_table(ccstructs_dtor_I, two_t));
}

/* ------------------------------------------------------------------ */

two_t *
ccname_new(two_t, guarded_clean) (cce_destination_t L, ccstructs_clean_handler_t * I_H, int init)
{
  two_t * S = ccname_new(two_t)(L, init);
  ccstructs_init_and_register_handler(L, I_H, ccname_iface_new(ccstructs_dtor_I, two_t)(S));
  return S;
}

two_t *
ccname_new(two_t, guarded_error) (cce_destination_t L, ccstructs_error_handler_t * I_H, int init)
{
  two_t * S = ccname_new(two_t)(L, init);
  ccstructs_init_and_register_handler(L, I_H, ccname_iface_new(ccstructs_dtor_I, two_t)(S));
  return S;
}

#define two_new_guarded(L,I_H,S)		\
  _Generic((I_H),						  \
	   ccstructs_clean_handler_t	*: ccname_new(two_t, guarded_clean), \
	   ccstructs_error_handler_t	*: ccname_new(two_t, guarded_error))(L,I_H,S)

/* ------------------------------------------------------------------ */

void
test_2_1 (cce_destination_t upper_L)
/* Destruction through clean handler. */
{
  cce_location_t		L[1];
  ccstructs_clean_handler_t	I_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    two_t * S = ccname_new(two_t)(L, 123);
    ccstructs_init_and_register_handler(L, I_H, ccname_iface_new(ccstructs_dtor_I, two_t)(S));

    cce_run_body_handlers(L);
  }
}

void
test_2_2 (cce_destination_t upper_L)
/* Destruction through error handler. */
{
  cce_location_t		L[1];
  ccstructs_error_handler_t	I_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    two_t * S = ccname_new(two_t)(L, 123);
    ccstructs_init_and_register_handler(L, I_H, ccname_iface_new(ccstructs_dtor_I, two_t)(S));

    cce_raise(L, cctests_condition_new_signal_1());
    cce_run_body_handlers(L);
  }
}

void
test_2_3 (cce_destination_t upper_L)
/* Destruction through clean handler from guarded constructor. */
{
  cce_location_t		L[1];
  ccstructs_clean_handler_t	I_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    two_t * S = two_new_guarded(L, I_H, 123);

    fprintf(stderr, "%s: %p\n", __func__, (void *)S);
    cce_run_body_handlers(L);
  }
}

void
test_2_4 (cce_destination_t upper_L)
/* Destruction through error handler from guarded constructor. */
{
  cce_location_t		L[1];
  ccstructs_error_handler_t	I_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    two_t * S = two_new_guarded(L, I_H, 123);

    fprintf(stderr, "%s: %p\n", __func__, (void *)S);
    cce_raise(L, cctests_condition_new_signal_1());
    cce_run_body_handlers(L);
  }
}


int
main (void)
{
  cctests_init("tests exception handlers");
  {
    cctests_begin_group("empty release method");
    {
      cctests_run(test_1_1);
      cctests_run(test_1_2);
    }
    cctests_end_group();

    cctests_begin_group("non-empty release method");
    {
      cctests_run(test_2_1);
      cctests_run(test_2_2);
      cctests_run(test_2_3);
      cctests_run(test_2_4);
    }
    cctests_end_group();
  }
  cctests_final();
}

/* end of file */
