/*
  Part of: CCStructs
  Contents: tests for the writable interface
  Date: Sat Sep 22, 2018

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

#include "ccstructs.h"
#include <cctests.h>
#include <errno.h>


/** --------------------------------------------------------------------
 ** Writable interface: fprintf method.
 ** ----------------------------------------------------------------- */

typedef struct one_one_t	one_one_t;

struct one_one_t {
  int		alpha;
  int		beta;
};

static void
one_one_fwrite_method (cce_destination_t L, FILE * stream, ccstructs_writable_iface_t I)
{
  CCSTRUCTS_PC(one_one_t, S, I.self);
  int	rv;

  errno = 0;
  rv = fprintf(stream, "serialisation of one_one_t: alpha=%d, beta=%d", S->alpha, S->beta);
  if (0 > rv) {
    cce_raise(L, cce_condition_new_errno_clear());
  }
}

static ccstructs_writable_iface_methods_t const one_one_writable_iface_methods =
  {
   .fwrite = one_one_fwrite_method
  };

static ccstructs_writable_iface_t
one_one_writable_iface (one_one_t * S)
{
  ccstructs_writable_iface_t	I =
    {
     .methods	= &one_one_writable_iface_methods,
     .self	= (ccstructs_core_t *)S
    };
  return I;
}

void
test_1_1 (cce_destination_t upper_L)
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    one_one_t	S =
      {
       .alpha	= 1,
       .beta	= 2
      };
    ccstructs_writable_iface_t	I = one_one_writable_iface(&S);

    ccstructs_writable_fwrite(L, stderr, I);
    fprintf(stderr, "\n");

    cce_run_body_handlers(L);
  }
}


int
main (void)
{
  cctests_init("tests writable interface");
  {
    cctests_begin_group("condition objects");
    {
      cctests_run(test_1_1);
    }
    cctests_end_group();
  }
  cctests_final();
}

/* end of file */
