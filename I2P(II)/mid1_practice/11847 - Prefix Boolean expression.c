#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char data;
    struct node *left, *right;
} Node;

Node* construct() {
    Node* root = malloc(sizeof(Node));
    char c = getchar();
    root->data = c;
    root->left = root->right = NULL;
    if(root->left == NULL && (root->data == '|' || root->data == '&'))
        root->left = construct();
    if(root->right == NULL && (root->data == '|' || root->data == '&'))
        root->right = construct();
    return root;
}

int bits = 0;

int evaluate(Node *root) {
    if(root->data == '|') {
        return evaluate(root->left) | evaluate(root->right);
    }

    else if(root->data == '&') {
        return evaluate(root->left) & evaluate(root->right);
    }
    else if(root->data == 'A') {
        return (bits & (1<<3)) > 0;
    }
    else if(root->data == 'B') {
        return (bits & (1<<2)) > 0;
    }
    else if(root->data == 'C') {
        return (bits & (1<<1)) > 0;
    }
    else if(root->data == 'D') {
        return (bits & (1)) > 0;
    }
}


int main() {
    Node *root = construct();
    for(;bits < 16; bits++) {
        printf("%d %d %d %d ", (bits&(1<<3)) > 0, (bits&(1<<2)) > 0, (bits&(1<<1)) > 0, (bits&(1)) > 0);
        printf("%d\n", evaluate(root));
    }
    //printInfix(root);
    return 0;
}
