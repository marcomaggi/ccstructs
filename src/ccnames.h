/*
  Part of: CCStructs
  Contents: preprocessor macros to define common API names
  Date: Tue Jan  1, 2019

  Abstract



  Copyright (C) 2019 Marco Maggi <marco.maggi-ipsu@poste.it>

  This is free software; you  can redistribute it and/or modify it under
  the terms of the GNU Lesser General Public License as published by the
  Free Software  Foundation; either version  3.0 of the License,  or (at
  your option) any later version.

  This library  is distributed in the  hope that it will  be useful, but
  WITHOUT   ANY  WARRANTY;   without  even   the  implied   warranty  of
  MERCHANTABILITY  or FITNESS  FOR A  PARTICULAR PURPOSE.   See  the GNU
  Lesser General Public License for more details.

  You  should have  received a  copy of  the GNU  Lesser  General Public
  License along  with this library; if  not, write to  the Free Software
  Foundation, Inc.,  59 Temple Place,  Suite 330, Boston,  MA 02111-1307
  USA.

*/

#ifndef CCNAMES_H
#define CCNAMES_H 1


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

//#include <ccexceptions.h>


/** --------------------------------------------------------------------
 ** Variadic macros mechanism.
 ** ----------------------------------------------------------------- */

/* The  following  macros are  adapted  from  Stack Overflow  (URL  last
 * accessed Jan 2, 2019):
 *
 *   <https://stackoverflow.com/a/26408195>
 */

/* The macro use:
 *
 *   CCNAMES__NARG__(__VA_ARGS__)
 *
 * expands into the number of arguments in __VA_ARGS__.
 */
#define CCNAMES__NARG__(...)	CCNAMES__NARG_I_(__VA_ARGS__,CCNAMES__RSEQ_N())
#define CCNAMES__NARG_I_(...)	CCNAMES__ARG_N(__VA_ARGS__)
#define CCNAMES__ARG_N( \
      _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
     _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
     _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
     _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
     _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
     _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
     _61,_62,_63,N,...)		N
#define CCNAMES__RSEQ_N() \
     63,62,61,60,                   \
     59,58,57,56,55,54,53,52,51,50, \
     49,48,47,46,45,44,43,42,41,40, \
     39,38,37,36,35,34,33,32,31,30, \
     29,28,27,26,25,24,23,22,21,20, \
     19,18,17,16,15,14,13,12,11,10, \
     9,8,7,6,5,4,3,2,1,0

/* The macro uses:
 *
 *    CCNAMES_VFUNC(ccname_new, alpha)
 *    CCNAMES_VFUNC(ccname_new, alpha, beta)
 *
 * respectively expand into:
 *
 *    ccname_new_1(alpha)
 *    ccname_new_2(alpha, beta)
 *
 */
#define CCNAMES___VFUNC(NAME, N)	NAME ## _ ## N
#define CCNAMES__VFUNC(NAME, N)		CCNAMES___VFUNC(NAME, N)
#define CCNAMES_VFUNC(FUNC, ...)	CCNAMES__VFUNC(FUNC, CCNAMES__NARG__(__VA_ARGS__))(__VA_ARGS__)


/** --------------------------------------------------------------------
 ** Name definitions.
 ** ----------------------------------------------------------------- */

/* Given   a  struct   type  name   and  a   (possibly  empty)   variant
   specification: expand into the name of the API function "new()". */
#define CCNAME_NEW(STRUCT_TYPE, VARIANT)	STRUCT_TYPE ## __ ## VARIANT ## __new

/* Given a  struct type name: expand  into the name of  the API function
   "delete()". */
#define CCNAME_DELETE(STRUCT_TYPE)		STRUCT_TYPE ## __delete

/* Given   a  struct   type  name   and  a   (possibly  empty)   variant
   specification: expand into the name of the API function "init()". */
#define CCNAME_INIT(STRUCT_TYPE, VARIANT)	STRUCT_TYPE ## __ ## VARIANT ## __init

/* Given a  struct type name: expand  into the name of  the API function
   "final()". */
#define CCNAME_FINAL(STRUCT_TYPE)		STRUCT_TYPE ## __final

/* Given a  struct type name: expand  into the name of  the API function
   "release()". */
#define CCNAME_RELEASE(STRUCT_TYPE)		STRUCT_TYPE ## __release

/* Given a struct  type name: expand into the name  of the methods table
   type for the struct type. */
#define CCNAME_TABLE_T(STRUCT_TYPE)		STRUCT_TYPE ## __methods_table_t

/* Given   a  struct   type  name   and  a   (possibly  empty)   variant
   specification: expand  into the  name of the  methods table  for that
   type. */
#define CCNAME_TABLE(STRUCT_TYPE, VARIANT)	STRUCT_TYPE ## __ ## VARIANT ## __methods_table

/* Given an  interface type name,  a struct  type name, and  a (possibly
   empty)  variant  specification:  expand  into the  name  of  the  API
   function "new()"  used to instantiate  that variant of  the interface
   type for that struct type. */
