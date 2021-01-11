#include <stdio.h>
#include <stdlib.h>
#define max(a, b) (((a) > (b)) ? (a) : (b))
int arr[100001];

int cmp(const void *a, const void *b) {
    return (*(int *) a - *(int *) b);
}


int main() {
    int n, q, op, val, j;
    int x_idx = 0, y_idx = 0;

    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    qsort(arr, n, sizeof(int), cmp);

    scanf("%d", &q);
    while(q--) {
        scanf("%d %d", &op, &val);
        switch(op) {
            case 1:
                for(int i = x_idx; i < n; i++) {
                    if(arr[i] == val) {
                        arr[i] = -1;
                        x_idx = i;
                        //break; // ai may duplicate
                    }
                    if(arr[i] > val) {
                        x_idx = max(i-1, 0);
                        break;
                    }
                }
                /*for(int i = 0; i < n; i++) {
                    printf("%2d ", arr[i]);

                }
                printf("\n");
                for(int i = 0; i < n; i++) {
                    printf("%c  ", " ^"[i==x_idx]);

                }
                printf("\n");*/
                break;
            case 2:
                for(j = y_idx; j < n; j++) {
                    if(arr[j] == val) {
                        printf("Yes\n");
                        y_idx = j;
                        break;
                    }
                    if(arr[j] > val) {
                        printf("No\n");
                        y_idx = max(j-1, 0);
                        break;
                    }
                }
                if(j == n)
                    printf("No\n");
                /*for(int i = 0; i < n; i++) {
                    printf("%2d ", arr[i]);

                }
                printf("\n");
                for(int i = 0; i < n; i++) {
                    printf("%c  ", " ^"[i==y_idx]);

                }
                printf("\n");*/
                break;
        }
    }
    return 0;
}
