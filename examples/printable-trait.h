/*
  Part of: CCStructs
  Contents: header file for printable trait
  Date: Jan 11, 2019

  Abstract

	This  header file  defines  the trait  "my_printable_T", to  be  used by  the
	example programs.


  Copyright (C) 2018, 2019, 2020 Marco Maggi <marco.maggi-ipsu@poste.it>

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

#ifndef PRINTABLE_TNTERFACE_H
#define PRINTABLE_TNTERFACE_H 1


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include <ccmemory.h>
#include <ccstructs.h>
#include <stdio.h>
#include <stdlib.h>


/** --------------------------------------------------------------------
 ** Trait "my_printable_T": definition.
 ** ----------------------------------------------------------------- */

typedef struct my_printable_T				my_printable_T;
typedef struct ccname_trait_table_type(my_printable_T)	ccname_trait_table_type(my_printable_T);

struct my_printable_T {
  ccname_trait_table_type(my_printable_T)	const * methods;
  ccstructs_core_t				const * self;
};

typedef void ccname_trait_method_type(my_printable_T, print) (cce_destination_t L, my_printable_T I, FILE * stream);

struct ccname_trait_table_type(my_printable_T) {
  ccname_trait_method_type(my_printable_T, print) *	print_rec;
  ccname_trait_method_type(my_printable_T, print) *	print_pol;
};

/* ------------------------------------------------------------------ */

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2)
static inline my_printable_T
ccname_new(my_printable_T) (ccstructs_core_t const * S, ccname_trait_table_type(my_printable_T) const * M)
{
  my_printable_T	I = {
    .methods	= M,
    .self	= S
  };
  return I;
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL
static inline ccstructs_core_t const *
my_printable_self (my_printable_T I)
{
  return I.self;
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1,3)
static inline void
my_printable_print_rec (cce_destination_t L, my_printable_T I, FILE * stream)
{
  I.methods->print_rec(L, I, stream);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1,3)
static inline void
my_printable_print_pol (cce_destination_t L, my_printable_T I, FILE * stream)
{
  I.methods->print_pol(L, I, stream);
}


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* defined STRUCT_WITH_METHODS_H */

/* end of file */
