/*
  Part of: CCStructs
  Contents: simple implementations of pathname interfaces
  Date: Mon Oct  8, 2018

  Abstract



  Copyright (C) 2018 Marco Maggi <marco.maggi-ipsu@poste.it>

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


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "ccstructs-internals.h"


/** --------------------------------------------------------------------
 ** Pathname interface: from ASCIIZ static strings.
 ** ----------------------------------------------------------------- */

static size_t
ccstructs_pathname_I_from_static_length (ccstructs_pathname_I I)
{
  char const *	ptn = (char const *)ccstructs_pathname_self(I);
  return strlen(ptn);
}

char const *
ccstructs_pathname_I_from_static_pointer (ccstructs_pathname_I I)
{
  char const *	ptn = (char const *)ccstructs_pathname_self(I);
  return ptn;
}

bool
ccstructs_pathname_I_from_static_is_persistent (ccstructs_pathname_I I CCSTRUCTS_UNUSED)
{
  return true;
}

static ccstructs_pathname_I_methods_t const ccstructs_pathname_I_methods_from_static = {
  .length		= ccstructs_pathname_I_from_static_length,
  .pointer		= ccstructs_pathname_I_from_static_pointer,
  .is_persistent	= ccstructs_pathname_I_from_static_is_persistent
};

ccstructs_pathname_I
ccstructs_new_pathname_from_static_string (const char * pathname)
{
  return ccstructs_new_pathname(ccstructs_core(pathname), &ccstructs_pathname_I_methods_from_static);
}


/** --------------------------------------------------------------------
 ** Pathname interface: from ASCIIZ structs.
 ** ----------------------------------------------------------------- */

static size_t
ccstructs_pathname_I_from_asciiz_length (ccstructs_pathname_I I)
{
  ccmem_ascii_t *	S = (ccmem_ascii_t *) ccstructs_pathname_self(I);
  return S->len;
}

char const *
ccstructs_pathname_I_from_asciiz_pointer (ccstructs_pathname_I I)
{
  ccmem_ascii_t *	S = (ccmem_ascii_t *) ccstructs_pathname_self(I);
  return S->ptr;
}

bool
ccstructs_pathname_I_from_asciiz_is_persistent (ccstructs_pathname_I I CCSTRUCTS_UNUSED)
{
  return false;
}

static ccstructs_pathname_I_methods_t const ccstructs_pathname_I_methods_from_asciiz = {
  .length		= ccstructs_pathname_I_from_asciiz_length,
  .pointer		= ccstructs_pathname_I_from_asciiz_pointer,
  .is_persistent	= ccstructs_pathname_I_from_asciiz_is_persistent
};

ccstructs_pathname_I
ccstructs_new_pathname_from_asciiz_string (const char * pathname)
{
  return ccstructs_new_pathname(ccstructs_core(pathname), &ccstructs_pathname_I_methods_from_asciiz);
}


/* end of file */
