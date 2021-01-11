#include "function.h"
#include <stdlib.h>

Node* Merge_lists(Node* l1, Node* l2) {
    int num;
    Node *head = (Node *) malloc(sizeof(Node)), *ptr = head;
    if(l1->data < l2->data) {
        head->data = l1->data;
        num = l1->data;
        l1 = l1->next;
    }
    else {
        head->data = l2->data;
        num = l2->data;
        l2 = l2->next;
    }

    while(l1 != NULL || l2 != NULL) {
        if((l1 != NULL && l2 != NULL && l1->data < l2->data) || l2 == NULL) {
            if(l1->data != num) {
                num = l1->data;
                Node *tmp = (Node *) malloc(sizeof(Node));
                tmp->data = l1->data;
                ptr->next = tmp;
                ptr = ptr->next;
            }
            l1 = l1->next;
        }
        else {
            if(l2->data != num) {
                num = l2->data;
                Node *tmp = (Node *) malloc(sizeof(Node));
                tmp->data = l2->data;
                ptr->next = tmp;
                ptr = ptr->next;
            }
            l2 = l2->next;
        }
    }
    ptr->next = NULL;
    return head;
}
