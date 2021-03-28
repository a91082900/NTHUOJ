#include "function.h"
#include <stdio.h>

void printInfix(Node *root) {
    if(root != NULL) {
        printInfix(root->left);
        printf("%c", root->data);
        if(root->right != NULL) {
            if(root->right->data == '|' || root->right->data == '&') {
                printf("(");
                printInfix(root->right);
                printf(")");
            }
            else
                printInfix(root->right);
        }
    }
}
