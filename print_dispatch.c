/* Compile with:
CFLAGS="-g -Wall -std=gnu11 -O3" make print_dispatch
*/
#define skip_main
#include "print_methods.c"

textlist_s recipe = {.title="Starfish and Coffee",
     .len=2, .items=(char*[]){"Starfish", "Coffee"}};

void textlist_print(textlist_s *in){
    if (in->print){
        in->print(in);
        return;
    }

    printf("Title: %s\n\nItems:\n", in->title);
    for (int i=0; i< in->len; i++)
        printf("\t%s\n", in->items[i]);
}

int main(){
    textlist_print(&save);
    printf("\n-----\n\n");
    textlist_print(&recipe);
}
