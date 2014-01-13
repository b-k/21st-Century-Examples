/* Compile with:
export CFLAGS="-g -Wall -std=gnu11 -O3"  #the usual.
make getenv

#Sample usage
reps=10 msg="Ha" ./getenv
msg="Ha" ./getenv
reps=20 msg=" " ./getenv
*/
#include <stdlib.h> //getenv, atoi
#include <stdio.h>  //printf

int main(){
    char *repstext = getenv("reps");
    int reps = repstext ? atoi(repstext) : 10;

    char *msg = getenv("msg");
    if (!msg) msg = "Hello.";

    for (int i=0; i< reps; i++)
        printf("%s\n", msg);
}
