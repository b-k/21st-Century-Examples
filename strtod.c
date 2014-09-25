/* Compile with:
export CFLAGS="-g -Wall -std=gnu11 -O3"  #the usual.
make strtod
*/
#include "stopif.h"
#include <stdlib.h> //strtod
#include <math.h>   //pow

int main(int argc, char **argv){
    Stopif (argc < 2, return 1, "Give me a number on the command line to square.");
    char *end;
    double in = strtod(argv[1], &end);
    Stopif(*end, return 2, "I couldn't parse '%s' to a number. "
                "I had trouble with '%s'.", argv[1], end);
    printf("The square of %s is %g\n", argv[1], pow(in, 2));
}
