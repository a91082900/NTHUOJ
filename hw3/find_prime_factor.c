#include <stdio.h>
#include <math.h>
int prime[105] = {0};
int main() {
    unsigned int n;
    scanf("%u", &n);
    for(int i = n; i <= n; i++) {
        int flag = 1;
        int test = i;
        int square = sqrt(test);
        printf("test until %d\n", square);
        for(int j = 2; j <= test; j++) {
            if(!(test % j)) {
                flag = 0;
                test /= j;
                printf("find an prime factor %d\n", j);
                //prime[j]++; // we can ensure that j must be a prime
                j--;
                continue;
            }
            if(j > square && flag)
                break;
        }
        if(flag) // i is prime
            //prime[i]++;
            printf("%d is a prime\n", i);
    }
    /*unsigned long long ans = 1;
    for(int i = 0; i < 100; i++) {
        if(prime[i] != 0) {
            ans *= (prime[i]+1);
        }
    }
    printf("%llu", ans);*/
    return 0;
}
