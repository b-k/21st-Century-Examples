/* Suggested makefile:
----------
P=amort_use
objects=amort_interface.o amortize.o
LDLIBS=-lm
CFLAGS=-g -Wall -O3 -std=gnu11  #the usual

$(P):$(objects)
----------
*/
#include <stdio.h>
#include "amortize.h"

int main(){
    printf("A typical loan:\n");
    amortization_s nopayments = amortization(.amount=200000, .inflation=3);
    printf("You flushed real $%g down the toilet, or $%g in present value.\n",
            nopayments.interest, nopayments.interest_pv);

    amortization_s a_hundred = amortization(.amount=200000, .inflation=3,
                                            .show_table=0, .extra_payoff=100);
    printf("Paying an extra $100/month, you lose only $%g (PV), "
            "and the loan is paid off in %g years.\n",
            a_hundred.interest_pv, a_hundred.years_to_payoff);

    printf("If you sell off in ten years, you pay $%g in interest (PV).\n",
                     amortization(.amount=200000, .inflation=3,
                                  .show_table=0, .selloff_year=10).interest_pv);
}
