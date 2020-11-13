#include <stdio.h>

int board[13][13], stars[13][13] = {0}, n;
long long max = -1e10;


int check(int r, int c) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(stars[i][j] && (i+j == r+c || i-j == r-c || i == r || j == c))
                return 0;
        }
    }
    return 1;

}

void backtrack(int line) {
    if(line == n) {
        long long current = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(stars[i][j])
                    current += board[i][j];
            }
        }

        max = (current > max) ? current : max;
        return;
    }

    for(int j = 0; j < n; j++) {
        if(check(line, j)) {
            //printf("find (%d, %d), checking line %d\n", line, j, line+1);
            stars[line][j] = 1;
            backtrack(line+1);
            stars[line][j] = 0; // back this line
        }
    }
}

int main() {

    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &board[i][j]);
        }
    }
    if(n == 2 || n == 3) {
        printf("no solution\n");
        return 0;
    }
    backtrack(0);
    printf("%lld\n", max);
    return 0;
}
