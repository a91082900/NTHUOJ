#include <stdio.h>
char maze[303][303];
int portal[28][2]; // record capital letters' position
int walked[303][303], n, m;
int move(int from_x, int from_y, int to_x, int to_y, int d) {
    //printf("from_x = %d, from_y = %d, to_x = %d, to_y = %d\n", from_x, from_y, to_x, to_y);
    if(from_x < 0 || from_x > n-1 || to_x < 0 || to_x > n-1 || from_y < 0 || from_y > m-1 || to_y < 0 || to_y > m-1 || walked[to_x][to_y]) {
        return 0;
    }
    if(maze[to_x][to_y] == '#')
        return 0;
    if(maze[to_x][to_y] == '&')
        return 1;
    int idx = -1, tmpx, tmpy;
    walked[to_x][to_y] = 1;

    if(maze[to_x][to_y] >= 'a' && maze[to_x][to_y] <= 'z') {
        idx = maze[to_x][to_y]-'a';
        tmpx = to_x, tmpy = to_y;
        to_x = portal[idx][0], to_y = portal[idx][1];
        walked[to_x][to_y] = 1;
    }

    if(move(to_x, to_y, to_x-1, to_y, -1))
            return 1;
    if(move(to_x, to_y, to_x+1, to_y, 1))
            return 1;
    if(move(to_x, to_y, to_x, to_y-1, -2))
            return 1;
    if(move(to_x, to_y, to_x, to_y+1, 2))
            return 1;


    return 0;
}
int main() {
    int t, start_x = 0, start_y = 0;
    scanf("%d", &t);
    while(t--) {
        for(int i = 0; i < 26; i++) {
            portal[i][0] = portal[i][1] = 0;
        }

        scanf("%d %d", &n, &m);

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                walked[i][j] = 0;
                scanf(" %c", &maze[i][j]);
                if(maze[i][j] == '$')
                    start_x = i, start_y = j;
                if(maze[i][j] >= 'A' && maze[i][j] <= 'Z') {
                    portal[maze[i][j]-'A'][0] = i;
                    portal[maze[i][j]-'A'][1] = j;
                }
            }
        }

        if(move(start_x, start_y, start_x+1, start_y, 1)
           || move(start_x, start_y, start_x-1, start_y, -1)
           || move(start_x, start_y, start_x, start_y+1, 2)
           || move(start_x, start_y, start_x, start_y-1, -2))
            printf("Yes\n");

        else
            printf("No\n");

    }
    return 0;
}
