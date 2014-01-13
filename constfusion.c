/* Compile with:
export CFLAGS="-g -std=gnu11 -O3"   #The usual, but without -Wall
make constfusion                    #Still, this will throw a warning
*/
#include <stdio.h>

int main(){
    int *var;
    int const **constptr = &var; // the line that sets up the failure
    int const fixed = 20;
    *constptr = &fixed;          // 100% valid
    *var = 30;
    printf("x=%i y=%i\n", fixed, *var);
}
