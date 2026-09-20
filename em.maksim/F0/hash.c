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

// Tag operations
bool tag_insert(TagHashTable *table, const char *key, Tag value) {
    unsigned int h1 = hash1_str(key);
    unsigned int h2 = hash2_str(key);

    // Check if exists
    if (table->table[h1].occupied && strcmp(table->table[h1].key, key) == 0)
        return false;
    if (table->table[h2].occupied && strcmp(table->table[h2].key, key) == 0)
        return false;

    // Try to insert
    for (int i = 0; i < 500; i++) {
        if (!table->table[h1].occupied) {
            strcpy(table->table[h1].key, key);
            table->table[h1].value = value;
            table->table[h1].occupied = true;
            table->count++;
            return true;
        }

        // Cuckoo displacement
        TagNode temp = table->table[h1];
        strcpy(table->table[h1].key, key);
        table->table[h1].value = value;
        table->table[h1].occupied = true;

        key = temp.key;
        value = temp.value;
        unsigned int new_h = (hash1_str(key) == h1) ? h2 : hash1_str(key);
        h1 = new_h;
    }
    return false;
}

bool tag_find(TagHashTable *table, const char *key, Tag *result) {
    unsigned int h1 = hash1_str(key);
    unsigned int h2 = hash2_str(key);

    if (table->table[h1].occupied && strcmp(table->table[h1].key, key) == 0) {
        *result = table->table[h1].value;
        return true;
    }
    if (table->table[h2].occupied && strcmp(table->table[h2].key, key) == 0) {
        *result = table->table[h2].value;
        return true;
    }
    return false;
}

bool tag_delete(TagHashTable *table, const char *key) {
    unsigned int h1 = hash1_str(key);
    unsigned int h2 = hash2_str(key);

    if (table->table[h1].occupied && strcmp(table->table[h1].key, key) == 0) {
        table->table[h1].occupied = false;
        table->count--;
        return true;
    }
    if (table->table[h2].occupied && strcmp(table->table[h2].key, key) == 0) {
        table->table[h2].occupied = false;
        table->count--;
        return true;
    }
    return false;
}

// Perk operations (Cuckoo Hashing)
bool perk_insert(PerkHashTable *table, const char *key, Perk value) {
    unsigned int h1 = hash1_str(key);
    unsigned int h2 = hash2_str(key);

    // Check duplicates
    if (table->table[h1].occupied && strcmp(table->table[h1].key, key) == 0)
        return false;
    if (table->table[h2].occupied && strcmp(table->table[h2].key, key) == 0)
        return false;

    for (int i = 0; i < 500; i++) {
        if (!table->table[h1].occupied) {
            strcpy(table->table[h1].key, key);
            table->table[h1].value = value;
            table->table[h1].occupied = true;
            table->count++;
            return true;
        }

        PerkNode temp = table->table[h1];
        strcpy(table->table[h1].key, key);
        table->table[h1].value = value;
        table->table[h1].occupied = true;

        key = temp.key;
        value = temp.value;
        unsigned int new_h = (hash1_str(key) == h1) ? h2 : hash1_str(key);
        h1 = new_h;
    }
    return false;
}

bool perk_find(PerkHashTable *table, const char *key, Perk *result) {
    unsigned int h1 = hash1_str(key);
    unsigned int h2 = hash2_str(key);

    if (table->table[h1].occupied && strcmp(table->table[h1].key, key) == 0) {
        *result = table->table[h1].value;
        return true;
    }
    if (table->table[h2].occupied && strcmp(table->table[h2].key, key) == 0) {
        *result = table->table[h2].value;
        return true;
    }
    return false;
}

bool perk_delete(PerkHashTable *table, const char *key) {
    unsigned int h1 = hash1_str(key);
    unsigned int h2 = hash2_str(key);

    if (table->table[h1].occupied && strcmp(table->table[h1].key, key) == 0) {
        table->table[h1].occupied = false;
        table->count--;
        return true;
    }
    if (table->table[h2].occupied && strcmp(table->table[h2].key, key) == 0) {
        table->table[h2].occupied = false;
        table->count--;
        return true;
    }
    return false;
}

// Build operations (simplified - linear probing)
bool build_insert(BuildHashTable *table, const char *key, Build value) {
    unsigned int h1 = hash1_str(key);

    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        unsigned int idx = (h1 + i) % HASH_TABLE_SIZE;
        if (!table->table[idx].occupied) {
            strcpy(table->table[idx].key, key);
            table->table[idx].value = value;
            table->table[idx].occupied = true;
            table->count++;
            return true;
        }
        if (strcmp(table->table[idx].key, key) == 0)
            return false; // Already exists
    }
    return false;
}

bool build_find(BuildHashTable *table, const char *key, Build *result) {
    unsigned int h1 = hash1_str(key);
    unsigned int h2 = hash2_str(key);

    if (table->table[h1].occupied && strcmp(table->table[h1].key, key) == 0) {
        *result = table->table[h1].value;
        return true;
    }
    if (table->table[h2].occupied && strcmp(table->table[h2].key, key) == 0) {
        *result = table->table[h2].value;
        return true;
    }
    return false;
}

bool build_delete(BuildHashTable *table, const char *key) {
    unsigned int h1 = hash1_str(key);
    unsigned int h2 = hash2_str(key);

    if (table->table[h1].occupied && strcmp(table->table[h1].key, key) == 0) {
        table->table[h1].occupied = false;
        table->count--;
        return true;
    }
    if (table->table[h2].occupied && strcmp(table->table[h2].key, key) == 0) {
        table->table[h2].occupied = false;
        table->count--;
        return true;
    }
    return false;
}
