/*
  Part of: CCStructs
  Contents: simple implementations of pathname interfaces
  Date: Mon Oct  8, 2018

  Abstract

	This  file   defines  a  simple   implementation  of  file   system  pathname
	representation: "ccstructs_pathname_t".  It is  vastly incomplete in terms of
	features.   This pathname  struct implements  the "ccstructs_dtor_I"  and the
	"ccstructs_pathname_I" interfaces.

	There are two "ccstruct_dtor_I" implementations: one for structs allocated on
	the  stack or  embedded into  enclosing structs;  one for  standalone structs
	allocated on the heap.

  Copyright (C) 2018, 2019 Marco Maggi <marco.maggi-ipsu@poste.it>

  This is free software; you can redistribute  it and/or modify it under the terms of
  the GNU Lesser General Public License as published by the Free Software Foundation;
  either version 3.0 of the License, or (at your option) any later version.

  This library  is distributed in the  hope that it  will be useful, but  WITHOUT ANY
  WARRANTY; without  even the implied  warranty of  MERCHANTABILITY or FITNESS  FOR A
  PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License along with
  this library; if not, write to the Free Software Foundation, Inc., 59 Temple Place,
  Suite 330, Boston, MA 02111-1307 USA.
*/


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "ccstructs-internals.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>

#undef CCSTRUCTS_DEBUGGING
#define CCSTRUCTS_DEBUGGING		0


/** --------------------------------------------------------------------
 ** Type definitions.
 ** ----------------------------------------------------------------- */

/* Function  prototype  of  the   constructor  of  "ccstruct_dtor_I"  implemented  by
   "ccstructs_pathname_t" for embedded structs. */
static ccname_iface_new_type(ccstructs_dtor_I, ccstructs_pathname_t) ccname_iface_new(ccstructs_dtor_I, ccstructs_pathname_t, embedded);

/* Function  prototype  of  the   constructor  of  "ccstruct_dtor_I"  implemented  by
   "ccstructs_pathname_t" for standalone structs. */
static ccname_iface_new_type(ccstructs_dtor_I, ccstructs_pathname_t) ccname_iface_new(ccstructs_dtor_I, ccstructs_pathname_t, standalone);

typedef struct ccstructs_serialised_pathname_t	ccstructs_serialised_pathname_t;

/* The layout of a serialised "ccstructs_pathname_t". */
struct ccstructs_serialised_pathname_t {
  size_t	len;
  char const *	ptr[];
};


/** --------------------------------------------------------------------
 ** Data struct "ccstructs_pathname_t": methods table type definition.
 ** ----------------------------------------------------------------- */

/* Type  of  method function  for  "ccstructs_pathname_t".   Functions of  this  type
   implement the method "new_dtor". */
typedef ccstructs_dtor_I ccname_method_type(ccstructs_pathname_t, new_dtor) (ccstructs_pathname_t const * ptn);

/* Type of methods table for instances of "ccstructs_pathnamt_t". */
struct ccname_table_type(ccstructs_pathname_t) {
  ccname_method_type(ccstructs_pathname_t, new_dtor) *	new_dtor;
};


/** --------------------------------------------------------------------
 ** Data struct "ccstructs_pathname_t": methods table for embedded instances.
 ** ----------------------------------------------------------------- */

/* Method function prototype.   Implementation function of the  method "new_dtor" for
   embedded instances of "ccstructs_pathname_t". */
static ccname_method_type(ccstructs_pathname_t, new_dtor) ccname_method(ccstructs_pathname_t, embedded, new_dtor);

/* Methods table for instances of "ccstructs_pathnamt_t": embedded variant. */
static ccname_table_type(ccstructs_pathname_t) const ccname_table(ccstructs_pathname_t, embedded) = {
  .new_dtor	= ccname_method(ccstructs_pathname_t, embedded, new_dtor)
};

ccstructs_dtor_I
ccname_method(ccstructs_pathname_t, embedded, new_dtor) (ccstructs_pathname_t const * ptn)
/* Implementation    of    method    "new_dtor"    for    embedded    instances    of
   "ccstructs_pathname_t". */
{
  return ccname_iface_new(ccstructs_dtor_I, ccstructs_pathname_t, embedded)(ptn);
}


