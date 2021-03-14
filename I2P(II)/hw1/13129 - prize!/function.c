#include "function.h"
#include <stdio.h>
#include <stdlib.h>

Node *ptr;
Node* createList(int n) {
    Node *head = malloc(sizeof(Node)), *tmp;
    ptr = head;

    head->number = 1;
    for(int i = 2; i <= n; i++) {
        tmp = malloc(sizeof(Node));
        tmp->number = i;
        tmp->prev = ptr;

        ptr->next = tmp;
        ptr = ptr->next;
    }
    head->prev = ptr;
    ptr->next = head;

    tmp = malloc(sizeof(Node));
    tmp->prev = head;
    tmp->next = head;

    ptr = tmp; // create a tmp node whose next and prev are all head
    return head;
}
void solveJosephus(int n, int m) {
    int length = n;
    int k, clockwise, j;
    for(int i = 0; i < m; i++) {
        scanf("%d", &k);
        clockwise = k % 2;
        k %= length;
        if(k == 0)
            k = length;
        j = 1;
        if(clockwise) {
            ptr = ptr->next;
            while(1) {
                if(j == k) {
                    printf("%d\n", ptr->number);
                    ptr->prev->next = ptr->next;
                    ptr->next->prev = ptr->prev;
                    break;
                }
                ptr = ptr->next;
                j++;
            }
        }
        else {
            ptr = ptr->prev;
            while(1) {
                if(j == k) {
                    printf("%d\n", ptr->number);
                    ptr->prev->next = ptr->next;
                    ptr->next->prev = ptr->prev;
                    break;
                }
                ptr = ptr->prev;
                j++;
            }
        }
        length--;
    }
}
