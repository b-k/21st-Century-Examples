#include <assert.h>

int main(){
    int list[100];
    int *list2 = list;    //Declares list2 as a pointer-to-int,
                          //pointing to the same block of memory list points to.

    *list2 = 7;           //list2 is a pointer-to-int, so *list2 is an int.

    assert(list[0] == 7);
}
