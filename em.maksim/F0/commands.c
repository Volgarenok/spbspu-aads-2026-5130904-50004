#include "commands.h"
#include "knapsack.h"
#include <stdio.h>

// ========== TAG COMMANDS ==========

void cmd_add_tag(TagHashTable *tags, const char *tag_name) {
    if (!tag_name) {
        printf("<INVALID: MISSING TAG NAME>\n");
        return;
    }

    Tag t;
    strcpy(t.name, tag_name);
    t.perk_count = 0;

    if (tag_insert(tags, tag_name, t))
        printf("<TAG ADDED: %s>\n", tag_name);
    else
        printf("<TAG ALREADY EXISTS>\n");
}

void cmd_drop_tag(TagHashTable *tags, const char *tag_name) {
    if (!tag_name) {
        printf("<INVALID: MISSING TAG NAME>\n");
        return;
    }

    Tag t;
    if (!tag_find(tags, tag_name, &t)) {
        printf("<INVALID: TAG NOT FOUND>\n");
        return;
    }

    if (t.perk_count > 0) {
        printf("<CANNOT DELETE: TAG HAS %d PERKS>\n", t.perk_count);
        return;
    }

    if (tag_delete(tags, tag_name))
        printf("<TAG DELETED>\n");
}

// ========== PERK COMMANDS ==========

void cmd_add_perk(TagHashTable *tags, PerkHashTable *perks,
                  const char *name, const char *tag, int w, int p, const char *killer) {
    if (!name || !tag || !killer) {
        printf("<INVALID: MISSING ARGUMENTS>\n");
        return;
    }

    // Check tag exists
    Tag t;
    if (!tag_find(tags, tag, &t)) {
        printf("<INVALID: TAG '%s' NOT FOUND>\n", tag);
        return;
    }

    // Validate stats
    if (w < 1 || w > 5) {
        printf("<INVALID: WEIGHT MUST BE 1-5>\n");
        return;
    }
    if (p < 1 || p > 10) {
        printf("<INVALID: POWER MUST BE 1-10>\n");
        return;
    }

    Perk perk;
    strcpy(perk.name, name);
    strcpy(perk.tag, tag);
    perk.weight = w;
    perk.power = p;
    strcpy(perk.killer, killer);

    if (perk_insert(perks, name, perk)) {
        printf("<PERK ADDED: %s (w=%d, p=%d)>\n", name, w, p);

        // Update tag counter
        t.perk_count++;
        tag_delete(tags, tag);
        tag_insert(tags, tag, t);
    } else {
        printf("<PERK ALREADY EXISTS>\n");
    }
}

void cmd_drop_perk(TagHashTable *tags, PerkHashTable *perks,
                   BuildHashTable *builds, const char *name) {
    if (!name) {
        printf("<INVALID: MISSING PERK NAME>\n");
        return;
    }

    // Check if used in builds
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        if (builds->table[i].occupied) {
            Build *b = &builds->table[i].value;
            for (int j = 0; j < b->perk_count; j++) {
                if (strcmp(b->perk_names[j], name) == 0) {
                    printf("<CANNOT DELETE: USED IN BUILD '%s'>\n", b->name);
                    return;
                }
            }
        }
    }

    // Get tag to update counter
    Perk p;
    if (perk_find(perks, name, &p)) {
        Tag t;
        if (tag_find(tags, p.tag, &t)) {
            t.perk_count--;
            tag_delete(tags, p.tag);
            tag_insert(tags, p.tag, t);
        }

        if (perk_delete(perks, name))
            printf("<PERK DELETED>\n");
    } else {
        printf("<INVALID: PERK NOT FOUND>\n");
    }
}

void cmd_find_perk(PerkHashTable *perks, const char *name) {
    if (!name) {
        printf("<INVALID: MISSING PERK NAME>\n");
        return;
    }

    Perk p;
    if (perk_find(perks, name, &p)) {
        printf("<PERK: %s>\n", p.name);
        printf("  Killer: %s\n", p.killer);
        printf("  Tag: %s\n", p.tag);
        printf("  Weight: %d\n", p.weight);
        printf("  Power: %d\n", p.power);
    } else {
        printf("<PERK NOT FOUND>\n");
    }
}
