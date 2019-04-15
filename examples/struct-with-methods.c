/*
  Part of: CCStructs
  Contents: body file for sample struct
  Date: Thu Dec 27, 2018

  Abstract

	This body file  defines the API to handle the  struct "my_coords_t" and shows
	how to implement the main traits for it.

	The "struct-with-methods"  example shows  how to implement  a struct  using a
	methods table for  the struct-specific trait constructors:  every instance of
	the struct type holds a pointer to a struct implementing a methods table.

  Copyright (C) 2018, 2019 Marco Maggi <marco.maggi-ipsu@poste.it>

  The author  hereby grant permission to  use, copy, modify, distribute,  and license
  this  software  and its  documentation  for  any  purpose, provided  that  existing
  copyright  notices are  retained in  all copies  and that  this notice  is included
  verbatim in  any distributions. No  written agreement,  license, or royalty  fee is
  required for  any of the  authorized uses.  Modifications  to this software  may be
  copyrighted by  their authors  and need  not follow  the licensing  terms described
  here, provided that the  new terms are clearly indicated on the  first page of each
  file where they apply.

  IN NO  EVENT SHALL THE AUTHOR  OR DISTRIBUTORS BE  LIABLE TO ANY PARTY  FOR DIRECT,
  INDIRECT, SPECIAL, INCIDENTAL,  OR CONSEQUENTIAL DAMAGES ARISING OUT OF  THE USE OF
  THIS SOFTWARE,  ITS DOCUMENTATION, OR ANY  DERIVATIVES THEREOF, EVEN IF  THE AUTHOR
  HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  THE AUTHOR  AND DISTRIBUTORS SPECIFICALLY  DISCLAIM ANY WARRANTIES,  INCLUDING, BUT
  NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
  PURPOSE, AND NON-INFRINGEMENT.  THIS SOFTWARE IS  PROVIDED ON AN "AS IS" BASIS, AND
  THE AUTHOR  AND DISTRIBUTORS  HAVE NO OBLIGATION  TO PROVIDE  MAINTENANCE, SUPPORT,
  UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
*/


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "struct-with-methods.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>


/** --------------------------------------------------------------------
 ** Type definitions.
 ** ----------------------------------------------------------------- */

typedef struct serialised_my_coords_t	serialised_my_coords_t;

/* The layout of a serialised "my_coords_t". */
struct serialised_my_coords_t {
  double	X;
  double	Y;
};


/** --------------------------------------------------------------------
 ** Data struct "my_coords_t": methods table.
 ** ----------------------------------------------------------------- */

/* Type of trait  constructor functions.  Functions of this  type build instances
   of "ccstructs_dtor_T" as implemented by "my_coords_t". */
typedef ccstructs_dtor_T ccname_trait_new_type(ccstructs_dtor_T, my_coords_t) (my_coords_t const * self);

/* Function  prototype:   constructor  for   "ccstructs_dtor_T"  as   implemented  by
   "my_coords_t".  This variant destroys embedded instances. */
static ccname_trait_new_type(ccstructs_dtor_T, my_coords_t) ccname_trait_new(ccstructs_dtor_T, my_coords_t, embedded);

/* Function  prototype:   constructor  for   "ccstructs_dtor_T"  as   implemented  by
   "my_coords_t".  This variant destroys standalone instances. */
static ccname_trait_new_type(ccstructs_dtor_T, my_coords_t) ccname_trait_new(ccstructs_dtor_T, my_coords_t, standalone);

/* Table of methods for "my_coords_t". */
struct ccname_table_type(my_coords_t) {
  ccname_trait_new_type(ccstructs_dtor_T, my_coords_t) *	new_dtor;
};

/* Methods table for "my_coords_t": this variant is for embedded instances. */
static ccname_table_type(my_coords_t) const ccname_table(my_coords_t, embedded) = {
  .new_dtor	= ccname_trait_new(ccstructs_dtor_T, my_coords_t, embedded)
};

/* Methods table for "my_coords_t": this variant is for standalone instances. */
static ccname_table_type(my_coords_t) const ccname_table(my_coords_t, standalone) = {
  .new_dtor	= ccname_trait_new(ccstructs_dtor_T, my_coords_t, standalone)
};


/** --------------------------------------------------------------------
 ** Data struct "my_coords_t": well known API functions.
 ** ----------------------------------------------------------------- */

void
ccname_init(my_coords_t, rec) (my_coords_t * S, double X, double Y)
{
  S->methods	= &ccname_table(my_coords_t, embedded);
  S->X		= X;
  S->Y		= Y;
}

