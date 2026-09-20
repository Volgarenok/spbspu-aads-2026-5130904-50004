#ifndef HASH_H
#define HASH_H

#include "types.h"

// Hash functions
unsigned int hash1_str(const char *str);
unsigned int hash2_str(const char *str);

// Table initialization
void init_tables(TagHashTable *tags, PerkHashTable *perks, BuildHashTable *builds);

// Tag operations
bool tag_insert(TagHashTable *table, const char *key, Tag value);
bool tag_find(TagHashTable *table, const char *key, Tag *result);
bool tag_delete(TagHashTable *table, const char *key);

// Perk operations
bool perk_insert(PerkHashTable *table, const char *key, Perk value);
bool perk_find(PerkHashTable *table, const char *key, Perk *result);
bool perk_delete(PerkHashTable *table, const char *key);

// Build operations
bool build_insert(BuildHashTable *table, const char *key, Build value);
bool build_find(BuildHashTable *table, const char *key, Build *result);
bool build_delete(BuildHashTable *table, const char *key);

#endif
