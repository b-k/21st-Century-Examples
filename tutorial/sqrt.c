#include <math.h>   //The square root function is declared here.
#include <stdio.h>

int main(){
    double x = 49;
    printf("The truncated square root of x is %g.\n",
                                    x > 0 ? sqrt(x) : 0);
}
