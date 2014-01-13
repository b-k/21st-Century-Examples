/* Suggested makefile:
----------
P=pthreads
objects=string_utilities.o
# To use Glib mutexes, some systems will require both glib-2.0 and gthread-2.0.
CFLAGS=`pkg-config --cflags glib-2.0` -g -Wall -std=gnu99 -O3 -pthread
LDLIBS=`pkg-config --libs glib-2.0` -pthread

$(P): $(objects)
----------
*/
#include "stopif.h"
#include "string_utilities.h"
#include <pthread.h>

typedef struct{
    int wc;
    char *docname;
} wc_struct;

void *wc(void *voidin){
    wc_struct *in = voidin;
    char *doc = string_from_file(in->docname);
    if (!doc) return NULL;   // in->wc remains zero.
    char *delimiters = " `~!@#$%^&*()_-+={[]}|\\;:\",<>./?\n";
    ok_array *words = ok_array_new(doc, delimiters);
    if (!words) return NULL;
    in->wc = words->length;
    ok_array_free(words);
    return NULL;
}

int main(int argc, char **argv){
    argc--;
    argv++;
    Stopif(!argc, return 0, "Please give some file names on the command line.");
    pthread_t threads[argc];
    wc_struct s[argc];
    for (int i=0; i< argc; i++){
        s[i] = (wc_struct){.docname=argv[i]};
        pthread_create(&threads[i], NULL, wc, &s[i]);
    }

    for (int i=0; i< argc; i++) pthread_join(threads[i], NULL);

    for (int i=0; i< argc; i++) printf("%s:\t%i\n",argv[i], s[i].wc);
}