/** --------------------------------------------------------------------
 ** Data struct "ccstructs_pathname_t": methods table for standalone instances.
 ** ----------------------------------------------------------------- */

/* Method function prototype.   Implementation function of the  method "new_dtor" for
   standalone instances of "ccstructs_pathname_t". */
static ccname_method_type(ccstructs_pathname_t, new_dtor) ccname_method(ccstructs_pathname_t, standalone, new_dtor);

/* Methods table for instances of "ccstructs_pathnamt_t": standalone variant. */
static ccname_table_type(ccstructs_pathname_t) const ccname_table(ccstructs_pathname_t, standalone) = {
  .new_dtor	= ccname_method(ccstructs_pathname_t, standalone, new_dtor)
};

ccstructs_dtor_I
ccname_method(ccstructs_pathname_t, standalone, new_dtor) (ccstructs_pathname_t const * ptn)
/* Implementation    of   method    "new_dtor"    for    standalone   instances    of
   "ccstructs_pathname_t". */
{
  return ccname_iface_new(ccstructs_dtor_I, ccstructs_pathname_t, standalone)(ptn);
}


/** --------------------------------------------------------------------
 ** Data struct "ccstructs_pathname_t": well known functions.
 ** ----------------------------------------------------------------- */

void
ccname_init(ccstructs_pathname_t, from_asciiz) (cce_destination_t L, ccstructs_pathname_t * const ptn, ccmem_asciiz_t const rep)
/* Instance  constructor.  Initialise  a struct  already  allocated on  the stack  or
   embedded   into   an  enclosing   struct.    Initialise   the  internal   pathname
   representation from an ASCIIZ block. */
{
  ptn->methods	= &ccname_table(ccstructs_pathname_t, embedded);
  ptn->rep.len = rep.len;
  ptn->rep.ptr = ccmem_std_malloc(L, sizeof(char) * (1 + ptn->rep.len));
  memcpy(ptn->rep.ptr, rep.ptr, rep.len);
  ptn->rep.ptr[ptn->rep.len] = '\0';
}

void
ccname_init(ccstructs_pathname_t, from_ascii) (cce_destination_t L, ccstructs_pathname_t * const ptn, ccmem_ascii_t const rep)
/* Instance  constructor.  Initialise  a struct  already  allocated on  the stack  or
   embedded   into   an  enclosing   struct.    Initialise   the  internal   pathname
   representation from an ASCII block. */
{
  ptn->methods	= &ccname_table(ccstructs_pathname_t, embedded);
  ptn->rep.len = rep.len;
  ptn->rep.ptr = ccmem_std_malloc(L, sizeof(char) * (1 + ptn->rep.len));
  memcpy(ptn->rep.ptr, rep.ptr, rep.len);
  ptn->rep.ptr[ptn->rep.len] = '\0';
}

void
ccname_init(ccstructs_pathname_t, from_chars) (cce_destination_t L, ccstructs_pathname_t * const ptn, char const * const P)
/* Instance  constructor.  Initialise  a struct  already  allocated on  the stack  or
   embedded   into   an  enclosing   struct.    Initialise   the  internal   pathname
   representation from an ASCIIZ string pointer. */
{
  ptn->methods	= &ccname_table(ccstructs_pathname_t, embedded);
  ptn->rep.len = strlen(P);
  ptn->rep.ptr = ccmem_std_malloc(L, sizeof(char) * (1 + ptn->rep.len));
  memcpy(ptn->rep.ptr, P, ptn->rep.len);
  ptn->rep.ptr[ptn->rep.len] = '\0';
}

void
ccname_init(ccstructs_pathname_t, deserialisable) (ccstructs_pathname_t * ptn)
{
  ptn->methods	= &ccname_table(ccstructs_pathname_t, embedded);
  ptn->rep.len	= 0;
  ptn->rep.ptr	= NULL;
}

/* ------------------------------------------------------------------ */

static void
ccname_final(ccstructs_pathname_t) (ccstructs_pathname_t * ptn)
/* Instance destructor.  Finalise  a struct releasing all  the asynchronous resources
   owned by the fields.  Leave the struct itself alone. */
{
  if (ptn->rep.ptr) {
    ccmem_std_free(ptn->rep.ptr);
  }
  ptn->rep.ptr = NULL;
  ptn->rep.len = 0;
  if (CCSTRUCTS_DEBUGGING) { fprintf(stderr, "%s: finalised\n", __func__); }
}

