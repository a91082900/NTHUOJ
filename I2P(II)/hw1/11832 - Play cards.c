#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int data;
    struct _node *next;
} Node;

void traverse(Node *head) {
    Node *ptr = head;
    while(ptr != NULL) {
        printf("%d\n", ptr->data);
        ptr = ptr->next;
    }
    //printf("\n");
}

int main() {
    int n, m, num, idx, a, b;

    char op[5];
    scanf("%d %d", &n, &m);
    Node *head = malloc(sizeof(Node)), *ptr = head, *tmp;
    int length = n;
    scanf("%d", &num);
    head->data = num;

    for(int i = 1; i < n; i++) {
        tmp = malloc(sizeof(Node));
        scanf("%d", &num);
        tmp->data = num;
        ptr->next = tmp;
        ptr = ptr->next;
    }
    ptr->next = NULL;

    for(int i = 0; i < m; i++) {
        scanf("%s", op);
        if(op[0] == 'A') { // add
            scanf("%d %d", &idx, &num);
            tmp = malloc(sizeof(Node));
            tmp->data = num;

            if(idx == 0) {
                tmp->next = head;
                head = tmp;
                length++;
            }
            else if(idx <= length) {
                ptr = head;
                for(int j = 0; ptr != NULL; j++) {
                    if(j == idx-1) {
                        tmp->next = ptr->next;
                        ptr->next = tmp;
                        break;
                    }
                    ptr = ptr->next;
                }
                length++;
            }
        }
        else {  // cut
            scanf("%d %d", &a, &b);
            if(a == 0)
                continue;
            Node *next, *old_head;
            ptr = old_head = head;
            for(int j = 0; ptr != NULL; j++) {
                next = ptr->next;
                if(j == a-1) {
                    tmp = ptr;
                }
                if(j == a) {
                    head = ptr;
                }
                if(j == a+b-1) {
                    tmp->next = ptr->next;
                    ptr->next = old_head;
                }
                ptr = next;
            }
            // head = a;
            // a+b-1->next = old head;
            // a-1->next = a+b-1->next;
        }

    }
    traverse(head);

    return 0;
}
