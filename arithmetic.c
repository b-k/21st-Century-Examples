/* Compile with:
make arithmetic CFLAGS="-g -Wall -std=gnu11 -O3"
*/
#include <stdio.h>

int main(){
    int evens[5] = {0, 2, 4, 6, 8};
    printf("The first even number is, of course, %i\n", *evens);
    int *positive_evens = &evens[1];
    printf("The first positive even number is %i\n", positive_evens[0]);
}
