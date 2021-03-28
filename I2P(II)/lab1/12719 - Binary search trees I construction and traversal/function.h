#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000006

typedef struct Node
{
    int key;
    struct Node *ltree;
    struct Node *rtree;
} Node ;

// build a binary search tree with given pre-order traversal
// return pointer to root
Node *buildBST(int n, int *preOrder);

// print the in-order traversal of a given tree
// it is suggested to implement using recursion
void printInOrder(Node *ptr);

// print the post-order traversal of a given tree
// it is suggested to implement using recursion
void printPostOrder(Node *ptr);

// delete the binary search tree in case of memory leak
// it is suggested to implement using recursion
void freeTree(Node *ptr);

#endif // FUNCTION_H_
