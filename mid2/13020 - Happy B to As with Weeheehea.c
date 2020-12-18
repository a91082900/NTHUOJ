#include <stdio.h>
char bpuz[4][4], tmppuz[4][4];
int cnt[2500] = {}, become[2500] = {};
// if b can be made into state i within max_step steps, become[i] is 1, else 0
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0}, max_step;

int calc() {
    int position = 0, offset = -1;
    for(int j = 0; j < 3; j++) {
        for(int k = 0; k < 3; k++) {
            if(bpuz[j][k] == 'x')
                offset = 256 * (j*3+k);
            else {
                position += (bpuz[j][k]-'0') << (j*3+k - (offset != -1));
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

void move(int r, int c, int step) {
    int newr, newc;
    char tmp;

    if(step < 0)
        return;
    become[calc()] = 1;
    for(int dir = 0; dir < 4; dir++) {
        newr = r + dx[dir], newc = c + dy[dir];
        if(newr > 2 || newr < 0 || newc > 2 || newc < 0 || step < 1)
            continue;

        tmp = bpuz[newr][newc];
        bpuz[newr][newc] = bpuz[r][c];
        bpuz[r][c] = tmp;

        move(newr, newc, step-1);

        tmp = bpuz[newr][newc];
        bpuz[newr][newc] = bpuz[r][c];
        bpuz[r][c] = tmp;
    }
    return;
}

int main() {
    int start_x = 0, start_y = 0;
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
                offset = 256 * (j*3+k), start_x = j, start_y = k;
            else {
                position += (bpuz[j][k] - '0') << (j*3+k - (offset != -1));
            }
        }
    }
    move(start_x, start_y, max_step);
    for(int i = 0; i < 2304; i++) {
        ans += cnt[i] * become[i];
    }
    printf("%d\n", ans);

    return 0;
}
