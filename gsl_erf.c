/* Compile with:
export LDLIBS="`pkg-config --libs gsl`"
export CFLAGS="`pkg-config --cflags gsl` -g -Wall -std=gnu11 -O3"
make gsl_erf
*/
#include <gsl/gsl_cdf.h>
#include <stdio.h>

int main(){
    double bottom_tail = gsl_cdf_gaussian_P(-1.96, 1);
    printf("Area between [-1.96, 1.96]: %g\n", 1-2*bottom_tail);
}
