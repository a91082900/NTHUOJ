#include <stdio.h>
char bpuz[4][4], tmppuz[4][4];
int cnt[2500] = {};
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0}, max_step;

int calc() {
    int position = 0, offset = -1;
    for(int j = 0; j < 3; j++) {
        for(int k = 0; k < 3; k++) {
            if(tmppuz[j][k] == 'x')
                offset = 256 * (j*3+k);
            else {
                position += (tmppuz[j][k]-'0') << (j*3+k - (offset != -1));
            }
        }
    }
    return position + offset;
}

int check() {
    for(int j = 0; j < 3; j++) {
        for(int k = 0; k < 3; k++) {
            if(bpuz[j][k] != tmppuz[j][k])
                return 0;
        }
    }
    return 1;
}

int move(int r, int c, int step) {
    int newr, newc;
    char tmp;
    if(check()) {
       return 1;
    }

    if(step < 0)
        return 0;
    for(int dir = 0; dir < 4; dir++) {
        newr = r + dx[dir], newc = c + dy[dir];
        if(newr > 2 || newr < 0 || newc > 2 || newc < 0 || step < 1)
            continue;

        tmp = tmppuz[newr][newc];
        tmppuz[newr][newc] = tmppuz[r][c];
        tmppuz[r][c] = tmp;
        if(move(newr, newc, step-1)) {
            return 1;
        }

        tmp = tmppuz[newr][newc];
        tmppuz[newr][newc] = tmppuz[r][c];
        tmppuz[r][c] = tmp;
    }
    return 0;
}

int main() {
    int b_ones = 0, tmp_ones = 0;
    int n, position, offset, ans = 0;
    scanf("%d %d", &n, &max_step);
    for(int i = 0; i < n; i++) {
        position = 0, offset = -1;
        for(int j = 0; j < 3; j++) {
            for(int k = 0; k < 3; k++) {
                scanf(" %c", &tmppuz[j][k]);
                if(tmppuz[j][k] == 'x')
                    offset = 256 * (j*3+k);
                else {
                    position += (tmppuz[j][k]-'0') << (j*3+k - (offset != -1));
                }
            }
        }
        cnt[offset+position] += 1;
    }
    position = 0, offset = -1;
    for(int j = 0; j < 3; j++) {
        for(int k = 0; k < 3; k++) {
            scanf(" %c", &bpuz[j][k]);
            if(bpuz[j][k] == 'x')
                offset = 256 * (j*3+k);
            else {
                if(bpuz[j][k] == '1') {
                    position += 1 << (j*3+k - (offset != -1));
                    b_ones++;
                }
            }
        }
    }

    for(int i = 0; i < 2304; i++) {
        if(cnt[i]) {
            tmp_ones = 0;
            int xpos = i/256;
            int val = i - 256*xpos;
            //printf("xpos = %d, val = %d\n", xpos, val);
            for(int j = 0; j < 9; j++) {
                if(j == xpos) {
                    tmppuz[j/3][j%3] = 'x';
                }
                else {
                    if(val % 2) {
                        tmppuz[j/3][j%3] = '1';
                        tmp_ones++;
                    }
                    else
                        tmppuz[j/3][j%3] = '0';
                    val >>= 1;
                }
            }
            if(b_ones == tmp_ones)
                ans += cnt[i] * move(xpos/3, xpos%3, max_step);
        }
    }
    printf("%d\n", ans);

    return 0;
}