#define CCNAME_IFACE_NEW(IFACE_TYPE, STRUCT_TYPE, VARIANT)	\
  CCNAME_NEW(IFACE_TYPE ## __ ## STRUCT_TYPE, VARIANT)

/* Given an  interface type name,  a struct  type name, and  a (possibly
   empty) variant  specification: expand  into the  name of  the methods
   table for that variant of the interface implementation for the struct
   type. */
#define CCNAME_IFACE_TABLE(IFACE_TYPE, STRUCT_TYPE, VARIANT)	\
  CCNAME_TABLE(IFACE_TYPE ## __ ## STRUCT_TYPE, VARIANT)

/* Given an interface type name, a  struct type name, a (possibly empty)
   variant specification, and a method name: expand into the name of the
   method function for that variant  of the interface implementation for
   the struct type. */
#define CCNAME_IFACE_METHOD(IFACE_TYPE, STRUCT_TYPE, VARIANT, METHOD_NAME)	\
  IFACE_TYPE ## __ ## STRUCT_TYPE ## __ ## VARIANT ## __method__ ## METHOD_NAME


/** --------------------------------------------------------------------
 ** Function invocations.
 ** ----------------------------------------------------------------- */

/* Given a struct type name, a variant specification, a (possibly empty)
   variant  specification, and  a  (possibly empty)  list of  arguments:
   expand into the invocation of the API function "new()". */
#define ccname_new_1(STRUCT_TYPE)		CCNAME_NEW(STRUCT_TYPE, )
#define ccname_new_2(STRUCT_TYPE, VARIANT)	CCNAME_NEW(STRUCT_TYPE, VARIANT)
#define ccname_new(...)				CCNAMES_VFUNC(ccname_new, __VA_ARGS__)

/* Given a struct type name and an expression evaluating to a pointer to
   the struct instance:  expand into the invocation of  the API function
   "delete()". */
#define ccname_delete(STRUCT_TYPE)		CCNAME_DELETE(STRUCT_TYPE)

/* Given a struct type name, a variant specification, a (possibly empty)
   variant  specification, and  a  (possibly empty)  list of  arguments:
   expand into the invocation of the API function "init()". */
#define ccname_init_1(STRUCT_TYPE)		CCNAME_INIT(STRUCT_TYPE, )
#define ccname_init_2(STRUCT_TYPE, VARIANT)	CCNAME_INIT(STRUCT_TYPE, VARIANT)
#define ccname_init(...)			CCNAMES_VFUNC(ccname_init, __VA_ARGS__)

/* Given a struct type name and an expression evaluating to a pointer to
   the struct instance:  expand into the invocation of  the API function
   "final()". */
#define ccname_final(STRUCT_TYPE)		CCNAME_FINAL(STRUCT_TYPE)

/* Given a struct type name and an expression evaluating to a pointer to
   the struct instance:  expand into the invocation of  the API function
   "release()". */
#define ccname_release(STRUCT_TYPE)		CCNAME_RELEASE(STRUCT_TYPE)

/* Given a struct  type name: expand into the name  of the methods table
   type for the struct type. */
#define ccname_table_type(STRUCT_TYPE)		CCNAME_TABLE_T(STRUCT_TYPE)

/* Given   a  struct   type  name   and  a   (possibly  empty)   variant
   specification: expand  into the  name of the  methods table  for that
   type. */
#define ccname_table_1(STRUCT_TYPE)		CCNAME_TABLE(STRUCT_TYPE, )
#define ccname_table_2(STRUCT_TYPE, VARIANT)	CCNAME_TABLE(STRUCT_TYPE, VARIANT)
#define ccname_table(...)			CCNAMES_VFUNC(ccname_table, __VA_ARGS__)

/* Given an  interface type name,  a struct  type name, and  a (possibly
   empty) variant  specification: expand  into the  name of  the methods
   table for that variant of the interface implementation for the struct
   type. */
#define ccname_iface_table_2(IFACE_TYPE, STRUCT_TYPE)		CCNAME_IFACE_TABLE(IFACE_TYPE, STRUCT_TYPE, )
#define ccname_iface_table_3(IFACE_TYPE, STRUCT_TYPE, VARIANT)	CCNAME_IFACE_TABLE(IFACE_TYPE, STRUCT_TYPE, VARIANT)
#define ccname_iface_table(...)					CCNAMES_VFUNC(ccname_iface_table, __VA_ARGS__)

/* Given an interface type name, a  struct type name, a (possibly empty)
   variant specification, and an expression  that evaluates to a pointer
   to struct  instance: expand into  the invocation of the  API function
   "new()" that instantiates the interface for the struct. */
#define ccname_iface_new_2(IFACE_TYPE, STRUCT_TYPE)		CCNAME_IFACE_NEW(IFACE_TYPE, STRUCT_TYPE, )
#define ccname_iface_new_3(IFACE_TYPE, STRUCT_TYPE, VARIANT)	CCNAME_IFACE_NEW(IFACE_TYPE, STRUCT_TYPE, VARIANT)
#define ccname_iface_new(...)					CCNAMES_VFUNC(ccname_iface_new, __VA_ARGS__)

/* Given an interface type name, a  struct type name, a (possibly empty)
   variant specification, and a method name: expand into the name of the
   method function for that variant  of the interface implementation for
   the struct type. */
#define ccname_iface_method_3(IFACE_TYPE, STRUCT_TYPE, METHOD_NAME)		\
  CCNAME_IFACE_METHOD(IFACE_TYPE, STRUCT_TYPE,        , METHOD_NAME)
#define ccname_iface_method_4(IFACE_TYPE, STRUCT_TYPE, VARIANT, METHOD_NAME)	\
  CCNAME_IFACE_METHOD(IFACE_TYPE, STRUCT_TYPE, VARIANT, METHOD_NAME)
#define ccname_iface_method(...)				CCNAMES_VFUNC(ccname_iface_method, __VA_ARGS__)


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#endif /* defined CCNAMES_H */

/* end of file */
