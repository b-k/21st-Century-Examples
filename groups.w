@
/* See compilation notes in groupabm.w*/

@ Here in the introductory material, we include the header and specify
the global list of groups that the program makes use of. We'll need
new/copy/free functions for each group.

@c
#include "groups.h"

GList *group_list;
@<new group@>
@<copy group@>
@<free group@>

@ The new group method is boilerplate: we |malloc| some space,
fill the struct using designated initializers, and append the newly-formed
group to the list.

@<new group@>=
group_s *group_new(gsl_vector *position){
    static int id=0;
    group_s *out = malloc(sizeof(group_s));
    *out = (group_s) {.position=apop_vector_copy(position), .id=id++, .size=1};
    group_list = g_list_append(group_list, out);
    return out;
}

@ When an agent joins a group, the group is `copied' to the agent, but
there isn't any memory being copied: the group is simply modified to
accommodate the new person. We have to increment the reference count, which
is easy enough, and then modify the mean position.  If the mean position
without the $n$th person is $P_{n-1}$, and the $n$th person is at position
$p$, then the new mean position with the person, $P_n$ is the weighted sum.

$$P_n = \left( (n-1)P_{n-1}/n \right) + p/n.$$

We calculate that for each dimension.

@<copy group@>=
group_s *group_join(group_s *joinme, gsl_vector *position){
   int n = ++joinme->size;  //increment the reference count
   for (int i=0; i< joinme->position->size; i++){
       joinme->position->data[i] *= (n-1.)/n;
       joinme->position->data[i] += position->data[i]/n;
   }
   return joinme;
}

@ The `free` function really only frees the group when the reference count
is zero. When it isn't, then we need to run the data-augmenting formula
for the mean in reverse to remove a person.

@<free group@>=
void group_exit(group_s *leaveme, gsl_vector *position){
   int n = leaveme->size--;  //lower the reference count
   for (int i=0; i< leaveme->position->size; i++){
       leaveme->position->data[i] -= position->data[i]/n;
       leaveme->position->data[i] *= n/(n-1.);
   }
   if (leaveme->size == 0){ //garbage collect?
       gsl_vector_free(leaveme->position);
       group_list= g_list_remove(group_list, leaveme);
       free(leaveme);
   }
}

@ I played around a lot with different rules for how exactly people
evaluate the distance to the groups. In the end, I wound up using the $L_3$
norm. The standard distance is the $L_2$ norm, aka Euclidian distance,
meaning that the distance between $(x_1, y_1)$ and $(x_2, y_2)$ is
$\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$. This is $L_3$,
$\sqrt[3]{(x_1-x_2)^3+(y_1-y_2)^3}$.
This and the call to |apop_copy| above are the only calls to the Apophenia
library; you could write around them if you don't have that library on hand.

@<distance@>=
apop_vector_distance(g->position, position, .metric='L', .norm=3)

@ By `closest', I mean the group that provides the greatest benefit,
by having the smallest distance minus weighted size. Given the utility
function represented by the |dist| line, this is just a simple |for|
loop to find the smallest distance.

@c
group_s *group_closest(gsl_vector *position, double mass_benefit){
    group_s *fave=NULL;
    double smallest_dist=GSL_POSINF;
    for (GList *gl=group_list; gl!= NULL; gl = gl->next){
        group_s *g = gl->data;
        double dist= @<distance@> - mass_benefit*g->size;
        if(dist < smallest_dist){
            smallest_dist = dist;
            fave = g;
        }
    }
    return fave;
}

@ Gnuplot is automation-friendly. Here we get an animated simulation with
four lines of plotting code. The header |plot '-'| tells the system to plot
the data to follow, then we print the $(X, Y)$ positions, one to a line. The
final |e| indicates the end of the data set. The main program will set some
initial Gnuplot settings.

@c
void print_groups(){
    printf("plot '-' with points pointtype 6\n");
    for (GList *gl=group_list; gl!= NULL; gl = gl->next)
        apop_vector_print(((group_s*)gl->data)->position);
    printf("e\n");
}
