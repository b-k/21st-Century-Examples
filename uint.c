/* Compile with:
export CFLAGS="-g -Wall -std=gnu11 -O3"  #the usual.
make uint
*/
#include <stdio.h>

int main(){
    int neg = -2;
    size_t zero = 0;
    if (neg < zero) printf("Yes, -2 is less than 0.\n");
    else            printf("No, -2 is not less than 0.\n");
}
