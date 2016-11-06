#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "problem.h"

// param[out]   initial_state: the initial state of the problem
// return void
static void random_initial_state(uint8_t *initial_state)
{
    // from the book
    initial_state[0] = 32;
    initial_state[1] = 41;
    initial_state[2] = 50;
    initial_state[3] = 27;
    initial_state[4] = 36;
    initial_state[5] = 45;
    initial_state[6] = 54;
    initial_state[7] = 47;

}

// param[in]    problem: our problem (8-queen)
// return void
void init_problem(struct problem *problem)
{
    random_initial_state(problem->initial_state);
}