/* ------------------------------------------------------------------ */

__attribute__((__nonnull__(1)))
static ccstructs_pathname_t *
ccname_alloc(ccstructs_pathname_t) (cce_destination_t L)
/* Allocate a  new instance on the  heap using the standard  allocator implemented by
   CCMemory. */
{
  ccstructs_pathname_t *	ptn = ccmem_std_malloc(L, sizeof(ccstructs_pathname_t));

  return ptn;
}

static void
ccname_release(ccstructs_pathname_t) (ccstructs_pathname_t const * ptn)
/* Release an instance allocated on the heap using the standard allocator implemented
   by CCMemory. */
{
  ccmem_std_free((void *)ptn);
  if (CCSTRUCTS_DEBUGGING) { fprintf(stderr, "%s: released\n", __func__); }
}

/* ------------------------------------------------------------------ */

ccstructs_pathname_t const *
ccname_new(ccstructs_pathname_t, from_asciiz) (cce_destination_t L, ccmem_asciiz_t const rep)
/* Instance constructor.   Allocate a new  struct and initialise it.   Initialise the
   internal pathname representation from an ASCIIZ block. */
{
  ccstructs_pathname_t *	ptn = ccname_alloc(ccstructs_pathname_t)(L);

  ccname_init(ccstructs_pathname_t, from_asciiz)(L, ptn, rep);
  ptn->methods	= &ccname_table(ccstructs_pathname_t, standalone);
  return ptn;
}

ccstructs_pathname_t const *
ccname_new(ccstructs_pathname_t, from_ascii)  (cce_destination_t L, ccmem_ascii_t const rep)
/* Instance constructor.   Allocate a new  struct and initialise it.   Initialise the
   internal pathname representation from an ASCII block. */
{
  ccstructs_pathname_t *	ptn = ccname_alloc(ccstructs_pathname_t)(L);

  ccname_init(ccstructs_pathname_t, from_ascii)(L, ptn, rep);
  ptn->methods	= &ccname_table(ccstructs_pathname_t, standalone);
  return ptn;
}

ccstructs_pathname_t const *
ccname_new(ccstructs_pathname_t, from_chars)  (cce_destination_t L, char const * const P)
/* Instance constructor.   Allocate a new  struct and initialise it.   Initialise the
   internal pathname representation from an ASCIIZ string pointer. */
{
  ccstructs_pathname_t *	ptn = ccname_alloc(ccstructs_pathname_t)(L);

  ccname_init(ccstructs_pathname_t, from_chars)(L, ptn, P);
  ptn->methods	= &ccname_table(ccstructs_pathname_t, standalone);
  return ptn;
}

ccstructs_pathname_t *
ccname_new(ccstructs_pathname_t, deserialisable) (cce_destination_t L)
{
  ccstructs_pathname_t *	ptn = ccname_alloc(ccstructs_pathname_t)(L);

  ccname_init(ccstructs_pathname_t, deserialisable)(ptn);
  ptn->methods	= &ccname_table(ccstructs_pathname_t, standalone);
  return ptn;
}

/* ------------------------------------------------------------------ */

static CCSTRUCTS_UNUSED void
ccname_delete(ccstructs_pathname_t) (ccstructs_pathname_t * const ptn)
/* Instance destructor.  Finalise  a struct releasing all  the asynchronous resources
   owned by the fields.  Release the memory allocated for the struct.

   This function  is marked  as unused  because we  are meant  to use  the destructor
   interface to finalise instances of "ccstructs_pathname_t". */
{
  ccname_final(ccstructs_pathname_t)(ptn);
  ccname_release(ccstructs_pathname_t)(ptn);
}


/** --------------------------------------------------------------------
 ** Interface "ccstructs_dtor_I": implementation for embedded "ccstructs_pathname_t".
 ** ----------------------------------------------------------------- */

static ccstructs_core_destructor_fun_t ccstructs_embedded_pathname_destructor;

ccstructs_dtor_I
ccname_iface_new(ccstructs_dtor_I, ccstructs_pathname_t, embedded) (ccstructs_pathname_t const * const ptn)
/* Interface constructor.   Build and  return a  new interface  "ccstructs_dtor_I" as
   implemented by "ccstructs_pathname_t".  This is for embedded instances. */
{
  return ccname_new(ccstructs_dtor_I)(ccstructs_core(ptn), ccstructs_embedded_pathname_destructor);
}

