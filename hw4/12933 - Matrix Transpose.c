#include <stdio.h>

short n[1005][1005];
int main() {
    int row, col;
    scanf("%d%d", &row, &col);

    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            scanf("%d", &n[i][j]);
        }
    }


    for(int i = 0; i < col; i++) {
        for(int j = 0; j < row; j++) {
            printf("%d%c", n[j][i], " \n"[j==row-1]);
        }
    }

    return 0;
}
