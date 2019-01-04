/*
  Part of: CCStructs
  Contents: header file for sample struct with methods table
  Date: Thu Dec 27, 2018

  Abstract

	This header file  defines the struct "my_alpha_t"  and shows how
	to  implement the  main interfaces  for it.   "my_alpha_t" is  a
	simple  struct with  embedded  fields, no  pointers to  external
	memory blocks.

	The "dtor-with-methods-and-names" example shows how to implement
	a struct using a methods table for the struct-specific interface
	constructors: every instance of the  struct type holds a pointer
	to a struct implementing a methods table.

	This example uses the features from the header file "ccnames.h".

  Copyright (C) 2018, 2019 Marco Maggi <marco.maggi-ipsu@poste.it>

  The author hereby  grant permission to use,  copy, modify, distribute,
  and  license this  software  and its  documentation  for any  purpose,
  provided that  existing copyright notices  are retained in  all copies
  and that  this notice  is included verbatim  in any  distributions. No
  written agreement, license, or royalty fee  is required for any of the
  authorized uses.  Modifications to this software may be copyrighted by
  their authors and need not  follow the licensing terms described here,
  provided that the new terms are clearly indicated on the first page of
  each file where they apply.

  IN NO  EVENT SHALL THE AUTHOR  OR DISTRIBUTORS BE LIABLE  TO ANY PARTY
  FOR  DIRECT, INDIRECT, SPECIAL,  INCIDENTAL, OR  CONSEQUENTIAL DAMAGES
  ARISING OUT  OF THE  USE OF THIS  SOFTWARE, ITS DOCUMENTATION,  OR ANY
  DERIVATIVES  THEREOF, EVEN  IF THE  AUTHOR  HAVE BEEN  ADVISED OF  THE
  POSSIBILITY OF SUCH DAMAGE.

  THE  AUTHOR  AND DISTRIBUTORS  SPECIFICALLY  DISCLAIM ANY  WARRANTIES,
  INCLUDING,   BUT   NOT  LIMITED   TO,   THE   IMPLIED  WARRANTIES   OF
  MERCHANTABILITY,    FITNESS   FOR    A    PARTICULAR   PURPOSE,    AND
  NON-INFRINGEMENT.  THIS  SOFTWARE IS PROVIDED  ON AN "AS  IS" BASIS,
  AND  THE  AUTHOR  AND  DISTRIBUTORS  HAVE  NO  OBLIGATION  TO  PROVIDE
  MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

*/

#ifndef DTOR_WITH_METHODS_AND_NAMES_H
#define DTOR_WITH_METHODS_AND_NAMES_H 1


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "ccstructs.h"
#include "ccnames.h"
#include <stdio.h>
#include <stdlib.h>


/** --------------------------------------------------------------------
 ** Type definitions.
 ** ----------------------------------------------------------------- */

typedef struct my_alpha_t			my_alpha_t;
typedef struct ccname_table_type(my_alpha_t)	ccname_table_type(my_alpha_t);

struct my_alpha_t {
  ccname_table_type(my_alpha_t) const *	methods;
  double	X;
  double	Y;
  double	Z;
};


/** --------------------------------------------------------------------
 ** Function prototypes: constructors.
 ** ----------------------------------------------------------------- */

/* Constructor function.  Allocate the struct instance on the heap using
   the standard memory allocator implemented by CCMemory. */
ccstructs_decl my_alpha_t const * ccname_new(my_alpha_t) (cce_destination_t L, double x, double y, double z)
  __attribute__((__nonnull__((1))));

/* Constructor function.  Initialise an already allocated struct. */
ccstructs_decl void ccname_init(my_alpha_t) (my_alpha_t * self, double x, double y, double z)
  __attribute__((__nonnull__((1))));


/** --------------------------------------------------------------------
 ** Interface "dtor".
 ** ----------------------------------------------------------------- */

/* Interface  constructor function.   Return a  new instance  of "dtor"
   interface which destroys the struct instance. */
ccstructs_decl ccstructs_dtor_I ccname_iface_new(ccstructs_dtor_I, my_alpha_t) (my_alpha_t const * self)
  __attribute__((__nonnull__(1)));


/** --------------------------------------------------------------------
 ** Function prototypes: printing.
 ** ----------------------------------------------------------------- */

ccstructs_decl void my_print_alpha (cce_destination_t L, FILE * stream, my_alpha_t const * self)
  __attribute__((__nonnull__(1,2,3)));


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#endif /* defined DTOR_WITH_METHODS_AND_NAMES_H */

/* end of file */
