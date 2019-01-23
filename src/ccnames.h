/*
  Part of: CCStructs
  Contents: preprocessor macros to define common API names
  Date: Tue Jan  1, 2019

  Abstract

	This  header file  defines a  set  of macros  that generate,  at
	expansion  time, identifiers  for functions  and variables  that
	have "well known" roles in the API of the CCLibraries projects.

	It is to be considered experimental.

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
 ** Preliminary definitions.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif

/* The  macro  CCNAMES_UNUSED  indicates  that a  function,  function
   argument or variable may potentially be unused. Usage examples:

   static int unused_function (char arg) CCNAMES_UNUSED;
   int foo (char unused_argument CCNAMES_UNUSED);
   int unused_variable CCNAMES_UNUSED;
*/
#ifdef __GNUC__
#  define CCNAMES_UNUSED		__attribute__((__unused__))
#else
#  define CCNAMES_UNUSED		/* empty */
#endif


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
 *   _CCNAMES__NARG__(__VA_ARGS__)
 *
 * expands into the number of arguments in __VA_ARGS__.
 */
#define _CCNAMES__NARG__(...)	_CCNAMES__NARG_I_(__VA_ARGS__,_CCNAMES__RSEQ_N())
#define _CCNAMES__NARG_I_(...)	_CCNAMES__ARG_N(__VA_ARGS__)
#define _CCNAMES__ARG_N( \
      _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
     _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
     _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
     _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
     _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
     _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
     _61,_62,_63,N,...)		N
#define _CCNAMES__RSEQ_N() \
     63,62,61,60,                   \
     59,58,57,56,55,54,53,52,51,50, \
     49,48,47,46,45,44,43,42,41,40, \
     39,38,37,36,35,34,33,32,31,30, \
     29,28,27,26,25,24,23,22,21,20, \
     19,18,17,16,15,14,13,12,11,10, \
     9,8,7,6,5,4,3,2,1,0

/* The macro uses:
 *
 *    _CCNAMES_VFUNC(ccname_new, alpha)
 *    _CCNAMES_VFUNC(ccname_new, alpha, beta)
 *
 * respectively expand into:
 *
 *    ccname_new_1(alpha)
 *    ccname_new_2(alpha, beta)
 *
 */
#define _CCNAMES___VFUNC(NAME, N)	NAME ## _ ## N
#define _CCNAMES__VFUNC(NAME, N)	_CCNAMES___VFUNC(NAME, N)
#define _CCNAMES_VFUNC(FUNC, ...)	_CCNAMES__VFUNC(FUNC, _CCNAMES__NARG__(__VA_ARGS__))(__VA_ARGS__)


/** --------------------------------------------------------------------
 ** Construction of automatically generated names.
 ** ----------------------------------------------------------------- */

/* Given   a  struct   type  name   and  a   (possibly  empty)   variant
   specification: expand into the name of the API function "new()". */
#define _CCNAME_NEW(STRUCT_TYPE, VARIANT)	STRUCT_TYPE ## __ ## VARIANT ## __new

/* Given a  struct type name: expand  into the name of  the API function
   "delete()". */
#define _CCNAME_DELETE(STRUCT_TYPE)		STRUCT_TYPE ## __delete

/* Given   a  struct   type  name   and  a   (possibly  empty)   variant
   specification: expand into the name of the API function "init()". */
#define _CCNAME_INIT(STRUCT_TYPE, VARIANT)	STRUCT_TYPE ## __ ## VARIANT ## __init

/* Given a  struct type name: expand  into the name of  the API function
   "final()". */
#define _CCNAME_FINAL(STRUCT_TYPE)		STRUCT_TYPE ## __final

/* Given a  struct type name: expand  into the name of  the API function
   "alloc()". */
#define _CCNAME_ALLOC(STRUCT_TYPE)		STRUCT_TYPE ## __alloc

/* Given a  struct type name: expand  into the name of  the API function
   "release()". */
#define _CCNAME_RELEASE(STRUCT_TYPE)		STRUCT_TYPE ## __release

/* Given a struct type name an a (possibly empty) variant specification:
   expand  into the  name  of  the methods  table  type  for the  struct
   type. */
