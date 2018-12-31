/*
  Part of: CCStructs
  Contents: tests for the exception handlers
  Date: Sep 24, 2018

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
 ** Exception handlers: empty delete method.
 ** ----------------------------------------------------------------- */

typedef struct one_t	one_t;

struct one_t {
  void *	pointer;
};

static void
one_dtor_method_delete (ccstructs_dtor_I I)
{
  CCSTRUCTS_PC(one_t, S, ccstructs_dtor_self(I));

  fprintf(stderr, "%s: delete method for %p\n", __func__, (void *)S);
}

static void
one_dtor_method_final (ccstructs_dtor_I I)
{
  CCSTRUCTS_PC(one_t, S, ccstructs_dtor_self(I));

  ccmem_free(ccmem_standard_allocator, S->pointer);
  fprintf(stderr, "%s: final method for %p\n", __func__, (void *)S);
}

static ccstructs_dtor_I_methods_t const one_dtor_I_methods = {
  .delete	= one_dtor_method_delete,
  .final	= one_dtor_method_final
};

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccstructs_dtor_I
one_new_I_dtor (one_t * S)
{
  return ccstructs_new_dtor(ccstructs_core(S), &one_dtor_I_methods);
}

void
test_1_1 (cce_destination_t upper_L)
/* Call the delete method. */
{
  cce_location_t		L[1];
  ccstructs_clean_handler_t	I_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    one_t	S = {
      .pointer	= ccmem_malloc(L, ccmem_standard_allocator, 256)
    };
    ccstructs_handler_init(L, I_H, one_new_I_dtor(&S));

    memset(S.pointer, 123, 256);
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Exception handlers: non-empty delete method.
 ** ----------------------------------------------------------------- */

typedef struct two_t	two_t;

struct two_t {
  void *	pointer;
};

two_t *
two_new (cce_destination_t upper_L, int init)
{
  cce_location_t	L[1];
  cce_error_handler_t	S_H[1];
  two_t *		S;

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    S		= cce_sys_malloc_guarded(L, S_H, sizeof(two_t));
    S->pointer	= cce_sys_malloc(L, 256);
    memset(S->pointer, init, 256);
    cce_run_body_handlers(L);
  }
  return S;
}

/* ------------------------------------------------------------------ */
/* Destructors interface implementation. */

static void
two_dtor_method_delete (ccstructs_dtor_I I)
{
  CCSTRUCTS_PC(two_t, S, ccstructs_dtor_self(I));

  free(S);
  fprintf(stderr, "%s: delete method for %p\n", __func__, (void *)S);
}

static void
two_dtor_method_final (ccstructs_dtor_I I)
{
  CCSTRUCTS_PC(two_t, S, ccstructs_dtor_self(I));

  free(S->pointer);
  fprintf(stderr, "%s: final method for %p\n", __func__, (void *)S);
}

static ccstructs_dtor_I_methods_t const two_dtor_I_methods = {
  .delete	= two_dtor_method_delete,
  .final	= two_dtor_method_final
};

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccstructs_dtor_I
two_new_I_dtor (two_t * S)
{
  return ccstructs_new_dtor(ccstructs_core(S), &two_dtor_I_methods);
}

/* ------------------------------------------------------------------ */

two_t *
two_new_guarded_clean (cce_destination_t L, ccstructs_clean_handler_t * I_H, int init)
{
  two_t * S = two_new(L, init);
  ccstructs_handler_init(L, I_H, two_new_I_dtor(S));
  return S;
}

two_t *
two_new_guarded_error (cce_destination_t L, ccstructs_error_handler_t * I_H, int init)
{
  two_t * S = two_new(L, init);
  ccstructs_handler_init(L, I_H, two_new_I_dtor(S));
  return S;
}

#define two_new_guarded(L,I_H,S)		\
  _Generic((I_H),						  \
	   ccstructs_clean_handler_t	*: two_new_guarded_clean, \
	   ccstructs_error_handler_t	*: two_new_guarded_error)(L,I_H,S)

/* ------------------------------------------------------------------ */

void
test_2_1 (cce_destination_t upper_L)
{
  cce_location_t		L[1];
  ccstructs_clean_handler_t	I_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    two_t * S = two_new(L, 123);
    ccstructs_handler_init(L, I_H, two_new_I_dtor(S));

    cce_run_body_handlers(L);
  }
}

void
test_2_2 (cce_destination_t upper_L)
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


int
main (void)
{
  cctests_init("tests exception handlers");
  {
    cctests_begin_group("empty delete method");
    {
      cctests_run(test_1_1);
    }
    cctests_end_group();

    cctests_begin_group("non-empty delete method");
    {
      cctests_run(test_2_1);
      cctests_run(test_2_2);
    }
    cctests_end_group();
  }
  cctests_final();
}

/* end of file */