void
ccname_init(my_coords_t, pol) (my_coords_t * S, double RHO, double THETA)
{
  S->methods	= &ccname_table(my_coords_t, embedded);
  S->X		= RHO * cos(THETA);
  S->Y		= RHO * sin(THETA);
}

void
ccname_init(my_coords_t, deserialisable) (my_coords_t * S)
{
  S->methods	= &ccname_table(my_coords_t, embedded);
  S->X = 0.0;
  S->Y = 0.0;
}

/* ------------------------------------------------------------------ */

static void
ccname_final(my_coords_t) (my_coords_t const * S CCSTRUCTS_UNUSED)
{
  if (1) { fprintf(stderr, "%-35s: finalised\n", __func__); }
}

/* ------------------------------------------------------------------ */

static my_coords_t *
ccname_alloc(my_coords_t) (cce_destination_t L)
{
  return (my_coords_t *)ccmem_std_malloc(L, sizeof(my_coords_t));
}

/* ------------------------------------------------------------------ */

static void
ccname_release(my_coords_t) (my_coords_t const * S)
{
  ccmem_std_free((void *)S);
  if (1) { fprintf(stderr, "%-35s: released\n", __func__); }
}

/* ------------------------------------------------------------------ */

my_coords_t const *
ccname_new(my_coords_t, rec) (cce_destination_t L, double X, double Y)
{
  my_coords_t *	S = ccname_alloc(my_coords_t)(L);

  ccname_init(my_coords_t, rec)(S, X, Y);
  S->methods	= &ccname_table(my_coords_t, standalone);
  return (my_coords_t const *) S;
}

my_coords_t const *
ccname_new(my_coords_t, pol) (cce_destination_t L, double RHO, double THETA)
{
  my_coords_t *	S = ccname_alloc(my_coords_t)(L);

  ccname_init(my_coords_t, pol)(S, RHO, THETA);
  S->methods	= &ccname_table(my_coords_t, standalone);
  return (my_coords_t const *) S;
}

my_coords_t *
ccname_new(my_coords_t, deserialisable) (cce_destination_t L)
{
  my_coords_t *	S = ccname_alloc(my_coords_t)(L);

  ccname_init(my_coords_t, deserialisable)(S);
  S->methods	= &ccname_table(my_coords_t, standalone);
  return S;
}

/* ------------------------------------------------------------------ */

void
ccname_delete(my_coords_t) (my_coords_t const * S)
{
  ccname_final(my_coords_t)(S);
  ccname_release(my_coords_t)(S);
  if (1) { fprintf(stderr, "%-35s: delete\n", __func__); }
}


/** --------------------------------------------------------------------
 ** Trait "ccstructs_dtor_T": implementation for embedded "my_coords_t".
 ** ----------------------------------------------------------------- */

static ccstructs_core_destructor_fun_t	my_coords_embedded_destructor;

ccstructs_dtor_T
ccname_trait_new(ccstructs_dtor_T, my_coords_t, embedded) (my_coords_t const * const self)
{
  return ccname_new(ccstructs_dtor_T)(ccstructs_core(self), my_coords_embedded_destructor);
}

/* ------------------------------------------------------------------ */

void
my_coords_embedded_destructor (ccstructs_core_t * S)
{
  CCSTRUCTS_PC(my_coords_t, self, S);

  ccname_final(my_coords_t)(self);
  if (1) { fprintf(stderr, "%-35s: finalised by dtor\n", __func__); }
}


/** --------------------------------------------------------------------
 ** Trait "ccstructs_dtor_T": implementation for standalone "my_coords_t".
 ** ----------------------------------------------------------------- */

static ccstructs_core_destructor_fun_t	my_coords_standalone_destructor;

ccstructs_dtor_T
ccname_trait_new(ccstructs_dtor_T, my_coords_t, standalone) (my_coords_t const * const self)
{
  return ccname_new(ccstructs_dtor_T)(ccstructs_core(self), my_coords_standalone_destructor);
}

/* ------------------------------------------------------------------ */

void
my_coords_standalone_destructor (ccstructs_core_t * S)
{
  CCSTRUCTS_PC(my_coords_t, self, S);

  ccname_delete(my_coords_t)(self);
  if (1) { fprintf(stderr, "%-35s: deleted by dtor\n", __func__); }
}


/** --------------------------------------------------------------------
 ** Trait "ccstructs_dtor_T": public constructor for "my_coords_t".
 ** ----------------------------------------------------------------- */

