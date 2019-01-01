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
#define ccname_new(STRUCT_TYPE)			CCNAME_NEW(STRUCT_TYPE, )
#define ccname_newex(STRUCT_TYPE, VARIANT)	CCNAME_NEW(STRUCT_TYPE, VARIANT)

/* Given a struct type name and an expression evaluating to a pointer to
   the struct instance:  expand into the invocation of  the API function
   "delete()". */
#define ccname_delete(STRUCT_TYPE)		CCNAME_DELETE(STRUCT_TYPE)

/* Given a struct type name, a variant specification, a (possibly empty)
   variant  specification, and  a  (possibly empty)  list of  arguments:
   expand into the invocation of the API function "init()". */
#define ccname_init(STRUCT_TYPE)		CCNAME_INIT(STRUCT_TYPE, )
#define ccname_initex(STRUCT_TYPE, VARIANT)	CCNAME_INIT(STRUCT_TYPE, VARIANT)

/* Given a struct type name and an expression evaluating to a pointer to
   the struct instance:  expand into the invocation of  the API function
   "final()". */
#define ccname_final(STRUCT_TYPE)		CCNAME_FINAL(STRUCT_TYPE)

/* Given a struct type name and an expression evaluating to a pointer to
   the struct instance:  expand into the invocation of  the API function
   "release()". */
#define ccname_release(STRUCT_TYPE)		CCNAME_RELEASE(STRUCT_TYPE)

/* Given an interface type name, a  struct type name, a (possibly empty)
   variant specification, and an expression  that evaluates to a pointer
   to struct  instance: expand into  the invocation of the  API function
   "new()" that instantiates the interface for the struct. */
#define ccname_iface_new(IFACE_TYPE, STRUCT_TYPE)		CCNAME_IFACE_NEW(IFACE_TYPE, STRUCT_TYPE, )
#define ccname_iface_newex(IFACE_TYPE, STRUCT_TYPE, VARIANT)	CCNAME_IFACE_NEW(IFACE_TYPE, STRUCT_TYPE, VARIANT)

/* Given an interface type name, a  struct type name, a (possibly empty)
   variant specification, and a method name: expand into the name of the
   method function for that variant  of the interface implementation for
   the struct type. */
#define ccname_iface_method(IFACE_TYPE, STRUCT_TYPE, METHOD_NAME)	\
  CCNAME_IFACE_METHOD(IFACE_TYPE, STRUCT_TYPE,        , METHOD_NAME)
#define ccname_iface_methodex(IFACE_TYPE, STRUCT_TYPE, VARIANT, METHOD_NAME)	\
  CCNAME_IFACE_METHOD(IFACE_TYPE, STRUCT_TYPE, VARIANT, METHOD_NAME)


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#endif /* defined CCNAMES_H */

/* end of file */
