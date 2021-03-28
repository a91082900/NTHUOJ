#include "function.h"

// build a binary search tree with given pre-order traversal
// return pointer to root

int i = 0;
Node *buildBST(int n, int *preOrder) {
    Node *root = malloc(sizeof(Node));//, *ptr = root;
    root->key = preOrder[0];
    root->ltree = root->rtree = NULL;

    while(i < n) {
        i++;
        printf("i = %d\n", i);
        if(preOrder[i] < root->key) {
            printf("build left tree\n");
            root->ltree = buildBST(n-1, preOrder+1);
        }
        else {
            printf("build right tree\n");
            root->rtree = buildBST(n-i, preOrder+i);
        }
    }

    return root;
}

// print the in-order traversal of a given tree
// it is suggested to implement using recursion
void printInOrder(Node *ptr) {
    if(ptr != NULL) {
        printInOrder(ptr->ltree);
        printf("%d ", ptr->key);
        printInOrder(ptr->rtree);
    }
}

// print the post-order traversal of a given tree
// it is suggested to implement using recursion
void printPostOrder(Node *ptr) {
    if(ptr != NULL) {
        printPostOrder(ptr->ltree);
        printPostOrder(ptr->rtree);
        printf("%d ", ptr->key);
    }
}

// delete the binary search tree in case of memory leak
// it is suggested to implement using recursion
void freeTree(Node *ptr) {
    if(ptr != NULL) {
        freeTree(ptr->ltree);
        freeTree(ptr->rtree);
        free(ptr);
    }
}
