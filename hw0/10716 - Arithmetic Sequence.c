#include <stdio.h>

int main() {
    int a, n, d;
    scanf("%d%d%d", &a, &n, &d);
    printf("%d %d", a + (n-1)*d, n*(2*a + (n-1)*d)/2);
    // an = a1+(n-1)d, sn=n(2a1+(n-1)d)/2
    return 0;
}
