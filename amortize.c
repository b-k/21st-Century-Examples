/* See compilation notes in amort_use.c*/
#include <math.h> //pow.
#include <stdio.h>
#include "amortize.h"

double amortize(double amt, double rate, double inflation, int months,
                int selloff_month, double extra_payoff, int verbose,
                double *interest_pv, double *duration, double *monthly_payment){
    double total_interest    = 0;
    *interest_pv = 0;
    double mrate = rate/1200;

    //The monthly rate is fixed, but the proportion going to interest changes.
    *monthly_payment = amt * mrate/(1-pow(1+mrate, -months))+extra_payoff;
    if (verbose) printf("Your total monthly payment: %g\n\n", *monthly_payment);
    int end_month = (selloff_month && selloff_month < months )
                            ? selloff_month
                            : months;
    if (verbose) printf("yr/mon\t Princ.\t\tInt.\t|  PV Princ.\t PV Int.\t  Ratio\n");
    int m;
    for (m=0; m < end_month && amt > 0; m++){
        double interest_payment = amt*mrate;
        double principal_payment = *monthly_payment - interest_payment;
        if (amt <= 0)
            principal_payment =
            interest_payment  = 0;
        amt -= principal_payment;
        double deflator = pow(1+ inflation/100, -m/12.);
        *interest_pv   += interest_payment * deflator;
        total_interest += interest_payment;
        if (verbose) printf("%i/%i\t%7.2f\t\t%7.2f\t| %7.2f\t %7.2f\t%7.2f\n",
                m/12, m-12*(m/12)+1, principal_payment, interest_payment,
                principal_payment*deflator, interest_payment*deflator,
                principal_payment/(principal_payment+interest_payment)*100);
    }
    *duration = m/12.;
    return total_interest;
}
