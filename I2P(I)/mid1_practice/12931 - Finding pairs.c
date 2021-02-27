#include <stdio.h>
int seq[10010] = {0};
int main() {
    //freopen("testcase.txt", "r", stdin);
    int n, in;
    unsigned long long ans = 0;
    scanf("%d", &n);
    while(n--) {
        scanf("%d", &in);
        seq[in]++;
    }

    for(int i = 0; i <= 10000; i++) {
        if(seq[i] > 1) { // pairs = C(q, 2) = q*(q-1) / 2
            ans  = ans + (unsigned long long)seq[i]*(seq[i]-1)/2;
        }
    }

    printf("%llu\n", ans);

    return 0;
}
