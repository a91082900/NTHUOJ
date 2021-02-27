#include <stdio.h>
long long pre[1000010] = {0};
int main() {
    int n, q, l, r;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &pre[i]);
        pre[i] += pre[i-1];
    }

    scanf("%d", &q);
    while (q--) {
        scanf("%d%d", &l, &r);
        printf("%lld\n", pre[r]-pre[l-1]);
    }
    return 0;
}
