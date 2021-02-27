#include <stdio.h>

int queens[100] = {0}, cnt = 0;
int q;
// queens saves the index of queens in each line
int check(int i_chk, int j_chk) {
    for (int i = 0; i < i_chk; i++) { // 以不同橫列為準檢查
        int j = queens[i];
        if (j_chk == j) // 同一直行
            return 0;
        else if ((i + j) == (i_chk + j_chk)) // 同一斜線(左上-右下)
            return 0;
        else if ((i - j) == (i_chk - j_chk)) // 同一斜線(右上-左下)
            return 0;
    }
    return 1;
}

void eight_queen(int i) { // 第 i 行
    for (int j = 0; j < q; j++) { // enumurating index j in line i
        if (check(i, j)) {
            queens[i] = j;
            if (i == q-1) { // in line 8 and successfully placed 8 queens
                cnt++;
                queens[i] = 0;
                return;
            }
            eight_queen(i+1);
            queens[i] = 0; // backtrace to previous step
        }
    }
}

int main() {

    scanf("%d", &q);
    eight_queen(0);
    printf("%d Queens has %d Solutions!", q, cnt);
    return 0;
}
