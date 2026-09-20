#include "hash.h"

unsigned int hash1_str(const char *str) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % HASH_TABLE_SIZE;
}

unsigned int hash2_str(const char *str) {
    unsigned int hash = 0;
    int i = 0;
    while (str[i]) {
        hash = (hash * 31) + str[i];
        i++;
    }
    return (hash + 1) % (HASH_TABLE_SIZE - 1);
}

void init_tables(TagHashTable *tags, PerkHashTable *perks, BuildHashTable *builds) {
    tags->count = 0;
    perks->count = 0;
    builds->count = 0;

    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        tags->table[i].occupied = false;
        perks->table[i].occupied = false;
        builds->table[i].occupied = false;
    }
}
