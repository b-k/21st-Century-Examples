/* See compilation notes in openmp_wc.c or mapreduce_wc.c*/
#include "string_utilities.h"

int wc(char *docname){
    char *doc = string_from_file(docname);
    if (!doc) return 0;
    char *delimiters = " `~!@#$%^&*()_-+={[]}|\\;:\",<>./?\n";
    ok_array *words = ok_array_new(doc, delimiters);
    if (!words) return 0;
    double out= words->length;
    ok_array_free(words);
    return out;
}
