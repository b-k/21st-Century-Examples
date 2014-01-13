/* See compilation notes in dict_use.c*/
typedef struct keyval{
   char *key;
   void *value;
} keyval;

keyval *keyval_new(char *key, void *value);
keyval *keyval_copy(keyval const *in);
void keyval_free(keyval *in);
int keyval_matches(keyval const *in, char const *key);
