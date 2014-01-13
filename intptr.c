/* Compile with:
make intptr CFLAGS="-g -Wall -std=gnu11"
*/
#include <stdio.h>
#include <stdint.h> //intptr_t

int main(){
    char *astring = "I am somwhere in memory.";
    intptr_t location = (intptr_t)astring;
    printf("%s\n", (char*)location);
}
