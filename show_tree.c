/* Suggested makefile:
----------
P=show_tree
objects=process_dir.o process_dir.h
CFLAGS= -g -Wall -O3
LDLIBS=
CC=c99

$(P): $(objects)
----------
*/

#include <stdio.h>
#include "process_dir.h"

void print_dir(filestruct in){
    for (int i=0; i< in.depth-1; i++) printf("    ");
    printf("├ %s\n", in.name);
    for (int i=0; i< in.depth-1; i++) printf("    ");
    printf("└───┐\n");
}

void print_file(filestruct in){
    for (int i=0; i< in.depth; i++) printf("    ");
    printf("│ %s\n", in.name);
}

int main(int argc, char **argv){
    char *start = (argc>1) ? argv[1] : ".";
    printf("Tree for %s:\n", start ? start: "the current directory");
    process_dir(.name=start, .file_action=print_file, .directory_action=print_dir);
}
