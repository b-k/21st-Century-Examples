/* Compile with:
export LDLIBS="`pkg-config --libs apophenia`"
export CFLAGS="`pkg-config --cflags apophenia` -g -Wall -O3"
export CC=c99
make gsl_distance
*/
#include <apop.h>

double one_dist(gsl_vector *v1, void *v2){
    return apop_vector_distance(v1, v2);
}

long double distance(apop_data *data, apop_model *model){
    gsl_vector *target = model->parameters->vector;
    return -apop_map_sum(data, .fn_vp=one_dist, .param=target);
}

apop_model *min_distance= &(apop_model){
  .name="Minimum distance to a set of input points.", .p=distance, .vsize=-1};

int main(){
    apop_data *locations = apop_data_falloc((5, 2),
                            1.1, 2.2,
                            4.8, 7.4,
                            2.9, 8.6,
                            -1.3, 3.7,
                            2.9, 1.1);
    Apop_model_add_group(min_distance, apop_mle, .method= "NM simplex",
                                                  .tolerance=1e-5);
    apop_model *est = apop_estimate(locations, min_distance);
    apop_model_show(est);
}
