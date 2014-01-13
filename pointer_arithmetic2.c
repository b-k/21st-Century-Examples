/* Compile with:
export CFLAGS="-g -Wall -std=gnu11 -O3"  #the usual.
make pointer_arithmetic2
*/
#include <stdio.h>
typedef char* string;

int main(){
    string list[] = {"first", "second", "third", NULL};
    for (string *p=list; *p != NULL; p++){
        printf("%s\n", *p);
    }
}
