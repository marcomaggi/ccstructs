/*
  Part of: CCStructs
  Contents: body file for sample struct
  Date: Thu Dec 27, 2018

  Abstract

	This body file defines the API to handle the struct "my_alpha_t"
	and shows how to implement the main interfaces for it.

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


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "dtor-with-methods-and-names.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static ccstructs_new_dtor_fun_t ccname_iface_new(ccstructs_dtor_I, my_alpha_t, embedded);
static ccstructs_new_dtor_fun_t ccname_iface_new(ccstructs_dtor_I, my_alpha_t, standalone);

static void ccname_final(my_alpha_t) (my_alpha_t const * self)
  __attribute__((__nonnull__(1)));

static void ccname_release(my_alpha_t) (my_alpha_t const * self)
  __attribute__((__nonnull__(1)));


/** --------------------------------------------------------------------
 ** Struct methods table.
 ** ----------------------------------------------------------------- */

struct ccname_table_type(my_alpha_t) {
  ccstructs_new_dtor_fun_t *		new_dtor;
};

static ccname_table_type(my_alpha_t) const ccname_table(my_alpha_t, embedded) = {
  .new_dtor	= ccname_iface_new(ccstructs_dtor_I, my_alpha_t, embedded)
};

static ccname_table_type(my_alpha_t) const ccname_table(my_alpha_t, standalone) = {
  .new_dtor	= ccname_iface_new(ccstructs_dtor_I, my_alpha_t, standalone)
};


/** --------------------------------------------------------------------
 ** Constructors and destructors.
 ** ----------------------------------------------------------------- */

void
ccname_init(my_alpha_t) (my_alpha_t * self, double x, double y, double z)
{
  self->methods	= &ccname_table(my_alpha_t, embedded);
  self->X	= x;
  self->Y	= y;
  self->Z	= z;
}

my_alpha_t const *
ccname_new(my_alpha_t) (cce_destination_t L, double x, double y, double z)
{
  my_alpha_t *	self = ccmem_std_malloc(L, sizeof(my_alpha_t));

  ccname_init(my_alpha_t)(self, x, y, z);
  self->methods	= &ccname_table(my_alpha_t, standalone);
  return (my_alpha_t const *) self;
}

static void
ccname_final(my_alpha_t) (my_alpha_t const * self CCSTRUCTS_UNUSED)
{
  if (1) { fprintf(stderr, "%-35s: finalised\n", __func__); }
}

static void
ccname_release(my_alpha_t) (my_alpha_t const * self)
{
  ccmem_std_free((void *)self);
  if (1) { fprintf(stderr, "%-35s: released\n", __func__); }
}

void
ccname_delete(my_alpha_t) (my_alpha_t const * self)
{
  ccname_final(my_alpha_t)(self);
  ccname_release(my_alpha_t)(self);
  if (1) { fprintf(stderr, "%-35s: delete\n", __func__); }
}


/** --------------------------------------------------------------------
 ** Interface "dtor": embedded struct.
 ** ----------------------------------------------------------------- */

/* This is for struct instances allocated on the stack or embedded in an
   enclosing struct. */

/* Interface "dtor": "final()" method. */
static void
ccname_iface_method(ccstructs_dtor_I, my_alpha_t, embedded, final) (ccstructs_dtor_I I)
{
  CCSTRUCTS_PC(my_alpha_t, self, ccstructs_dtor_self(I));

  ccname_final(my_alpha_t)(self);
  if (1) { fprintf(stderr, "%-35s: finalised by dtor\n", __func__); }
}

/* Interface "dtor": "delete()" method. */
static void
ccname_iface_method(ccstructs_dtor_I, my_alpha_t, embedded, delete) (ccstructs_dtor_I I CCSTRUCTS_UNUSED)
{
  if (1) { fprintf(stderr, "%-35s: deleted by dtor\n", __func__); }
}

/* Methods table  for the  "dtor" interface. */
static ccstructs_dtor_I_methods_t const ccname_iface_table(ccstructs_dtor_I, my_alpha_t, embedded) = {
  .final	= ccname_iface_method(ccstructs_dtor_I, my_alpha_t, embedded, final),
  .delete	= ccname_iface_method(ccstructs_dtor_I, my_alpha_t, embedded, delete)
};

/* Constructor for the "dtor" interface. */
static ccstructs_dtor_I
ccname_iface_new(ccstructs_dtor_I, my_alpha_t, embedded) (ccstructs_core_t const * const self)
{
  return ccstructs_new_dtor(self, &ccname_iface_table(ccstructs_dtor_I, my_alpha_t, embedded));
}


/** --------------------------------------------------------------------
 ** Interface "dtor": standalone struct.
 ** ----------------------------------------------------------------- */

/* This is for struct instances allocated on the heap. */

/* Interface "dtor": "final()" method. */
static void
ccname_iface_method(ccstructs_dtor_I, my_alpha_t, standalone, final) (ccstructs_dtor_I I)
{
  CCSTRUCTS_PC(my_alpha_t, self, ccstructs_dtor_self(I));

  ccname_final(my_alpha_t)(self);
  if (1) { fprintf(stderr, "%-35s: finalised by dtor\n", __func__); }
}

/* Interface "dtor": "delete()" method. */
static void
ccname_iface_method(ccstructs_dtor_I, my_alpha_t, standalone, delete) (ccstructs_dtor_I I)
{
  CCSTRUCTS_PC(my_alpha_t, self, ccstructs_dtor_self(I));

  ccname_release(my_alpha_t)(self);
  if (1) { fprintf(stderr, "%-35s: deleted by dtor\n", __func__); }
}

/* Methods table for the "dtor" interface. */
static ccstructs_dtor_I_methods_t const ccname_iface_table(ccstructs_dtor_I, my_alpha_t, standalone) = {
  .final	= ccname_iface_method(ccstructs_dtor_I, my_alpha_t, standalone, final),
  .delete	= ccname_iface_method(ccstructs_dtor_I, my_alpha_t, standalone, delete)
};

/* Constructor for the "dtor" interface. */
static ccstructs_dtor_I
ccname_iface_new(ccstructs_dtor_I, my_alpha_t, standalone) (ccstructs_core_t const * const self)
{
  return ccstructs_new_dtor(self, &ccname_iface_table(ccstructs_dtor_I, my_alpha_t, standalone));
}


/** --------------------------------------------------------------------
 ** Interface "dtor": constructors.
 ** ----------------------------------------------------------------- */

/* Interface  constructor function.   Return a  new instance  of "dtor"
   interface which destroys the struct instance. */
ccstructs_dtor_I
ccname_iface_new(ccstructs_dtor_I, my_alpha_t) (my_alpha_t const * const self)
{
  return self->methods->new_dtor(ccstructs_core(self));
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
