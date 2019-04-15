/*
  Part of: CCStructs
  Contents: header file for sample struct with methods table
  Date: Thu Dec 27, 2018

  Abstract

	This header file defines the struct  "my_coords_t" and shows how to implement
	the  main traits  for it.   "my_coords_t" is  a simple  struct with  embedded
	fields, no pointers to external memory blocks.

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

#ifndef STRUCT_WITH_METHODS_H
#define STRUCT_WITH_METHODS_H 1


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include <ccmemory.h>
#include <ccstructs.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "printable-trait.h"


/** --------------------------------------------------------------------
 ** Preliminary definitions.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif


/** --------------------------------------------------------------------
 ** Type definitions: data struct "my_coords_t".
 ** ----------------------------------------------------------------- */

typedef struct my_coords_t			my_coords_t;
typedef struct ccname_table_type(my_coords_t)	ccname_table_type(my_coords_t);

struct my_coords_t {
  ccname_table_type(my_coords_t) const *	methods;
  double	X;
  double	Y;
};


/** --------------------------------------------------------------------
 ** Data struct "my_coords_t": well known functions API.
 ** ----------------------------------------------------------------- */

/* Initialisation  function  that  initialises  an already  allocated  struct.   This
   initialises from rectangular coordinates. */
ccstructs_decl void ccname_init(my_coords_t, rec) (my_coords_t * S, double X, double Y)
  __attribute__((__nonnull__(1)));

/* Initialisation  function  that  initialises  an already  allocated  struct.   This
   initialises from polar coordinates. */
ccstructs_decl void ccname_init(my_coords_t, pol) (my_coords_t * S, double RHO, double THETA)
  __attribute__((__nonnull__(1)));

/* Initialisation  function  that  initialises  an already  allocated  struct.   This
   initialises in such a  way that it allows for both  finalisation and mutation from
   deserialisation. */
ccstructs_decl void ccname_init(my_coords_t, deserlialisable) (my_coords_t * S)
  __attribute__((__nonnull__(1)));

/* ------------------------------------------------------------------ */

ccstructs_decl my_coords_t const * ccname_new(my_coords_t, rec) (cce_destination_t L, double X, double Y)
  __attribute__((__nonnull__(1),__returns_nonnull__));

/* Constructor function  that allocates  the struct  on the  heap using  the standard
   memory   allocator  implemented   by  CCMemory.    This  initialises   from  polar
   coordinates. */
ccstructs_decl my_coords_t const * ccname_new(my_coords_t, pol) (cce_destination_t L, double RHO, double THETA)
  __attribute__((__nonnull__(1),__returns_nonnull__));

/* Constructor function  that allocates  the struct  on the  heap using  the standard
   memory allocator implemented by CCMemory.  This  initialises in such a way that it
   allows for both finalisation and mutation from deserialisation. */
ccstructs_decl my_coords_t * ccname_new(my_coords_t, deserialisable) (cce_destination_t L)
  __attribute__((__nonnull__(1),__returns_nonnull__));


/** --------------------------------------------------------------------
 ** Data struct "my_coords_t": constructors for implemented traits.
 ** ----------------------------------------------------------------- */

/* Constructor for a "ccstructs_dtor_T" trait. */
ccstructs_decl ccstructs_dtor_T ccname_trait_new(ccstructs_dtor_T, my_coords_t) (my_coords_t const * self)
  __attribute__((__nonnull__(1)));

/* ------------------------------------------------------------------ */

/* Constructor  for   a  "ccstructs_dumpable_T"   trait  that  prints   a  struct
   representation on some output channel. */
ccstructs_decl ccstructs_dumpable_T ccname_trait_new(ccstructs_dumpable_T, my_coords_t) (my_coords_t const * S)
  __attribute__((__nonnull__(1)));

/* ------------------------------------------------------------------ */

/* Constructor for a "ccstructs_serialiser_T" trait that serialises an instance of
   "my_coords_t" into a memory block. */
ccstructs_decl ccstructs_serialiser_T ccname_trait_new(ccstructs_serialiser_T, my_coords_t) (my_coords_t const * S)
  __attribute__((__nonnull__(1)));

/* Constructor  for  a  "ccstructs_deserialiser_T"   trait  that  deserialises  an
   instance of "my_coords_t" from a memory block. */
ccstructs_decl ccstructs_deserialiser_T ccname_trait_new(ccstructs_deserialiser_T, my_coords_t) (my_coords_t * S)
  __attribute__((__nonnull__(1)));

/* ------------------------------------------------------------------ */

/* Constructor for a  "my_printable_T" trait that prints  a struct representation
   on some output channel. */
ccstructs_decl my_printable_T ccname_trait_new(my_printable_T, my_coords_t) (my_coords_t const * S)
  __attribute__((__nonnull__(1)));


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* defined STRUCT_WITH_METHODS_H */

/* end of file */
