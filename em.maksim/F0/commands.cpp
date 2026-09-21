#include "commands.h"
#include "knapsack.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void cmd_add_tag(TagHashTable *tags, const char *tag_name) {
    if (!tag_name) { printf("<INVALID: MISSING TAG NAME>\n"); return; }
    Tag t;
    strcpy(t.name, tag_name);
    t.perk_count = 0;
    if (tag_insert(tags, tag_name, t)) printf("<TAG ADDED: %s>\n", tag_name);
    else printf("<TAG ALREADY EXISTS>\n");
}

void cmd_drop_tag(TagHashTable *tags, const char *tag_name) {
    if (!tag_name) { printf("<INVALID: MISSING TAG NAME>\n"); return; }
    Tag t;
    if (!tag_find(tags, tag_name, &t)) { printf("<INVALID: TAG NOT FOUND>\n"); return; }
    if (t.perk_count > 0) { printf("<CANNOT DELETE: TAG HAS %d PERKS>\n", t.perk_count); return; }
    if (tag_delete(tags, tag_name)) printf("<TAG DELETED>\n");
}

void cmd_add_perk(TagHashTable *tags, PerkHashTable *perks, const char *name, const char *tag, int w, int p, const char *killer) {
    if (!name || !tag || !killer) { printf("<INVALID: MISSING ARGUMENTS>\n"); return; }
    Tag t;
    if (!tag_find(tags, tag, &t)) { printf("<INVALID: TAG '%s' NOT FOUND>\n", tag); return; }
    if (w < 1 || w > 5) { printf("<INVALID: WEIGHT MUST BE 1-5>\n"); return; }
    if (p < 1 || p > 10) { printf("<INVALID: POWER MUST BE 1-10>\n"); return; }
    Perk perk;
    strcpy(perk.name, name);
    strcpy(perk.tag, tag);
    perk.weight = w;
    perk.power = p;
    strcpy(perk.killer, killer);
    if (perk_insert(perks, name, perk)) {
        printf("<PERK ADDED: %s (w=%d, p=%d)>\n", name, w, p);
        t.perk_count++;
        tag_delete(tags, tag);
        tag_insert(tags, tag, t);
    } else {
        printf("<PERK ALREADY EXISTS>\n");
    }
}

void cmd_drop_perk(TagHashTable *tags, PerkHashTable *perks, BuildHashTable *builds, const char *name) {
    if (!name) { printf("<INVALID: MISSING PERK NAME>\n"); return; }
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
    Perk p;
    if (perk_find(perks, name, &p)) {
        Tag t;
        if (tag_find(tags, p.tag, &t)) {
            t.perk_count--;
            tag_delete(tags, p.tag);
            tag_insert(tags, p.tag, t);
        }
        if (perk_delete(perks, name)) printf("<PERK DELETED>\n");
    } else {
        printf("<INVALID: PERK NOT FOUND>\n");
    }
}

void cmd_find_perk(PerkHashTable *perks, const char *name) {
    if (!name) { printf("<INVALID: MISSING PERK NAME>\n"); return; }
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

void cmd_make_build(PerkHashTable *perks, BuildHashTable *builds, const char *b_name, char *p1, char *p2, char *p3, char *p4) {
    if (!b_name || !p1 || !p2 || !p3 || !p4) { printf("<INVALID: NEED BUILD NAME AND 4 PERKS>\n"); return; }
    char *perks_arr[4] = {p1, p2, p3, p4};
    for (int i = 0; i < 4; i++) {
        Perk temp;
        if (!perk_find(perks, perks_arr[i], &temp)) { printf("<INVALID: PERK '%s' NOT FOUND>\n", perks_arr[i]); return; }
        for (int j = i + 1; j < 4; j++) {
            if (strcmp(perks_arr[i], perks_arr[j]) == 0) { printf("<INVALID: DUPLICATE PERK '%s'>\n", perks_arr[i]); return; }
        }
    }
    Build b;
    strcpy(b.name, b_name);
    b.perk_count = 4;
    b.total_weight = 0;
    b.total_power = 0;
    for (int i = 0; i < 4; i++) {
        strcpy(b.perk_names[i], perks_arr[i]);
        Perk p;
        perk_find(perks, perks_arr[i], &p);
        b.total_weight += p.weight;
        b.total_power += p.power;
    }
    if (b.total_weight > MAX_WEIGHT_LIMIT) { printf("<INVALID: TOTAL WEIGHT %d EXCEEDS LIMIT %d>\n", b.total_weight, MAX_WEIGHT_LIMIT); return; }
    if (build_insert(builds, b_name, b)) {
        printf("<BUILD CREATED: %s>\n", b_name);
        printf("  Total Weight: %d\n", b.total_weight);
        printf("  Total Power: %d\n", b.total_power);
    } else {
        printf("<BUILD ALREADY EXISTS>\n");
    }
}

void cmd_show_build(PerkHashTable *perks, BuildHashTable *builds, const char *b_name) {
    if (!b_name) { printf("<INVALID: MISSING BUILD NAME>\n"); return; }
    Build b;
    if (!build_find(builds, b_name, &b)) { printf("<BUILD NOT FOUND>\n"); return; }
    printf("<BUILD: %s>\n", b.name);
    for (int i = 0; i < b.perk_count; i++) {
        Perk p;
        if (perk_find(perks, b.perk_names[i], &p)) {
            printf("  %d. %s (w=%d, p=%d, tag=%s)\n", i+1, p.name, p.weight, p.power, p.tag);
        }
    }
    printf("  TOTAL: weight=%d, power=%d\n", b.total_weight, b.total_power);
}

void cmd_drop_build(BuildHashTable *builds, const char *b_name) {
    if (!b_name) { printf("<INVALID: MISSING BUILD NAME>\n"); return; }
    if (build_delete(builds, b_name)) printf("<BUILD DELETED>\n");
    else printf("<BUILD NOT FOUND>\n");
}

void cmd_list_builds(BuildHashTable *builds) {
    printf("<BUILDS LIST>\n");
    bool found = false;
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        if (builds->table[i].occupied) {
            Build *b = &builds->table[i].value;
            printf("  [%d] %s (weight=%d, power=%d)\n", i, b->name, b->total_weight, b->total_power);
            found = true;
        }
    }
    if (!found) printf("  (no builds)\n");
    printf(">\n");
}

