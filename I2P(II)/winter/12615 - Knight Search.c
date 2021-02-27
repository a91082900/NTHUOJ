#include <stdio.h>

char str[] = "ICPCASIASG";
char board[105][105];
int start[100][2], start_idx = 0, n;
int find(int word, int i, int j) {
    if(i < 0 || i >= n || j < 0 || j >= n)
        return 0;
    if(board[i][j] == str[word]) {
        if(word == 9)
            return 1;
        else {
            return find(word+1, i+2, j+1) |
                find(word+1, i+1, j+2) |
                find(word+1, i+2, j-1) |
                find(word+1, i+1, j-2) |
                find(word+1, i-2, j+1) |
                find(word+1, i-1, j+2) |
                find(word+1, i-2, j-1) |
                find(word+1, i-1, j-2);
        }
    }
    return 0;
}

int main() {
    scanf("%d %d", &n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf(" %c", &board[i][j]);
            if(board[i][j] == 'I') {
                start[start_idx][0] = i;
                start[start_idx++][1] = j;
            }
        }
    }

    for(int i = 0; i < start_idx; i++) {
        if(find(0, start[i][0], start[i][1])) {
            printf("YES\n");
            return 0;
        }
    }
    printf("NO\n");
    /*for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf(" %c", board[i][j]);
        }
        printf("\n");
    }*/
    return 0;
}
