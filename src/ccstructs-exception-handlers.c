/*
  Part of: CCStructs
  Contents: exception handlers
  Date: Sat Sep 22, 2018

  Abstract

	This  module  traits  CCExceptions's   exception  handlers  with  CCStructs's
	destructor traits.

  Copyright (C) 2018, 2019 Marco Maggi <mrc.mgg@gmail.com>

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

void
ccstructs_init_and_register_clean_handler (cce_location_t * L, ccstructs_clean_handler_t * I_H, ccstructs_dtor_T I)
{
  cce_init_and_register_handler(L, ccstructs_handler_handler(I_H), cce_default_clean_handler_function,
				cce_resource_pointer(I.self), (cce_resource_destructor_fun_t *)I.destroy);
}

void
ccstructs_init_and_register_error_handler (cce_location_t * L, ccstructs_error_handler_t * I_H, ccstructs_dtor_T I)
{
  cce_init_and_register_handler(L, ccstructs_handler_handler(I_H), cce_default_error_handler_function,
				cce_resource_pointer(I.self), (cce_resource_destructor_fun_t *)I.destroy);
}

/* end of file */
