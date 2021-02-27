#include <stdio.h>
char maze[105][105];
int cnt, min, walked[105][105] = {0}, r, c;
int d[4][2] = {{1, 0}, {0, 1}, {-1, 0},{0, -1}};
int walk(int x, int y, int step) {
    if(maze[x][y] == 'F') {
        cnt++;
        return step;
    }

    int step_min = 100001, s;
    for(int i = 0; i < 4; i++) {
       if(x+d[i][0] < 0 || x+d[i][0] > r-1 || y+d[i][1] < 0 || y+d[i][1] > c-1 || maze[x+d[i][0]][y+d[i][1]] == '#')
            continue;
        if(!walked[x+d[i][0]][y+d[i][1]]) {
            walked[x+d[i][0]][y+d[i][1]] = 1;
            s = walk(x+d[i][0], y+d[i][1], step+1);
            if(s < step_min)
                step_min = s;
            walked[x+d[i][0]][y+d[i][1]] = 0;
        }
    }
    return step_min;
}
int main(){
    int n, start_x, start_y;
    scanf("%d", &n);
    while(n--) {
        cnt = 0, start_x = 0, start_y = 0;
        scanf("%d %d", &r, &c);
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                scanf("\n%c", &maze[i][j]);
                if(maze[i][j] == 'S') 
                    start_x = i, start_y = j;
            }
        }
        walked[start_x][start_y] = 1;
        min = walk(start_x, start_y, 0);
        walked[start_x][start_y] = 0;
        if(cnt)
            printf("%d %d\n", cnt, min);
        else
            printf("0 -1\n");
    }
    return 0;
}