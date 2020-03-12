/*
  Part of: CCStructs
  Contents: public header file
  Date: Apr 30, 2018

  Abstract

	This file must be included in all the source files making use of CCStructs.

  Copyright (C) 2018, 2019 Marco Maggi <mrc.mgg@gmail.com>

  This program is free  software: you can redistribute it and/or  modify it under the
  terms of the  GNU Lesser General Public  License as published by  the Free Software
  Foundation, either version 3 of the License, or (at your option) any later version.

  This program  is distributed in the  hope that it  will be useful, but  WITHOUT ANY
  WARRANTY; without  even the implied  warranty of  MERCHANTABILITY or FITNESS  FOR A
  PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

  You should have received a copy of the Lesser GNU General Public License along with
  this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CCSTRUCTS_H
#define CCSTRUCTS_H 1


/** --------------------------------------------------------------------
 ** Preliminary definitions.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif

/* The  macro  CCSTRUCTS_UNUSED  indicates  that a  function,  function  argument  or
   variable may potentially be unused. Usage examples:

   static int unused_function (char arg) CCSTRUCTS_UNUSED;
   int foo (char unused_argument CCSTRUCTS_UNUSED);
   int unused_variable CCSTRUCTS_UNUSED;
*/
#ifdef __GNUC__
#  define CCSTRUCTS_UNUSED		__attribute__((__unused__))
#else
#  define CCSTRUCTS_UNUSED		/* empty */
#endif

#ifndef __GNUC__
#  define __attribute__(...)	/* empty */
#endif

/* I found  the following chunk on  the Net.  (Marco Maggi;  Sun Feb 26,
   2012) */
#if defined _WIN32 || defined __CYGWIN__
#  ifdef BUILDING_DLL
#    ifdef __GNUC__
#      define ccstructs_decl		__attribute__((__dllexport__)) extern
#    else
#      define ccstructs_decl		__declspec(dllexport) extern
#    endif
#  else
#    ifdef __GNUC__
#      define ccstructs_decl		__attribute__((__dllimport__)) extern
#    else
#      define ccstructs_decl		__declspec(dllimport) extern
#    endif
#  endif
#  define ccstructs_private_decl	extern
#else
#  if __GNUC__ >= 4
#    define ccstructs_decl		__attribute__((__visibility__("default"))) extern
#    define ccstructs_private_decl	__attribute__((__visibility__("hidden")))  extern
#  else
#    define ccstructs_decl		extern
#    define ccstructs_private_decl	extern
#  endif
#endif


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include <ccmemory.h>
#include <ccnames.h>


/** --------------------------------------------------------------------
 ** Constants and preprocessor macros.
 ** ----------------------------------------------------------------- */

#define CCSTRUCTS_PC(POINTER_TYPE, POINTER_NAME, EXPRESSION)	\
  POINTER_TYPE * POINTER_NAME = (POINTER_TYPE *) (EXPRESSION)


/** --------------------------------------------------------------------
 ** Version functions.
 ** ----------------------------------------------------------------- */

ccstructs_decl char const *	ccstructs_version_string		(void);
ccstructs_decl int		ccstructs_version_interface_current	(void);
ccstructs_decl int		ccstructs_version_interface_revision	(void);
ccstructs_decl int		ccstructs_version_interface_age		(void);


/** --------------------------------------------------------------------
 ** Generic struct wrapper.
 ** ----------------------------------------------------------------- */

typedef struct ccstructs_core_t		ccstructs_core_t;
typedef void ccstructs_core_destructor_fun_t (ccstructs_core_t * S);

struct ccstructs_core_t;

__attribute__((__always_inline__,__nonnull__(1),__returns_nonnull__))
static inline ccstructs_core_t const *
ccstructs_core (void const * S)
{
  return ((ccstructs_core_t *)(S));
}


/** --------------------------------------------------------------------
 ** Trait: destructors.
 ** ----------------------------------------------------------------- */

