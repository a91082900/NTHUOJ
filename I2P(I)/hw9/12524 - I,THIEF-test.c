#include <stdio.h>
#include <stdbool.h>
#define max(a, b) ((a) > (b) ? (a) : (b))
bool chosen[105] = {};
int dp[105][2] = {}, houses[105];
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &houses[i]);
    }

    for(int i = 1; i <= n; i++){
        dp[i][0] = max(dp[i-1][0], dp[i-1][1]);
        dp[i][1] = dp[i-1][0] + houses[i];
    }

    /*for(int i = 1; i <= n; i++){
        printf("%d ", dp[i][0]);
    }
    printf("\n");
    for(int i = 1; i <= n; i++){
        printf("%d ", dp[i][1]);
    }
    printf("\n");*/

    int idx = dp[n][1] > dp[n][0];
    chosen[n] = idx;
    for(int i = n; i > 1; i--)  {
        if(idx) {
            idx = false;
        }
        else {
            if(dp[i][0] == dp[i-1][1]) {
                chosen[i-1] = true;
                idx = true;
            }
        }
    }

    for(int i = 1; i <= n; i++)  {
        if(chosen[i])
            printf("%d ", i);
    }
    return 0;
}
