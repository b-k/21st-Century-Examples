/* Compile with:
export CFLAGS="-g -Wall -std=gnu11 -O3"  #the usual.
make macro_varargs
*/
#define _GNU_SOURCE //cause stdio.h to include vasprintf
#include <stdio.h>  //printf, vasprintf
#include <stdlib.h> //system
#include <assert.h>

#define System_w_printf(outval, ...) {           \
    char *string_for_systemf;                    \
    asprintf(&string_for_systemf, __VA_ARGS__);  \
    outval = system(string_for_systemf);         \
    free(string_for_systemf);                    \
}

int main(int argc, char **argv){
    assert(argc == 2);
    int out;
    System_w_printf(out, "ls %s", argv[1]);
    return out;
}
