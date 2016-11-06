#ifndef _PROBLEM_H
#define _PROBLEM_H

#include <stdint.h>

#define NOACT   0b0000
#define LEFT    0b0001
#define UP      0b0010
#define RIGHT   0b0100
#define DOWN    0b1000

struct problem {
    uint8_t initial_state[8]; // for eight queens
};

void init_problem(struct problem *problem);

#endif /* ifndef _PROBLEM_H */
