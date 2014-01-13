/* Compile with:
export CFLAGS="-g -Wall -std=gnu11 -O3"  #the usual.
make floatfail
*/
#include <stdio.h>

int main(){
    printf("%f\n", (float)333334126.98);
    printf("%f\n", (float)333334125.31);
}
