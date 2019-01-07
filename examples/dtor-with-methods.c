/*
  Part of: CCStructs
  Contents: body file for sample struct
  Date: Thu Dec 27, 2018

  Abstract

	This  body   file  defines   the  API   to  handle   the  struct
	"my_coords_t" and shows how to implement the main interfaces for
	it.

	The "dtor-with-methods" example shows  how to implement a struct
	using  a   methods  table  for  the   struct-specific  interface
	constructors: every instance of the  struct type holds a pointer
	to a struct implementing a methods table.

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

#include "dtor-with-methods.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


/** --------------------------------------------------------------------
 ** Data struct "my_coords_t": methods table.
 ** ----------------------------------------------------------------- */

/* Type  of interface  constructor  functions.  Functions  of this  type
   build   instances    of   "ccstructs_dtor_I"   as    implemented   by
   "my_coords_t". */
typedef ccstructs_dtor_I ccname_iface_new_type(ccstructs_dtor_I, my_coords_t) (my_coords_t const * self);

/* Function prototype: constructor for "ccstructs_dtor_I" as implemented
   by "my_coords_t".  This variant destroys embedded instances. */
static ccname_iface_new_type(ccstructs_dtor_I, my_coords_t) ccname_iface_new(ccstructs_dtor_I, my_coords_t, embedded);

/* Function prototype: constructor for "ccstructs_dtor_I" as implemented
   by "my_coords_t".  This variant destroys standalone instances. */
static ccname_iface_new_type(ccstructs_dtor_I, my_coords_t) ccname_iface_new(ccstructs_dtor_I, my_coords_t, standalone);

/* Table of methods for "my_coords_t". */
struct ccname_table_type(my_coords_t) {
  ccname_iface_new_type(ccstructs_dtor_I, my_coords_t) *	new_dtor;
};

/* Methods  table  for  "my_coords_t":  this  variant  is  for  embedded
   instances. */
static ccname_table_type(my_coords_t) const ccname_table(my_coords_t, embedded) = {
  .new_dtor	= ccname_iface_new(ccstructs_dtor_I, my_coords_t, embedded)
};

/* Methods  table  for "my_coords_t":  this  variant  is for  standalone
   instances. */
static ccname_table_type(my_coords_t) const ccname_table(my_coords_t, standalone) = {
  .new_dtor	= ccname_iface_new(ccstructs_dtor_I, my_coords_t, standalone)
};


/** --------------------------------------------------------------------
 ** Data struct "my_coords_t": constructors and destructors.
 ** ----------------------------------------------------------------- */

void
ccname_init(my_coords_t) (my_coords_t * self, double x, double y, double z)
{
  self->methods	= &ccname_table(my_coords_t, embedded);
  self->X	= x;
  self->Y	= y;
  self->Z	= z;
}

my_coords_t const *
ccname_new(my_coords_t) (cce_destination_t L, double x, double y, double z)
{
  my_coords_t *	self = ccmem_std_malloc(L, sizeof(my_coords_t));

  ccname_init(my_coords_t)(self, x, y, z);
  self->methods	= &ccname_table(my_coords_t, standalone);
  return (my_coords_t const *) self;
}

static void
ccname_final(my_coords_t) (my_coords_t const * self CCSTRUCTS_UNUSED)
{
  if (1) { fprintf(stderr, "%-35s: finalised\n", __func__); }
}

static void
ccname_release(my_coords_t) (my_coords_t const * self)
{
  ccmem_std_free((void *)self);
  if (1) { fprintf(stderr, "%-35s: released\n", __func__); }
}

void
ccname_delete(my_coords_t) (my_coords_t const * self)
{
  ccname_final(my_coords_t)(self);
  ccname_release(my_coords_t)(self);
  if (1) { fprintf(stderr, "%-35s: delete\n", __func__); }
}


/** --------------------------------------------------------------------
 ** Interface "ccstructs_dtor_I" for "my_coords_t": embedded structs.
 ** ----------------------------------------------------------------- */

static void
ccname_iface_method(ccstructs_dtor_I, my_coords_t, embedded, final) (ccstructs_dtor_I I)
/* Implementation   of   the   method   "final()"   in   the   interface
   "ccstructs_dtor_I"  as implemented  by  "my_coords_t".  This  variant
   finalises embedded structs. */
{
  CCSTRUCTS_PC(my_coords_t, self, ccstructs_dtor_self(I));

  ccname_final(my_coords_t)(self);
  if (1) { fprintf(stderr, "%-35s: finalised by dtor\n", __func__); }
}

