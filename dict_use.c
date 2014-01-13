/* Compile with:
    mkdir -p hash
    cp dict_use.c dict.h dict.c keyval.c keyval.h dict_test.c hash
    cp dict.automake hash/Makefile.am
    cd hash

    touch NEWS README AUTHORS ChangeLog #still cheating

    autoscan
    sed -e 's/FULL-PACKAGE-NAME/hashdict/'        \
        -e 's/VERSION/1/'                         \
        -e 's|BUG-REPORT-ADDRESS|/dev/null|'      \
        -e '12i\
              AM_INIT_AUTOMAKE'                   \
        -e '13i\
              LT_INIT'                            \
        -e '14i\
              AC_CHECK_LIB([glib-2.0],[g_free])'  \
        -e 's|PROG_CC|PROG_CC_C99|'               \
           < configure.scan > configure.ac

    autoreconf -i > /dev/null
    ./configure
    make distcheck
    make
*/
#include <stdio.h>
#include "dict.h"

int main(){
    int zero = 0;
    float one = 1.0;
    char two[] = "two";
    dictionary *d = dictionary_new();
    dictionary_add(d, "an int", &zero);
    dictionary_add(d, "a float", &one);
    dictionary_add(d, "a string", &two);
    printf("The integer I recorded was: %i\n", *(int*)dictionary_find(d, "an int"));
    printf("The string was: %s\n", (char*)dictionary_find(d, "a string"));
    dictionary_free(d);
}
