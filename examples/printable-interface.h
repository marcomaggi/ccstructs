/*
  Part of: CCStructs
  Contents: header file for printable interface
  Date: Jan 11, 2019

  Abstract

	This header  file defines the interface  "my_printable_I", to be used  by the
	example programs.


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

#ifndef PRINTABLE_INTERFACE_H
#define PRINTABLE_INTERFACE_H 1


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include <ccmemory.h>
#include <ccstructs.h>
#include <stdio.h>
#include <stdlib.h>


/** --------------------------------------------------------------------
 ** Interface "my_printable_I": definition.
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
ccname_new(my_printable_I) (ccstructs_core_t const * S, ccname_iface_table_type(my_printable_I) const * M)
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
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* defined STRUCT_WITH_METHODS_H */

/* end of file */
