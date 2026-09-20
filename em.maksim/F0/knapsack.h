#ifndef KNAPSACK_H
#define KNAPSACK_H

#include "types.h"

typedef struct {
    char perk_name[MAX_NAME_LEN];
    int weight;
    int power;
} Item;

// Solve 0/1 Knapsack problem
// Returns maximum power, fills selected_indices with chosen items
int knapsack_solve(Item items[], int n, int max_weight, int selected_indices[]);

#endif
