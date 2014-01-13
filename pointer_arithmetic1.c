/* Compile with:
export CFLAGS="-g -Wall -std=gnu11 -O3"  #the usual.
make pointer_arithmetic1
*/
#include <stdio.h>

int main(){
    char *list[] = {"first", "second", "third", NULL};
    for (char **p=list; *p != NULL; p++){
        printf("%s\n", p[0]);
    }
}
