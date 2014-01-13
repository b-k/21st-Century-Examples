@
/* Suggested makefile:
----------
#GNU make knows how to run ctangle groupabm.w to generate groupabm.c.
#If you have TeX installed, also try "make groupabm.tex; pdftex groupabm.tex" .
P = groupabm
objects = groups.o
CFLAGS=`pkg-config --cflags glib-2.0 apophenia` -std=gnu11 -g -Wall -O3
LDLIBS=`pkg-config --libs glib-2.0 apophenia`

$(P): $(objects)
----------
*/

@* Initializations.

@ This is the part of the agent-based model with the handlers for the
|people| structures and the procedure itself.

At this point all interface with the groups happens via the
new/join/exit/print functions from |groups.cweb.c|. Thus, there is zero
memory management code in this file--the reference counting guarantees us
that when the last member exits a group, the group will be freed.

@c
#include "groups.h"

int pop=2000,
    periods=200,
    dimension=2;

@ In |main|, we'll initialize a few constants that we can't have as static
variables because they require math.

@<set up more constants@>=
    double  new_group_odds = 1./pop,
            mass_benefit = .7/pop;
    gsl_rng *r = apop_rng_alloc(1234);

@ The people in this simulation are pretty boring: they do not die, and do
not move. So the struct that represents them is simple, with just |position|
and a pointer to the group of which the agent is currently a member.

@c
typedef struct {
    gsl_vector *position;
    group_s *group;
} person_s;

@ The setup routine is also boring, and consists of allocating a uniform
random vector in two dimensions.

@c
person_s person_setup(gsl_rng *r){
    gsl_vector *posn = gsl_vector_alloc(dimension);
    for (int i=0; i< dimension; i++)
        gsl_vector_set(posn, i, 2*gsl_rng_uniform(r)-1);
    return (person_s){.position=posn};
}

@* Group membersip.

@ At the outset of this function, the person leaves its group.
Then, the decision is only whether to form a new group or join an existing one.

@c
void check_membership(person_s *p, gsl_rng *r,
                        double mass_benefit, double new_group_odds){
    group_exit(p->group, p->position);
    p->group = (gsl_rng_uniform(r) < new_group_odds)
             ? @<form a new group@>
             : @<join the closest group@>;
}

@
@<form a new group@>=
group_new(p->position)

@
@<join the closest group@>=
group_join(group_closest(p->position, mass_benefit), p->position)

@* Simulation startup.

@ The initialization of the population. Using CWEB's macros, it is at this point
self-documenting.

@c
void init(person_s *people, int pop, gsl_rng *r){
    @<position everybody@>
    @<start with ten groups@>
    @<everybody joins a group@>
}

@
@<position everybody@>=
    for (int i=0; i< pop; i++)
        people[i] = person_setup(r);

@ The first ten people in our list form new groups, but because everybody's
position is random, this is assigning the ten groups at random.

@<start with ten groups@>=
    for (int i=0; i< 10; i++)
        people[i].group = group_new(people[i].position);

@
@<everybody joins a group@>=
    for (int i=10; i< pop; i++)
        people[i].group = group_join(people[i%10].group, people[i].position);

@* Plotting.

@ This is the header for Gnuplot. I arrived at it by manually playing
around with Gnuplot, then writing down my final picks for settings here.

@<print the Gnuplot header@>=
printf("unset key;set xrange [-1:1]\nset yrange [-1:1]\n");

@ Gnuplot animation simply consists of sending a sequence of plot statements.
@<plot one animation frame@>=
print_groups();

@* |main|.

@ The |main| routine consists of a few setup steps, and a simple loop:
calculate a new state, then plot it.

@c
int main(){
    @<set up more constants@>
    person_s people[pop];
    init(people, pop, r);

    @<print the Gnuplot header@>
    for (int t=0; t< periods; t++){
        for (int i=0; i< pop; i++)
            check_membership(&people[i], r, mass_benefit, new_group_odds);
        @<plot one animation frame@>
    }
}
