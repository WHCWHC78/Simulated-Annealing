#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <fcgi_stdio.h>

#include "node.h"
#include "simulated_annealing.h"

static void print_state(uint8_t *state);
static void print_result(struct node *node);

int main(void)
{
    struct problem problem;
    struct node *node;

    srand(time(NULL));
    init_problem(&problem);

    while(FCGI_Accept() >= 0) {
        char *q_str;

        printf( "Content-type: text/plain\r\n\r\n");

        q_str = getenv("QUERY_STRING");

        if (strcmp(q_str, "compute") == 0) {
            node = simulated_annealing(&problem, 400000);
            print_result(node);
            free(node);

            continue;
        } else if (strncmp(q_str, "init=", 5) == 0) {
            uint8_t isDone;

            if (strlen(q_str) != 21) {
                /** printf("You have to enter exactly 8 queens."); */
                printf("0");
                continue;
            }

            isDone = 1;

            for (uint8_t cnt = 0; cnt < 8; ++cnt) {
                uint8_t row/** , col */;

                row = (q_str[5 + (cnt * 2)] - 0x30 - 1);
                /** col = q_str[5 + (cnt * 2) + 1] - 0x30 - 1; */

                if (row >= 0 && row < 8) {
                    problem.initial_state[cnt] = (row * 8) + cnt;
                } else {
                    /** printf("Cannot configure queen number %u.", cnt + 1); */
                    isDone = 0;
                    problem.initial_state[cnt] = cnt;
                }
            }

            if (isDone)
                printf("1");
            else
                printf("0");

            /** printf("Configuration done."); */
        } else if (strcmp(q_str, "get_init") == 0) {
            print_state(problem.initial_state);
        } else {
            printf("0");
            /** printf( "Please specify a valid parameter.\n" */
            /**         "Your parameter is \"%s\".", q_str); */
        }
    }

    return 0;
}

static void print_state(uint8_t *state)
{
    for (uint8_t cnt = 0; cnt < 8; ++cnt) {
        printf("%u%u", (state[cnt] / 8) + 1, (state[cnt] % 8) + 1);
    }
}

static void print_result(struct node *node)
{
    print_state(node->state);
    printf("%02u", node->h);
}
