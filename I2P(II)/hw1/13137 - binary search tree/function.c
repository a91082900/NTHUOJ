#include "function.h"
#include <stdlib.h>
#include <stdio.h>

void add_node(int n) {
    if(tree_head == NULL) {
        tree_head = malloc(sizeof(Tree_Node));
        tree_head->parent = NULL;
        tree_head->left = NULL;
        tree_head->right = NULL;
        tree_head->number = n;
        return;
    }
    Tree_Node *ptr = tree_head;
    while(1) {
        if(n > ptr->number) {
            if(ptr->right == NULL) {
                ptr->right = malloc(sizeof(Tree_Node));
                ptr->right->number = n;
                ptr->right->parent = ptr;
                ptr->right->left = ptr->right->right = NULL;
                break;
            }
            else
                ptr = ptr->right;
        }
        else {
            if(ptr->left == NULL) {
                ptr->left = malloc(sizeof(Tree_Node));
                ptr->left->number = n;
                ptr->left->parent = ptr;
                ptr->left->left = ptr->left->right = NULL;
                break;
            }
            else
                ptr = ptr->left;
        }
    }
}

void showtree(Tree_Node* treenow) {
    if(treenow != NULL){
        showtree(treenow->left);
        printf("%d ", treenow->number);
        showtree(treenow->right);
    }
}
