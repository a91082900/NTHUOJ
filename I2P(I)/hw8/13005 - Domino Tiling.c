#include <stdio.h>
int board[5][25];
int n;
int check() {
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < n; j++)
            if(!board[i][j])
                return 0;
    return 1;
}
int tile(int x, int y) {
    //printf("%d %d\n",x ,y );
    int res = 0;
    if(check())
        return 1;
    if(board[x][y]) {
        if(x<3)
            return tile(x+1, y);
        else
            return tile(0, y+1);
    }
    if(x<2 && !board[x+1][y]) {
        board[x][y] = board[x+1][y] = 1;
        if(x<3)
            res += tile(x+1, y);
        else
            res += tile(0, y+1);
        board[x][y] = board[x+1][y] = 0;
    }
    if(y<n-1 && !board[x][y+1]) {
        board[x][y] = board[x][y+1] = 1;
        if(x<3)
            res += tile(x+1, y);
        else
            res += tile(0, y+1);
        board[x][y] = board[x][y+1] = 0;
    }
    return res;
}

int main() {
    scanf("%d", &n);
    printf("%d\n", tile(0, 0));
    return 0;
}
