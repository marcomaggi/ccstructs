/*
  Part of: CCStructs
  Contents: body file for sample struct with no methods table
  Date: Thu Dec 27, 2018

  Abstract

	This  body   file  defines   the  API   to  handle   the  struct
	"my_coords_t" and shows how to implement the main interfaces for
	it.

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


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "dtor-no-methods.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


/** --------------------------------------------------------------------
 ** Constructors and destructors.
 ** ----------------------------------------------------------------- */

void
ccname_init(my_coords_t) (my_coords_t * self, double x, double y, double z)
/* Constructor for embedded instances.   Initialise an already allocated
   struct. */
{
  self->X	= x;
  self->Y	= y;
  self->Z	= z;
}

void
ccname_final(my_coords_t) (my_coords_t const * self CCSTRUCTS_UNUSED)
/* Destructor  for embedded  instances.   Release  all the  asynchronous
   resources  associated to  the  struct instance;  does  not touch  the
   struct itself. */
{
  if (1) { fprintf(stderr, "%-35s: finalised\n", __func__); }
}

/* ------------------------------------------------------------------ */

static my_coords_t *
ccname_alloc(my_coords_t) (cce_destination_t L)
{
  return ccmem_std_malloc(L, sizeof(my_coords_t));
}

static void
ccname_release(my_coords_t) (my_coords_t const * self)
/* Release the memory  block allocated for the struct  instance usin the
   standard memory  allocator implemented  by CCMemory.  Does  not touch
   the struct's fields. */
{
  ccmem_std_free((void *)self);
  if (1) { fprintf(stderr, "%-35s: released\n", __func__); }
}

/* ------------------------------------------------------------------ */

my_coords_t const *
ccname_new(my_coords_t) (cce_destination_t L, double x, double y, double z)
/* Constructor for  standalone instances.   Uses the  standard allocator
   implemented by CCMemory. */
{
  my_coords_t *	self = ccname_alloc(my_coords_t)(L);

  ccname_init(my_coords_t)(self, x, y, z);
  return (my_coords_t const *) self;
}

void
ccname_delete(my_coords_t) (my_coords_t const * self)
/* Destructor for  standalone instances.   Release all  the asynchronous
   resources associated to the struct instance; release the memory block
   allocated for the struct instance. */
{
  ccname_final(my_coords_t)(self);
  ccname_release(my_coords_t)(self);
  if (1) { fprintf(stderr, "%-35s: deleted\n", __func__); }
}


/** --------------------------------------------------------------------
 ** Plain exception handlers.
 ** ----------------------------------------------------------------- */

static void
my_coords_handler_final (cce_condition_t const * C CCSTRUCTS_UNUSED, cce_handler_t * H)
/* Destructor  handler   for  embedded   instances.   Release   all  the
   asynchronous resources  associated to  the struct instance;  does not
   touch the struct itself. */
{
  CCSTRUCTS_PC(my_coords_t, self, H->pointer);

  ccname_final(my_coords_t)(self);
  if (1) { fprintf(stderr, "%-35s: finalised by plain handler\n", __func__); }
}

void
my_coords_register_clean_handler_final (cce_destination_t L, cce_clean_handler_t * H, my_coords_t const * self)
{
  H->handler.function	= my_coords_handler_final;
  H->handler.pointer	= (void *)self;
  cce_register_clean_handler(L, H);
}

void
my_coords_register_error_handler_final (cce_destination_t L, cce_error_handler_t * H, my_coords_t const * self)
{
  H->handler.function	= my_coords_handler_final;
  H->handler.pointer	= (void *)self;
  cce_register_error_handler(L, H);
}

/* ------------------------------------------------------------------ */

static void
my_coords_handler_delete (cce_condition_t const * C CCSTRUCTS_UNUSED, cce_handler_t * H)
/* Destructor  handler  for  standalone   instances.   Release  all  the
   asynchronous resources associated to the struct instance; release the
   memory block  allocated for  the struct  instance using  the standard
   memory allocator implemented by CCMemory.

   To be used to destroy instances dynamically allocated on the heap. */
{
  CCSTRUCTS_PC(my_coords_t, self, H->pointer);

  ccname_delete(my_coords_t)(self);
  if (1) { fprintf(stderr, "%-35s: deleted by plain handler\n", __func__); }
}

