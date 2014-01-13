/* Compile with:
export CFLAGS="-g -Wall -std=gnu11 -O3"  #the usual.
make ideal
*/
#include <stdio.h>

typedef struct {
    double pressure, moles, temp;
} ideal_struct;

/** Find the volume (in cubic meters) via the ideal gas law: V =nRT/P
Inputs:
pressure in atmospheres (default 1)
moles of material (default 1)
temperature in Kelvins (default freezing = 273.15)
  */
#define ideal_pressure(...) ideal_pressure_base((ideal_struct){.pressure=1,   \
                                        .moles=1, .temp=273.15, __VA_ARGS__})

double ideal_pressure_base(ideal_struct in){
    return 8.314 * in.moles*in.temp/in.pressure;
}

int main(){
    printf("volume given defaults: %g\n", ideal_pressure() );
    printf("volume given boiling temp: %g\n", ideal_pressure(.temp=373.15) );
    printf("volume given two moles: %g\n", ideal_pressure(.moles=2) );
    printf("volume given two boiling moles: %g\n",
                                ideal_pressure(.moles=2, .temp=373.15) );
}