void cmd_filter_tag(PerkHashTable *perks, const char *tag_name) {
    if (!tag_name) { printf("<INVALID: MISSING TAG NAME>\n"); return; }
    printf("<PERKS WITH TAG '%s'>\n", tag_name);
    bool found = false;
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        if (perks->table[i].occupied && strcmp(perks->table[i].value.tag, tag_name) == 0) {
            Perk *p = &perks->table[i].value;
            printf("  - %s (w=%d, p=%d, killer=%s)\n", p->name, p->weight, p->power, p->killer);
            found = true;
        }
    }
    if (!found) printf("  (no perks found)\n");
    printf(">\n");
}

void cmd_optimize(PerkHashTable *perks, BuildHashTable *builds, const char *b_name, int max_w, char *t1, char *t2) {
    if (!b_name || !t1) { printf("<INVALID: NEED BUILD NAME, MAX WEIGHT, AND AT LEAST ONE TAG>\n"); return; }
    Item items[HASH_TABLE_SIZE];
    int count = 0;
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        if (perks->table[i].occupied) {
            Perk *p = &perks->table[i].value;
            bool match = false;
            if (strcmp(p->tag, t1) == 0) match = true;
            if (t2 && strcmp(p->tag, t2) == 0) match = true;
            if (match) {
                strcpy(items[count].perk_name, p->name);
                items[count].weight = p->weight;
                items[count].power = p->power;
                count++;
            }
        }
    }
    if (count == 0) { printf("<NO PERKS FOUND FOR SPECIFIED TAGS>\n"); return; }
    int indices[MAX_PERKS_IN_BUILD];
    for(int i=0; i<MAX_PERKS_IN_BUILD; i++) indices[i] = -1;
    int max_power = knapsack_solve(items, count, max_w, indices);
    Build b;
    strcpy(b.name, b_name);
    b.perk_count = 0;
    b.total_weight = 0;
    b.total_power = 0;
    printf("<OPTIMIZATION RESULT>\n");
    printf("  Max Power: %d (weight limit: %d)\n", max_power, max_w);
    printf("  Selected perks:\n");
    for (int i = 0; i < MAX_PERKS_IN_BUILD && indices[i] != -1; i++) {
        int idx = indices[i];
        strcpy(b.perk_names[b.perk_count], items[idx].perk_name);
        b.perk_count++;
        b.total_weight += items[idx].weight;
        b.total_power += items[idx].power;
        printf("    + %s (w=%d, p=%d)\n", items[idx].perk_name, items[idx].weight, items[idx].power);
    }
    printf("  TOTAL: weight=%d, power=%d\n", b.total_weight, b.total_power);
    if (build_insert(builds, b_name, b)) printf("<BUILD SAVED: %s>\n", b_name);
    else printf("<WARNING: Could not save build (name exists)>\n");
}

void cmd_help() {
    printf("<AVAILABLE COMMANDS>\n");
    printf("  TAGS:\n");
    printf("    add-tag <name>\n");
    printf("    drop-tag <name>\n");
    printf("  PERKS:\n");
    printf("    add-perk <name> <tag> <weight> <power> <killer>\n");
    printf("    drop-perk <name>\n");
    printf("    find-perk <name>\n");
    printf("    filter <tag>\n");
    printf("  BUILDS:\n");
    printf("    make-build <name> <perk1> <perk2> <perk3> <perk4>\n");
    printf("    show-build <name>\n");
    printf("    drop-build <name>\n");
    printf("    list-builds\n");
    printf("  ADVANCED:\n");
    printf("    optimize <name> <max_weight> <tag1> [tag2]\n");
    printf("  OTHER:\n");
    printf("    help\n");
    printf(">\n");
}
