/* See compilation notes in amort_use.c*/
#include "stopif.h"
#include <stdio.h>
#include "amortize.h"

amortization_s amortize_prep(amortization_s in){
    Stopif(!in.amount || in.amount < 0 || in.rate < 0
            || in.months < 0 || in.years < 0 || in.selloff_month < 0 || in.selloff_year < 0,
            return (amortization_s){.error="Invalid input"},
            "Invalid input. Returning zeros.");

    int months = in.months;
    if (!months){
        if (in.years) months = in.years * 12;
        else          months = 12 * 30; //home loan
    }

    int selloff_month = in.selloff_month;
    if (!selloff_month && in.selloff_year)
        selloff_month = in.selloff_year * 12;

    amortization_s out = in;
    out.rate = in.rate ? in.rate : 4.5;
    out.interest = amortize(in.amount, out.rate, in.inflation,
            months, selloff_month, in.extra_payoff, in.show_table,
            &(out.interest_pv), &(out.years_to_payoff), &(out.monthly_payment));
    return out;
}
