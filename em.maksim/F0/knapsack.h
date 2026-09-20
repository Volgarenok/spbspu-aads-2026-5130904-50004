#ifndef KNAPSACK_H
#define KNAPSACK_H

#include "types.h"

typedef struct {
    char perk_name[MAX_NAME_LEN];
    int weight;
    int power;
} Item;

int knapsack_solve(Item items[], int n, int max_weight, int selected_indices[]);

#endif
