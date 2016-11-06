#ifndef _NODE_H
#define _NODE_H

#include <stdint.h>

struct node {
    uint8_t state[8];
    uint8_t h; // cost from the node the goal
};

struct node *successor(struct node *node);
struct node *make_node(uint8_t *state);

#endif /* ifndef _NODE_H */