typedef struct ccstructs_dtor_T		ccstructs_dtor_T;

struct ccstructs_dtor_T {
  ccstructs_core_destructor_fun_t	* destroy;
  ccstructs_core_t const		* self;
};

/* ------------------------------------------------------------------ */

__attribute__((__always_inline__,__nonnull__(1,2)))
static inline ccstructs_dtor_T
ccname_new(ccstructs_dtor_T)(ccstructs_core_t const * S, ccstructs_core_destructor_fun_t * destroy)
{
  ccstructs_dtor_T	I = { .destroy = destroy, .self = S };
  return I;
}

__attribute__((__always_inline__,__pure__))
static inline ccstructs_core_t const *
ccstructs_dtor_self (ccstructs_dtor_T I)
{
  return I.self;
}

__attribute__((__always_inline__))
static inline void
ccstructs_dtor_destroy (ccstructs_dtor_T I)
{
  I.destroy(cce_resource_pointer(I.self));
}


/** --------------------------------------------------------------------
 ** Generic struct handling: exception handlers.
 ** ----------------------------------------------------------------- */

typedef struct ccstructs_clean_handler_t	ccstructs_clean_handler_t;
typedef struct ccstructs_error_handler_t	ccstructs_error_handler_t;

struct ccstructs_clean_handler_t {
  cce_clean_handler_t	handler;
};

struct ccstructs_error_handler_t {
  cce_error_handler_t	handler;
};

/* ------------------------------------------------------------------ */

__attribute__((__always_inline__,__nonnull__(1),__returns_nonnull__))
static inline cce_clean_handler_t *
ccstructs_clean_handler_handler (ccstructs_clean_handler_t * const H)
{
  return &(H->handler);
}

__attribute__((__always_inline__,__nonnull__(1),__returns_nonnull__))
static inline cce_error_handler_t *
ccstructs_error_handler_handler (ccstructs_error_handler_t * const H)
{
  return &(H->handler);
}

__attribute__((__always_inline__,__nonnull__(1),__returns_nonnull__))
static inline cce_clean_handler_t const *
ccstructs_const_clean_handler_handler (ccstructs_clean_handler_t const * const H)
{
  return &(H->handler);
}

__attribute__((__always_inline__,__nonnull__(1),__returns_nonnull__))
static inline cce_error_handler_t const *
ccstructs_const_error_handler_handler (ccstructs_error_handler_t const * const H)
{
  return &(H->handler);
}

#define ccstructs_handler_handler(H)					\
  _Generic((H),								\
	   ccstructs_clean_handler_t *: ccstructs_clean_handler_handler, \
	   ccstructs_error_handler_t *: ccstructs_error_handler_handler, \
	   ccstructs_clean_handler_t const *: ccstructs_const_clean_handler_handler, \
	   ccstructs_error_handler_t const *: ccstructs_const_error_handler_handler)(H)

/* ------------------------------------------------------------------ */

ccstructs_decl void ccstructs_init_and_register_clean_handler (cce_destination_t L, ccstructs_clean_handler_t * H, ccstructs_dtor_T I)
  __attribute__((__nonnull__(1,2)));

ccstructs_decl void ccstructs_init_and_register_error_handler (cce_destination_t L, ccstructs_error_handler_t * H, ccstructs_dtor_T I)
  __attribute__((__nonnull__(1,2)));

#define ccstructs_init_and_register_handler(L,S_H,S)			\
  _Generic((S_H),							\
	   ccstructs_clean_handler_t	*: ccstructs_init_and_register_clean_handler, \
	   ccstructs_error_handler_t	*: ccstructs_init_and_register_error_handler)(L,S_H,S)


/** --------------------------------------------------------------------
 ** Trait: dumpable.
 ** ----------------------------------------------------------------- */

typedef struct ccstructs_dumpable_T				ccstructs_dumpable_T;
typedef struct ccname_trait_table_type(ccstructs_dumpable_T)	ccname_trait_table_type(ccstructs_dumpable_T);