#define _CCNAME_TABLE_TYPE(STRUCT_TYPE, VARIANT) STRUCT_TYPE ## __ ## VARIANT ## __methods_table_t

/* Given   a  struct   type  name   and  a   (possibly  empty)   variant
   specification: expand  into the  name of the  methods table  for that
   type. */
#define _CCNAME_TABLE(STRUCT_TYPE, VARIANT)	STRUCT_TYPE ## __ ## VARIANT ## __methods_table

/* Given a struct  type name, a (possibly  empty) variant specification,
   and a method name:  expand into the type name of  that variant of the
   method function for the struct type. */
#define _CCNAME_METHOD_TYPE(STRUCT_TYPE, VARIANT, METHOD_NAME)	\
  STRUCT_TYPE ## __ ## VARIANT ## __method__ ## METHOD_NAME ## __fun_t

/* Given a struct  type name, a (possibly  empty) variant specification,
   and  a method  name: expand  into  the name  of the  method for  that
   type. */
#define _CCNAME_METHOD(STRUCT_TYPE, VARIANT, METHOD_NAME) STRUCT_TYPE ## __ ## VARIANT ## __method__ ## METHOD_NAME


/** --------------------------------------------------------------------
 ** Automatically generated names API: data structs.
 ** ----------------------------------------------------------------- */

/* Given  a struct  type  name and  an  optional variant  specification:
   expand into the name of the API function "new()". */
#define ccname_new_1(STRUCT_TYPE)			_CCNAME_NEW(STRUCT_TYPE, )
#define ccname_new_2(STRUCT_TYPE, VARIANT)		_CCNAME_NEW(STRUCT_TYPE, VARIANT)
#define ccname_new_3(STRUCT_TYPE, VARIANT1, VARIANT2)	_CCNAME_NEW(STRUCT_TYPE, VARIANT1 ## __ ## VARIANT2)
#define ccname_new(...)					_CCNAMES_VFUNC(ccname_new, __VA_ARGS__)

/* Given a  struct type name: expand  into the name of  the API function
   "delete()". */
#define ccname_delete(STRUCT_TYPE)		_CCNAME_DELETE(STRUCT_TYPE)

/* Given  a struct  type  name and  an  optional variant  specification:
   expand into the name of the API function "init()". */
#define ccname_init_1(STRUCT_TYPE)			_CCNAME_INIT(STRUCT_TYPE, )
#define ccname_init_2(STRUCT_TYPE, VARIANT)		_CCNAME_INIT(STRUCT_TYPE, VARIANT)
#define ccname_init_3(STRUCT_TYPE, VARIANT1, VARIANT2)	_CCNAME_INIT(STRUCT_TYPE, VARIANT1 ## __ ## VARIANT2)
#define ccname_init(...)				_CCNAMES_VFUNC(ccname_init, __VA_ARGS__)

/* Given a  struct type name: expand  into the name of  the API function
   "final()". */
#define ccname_final(STRUCT_TYPE)		_CCNAME_FINAL(STRUCT_TYPE)

/* Given a  struct type name: expand  into the name of  the API function
   "alloc()". */
#define ccname_alloc(STRUCT_TYPE)		_CCNAME_ALLOC(STRUCT_TYPE)

/* Given a  struct type name: expand  into the name of  the API function
   "release()". */
#define ccname_release(STRUCT_TYPE)		_CCNAME_RELEASE(STRUCT_TYPE)


/** --------------------------------------------------------------------
 ** Automatically generated names API: methods table for data structs.
 ** ----------------------------------------------------------------- */

/* Given a struct  type name: expand into the name  of the methods table
   type for the struct type. */
#define ccname_table_type_1(STRUCT_TYPE)	_CCNAME_TABLE_TYPE(STRUCT_TYPE, )
#define ccname_table_type_2(STRUCT_TYPE, VARIANT) _CCNAME_TABLE_TYPE(STRUCT_TYPE, VARIANT)
#define ccname_table_type(...)			_CCNAMES_VFUNC(ccname_table_type, __VA_ARGS__)

/* Given  a struct  type  name and  an  optional variant  specification:
   expand into the name of the methods table for that type. */
