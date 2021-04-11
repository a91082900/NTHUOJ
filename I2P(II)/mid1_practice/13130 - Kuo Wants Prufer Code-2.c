#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *next;
} Node;

Node *head[5005], *tail[5005];
int edge[5005], n;

void removeVertice(Node **head, int i) {
    Node *ptr = *head;
    if((*head)->val == i) {
        *head = (*head)->next;
        free(ptr);
        return;
    }
    while(ptr->next != NULL) {
        if(ptr->next->val == i) {
            Node *tmp = ptr->next;
            ptr->next = ptr->next->next;
            free(tmp);
            return;
        }
        ptr = ptr->next;
    }
}

int main() {
    int u, v;
    scanf("%d", &n);
    for(int i = 0; i < n-1; i++) {
        scanf("%d %d", &u, &v);
        if(tail[u] == NULL) {
            tail[u] = head[u] = malloc(sizeof(Node));
            tail[u]->val = v;
            tail[u]->next = NULL;
        }
        else {
            tail[u] = tail[u]->next = malloc(sizeof(Node));
            tail[u]->val = v;
            tail[u]->next = NULL;
        }

        if(tail[v] == NULL) {
            tail[v] = head[v] = malloc(sizeof(Node));
            tail[v]->val = u;
            tail[v]->next = NULL;
        }
        else {
            tail[v] = tail[v]->next = malloc(sizeof(Node));
            tail[v]->val = u;
            tail[v]->next = NULL;
        }
        edge[u]++;
        edge[v]++;
    }
    for(int i = 0; i < n-2; i++) {
        for(int i = 1; i <= n; i++) {
            if(edge[i] == 1) {
                edge[i]--;
                edge[head[i]->val]--;
                printf("%d ", head[i]->val);
                removeVertice(&head[head[i]->val], i);
                break;
            }
        }
    }
    printf("\n");
    return 0;
}