ccstructs_dtor_T
ccname_trait_new(ccstructs_dtor_T, my_coords_t) (my_coords_t const * const self)
/* Trait constructor for "ccstructs_dtor_T" implemented by "my_coords_t". */
{
  return self->methods->new_dtor(self);
}


/** --------------------------------------------------------------------
 ** Trait "ccstructs_dumpable_T": implementation for "my_coords_t".
 ** ----------------------------------------------------------------- */

static ccname_trait_method_type(ccstructs_dumpable_T, dump)  ccname_trait_method(ccstructs_dumpable_T, my_coords_t, dump);

static ccname_trait_table_type(ccstructs_dumpable_T) const ccname_trait_table(ccstructs_dumpable_T, my_coords_t) = {
  .dump	= ccname_trait_method(ccstructs_dumpable_T, my_coords_t, dump)
};

ccstructs_dumpable_T
ccname_trait_new(ccstructs_dumpable_T, my_coords_t) (my_coords_t const * S)
{
  return ccname_new(ccstructs_dumpable_T)(ccstructs_core(S), &ccname_trait_table(ccstructs_dumpable_T, my_coords_t));
}

void
ccname_trait_method(ccstructs_dumpable_T, my_coords_t, dump) (cce_destination_t L, ccstructs_dumpable_T I)
{
  CCSTRUCTS_PC(my_coords_t, S, ccstructs_dumpable_self(I));
  int	rv;

  errno = 0;
  rv = fprintf(stderr, "X=%f, Y=%f\n", S->X, S->Y);
  if (rv < 0) {
    cce_raise(L, cce_condition_new_errno_clear());
  }
}


/** --------------------------------------------------------------------
 ** Trait "ccstructs_serialiser_T": implementation for "my_coords_t".
 ** ----------------------------------------------------------------- */

static ccname_trait_method_type(ccstructs_serialiser_T, required_size)
  ccname_trait_method(ccstructs_serialiser_T, my_coords_t, required_size);
static ccname_trait_method_type(ccstructs_serialiser_T, write)
  ccname_trait_method(ccstructs_serialiser_T, my_coords_t, write);

/* Trait  table  of  methods.    Implementation  of  "ccstructs_serialiser_T"  for
   "my_coords_t". */
static ccname_trait_table_type(ccstructs_serialiser_T) const ccname_trait_table(ccstructs_serialiser_T, my_coords_t) = {
  .required_size = ccname_trait_method(ccstructs_serialiser_T, my_coords_t, required_size),
  .write         = ccname_trait_method(ccstructs_serialiser_T, my_coords_t, write),
};

ccstructs_serialiser_T
ccname_trait_new(ccstructs_serialiser_T, my_coords_t) (my_coords_t const * S)
/* Trait   constructor.   Build   an  instance   of  "ccstructs_serialiser_T"   as
   implemented by "my_coords_t". */
{
  return ccname_new(ccstructs_serialiser_T)(ccstructs_core(S), &ccname_trait_table(ccstructs_serialiser_T, my_coords_t));
}

/* ------------------------------------------------------------------ */

size_t
ccname_trait_method(ccstructs_serialiser_T, my_coords_t, required_size) (ccstructs_serialiser_T I CCSTRUCTS_UNUSED)
/* Return the minimum number of bytes  required to hold the serialised representation
   of "my_coords_t".*/
{
  return sizeof(serialised_my_coords_t);
}

ccmem_block_t
ccname_trait_method(ccstructs_serialiser_T, my_coords_t,
		    write) (cce_destination_t L CCSTRUCTS_UNUSED, ccstructs_serialiser_T I, ccmem_block_t B)
/* Trait  method implementation.   Serialise an  instance of  "my_coords_t" in  the
   memory block "B". */
{
  CCSTRUCTS_PC(my_coords_t const, S, ccstructs_serialiser_self(I));
  CCSTRUCTS_PC(serialised_my_coords_t, W, B.ptr);
  ccmem_block_t	N = {
    .ptr	= B.ptr + sizeof(serialised_my_coords_t),
    .len	= B.len - sizeof(serialised_my_coords_t)
  };

  W->X	= S->X;
  W->Y	= S->Y;
  return N;
}


/** --------------------------------------------------------------------
 ** Trait "ccstructs_deserialiser_T": implementation for "my_coords_t".
 ** ----------------------------------------------------------------- */

static ccname_trait_method_type(ccstructs_deserialiser_T, required_size)
  ccname_trait_method(ccstructs_deserialiser_T, my_coords_t, required_size);
