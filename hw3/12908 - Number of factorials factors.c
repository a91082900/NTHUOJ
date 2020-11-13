#include <stdio.h>
#include <math.h>
int prime[105] = {0};
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 2; i <= n; i++) {
        int flag = 1;
        int test = i;
        int square = sqrt(test);
        for(int j = 2; j <= test; j++) {
            if(!(test % j)) {
                flag = 0;
                test /= j;
                //printf("Now i = %d and j = %d\n", test, j);
                prime[j]++; // we can ensure that j must be a prime
                j--;
                continue;
            }
            if(j > square && flag)
                break;
        }
        if(flag) // i is prime
            prime[i]++;
    }
    unsigned long long ans = 1;
    for(int i = 0; i < 100; i++) {
        ans *= (prime[i]+1);

    }
    printf("%llu", ans);
    return 0;
}
