/*
  Part of: CCStructs
  Contents: public header file
  Date: Apr 30, 2018

  Abstract

	This file must be included in all the source files making use of
	CCStructs.

  Copyright (C) 2018 Marco Maggi <marco.maggi-ipsu@poste.it>

  This program is  free software: you can redistribute  it and/or modify
  it  under the  terms  of  the GNU  Lesser  General  Public License  as
  published by  the Free  Software Foundation, either  version 3  of the
  License, or (at your option) any later version.

  This program  is distributed in the  hope that it will  be useful, but
  WITHOUT   ANY  WARRANTY;   without  even   the  implied   warranty  of
  MERCHANTABILITY  or FITNESS  FOR A  PARTICULAR PURPOSE.   See  the GNU
  General Public License for more details.

  You  should have received  a copy  of the  GNU General  Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CCSTRUCTS_H
#define CCSTRUCTS_H 1


/** --------------------------------------------------------------------
 ** Preliminary definitions.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif

/* The  macro  CCSTRUCTS_UNUSED  indicates  that a  function,  function
   argument or variable may potentially be unused. Usage examples:

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

struct ccstructs_core_t;

#define ccstructs_core(S)	((ccstructs_core_t *)(S))


/** --------------------------------------------------------------------
 ** Generic struct handling: destructors interface.
 ** ----------------------------------------------------------------- */

typedef struct ccstructs_dtors_I_methods_t	ccstructs_dtors_I_methods_t;
typedef struct ccstructs_dtors_I		ccstructs_dtors_I;

struct ccstructs_dtors_I {
  ccstructs_dtors_I_methods_t const	* methods;
  ccstructs_core_t			* self;
};

/* Release the memory allocated for the struct, if needed. */
typedef void ccstructs_dtors_I_delete_fun_t (ccstructs_dtors_I I);

/* Release all  the asynchronous  resources owned by  the fields  of the
   struct, if any. */
typedef void ccstructs_dtors_I_final_fun_t (ccstructs_dtors_I I);

struct ccstructs_dtors_I_methods_t {
  ccstructs_dtors_I_delete_fun_t	* delete;
  ccstructs_dtors_I_final_fun_t	* final;
};

/* ------------------------------------------------------------------ */

__attribute__((__always_inline__,__nonnull__(1,2)))
static inline ccstructs_dtors_I
ccstructs_new_dtors (ccstructs_core_t * S, ccstructs_dtors_I_methods_t const * const M)
{
  ccstructs_dtors_I	I = {
    .methods	= M,
    .self	= S
  };
  return I;
}

__attribute__((__always_inline__,__pure__))
static inline ccstructs_core_t *
ccstructs_dtors_self (ccstructs_dtors_I I)
{
  return I.self;
}

__attribute__((__always_inline__))
static inline void
ccstructs_dtors_final (ccstructs_dtors_I I)
{
  I.methods->final(I);
}

__attribute__((__always_inline__))
static inline void
ccstructs_dtors_delete (ccstructs_dtors_I I)
{
  I.methods->final(I);
  I.methods->delete(I);
}


/** --------------------------------------------------------------------
 ** Generic struct handling: exception handlers.
 ** ----------------------------------------------------------------- */

typedef struct ccstructs_clean_handler_t	ccstructs_clean_handler_t;
typedef struct ccstructs_error_handler_t	ccstructs_error_handler_t;

struct ccstructs_clean_handler_t {
  cce_clean_handler_t	handler;
  ccstructs_dtors_I	dtors;
};

struct ccstructs_error_handler_t {
  cce_error_handler_t	handler;
  ccstructs_dtors_I	dtors;
};

ccstructs_decl void ccstructs_clean_handler_init (cce_destination_t L, ccstructs_clean_handler_t * H, ccstructs_dtors_I I)
  __attribute__((__nonnull__(1,2)));

ccstructs_decl void ccstructs_error_handler_init (cce_destination_t L, ccstructs_error_handler_t * H, ccstructs_dtors_I I)
  __attribute__((__nonnull__(1,2)));

#define ccstructs_handler_init(L,S_H,S)		\
  _Generic((S_H),							\
	   ccstructs_clean_handler_t	*: ccstructs_clean_handler_init, \
	   ccstructs_error_handler_t	*: ccstructs_error_handler_init)(L,S_H,S)


/** --------------------------------------------------------------------
 ** Generic struct handling: input/output writability.
 ** ----------------------------------------------------------------- */

typedef struct ccstructs_writable_I		ccstructs_writable_I;
typedef struct ccstructs_writable_I_methods_t	ccstructs_writable_I_methods_t;

struct ccstructs_writable_I {
  ccstructs_writable_I_methods_t	const * methods;
  ccstructs_core_t			const * self;
};

/* Write the  struct to some output  channel.  Raise an exception  if an
   error occurs. */
typedef void ccstructs_writable_I_write_fun_t (cce_destination_t, ccstructs_writable_I const);

struct ccstructs_writable_I_methods_t {
  ccstructs_writable_I_write_fun_t		* write;
};

/* ------------------------------------------------------------------ */

__attribute__((__always_inline__,__nonnull__(1,2)))
static inline ccstructs_writable_I
ccstructs_new_writable (ccstructs_core_t * S, ccstructs_writable_I_methods_t const * const M)
{
  ccstructs_writable_I	I = {
    .methods	= M,
    .self	= S
  };
  return I;
}

__attribute__((__always_inline__,__pure__))
static inline ccstructs_core_t const *
ccstructs_writable_self (ccstructs_writable_I I)
{
  return I.self;
}

