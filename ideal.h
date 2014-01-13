/* This is cut down from ideal.c, providing only that which is needed for
   a header. The Python package will use this. */

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

double ideal_pressure_base(ideal_struct in);
