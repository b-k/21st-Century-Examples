/* See compilation notes in simple_cplx.c*/
#include <complex.h> //nice names for C's complex types
#include <gsl/gsl_vector.h> //gsl_vector_complex

gsl_vector_complex *cvec_dot_gslcplx(gsl_vector_complex *v, gsl_complex x);
gsl_vector_complex *vec_dot_gslcplx(gsl_vector *v, gsl_complex x);
gsl_vector_complex *cvec_dot_c(gsl_vector_complex *v, complex double x);
gsl_vector_complex *vec_dot_c(gsl_vector *v, complex double x);
void gsl_vector_complex_print(gsl_vector_complex *v);

#define gsl_cplx_from_c99(x) (gsl_complex){.dat= {creal(x), cimag(x)}}

complex double ddot (complex double x, complex double y);

#define dot(x,y)  _Generic((x),                                 \
                    gsl_vector*: dot_given_vec(y),              \
                    gsl_vector_complex*: dot_given_cplx_vec(y), \
                    default: ddot)((x),(y))

#define dot_given_vec(y) _Generic((y),                          \
                        gsl_complex: vec_dot_gslcplx,           \
                        default: vec_dot_c)

#define dot_given_cplx_vec(y) _Generic((y),                     \
                        gsl_complex: cvec_dot_gslcplx,          \
                        default: cvec_dot_c)


