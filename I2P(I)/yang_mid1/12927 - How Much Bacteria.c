#include <stdio.h>
int a[1000005] = {0};
int pre[1000005][35] = {0};
int main() {
    //freopen("testcase.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    int n, q, l, r;
    scanf("%d %d", &n, &q);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);

        for(int num = 0; num < 33; num++) {
            pre[i][num] = pre[i-1][num];

        }
        pre[i][a[i]]++;

    }

    while(q--) {
        int ans = 0;
        scanf("%d %d", &l, &r);
        for(int num = 0; num < 33; num++) {
            //printf("%d counts from index %d to %d : %d\n", num, l, r, pre[r][num]-pre[l-1][num]);
            if(pre[r+1][num]-pre[l][num]) {
                ans++;
            }
        }
        printf("%d\n", ans);
    }
    /*for(int i = 0; i <= n; i++) {

        for(int j = 0; j <= n; j++) {
            printf("%d ", pre[i][j]);
        }
        printf("\n");
    }*/

    return 0;
}

