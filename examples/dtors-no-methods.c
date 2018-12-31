/*
  Part of: CCStructs
  Contents: body file for sample struct with no methods table
  Date: Thu Dec 27, 2018

  Abstract

	This body file defines the API to handle the struct "my_alpha_t"
	and shows how to implement the main interfaces for it.

	The "dtors-no-methods"  example shows how to  implement a struct
	using  no  methods  table   for  the  struct-specific  interface
	constructors.

  Copyright (C) 2018 Marco Maggi <marco.maggi-ipsu@poste.it>

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


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "dtors-no-methods.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


/** --------------------------------------------------------------------
 ** Constructors and destructors.
 ** ----------------------------------------------------------------- */

void
my_init_alpha (my_alpha_t * self, double x, double y, double z)
/* Initialise an already allocated struct. */
{
  self->X	= x;
  self->Y	= y;
  self->Z	= z;
}

my_alpha_t const *
/* Instance  constructor   that  allocates  memory  with   the  standard
   allocator implemented by CCMemory. */
my_new_alpha (cce_destination_t L, double x, double y, double z)
{
  my_alpha_t *	self = ccmem_std_malloc(L, sizeof(my_alpha_t));

  my_init_alpha(self, x, y, z);
  return (my_alpha_t const *) self;
}

void
my_final_alpha (my_alpha_t const * self CCSTRUCTS_UNUSED)
/* Destructor   function.   Release   all  the   asynchronous  resources
   associated to the struct instance; does not touch the struct itself.

   To be  used to destroy instances  allocated on the stack  or embedded
   into an enclosing struct instance. */
{
  if (1) { fprintf(stderr, "%-35s: finalised\n", __func__); }
}

static void
my_alpha_release_struct (my_alpha_t const * self)
/* Release the memory  block allocated for the struct  instance usin the
   standard memory  allocator implemented  by CCMemory.  Does  not touch
   the struct's fields. */
{
  ccmem_std_free((void *)self);
  if (1) { fprintf(stderr, "%-35s: released\n", __func__); }
}

void
my_delete_alpha (my_alpha_t const * self)
/* Destructor   function.   Release   all  the   asynchronous  resources
   associated to the struct instance; release the memory block allocated
   for  the   struct  instance  using  the   standard  memory  allocator
   implemented by CCMemory.

   To be used to destroy instances dynamically allocated on the heap. */
{
  my_final_alpha(self);
  my_alpha_release_struct(self);
  if (1) { fprintf(stderr, "%-35s: deleted\n", __func__); }
}


/** --------------------------------------------------------------------
 ** Plain exception handlers.
 ** ----------------------------------------------------------------- */

static void
my_alpha_handler_final (cce_condition_t const * C CCSTRUCTS_UNUSED, cce_handler_t * H)
/* Destructor   handler.   Release   all   the  asynchronous   resources
   associated to the struct instance; does not touch the struct itself.

   To be  used to destroy instances  allocated on the stack  or embedded
   into an enclosing struct instance. */
{
  CCSTRUCTS_PC(my_alpha_t, self, H->pointer);

  my_final_alpha(self);
  if (1) { fprintf(stderr, "%-35s: finalised by plain handler\n", __func__); }
}

void
my_alpha_register_clean_handler_final (cce_destination_t L, cce_clean_handler_t * H, my_alpha_t const * self)
{
  H->handler.function	= my_alpha_handler_final;
  H->handler.pointer	= (void *)self;
  cce_register_clean_handler(L, H);
}

void
my_alpha_register_error_handler_final (cce_destination_t L, cce_error_handler_t * H, my_alpha_t const * self)
{
  H->handler.function	= my_alpha_handler_final;
  H->handler.pointer	= (void *)self;
  cce_register_error_handler(L, H);
}

/* ------------------------------------------------------------------ */

static void
my_alpha_handler_delete (cce_condition_t const * C CCSTRUCTS_UNUSED, cce_handler_t * H)
/* Destructor   handler.   Release   all   the  asynchronous   resources
   associated to the struct instance; release the memory block allocated
   for  the   struct  instance  using  the   standard  memory  allocator
   implemented by CCMemory.

   To be used to destroy instances dynamically allocated on the heap. */
{
  CCSTRUCTS_PC(my_alpha_t, self, H->pointer);

  my_delete_alpha(self);
  if (1) { fprintf(stderr, "%-35s: deleted by plain handler\n", __func__); }
}

