#include <stdio.h>

char board[16][16];

int check_dir(int i, int j, char c, int cnt, int direction) {
    if(i < 0 || j < 0 || i > 14 || j > 14)
        return 0;
    if(board[i][j] == c) {
        if(cnt == 4)
            return 1;
        if(direction == 1)
            return check_dir(i-1, j, c, cnt+1, direction);
        else if(direction == 2)
            return check_dir(i-1, j+1, c, cnt+1, direction);
        else if(direction == 3)
            return check_dir(i, j+1, c, cnt+1, direction);
        else if(direction == 4)
            return check_dir(i+1, j+1, c, cnt+1, direction);
    }
    return 0;
}

int check(int i, int j, char c) {
    if(check_dir(i, j, c, 0, 1) | check_dir(i, j, c, 0, 2) |
       check_dir(i, j, c, 0, 3) | check_dir(i, j, c, 0, 4) ) {
        return 1;
    }
    return 0;
}

int main() {
    int q = 0;
    scanf("%d", &q);
    int find = 0;
    while(q--) {
        find = 0;

        for(int i = 0; i < 15; i++) {
            for(int j = 0; j < 15; j++) {
                scanf("\n%c", &board[i][j]);
            }
        }

        for(int i = 0; i < 15; i++) {
            for(int j = 0; j < 15; j++) {
                if(check(i, j, 'b')) {
                    printf("black\n");
                    find = 1;
                    break;
                }
                else if(check(i, j, 'w')) {
                    printf("white\n");
                    find = 1;
                    break;
                }
            }
            if(find)
                break;
        }

        if(!find) {
            printf("none\n");
        }
    }
    return 0;
}