/* ------------------------------------------------------------------ */

void
ccstructs_embedded_pathname_destructor (ccstructs_core_t * S)
{
  CCSTRUCTS_PC(ccstructs_pathname_t, ptn, S);

  ccname_final(ccstructs_pathname_t)(ptn);
}


/** --------------------------------------------------------------------
 ** Interface "ccstructs_dtor_I": implementation for standalone "ccstructs_pathname_t".
 ** ----------------------------------------------------------------- */

static ccstructs_core_destructor_fun_t ccstructs_standalone_pathname_destructor;

ccstructs_dtor_I
ccname_iface_new(ccstructs_dtor_I, ccstructs_pathname_t, standalone) (ccstructs_pathname_t const * const ptn)
/* Interface constructor.   Build and  return a  new interface  "ccstructs_dtor_I" as
   implemented by "ccstructs_pathname_t".  This is for standalone instances. */
{
  return ccname_new(ccstructs_dtor_I)(ccstructs_core(ptn), ccstructs_standalone_pathname_destructor);
}

/* ------------------------------------------------------------------ */

void
ccstructs_standalone_pathname_destructor (ccstructs_core_t * S)
{
  CCSTRUCTS_PC(ccstructs_pathname_t, ptn, S);

  ccname_delete(ccstructs_pathname_t)(ptn);
}


/** --------------------------------------------------------------------
 ** Interface "ccstructs_pathname_I": implementation for "ccstructs_pathname_t".
 ** ----------------------------------------------------------------- */

/* Method  function prototype.   This  function implements  the  method "asciiz"  for
   instances     of     type     "ccstructs_pathname_I"     as     implemented     by
   "ccstructs_pathname_t". */
static ccname_iface_method_type(ccstructs_pathname_I, asciiz)
  ccname_iface_method(ccstructs_pathname_I, ccstructs_pathname_t, asciiz);

/* Method function  prototype.  This function  implements the method  "is_static" for
   instances     of     type     "ccstructs_pathname_I"     as     implemented     by
   "ccstructs_pathname_t". */
static ccname_iface_method_type(ccstructs_pathname_I, is_static)
  ccname_iface_method(ccstructs_pathname_I, ccstructs_pathname_t, is_static);

/* Method function prototype.  This function  implements the method "is_absolute" for
   instances     of     type     "ccstructs_pathname_I"     as     implemented     by
   "ccstructs_pathname_t". */
static ccname_iface_method_type(ccstructs_pathname_I, is_absolute)
  ccname_iface_method(ccstructs_pathname_I, ccstructs_pathname_t, is_absolute);

/* Method function prototype.  This function  implements the method "is_relative" for
   instances     of     type     "ccstructs_pathname_I"     as     implemented     by
   "ccstructs_pathname_t". */
static ccname_iface_method_type(ccstructs_pathname_I, is_relative)
  ccname_iface_method(ccstructs_pathname_I, ccstructs_pathname_t, is_relative);

/* Method function  prototype.  This  function implements the  method "is_normalised"
   for    instances    of    type   "ccstructs_pathname_I"    as    implemented    by
   "ccstructs_pathname_t". */
static ccname_iface_method_type(ccstructs_pathname_I, is_normalised)
  ccname_iface_method(ccstructs_pathname_I, ccstructs_pathname_t, is_normalised);

/* Method function prototype.  This function  implements the method "is_realpath" for
   instances     of     type     "ccstructs_pathname_I"     as     implemented     by
   "ccstructs_pathname_t". */
static ccname_iface_method_type(ccstructs_pathname_I, is_realpath)
  ccname_iface_method(ccstructs_pathname_I, ccstructs_pathname_t, is_realpath);

/* Method  function  prototype.   This  function implements  the  method  "dtor"  for
   instances     of     type     "ccstructs_pathname_I"     as     implemented     by
   "ccstructs_pathname_t". */
static ccname_iface_method_type(ccstructs_pathname_I, dtor)
  ccname_iface_method(ccstructs_pathname_I, ccstructs_pathname_t, dtor);

