#include <stdio.h>
long long dp[25][1005] = {0};
int w[25], v[25];
int main() {
    int n, maxw;
    scanf("%d%d", &n, &maxw);
    for(int i = 1; i <= n; i++) {
        scanf("%d%d", &w[i], &v[i]);
    }

    for(int j = 1; j <= n; j++) {
        for(int i = 1; i <= maxw; i++) {
            if(w[j] <= i && (dp[j-1][i-w[j]] + v[j]) > dp[j-1][i])
                dp[j][i] = dp[j-1][i-w[j]] + v[j];
            else
                dp[j][i] = dp[j-1][i];
        }

    }
    printf("%lld\n", dp[n][maxw]);
    /*for(int i = 0; i <= maxw; i++)
        for(int j = 1; j <= n; j++)
            printf("%d %d: %lld\n", i, j, dp[j][i]);*/
    return 0;
}
