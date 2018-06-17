/* See compilation notes in print_vtable_use.c*/
#include <glib.h>
#include "print_typedef.h"

extern GHashTable *print_fns;

typedef void (*print_fn_type)(textlist_s*);

void check_print_fn(print_fn_type pf);

#define print_hash_add(object, print_fn){                         \
    check_print_fn(print_fn);                                     \
    g_hash_table_insert(print_fns, (object)->print, print_fn);    \
}

void textlist_print_html(textlist_s *in);
