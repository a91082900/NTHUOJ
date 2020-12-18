#include <stdio.h>
#include <math.h>
char s[105];
int n = 0;
int par[105], stack[105];

int find(int target, int from, int to) {
    for(int i = from; i < to; i++) {
        if(par[i] == target)
            return i;
    }
}

long long compute(int start, int end) {
    if(start >= end)
        return 0;

    if(par[start] == par[start+1])
        return 1 + compute(start+2, end);
    else {
        int idx = find(par[start], start+1, end);
        return 2 * compute(start+1, idx) + compute(idx+1, end);
    }

}

int main() {
    scanf("%d %s", &n, s);
    int head = 0, pn = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] == '(') {
            stack[head++] = pn;
            par[i] = pn++;
        }
        else {
            head--;
            par[i] = stack[head];
        }
    }
    printf("%lld\n", compute(0, n));
    return 0;
}
