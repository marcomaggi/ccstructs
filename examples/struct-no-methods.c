/*
  Part of: CCStructs
  Contents: demo program for CCNames
  Date: Jan  4, 2019

  Abstract

	This  body   file  implements  functions   and  interfaces  for   the  struct
	"my_coords_t".  "my_coords_t"  is a  simple struct  with embedded  fields, no
	pointers to external memory blocks.

	The  "struct-no-methods" example  shows how  to implement  a struct  using no
	methods table for the struct-specific interface constructors.

  Copyright (C) 2019 Marco Maggi <marco.maggi-ipsu@poste.it>

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

#include "struct-no-methods.h"
#include <errno.h>
#include <math.h>
#include <stdarg.h>


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
 ** Data struct "my_coords_t": well known functions.
 ** ----------------------------------------------------------------- */

void
ccname_init(my_coords_t, rec) (my_coords_t * S, double X, double Y)
{
  S->X = X;
  S->Y = Y;
}

void
ccname_init(my_coords_t, pol) (my_coords_t * S, double RHO, double THETA)
{
  S->X = RHO * cos(THETA);
  S->Y = RHO * sin(THETA);
}

void
ccname_init(my_coords_t, deserialisable) (my_coords_t * S)
{
  S->X = 0.0;
  S->Y = 0.0;
}

/* ------------------------------------------------------------------ */

void
ccname_final(my_coords_t) (my_coords_t const * S CCNAMES_UNUSED)
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
  my_coords_t * S = ccname_alloc(my_coords_t)(L);

  ccname_init(my_coords_t, rec)(S, X, Y);
  return S;
}

my_coords_t const *
ccname_new(my_coords_t, pol) (cce_destination_t L, double RHO, double THETA)
{
  my_coords_t * S = ccname_alloc(my_coords_t)(L);

  ccname_init(my_coords_t, pol)(S, RHO, THETA);
  return S;
}

