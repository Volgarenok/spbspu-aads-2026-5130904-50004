#include "types.h"
#include "hash.h"
#include "commands.h"
#include <stdio.h>
#include <string.h>

int main() {
    TagHashTable tags;
    PerkHashTable perks;
    BuildHashTable builds;
    
    init_tables(&tags, &perks, &builds);
    
    printf("<DEAD BY DAYLIGHT BUILD OPTIMIZER>\n");
    printf("<Type 'help' for commands>\n\n");
    
    char input[256];
    
    while (1) {
        printf("> ");
        fflush(stdout);
        
        if (!fgets(input, sizeof(input), stdin))
            break;
        
        // Remove newline
        input[strcspn(input, "\n")] = 0;
        
        // Skip empty lines
        if (strlen(input) == 0)
            continue;
        
        // Parse command
        char *cmd = strtok(input, " ");
        if (!cmd)
            continue;
        
        if (strcmp(cmd, "add-tag") == 0) {
            cmd_add_tag(&tags, strtok(NULL, " "));
        }
        else if (strcmp(cmd, "drop-tag") == 0) {
            cmd_drop_tag(&tags, strtok(NULL, " "));
        }
        else if (strcmp(cmd, "add-perk") == 0) {
            char *name = strtok(NULL, " ");
            char *tag = strtok(NULL, " ");
            int weight = atoi(strtok(NULL, " "));
            int power = atoi(strtok(NULL, " "));
            char *killer = strtok(NULL, " ");
            cmd_add_perk(&tags, &perks, name, tag, weight, power, killer);
        }
        else if (strcmp(cmd, "drop-perk") == 0) {
            cmd_drop_perk(&tags, &perks, &builds, strtok(NULL, " "));
        }
        else if (strcmp(cmd, "find-perk") == 0) {
            cmd_find_perk(&perks, strtok(NULL, " "));
        }
        else if (strcmp(cmd, "make-build") == 0) {
            char *name = strtok(NULL, " ");
            char *p1 = strtok(NULL, " ");
            char *p2 = strtok(NULL, " ");
            char *p3 = strtok(NULL, " ");
            char *p4 = strtok(NULL, " ");
            cmd_make_build(&perks, &builds, name, p1, p2, p3, p4);
        }
        else if (strcmp(cmd, "show-build") == 0) {
            cmd_show_build(&perks, &builds, strtok(NULL, " "));
        }
        else if (strcmp(cmd, "drop-build") == 0) {
            cmd_drop_build(&builds, strtok(NULL, " "));
        }
        else if (strcmp(cmd, "list-builds") == 0) {
            cmd_list_builds(&builds);
        }
        else if (strcmp(cmd, "optimize") == 0) {
            char *name = strtok(NULL, " ");
            int max_weight = atoi(strtok(NULL, " "));
            char *tag1 = strtok(NULL, " ");
            char *tag2 = strtok(NULL, " ");
            cmd_optimize(&tags, &perks, &builds, name, max_weight, tag1, tag2);
        }
        else if (strcmp(cmd, "filter") == 0) {
            cmd_filter_tag(&perks, strtok(NULL, " "));
        }
        else if (strcmp(cmd, "help") == 0) {
            cmd_help();
        }
        else {
            printf("<UNKNOWN COMMAND: %s>\n", cmd);
            printf("Type 'help' for available commands\n");
        }
    }
    
    printf("<GOODBYE>\n");
    return 0;
}