#define ccname_table_1(STRUCT_TYPE)		_CCNAME_TABLE(STRUCT_TYPE, )
#define ccname_table_2(STRUCT_TYPE, VARIANT)	_CCNAME_TABLE(STRUCT_TYPE, VARIANT)
#define ccname_table(...)			_CCNAMES_VFUNC(ccname_table, __VA_ARGS__)

/* Given a  struct type name,  an optional variant specification,  and a
   method name: expand into the type  name of that variant of the method
   function for the struct type. */
#define ccname_method_type_2(STRUCT_TYPE,          METHOD_NAME)	_CCNAME_METHOD_TYPE(STRUCT_TYPE,        , METHOD_NAME)
#define ccname_method_type_3(STRUCT_TYPE, VARIANT, METHOD_NAME)	_CCNAME_METHOD_TYPE(STRUCT_TYPE, VARIANT, METHOD_NAME)
#define ccname_method_type(...)			_CCNAMES_VFUNC(ccname_method_type, __VA_ARGS__)

/* Given a  struct type name,  an optional variant specification,  and a
   method name: expand into the name of the method for that type. */
#define ccname_method_2(STRUCT_TYPE,          METHOD_NAME)	_CCNAME_METHOD(STRUCT_TYPE,        , METHOD_NAME)
#define ccname_method_3(STRUCT_TYPE, VARIANT, METHOD_NAME)	_CCNAME_METHOD(STRUCT_TYPE, VARIANT, METHOD_NAME)
#define ccname_method(...)					_CCNAMES_VFUNC(ccname_method, __VA_ARGS__)


/** --------------------------------------------------------------------
 ** Automatically generated names API: interface structs.
 ** ----------------------------------------------------------------- */

/* Given an  interface type name,  a (possibly empty) struct  type name,
   and  a  (possibly  empty)  variant  specification:  expand  into  the
   function  type  of the  selected  variant  of interface  constructors
   implemented by the struct type. */
#define _CCNAME_IFACE_NEW_TYPE(IFACE_TYPE, STRUCT_TYPE, VARIANT)	\
  IFACE_TYPE ## __ ## STRUCT_TYPE ## __ ## VARIANT ## __new__fun_t

/* Given an  interface type name,  a struct  type name, and  a (possibly
   empty)  variant  specification:  expand  into the  name  of  the  API
   function "new()"  used to instantiate  that variant of  the interface
   type for that struct type. */
