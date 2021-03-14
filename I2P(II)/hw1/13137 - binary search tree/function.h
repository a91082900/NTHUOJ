#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED 

typedef struct _Tree_Node{
    int number;
    struct _Tree_Node* parent;
    struct _Tree_Node* left;
    struct _Tree_Node* right;
}Tree_Node;

Tree_Node* tree_head;


void add_node(int n);
void showtree(Tree_Node* treenow);

#endif



