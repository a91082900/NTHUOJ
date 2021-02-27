#include <stdio.h>

char str[10005], tmp[10005];
int main() {
    int k, l, r, q;
    scanf("%s", str);
    scanf("%d", &q);
    int len;
    while(q--) {
        scanf("%d %d %d", &l, &r, &k);
        len = r - l + 1;
        k %= len;
        for(int i = 0; i < len - k; i++) {
            tmp[i] = str[l-1+i];
        }
        for(int i = 0; i < k; i++) {
            str[l-1+i] = str[r-k+i];
        }
        for(int i = 0; i < len - k; i++) {
            str[l-1+k+i] = tmp[i];
        }

    }
    printf("%s\n", str);
    return 0;
}
