/* See compilation notes in dict_use.c*/
#include "keyval.h"

extern void *dictionary_not_found;

typedef struct dictionary{
   keyval **pairs;
   int length;
} dictionary;

dictionary *dictionary_new (void);
dictionary *dictionary_copy(dictionary *in);
void dictionary_free(dictionary *in);
void dictionary_add(dictionary *in, char *key, void *value);
void *dictionary_find(dictionary const *in, char const *key);
