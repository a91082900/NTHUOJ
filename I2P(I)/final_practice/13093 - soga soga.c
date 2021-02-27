#include <stdio.h>
#include <stdlib.h>
typedef struct _node {
    int data;
    struct _node *prev, *next;
} Node;

//int blocks[500010];
//int idx = 1, middle;
int main() {
    int n, q, op, dir, tmp, middle;

    Node *head = malloc(sizeof(Node)), *ptr = head, *mid, *idx = head;
    head->prev = NULL;

    scanf("%d", &n);
    middle = (n+1)/2;
    int n0 = n;

    scanf("%d", &tmp);
    head->data = tmp;
    for(int i = 2; i <= n; i++) {
        scanf("%d", &tmp);
        ptr->next = malloc(sizeof(Node));
        ptr->next->data = tmp;
        ptr->next->prev = ptr;
        ptr = ptr->next;

        if(i == middle)
            mid = ptr;
    }
    ptr->next = NULL;

    scanf("%d", &q);
    while(q--) {
        scanf("%d", &op);
        switch(op) {
            case 1:
                scanf("%d", &dir);
                if(dir == 1) {
                    idx = idx->next;
                }
                else {
                    idx = idx->prev;
                }
                break;
            case 2:
                printf("%d\n", idx->data);
                break;
            case 3:
                if(mid == idx)
                    idx = idx->next;
                if(mid->prev != NULL) {
                    mid->prev->next = mid->next;
                    mid->next->prev = mid->prev;
                }
                else {
                    mid->next->prev = NULL;
                }


                ptr = mid; // for free purpose
                if(n % 2) { // odd
                    //printf("This is n = odd\n");
                    mid = mid->prev;
                }
                else { // even
                    mid = mid->next;
                }
                free(ptr);
                n--;
                break;
        }
        /*printf("\n");
        for(int i = 1; i <= n0; i++) {
            printf("%2d ", blocks[i]);
        }
        printf("\n");
        for(int i = 1; i <= n0; i++) {
            printf(" %c ", " ^|*"[(i==idx) + 2*(i==middle)]);
        }
        printf("\n\n");*/
    }
    return 0;
}
