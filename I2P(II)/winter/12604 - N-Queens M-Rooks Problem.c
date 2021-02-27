#include <stdio.h>
#define ROOK 1
#define QUEEN 2

int board[10][2]; // 0: type, 1: col
int queens, rooks, ans;

int check(int piece, int line, int j) {
    for(int r = 0; r < line; r++) {
        if(j == board[r][1])
            return 0;
        if(board[r][0] == QUEEN || piece == QUEEN) {
            if(line+j == r+board[r][1] || line-j == r-board[r][1])
                return 0;
        }
    }
    return 1;
}
void place(int i, int remain_r, int remain_q) {
    if(remain_q == 0 && remain_r == 0) {
        ans++;
        return;
    }
    if(remain_q < 0 || remain_r < 0)
        return;
    for(int c = 0; c < queens+rooks; c++) {
        if(check(ROOK, i+1, c)) {
            board[i+1][0] = ROOK;
            board[i+1][1] = c;
            place(i+1, remain_r-1, remain_q);
        }
        if(check(QUEEN, i+1, c)) {
            board[i+1][0] = QUEEN;
            board[i+1][1] = c;
            place(i+1, remain_r, remain_q-1);
        }
    }
}

int main() {
    while(scanf("%d %d", &queens, &rooks) != EOF) {
        ans = 0;
        if(queens == 0) {
            ans = 1;
            while(rooks)
                ans *= rooks--;
        }
        else {
            for(int c = 0; c < queens+rooks; c++) {
                board[0][0] = ROOK;
                board[0][1] = c;
                place(0, rooks-1, queens);

                board[0][0] = QUEEN;
                board[0][1] = c;
                place(0, rooks, queens-1);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
