#include <stdlib.h>
#include <stdio.h>

#include "node.h"

/** @TODO: create hash table to speed up the search */
static uint8_t search_queen(uint8_t pos, uint8_t *state)
{
    uint8_t cnt, has_found;

    has_found = 0;

    for (cnt = 0; (has_found == 0) && (cnt < 8); ++cnt) {
        if (pos == state[cnt])
            has_found = 1;
    }

    return has_found;
}

static uint8_t h_func(uint8_t *state)
{
    uint8_t cnt, cost;

    cost = 0;

    for (cnt = 0; cnt < 8; ++cnt) {
        uint8_t col_cnt, col_left, row, row_left, row_col_left;

        row         = 1 + (state[cnt] / 8);
        row_left    = 8 - (state[cnt] / 8);
        col_left    = 8 - (state[cnt] % 8);

        // column iterate
        for (col_cnt = 1; col_cnt < col_left; ++col_cnt) {
            if (search_queen(state[cnt] + col_cnt, state))
                ++cost;
        }

        // row up iterate
        row_col_left = (row < col_left ? row : col_left);

        for (col_cnt = 1; col_cnt < row_col_left; ++col_cnt) {
            if (search_queen(state[cnt] - (8 * col_cnt) + col_cnt, state))
                ++cost;
        }

        // row down iterate
        row_col_left = (row_left < col_left ? row_left : col_left);

        for (col_cnt = 1; col_cnt < row_col_left; ++col_cnt) {
            if (search_queen(state[cnt] + (8 * col_cnt) + col_cnt, state))
                ++cost;
        }
    }

    return cost;
}

struct node *successor(struct node *node)
{
    struct node *child;
    uint8_t cnt;

    child = (struct node*)malloc(sizeof(struct node));

    for (cnt = 0; cnt < 8; ++cnt) {
        int r;

        r                   = rand() % 8;
        child->state[cnt]   = (r * 8) + (node->state[cnt] % 8);
    }

    child->h = h_func(child->state);

    return child;
}

struct node *make_node(uint8_t *state)
{
    struct node *tmp;
    uint8_t cnt;

    if (state == NULL)
        return NULL;

    tmp = (struct node*)malloc(sizeof(struct node));

    for (cnt = 0; cnt < 8; ++cnt)
        tmp->state[cnt] = state[cnt];

    tmp->h = h_func(tmp->state);

    return tmp;
}
