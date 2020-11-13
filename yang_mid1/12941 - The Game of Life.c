#include <stdio.h>

int board[510][510] = {0};
int changed[505*505*3] = {0};
int main() {
    int n, m, t;
    scanf("%d%d%d", &n, &m, &t);
    for(int i = 1; i < n+1; i++) {
        for(int j = 1; j < m+1; j++) {
            scanf("%d", &board[i][j]);
        }
    }

    while(t--) {
        int idx = 0;
        for(int i = 1; i < n+1; i++) {
            for(int j = 1; j < m+1; j++) {
                int cnt = 0;
                cnt = board[i+1][j+1] + board[i][j+1] + board[i-1][j+1] +
                    board[i+1][j-1] + board[i][j-1] + board[i-1][j-1] +
                    board[i+1][j] + board[i-1][j];
                if(board[i][j] && (cnt < 2 || cnt > 3)) {
                    changed[idx++] = i;
                    changed[idx++] = j;
                    changed[idx++] = 0;
                }
                if(!board[i][j] && cnt == 3) {
                    changed[idx++] = i;
                    changed[idx++] = j;
                    changed[idx++] = 1;
                }
            }
        }

        for(int i = 0; i < idx; i += 3) {
            board[changed[i]][changed[i+1]] = changed[i+2];
        }
    }

    for(int i = 1; i < n+1; i++) {
        for(int j = 1; j < m+1; j++) {
            printf("%d%c", board[i][j], " \n"[j==m]);
        }
    }

    return 0;
}
