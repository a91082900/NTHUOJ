#ifndef __CODEGEN__
#define __CODEGEN__
#define MAXINS 10000
#define MAXREG 8

#include "parser.h"

// Evaluate the syntax tree
extern BTNode* evaluateTree(BTNode *root, int under_assign);

// Print the syntax tree in prefix
extern void printPrefix(BTNode *root);
extern int postfixTraversal(BTNode *root);
extern void freeReg(char *lexeme);

extern char instructions[MAXINS][20];
extern int ins_len;
#endif // __CODEGEN__
