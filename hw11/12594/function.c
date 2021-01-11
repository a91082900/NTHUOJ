#include "function.h"
#include <stdlib.h>

Node* createList(int *a, int size) {
    Node *head = (Node *) malloc(sizeof(Node));
    head->data = a[0];
    Node *ptr = head;
    for(int i =  1; i < size; i++) {
        Node *tmp = (Node *) malloc(sizeof(Node));
        tmp->data = a[i];
        ptr->next = tmp;
        ptr = tmp;
    }
    ptr->next = NULL;
    return head;
}
void push_front(Node** head, int val) {
    Node *insert = (Node *) malloc(sizeof(Node));
    insert->data = val;
    insert->next = *head;
    *head = insert;
}
void deleteElementByIdx(Node** head, int idx) {
    int i = 0;
    if(idx == 0) {
        Node *deleted = *head;
        *head = (*head)->next;
        free(deleted);
    }
    else if(idx > 0) {
        Node *ptr = *head;
        while(ptr != NULL) {
            i++;
            if(i == idx) {
                Node *deleted = ptr->next;
                ptr->next = ptr->next->next;
                free(deleted);
                break;
            }
            ptr = ptr->next;
        }
    }
}
Node* copyList(Node* head) {
    Node *newHead = (Node *) malloc(sizeof(Node));
    Node *newPtr = newHead, *ptr = head->next;
    newHead->data = head->data;
    while(1) {
        if(ptr == NULL)
            break;
        Node *tmp = (Node *) malloc(sizeof(Node));
        tmp->data = ptr->data;
        newPtr->next = tmp;
        newPtr = newPtr->next;
        ptr = ptr->next;
    }
    newPtr->next = NULL;
    return newHead;
}

void SwapElementByIdx(Node** head, int idx1, int idx2) {
    int i = 0;
    Node *front1, *front2, *node1, *node2;
    if(idx2 < idx1) {
        idx1 ^= idx2;
        idx2 ^= idx1;
        idx1 ^= idx2;
    }
    else if(idx1 == idx2)
        return;

    if(idx1 == 0) {
        Node *ptr = *head;
        while(ptr->next != NULL) {
            if(i == idx2-1) {
                front2 = ptr;
                node2 = ptr->next;
                Node *tmp = node2->next;


                node2->next = (*head)->next;
                front2->next = *head;
                (*head)->next = tmp;
                *head = node2;
                break;
            }
            ptr = ptr->next;
            i++;
        }
    }
    else if(idx1 > 0) {
        Node *ptr = *head;
        while(ptr->next != NULL) {
            if(i == idx1-1) {
                front1 = ptr;
                node1 = ptr->next;
            }
            if(i == idx2-1) {
                front2 = ptr;
                node2 = ptr->next;
                Node *tmp = node2->next;

                front1->next = node2;
                node2->next = node1->next;
                front2->next = node1;
                node1->next = tmp;
                break;
            }
            ptr = ptr->next;
            i++;
        }
    }
}
