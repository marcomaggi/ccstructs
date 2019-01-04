/*
  Part of: CCStructs
  Contents: demo program for CCNames
  Date: Jan  4, 2019

  Abstract

	This demo program shows how to	implement a struct type with the
	"well known" functions in the API supported by CCNames.

  Copyright (C) 2019 Marco Maggi <marco.maggi-ipsu@poste.it>

  The author hereby  grant permission to use,  copy, modify, distribute,
  and  license this  software  and its	documentation  for any	purpose,
  provided that	 existing copyright notices  are retained in  all copies
  and that  this notice	 is included verbatim  in any  distributions. No
  written agreement, license, or royalty fee  is required for any of the
  authorized uses.  Modifications to this software may be copyrighted by
  their authors and need not  follow the licensing terms described here,
  provided that the new terms are clearly indicated on the first page of
  each file where they apply.

  IN NO	 EVENT SHALL THE AUTHOR	 OR DISTRIBUTORS BE LIABLE  TO ANY PARTY
  FOR  DIRECT, INDIRECT, SPECIAL,  INCIDENTAL, OR  CONSEQUENTIAL DAMAGES
  ARISING OUT  OF THE  USE OF THIS  SOFTWARE, ITS DOCUMENTATION,  OR ANY
  DERIVATIVES  THEREOF, EVEN  IF THE  AUTHOR  HAVE BEEN	 ADVISED OF  THE
  POSSIBILITY OF SUCH DAMAGE.

  THE  AUTHOR  AND DISTRIBUTORS	 SPECIFICALLY  DISCLAIM ANY  WARRANTIES,
  INCLUDING,   BUT   NOT  LIMITED   TO,	  THE	IMPLIED	 WARRANTIES   OF
  MERCHANTABILITY,    FITNESS	FOR    A    PARTICULAR	 PURPOSE,    AND
  NON-INFRINGEMENT.  THIS  SOFTWARE IS PROVIDED	 ON AN "AS  IS" BASIS,
  AND  THE  AUTHOR  AND	 DISTRIBUTORS  HAVE  NO	 OBLIGATION  TO	 PROVIDE
  MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

*/


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include <ccmemory.h>
#include <ccnames.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/** --------------------------------------------------------------------
 ** Type definitions.
 ** ----------------------------------------------------------------- */

typedef struct my_coords_t	my_coords_t;

struct my_coords_t {
  double	X;
  double	Y;
};


/** --------------------------------------------------------------------
 ** Well known functions.
 ** ----------------------------------------------------------------- */

void
ccname_init(my_coords_t, rec) (my_coords_t * S, double X, double Y)
{
  S->X = X;
  S->Y = Y;
}

void
ccname_init(my_coords_t, pol) (my_coords_t * S, double RHO, double THETA)
{
  S->X = RHO * cos(THETA);
  S->Y = RHO * sin(THETA);
}

void
ccname_final(my_coords_t) (my_coords_t * S CCNAMES_UNUSED)
{
}

static my_coords_t *
ccname_alloc(my_coords_t) (cce_destination_t L)
{
  return (my_coords_t *)ccmem_std_malloc(L, sizeof(my_coords_t));
}

static void
ccname_release(my_coords_t) (my_coords_t * S)
{
  ccmem_std_free(S);
}

my_coords_t *
ccname_new(my_coords_t, rec) (cce_destination_t L, double X, double Y)
{
  my_coords_t * S = ccname_alloc(my_coords_t)(L);

  ccname_init(my_coords_t, rec)(S, X, Y);
  return S;
}

my_coords_t *
ccname_new(my_coords_t, pol) (cce_destination_t L, double RHO, double THETA)
{
  my_coords_t * S = ccname_alloc(my_coords_t)(L);

  ccname_init(my_coords_t, pol)(S, RHO, THETA);
  return S;
}

void
ccname_delete(my_coords_t) (my_coords_t * S)
{
  ccname_final(my_coords_t)(S);
  ccname_release(my_coords_t)(S);
}


/** --------------------------------------------------------------------
 ** Let's go.
 ** ----------------------------------------------------------------- */

int
main (void)
{
  cce_location_t	L[1];
  my_coords_t *		S;

  if (cce_location(L)) {
    cce_run_catch_handlers_final(L);
  } else {
    S = ccname_new(my_coords_t, rec)(L, 1.0, 2.0);

    printf("X=%f, Y=%f\n", S->X, S->Y);
    ccname_delete(my_coords_t)(S);
  }
  exit(EXIT_SUCCESS);
}

/* end of file */
