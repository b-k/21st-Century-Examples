/* Suggested makefile:
----------
P=unicode
objects=string_utilities.o
CFLAGS=`pkg-config --cflags glib-2.0` -g -Wall -std=gnu11 -O3
LDLIBS=`pkg-config --libs   glib-2.0`

$(P): $(objects)
----------
*/
/* Here is some sample UTF-8, so you can try this out.
   If this looks like a mess, your browser may have an easier time displaying it, or try
   iconv -f utf-8 -t UTF-16 < unicode.c > unicode.c.16

京冀洪涝灾情启动四级响应   #Today's headline from Chinadaily.com.
España, cercada por los mercados, prohíbe las operaciones especulativas  #Today's headline from elpais.es.
3.141592653589793238462643383279  #pi.

 */
#include <glib.h>
#include <locale.h> //setlocale
#include "string_utilities.h"
#include "stopif.h"

//Frees instring for you--we can't use it for anything else.
char *localstring_to_utf8(char *instring){
    GError *e=NULL;
    setlocale(LC_ALL, ""); //get the OS's locale.
    char *out = g_locale_to_utf8(instring, -1, NULL, NULL, &e);
    free(instring); //done with the original
    Stopif(!out, return NULL, "Trouble converting from your locale to UTF-8.");
    Stopif(!g_utf8_validate(out, -1, NULL), free(out); return NULL,
            "Trouble: I couldn't convert your file to a valid UTF-8 string.");
    return out;
}

int main(int argc, char **argv){
    Stopif(argc==1, return 1, "Please give a filename as an argument. "
                      "I will print useful info about it to uout.html.");

    char *ucs = localstring_to_utf8(string_from_file(argv[1]));
    Stopif(!ucs, return 1, "Exiting.");

    FILE *out = fopen("uout.html", "w");
    Stopif(!out, return 1, "Couldn't open uout.html for writing.");
    fprintf(out, "<head><meta http-equiv=\"Content-Type\" "
                 "content=\"text/html; charset=UTF-8\" />\n");
    fprintf(out, "This document has %li characters.<br>", g_utf8_strlen(ucs, -1));
    fprintf(out, "Its Unicode encoding required %zu bytes.<br>", strlen(ucs));
    fprintf(out, "Here it is, with each space-delimited element on a line "
                 "(with commentary on the first character):<br>");

    ok_array *spaced = ok_array_new(ucs, " \n");
    for (int i=0; i< spaced->length; i++, (spaced->elements)++){
        fprintf(out, "%s", *spaced->elements);
        gunichar c = g_utf8_get_char(*spaced->elements);
        if (g_unichar_isalpha(c)) fprintf(out, " (a letter)");
        if (g_unichar_isdigit(c)) fprintf(out, " (a digit)");
        if (g_unichar_iswide(c)) fprintf(out, " (wide, CJK)");
        fprintf(out, "<br>");
    }
    fclose(out);
    printf("Info printed to uout.html. Have a look at it in your browser.\n");
}
