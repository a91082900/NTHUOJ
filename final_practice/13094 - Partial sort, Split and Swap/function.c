#include "function.h"
#include <stdlib.h>

Node* Partial_sort(Node* head, int num) {
    Node *l_ptr = NULL, *r_ptr = NULL, *l_head = NULL, *r_head = NULL, *tmp;
    Node *ptr = head;
    while(ptr != NULL) {
        tmp = malloc(sizeof(Node));
        tmp->data = ptr->data;
        if(ptr->data < num) {
            if(l_ptr == NULL) {
                l_ptr = tmp;
                l_head = l_ptr;
            }
            else {
                l_ptr->next = tmp;
                l_ptr = l_ptr->next;
            }
        }
        else {
            if(r_ptr == NULL) {
                r_ptr = tmp;
                r_head = r_ptr;
            }
            else {
                r_ptr->next = tmp;
                r_ptr = r_ptr->next;
            }
        }
        //tmp = ptr;
        ptr = ptr->next;
        //free(tmp);
    }
    if(l_ptr == NULL)
        return r_head;
    else if(r_ptr == NULL)
        return l_head;
    l_ptr->next = r_head;
    r_ptr->next = NULL;
    return l_head;
}

Node* Split_and_Swap(Node* head, int left, int right) {
    // right -> ... -> n-1 -> (left+1 -> ... -> right-1) -> 0 -> 1 -> ... -> left

    int i = 0;
    Node *ptr = head, *o_head = head, *rm1, *l, *r = NULL, *la1, *tmp;
    while(ptr->next != NULL) {
        if(i == left) {
            l = ptr;
            //printf("left: %d\n", ptr->data);
        }
        else if(i == left+1) {
            la1 = ptr;
            //printf("l+1: %d\n", ptr->data);
        }
        if(i == right-1) {
            rm1 = ptr;
            //printf("r-1: %d\n", ptr->data);
        }
        else if(i == right) {
            r = ptr;
            //printf("right: %d\n", ptr->data);
        }
        ptr = ptr->next;
        i++;
    }
    if(r == NULL)
        r = ptr;
    Node *h = malloc(sizeof(Node)), *nptr = h;
    h->data = r->data;
    r = r->next;
    while(r != NULL) {
        tmp = malloc(sizeof(Node));
        tmp->data = r->data;
        nptr->next = tmp;
        nptr = nptr->next;
        r = r->next;
    }
    if(right - left > 1) {
        while(la1 != rm1->next) {
            tmp = malloc(sizeof(Node));
            tmp->data = la1->data;
            nptr->next = tmp;
            nptr = nptr->next;
            la1 = la1->next;
        }
    }
    while(o_head != l->next) {
        tmp = malloc(sizeof(Node));
        tmp->data = o_head->data;
        nptr->next = tmp;
        nptr = nptr->next;
        o_head = o_head->next;
    }
    nptr->next = NULL;
    return h;


    /*if(right - left == 1) {
        ptr->next = o_head;
    }
    else {
        ptr->next = la1;
        rm1->next = o_head;
    }
        l->next = NULL;
    return r;*/
}
