/* Compile with:
CFLAGS="-g -Wall -std=gnu11 -O3 -lm" make na
*/
#include <stdio.h>
#include <math.h> //isnan, NAN, nan

double ref;

double set_na(){
    if (!ref) ref=nan("21");
    return ref;
}

int is_na(double in){
    if (!ref) return 0;  //set_na was never called==>no NAs yet.

    char *cc = (char *)(&in);
    char *cr = (char *)(&ref);
    for (int i=0; i< sizeof(double); i++)
        if (cc[i] != cr[i]) return 0;
    return 1;
}

int main(){
    double x = set_na();
    double y = x;
    printf("Is x=set_na() NA? %i\n", is_na(x));
    printf("Is x=set_na() NAN? %i\n", isnan(x));
    printf("Is y=x NA? %i\n", is_na(y));
    printf("Is 0/0 NA? %i\n", is_na(0/0.));
    printf("Is 8 NA? %i\n", is_na(8));
}
