/* Compile with:
make errortuple CFLAGS="-g -Wall -std=gnu11 -O3"
*/
#include <stdio.h>
#include <math.h> //NaN, pow

#define make_err_s(intype, shortname) \
    typedef struct {                  \
        intype value;                 \
        char const *error;            \
    } shortname##_err_s;

make_err_s(double, double)
make_err_s(int, int)
make_err_s(char *, string)

double_err_s free_fall_energy(double time, double mass){
    double_err_s out = {};  //initialize to all zeros.
    out.error = time < 0      ? "negative time"
                : mass < 0    ? "negative mass"
                : isnan(time) ? "NaN time"
                : isnan(mass) ? "NaN mass"
                              : NULL;
    if (out.error) return out;

    double velocity = 9.8*time;
    out.value = mass*pow(velocity,2)/2.;
    return out;
}

#define Check_err(checkme, return_val)  \
    if (checkme.error) {fprintf(stderr, "error: %s\n", checkme.error); return return_val;}

int main(){
    double notime=0, fraction=0;
    double_err_s energy = free_fall_energy(1, 1);
    Check_err(energy, 1);
    printf("Energy after one second: %g Joules\n", energy.value);
    energy = free_fall_energy(2, 1);
    Check_err(energy, 1);
    printf("Energy after two seconds: %g Joules\n", energy.value);
    energy = free_fall_energy(notime/fraction, 1);
    Check_err(energy, 1);
    printf("Energy after 0/0 seconds: %g Joules\n", energy.value);
}
