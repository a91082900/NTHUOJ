#include "function.h"
#include <stdlib.h>
#include <stdio.h>
// A&B|C&D&A&B|C&D
BTNode* EXPR() {

    BTNode *root, *rchild;

    if((expr[pos] >= 'A' && expr[pos] <= 'D') || expr[pos] == ')') { // (EXPR)
        rchild =  FACTOR();
    }
    if(pos>=0 && (expr[pos] == '&' || expr[pos] == '|')) {
        //printf("pos = %d, expr[pos] = %c\n", pos, expr[pos]);
        root = makeNode(expr[pos--]);
        root->right = rchild;
        root->left = EXPR();
        return root;
    }
    else  {
        //printf("pos = %d, rchild.data = %d\n", pos, rchild->data);
        return rchild;
    }
}
BTNode* FACTOR() {
    BTNode *factor;
    if(expr[pos] == ')') {
        pos--;
        factor = EXPR();
        pos--;
    }
    else
        factor = makeNode(expr[pos--]);
    return factor;
}
BTNode* makeNode(char c) {
    BTNode *node = (BTNode *) malloc(sizeof(BTNode));
    //printf("\tmake node of '%c'\n", c);
    switch(c) {
        case 'A':
            node->data = ID_A;
            break;
        case 'B':
            node->data = ID_B;
            break;
        case 'C':
            node->data = ID_C;
            break;
        case 'D':
            node->data = ID_D;
            break;
        case '&':
            node->data = OP_AND;
            break;
        case '|':
            node->data = OP_OR;
            break;
    }
    node->left = node->right = NULL;
    return node;
}
