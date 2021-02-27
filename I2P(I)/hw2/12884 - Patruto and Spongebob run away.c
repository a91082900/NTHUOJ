#include <stdio.h>
int a[505][505];
int main() {
    int n, k, line = 0, cnt = 1;
    scanf("%d", &n);

    k = 2*n;
    for(int t = 0; t < n; t++) {
        for(int i = 2*n-k; i < k; i++, cnt++) {
            a[t][i] = cnt;
        }
        k--;
        for(int i = 2*n-k; i < k+1; i++, cnt++) {
            a[i][2*n-1-t] = cnt;
        }
        for(int i = 2*n-k; i < k+1; i++, cnt++) {
            a[2*n-1-t][2*n-i-1] = cnt;
        }
        for(int i = 2*n-k; i < k; i++, cnt++) {
            a[2*n-i-1][t] = cnt;
        }
    }

    for(int i = 0; i < 2*n; i++) {
        for(int j = 0; j < 2*n; j++) {
            printf("%d%c", a[i][j], " \n"[j==2*n-1]);
        }
    }
    return 0;
}
