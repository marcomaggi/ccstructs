/*
  Part of: CCStructs
  Contents: demo program for structs with no methods, header file
  Date: Jan 11, 2019

  Abstract

	This demo program shows how to implement  an interface for a struct type.  In
	this demo the data struct has no methods table.

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

#ifndef STRUCT_NO_METHODS_H
#define STRUCT_NO_METHODS_H


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include <ccmemory.h>
#include <ccstructs.h>
#include <ccnames.h>
#include <stdio.h>
#include <stdlib.h>


/** --------------------------------------------------------------------
 ** Type definitions: data struct "my_coords_t".
 ** ----------------------------------------------------------------- */

typedef struct my_coords_t	my_coords_t;

struct my_coords_t {
  double	X;
  double	Y;
};


/** --------------------------------------------------------------------
 ** Data struct "my_coords_t": well known functions API.
 ** ----------------------------------------------------------------- */

ccstructs_decl void ccname_init(my_coords_t, rec) (my_coords_t * S, double X, double Y)
  __attribute__((__nonnull__(1)));

ccstructs_decl void ccname_init(my_coords_t, pol) (my_coords_t * S, double RHO, double THETA)
  __attribute__((__nonnull__(1)));

ccstructs_decl void ccname_final(my_coords_t) (my_coords_t const * S CCNAMES_UNUSED)
  __attribute__((__nonnull__(1)));

ccstructs_decl my_coords_t const * ccname_new(my_coords_t, rec) (cce_destination_t L, double X, double Y)
  __attribute__((__nonnull__(1),__returns_nonnull__));

ccstructs_decl my_coords_t const * ccname_new(my_coords_t, pol) (cce_destination_t L, double RHO, double THETA)
  __attribute__((__nonnull__(1),__returns_nonnull__));

ccstructs_decl void ccname_delete(my_coords_t) (my_coords_t const * S)
  __attribute__((__nonnull__(1)));


/** --------------------------------------------------------------------
 ** Interface "my_printable_I".
 ** ----------------------------------------------------------------- */

typedef struct my_printable_I				my_printable_I;
typedef struct ccname_iface_table_type(my_printable_I)	ccname_iface_table_type(my_printable_I);

struct my_printable_I {
  ccname_iface_table_type(my_printable_I)	const * methods;
  ccstructs_core_t				const * self;
};

typedef void ccname_iface_method_type(my_printable_I, print) (cce_destination_t L, my_printable_I I, FILE * stream);

struct ccname_iface_table_type(my_printable_I) {
  ccname_iface_method_type(my_printable_I, print) *	print_rec;
  ccname_iface_method_type(my_printable_I, print) *	print_pol;
};

/* ------------------------------------------------------------------ */

__attribute__((__always_inline__,__nonnull__(1,2)))
static inline my_printable_I
my_printable_new (ccstructs_core_t const * S, ccname_iface_table_type(my_printable_I) const * M)
{
  my_printable_I	I = {
    .methods	= M,
    .self	= S
  };
  return I;
}

__attribute__((__always_inline__,__returns_nonnull__))
static inline ccstructs_core_t const *
my_printable_self (my_printable_I I)
{
  return I.self;
}

__attribute__((__always_inline__,__nonnull__(1,3)))
static inline void
my_printable_print_rec (cce_destination_t L, my_printable_I I, FILE * stream)
{
  I.methods->print_rec(L, I, stream);
}

__attribute__((__always_inline__,__nonnull__(1,3)))
static inline void
my_printable_print_pol (cce_destination_t L, my_printable_I I, FILE * stream)
{
  I.methods->print_pol(L, I, stream);
}


/** --------------------------------------------------------------------
 ** Data struct "my_coords_t": implemented interfaces constructors.
 ** ----------------------------------------------------------------- */

ccstructs_decl my_printable_I ccname_iface_new(my_printable_I, my_coords_t) (my_coords_t const * S)
  __attribute__((__nonnull__(1)));

ccstructs_decl ccstructs_serialise_I ccname_iface_new(ccstructs_serialise_I, my_coords_t) (my_coords_t const * S)
  __attribute__((__nonnull__(1)));

ccstructs_decl ccstructs_deserialise_I ccname_iface_new(ccstructs_deserialise_I, my_coords_t) (my_coords_t * S)
  __attribute__((__nonnull__(1)));


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#endif /* define STRUCT_NO_METHODS_H */

/* end of file */
