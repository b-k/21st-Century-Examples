#ifndef textlist_s_h
#define textlist_s_h

typedef struct textlist_s {
    char *title;
    char **items;
    int len;
    void (*print)(struct textlist_s*);
} textlist_s;

#endif
