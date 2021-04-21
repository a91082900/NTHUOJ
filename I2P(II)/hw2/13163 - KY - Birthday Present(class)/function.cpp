#include "function.h"
#include <iostream>
using namespace std;

int tagCount = 0;
KuoYangPresent::KuoYangPresent(int k) {
    this->k = k;
    this->sz = 0;
    this->head = this->tail = this->mid = NULL;
}
void KuoYangPresent::Push(int x) {
    if(sz == 0) {
        head = mid = tail = new Node();
        tail->val = x;
        tail->tag = tagCount;
        tail->prev = tail->next = NULL;
    }
    else {
        tail->next = new Node();
        tail->next->prev = tail;
        tail->next->val = x;
        tail->next->tag = tagCount;
        tail = tail->next;
        if(!(sz % 2)) {
            mid = mid->next;
        }
    }
    this->sz++;

}
void KuoYangPresent::Pop() {
    if(sz <= 0)
        return;
    if(sz == 1) {
        delete mid;
        head = tail = mid = NULL;
    }
    else if(sz == 2) {
        delete head;
        head = mid = tail;
    }
    else {
        mid->prev->next = mid->next;
        mid->next->prev = mid->prev;

        Node *tmp = mid;
        if(sz % 2) {
            mid = mid->prev;
        }
        else {
            mid = mid->next;
        }
        delete tmp;
    }
    sz--;
}
void KuoYangPresent::ProgrammingTanoshi() {
    tagCount++;
}
void KuoYangPresent::KuoYangTeTe() {
    Node *ptr = head;
    while(ptr != NULL) {
        if(ptr->tag < tagCount) {
            ptr->val = ptr->val % k;
        }
        ptr = ptr->next;
    }
}

void KuoYangPresent::PrintList() {
    Node *ptr = head;
    while(ptr != NULL) {
        cout << ptr->val << ' ';
        ptr = ptr->next;
    }
    cout << '\n';
}
