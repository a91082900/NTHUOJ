#include <stdio.h>

int n, edges[5005][2], deg[5005];
int ans[5005];
int main() {

    int min, minparent, edgeidx;
    scanf("%d", &n);
    for(int i = 1; i < n; i++) {
        scanf("%d %d", &edges[i][0], &edges[i][1]);
        deg[edges[i][0]]++;
        deg[edges[i][1]]++;
    }

    for(int k = 0; k < n-2; k++) {
        min = n+1;
        for(int i = 0; i < n; i++) {
            if(edges[i][0] < 0)
                continue;
            if(deg[edges[i][0]] == 1) {
                if(edges[i][0] < min) {
                    min = edges[i][0];
                    minparent = edges[i][1];
                    edgeidx = i;
                }
            }
            else if(deg[edges[i][1]] == 1) {
                if(edges[i][1] < min) {
                    min = edges[i][1];
                    minparent = edges[i][0];
                    edgeidx = i;
                }
            }
        }
        deg[min]--;
        deg[minparent]--;
        edges[edgeidx][0] = edges[edgeidx][1] = -1;
        ans[k] = minparent;
    }

    for(int k = 0; k < n-2; k++) {
        printf("%d ", ans[k]);
    }
    printf("\n");
    return 0;
}
