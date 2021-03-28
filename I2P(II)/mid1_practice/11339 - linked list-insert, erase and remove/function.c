#include <stdio.h>
#include <stdlib.h>
#include "function.h"
int length = 0;
void do_I(Node **head,size_t pos,unsigned short val) {
    if(*head == NULL) {
        *head = malloc(sizeof(Node));
        (*head)->prev = (*head)->next = NULL;
        (*head)->val = val;
    }
    else if(pos == 0) {
        Node *new_head = malloc(sizeof(Node));
        new_head->val = val;
        new_head->next = (*head);
        new_head->prev = NULL;
        (*head)->prev = new_head;
        *head = new_head;
    }
    else if(pos >= length) {
        Node *ptr = *head;
        for(; ptr->next != NULL;) {
            ptr = ptr->next;
        }
        ptr->next = malloc(sizeof(Node));
        ptr->next->prev = ptr;
        ptr->next->next = NULL;
        ptr->next->val = val;
    }
    else {
        Node *ptr = *head;
        for(int i = 0; i < pos; i++) {
            ptr = ptr->next;
        }
        Node *insert = malloc(sizeof(Node));
        insert->next = ptr;
        insert->prev = ptr->prev;
        insert->val = val;
        ptr->prev->next = insert;
        ptr->prev = insert;

    }
    length++;
}
void do_E_start_0(Node **head, size_t end_pos) {
    Node *ptr = *head;
    if(end_pos >= length) { // delete whole list
        *head = NULL;
        length = 0;
    }
    else {
        for(int i = 0; i < end_pos; i++) {
            ptr = ptr->next;
        }
        *head = ptr;
        length -= end_pos;

    }
}
void do_E(Node **head,size_t begin_pos,size_t end_pos) {
    if(begin_pos >= length || begin_pos >= end_pos)
        return;
    if(begin_pos == 0) {
        do_E_start_0(head, end_pos);
        return;
    }
    Node *ptr = *head, *start, *end;
    if(end_pos >= length) { // delete until last
        end_pos = length;
        for(int i = 0; i < begin_pos; i++) {
            ptr = ptr->next;
        }
        ptr->prev->next = NULL;
    }
    else {
        for(int i = 0; i < end_pos; i++) {
            if(i == begin_pos) {
                start = ptr;
            }
            ptr = ptr->next;
        }
        end = ptr;
        // do not delete end
        start->prev->next = end;
        end->prev = start->prev;
    }
    length -= (end_pos - begin_pos);
}
void do_P(Node  *head,size_t pos) {
    if(length == 0)
        return;
    if(pos >= length)
        pos = length-1;
    Node *ptr = head;
    for(int i = 0; i < pos; i++) {
        ptr = ptr->next;
    }
    printf("%u ", ptr->val);

}
void do_R(Node **head,unsigned short val) {
    if(*head == NULL)
        return;
    while((*head)->val == val) {
        *head = (*head)->next;
        length--;
        if(*head == NULL)
            return;
        (*head)->prev = NULL;
    }
    Node *ptr = *head;
    while(ptr != NULL) {
        if(ptr->val == val) {
            ptr->prev->next = ptr->next;
            if(ptr->next != NULL)
                ptr->next->prev = ptr->prev;
            length--;
        }
        ptr = ptr->next;
    }
}
void do_S(Node  *head) {
    Node *ptr = head;
    //printf("L = %d\n", length);
    while(ptr != NULL) {
        printf("%u ", ptr->val);
        ptr = ptr->next;
    }
}