/* Method function  prototype.  This  function implements  the method  "dumpable" for
   instances     of     type     "ccstructs_pathname_I"     as     implemented     by
   "ccstructs_pathname_t". */
static ccname_iface_method_type(ccstructs_pathname_I, dumpable)
  ccname_iface_method(ccstructs_pathname_I, ccstructs_pathname_t, dumpable);

/* Method function prototype.   This function implements the  method "serialiser" for
   instances     of     type     "ccstructs_pathname_I"     as     implemented     by
   "ccstructs_pathname_t". */
static ccname_iface_method_type(ccstructs_pathname_I, serialiser)
  ccname_iface_method(ccstructs_pathname_I, ccstructs_pathname_t, serialiser);

/* Method function prototype.  This function implements the method "deserialiser" for
   instances     of     type     "ccstructs_pathname_I"     as     implemented     by
   "ccstructs_pathname_t". */
static ccname_iface_method_type(ccstructs_pathname_I, deserialiser)
  ccname_iface_method(ccstructs_pathname_I, ccstructs_pathname_t, deserialiser);

/* Interface  methods  table.  This  struct  implements  the  methods table  for  the
   interface "ccstructs_pathname_I" as implemented by "ccstructs_pathname_t". */
static ccname_iface_table_type(ccstructs_pathname_I) const ccname_iface_table(ccstructs_pathname_I, ccstructs_pathname_t) = {
  .asciiz	= ccname_iface_method(ccstructs_pathname_I, ccstructs_pathname_t, asciiz),
  .is_static	= ccname_iface_method(ccstructs_pathname_I, ccstructs_pathname_t, is_static),
  .is_absolute	= ccname_iface_method(ccstructs_pathname_I, ccstructs_pathname_t, is_absolute),
  .is_relative	= ccname_iface_method(ccstructs_pathname_I, ccstructs_pathname_t, is_relative),
  .is_normalised= ccname_iface_method(ccstructs_pathname_I, ccstructs_pathname_t, is_normalised),
  .is_realpath	= ccname_iface_method(ccstructs_pathname_I, ccstructs_pathname_t, is_realpath),

  .dtor		= ccname_iface_method(ccstructs_pathname_I, ccstructs_pathname_t, dtor),
  .dumpable	= ccname_iface_method(ccstructs_pathname_I, ccstructs_pathname_t, dumpable),
  .serialiser	= ccname_iface_method(ccstructs_pathname_I, ccstructs_pathname_t, serialiser),
  .deserialiser	= ccname_iface_method(ccstructs_pathname_I, ccstructs_pathname_t, deserialiser)
};

/* ------------------------------------------------------------------ */

ccmem_asciiz_t
ccname_iface_method(ccstructs_pathname_I, ccstructs_pathname_t, asciiz) (cce_destination_t L CCSTRUCTS_UNUSED, ccstructs_pathname_I I)
/* Method implementation  function.  Implement the  method "asciiz" for  instances of
   type "ccstructs_pathname_I" as implemented by "ccstructs_pathname_t". */
{
  CCSTRUCTS_PC(ccstructs_pathname_t const, ptn, ccstructs_pathname_self(I));
  return ptn->rep;
}

bool
ccname_iface_method(ccstructs_pathname_I, ccstructs_pathname_t, is_static) (ccstructs_pathname_I I CCSTRUCTS_UNUSED)
/* Method implementation function.  Implement the method "is_static" for instances of
   type "ccstructs_pathname_I" as implemented by "ccstructs_pathname_t". */
{
  return false;
}

bool
ccname_iface_method(ccstructs_pathname_I, ccstructs_pathname_t, is_absolute) (cce_destination_t L CCSTRUCTS_UNUSED, ccstructs_pathname_I I)
/* Method implementation function.  Implement  the method "is_absolute" for instances
   of type "ccstructs_pathname_I" as implemented by "ccstructs_pathname_t". */
{
  CCSTRUCTS_PC(ccstructs_pathname_t const, ptn, ccstructs_pathname_self(I));
  return ('/' == ptn->rep.ptr[0])? true : false;
}

