#include <stdio.h>

unsigned long long stair[120] = {0L};
int main() {
    stair[0] = stair[1] = stair[2] = 1L;
    int n;
    scanf("%d", &n);
    for(int i = 3; i <= n; i++) {
        stair[i] = stair[i-3] + stair[i-1];
    }

    printf("%llu\n", stair[n]);

    return 0;
}
