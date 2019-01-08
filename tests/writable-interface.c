/*
  Part of: CCStructs
  Contents: tests for the writable interface
  Date: Sat Sep 22, 2018

  Abstract



  Copyright (C) 2018, 2019 Marco Maggi <marco.maggi-ipsu@poste.it>

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

#include "ccstructs.h"
#include <cctests.h>
#include <errno.h>


/** --------------------------------------------------------------------
 ** Writable interface: fwrite method.
 ** ----------------------------------------------------------------- */

typedef struct one_one_t	one_one_t;

struct one_one_t {
  int		alpha;
  int		beta;
};

static void
ccname_iface_method(ccstructs_writable_I, one_one_t, write) (cce_destination_t L, ccstructs_writable_I I)
{
  CCSTRUCTS_PC(one_one_t const, S, ccstructs_writable_self(I));
  int	rv;

  errno = 0;
  rv = fprintf(stderr, "serialisation of one_one_t: alpha=%d, beta=%d\n", S->alpha, S->beta);
  if (0 > rv) {
    cce_raise(L, cce_condition_new_errno_clear());
  }
}

static ccname_iface_table_type(ccstructs_writable_I) const ccname_iface_table(ccstructs_writable_I, one_one_t) = {
  .write = ccname_iface_method(ccstructs_writable_I, one_one_t, write)
};

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccstructs_writable_I
ccname_iface_new(ccstructs_writable_I, one_one_t) (one_one_t const * S)
{
  return ccname_new(ccstructs_writable_I)(ccstructs_core(S), &ccname_iface_table(ccstructs_writable_I, one_one_t));
}

void
test_1_1 (cce_destination_t upper_L)
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    one_one_t	S = {
      .alpha	= 1,
      .beta	= 2
    };
    ccstructs_writable_I	I = ccname_iface_new(ccstructs_writable_I, one_one_t)(&S);

    ccstructs_writable_write(L, I);

    cce_run_body_handlers(L);
  }
}


int
main (void)
{
  cctests_init("tests writable interface");
  {
    cctests_begin_group("fwrite method");
    {
      cctests_run(test_1_1);
    }
    cctests_end_group();
  }
  cctests_final();
}

/* end of file */
