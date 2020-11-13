#include <stdio.h>

char maze[505][505];
int old[505] = {0};
int main() {
        int n, m, q;
        scanf("%d %d", &n, &m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                scanf(" %c", &maze[i][j]);
            }
        }

        scanf("%d", &q);

        while(q--) {
            int col, ans = 0;
            scanf("%d", &col);
            int c = col;
            if(old[c]) {
                ans = old[col];
            }
            else {
                for(int level = 0; level < n; level++) {
                    if(maze[level][col-1] == '\\') { // check right
                        if(col == m) {
                            ans = -2;
                            break;
                        }
                        if(maze[level][col] == '\\')
                            col++;
                        else {
                            ans = -3;
                            break;
                        }
                    }
                    else { // check left
                        if(col == 1) {
                            ans = -1;
                            break;
                        }
                        if(maze[level][col-2] == '/')
                            col--;
                        else {
                            ans = -3;
                            break;
                        }
                    }
                }

                if(ans == 0) ans = col;
                old[c] = ans;
            }
            if(ans > 0) {
                printf("Position: %d\n", ans);
            }
            else if(ans == -1) {
                printf("Left!\n");
            }
            else if(ans == -2) {
                printf("Right!\n");
            }
            else {
                printf("Stuck QQ\n");
            }
        }

    return 0;
}
