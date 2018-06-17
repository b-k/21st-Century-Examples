#include <stdio.h>

void loops(int max){
    int i=0;
    do {
        printf("Hello #%i\n", i);
        i++;
    } while (i < max);      //Note the semicolon.
}

int main(){
    loops(3); //prints three greetings
    loops(0); //prints one greeting
}
