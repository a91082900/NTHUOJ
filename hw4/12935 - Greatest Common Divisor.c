#include <stdio.h>

int main() {
    int a, b;
    scanf("%d%d", &a, &b);

    while(b) {
        a %= b;
        a ^= b ^= a ^= b; // a = a ^ b, b = b ^ a,
    }
    printf("%d\n", a);
    return 0;
}
