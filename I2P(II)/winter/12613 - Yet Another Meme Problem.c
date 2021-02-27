#include <stdio.h>

int main() {
    int q;
    long long A, B;
    scanf("%d", &q);
    while(q--) {
        int len = 0, all_nine = 1;
        scanf("%lld %lld", &A, &B);
        while(B) {
            if(B % 10 != 9)
                all_nine = 0;
            B /= 10;
            len++;
        }
        printf("%lld\n", A*(len - 1 + all_nine));
    }
    return 0;
}
