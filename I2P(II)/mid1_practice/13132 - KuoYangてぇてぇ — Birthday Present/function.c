#include <stdlib.h>
#include "function.h"

Node *mid, *tail;
int length = 0, tagCount = 0;
void push(int x) {
    if(head == NULL) {
        head = malloc(sizeof(Node));
        head->val = x;
        head->prev = head->next = NULL;
        head->tag = tagCount;
        tail = mid = head;
    }
    else {
        tail->next = malloc(sizeof(Node));
        tail->next->val = x;
        tail->next->prev = tail;
        tail->next->next = NULL;
        tail->next->tag = tagCount;

        tail = tail->next;
        if(!(length % 2)) { // length is even before pushing
            mid = mid->next;
        }
    }
    length++;
    // TODO: maintain mid
}
void pop() {
    if(length <= 0)
        return;
    if(length == 1) {
        free(head);
        head = tail = mid = NULL;
        length = 0;
    }
    else if(length == 2) {
        head = mid = tail;
        free(tail->prev);
        tail->prev = NULL;
        length = 1;
    }
    else {
        mid->prev->next = mid->next;
        mid->next->prev = mid->prev;
        if(length % 2) { // length is odd before popping
            mid = mid->prev;
        }
        else {
            mid = mid->next;
        }
        length--;
    }

}
void programming_tanoshi() {
    tagCount++;
}
void KuoYangTeTe() {
    Node *ptr = head;
    while(ptr != NULL) {
        if(ptr->tag < tagCount) { // need to do module
            ptr->val %= k;
        }
        ptr = ptr->next;
    }
}
