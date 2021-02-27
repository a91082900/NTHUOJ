#include <stdio.h>

void print(long long k, long long l, long long r) {
    if(l>r || k <= 0)
        return;
    //printf("%lld %lld %lld\n", k, l, r);
    long long len, mid, i;
    len = 3*(1ll<<k)-3;
    mid = len/2;

    if(r < mid) {
        if(l == 0) {
            printf("O");
            l = 1;
        }
        print(k-1, l-1, r-1);
    }
    else if(l > mid) {
        int right_flag = 0;
        if(r == len-1) {
            right_flag = 1;
            r--;
        }
        print(k-1, l-mid-1, r-mid-1);
        if(right_flag) {
            printf("Q");
        }

    }
    else if(mid == l) {
        printf("u");
        print(k, mid+1, r);
    }
    else if(mid == r) {
        print(k, l, mid-1);
        printf("u");
    }
    else {
        print(k, l, mid-1);
        printf("u");
        print(k, mid+1, r);
    }
}

int main() {
    long long k, l, r;
    long long len, mid;
    while(scanf("%lld%lld%lld", &k, &l, &r) != EOF) {
        len = 3*(1ll<<k)-3;
        mid = len/2;

        //printf("len: %lld\nmid: %lld\n", len, mid);
        print(k, l, r);
        printf("\n");
    }
    return 0;
}
