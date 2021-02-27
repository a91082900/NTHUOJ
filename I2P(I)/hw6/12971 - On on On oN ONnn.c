#include <stdio.h>
int bulbs[25][25], n, m;
int min = 21;

int check() {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(!bulbs[i][j])
                return 0;
        }
    }
    return 1;

}

void switching(int r, int c) {
    bulbs[r][c] = !bulbs[r][c];
    bulbs[r+1][c] = !bulbs[r+1][c];
    bulbs[r-1][c] = !bulbs[r-1][c];
    bulbs[r][c+1] = !bulbs[r][c+1];
    bulbs[r][c-1] = !bulbs[r][c-1];
}

void backtrack(int r, int c, int do_switch, int cnt) {
    //printf("doing (%d, %d). switch = %d\n", r, c, do_switch);

    if(do_switch)
        switching(r, c);


    if(c < m) {
        backtrack(r, c+1, 0, cnt);
        backtrack(r, c+1, 1, cnt+1);
    }
    else {
        if(r == n) { // ended
            if(check())
                min = (cnt < min) ? cnt : min;
        }
        else {
            backtrack(r+1, 1, 0, cnt);
            backtrack(r+1, 1, 1, cnt+1);
        }
    }

    if(do_switch)
        switching(r, c);

}

int main() {

    scanf("%d%d", &n, &m);

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            scanf("%d", &bulbs[i][j]);
        }
    }

    backtrack(1, 1, 0, 0);
    backtrack(1, 1, 1, 1);
    if(min == 21)
        printf("no solution\n");
    else
        printf("%d\n", min);

    return 0;
}
