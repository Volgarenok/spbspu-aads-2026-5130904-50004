#ifndef COMMANDS_H
#define COMMANDS_H

#include "types.h"
#include "hash.h"

// Tag commands
void cmd_add_tag(TagHashTable *tags, const char *tag_name);
void cmd_drop_tag(TagHashTable *tags, const char *tag_name);

// Perk commands
void cmd_add_perk(TagHashTable *tags, PerkHashTable *perks, 
                  const char *name, const char *tag, int w, int p, const char *killer);
void cmd_drop_perk(TagHashTable *tags, PerkHashTable *perks, 
                   BuildHashTable *builds, const char *name);
void cmd_find_perk(PerkHashTable *perks, const char *name);

// Build commands
void cmd_make_build(PerkHashTable *perks, BuildHashTable *builds, 
                    const char *b_name, char *p1, char *p2, char *p3, char *p4);
void cmd_show_build(PerkHashTable *perks, BuildHashTable *builds, const char *b_name);
void cmd_drop_build(BuildHashTable *builds, const char *b_name);
void cmd_list_builds(BuildHashTable *builds);

// Advanced commands
void cmd_optimize(TagHashTable *tags, PerkHashTable *perks, BuildHashTable *builds,
                  const char *b_name, int max_w, char *t1, char *t2);
void cmd_filter_tag(PerkHashTable *perks, const char *tag_name);

// Help
void cmd_help();

#endif
