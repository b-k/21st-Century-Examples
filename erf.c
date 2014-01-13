/* Compile with:
make erf LDLIBS="-lm" CFLAGS="-g -Wall -std=gnu11 -O3"
*/
#include <math.h>  //erf, sqrt
#include <stdio.h> //printf

int main(){
    printf("The integral of a Normal(0, 1) distribution "
           "between -1.96 and 1.96 is: %g\n", erf(1.96*sqrt(1/2.)));
}
