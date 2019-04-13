/*
  Part of: CCStructs
  Contents: exception handlers
  Date: Sat Sep 22, 2018

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

#include "ccstructs-internals.h"
#include <stdio.h>


/** --------------------------------------------------------------------
 ** Generic struct handling: exception handlers.
 ** ----------------------------------------------------------------- */

__attribute__((__nonnull__(1,2)))
static void
ccstructs_clean_handler_function (cce_condition_t const * C CCSTRUCTS_UNUSED, cce_clean_handler_t const * const H)
{
  CCSTRUCTS_PC(ccstructs_clean_handler_t const, I_H, H);

  ccstructs_dtor_delete(I_H->dtor);
}

void
ccstructs_init_and_register_clean_handler (cce_location_t * L, ccstructs_clean_handler_t * I_H, ccstructs_dtor_I I)
{
  cce_init_and_register_handler(L, ccstructs_handler_handler(I_H), ccstructs_clean_handler_function, cce_resource_pointer(NULL));
  I_H->dtor = I;
}

/* ------------------------------------------------------------------ */

__attribute__((__nonnull__(1,2)))
static void
ccstructs_error_handler_function (cce_condition_t const * C CCSTRUCTS_UNUSED, cce_error_handler_t const * const H)
{
  CCSTRUCTS_PC(ccstructs_error_handler_t const, I_H, H);

  ccstructs_dtor_delete(I_H->dtor);
}

void
ccstructs_init_and_register_error_handler (cce_location_t * L, ccstructs_error_handler_t * I_H, ccstructs_dtor_I I)
{
  cce_init_and_register_handler(L, ccstructs_handler_handler(I_H), ccstructs_error_handler_function, cce_resource_pointer(NULL));
  I_H->dtor = I;
}

/* end of file */
