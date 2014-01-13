/* Compile with:
make copystructs2 CFLAGS="-g -Wall -O3 -std=gnu99"
*/
#include <assert.h>

int main(){
    int abc[] = {0, 1, 2};
    int *copy = abc;

    copy[0] = 3;
    assert(abc[0]==3);
}
