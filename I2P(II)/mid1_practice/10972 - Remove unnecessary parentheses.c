#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treeNode {
    char data;
    struct treeNode *left;
    struct treeNode *right;
} Node;

char expr[300];
int pos;

Node* EXPR();
Node* FACTOR();
Node* makeNode(char c);
void printInfix(Node *root);

int main() {
    scanf("%s", expr);
    pos = strlen(expr)-1;
    Node *root = EXPR();
    printInfix(root);
    //printf("\n");
    return 0;
}

Node* EXPR() {

    Node *root, *rchild;

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
Node* FACTOR() {
    Node *factor;
    if(expr[pos] == ')') {
        pos--;
        factor = EXPR();
        pos--;
    }
    else
        factor = makeNode(expr[pos--]);
    return factor;
}
Node* makeNode(char c) {
    Node *node = (Node *) malloc(sizeof(Node));
    //printf("\tmake node of '%c'\n", c);
    node->data = c;
    node->left = node->right = NULL;
    return node;
}

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
