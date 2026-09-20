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
