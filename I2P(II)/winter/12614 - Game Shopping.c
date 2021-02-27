#include <stdio.h>

int cost[1005], wallet[1005];
int main() {
    int n, m;
    int c_idx = 0, w_idx = 0;

    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i++) {
        scanf("%d", &cost[i]);
    }
    for(int i = 0; i < m; i++) {
        scanf("%d", &wallet[i]);
    }
    int bought = 0;
    for(; c_idx < n && w_idx < m; c_idx++) {
        if(wallet[w_idx] >= cost[c_idx]) {
            bought++;
            w_idx++;
            //printf("He bought %d-th game with %d-th bill\n", c_idx, w_idx);
        }
    }
    printf("%d\n", bought);

    return 0;
}