bool
ccname_iface_method(ccstructs_pathname_I, ccstructs_pathname_t, is_relative) (cce_destination_t L CCSTRUCTS_UNUSED, ccstructs_pathname_I I)
/* Method implementation function.  Implement  the method "is_relative" for instances
   of type "ccstructs_pathname_I" as implemented by "ccstructs_pathname_t". */
{
  CCSTRUCTS_PC(ccstructs_pathname_t const, ptn, ccstructs_pathname_self(I));
  return ('/' == ptn->rep.ptr[0])? false : true;
}

bool
ccname_iface_method(ccstructs_pathname_I, ccstructs_pathname_t, is_normalised) (cce_destination_t L, ccstructs_pathname_I I CCSTRUCTS_UNUSED)
/* Method  implementation   function.   Implement  the  method   "is_normalised"  for
   instances     of     type     "ccstructs_pathname_I"     as     implemented     by
   "ccstructs_pathname_t". */
{
  cce_raise(L, cce_condition_new_unimplemented());
}

bool
ccname_iface_method(ccstructs_pathname_I, ccstructs_pathname_t, is_realpath) (cce_destination_t L, ccstructs_pathname_I I CCSTRUCTS_UNUSED)
/* Method implementation function.  Implement  the method "is_realpath" for instances
   of type "ccstructs_pathname_I" as implemented by "ccstructs_pathname_t". */
{
  cce_raise(L, cce_condition_new_unimplemented());
}

/* ------------------------------------------------------------------ */

ccstructs_dtor_I
ccname_iface_method(ccstructs_pathname_I, ccstructs_pathname_t, dtor) (ccstructs_pathname_I I)
/* Method implementation function.  Implement the method "dtor" for instances of type
   "ccstructs_pathname_I"  as implemented  by  "ccstructs_pathname_t".  The  returned
   destructor will work for both embedded and standalone instances. */
{
  CCSTRUCTS_PC(ccstructs_pathname_t const, ptn, ccstructs_pathname_self(I));

  return ccname_iface_new(ccstructs_dtor_I, ccstructs_pathname_t)(ptn);
}

ccstructs_dumpable_I
ccname_iface_method(ccstructs_pathname_I, ccstructs_pathname_t, dumpable) (cce_destination_t L CCSTRUCTS_UNUSED, ccstructs_pathname_I I)
/* Method implementation function.  Implement the  method "dumpable" for instances of
   type  "ccstructs_pathname_I"   as  implemented  by   "ccstructs_pathname_t".   The
   returned destructor will work for both embedded and standalone instances. */
{
  CCSTRUCTS_PC(ccstructs_pathname_t const, ptn, ccstructs_pathname_self(I));

  return ccname_iface_new(ccstructs_dumpable_I, ccstructs_pathname_t)(ptn);
}

ccstructs_serialiser_I
ccname_iface_method(ccstructs_pathname_I, ccstructs_pathname_t, serialiser) (cce_destination_t L CCSTRUCTS_UNUSED, ccstructs_pathname_I I)
/* Method implementation  function.  Implement the method  "serialiser" for instances
   of  type "ccstructs_pathname_I"  as  implemented  by "ccstructs_pathname_t".   The
   returned destructor will work for both embedded and standalone instances. */
{
  CCSTRUCTS_PC(ccstructs_pathname_t const, ptn, ccstructs_pathname_self(I));

  return ccname_iface_new(ccstructs_serialiser_I, ccstructs_pathname_t)(ptn);
}

ccstructs_deserialiser_I
ccname_iface_method(ccstructs_pathname_I, ccstructs_pathname_t, deserialiser) (cce_destination_t L CCSTRUCTS_UNUSED, ccstructs_pathname_I I)
/* Method implementation function.  Implement the method "deserialiser" for instances
   of  type "ccstructs_pathname_I"  as  implemented  by "ccstructs_pathname_t".   The
   returned destructor will work for both embedded and standalone instances. */
{
  CCSTRUCTS_PC(ccstructs_pathname_t, ptn, ccstructs_pathname_self(I));

  return ccname_iface_new(ccstructs_deserialiser_I, ccstructs_pathname_t)(ptn);
}


/** --------------------------------------------------------------------
 ** Interface "ccstructs_serialiser_I": implementation for "ccstructs_pathname_t".
 ** ----------------------------------------------------------------- */

static ccname_iface_method_type(ccstructs_serialiser_I, required_size)
  ccname_iface_method(ccstructs_serialiser_I, ccstructs_pathname_t, required_size);
