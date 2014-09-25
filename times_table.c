/* Compile with:
export CFLAGS="-g -Wall -std=gnu11 -O3"  #the usual.
make times_table
*/
#include <math.h> //NAN
#include <stdio.h>

#define make_a_list(...) (double[]){__VA_ARGS__, NAN}

#define matrix_cross(list1, list2) matrix_cross_base(make_a_list list1, make_a_list list2)

void matrix_cross_base(double *list1, double *list2){
    int count1 = 0, count2 = 0;
    while (!isnan(list1[count1])) count1++;
    while (!isnan(list2[count2])) count2++;

    for (int i=0; i<count1; i++){
        for (int j=0; j<count2; j++)
            printf("%g\t", list1[i]*list2[j]);
        printf("\n");
    }
    printf("\n\n");
}

int main(){
    matrix_cross((1,2,4,8), (5, 11.11, 15));

    matrix_cross((17, 19, 23), (1,2,3,5,7,11,13));

    matrix_cross((1,2,3,5,7,11,13), (1));   //a column vector
}
