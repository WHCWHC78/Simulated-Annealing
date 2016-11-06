#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "node.h"
#include "simulated_annealing.h"

static void switch_node(struct node **fst, struct node *snd)
{
    free(*fst);
    (*fst) = snd;
}

struct node *simulated_annealing(struct problem *problem, uint32_t init_t)
{
    uint64_t t;
    struct node *node, *child;

    node = make_node(problem->initial_state);

    if (node->h == 0)
        return node;

    for (t = init_t; t; --t) {
        int8_t delta_e;

        child = successor(node);
        delta_e = (node->h) - (child->h);

        /** printf("%03u) ", t); */

        if (child->h == 0) {
            switch_node(&node, child);
            /** printf("done\n"); */

            break;
        } else if (delta_e > 0) {
            switch_node(&node, child);
            /** printf("skipped with delta_e = %d\n", delta_e); */
        } else {
            double p = exp(((float)delta_e) / t);

            if (p > 0.6)
                switch_node(&node, child);
            else
                printf("p = %f\n", p);
        }
    }

    return node;
}
