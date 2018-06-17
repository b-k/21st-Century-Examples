/* Suggested makefile:
----------
P=openmp_factors
CFLAGS=`pkg-config --cflags glib-2.0` -g -Wall -std=gnu99 -O3 -fopenmp
LDLIBS=`pkg-config --libs glib-2.0` -fopenmp

$(P):
----------
*/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h> //malloc
#include <string.h> //memset

#include "openmp_getmax.c"

int main(){
    long int max = 1e7;
    int *factor_ct = malloc(sizeof(int)*max);

    int lock_ct = 128;
    omp_lock_t locks[lock_ct];
    for (long int i=0; i< lock_ct; i++)
        omp_init_lock(&locks[i]);

    factor_ct[0] = 0;
    factor_ct[1] = 1;
    for (long int i=2; i< max; i++)
        factor_ct[i] = 2;

    #pragma omp parallel for
    for (long int i=2; i<= max/2; i++)
        for (long int scale=2; scale*i < max; scale++) {
                omp_set_lock(&locks[scale*i % lock_ct]);
                factor_ct[scale*i]++;
                omp_unset_lock(&locks[scale*i % lock_ct]);
            }

    int max_factors = get_max(factor_ct, max);
    long int tally[max_factors+1];
    memset(tally, 0, sizeof(long int)*(max_factors+1));

    #pragma omp parallel for
    for (long int i=0; i< max; i++){
        int factors = factor_ct[i];
        omp_set_lock(&locks[factors % lock_ct]);
        tally[factors]++;
        omp_unset_lock(&locks[factors % lock_ct]);
    }

    for (int i=0; i<=max_factors; i++)
        printf("%i\t%li\n", i, tally[i]);
}
