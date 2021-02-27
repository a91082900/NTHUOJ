#include <stdlib.h>
#include <stdio.h>
#include "function.h"
int length = 0;
void deleteNode(Node ** nd, int data) {
    Node *head = *nd, *tmp, *ptr = head;
    if(data == 1) {
        if(head != NULL) {
            *nd = head->next;
            free(head);
        }
    }
    else if(data <= length) {
        int i = 2;
        while(ptr->next != NULL) {
            if(i == data) {
                tmp = ptr->next;
                ptr->next = ptr->next->next;
                free(tmp);
                length--;
                break;
            }

            ptr = ptr->next;
            i++;
        }
    }
}

Node* createList() {
    Node *head = (Node *) malloc(sizeof(Node)), *tmp, *ptr = head;
    int data, i = 1;
    scanf("%d", &data);

    if(data == -1)
        return NULL;

    head->data = data;

    while(1) {
        scanf("%d", &data);
        if(data > -1) {
            tmp = (Node *) malloc(sizeof(Node));
            tmp->data = data;
            ptr->next = tmp;
            ptr = ptr->next;
            i++;
        }
        else {
            ptr->next = NULL;
            break;
        }

    }
    length = i;
    return head;
}