static ccname_trait_method_type(ccstructs_deserialiser_T, read)
  ccname_trait_method(ccstructs_deserialiser_T, my_coords_t, read);

/* Trait  table  of  methods.  Implementation  of  "ccstructs_deserialiser_T"  for
   "my_coords_t". */
static ccname_trait_table_type(ccstructs_deserialiser_T) const ccname_trait_table(ccstructs_deserialiser_T, my_coords_t) = {
  .required_size = ccname_trait_method(ccstructs_deserialiser_T, my_coords_t, required_size),
  .read          = ccname_trait_method(ccstructs_deserialiser_T, my_coords_t, read)
};

ccstructs_deserialiser_T
ccname_trait_new(ccstructs_deserialiser_T, my_coords_t) (my_coords_t * S)
/* Trait  constructor.    Build  an  instance  of   "ccstructs_deserialiser_T"  as
   implemented by "my_coords_t". */
{
  return ccname_new(ccstructs_deserialiser_T)(ccstructs_core(S), &ccname_trait_table(ccstructs_deserialiser_T, my_coords_t));
}

/* ------------------------------------------------------------------ */

size_t
ccname_trait_method(ccstructs_deserialiser_T, my_coords_t, required_size) (ccstructs_deserialiser_T I CCSTRUCTS_UNUSED)
/* Return the minimum number of bytes  required to hold the serialised representation
   of "my_coords_t".*/
{
  return sizeof(serialised_my_coords_t);
}

ccmem_block_t
ccname_trait_method(ccstructs_deserialiser_T, my_coords_t,
		    read) (cce_destination_t L CCSTRUCTS_UNUSED, ccstructs_deserialiser_T I, ccmem_block_t B)
/* Trait method implementation.  Dedeserialise  an instance of "my_coords_t" from
   the memory block "B". */
{
  CCSTRUCTS_PC(my_coords_t, S, ccstructs_deserialiser_self(I));
  CCSTRUCTS_PC(serialised_my_coords_t const, W, B.ptr);
  ccmem_block_t	N = {
    .ptr	= B.ptr + sizeof(serialised_my_coords_t),
    .len	= B.len - sizeof(serialised_my_coords_t)
  };

  S->X	= W->X;
  S->Y	= W->Y;
  return N;
}


/** --------------------------------------------------------------------
 ** Trait "my_printable_T": implementation for "my_coords_t".
 ** ----------------------------------------------------------------- */

static void my_printable_fprintf (cce_destination_t L, FILE * stream, char const * format, ...)
  __attribute__((__format__(printf,3,4)));

static ccname_trait_method_type(my_printable_T, print)  ccname_trait_method(my_printable_T, my_coords_t, print_rec);
static ccname_trait_method_type(my_printable_T, print)  ccname_trait_method(my_printable_T, my_coords_t, print_pol);

static ccname_trait_table_type(my_printable_T) const ccname_trait_table(my_printable_T, my_coords_t) = {
  .print_rec	= ccname_trait_method(my_printable_T, my_coords_t, print_rec),
  .print_pol	= ccname_trait_method(my_printable_T, my_coords_t, print_pol)
};

my_printable_T
ccname_trait_new(my_printable_T, my_coords_t) (my_coords_t const * S)
{
  return ccname_new(my_printable_T)(ccstructs_core(S), &ccname_trait_table(my_printable_T, my_coords_t));
}

void
my_printable_fprintf (cce_destination_t L, FILE * stream, char const * format, ...)
{
  va_list	ap;
  int		rv;

  va_start(ap, format);
  {
    errno = 0;
    rv = vfprintf(stream, format, ap);
  }
  va_end(ap);
  if (rv < 0) {
    cce_raise(L, cce_condition_new_errno_clear());
  }
}

void
ccname_trait_method(my_printable_T, my_coords_t, print_rec) (cce_destination_t L, my_printable_T I, FILE * stream)
{
  CCSTRUCTS_PC(my_coords_t, S, my_printable_self(I));

  my_printable_fprintf(L, stream, "X=%f, Y=%f\n", S->X, S->Y);
}

void
ccname_trait_method(my_printable_T, my_coords_t, print_pol) (cce_destination_t L, my_printable_T I, FILE * stream)
{
  CCSTRUCTS_PC(my_coords_t, S, my_printable_self(I));
  double	RHO   = hypot(S->X, S->Y);
  double	THETA = atan2(S->Y, S->X);

  my_printable_fprintf(L, stream, "RHO=%f, THETA=%f\n", RHO, THETA);
}


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

/* end of file */
