/* Compile with:
export CFLAGS="-g -Wall -std=gnu11 -O3"  #the usual.
make olden_varargs
*/
#define _GNU_SOURCE //cause stdio.h to include vasprintf
#include <stdio.h>  //printf, vasprintf
#include <stdarg.h> //va_start, va_end
#include <stdlib.h> //system, free
#include <assert.h>

int system_w_printf(char const *fmt, ...) __attribute__ ((format (printf,1,2)));

int system_w_printf(char const *fmt, ...){
    char *cmd;
    va_list argp;
    va_start(argp, fmt);
    vasprintf(&cmd, fmt, argp);
    va_end(argp);
    int out= system(cmd);
    free(cmd);
    return out;
}

int main(int argc, char **argv){
    assert(argc == 2);
    return system_w_printf("ls %s", argv[1]);
}
