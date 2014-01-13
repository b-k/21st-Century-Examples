/* See compilation notes in amort_use.c*/
double amortize(double amt, double rate, double inflation, int months,
            int selloff_month, double extra_payoff, int verbose,
            double *interest_pv, double *duration, double *monthly_payment);

typedef struct {
    double amount, years, rate, selloff_year, extra_payoff, inflation;
    int months, selloff_month;
    _Bool show_table;
    double interest, interest_pv, monthly_payment, years_to_payoff;
    char *error;
} amortization_s;


/**
Calculate the inflation-adjusted amount of interest you would pay
over the life of an amortized loan, such as a mortgage.

\li \c amount  The dollar value of the loan. No default--if unspecified,
               I print an error and return zeros.
\li \c months  The number of months in the loan. Default: zero, but see years.
\li \c years  If you do not specify months, you can specify the number of
              years. E.g., 10.5=ten years, six months.
              Default: 30 (a typical U.S. mortgage).
\li \c rate  The interest rate of the loan, expressed in annual
             percentage rate (APR). Default: 4.5 (i.e., 4.5%), which
             is typical for the current (US 2012) housing market.
\li \c inflation  The inflation rate as an annual percent, for calculating
                  the present value of money. Default: 0, meaning no
                  present-value adjustment. A rate of about 3 has been typical
                  for the last few decades in the USA.
\li \c selloff_month  At this month, the loan is paid off (e.g., you resell
                      the house). Default: zero (meaning no selloff).
\li \c selloff_year  If selloff_month==0 and this is positive, the year of
                     selloff. Default: zero (meaning no selloff).
\li \c extra_payoff  Additional monthly principal payment. Default: zero.
\li \c show_table  If nonzero, display a table of payments. If zero, display
                   nothing (just return the total interest). Default: 1

All inputs but \c extra_payoff and \c inflation must be nonnegative.

\return  an \c amortization_s structure, with all of the above values set as
         per your input, plus:

\li \c interest  Total cash paid in interest.
\li \c interest_pv  Total interest paid, with present-value adjustment for inflation.
\li \c monthly_payment  The fixed monthly payment (for a mortgage, taxes and
                   interest get added to this)
\li \c years_to_payoff  Normally the duration or selloff date, but if you make early
                   payments, the loan is paid off sooner.
\li error            If <tt>error != NULL</tt>, something went wrong and the results are invalid.

*/
#define amortization(...) amortize_prep((amortization_s){.show_table=1, \
                                                          __VA_ARGS__})

amortization_s amortize_prep(amortization_s in);