my_coords_t *
ccname_new(my_coords_t, deserialisable) (cce_destination_t L)
{
  my_coords_t * S = ccname_alloc(my_coords_t)(L);

  ccname_init(my_coords_t, deserialisable)(S);
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
 ** Plain exception handlers.
 ** ----------------------------------------------------------------- */

static void
my_coords_handler_final (cce_condition_t const * C CCSTRUCTS_UNUSED, cce_handler_t * H)
/* Destructor handler for embedded instances.  Release all the asynchronous resources
   associated to the struct instance; does not touch the struct itself. */
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
/* Destructor  handler  for  standalone  instances.   Release  all  the  asynchronous
   resources associated  to the struct  instance; release the memory  block allocated
   for  the  struct instance  using  the  standard  memory allocator  implemented  by
   CCMemory.

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
 ** Interface "ccstructs_dtor_I": implementation for embedded "my_coords_t".
 ** ----------------------------------------------------------------- */

static ccname_iface_method_type(ccstructs_dtor_I, release) ccname_iface_method(ccstructs_dtor_I, my_coords_t, embedded, release);
static ccname_iface_method_type(ccstructs_dtor_I, final)   ccname_iface_method(ccstructs_dtor_I, my_coords_t, embedded, final);

static ccname_iface_table_type(ccstructs_dtor_I) const ccname_iface_table(ccstructs_dtor_I, my_coords_t, embedded) = {
  .final	= ccname_iface_method(ccstructs_dtor_I, my_coords_t, embedded, final),
  .release	= ccname_iface_method(ccstructs_dtor_I, my_coords_t, embedded, release)
};

ccstructs_dtor_I
ccname_iface_new(ccstructs_dtor_I, my_coords_t, embedded) (my_coords_t const * const self)
{
  return ccname_new(ccstructs_dtor_I)(ccstructs_core(self), &ccname_iface_table(ccstructs_dtor_I, my_coords_t, embedded));
}

/* ------------------------------------------------------------------ */

void
ccname_iface_method(ccstructs_dtor_I, my_coords_t, embedded, release) (ccstructs_dtor_I I CCSTRUCTS_UNUSED)
{
  if (1) { fprintf(stderr, "%-35s: deleted by dtor\n", __func__); }
}

void
ccname_iface_method(ccstructs_dtor_I, my_coords_t, embedded, final) (ccstructs_dtor_I I)
{
  CCSTRUCTS_PC(my_coords_t, self, ccstructs_dtor_self(I));

  ccname_final(my_coords_t)(self);
  if (1) { fprintf(stderr, "%-35s: finalised by dtor\n", __func__); }
}


/** --------------------------------------------------------------------
 ** Interface "ccstructs_dtor_I": implementation for standalone "my_coords_t".
 ** ----------------------------------------------------------------- */

static ccname_iface_method_type(ccstructs_dtor_I, release) ccname_iface_method(ccstructs_dtor_I, my_coords_t, standalone, release);
static ccname_iface_method_type(ccstructs_dtor_I, final)   ccname_iface_method(ccstructs_dtor_I, my_coords_t, standalone, final);

static ccname_iface_table_type(ccstructs_dtor_I) const ccname_iface_table(ccstructs_dtor_I, my_coords_t, standalone) = {
  .final	= ccname_iface_method(ccstructs_dtor_I, my_coords_t, standalone, final),
  .release	= ccname_iface_method(ccstructs_dtor_I, my_coords_t, standalone, release)
};

ccstructs_dtor_I
ccname_iface_new(ccstructs_dtor_I, my_coords_t, standalone) (my_coords_t const * const self)
{
  return ccname_new(ccstructs_dtor_I)(ccstructs_core(self), &ccname_iface_table(ccstructs_dtor_I, my_coords_t, standalone));
}

/* ------------------------------------------------------------------ */

void
ccname_iface_method(ccstructs_dtor_I, my_coords_t, standalone, release) (ccstructs_dtor_I I)
{
  CCSTRUCTS_PC(my_coords_t, self, ccstructs_dtor_self(I));

  ccname_release(my_coords_t)(self);
  if (1) { fprintf(stderr, "%-35s: deleted by dtor\n", __func__); }
}

void
ccname_iface_method(ccstructs_dtor_I, my_coords_t, standalone, final) (ccstructs_dtor_I I)
{
  CCSTRUCTS_PC(my_coords_t, self, ccstructs_dtor_self(I));

  ccname_final(my_coords_t)(self);
  if (1) { fprintf(stderr, "%-35s: finalised by dtor\n", __func__); }
}


/** --------------------------------------------------------------------
 ** Interface "ccstructs_dumpable_I": implementation for "my_coords_t".
 ** ----------------------------------------------------------------- */

static ccname_iface_method_type(ccstructs_dumpable_I, dump)  ccname_iface_method(ccstructs_dumpable_I, my_coords_t, dump);

static ccname_iface_table_type(ccstructs_dumpable_I) const ccname_iface_table(ccstructs_dumpable_I, my_coords_t) = {
  .dump	= ccname_iface_method(ccstructs_dumpable_I, my_coords_t, dump)
};

ccstructs_dumpable_I
ccname_iface_new(ccstructs_dumpable_I, my_coords_t) (my_coords_t const * S)
{
  return ccname_new(ccstructs_dumpable_I)(ccstructs_core(S), &ccname_iface_table(ccstructs_dumpable_I, my_coords_t));
}

void
ccname_iface_method(ccstructs_dumpable_I, my_coords_t, dump) (cce_destination_t L, ccstructs_dumpable_I I)
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
 ** Interface "my_serialise_I": implementation for "my_coords_t".
 ** ----------------------------------------------------------------- */

static ccname_iface_method_type(ccstructs_serialise_I, required_size) ccname_iface_method(ccstructs_serialise_I, my_coords_t, required_size);
static ccname_iface_method_type(ccstructs_serialise_I, write)         ccname_iface_method(ccstructs_serialise_I, my_coords_t, write);

/* Interface  table  of  methods.    Implementation  of  "ccstructs_serialise_I"  for
   "my_coords_t". */
static ccname_iface_table_type(ccstructs_serialise_I) const ccname_iface_table(ccstructs_serialise_I, my_coords_t) = {
  .required_size = ccname_iface_method(ccstructs_serialise_I, my_coords_t, required_size),
  .write         = ccname_iface_method(ccstructs_serialise_I, my_coords_t, write),
};

ccstructs_serialise_I
ccname_iface_new(ccstructs_serialise_I, my_coords_t) (my_coords_t const * S)
/* Interface   constructor.   Build   an  instance   of  "ccstructs_serialise_I"   as
   implemented by "my_coords_t". */
{
  return ccname_new(ccstructs_serialise_I)(ccstructs_core(S), &ccname_iface_table(ccstructs_serialise_I, my_coords_t));
}

/* ------------------------------------------------------------------ */

size_t
ccname_iface_method(ccstructs_serialise_I, my_coords_t, required_size) (ccstructs_serialise_I I CCSTRUCTS_UNUSED)
/* Return the minimum number of */
{
  return sizeof(serialised_my_coords_t);
}

ccmem_block_t
ccname_iface_method(ccstructs_serialise_I, my_coords_t,
		    write) (cce_destination_t L CCSTRUCTS_UNUSED, ccstructs_serialise_I I, ccmem_block_t B)
/* Interface  method implementation.   Serialise an  instance of  "my_coords_t" in  the
   memory block "B". */
{
  CCSTRUCTS_PC(my_coords_t const, S, ccstructs_serialise_self(I));
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
 ** Interface "my_deserialise_I": implementation for "my_coords_t".
 ** ----------------------------------------------------------------- */

static ccname_iface_method_type(ccstructs_deserialise_I, read) ccname_iface_method(ccstructs_deserialise_I, my_coords_t, read);

/* Interface  table  of  methods.  Implementation  of  "ccstructs_deserialise_I"  for
   "my_coords_t". */
static ccname_iface_table_type(ccstructs_deserialise_I) const ccname_iface_table(ccstructs_deserialise_I, my_coords_t) = {
  .read          = ccname_iface_method(ccstructs_deserialise_I, my_coords_t, read)
};

ccstructs_deserialise_I
ccname_iface_new(ccstructs_deserialise_I, my_coords_t) (my_coords_t * S)
/* Interface  constructor.    Build  an  instance  of   "ccstructs_deserialise_I"  as
   implemented by "my_coords_t". */
{
  return ccname_new(ccstructs_deserialise_I)(ccstructs_core(S), &ccname_iface_table(ccstructs_deserialise_I, my_coords_t));
}

/* ------------------------------------------------------------------ */

ccmem_block_t
ccname_iface_method(ccstructs_deserialise_I, my_coords_t,
		    read) (cce_destination_t L CCSTRUCTS_UNUSED, ccstructs_deserialise_I I, ccmem_block_t B)
/* Interface method implementation.  Dedeserialise  an instance of "my_coords_t" from
   the memory block "B". */
{
  CCSTRUCTS_PC(my_coords_t, S, ccstructs_deserialise_self(I));
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
 ** Interface "my_printable_I": implementation for "my_coords_t".
 ** ----------------------------------------------------------------- */

static void my_printable_fprintf (cce_destination_t L, FILE * stream, char const * format, ...);

static ccname_iface_method_type(my_printable_I, print)  ccname_iface_method(my_printable_I, my_coords_t, print_rec);
static ccname_iface_method_type(my_printable_I, print)  ccname_iface_method(my_printable_I, my_coords_t, print_pol);

static ccname_iface_table_type(my_printable_I) const ccname_iface_table(my_printable_I, my_coords_t) = {
  .print_rec	= ccname_iface_method(my_printable_I, my_coords_t, print_rec),
  .print_pol	= ccname_iface_method(my_printable_I, my_coords_t, print_pol)
};

my_printable_I
ccname_iface_new(my_printable_I, my_coords_t) (my_coords_t const * S)
{
  return ccname_new(my_printable_I)(ccstructs_core(S), &ccname_iface_table(my_printable_I, my_coords_t));
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
ccname_iface_method(my_printable_I, my_coords_t, print_rec) (cce_destination_t L, my_printable_I I, FILE * stream)
{
  CCSTRUCTS_PC(my_coords_t, S, my_printable_self(I));

  my_printable_fprintf(L, stream, "X=%f, Y=%f\n", S->X, S->Y);
}

void
ccname_iface_method(my_printable_I, my_coords_t, print_pol) (cce_destination_t L, my_printable_I I, FILE * stream)
{
  CCSTRUCTS_PC(my_coords_t, S, my_printable_self(I));
  double	RHO   = hypot(S->X, S->Y);
  double	THETA = atan2(S->Y, S->X);

  my_printable_fprintf(L, stream, "RHO=%f, THETA=%f\n", RHO, THETA);
}

/* end of file */
