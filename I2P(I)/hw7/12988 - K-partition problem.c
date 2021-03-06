#include <stdio.h>
int a[11], sum[6];
int n, k;
int put(int avg, int i, int ki) {
    if(i == n) {
        int flag = 1;
        for(int j = 0; j < k-1; j++) {
            if(sum[j] != sum[j+1]) {
                flag = 0;
                break;
            }
        }
        return flag;
    }
    sum[ki] += a[i];
    int f = 0;
    for(int j = 0; j < k; j++) {
        if(i == n-1 || a[i+1] + sum[j] <= avg)
            f = f | put(avg, i+1, j);
    }
    sum[ki] -= a[i];
    return f;


}

int main() {
    int q;
    scanf("%d", &q);
    while(q--) {
        int total = 0;
        scanf("%d %d", &n, &k);
        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            total += a[i];
        }
        int flag = 1;
        if(total % k == 0) {
            int avg = total / k;
            //printf("avg = %d\n", avg);
            for(int j = 0; j < k; j++) {
                if(a[0] < avg && put(avg, 0, j)) {
                    flag = 0;
                    printf("True\n");
                    break;
                }
            }
        }
        if(flag)
            printf("False\n");
    }
    return 0;
}
