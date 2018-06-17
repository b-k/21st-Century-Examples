#include <stdio.h>

int main(){
    double pi= 3.14159265; //POSIX defines the constant M_PI in math.h, by the way.
    int count= 10;
    printf("%g times %i = %g.\n", pi, count, pi*count);
}