static ccname_iface_method_type(ccstructs_serialiser_I, write)
  ccname_iface_method(ccstructs_serialiser_I, ccstructs_pathname_t, write);

/* Interface  table  of  methods.    Implementation  of  "ccstructs_serialiser_I"  for
   "ccstructs_pathname_t". */
static ccname_iface_table_type(ccstructs_serialiser_I) const ccname_iface_table(ccstructs_serialiser_I, ccstructs_pathname_t) = {
  .required_size = ccname_iface_method(ccstructs_serialiser_I, ccstructs_pathname_t, required_size),
  .write         = ccname_iface_method(ccstructs_serialiser_I, ccstructs_pathname_t, write),
};

/* ------------------------------------------------------------------ */

size_t
ccname_iface_method(ccstructs_serialiser_I, ccstructs_pathname_t, required_size) (ccstructs_serialiser_I I)
/* Return the minimum number of bytes  required to hold the serialised representation
   of "ccstructs_pathname_t".*/
{
  CCSTRUCTS_PC(ccstructs_pathname_t const, ptn, ccstructs_serialiser_self(I));

  return sizeof(ccstructs_serialised_pathname_t) + ptn->rep.len;
}

ccmem_block_t
ccname_iface_method(ccstructs_serialiser_I, ccstructs_pathname_t,
		    write) (cce_destination_t L CCSTRUCTS_UNUSED, ccstructs_serialiser_I I, ccmem_block_t B)
/* Interface method implementation.  Serialise  an instance of "ccstructs_pathname_t"
   in the memory block "B". */
{
  CCSTRUCTS_PC(ccstructs_pathname_t const, ptn, ccstructs_serialiser_self(I));
  CCSTRUCTS_PC(ccstructs_serialised_pathname_t, W, B.ptr);
  ccmem_block_t	N = {
    .ptr	= B.ptr + sizeof(ccstructs_serialised_pathname_t) + ptn->rep.len,
    .len	= B.len - sizeof(ccstructs_serialised_pathname_t) - ptn->rep.len
  };

  W->len = ptn->rep.len;
  memcpy(W->ptr, ptn->rep.ptr, ptn->rep.len);
  return N;
}


/** --------------------------------------------------------------------
 ** Interface "ccstructs_deserialiser_I": implementation for "ccstructs_pathname_t".
 ** ----------------------------------------------------------------- */

static ccname_iface_method_type(ccstructs_deserialiser_I, required_size)
  ccname_iface_method(ccstructs_deserialiser_I, ccstructs_pathname_t, required_size);
static ccname_iface_method_type(ccstructs_deserialiser_I, read)
  ccname_iface_method(ccstructs_deserialiser_I, ccstructs_pathname_t, read);

/* Interface  table  of  methods.  Implementation  of  "ccstructs_deserialiser_I"  for
   "ccstructs_pathname_t". */
static ccname_iface_table_type(ccstructs_deserialiser_I) const ccname_iface_table(ccstructs_deserialiser_I, ccstructs_pathname_t) = {
  .required_size = ccname_iface_method(ccstructs_deserialiser_I, ccstructs_pathname_t, required_size),
  .read          = ccname_iface_method(ccstructs_deserialiser_I, ccstructs_pathname_t, read)
};

/* ------------------------------------------------------------------ */

size_t
ccname_iface_method(ccstructs_deserialiser_I, ccstructs_pathname_t, required_size) (ccstructs_deserialiser_I I)
/* Return the minimum number of bytes  required to hold the serialised representation
   of "ccstructs_pathname_t".*/
{
  CCSTRUCTS_PC(ccstructs_pathname_t const, ptn, ccstructs_deserialiser_self(I));

  return sizeof(ccstructs_serialised_pathname_t) + ptn->rep.len;
}

ccmem_block_t
ccname_iface_method(ccstructs_deserialiser_I, ccstructs_pathname_t,
		    read) (cce_destination_t L, ccstructs_deserialiser_I I, ccmem_block_t B)
