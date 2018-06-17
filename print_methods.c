/* Compile with:
CFLAGS="-g -Wall -std=gnu11 -O3" make print_methods
*/
#include <stdio.h>
#include "print_typedef.h"

static void print_ad(textlist_s *in){
    printf("BUY THIS %s!!!! Features:\n", in->title);
    for (int i=0; i< in->len; i++)
        printf("∙ %s\n", in->items[i]);
}

static void print_song(textlist_s *in){
    printf("♫ %s ♫\nLyrics:\n\n", in->title);
    for (int i=0; i< in->len; i++)
        printf("\t%s\n", in->items[i]);
}

textlist_s save = {.title="God Save the Queen",
     .len=3, .items=(char*[]){
    "There's no future", "No future", "No future for me."},
    .print=print_song};

textlist_s spend = {.title="Never mind the Bollocks LP",
    .items=(char*[]){"By the Sex Pistols", "Anti-consumption themes"},
    .len=2, .print=print_ad};

#ifndef skip_main
int main(){
    save.print(&save);
    printf("\n-----\n\n");
    spend.print(&spend);
}
#endif
