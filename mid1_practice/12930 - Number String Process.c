#include <stdio.h>
#include <string.h>
char s[1005];
int main() {
    //freopen("testcase.txt", "r", stdin);
    int n, q;
    int a, b, sz;
    scanf("%d %s %d", &n, s, &q);

    while(q--) {
        scanf("%d %d %d", &a, &b, &sz);
        long long x = 0, y = 0;
        for(int i = 0; i < sz; i++) {
            x = 10*x + s[a+i] - '0';
            y = 10*y + s[b+i] - '0';
        }
        printf("%lld\n", x*y);
        int i;

        for(i = 0; a+i+sz < b; i++) {

            s[a+i] = s[a+sz+i];
            s[a+sz+i] = 'X';
            /*for(int x = 0; x < n; x++)
                printf("%c", s[x]);
            printf("\n");*/
        }
        for(int j = 0; b+sz+j < n; i++, j++) {
            s[a+i]= s[b+sz+j];
            s[b+sz+j] = 'X';
            /*for(int x = 0; x < n; x++)
                printf("%c", s[x]);
            printf("\n");*/
        }
        n -= 2*sz;
        s[n] = '\0';
        //printf("%d: %s\n", q, s);
    }

    return 0;
}
