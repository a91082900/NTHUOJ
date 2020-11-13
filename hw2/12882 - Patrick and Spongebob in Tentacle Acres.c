#include <stdio.h>

int main() {

    int n, m, q, u, d, l, r;
    scanf("%d%d", &n, &m);
        int a[105][105];
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);

    scanf("%d", &q);
    int ans;
    while(q--) {
        ans = 0;
        scanf("%d%d%d%d", &u, &d, &l, &r);
        for(int i = u; i <= d; i++) {
            for(int j = l; j <= r; j++)
                if(a[i][j] > ans)
                    ans = a[i][j];
        }
        printf("%d\n", ans);
    }

    return 0;
}