/* Interface method implementation.  Dedeserialise  an instance of "ccstructs_pathname_t" from
   the memory block "B". */
{
  CCSTRUCTS_PC(ccstructs_pathname_t, ptn, ccstructs_deserialiser_self(I));
  CCSTRUCTS_PC(ccstructs_serialised_pathname_t const, W, B.ptr);
  ccmem_block_t	N = {
    .ptr	= B.ptr + sizeof(ccstructs_serialised_pathname_t),
    .len	= B.len - sizeof(ccstructs_serialised_pathname_t)
  };

  ptn->rep.len = W->len;
  ptn->rep.ptr = ccmem_std_malloc(L, sizeof(char) * (1 + ptn->rep.len));
  memcpy(ptn->rep.ptr, W->ptr, W->len);
  ptn->rep.ptr[ptn->rep.len] = '\0';
  return N;
}


/** --------------------------------------------------------------------
 ** Interface "ccstructs_dumpable_I": implementation for "ccstructs_pathname_t".
 ** ----------------------------------------------------------------- */

static ccname_iface_method_type(ccstructs_dumpable_I, dump)  ccname_iface_method(ccstructs_dumpable_I, ccstructs_pathname_t, dump);

static ccname_iface_table_type(ccstructs_dumpable_I) const ccname_iface_table(ccstructs_dumpable_I, ccstructs_pathname_t) = {
  .dump	= ccname_iface_method(ccstructs_dumpable_I, ccstructs_pathname_t, dump)
};

/* ------------------------------------------------------------------ */

void
ccname_iface_method(ccstructs_dumpable_I, ccstructs_pathname_t, dump) (cce_destination_t L, ccstructs_dumpable_I I)
{
  CCSTRUCTS_PC(ccstructs_pathname_t const, ptn, ccstructs_dumpable_self(I));
  int	rv;

  errno = 0;
  rv = fprintf(stderr, "%s\n", ptn->rep.ptr);
  if (rv < 0) {
    cce_raise(L, cce_condition_new_errno_clear());
  }
}


/** --------------------------------------------------------------------
 ** Data struct "ccstructs_pathname_t": implemented interfaces constructors.
 ** ----------------------------------------------------------------- */

ccstructs_dtor_I
ccname_iface_new(ccstructs_dtor_I, ccstructs_pathname_t) (ccstructs_pathname_t const * const ptn)
/* Interface constructor.  Build  and return a new  "ccstructs_dtor_I" implemented by
   "ccstructs_pathname_t".  Make  use of  the interface  constructor selected  by the
   data struct's methods table.*/
{
  return ptn->methods->new_dtor(ptn);
}

ccstructs_pathname_I
ccname_iface_new(ccstructs_pathname_I, ccstructs_pathname_t) (ccstructs_pathname_t const * const ptn)
/* Interface constructor.  Build and  return a new "ccstructs_pathname_I" implemented
   by "ccstructs_pathname_t". */
{
  return ccname_new(ccstructs_pathname_I)(ccstructs_core(ptn), &ccname_iface_table(ccstructs_pathname_I, ccstructs_pathname_t));
}

ccstructs_serialiser_I
ccname_iface_new(ccstructs_serialiser_I, ccstructs_pathname_t) (ccstructs_pathname_t const * S)
/* Interface   constructor.   Build   an  instance   of  "ccstructs_serialiser_I"   as
   implemented by "ccstructs_pathname_t". */
{
  return ccname_new(ccstructs_serialiser_I)(ccstructs_core(S), &ccname_iface_table(ccstructs_serialiser_I, ccstructs_pathname_t));
}

ccstructs_deserialiser_I
ccname_iface_new(ccstructs_deserialiser_I, ccstructs_pathname_t) (ccstructs_pathname_t * S)
/* Interface  constructor.    Build  an  instance  of   "ccstructs_deserialiser_I"  as
   implemented by "ccstructs_pathname_t". */
{
  return ccname_new(ccstructs_deserialiser_I)(ccstructs_core(S), &ccname_iface_table(ccstructs_deserialiser_I, ccstructs_pathname_t));
}

ccstructs_dumpable_I
ccname_iface_new(ccstructs_dumpable_I, ccstructs_pathname_t) (ccstructs_pathname_t const * S)
/* Interface constructor.  Build an instance of "ccstructs_dumpable_I" as implemented
   by "ccstructs_pathname_t". */
{
  return ccname_new(ccstructs_dumpable_I)(ccstructs_core(S), &ccname_iface_table(ccstructs_dumpable_I, ccstructs_pathname_t));
}

/* end of file */
