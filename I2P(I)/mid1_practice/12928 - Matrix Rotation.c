#include <stdio.h>

int n[105][105];
int main() {
    int row, col, q;
    scanf("%d%d", &row, &col);

    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            scanf("%d", &n[i][j]);
        }
    }
    scanf("%d", &q);

    q %= 4;

    if(q == 1) {
        for(int j = 0; j < col; j++) {
            for(int i = row-1; i >= 0; i--) {
                printf("%d%c", n[i][j], " \n"[i==0]);
            }
        }
    }
    else if(q == 2) {
        for(int i = row-1; i >= 0; i--) {
            for(int j = col-1; j >= 0; j--) {
                printf("%d%c", n[i][j], " \n"[j==0]);
            }
        }
    }
    else if (q == 3) {
        for(int j = col-1; j >= 0; j--) {
            for(int i = 0; i < row; i++) {
                printf("%d%c", n[i][j], " \n"[i==row-1]);
            }
        }
    }
    else {
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                printf("%d%c", n[i][j], " \n"[j==col-1]);
            }
        }
    }

    return 0;
}
