#include <stdio.h>
#include <math.h>
char s[105];
int n = 0;
long long compute(int i, int depth) {
    long long ans = 0;
    //printf("calculating %d, %d\n", i, depth);
    if(s[i] == '(') {
        ans += compute(i+1, depth+1);
    }
    else if(s[i] == ')') {
        ans += (long long) pow(2, depth-1);
        int d = depth, j = i;
        while(d) {
            d--;
            if(j < n-1 && s[j+1] == '(') {
                ans += compute(j+1, d);
                break;
            }
            j++;
        }
    }

    //printf("%d, %d returns %lld\n", i, depth, ans);
    return ans;

}

int main() {
    //long long ans = 0;
    scanf("%d %s", &n, s);
    printf("%lld\n", compute(0,0));
    return 0;
}
