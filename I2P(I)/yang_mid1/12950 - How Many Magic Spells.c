#include <stdio.h>
#include <string.h>
char a[2005], b[2005];
int dp[2005][2005]; // l, r
//int pre[2005][2005];
int main() {
    int t, q, l, r, ans;
    int la, lb, lmin;
    scanf("%d", &t);
    while(t--) {
        scanf("%s %s", a, b);
        scanf("%d", &q);

        la = strlen(a);
        lb = strlen(b);
        for(int i = 0; i < la; i++) {
            for(int j = i+1; j < la; j++) {
                dp[i][j] = 0;
                //pre[i][j] = 0;
            }
        }

        for(int i = 0; i < la; i++) {
            dp[i][i] = (a[i] == b[0]);
            for(int j = i+1; j < la; j++) {
                if(!dp[i][j-1] || j-i >= lb)
                    dp[i][j] = 0;
                else
                    dp[i][j] = (a[j] == b[j-i]);
            }

            for(int j = i; j < la; j++) {
                if(i > 0)
                    dp[i][j] = dp[i-1][j] + dp[i][j];
            }
        }
        /*for(int i = 0; i < la; i++) {
            for(int j = 0; j < la; j++) {
                printf("%d ", dp[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        for(int i = 0; i < la; i++) {
            for(int j = 0; j < la; j++) {
                printf("%d ", pre[i][j]);
            }
            printf("\n");
        }

        for(int len = 1; len <= lmin; len++) {
            int flag = 1;
            for(int i = 0; i < len; i++) {
                //printf("%d:%c, %d:%c\n", r-len+i+1,
                if(a[r-len+i+1] != b[i]) {
                    flag = 0;
                    break;
                }
            }
            ans += flag;
        }*/

        while(q--) {
            scanf("%d %d", &l, &r);
            if(l > 0)
                printf("%d\n", dp[r][r] - dp[l-1][r] + 1);
            else
                printf("%d\n", dp[r][r] + 1);
        }
    }
    return 0;
}
