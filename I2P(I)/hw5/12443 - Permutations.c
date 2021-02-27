#include <stdio.h>
int p[10], filled[10] = {0}, n;

void backtrack(int s) {
    if(s == n+1) {
        for(int i = 1; i <= n; i++) {
            printf("%d ", p[i]);
        }
        printf("\n");
    }
    for(int i = 1; i <= n; i++) {
        if(!filled[i]) {
            filled[i] = 1;
            p[s] = i;
            backtrack(s+1);
            filled[i] = 0;
        }
    }
}

int main() {
    scanf("%d", &n);
    backtrack(1);
    return 0;
}
