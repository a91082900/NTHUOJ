#include <stdio.h>
int edges[5005], connect[5005][2];
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n-1; i++) {
        scanf("%d %d", &connect[i][0], &connect[i][1]);
        edges[connect[i][0]]++;
        edges[connect[i][1]]++;
    }

    int min, minidx;
    for(int j = 0; j < n-2; j++) {
        min = (int) 1e9, minidx = 0;
        for(int i = 0; i < n-1; i++) {
            //printf("finding: %d %d\n", connect[i][0], connect[i][1]);
            if(edges[connect[i][0]] == 1) {
                if(connect[i][0] < min) {
                    min = connect[i][0];
                    minidx = i;
                }
            }
            else if(edges[connect[i][1]] == 1) {
                if(connect[i][1] < min) {
                    min = connect[i][1];
                    minidx = i;
                }
            }
        }
        //printf("min = %d, idx = %d\n", min, minidx);
        edges[connect[minidx][0]]--;
        edges[connect[minidx][1]]--;

        if(!edges[connect[minidx][0]]) {
            printf("%d ", connect[minidx][1]);
        }
        else {
            printf("%d ", connect[minidx][0]);
        }
        connect[minidx][0] = connect[minidx][1] = -1;
    }
    printf("\n");
    return 0;
}
