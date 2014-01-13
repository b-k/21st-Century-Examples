/* Compile with:
make copystructs CFLAGS="-g -Wall -O3 -std=gnu99"
*/
#include <assert.h>

typedef struct{
    int a, b;
    double c, d;
    int *efg;
} demo_s;

int main(){
    demo_s d1 = {.b=1, .c=2, .d=3, .efg=(int[]){4,5,6}};
    demo_s d2 = d1;

    d1.b=14;
    d1.c=41;
    d1.efg[0]=7;

    assert(d2.a==0);
    assert(d2.b==1);
    assert(d2.c==2);
    assert(d2.d==3);
    assert(d2.efg[0]==7);
}
