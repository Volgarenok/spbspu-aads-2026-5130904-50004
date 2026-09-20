#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME_LEN 64
#define MAX_TAG_LEN 32
#define MAX_PERKS_IN_BUILD 4
#define MAX_WEIGHT_LIMIT 20
#define HASH_TABLE_SIZE 101

// Perk structure
typedef struct {
    char name[MAX_NAME_LEN];
    char tag[MAX_TAG_LEN];
    int weight;
    int power;
    char killer[MAX_NAME_LEN];
} Perk;

// Tag structure
typedef struct {
    char name[MAX_TAG_LEN];
    int perk_count;
} Tag;

// Build structure
typedef struct {
    char name[MAX_NAME_LEN];
    char perk_names[MAX_PERKS_IN_BUILD][MAX_NAME_LEN];
    int perk_count;
    int total_weight;
    int total_power;
} Build;

#endif