__attribute__((__nonnull__(1),__always_inline__))
static inline void
ccstructs_writable_write (cce_destination_t L, ccstructs_writable_I const I)
{
  I.methods->write(L, I);
}


/** --------------------------------------------------------------------
 ** Interface: serialisable.
 ** ----------------------------------------------------------------- */

typedef struct ccstructs_serialisable_I			ccstructs_serialisable_I;
typedef struct ccstructs_serialisable_I_methods_t	ccstructs_serialisable_I_methods_t;

struct ccstructs_serialisable_I {
  ccstructs_serialisable_I_methods_t	const *	methods;
  ccstructs_core_t			const * self;
};

typedef size_t ccstructs_serialisable_I_minimum_size_fun_t (ccstructs_serialisable_I const I);
typedef ccmem_block_t ccstructs_serialisable_I_to_block_fun_t   (cce_destination_t L, ccstructs_serialisable_I const I, ccmem_block_t B);
typedef ccmem_block_t ccstructs_serialisable_I_from_block_fun_t (cce_destination_t L, ccstructs_serialisable_I const I, ccmem_block_t B);

struct ccstructs_serialisable_I_methods_t {
  ccstructs_serialisable_I_minimum_size_fun_t *	minimum_size;
  ccstructs_serialisable_I_to_block_fun_t *	to_block;
  ccstructs_serialisable_I_from_block_fun_t *	from_block;
};

/* ------------------------------------------------------------------ */

__attribute__((__always_inline__,__nonnull__(1,2)))
static inline ccstructs_serialisable_I
ccstructs_new_serialisable (ccstructs_core_t * S, ccstructs_serialisable_I_methods_t const * const M)
{
  ccstructs_serialisable_I	I = {
    .methods	= M,
    .self	= S
  };
  return I;
}

__attribute__((__always_inline__,__pure__))
static inline ccstructs_core_t const *
ccstructs_serialisable_self (ccstructs_serialisable_I const I)
{
  return I.self;
}

__attribute__((__always_inline__))
static inline size_t
ccstructs_serialisable_minimum_size (ccstructs_serialisable_I const I)
{
  return I.methods->minimum_size(I);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccmem_block_t
ccstructs_serialisable_to_block (cce_destination_t L, ccstructs_serialisable_I const I, ccmem_block_t B)
{
  return I.methods->to_block(L, I, B);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccmem_block_t
ccstructs_serialisable_from_block (cce_destination_t L, ccstructs_serialisable_I const I, ccmem_block_t B)
{
  return I.methods->from_block(L, I, B);
}


/** --------------------------------------------------------------------
 ** Interface: pathname.
 ** ----------------------------------------------------------------- */

typedef struct ccstructs_pathname_I		ccstructs_pathname_I;
typedef struct ccstructs_pathname_I_methods_t	ccstructs_pathname_I_methods_t;

struct ccstructs_pathname_I {
  ccstructs_pathname_I_methods_t	const *	methods;
  ccstructs_core_t			const * self;
};

typedef size_t		ccstructs_pathname_I_length_fun_t	(cce_destination_t L, ccstructs_pathname_I const I);
typedef char const *	ccstructs_pathname_I_pointer_fun_t	(cce_destination_t L, ccstructs_pathname_I const I);
typedef bool		ccstructs_pathname_I_is_static_fun_t	(ccstructs_pathname_I const I);

struct ccstructs_pathname_I_methods_t {
  ccstructs_pathname_I_length_fun_t	* length;
  ccstructs_pathname_I_pointer_fun_t	* pointer;
  ccstructs_pathname_I_is_static_fun_t	* is_static;
};

/* ------------------------------------------------------------------ */

__attribute__((__always_inline__,__nonnull__(1,2)))
static inline ccstructs_pathname_I
ccstructs_new_pathname (ccstructs_core_t const * S, ccstructs_pathname_I_methods_t const * const M)
{
  ccstructs_pathname_I	I = {
    .methods	= M,
    .self	= S
  };
  return I;
}

__attribute__((__always_inline__,__pure__))
static inline ccstructs_core_t const *
ccstructs_pathname_self (ccstructs_pathname_I const I)
{
  return I.self;
}

__attribute__((__always_inline__))
static inline size_t
ccstructs_pathname_length (cce_destination_t L, ccstructs_pathname_I const I)
{
  return I.methods->length(L, I);
}

__attribute__((__always_inline__))
static inline char const *
ccstructs_pathname_pointer (cce_destination_t L, ccstructs_pathname_I const I)
{
  return I.methods->pointer(L, I);
}

__attribute__((__always_inline__,__pure__))
static inline bool
ccstructs_pathname_is_static (ccstructs_pathname_I const I)
{
  return I.methods->is_static(I);
}

/* ------------------------------------------------------------------ */
/* simple implementation for statically allocated strings */

ccstructs_decl ccstructs_pathname_I ccstructs_new_pathname_from_static_string (const char * ptn)
  __attribute__((__nonnull__(1)));

ccstructs_decl ccstructs_pathname_I ccstructs_new_pathname_from_dynamic_string (const char * ptn)
  __attribute__((__nonnull__(1)));

ccstructs_decl ccstructs_pathname_I ccstructs_new_pathname_from_static_asciiz (ccmem_asciiz_t const * ptn);

ccstructs_decl ccstructs_pathname_I ccstructs_new_pathname_from_dynamic_asciiz (ccmem_asciiz_t const * ptn);


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* CCSTRUCTS_H */

/* end of file */
