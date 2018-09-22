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
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


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
 ** Memory handling: blocks.
 ** ----------------------------------------------------------------- */

typedef struct ccstructs_block_t {
  size_t	len;
  uint8_t *	ptr;
} ccstructs_block_t;

#if 0

static inline __attribute__((__always_inline__,__nonnull__))
void
ccstructs_block_set (ccstructs_block_t * block, void * p, size_t len)
{
  block->ptr = p;
  block->len = len;
}
static inline __attribute__((__always_inline__,__nonnull__))
void
ccstructs_block_reset (ccstructs_block_t * block)
{
  block->ptr = NULL;
  block->len = 0;
}
static inline __attribute__((__always_inline__))
ccstructs_bool_t
ccstructs_block_is_null (ccstructs_block_t block)
{
  return (NULL == block.ptr);
}
static inline __attribute__((__always_inline__))
void
ccstructs_block_clean_memory (ccstructs_block_t block)
{
  memset(block.ptr, '\0', block.len);
}
static inline __attribute__((__always_inline__))
ccstructs_block_t
ccstructs_block_alloc (ccstructs_memory_allocator_t allocator, size_t dim)
{
  ccstructs_block_t	block = { .ptr = NULL, .len = dim };
  allocator.alloc(allocator.data, &(block.ptr), dim);
  return block;
}
static inline __attribute__((__always_inline__))
ccstructs_block_t
ccstructs_block_realloc (ccstructs_memory_allocator_t allocator, ccstructs_block_t block, size_t new_dim)
{
  allocator.alloc(allocator.data, &(block.ptr), new_dim);
  block.len = new_dim;
  return block;
}
static inline __attribute__((__always_inline__))
void
ccstructs_block_free (ccstructs_memory_allocator_t allocator, ccstructs_block_t block)
{
  if (block.ptr)
    allocator.alloc(allocator.data, &(block.ptr), 0);
}
static inline void
ccstructs_block_shift_x (ccstructs_block_t * block, ssize_t offset, size_t dim)
{
  if (dim) {
    if (1 != dim) {
      block->ptr += offset;
      block->len -= offset;
    } else {
      block->ptr += offset * dim;
      block->len -= offset * dim;
    }
  }
}
static inline ccstructs_block_t
ccstructs_block_shift (ccstructs_block_t A, ssize_t offset, size_t dim)
{
  ccstructs_block_t	B;
  if (dim) {
    if (1 != dim) {
      B.ptr = A.ptr + offset;
      B.len = A.len + offset;
    } else {
      B.ptr = A.ptr + offset * dim;
      B.len = A.len + offset * dim;
    }
  } else {
    B = A;
  }
  return B;
}
static inline __attribute__((__always_inline__))
ccstructs_block_t
ccstructs_block_difference (ccstructs_block_t A, ccstructs_block_t B)
{
  ccstructs_block_t	C = { .ptr = A.ptr, .len = B.ptr - A.ptr };
  return C;
}

#endif


/** ------------------------------------------------------------
 ** Memory handling: ASCII-coded, zero-terminated strings.
 ** ----------------------------------------------------------*/

typedef struct ccstructs_ascii_t {
  size_t	len;
  char *	ptr;
} ccstructs_ascii_t;

typedef struct ccstructs_ascii_list_t {
  size_t	len;
  char **	ptr;
} ccstructs_ascii_list_t;

#if 0

extern const ccstructs_ascii_t ccstructs_ascii_empty;

/* ------------------------------------------------------------ */

