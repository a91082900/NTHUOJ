#include <stdio.h>
char init[4][4], fin[4][4];
int move(int from_x, int from_y, int to_x, int to_y, int d, int step) {
    if(from_x < 0 || from_x > 2 || from_y < 0 || from_y > 2 || to_x < 0 || to_x > 2 || to_y < 0 || to_y > 2) {
        return 0;
    }

    if(step <= 0)
        return 0;


    char tmp = init[from_x][from_y];
    init[from_x][from_y] = init[to_x][to_y];
    init[to_x][to_y] = tmp;

    int flag = 1;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(init[i][j] != fin[i][j])
                flag = 0;
        }
    }
    if(flag)
        return 1;
    if(step > 1) {
        if(d != 1) {
            if(move(to_x, to_y, to_x-1, to_y, -1, step-1))
                return 1;
        }
        if(d != -1) {
            if(move(to_x, to_y, to_x+1, to_y, 1, step-1))
                return 1;
        }
        if(d != 2) {
            if(move(to_x, to_y, to_x, to_y-1, -2, step-1))
                return 1;
        }
        if(d != -2) {
            if(move(to_x, to_y, to_x, to_y+1, 2, step-1))
                return 1;
        }
    }
    // backtrack
    tmp = init[from_x][from_y];
    init[from_x][from_y] = init[to_x][to_y];
    init[to_x][to_y] = tmp;

    return 0;
}
int main() {
    int n, step, start_x = 0, start_y = 0;
    scanf("%d", &n);
    while(n--) {
        scanf("%d", &step);
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                scanf(" %c", &init[i][j]);
                if(init[i][j] == 'x')
                    start_x = i, start_y = j;
            }
        }
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                scanf(" %c", &fin[i][j]);
            }
        }
        if(step == 0) {
            int flag = 1;
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++) {
                    if(init[i][j] != fin[i][j])
                        flag = 0;
                }
            }
            if(flag) printf("Yes\n");
            else printf("No\n");
        }
        else if(move(start_x, start_y, start_x+1, start_y, 1, step)
           || move(start_x, start_y, start_x-1, start_y, -1, step)
           || move(start_x, start_y, start_x, start_y+1, 2, step)
           || move(start_x, start_y, start_x, start_y-1, -2, step))
            printf("Yes\n");

        else
            printf("No\n");

    }
    return 0;
}
