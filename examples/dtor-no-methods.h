/*
  Part of: CCStructs
  Contents: header file for sample struct with no methods table
  Date: Thu Dec 27, 2018

  Abstract

	This header file  defines the struct "my_alpha_t"  and shows how
	to  implement the  main interfaces  for it.   "my_alpha_t" is  a
	simple  struct with  embedded  fields, no  pointers to  external
	memory blocks.

	The "dtor-no-methods"  example shows  how to implement  a struct
	using  no  methods  table   for  the  struct-specific  interface
	constructors.

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

#ifndef DTOR_NO_METHODS_H
#define DTOR_NO_METHODS_H 1


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "ccstructs.h"
#include <stdio.h>
#include <stdlib.h>


/** --------------------------------------------------------------------
 ** Type definitions.
 ** ----------------------------------------------------------------- */

typedef struct my_alpha_t		my_alpha_t;

struct my_alpha_t {
  double	X;
  double	Y;
  double	Z;
};


/** --------------------------------------------------------------------
 ** Function prototypes: constructors and destructors.
 ** ----------------------------------------------------------------- */

/* Constructor function that allocates the  struct on the heap using the
   standard memory allocator implemented by CCMemory. */
ccstructs_decl my_alpha_t const * my_new_alpha (cce_destination_t L, double x, double y, double z)
  __attribute__((__nonnull__((1))));

/* Initialisation  function   that  initialises  an   already  allocated
   struct. */
ccstructs_decl void my_init_alpha (my_alpha_t * self, double x, double y, double z)
  __attribute__((__nonnull__((1))));

/* Finalisation function.  Releases all the asynchronous resources owned
   by  the  struct,   if  any.   The  struct's  memory   block  is  left
   untouched. */
ccstructs_decl void my_final_alpha (my_alpha_t const * self)
  __attribute__((__nonnull__((1))));

/* Destructor function.   Releases all the asynchronous  resources owned
   by the struct,  if any.  The struct's memory block  is released using
   the standard memory allocator implemented by CCMemory.  */
ccstructs_decl void my_delete_alpha (my_alpha_t const * self)
  __attribute__((__nonnull__((1))));


/** --------------------------------------------------------------------
 ** Function prototypes: plain exception handlers.
 ** ----------------------------------------------------------------- */

/* Initialises a "clean" exception handler that calls "my_final_alpha()"
   as destructor function. */
ccstructs_decl void my_alpha_register_clean_handler_final (cce_destination_t L, cce_clean_handler_t * H, my_alpha_t const * self)
  __attribute__((__nonnull__(1,2,3)));

/* Initialises    an    "error"    exception    handler    that    calls
   "my_final_alpha()" as destructor function. */
ccstructs_decl void my_alpha_register_error_handler_final (cce_destination_t L, cce_error_handler_t * H, my_alpha_t const * self)
  __attribute__((__nonnull__(1,2,3)));

/* Initialises    a    "clean"     exception    handler    that    calls
   "my_delete_alpha()" as destructor function. */
ccstructs_decl void my_alpha_register_clean_handler_delete (cce_destination_t L, cce_clean_handler_t * H, my_alpha_t const * self)
  __attribute__((__nonnull__(1,2,3)));

/* Initialises    an    "error"    exception    handler    that    calls
   "my_delete_alpha()" as destructor function. */
ccstructs_decl void my_alpha_register_error_handler_delete (cce_destination_t L, cce_error_handler_t * H, my_alpha_t const * self)
  __attribute__((__nonnull__(1,2,3)));


/** --------------------------------------------------------------------
 ** Interface "dtor".
 ** ----------------------------------------------------------------- */

/* Constructor  for   a  "dtor"  interface  that   finalises  instances
   allocated on the stack or embedded into enclosing structs. */
ccstructs_decl ccstructs_dtor_I my_new_alpha_embedded_I_dtor (my_alpha_t const * self)
  __attribute__((__nonnull__(1)));

/* Constructor  for  a  "dtor"   interface  that  finalises  standalone
   instances dynamically allocated on the heap. */
ccstructs_decl ccstructs_dtor_I my_new_alpha_standalone_I_dtor (my_alpha_t const * self)
  __attribute__((__nonnull__(1)));


/** --------------------------------------------------------------------
 ** Function prototypes: printing.
 ** ----------------------------------------------------------------- */

ccstructs_decl void my_print_alpha (cce_destination_t L, FILE * stream, my_alpha_t const * self)
  __attribute__((__nonnull__(1,2,3)));


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#endif /* defined DTOR_NO_METHODS_H */

/* end of file */
