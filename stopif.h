#include <stdio.h>
#include <stdlib.h> //abort

/** Set this to \c 's' to stop the program on an error.
    Otherwise, functions take error_action on failure.*/
char error_mode;

/** To where should I write errors? If this is \c NULL, write to \c stderr. */
FILE *error_log;

#define Stopif(assertion, error_action, ...) {                    \
        if (assertion){                                           \
            fprintf(error_log ? error_log : stderr, __VA_ARGS__); \
            fprintf(error_log ? error_log : stderr, "\n");        \
            if (error_mode=='s') abort();                         \
            else                 {error_action;}                  \
        } }


