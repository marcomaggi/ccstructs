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
 ** Pathname interface: from ASCIIZ static or dynamic strings.
 ** ----------------------------------------------------------------- */

static size_t
ccstructs_pathname_I_from_string_length (cce_destination_t L CCSTRUCTS_UNUSED, ccstructs_pathname_I I)
{
  CCSTRUCTS_PC(char const, ptn, ccstructs_pathname_self(I));
  return strlen(ptn);
}

static char const *
ccstructs_pathname_I_from_string_pointer (cce_destination_t L CCSTRUCTS_UNUSED, ccstructs_pathname_I I)
{
  CCSTRUCTS_PC(char const, ptn, ccstructs_pathname_self(I));
  return ptn;
}

static bool
ccstructs_pathname_I_from_static_string_is_static (ccstructs_pathname_I I CCSTRUCTS_UNUSED)
{
  return true;
}

static bool
ccstructs_pathname_I_from_dynamic_string_is_static (ccstructs_pathname_I I CCSTRUCTS_UNUSED)
{
  return false;
}

static ccstructs_pathname_I_methods_t const ccstructs_pathname_I_methods_from_static_string = {
  .length	= ccstructs_pathname_I_from_string_length,
  .pointer	= ccstructs_pathname_I_from_string_pointer,
  .is_static	= ccstructs_pathname_I_from_static_string_is_static
};

static ccstructs_pathname_I_methods_t const ccstructs_pathname_I_methods_from_dynamic_string = {
  .length	= ccstructs_pathname_I_from_string_length,
  .pointer	= ccstructs_pathname_I_from_string_pointer,
  .is_static	= ccstructs_pathname_I_from_dynamic_string_is_static
};

ccstructs_pathname_I
ccstructs_new_pathname_from_static_string (const char * const ptn)
{
  ccstructs_pathname_I	I = {
    .methods	= &ccstructs_pathname_I_methods_from_static_string,
    .self	= ccstructs_core(ptn)
  };
  return I;
}

ccstructs_pathname_I
ccstructs_new_pathname_from_dynamic_string (const char * const ptn)
{
  ccstructs_pathname_I	I = {
    .methods	= &ccstructs_pathname_I_methods_from_dynamic_string,
    .self	= ccstructs_core(ptn)
  };
  return I;
}


/** --------------------------------------------------------------------
 ** Pathname interface: from static or dynamic ASCIIZ structs.
 ** ----------------------------------------------------------------- */

static size_t
ccstructs_pathname_I_from_asciiz_length (cce_destination_t L CCSTRUCTS_UNUSED, ccstructs_pathname_I I)
{
  CCSTRUCTS_PC(ccmem_asciiz_t, S, ccstructs_pathname_self(I));
  return S->len;
}

static char const *
ccstructs_pathname_I_from_asciiz_pointer (cce_destination_t L CCSTRUCTS_UNUSED, ccstructs_pathname_I I)
{
  CCSTRUCTS_PC(ccmem_asciiz_t, S, ccstructs_pathname_self(I));
  return S->ptr;
}

static bool
ccstructs_pathname_I_from_static_asciiz_is_static (ccstructs_pathname_I I CCSTRUCTS_UNUSED)
{
  return true;
}

static bool
ccstructs_pathname_I_from_dynamic_asciiz_is_static (ccstructs_pathname_I I CCSTRUCTS_UNUSED)
{
  return false;
}

static ccstructs_pathname_I_methods_t const ccstructs_pathname_I_methods_from_static_asciiz = {
  .length	= ccstructs_pathname_I_from_asciiz_length,
  .pointer	= ccstructs_pathname_I_from_asciiz_pointer,
  .is_static	= ccstructs_pathname_I_from_static_asciiz_is_static
};

static ccstructs_pathname_I_methods_t const ccstructs_pathname_I_methods_from_dynamic_asciiz = {
  .length	= ccstructs_pathname_I_from_asciiz_length,
  .pointer	= ccstructs_pathname_I_from_asciiz_pointer,
  .is_static	= ccstructs_pathname_I_from_dynamic_asciiz_is_static
};

ccstructs_pathname_I
ccstructs_new_pathname_from_static_asciiz (ccmem_asciiz_t const * const S)
{
  ccstructs_pathname_I	I = {
    .methods	= &ccstructs_pathname_I_methods_from_static_asciiz,
    .self	= ccstructs_core(S)
  };
  return I;
}

ccstructs_pathname_I
ccstructs_new_pathname_from_dynamic_asciiz (ccmem_asciiz_t const * const S)
{
  ccstructs_pathname_I	I = {
    .methods	= &ccstructs_pathname_I_methods_from_dynamic_asciiz,
    .self	= ccstructs_core(S)
  };
  return I;
}

/* end of file */
