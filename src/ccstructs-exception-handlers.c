/*
  Part of: CCStructs
  Contents: exception handlers
  Date: Sat Sep 22, 2018

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

#include "ccstructs-internals.h"


/** --------------------------------------------------------------------
 ** Generic struct handling: exception handlers.
 ** ----------------------------------------------------------------- */

__attribute__((nonnull(1,2)))
static void
ccstructs_clean_handler_function (cce_condition_t const * C CCSTRUCTS_UNUSED, cce_handler_t * H)
{
  CCSTRUCTS_PC(ccstructs_clean_handler_t, S_H, H);

  ccstructs_dtors_delete(S_H->dtors);
  if (0) { fprintf(stderr, "%s: done releasing '%p'\n", __func__, (void *)(ccstructs_dtors_self(S_H->dtors))); }
}

void
ccstructs_clean_handler_init (cce_location_t * L, ccstructs_clean_handler_t * I_H, ccstructs_dtors_I I)
{
  I_H->handler.handler.function	= ccstructs_clean_handler_function;
  I_H->dtors			= I;
  cce_register_clean_handler(L, &(I_H->handler));
}

/* ------------------------------------------------------------------ */

__attribute__((nonnull(1,2)))
static void
ccstructs_error_handler_function (cce_condition_t const * C CCSTRUCTS_UNUSED, cce_handler_t * H)
{
  CCSTRUCTS_PC(ccstructs_error_handler_t, S_H, H);

  ccstructs_dtors_delete(S_H->dtors);
  if (0) { fprintf(stderr, "%s: done releasing '%p'\n", __func__, (void *)(ccstructs_dtors_self(S_H->dtors))); }
}

void
ccstructs_error_handler_init (cce_location_t * L, ccstructs_error_handler_t * I_H, ccstructs_dtors_I I)
{
  I_H->handler.handler.function	= ccstructs_error_handler_function;
  I_H->dtors			= I;
  cce_register_error_handler(L, &(I_H->handler));
}

/* end of file */
