#include <stdio.h>
long long res[22][22];
long long resi[1<<20] = {0};
int w[22], v[22];
int main() {
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    int n, m, q, a, b;
    scanf("%d %d", &n, &m);
    int enu = 1 << n;
    for(int i = 1; i <= n; i++) {
        scanf("%d %d", &w[i], &v[i]);
    }

    for(int i = 0; i < enu; i++) {
        int bin = 1, remain_w = m;
        long long r = 0;

        for(int j = 1; j <= n; j++, bin <<= 1) {
            if(j == a || j == b) {
                continue;
            }
            if(bin & i) {
                if(remain_w >= w[j]) {
                    r += v[j];
                    remain_w -= w[j];
                }
                else {
                    r = 0;
                    break;
                }
            }
        }
        resi[i] = r;
    }

    for(a = 1; a <= n; a++) {
        for(b = a+1; b <= n; b++) {
            long long maxr = 0;
            for(int i = 0; i < enu; i++) {
                if(!((1<<(a-1) & i) && (1<<(b-1) & i)))
                    continue;
                maxr = (resi[i] > maxr) ? resi[i] : maxr;
            }
            res[a][b] = maxr;
        }
    }

    scanf("%d", &q);
    while(q--) {
        scanf("%d %d", &a, &b);
        printf("%lld\n", res[a][b]);
    }
    return 0;
}
