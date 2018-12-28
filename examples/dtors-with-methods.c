/*
  Part of: CCStructs
  Contents: body file for sample struct
  Date: Thu Dec 27, 2018

  Abstract

	This body file defines the API to handle the struct "my_alpha_t"
	and shows how to implement the main interfaces for it.

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

#include "dtors-with-methods.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static ccstructs_new_dtors_fun_t my_new_alpha_embedded_I_dtors;
static ccstructs_new_dtors_fun_t my_new_alpha_standalone_I_dtors;


/** --------------------------------------------------------------------
 ** Struct methods table.
 ** ----------------------------------------------------------------- */

struct my_alpha_methods_t {
  ccstructs_new_dtors_fun_t *		new_dtors;
};

static my_alpha_methods_t const my_alpha_methods_embedded_stru = {
  .new_dtors	= my_new_alpha_embedded_I_dtors
};

static my_alpha_methods_t const my_alpha_methods_standalone_stru = {
  .new_dtors	= my_new_alpha_standalone_I_dtors
};


/** --------------------------------------------------------------------
 ** Constructors and destructors.
 ** ----------------------------------------------------------------- */

void
my_init_alpha (my_alpha_t * self, double x, double y, double z)
{
  self->methods	= &my_alpha_methods_embedded_stru;
  self->X	= x;
  self->Y	= y;
  self->Z	= z;
}

my_alpha_t const *
my_new_alpha (cce_destination_t L, double x, double y, double z)
{
  my_alpha_t *	self = ccmem_std_malloc(L, sizeof(my_alpha_t));

  my_init_alpha(self, x, y, z);
  self->methods	= &my_alpha_methods_standalone_stru;
  return (my_alpha_t const *) self;
}

void
my_final_alpha (my_alpha_t const * self CCSTRUCTS_UNUSED)
{
}

static void
my_alpha_release_struct (my_alpha_t const * self)
{
  ccmem_std_free((void *)self);
}

void
my_delete_alpha (my_alpha_t const * self)
{
  my_final_alpha(self);
  my_alpha_release_struct(self);
}


/** --------------------------------------------------------------------
 ** Plain exception handlers.
 ** ----------------------------------------------------------------- */

static void
my_alpha_handler_final (cce_condition_t const * C CCSTRUCTS_UNUSED, cce_handler_t * H)
{
  CCSTRUCTS_PC(my_alpha_t, self, H->pointer);

  my_final_alpha(self);
  if (1) { fprintf(stderr, "%s: finalised\n", __func__); }
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
{
  CCSTRUCTS_PC(my_alpha_t, self, H->pointer);

  my_delete_alpha(self);
  if (1) { fprintf(stderr, "%s: deleted\n", __func__); }
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

/* This is for subject structs allocated  on the stack or embedded in an
   enclosing struct. */

/* Interface "dtors": "delete()" method. */
static void
my_alpha_stack_dtors_method_delete (ccstructs_dtors_I I CCSTRUCTS_UNUSED)
{
}

/* Interface "dtors": "final()" method. */
static void
my_alpha_stack_dtors_method_final (ccstructs_dtors_I I)
{
  CCSTRUCTS_PC(my_alpha_t, self, ccstructs_dtors_self(I));

  my_final_alpha(self);
}

/* Methods table  for the  "dtors" interface. */
static ccstructs_dtors_I_methods_t const my_alpha_stack_dtors_I_methods = {
  .final	= my_alpha_stack_dtors_method_final,
  .delete	= my_alpha_stack_dtors_method_delete
};

/* Constructor for the "dtors" interface. */
static ccstructs_dtors_I
my_new_alpha_embedded_I_dtors (ccstructs_core_t const * const self)
{
  return ccstructs_new_dtors(self, &my_alpha_stack_dtors_I_methods);
}


/** --------------------------------------------------------------------
 ** Interface "dtors": standalone struct.
 ** ----------------------------------------------------------------- */

/* This is for subject structs allocated on the heap. */

/* Interface "dtors": "delete()" method. */
static void
my_alpha_heap_dtors_method_delete (ccstructs_dtors_I I)
{
  CCSTRUCTS_PC(my_alpha_t, self, ccstructs_dtors_self(I));

  my_alpha_release_struct(self);
}

/* Interface "dtors": "final()" method. */
static void
my_alpha_heap_dtors_method_final (ccstructs_dtors_I I)
{
  CCSTRUCTS_PC(my_alpha_t, self, ccstructs_dtors_self(I));

  my_final_alpha(self);
}

/* Methods table for the "dtors" interface. */
static ccstructs_dtors_I_methods_t const my_alpha_heap_dtors_I_methods = {
  .final	= my_alpha_heap_dtors_method_final,
  .delete	= my_alpha_heap_dtors_method_delete
};

/* Constructor for the "dtors" interface. */
static ccstructs_dtors_I
my_new_alpha_standalone_I_dtors (ccstructs_core_t const * const self)
{
  return ccstructs_new_dtors(self, &my_alpha_heap_dtors_I_methods);
}


/** --------------------------------------------------------------------
 ** Interface "dtors": constructors.
 ** ----------------------------------------------------------------- */

ccstructs_dtors_I
my_alpha_new_dtors (my_alpha_t const * const self)
{
  return self->methods->new_dtors(ccstructs_core(self));
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