#define _CCNAME_IFACE_NEW(IFACE_TYPE, STRUCT_TYPE, VARIANT)	\
  _CCNAME_NEW(IFACE_TYPE ## __ ## STRUCT_TYPE, VARIANT)

/* Given an interface  type name and an  optional variant specification:
   expand into  the name  of the  methods table  type for  the interface
   type. */
#define _CCNAME_IFACE_TABLE_TYPE(IFACE_TYPE, VARIANT)		\
  _CCNAME_TABLE_TYPE(IFACE_TYPE, VARIANT)

/* Given an  interface type name,  a struct  type name, and  a (possibly
   empty) variant  specification: expand  into the  name of  the methods
   table for that variant of the interface implementation for the struct
   type. */
#define _CCNAME_IFACE_TABLE(IFACE_TYPE, STRUCT_TYPE, VARIANT)	\
  _CCNAME_TABLE(IFACE_TYPE ## __ ## STRUCT_TYPE, VARIANT)

/* Given   an  interface   type   name,  a   (possibly  empty)   variant
   specification, and  a method name: expand  into the type name  of the
   method function for that variant of the interface implementation. */
#define _CCNAME_IFACE_METHOD_TYPE(IFACE_TYPE, VARIANT, METHOD_NAME)	\
  IFACE_TYPE ## __ ## VARIANT ## __method__ ## METHOD_NAME ## __fun_t

/* Given an interface type name, a  struct type name, a (possibly empty)
   variant specification, and a method name: expand into the name of the
   method function for that variant  of the interface implementation for
   the struct type. */
#define _CCNAME_IFACE_METHOD(IFACE_TYPE, STRUCT_TYPE, VARIANT, METHOD_NAME)	\
  IFACE_TYPE ## __ ## STRUCT_TYPE ## __ ## VARIANT ## __method__ ## METHOD_NAME

/* ------------------------------------------------------------------ */

/* Given an  interface type name,  an optional  struct type name  and an
   optional  variant specification:  expand  into the  function type  of
   interface implementation constructors. */
#define ccname_iface_new_type_1(IFACE_TYPE)				_CCNAME_IFACE_NEW_TYPE(IFACE_TYPE,,)
#define ccname_iface_new_type_2(IFACE_TYPE, STRUCT_TYPE)		_CCNAME_IFACE_NEW_TYPE(IFACE_TYPE, STRUCT_TYPE,)
#define ccname_iface_new_type_3(IFACE_TYPE, STRUCT_TYPE, VARIANT)	_CCNAME_IFACE_NEW_TYPE(IFACE_TYPE, STRUCT_TYPE, VARIANT)
#define ccname_iface_new_type(...)					_CCNAMES_VFUNC(ccname_iface_new_type, __VA_ARGS__)

/* Given an interface type name, a struct type name, an optional variant
   specification: expand into the name  of the API function "new()" that
   instantiates that variant of the interface for the struct. */
#define ccname_iface_new_2(IFACE_TYPE, STRUCT_TYPE)		_CCNAME_IFACE_NEW(IFACE_TYPE, STRUCT_TYPE, )
#define ccname_iface_new_3(IFACE_TYPE, STRUCT_TYPE, VARIANT)	_CCNAME_IFACE_NEW(IFACE_TYPE, STRUCT_TYPE, VARIANT)
#define ccname_iface_new(...)					_CCNAMES_VFUNC(ccname_iface_new, __VA_ARGS__)

/* Given an interface  type name and an  optional variant specification:
   expand into  the name  of the  methods table  type for  the interface
   type. */
#define ccname_iface_table_type_1(IFACE_TYPE)		_CCNAME_IFACE_TABLE_TYPE(IFACE_TYPE, )
#define ccname_iface_table_type_2(IFACE_TYPE, VARIANT)	_CCNAME_IFACE_TABLE_TYPE(IFACE_TYPE, VARIANT)
#define ccname_iface_table_type(...)			_CCNAMES_VFUNC(ccname_iface_table_type, __VA_ARGS__)

/* Given an  interface type name,  a struct  type name, and  an optional
   variant specification: expand into the  name of the methods table for
   that variant of the interface implementation for the struct type. */
#define ccname_iface_table_2(IFACE_TYPE, STRUCT_TYPE)		_CCNAME_IFACE_TABLE(IFACE_TYPE, STRUCT_TYPE, )
#define ccname_iface_table_3(IFACE_TYPE, STRUCT_TYPE, VARIANT)	_CCNAME_IFACE_TABLE(IFACE_TYPE, STRUCT_TYPE, VARIANT)
#define ccname_iface_table(...)					_CCNAMES_VFUNC(ccname_iface_table, __VA_ARGS__)

/* Given an interface type name,  an optional variant specification, and
   a method name:  expand into the type name of  the method function for
   that variant of the interface implementation. */
#define ccname_iface_method_type_2(IFACE_TYPE,          METHOD_NAME)	_CCNAME_IFACE_METHOD_TYPE(IFACE_TYPE,        , METHOD_NAME)
#define ccname_iface_method_type_3(IFACE_TYPE, VARIANT, METHOD_NAME)	_CCNAME_IFACE_METHOD_TYPE(IFACE_TYPE, VARIANT, METHOD_NAME)
#define ccname_iface_method_type(...)				_CCNAMES_VFUNC(ccname_iface_method_type, __VA_ARGS__)

/* Given an interface type name, a struct type name, an optional variant
   specification, and a method name: expand  into the name of the method
   function for  that variant  of the  interface implementation  for the
   struct type. */
#define ccname_iface_method_3(IFACE_TYPE, STRUCT_TYPE, METHOD_NAME)		\
  _CCNAME_IFACE_METHOD(IFACE_TYPE, STRUCT_TYPE,        , METHOD_NAME)
#define ccname_iface_method_4(IFACE_TYPE, STRUCT_TYPE, VARIANT, METHOD_NAME)	\
  _CCNAME_IFACE_METHOD(IFACE_TYPE, STRUCT_TYPE, VARIANT, METHOD_NAME)
#define ccname_iface_method(...)				_CCNAMES_VFUNC(ccname_iface_method, __VA_ARGS__)


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* defined CCNAMES_H */

/* end of file */
