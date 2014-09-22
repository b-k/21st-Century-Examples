/* Suggested makefile:
----------
P=mapreduce_wc
objects=string_utilities.o
CFLAGS=`pkg-config --cflags glib-2.0` -g -Wall -std=gnu99 -O3 -fopenmp
LDLIBS=`pkg-config --libs glib-2.0` -fopenmp

$(P): $(objects)
----------
*/
#include "stopif.h"
#include "wordcount.c"

int main(int argc, char **argv){
    argc--;
    argv++;
    Stopif(!argc, return 0, "Please give some file names on the command line.");
    long int total_wc = 0;

    #pragma omp parallel for  \
     reduction(+:total_wc)
    for (int i=0; i< argc; i++){
        long int this_count = wc(argv[i]);
        total_wc += this_count;
        printf("%s:\t%li\n", argv[i], this_count);
    }

    printf("Σ:\t%li\n", total_wc);
}