void
my_coords_register_clean_handler_delete (cce_destination_t L, cce_clean_handler_t * H, my_coords_t const * self)
{
  H->handler.function	= my_coords_handler_delete;
  H->handler.pointer	= (void *)self;
  cce_register_clean_handler(L, H);
}

void
my_coords_register_error_handler_delete (cce_destination_t L, cce_error_handler_t * H, my_coords_t const * self)
{
  H->handler.function	= my_coords_handler_delete;
  H->handler.pointer	= (void *)self;
  cce_register_error_handler(L, H);
}


/** --------------------------------------------------------------------
 ** Interface "ccstructs_dtor_I": embedded instances.
 ** ----------------------------------------------------------------- */

static void
ccname_iface_method(ccstructs_dtor_I, my_coords_t, embedded, release) (ccstructs_dtor_I I CCSTRUCTS_UNUSED)
{
  if (1) { fprintf(stderr, "%-35s: deleted by dtor\n", __func__); }
}

static void
ccname_iface_method(ccstructs_dtor_I, my_coords_t, embedded, final) (ccstructs_dtor_I I)
{
  CCSTRUCTS_PC(my_coords_t, self, ccstructs_dtor_self(I));

  ccname_final(my_coords_t)(self);
  if (1) { fprintf(stderr, "%-35s: finalised by dtor\n", __func__); }
}

static ccname_iface_table_type(ccstructs_dtor_I) const ccname_iface_table(ccstructs_dtor_I, my_coords_t, embedded) = {
  .final	= ccname_iface_method(ccstructs_dtor_I, my_coords_t, embedded, final),
  .release	= ccname_iface_method(ccstructs_dtor_I, my_coords_t, embedded, release)
};

ccstructs_dtor_I
ccname_iface_new(ccstructs_dtor_I, my_coords_t, embedded) (my_coords_t const * const self)
{
  return ccname_new(ccstructs_dtor_I)(ccstructs_core(self), &ccname_iface_table(ccstructs_dtor_I, my_coords_t, embedded));
}


/** --------------------------------------------------------------------
 ** Interface "ccstructs_dtor_I": standalone instances.
 ** ----------------------------------------------------------------- */

static void
ccname_iface_method(ccstructs_dtor_I, my_coords_t, standalone, release) (ccstructs_dtor_I I)
{
  CCSTRUCTS_PC(my_coords_t, self, ccstructs_dtor_self(I));

  ccname_release(my_coords_t)(self);
  if (1) { fprintf(stderr, "%-35s: deleted by dtor\n", __func__); }
}

static void
ccname_iface_method(ccstructs_dtor_I, my_coords_t, standalone, final) (ccstructs_dtor_I I)
{
  CCSTRUCTS_PC(my_coords_t, self, ccstructs_dtor_self(I));

  ccname_final(my_coords_t)(self);
  if (1) { fprintf(stderr, "%-35s: finalised by dtor\n", __func__); }
}

static ccname_iface_table_type(ccstructs_dtor_I) const ccname_iface_table(ccstructs_dtor_I, my_coords_t, standalone) = {
  .final	= ccname_iface_method(ccstructs_dtor_I, my_coords_t, standalone, final),
  .release	= ccname_iface_method(ccstructs_dtor_I, my_coords_t, standalone, release)
};

ccstructs_dtor_I
ccname_iface_new(ccstructs_dtor_I, my_coords_t, standalone) (my_coords_t const * const self)
{
  return ccname_new(ccstructs_dtor_I)(ccstructs_core(self), &ccname_iface_table(ccstructs_dtor_I, my_coords_t, standalone));
}


/** --------------------------------------------------------------------
 ** Printing.
 ** ----------------------------------------------------------------- */

void
my_print_coords (cce_destination_t L, FILE * stream, my_coords_t const * const self)
{
  int	rv;

  errno = 0;
  rv = fprintf(stream, "coords: X=%f, Y=%f, Z=%f\n", self->X, self->Y, self->Z);
  if (rv < 0) {
    cce_raise(L, cce_condition_new_errno_clear());
  }
}


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

/* end of file */
