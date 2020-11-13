#include <stdio.h>
int a[505];
int pre[505][505] = {0};
int main() {
    int n, q, l, r;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        for(int num = 0; num <= 500; num++) {
            //printf("num=%d, ai=%d\n", num, a[i]);
            if(num == a[i]) {
                pre[i+1][num] = pre[i][num] + 1;
            }
            else {
                pre[i+1][num] = pre[i][num];
            }
        }

    }

    scanf("%d", &q);
    while(q--) {
        int ans = 0, max_count = 0;
        scanf("%d %d", &l, &r);
        for(int num = 500; num >= 1; num--) {
            //printf("%d counts from index %d to %d : %d\n", num, l, r, pre[r][num]-pre[l-1][num]);
            if(pre[r][num]-pre[l-1][num] >= max_count) {
                ans = num;
                max_count = pre[r][num]-pre[l-1][num];
            }
        }
        printf("%d\n", ans);
    }
     /*for(int i = 1; i <= n; i++) {

        for(int j = 1; j <= n; j++) {
            printf("%d ", pre[i][j]);
        }
        printf("\n");
    }*/


}
