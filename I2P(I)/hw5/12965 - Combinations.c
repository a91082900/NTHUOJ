#include <stdio.h>
int c[25] = {0}, map[25] = {0}, filled[25] = {0};
int n, k;

void combine(int startAt, int idx) {
    if(idx == k+1) {
        for(int i = 1; i <= k; i++) {
            printf("%d%c", c[i], " \n"[i==k]);
        }
        return;
    }
    for(int i = startAt; i <= n; i++) {
        if(!filled[i]) {
            filled[i] = 1;
            c[idx] = map[i];
            combine(i+1, idx+1);
            filled[i] = 0;
        }
    }
}
int main() {
    scanf("%d%d", &n, &k);

    for(int i = 1; i <= n; i++) {
        scanf("%d", &map[i]);
    }
    combine(1, 1);

    return 0;
}
