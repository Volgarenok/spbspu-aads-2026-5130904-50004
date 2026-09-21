#include "knapsack.h"
#include <string.h>

int knapsack_solve(Item items[], int n, int max_weight, int selected_indices[]) {
    if (n == 0 || max_weight <= 0) return 0;
    int max_items = (n < MAX_PERKS_IN_BUILD) ? n : MAX_PERKS_IN_BUILD;
    int dp[n + 1][max_weight + 1];
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= max_weight; w++) {
            dp[i][w] = 0;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= max_weight; w++) {
            dp[i][w] = dp[i-1][w];
            if (items[i-1].weight <= w) {
                int include = dp[i-1][w - items[i-1].weight] + items[i-1].power;
                if (include > dp[i][w]) dp[i][w] = include;
            }
        }
    }
    int w = max_weight;
    int count = 0;
    for (int i = n; i > 0 && count < max_items; i--) {
        if (dp[i][w] != dp[i-1][w]) {
            selected_indices[count++] = i - 1;
            w -= items[i-1].weight;
        }
    }
    return dp[n][max_weight];
}
