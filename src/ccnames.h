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
  CCNAME_NEW(IFACE_TYPE ## STRUCT_TYPE, VARIANT)

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
#define ccstructs_new(STRUCT_TYPE, VARIANT, ...)	\
  CCNAME_NEW(STRUCT_TYPE, VARIANT)(__VA_ARGS__)

/* Given a struct type name and an expression evaluating to a pointer to
   the struct instance:  expand into the invocation of  the API function
   "delete()". */
#define ccstructs_delete(STRUCT_TYPE, STRUCT_INST)	\
  CCNAME_DELETE(STRUCT_TYPE)(STRUCT_INST)

/* Given a struct type name, a variant specification, a (possibly empty)
   variant  specification, and  a  (possibly empty)  list of  arguments:
   expand into the invocation of the API function "init()". */
#define ccstructs_init(STRUCT_TYPE, VARIANT, ...)	\
  CCNAME_INIT(STRUCT_TYPE, VARIANT)(__VA_ARGS__)

/* Given a struct type name and an expression evaluating to a pointer to
   the struct instance:  expand into the invocation of  the API function
   "final()". */
#define ccstructs_final(STRUCT_TYPE, STRUCT_INST)	\
  CCNAME_FINAL(STRUCT_TYPE)(STRUCT_INST)

/* Given a struct type name and an expression evaluating to a pointer to
   the struct instance:  expand into the invocation of  the API function
   "release()". */
#define ccstructs_release(STRUCT_TYPE, STRUCT_INST)	\
  CCNAME_RELEASE(STRUCT_TYPE)(STRUCT_INST)

/* Given an interface type name, a  struct type name, a (possibly empty)
   variant specification, and an expression  that evaluates to a pointer
   to struct  instance: expand into  the invocation of the  API function
   "new()" that instantiates the interface for the struct. */
#define ccstructs_iface_new(IFACE_TYPE, STRUCT_TYPE, VARIANT, STRUCT_INST)	\
  CCNAME_IFACE_NEW(IFACE_TYPE, STRUCT_TYPE, VARIANT)((STRUCT_INST))


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#endif /* defined CCNAMES_H */

/* end of file */
