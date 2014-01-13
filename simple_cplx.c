/* Suggested makefile:
----------
CFLAGS =-g -Wall -O3 `pkg-config --cflags gsl`
LDLIBS=`pkg-config --libs gsl`
CC=clang

simple_cplx: complex.o
----------
*/
#include <stdio.h>
#include "cplx.h"

int main(){
    int complex a = 1+2I;
    complex double b = 2+I;
    gsl_complex c = gsl_cplx_from_c99(a);

    gsl_vector *v = gsl_vector_alloc(8);
    for (int i=0; i< v->size; i++) gsl_vector_set(v, i, i/8.);

    complex double adotb = dot(a, b);
    printf("(1+2i) dot (2+i): %g + %gi\n", creal(adotb), cimag(adotb));

    printf("v dot 2:\n");
    double d = 2;
    gsl_vector_complex_print(dot(v, d));

    printf("v dot (1+2i):\n");
    gsl_vector_complex *vc = dot(v, a);
    gsl_vector_complex_print(vc);

    printf("v dot (1+2i) again:\n");
    gsl_vector_complex_print(dot(v, c));
}