static inline __attribute__((__always_inline__,__nonnull__))
void
ccstructs_ascii_set (ccstructs_ascii_t * ascii, void * ptr, size_t len)
{
  ascii->ptr = ptr;
  ascii->len = len;
}
static inline __attribute__((__always_inline__,__nonnull__))
void
ccstructs_ascii_reset (ccstructs_ascii_t * ascii)
{
  ascii->ptr = NULL;
  ascii->len = 0;
}
static inline __attribute__((__always_inline__,__nonnull__))
ccstructs_ascii_t
ccstructs_ascii_const (char * string)
{
  ccstructs_ascii_t	ascii;
  ascii.ptr = (void *)string;
  ascii.len = strlen(string);
  return ascii;
}
static inline __attribute__((__always_inline__,__nonnull__))
ccstructs_bool_t
ccstructs_ascii_is_null (ccstructs_ascii_t ascii)
{
  return (NULL == ascii.ptr);
}
static inline __attribute__((__always_inline__,__nonnull__))
ccstructs_bool_t
ccstructs_ascii_is_terminated (ccstructs_ascii_t ascii)
{
  return ('\0' == ascii.ptr[ascii.len]);
}
static inline __attribute__((__always_inline__,__nonnull__))
void
ccstructs_ascii_clean_memory (ccstructs_ascii_t ascii)
{
  memset(ascii.ptr,'\0',ascii.len);
  ascii.ptr[ascii.len] = '\0';
}
static inline __attribute__((__always_inline__,__nonnull__))
void
ccstructs_ascii_terminate (ccstructs_ascii_t ascii)
{
  ascii.ptr[ascii.len] = '\0';
}
static inline __attribute__((__always_inline__,__nonnull__))
ccstructs_ascii_t
ccstructs_ascii_from_block (ccstructs_block_t block)
{
  ccstructs_ascii_t	ascii;

  ascii.len = block.len - 1;
  ascii.ptr = (void *)block.ptr;
  ascii.ptr[block.len] = '\0';
  return ascii;
}
static inline __attribute__((__always_inline__,__nonnull__))
ccstructs_block_t
ccstructs_block_from_ascii (ccstructs_ascii_t ascii)
{
  ccstructs_block_t	block;

  block.len = 1 + ascii.len;
  block.ptr = (void *)ascii.ptr;
  return block;
}

/* ------------------------------------------------------------ */

static inline __attribute__((__always_inline__,__nonnull__))
ccstructs_ascii_t
ccstructs_ascii_alloc (ccstructs_memory_allocator_t allocator, size_t dim)
{
  ccstructs_ascii_t	ascii = { .ptr = NULL };

  allocator.alloc(allocator.data, &(ascii.ptr), 1+dim);
  ascii.len = dim;
  ascii.ptr[dim]='\0';
  return ascii;
}
static inline __attribute__((__always_inline__,__nonnull__))
ccstructs_ascii_t
ccstructs_ascii_realloc (ccstructs_memory_allocator_t allocator,
		   ccstructs_ascii_t ascii, size_t new_dim)
{
  allocator.alloc(allocator.data, &(ascii.ptr), 1+new_dim);
  ascii.len = new_dim;
  ascii.ptr[new_dim]='\0';
  return ascii;
}
static inline __attribute__((__always_inline__,__nonnull__))
void
ccstructs_ascii_free (ccstructs_memory_allocator_t allocator, ccstructs_ascii_t ascii)
{
  if (ascii.ptr)
    allocator.alloc(allocator.data, &(ascii.ptr), 0);
}

#endif


/** --------------------------------------------------------------------
 ** Generic struct wrapper.
 ** ----------------------------------------------------------------- */

typedef struct ccstructs_core_t		ccstructs_core_t;

struct ccstructs_core_t;


/** --------------------------------------------------------------------
 ** Generic struct handling: core interface.
 ** ----------------------------------------------------------------- */

typedef struct ccstructs_core_iface_methods_t		ccstructs_core_iface_methods_t;
typedef struct ccstructs_core_iface_t			ccstructs_core_iface_t;

struct ccstructs_core_iface_t {
  ccstructs_core_iface_methods_t const	* methods;
  ccstructs_core_t			* self;
};

/* Release the memory allocated for the struct, if needed. */
typedef void ccstructs_core_iface_delete_fun_t (ccstructs_core_iface_t I);

/* Release all  the asynchronous  resources owned by  the fields  of the
   struct, if any. */
typedef void ccstructs_core_iface_final_fun_t (ccstructs_core_iface_t I);

