/* Compile with:
make sizesof CFLAGS="-g -Wall -std=gnu11 -O3"
*/
#include <stdio.h>

#define peval(cmd) printf(#cmd ": %g\n", cmd);

int main(){
    double *plist = (double[]){1, 2, 3};
    double list[] = {1, 2, 3};
    peval(sizeof(plist)/(sizeof(double)+0.0));
    peval(sizeof(list)/(sizeof(double)+0.0));
}