struct ccstructs_dumpable_T {
  ccname_trait_table_type(ccstructs_dumpable_T)	const * methods;
  ccstructs_core_t				const * self;
};

/* Write the  struct to some output  channel.  Raise an exception  if an
   error occurs. */
typedef void ccname_trait_method_type(ccstructs_dumpable_T, dump) (cce_destination_t, ccstructs_dumpable_T const);

struct ccname_trait_table_type(ccstructs_dumpable_T) {
  ccname_trait_method_type(ccstructs_dumpable_T, dump)	* dump;
};

/* ------------------------------------------------------------------ */

__attribute__((__always_inline__,__nonnull__(1,2)))
static inline ccstructs_dumpable_T
ccname_new(ccstructs_dumpable_T) (ccstructs_core_t const * S, ccname_trait_table_type(ccstructs_dumpable_T) const * M)
{
  ccstructs_dumpable_T	I = {
    .methods	= M,
    .self	= S
  };
  return I;
}

__attribute__((__always_inline__,__pure__))
static inline ccstructs_core_t const *
ccstructs_dumpable_self (ccstructs_dumpable_T I)
{
  return I.self;
}

__attribute__((__nonnull__(1),__always_inline__))
static inline void
ccstructs_dumpable_dump (cce_destination_t L, ccstructs_dumpable_T const I)
{
  I.methods->dump(L, I);
}


/** --------------------------------------------------------------------
 ** Trait: serialise.
 ** ----------------------------------------------------------------- */

typedef struct ccstructs_serialiser_T				ccstructs_serialiser_T;
typedef struct ccname_trait_table_type(ccstructs_serialiser_T)	ccname_trait_table_type(ccstructs_serialiser_T);

struct ccstructs_serialiser_T {
  ccname_trait_table_type(ccstructs_serialiser_T)	const *	methods;
  ccstructs_core_t					const * self;
};

typedef size_t        ccname_trait_method_type(ccstructs_serialiser_T, required_size)
  (ccstructs_serialiser_T const I);
typedef ccmem_block_t ccname_trait_method_type(ccstructs_serialiser_T, write)
  (cce_destination_t L, ccstructs_serialiser_T const I, ccmem_block_t B);

struct ccname_trait_table_type(ccstructs_serialiser_T) {
  ccname_trait_method_type(ccstructs_serialiser_T, required_size)	* required_size;
  ccname_trait_method_type(ccstructs_serialiser_T, write)		* write;
};

/* ------------------------------------------------------------------ */

__attribute__((__always_inline__,__nonnull__(1,2)))
static inline ccstructs_serialiser_T
ccname_new(ccstructs_serialiser_T) (ccstructs_core_t const * const S, ccname_trait_table_type(ccstructs_serialiser_T) const * const M)
{
  ccstructs_serialiser_T	I = {
    .methods	= M,
    .self	= S
  };
  return I;
}

__attribute__((__always_inline__,__pure__))
static inline ccstructs_core_t const *
ccstructs_serialiser_self (ccstructs_serialiser_T const I)
{
  return I.self;
}

