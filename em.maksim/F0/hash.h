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

#endif
