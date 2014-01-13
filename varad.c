/* Compile with:
export CFLAGS="-g -Wall -std=gnu11 -O3"  #the usual.
make varad
*/
#include <stdio.h>

#define forloop(i, loopmax, ...) for(int i=0; i< loopmax; i++) \
                                        {__VA_ARGS__}

int main(){
    int sum=0;
    forloop(i, 10,
            sum += i;
            printf("sum to %i: %i\n", i, sum);
    )
}