static void
ccname_iface_method(ccstructs_dtor_I, my_coords_t, embedded, release) (ccstructs_dtor_I I CCSTRUCTS_UNUSED)
/* Implementation   of  the   method   "release()"   in  the   interface
   "ccstructs_dtor_I" as implemented by  "my_coords_t".  This variant is
   for embedded structs so: it does nothing. */
{
  if (1) { fprintf(stderr, "%-35s: released by dtor\n", __func__); }
}

/* Methods table for the  interface "ccstructs_dtor_I" as implemented by
   "my_coords_t".  This variant is for embedded structs. */
static ccname_iface_table_type(ccstructs_dtor_I) const ccname_iface_table(ccstructs_dtor_I, my_coords_t, embedded) = {
  .final	= ccname_iface_method(ccstructs_dtor_I, my_coords_t, embedded, final),
  .release	= ccname_iface_method(ccstructs_dtor_I, my_coords_t, embedded, release)
};


/** --------------------------------------------------------------------
 ** Interface "ccstructs_dtor_I" for "my_coords_t": standalone structs.
 ** ----------------------------------------------------------------- */

static void
ccname_iface_method(ccstructs_dtor_I, my_coords_t, standalone, final) (ccstructs_dtor_I I)
/* Implementation   of   the   method   "final()"   in   the   interface
   "ccstructs_dtor_I"  as implemented  by  "my_coords_t".  This  variant
   finalises standalone structs. */
{
  CCSTRUCTS_PC(my_coords_t, self, ccstructs_dtor_self(I));

  ccname_final(my_coords_t)(self);
  if (1) { fprintf(stderr, "%-35s: finalised by dtor\n", __func__); }
}

static void
ccname_iface_method(ccstructs_dtor_I, my_coords_t, standalone, release) (ccstructs_dtor_I I)
/* Implementation   of  the   method   "release()"   in  the   interface
   "ccstructs_dtor_I"  as implemented  by  "my_coords_t".  This  variant
   releases standalone structs. */
{
  CCSTRUCTS_PC(my_coords_t, self, ccstructs_dtor_self(I));

  ccname_release(my_coords_t)(self);
  if (1) { fprintf(stderr, "%-35s: released by dtor\n", __func__); }
}

/* Methods table for the  interface "ccstructs_dtor_I" as implemented by
   "my_coords_t".  This variant is for standalone structs. */
static ccname_iface_table_type(ccstructs_dtor_I) const ccname_iface_table(ccstructs_dtor_I, my_coords_t, standalone) = {
  .final	= ccname_iface_method(ccstructs_dtor_I, my_coords_t, standalone, final),
  .release	= ccname_iface_method(ccstructs_dtor_I, my_coords_t, standalone, release)
};


/** --------------------------------------------------------------------
 ** Data struct "my_coords_t": methods implementation.
 ** ----------------------------------------------------------------- */

static ccstructs_dtor_I
ccname_iface_new(ccstructs_dtor_I, my_coords_t, embedded) (my_coords_t const * const self)
/* Implement the method "new_dtor()"  for "my_coords_t": constructor for
   "ccstructs_dtor_I".  This variant destroys embedded structs. */
{
  return ccname_new(ccstructs_dtor_I)(ccstructs_core(self), &ccname_iface_table(ccstructs_dtor_I, my_coords_t, embedded));
}

static ccstructs_dtor_I
ccname_iface_new(ccstructs_dtor_I, my_coords_t, standalone) (my_coords_t const * const self)
/* Implement the  method "new_dtor()" for "my_coords_t":  constructor for
   "ccstructs_dtor_I".  This variant destroys embedded structs. */
{
  return ccname_new(ccstructs_dtor_I)(ccstructs_core(self), &ccname_iface_table(ccstructs_dtor_I, my_coords_t, standalone));
}


/** --------------------------------------------------------------------
 ** Data struct "my_coords_t": constructors of implemented interfaces.
 ** ----------------------------------------------------------------- */

ccstructs_dtor_I
ccname_iface_new(ccstructs_dtor_I, my_coords_t) (my_coords_t const * const self)
/* Interface   constructor   for   "ccstructs_dtor_I"   implemented   by
   "my_coords_t". */
{
  return self->methods->new_dtor(self);
}


/** --------------------------------------------------------------------
 ** Data struct "my_coords_t": printing.
 ** ----------------------------------------------------------------- */

void
my_print_alpha (cce_destination_t L, FILE * stream, my_coords_t const * const self)
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