struct ccstructs_core_iface_methods_t {
  ccstructs_core_iface_delete_fun_t	* delete;
  ccstructs_core_iface_final_fun_t	* final;
};

/* ------------------------------------------------------------------ */

__attribute__((__always_inline__))
static inline void
ccstructs_core_final (ccstructs_core_iface_t I)
{
  I.methods->final(I);
}

__attribute__((__always_inline__))
static inline void
ccstructs_core_delete (ccstructs_core_iface_t I)
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
  cce_clean_handler_t		handler;
  ccstructs_core_iface_t	core;
};

struct ccstructs_error_handler_t {
  cce_error_handler_t		handler;
  ccstructs_core_iface_t	core;
};

ccstructs_decl void ccstructs_clean_handler_init (cce_destination_t L, ccstructs_clean_handler_t * H, ccstructs_core_iface_t I)
  __attribute__((__nonnull__(1,2)));

ccstructs_decl void ccstructs_error_handler_init (cce_destination_t L, ccstructs_error_handler_t * H, ccstructs_core_iface_t I)
  __attribute__((__nonnull__(1,2)));

#define ccstructs_handler_init(L,S_H,S)		\
  _Generic((S_H),							\
	   ccstructs_clean_handler_t	*: ccstructs_clean_handler_init, \
	   ccstructs_error_handler_t	*: ccstructs_error_handler_init)(L,S_H,S)


/** --------------------------------------------------------------------
 ** Generic struct handling: input/output writability.
 ** ----------------------------------------------------------------- */

typedef struct ccstructs_writable_iface_t		ccstructs_writable_iface_t;
typedef struct ccstructs_writable_iface_methods_t	ccstructs_writable_iface_methods_t;

struct ccstructs_writable_iface_t {
  ccstructs_writable_iface_methods_t const	* methods;
  ccstructs_core_t const			* self;
};

/* Serialise the struct  to the stream.  Raise an exception  if an error
   occurs. */
typedef void ccstructs_writable_iface_fwrite_fun_t (cce_destination_t, FILE *, ccstructs_writable_iface_t const);

struct ccstructs_writable_iface_methods_t {
  ccstructs_writable_iface_fwrite_fun_t		* fwrite;
};

/* ------------------------------------------------------------------ */


__attribute__((__nonnull__(1,2),__always_inline__))
static inline void
ccstructs_writable_fwrite (cce_destination_t L, FILE * stream, ccstructs_writable_iface_t const I)
{
  I.methods->fwrite(L, stream, I);
}


/** --------------------------------------------------------------------
 ** Interface: serialisable.
 ** ----------------------------------------------------------------- */

#if 0

typedef struct ccstructs_serialisable_t		ccstructs_serialisable_t;
typedef struct ccstructs_serialisable_methods_t	ccstructs_serialisable_methods_t;

typedef void ccstructs_serialise_to_buffer_fun_t (cce_destination_t L, ccstructs_serialisable_t const * S, uint8_t * buf, size_t len);
typedef void ccstructs_serialise_to_ascii_fun_t  (cce_destination_t L, ccstructs_serialisable_t const * S, uint8_t * buf, size_t len);
typedef void ccstructs_serialise_to_asciiz_fun_t (cce_destination_t L, ccstructs_serialisable_t const * S, uint8_t * buf, size_t len);

struct ccstructs_serialisable_methods_t {
  ccstructs_serialise_to_buffer_fun_t *		serialise_to_buffer;
  ccstructs_serialise_to_ascii_fun_t *		serialise_to_ascii;
  ccstructs_serialise_to_asciiz_fun_t *		serialise_to_asciiz;
};

struct ccstructs_serialisable_t {
  ccstructs_serialisable_methods_t *	methods;
  void *				stru;
};

ccstructs_decl void ccstructs_serialise_to_buffer (cce_destination_t L, ccstructs_serialisable_t const * const S,
						   uint8_t * buf, size_t len)
  __attribute__((__nonnull__(1,2,3)));

#endif


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* CCSTRUCTS_H */

/* end of file */