__attribute__((__always_inline__))
static inline size_t
ccstructs_serialiser_required_size (ccstructs_serialiser_T const I)
{
  return I.methods->required_size(I);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccmem_block_t
ccstructs_serialiser_write (cce_destination_t L, ccstructs_serialiser_T const I, ccmem_block_t B)
{
  return I.methods->write(L, I, B);
}


/** --------------------------------------------------------------------
 ** Trait: deserialise.
 ** ----------------------------------------------------------------- */

typedef struct ccstructs_deserialiser_T				ccstructs_deserialiser_T;
typedef struct ccname_trait_table_type(ccstructs_deserialiser_T)	ccname_trait_table_type(ccstructs_deserialiser_T);

struct ccstructs_deserialiser_T {
  ccname_trait_table_type(ccstructs_deserialiser_T)	const *	methods;
  ccstructs_core_t					const * self;
};

typedef size_t        ccname_trait_method_type(ccstructs_deserialiser_T, required_size)
  (ccstructs_deserialiser_T const I);
typedef ccmem_block_t ccname_trait_method_type(ccstructs_deserialiser_T, read)
  (cce_destination_t L, ccstructs_deserialiser_T I, ccmem_block_t B);

struct ccname_trait_table_type(ccstructs_deserialiser_T) {
  ccname_trait_method_type(ccstructs_deserialiser_T, required_size)	* required_size;
  ccname_trait_method_type(ccstructs_deserialiser_T, read)		* read;
};

/* ------------------------------------------------------------------ */

__attribute__((__always_inline__,__nonnull__(1,2)))
static inline ccstructs_deserialiser_T
ccname_new(ccstructs_deserialiser_T) (ccstructs_core_t const * const S, ccname_trait_table_type(ccstructs_deserialiser_T) const * const M)
{
  ccstructs_deserialiser_T	I = {
    .methods	= M,
    .self	= S
  };
  return I;
}

__attribute__((__always_inline__,__pure__))
static inline ccstructs_core_t const *
ccstructs_deserialiser_self (ccstructs_deserialiser_T const I)
{
  return I.self;
}

__attribute__((__always_inline__))
static inline size_t
ccstructs_deserialiser_required_size (ccstructs_deserialiser_T const I)
{
  return I.methods->required_size(I);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccmem_block_t
ccstructs_deserialiser_read (cce_destination_t L, ccstructs_deserialiser_T const I, ccmem_block_t B)
{
  return I.methods->read(L, I, B);
}


/** --------------------------------------------------------------------
 ** Trait: pathname.
 ** ----------------------------------------------------------------- */

typedef struct ccstructs_pathname_T				ccstructs_pathname_T;
typedef struct ccname_trait_table_type(ccstructs_pathname_T)	ccname_trait_table_type(ccstructs_pathname_T);

struct ccstructs_pathname_T {
  ccname_trait_table_type(ccstructs_pathname_T)	const *	methods;
  ccstructs_core_t				const * self;
};

typedef ccmem_asciiz_t ccname_trait_method_type(ccstructs_pathname_T, asciiz) (cce_destination_t L, ccstructs_pathname_T I);
typedef bool ccname_trait_method_type(ccstructs_pathname_T, is_static)     (ccstructs_pathname_T I);
typedef bool ccname_trait_method_type(ccstructs_pathname_T, is_absolute)   (cce_destination_t L, ccstructs_pathname_T I);
typedef bool ccname_trait_method_type(ccstructs_pathname_T, is_relative)   (cce_destination_t L, ccstructs_pathname_T I);
typedef bool ccname_trait_method_type(ccstructs_pathname_T, is_normalised) (cce_destination_t L, ccstructs_pathname_T I);
typedef bool ccname_trait_method_type(ccstructs_pathname_T, is_realpath)   (cce_destination_t L, ccstructs_pathname_T I);

typedef ccstructs_dtor_T ccname_trait_method_type(ccstructs_pathname_T, dtor) (ccstructs_pathname_T I);
typedef ccstructs_dumpable_T
  ccname_trait_method_type(ccstructs_pathname_T, dumpable)     (cce_destination_t L, ccstructs_pathname_T I);
typedef ccstructs_serialiser_T
  ccname_trait_method_type(ccstructs_pathname_T, serialiser)   (cce_destination_t L, ccstructs_pathname_T I);
typedef ccstructs_deserialiser_T
  ccname_trait_method_type(ccstructs_pathname_T, deserialiser) (cce_destination_t L, ccstructs_pathname_T I);

struct ccname_trait_table_type(ccstructs_pathname_T) {
  ccname_trait_method_type(ccstructs_pathname_T, asciiz)	* asciiz;
  ccname_trait_method_type(ccstructs_pathname_T, is_static)	* is_static;
  ccname_trait_method_type(ccstructs_pathname_T, is_absolute)   * is_absolute;
  ccname_trait_method_type(ccstructs_pathname_T, is_relative)   * is_relative;
  ccname_trait_method_type(ccstructs_pathname_T, is_normalised) * is_normalised;
  ccname_trait_method_type(ccstructs_pathname_T, is_realpath)   * is_realpath;

  ccname_trait_method_type(ccstructs_pathname_T, dtor)		* dtor;
  ccname_trait_method_type(ccstructs_pathname_T, dumpable)	* dumpable;
  ccname_trait_method_type(ccstructs_pathname_T, serialiser)	* serialiser;
  ccname_trait_method_type(ccstructs_pathname_T, deserialiser)	* deserialiser;
};

/* ------------------------------------------------------------------ */

__attribute__((__always_inline__,__nonnull__(1,2)))
static inline ccstructs_pathname_T
ccname_new(ccstructs_pathname_T) (ccstructs_core_t const * const S, ccname_trait_table_type(ccstructs_pathname_T) const * const M)
{
  ccstructs_pathname_T	I = {
    .methods	= M,
    .self	= S
  };
  return I;
}

__attribute__((__always_inline__,__pure__))
static inline ccstructs_core_t const *
ccstructs_pathname_self (ccstructs_pathname_T const I)
{
  return I.self;
}

__attribute__((__always_inline__))
static inline ccmem_asciiz_t
ccstructs_pathname_asciiz (cce_destination_t L, ccstructs_pathname_T const I)
{
  return I.methods->asciiz(L, I);
}

__attribute__((__always_inline__,__pure__))
static inline bool
ccstructs_pathname_is_static (ccstructs_pathname_T const I)
{
  return I.methods->is_static(I);
}

__attribute__((__always_inline__,__pure__))
static inline bool
ccstructs_pathname_is_absolute (cce_destination_t L, ccstructs_pathname_T const I)
{
  return I.methods->is_absolute(L, I);
}

__attribute__((__always_inline__,__pure__))
static inline bool
ccstructs_pathname_is_relative (cce_destination_t L, ccstructs_pathname_T const I)
{
  return I.methods->is_relative(L, I);
}

__attribute__((__always_inline__,__pure__))
static inline bool
ccstructs_pathname_is_normalised (cce_destination_t L, ccstructs_pathname_T const I)
{
  return I.methods->is_normalised(L, I);
}

__attribute__((__always_inline__,__pure__))
static inline bool
ccstructs_pathname_is_realpath (cce_destination_t L, ccstructs_pathname_T const I)
{
  return I.methods->is_realpath(L, I);
}

/* ------------------------------------------------------------------ */

__attribute__((__always_inline__))
static inline ccstructs_dtor_T
ccname_trait_new(ccstructs_dtor_T, ccstructs_pathname_T) (ccstructs_pathname_T const I)
{
  return I.methods->dtor(I);
}

__attribute__((__always_inline__))
static inline ccstructs_dumpable_T
ccname_trait_new(ccstructs_dumpable_T, ccstructs_pathname_T) (cce_destination_t L, ccstructs_pathname_T const I)
{
  return I.methods->dumpable(L, I);
}

__attribute__((__always_inline__))
static inline ccstructs_serialiser_T
ccname_trait_new(ccstructs_serialiser_T, ccstructs_pathname_T) (cce_destination_t L, ccstructs_pathname_T const I)
{
  return I.methods->serialiser(L, I);
}

__attribute__((__always_inline__))
static inline ccstructs_deserialiser_T
ccname_trait_new(ccstructs_deserialiser_T, ccstructs_pathname_T) (cce_destination_t L, ccstructs_pathname_T const I)
{
  return I.methods->deserialiser(L, I);
}


/** --------------------------------------------------------------------
 ** Simple implementation of file system pathname representation.
 ** ----------------------------------------------------------------- */

typedef struct ccstructs_pathname_t			ccstructs_pathname_t;
typedef struct ccname_table_type(ccstructs_pathname_t)	ccname_table_type(ccstructs_pathname_t);

struct ccstructs_pathname_t {
  ccname_table_type(ccstructs_pathname_t) const * methods;
  ccmem_asciiz_t	rep;
};

/* ------------------------------------------------------------------ */

ccstructs_decl void ccname_init(ccstructs_pathname_t, from_asciiz) (cce_destination_t L, ccstructs_pathname_t * ptn, ccmem_asciiz_t rep)
  __attribute__((__nonnull__(1,2)));

ccstructs_decl void ccname_init(ccstructs_pathname_t, from_ascii)  (cce_destination_t L, ccstructs_pathname_t * ptn, ccmem_ascii_t  rep)
  __attribute__((__nonnull__(1,2)));

ccstructs_decl void ccname_init(ccstructs_pathname_t, from_chars)  (cce_destination_t L, ccstructs_pathname_t * ptn, char const * P)
  __attribute__((__nonnull__(1,2)));

ccstructs_decl void ccname_init(ccstructs_pathname_t, copy) (cce_destination_t L, ccstructs_pathname_t * dst,
							     ccstructs_pathname_t const * src)
  __attribute__((__nonnull__(1,2,3)));

/* Initialisation  function  that  initialises  an already  allocated  struct.   This
   initialises in such a  way that it allows for both  finalisation and mutation from
   deserialisation. */
ccstructs_decl void ccname_init(ccstructs_pathname_t, deserialisable) (ccstructs_pathname_t * ptn)
  __attribute__((__nonnull__(1)));

/* ------------------------------------------------------------------ */

ccstructs_decl ccstructs_pathname_t const * ccname_new(ccstructs_pathname_t, from_asciiz) (cce_destination_t L, ccmem_asciiz_t rep)
  __attribute__((__nonnull__(1), __returns_nonnull__));

ccstructs_decl ccstructs_pathname_t const * ccname_new(ccstructs_pathname_t, from_ascii)  (cce_destination_t L, ccmem_ascii_t rep)
  __attribute__((__nonnull__(1), __returns_nonnull__));

ccstructs_decl ccstructs_pathname_t const * ccname_new(ccstructs_pathname_t, from_chars)  (cce_destination_t L, char const * P)
  __attribute__((__nonnull__(1,2), __returns_nonnull__));

ccstructs_decl ccstructs_pathname_t const * ccname_new(ccstructs_pathname_t, copy)  (cce_destination_t L, ccstructs_pathname_t const * src)
  __attribute__((__nonnull__(1,2), __returns_nonnull__));

/* Constructor function  that allocates  the struct  on the  heap using  the standard
   memory allocator implemented by CCMemory.  This  initialises in such a way that it
   allows for both finalisation and mutation from deserialisation. */
ccstructs_decl ccstructs_pathname_t * ccname_new(ccstructs_pathname_t, deserialisable) (cce_destination_t L)
  __attribute__((__nonnull__(1),__returns_nonnull__));

/* ------------------------------------------------------------------ */

ccstructs_decl void ccname_init(ccstructs_pathname_t, from_asciiz, guarded, clean) \
  (cce_destination_t L, ccstructs_clean_handler_t * H, ccstructs_pathname_t * const ptn, ccmem_asciiz_t const rep)
  __attribute__((__nonnull__(1,2,3)));

ccstructs_decl void ccname_init(ccstructs_pathname_t, from_asciiz, guarded, error) \
  (cce_destination_t L, ccstructs_error_handler_t * H, ccstructs_pathname_t * const ptn, ccmem_asciiz_t const rep)
  __attribute__((__nonnull__(1,2,3)));

ccstructs_decl void ccname_init(ccstructs_pathname_t, from_ascii, guarded, clean) \
  (cce_destination_t L, ccstructs_clean_handler_t * H, ccstructs_pathname_t * const ptn, ccmem_ascii_t const rep)
  __attribute__((__nonnull__(1,2,3)));

ccstructs_decl void ccname_init(ccstructs_pathname_t, from_ascii, guarded, error) \
  (cce_destination_t L, ccstructs_error_handler_t * H, ccstructs_pathname_t * const ptn, ccmem_ascii_t const rep)
  __attribute__((__nonnull__(1,2,3)));

ccstructs_decl void ccname_init(ccstructs_pathname_t, from_chars, guarded, clean) \
  (cce_destination_t L, ccstructs_clean_handler_t * H, ccstructs_pathname_t * const ptn, char const * const P)
  __attribute__((__nonnull__(1,2,3,4)));

ccstructs_decl void ccname_init(ccstructs_pathname_t, from_chars, guarded, error) \
  (cce_destination_t L, ccstructs_error_handler_t * H, ccstructs_pathname_t * const ptn, char const * const P)
  __attribute__((__nonnull__(1,2,3,4)));

ccstructs_decl void ccname_init(ccstructs_pathname_t, copy, guarded, clean) \
  (cce_destination_t L, ccstructs_clean_handler_t * H, ccstructs_pathname_t * const dst, ccstructs_pathname_t const * const src)
  __attribute__((__nonnull__(1,2,3,4)));

ccstructs_decl void ccname_init(ccstructs_pathname_t, copy, guarded, error) \
  (cce_destination_t L, ccstructs_error_handler_t * H, ccstructs_pathname_t * const dst, ccstructs_pathname_t const * const src)
  __attribute__((__nonnull__(1,2,3,4)));

/* ------------------------------------------------------------------ */

ccstructs_decl ccstructs_pathname_t const * ccname_new(ccstructs_pathname_t, from_asciiz, guarded, clean) \
  (cce_destination_t L, ccstructs_clean_handler_t * H, ccmem_asciiz_t const rep)
  __attribute__((__nonnull__(1,2), __returns_nonnull__));

ccstructs_decl ccstructs_pathname_t const * ccname_new(ccstructs_pathname_t, from_asciiz, guarded, error) \
  (cce_destination_t L, ccstructs_error_handler_t * H, ccmem_asciiz_t const rep)
  __attribute__((__nonnull__(1,2), __returns_nonnull__));

ccstructs_decl ccstructs_pathname_t const * ccname_new(ccstructs_pathname_t, from_ascii, guarded, clean) \
  (cce_destination_t L, ccstructs_clean_handler_t * H, ccmem_ascii_t const rep)
  __attribute__((__nonnull__(1,2), __returns_nonnull__));

ccstructs_decl ccstructs_pathname_t const * ccname_new(ccstructs_pathname_t, from_ascii, guarded, error) \
  (cce_destination_t L, ccstructs_error_handler_t * H, ccmem_ascii_t const rep)
  __attribute__((__nonnull__(1,2), __returns_nonnull__));

ccstructs_decl ccstructs_pathname_t const * ccname_new(ccstructs_pathname_t, from_chars, guarded, clean) \
  (cce_destination_t L, ccstructs_clean_handler_t * H, char const * const P)
  __attribute__((__nonnull__(1,2,3), __returns_nonnull__));

ccstructs_decl ccstructs_pathname_t const * ccname_new(ccstructs_pathname_t, from_chars, guarded, error) \
  (cce_destination_t L, ccstructs_error_handler_t * H, char const * const P)
  __attribute__((__nonnull__(1,2,3), __returns_nonnull__));

ccstructs_decl ccstructs_pathname_t const * ccname_new(ccstructs_pathname_t, copy, guarded, clean) \
  (cce_destination_t L, ccstructs_clean_handler_t * H, ccstructs_pathname_t const * const src)
  __attribute__((__nonnull__(1,2,3), __returns_nonnull__));

ccstructs_decl ccstructs_pathname_t const * ccname_new(ccstructs_pathname_t, copy, guarded, error) \
  (cce_destination_t L, ccstructs_error_handler_t * H, ccstructs_pathname_t const * const src)
  __attribute__((__nonnull__(1,2,3), __returns_nonnull__));

/* ------------------------------------------------------------------ */

/* Type  of  trait  constructor.   Functions  of this  type  build  instances  of
   "ccstructs_dtor_T" implemented by "ccstructs_pathname_t". */
typedef ccstructs_dtor_T ccname_trait_new_type(ccstructs_dtor_T, ccstructs_pathname_t) (ccstructs_pathname_t const * ptn);

/* Trait    constructor     for    "ccstructs_dtor_T"    as     implemented    by
   "ccstructs_pathname_t".   The returned  destructor  trait will  work for  both
   embedded and standalone instances of "ccstructs_pathname_t". */
ccstructs_decl ccname_trait_new_type(ccstructs_dtor_T, ccstructs_pathname_t) ccname_trait_new(ccstructs_dtor_T, ccstructs_pathname_t)
  __attribute__((__nonnull__(1)));

/* ------------------------------------------------------------------ */

/* Type  of  trait  constructor.   Functions  of this  type  build  instances  of
   "ccstructs_pathname_T" implemented by "ccstructs_pathname_t". */
typedef ccstructs_pathname_T ccname_trait_new_type(ccstructs_pathname_T, ccstructs_pathname_t) (ccstructs_pathname_t const * ptn);

/* Trait    constructor   for    "ccstructs_pathname_T"    as   implemented    by
   "ccstructs_pathname_t". */
ccstructs_decl ccname_trait_new_type(ccstructs_pathname_T, ccstructs_pathname_t) ccname_trait_new(ccstructs_pathname_T, ccstructs_pathname_t)
  __attribute__((__nonnull__(1)));

/* ------------------------------------------------------------------ */

/* Type  of  trait  constructor.   Functions  of this  type  build  instances  of
   "ccstructs_dumpable_T" implemented by "ccstructs_pathname_t". */
typedef ccstructs_dumpable_T ccname_trait_new_type(ccstructs_dumpable_T, ccstructs_pathname_t) (ccstructs_pathname_t const * ptn);

/* Constructor  for   a  "ccstructs_dumpable_T"   trait  that  prints   a  struct
   representation on some output channel. */
ccstructs_decl ccname_trait_new_type(ccstructs_dumpable_T, ccstructs_pathname_t) ccname_trait_new(ccstructs_dumpable_T, ccstructs_pathname_t)
  __attribute__((__nonnull__(1)));

/* ------------------------------------------------------------------ */

/* Type  of  trait  constructor.   Functions  of this  type  build  instances  of
   "ccstructs_serialiser_T" implemented by "ccstructs_pathname_t". */
typedef ccstructs_serialiser_T ccname_trait_new_type(ccstructs_serialiser_T, ccstructs_pathname_t) (ccstructs_pathname_t const * ptn);

/* Type  of  trait  constructor.   Functions  of this  type  build  instances  of
   "ccstructs_deserialiser_T" implemented by "ccstructs_pathname_t". */
typedef ccstructs_deserialiser_T ccname_trait_new_type(ccstructs_deserialiser_T, ccstructs_pathname_t) (ccstructs_pathname_t * ptn);

/* Constructor for a "ccstructs_serialiser_T" trait that serialises an instance of
   "ccstructs_pathname_t" into a memory block. */
ccstructs_decl ccname_trait_new_type(ccstructs_serialiser_T, ccstructs_pathname_t)
  ccname_trait_new(ccstructs_serialiser_T, ccstructs_pathname_t)
  __attribute__((__nonnull__(1)));

/* Constructor  for  a  "ccstructs_deserialiser_T"   trait  that  deserialises  an
   instance of "ccstructs_pathname_t" from a memory block. */
ccstructs_decl ccname_trait_new_type(ccstructs_deserialiser_T, ccstructs_pathname_t)
  ccname_trait_new(ccstructs_deserialiser_T, ccstructs_pathname_t)
  __attribute__((__nonnull__(1)));


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* CCSTRUCTS_H */

/* end of file */
