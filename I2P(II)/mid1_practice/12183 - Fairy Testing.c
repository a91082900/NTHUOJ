#include <stdio.h>
#include <stdlib.h>
#define AND -1
#define OR -2
typedef struct node {
    int val;
    int symbol;
    struct node *left, *right, *parent;
} Node;
Node *var[100005];
char chr;
int id;
Node* buildPrefixTree(Node* parent) {
    Node *root = malloc(sizeof(Node));
    root->parent = parent;
    root->left = root->right = NULL;
    root->val = 0; // all results are 0 initially

    scanf("%c", &chr);
    if(chr == '[') {
        scanf("%d]", &id);
        root->symbol = id;
        var[id] = root;
    }
    else if(chr == '&') {
        root->symbol = AND;
    }
    else {
        root->symbol = OR;
    }

    if(root->left == NULL && root->symbol < 0) {
        root->left = buildPrefixTree(root);
    }
    if(root->right == NULL && root->symbol < 0) {
        root->right = buildPrefixTree(root);
    }

    // evaluating
    /*if(root->symbol == AND)
        root->val = root->left->val & root->right->val;
    else if(root->symbol == OR)
        root->val = root->left->val | root->right->val;*/
    return root;
}

int evaluate(Node *node) {
    if(node->symbol == OR)
        return node->left->val | node->right->val;
    else if(node->symbol == AND)
        return node->left->val & node->right->val;
    else
        return node->val;
}
int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        int n, m, flip, eval;
        scanf("%d %d ", &n, &m);
        Node *root = buildPrefixTree(NULL), *ptr;
        //Trav(root);
        while(m--) {
            scanf("%d", &flip);
            var[flip]->val = !(var[flip]->val);
            ptr = var[flip];
            while(ptr->parent != NULL) {
                eval = evaluate(ptr->parent);
                if(eval != ptr->parent->val) {
                    ptr->parent->val = eval;
                    ptr = ptr->parent;
                }
                else
                    break;
            }
            printf("%d\n", root->val);
        }
    }
    return 0;
}
