#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <fcgi_stdio.h>

#include "node.h"
#include "simulated_annealing.h"

int main(void)
{
    struct problem problem;
    struct node *node;

    srand(time(NULL));
    init_problem(&problem);

    node = simulated_annealing(&problem, 300000);

    for (uint8_t i = 0; i < 8; ++i) {
        printf("node->state[%u] = %u\n", i, node->state[i]);
    }

    printf("node->h = %u\n", node->h);
    free(node);

    return 0;
}