void
my_alpha_register_clean_handler_delete (cce_destination_t L, cce_clean_handler_t * H, my_alpha_t const * self)
{
  H->handler.function	= my_alpha_handler_delete;
  H->handler.pointer	= (void *)self;
  cce_register_clean_handler(L, H);
}

void
my_alpha_register_error_handler_delete (cce_destination_t L, cce_error_handler_t * H, my_alpha_t const * self)
{
  H->handler.function	= my_alpha_handler_delete;
  H->handler.pointer	= (void *)self;
  cce_register_error_handler(L, H);
}


/** --------------------------------------------------------------------
 ** Interface "dtors": embedded struct.
 ** ----------------------------------------------------------------- */

/* This is for struct instances allocated on the stack or embedded in an
   enclosing struct. */

/* Interface "dtors": "delete()" method. */
static void
my_alpha_embedded_dtors_method_delete (ccstructs_dtors_I I CCSTRUCTS_UNUSED)
{
  if (1) { fprintf(stderr, "%-35s: deleted by dtors\n", __func__); }
}

/* Interface "dtors": "final()" method. */
static void
my_alpha_embedded_dtors_method_final (ccstructs_dtors_I I)
{
  CCSTRUCTS_PC(my_alpha_t, self, ccstructs_dtors_self(I));

  my_final_alpha(self);
  if (1) { fprintf(stderr, "%-35s: finalised by dtors\n", __func__); }
}

/* Methods table  for the  "dtors" interface. */
static ccstructs_dtors_I_methods_t const my_alpha_embedded_dtors_I_methods = {
  .final	= my_alpha_embedded_dtors_method_final,
  .delete	= my_alpha_embedded_dtors_method_delete
};

/* Constructor for the "dtors" interface. */
ccstructs_dtors_I
my_new_alpha_embedded_I_dtors (my_alpha_t const * const self)
{
  return ccstructs_new_dtors(ccstructs_core(self), &my_alpha_embedded_dtors_I_methods);
}


/** --------------------------------------------------------------------
 ** Interface "dtors": standalone struct.
 ** ----------------------------------------------------------------- */

/* This is for struct instances allocated on the heap. */

/* Interface "dtors": "delete()" method. */
static void
my_alpha_standalone_dtors_method_delete (ccstructs_dtors_I I)
{
  CCSTRUCTS_PC(my_alpha_t, self, ccstructs_dtors_self(I));

  my_alpha_release_struct(self);
  if (1) { fprintf(stderr, "%-35s: deleted by dtors\n", __func__); }
}

/* Interface "dtors": "final()" method. */
static void
my_alpha_standalone_dtors_method_final (ccstructs_dtors_I I)
{
  CCSTRUCTS_PC(my_alpha_t, self, ccstructs_dtors_self(I));

  my_final_alpha(self);
  if (1) { fprintf(stderr, "%-35s: finalised by dtors\n", __func__); }
}

/* Methods table for the "dtors" interface. */
static ccstructs_dtors_I_methods_t const my_alpha_standalone_dtors_I_methods = {
  .final	= my_alpha_standalone_dtors_method_final,
  .delete	= my_alpha_standalone_dtors_method_delete
};

/* Constructor for the "dtors" interface. */
ccstructs_dtors_I
my_new_alpha_standalone_I_dtors (my_alpha_t const * const self)
{
  return ccstructs_new_dtors(ccstructs_core(self), &my_alpha_standalone_dtors_I_methods);
}


/** --------------------------------------------------------------------
 ** Printing.
 ** ----------------------------------------------------------------- */

void
my_print_alpha (cce_destination_t L, FILE * stream, my_alpha_t const * const self)
{
  int	rv;

  errno = 0;
  rv = fprintf(stream, "alpha: X=%f, Y=%f, Z=%f\n", self->X, self->Y, self->Z);
  if (rv < 0) {
    cce_raise(L, cce_condition_new_errno_clear());
  }
}


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

/* end of file */
