/* Compile with:
export CFLAGS="-g -Wall -std=gnu11 -O3"  #the usual.
make boxes
*/
#include <stdio.h>

typedef struct {
    char *name;
    int left, right, up, down;
} direction_s;

void this_row(direction_s d); //these functions are below
void draw_box(direction_s d);

int main(){
    direction_s D = {.name="left", .left=1};
    draw_box(D);

    D = (direction_s) {"upper right", .up=1, .right=1};
    draw_box(D);

    draw_box((direction_s){});
}

void this_row(direction_s d){
    printf( d.left    ? "*..\n"
            : d.right ? "..*\n"
            : ".*.\n");
}

void draw_box(direction_s d){
    printf("%s:\n", (d.name ? d.name : "a box"));
    d.up                ? this_row(d) : printf("...\n");
    (!d.up && !d.down)  ? this_row(d) : printf("...\n");
    d.down              ? this_row(d) : printf("...\n");
    printf("\n");
}
