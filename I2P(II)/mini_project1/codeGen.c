#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codeGen.h"

#define dest (under_assign ? instructions[ins_len++]: trash)

int reg = 0;
int ins_len = 0;
char trash[20], instructions[MAXINS][20];
/*int evaluateTree(BTNode *root) {
    int retval = 0, lv = 0, rv = 0;

    if (root != NULL) {
        switch (root->data) {
            case ID:
                retval = getval(root->lexeme);
                break;
            case INT:
                retval = atoi(root->lexeme);
                break;
            case ASSIGN:
                rv = evaluateTree(root->right);
                retval = setval(root->left->lexeme, rv);
                break;
            case ADDSUB:
            case MULDIV:
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                if (strcmp(root->lexeme, "+") == 0) {
                    retval = lv + rv;
                } else if (strcmp(root->lexeme, "-") == 0) {
                    retval = lv - rv;
                } else if (strcmp(root->lexeme, "*") == 0) {
                    retval = lv * rv;
                } else if (strcmp(root->lexeme, "/") == 0) {
                    if (rv == 0)
                        error(DIVZERO);
                    retval = lv / rv;
                }
                break;
            default:
                retval = 0;
        }
    }
    return retval;
}*/
void printPrefix(BTNode *root) {
    if (root != NULL) {
        printf("%s ", root->lexeme);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}
int postfixTraversal(BTNode *root) {
    if (root != NULL) {
        root->ldepth = 1 + postfixTraversal(root->left);
        root->rdepth = 1 + postfixTraversal(root->right);
        //printf("%s ", root->lexeme);
        if(root->ldepth > root->rdepth)
            return root->ldepth;
        else
            return root->rdepth;
    }
    return -1;
}

BTNode* evaluateTree(BTNode *root, int under_assign) {
    if(root != NULL) {
        int calcFirst = 2, calcLast = 1;
        //printf("%s: %d %d\n", root->lexeme, root->ldepth, root->rdepth);
        if(!under_assign) {
            under_assign = root->data == ASSIGN;
        }
        if(root->rdepth > root->ldepth) {
            calcFirst = 1, calcLast = 2;
            if(root->rdepth != 1)
                root->right = evaluateTree(root->right, under_assign);
            if(root->ldepth != 1)
                root->left = evaluateTree(root->left, under_assign);
        }
        else {
            if(root->ldepth != 1)
            root->left = evaluateTree(root->left, under_assign);
            if(root->rdepth != 1)
                root->right = evaluateTree(root->right, under_assign);
        }
        
        char buffer[10];
        int v = 0;
        BTNode *tmp = NULL;
        switch (root->data) {
            case ASSIGN:        
                sprintf(buffer, "%d", reg % MAXREG);
                if(root->left->data != ID)
                    err(ASSIGNERR);
                if(root->right->data == INT) {
                    sprintf(dest, "MOV r%d, %s\n", reg++ % MAXREG, root->right->lexeme);
                    root->right->data = REG;
                    root->right->val = atoi(root->right->lexeme);
                    strcpy(root->right->lexeme, buffer);
                }
                else if(root->right->data == ID) {
                    sprintf(dest, "MOV r%d, [%d]\n", reg++ % MAXREG, findaddr(root->right->lexeme));
                    root->right->data = REG;
                    root->right->val = getval(root->right->lexeme);
                    strcpy(root->right->lexeme, buffer);
                }
                else if(root->right->data != REG)
                    err(ASSIGNERR);
                setval(root->left->lexeme, root->right->val);
                sprintf(dest, "MOV [%d], r%s\n", findaddr(root->left->lexeme), root->right->lexeme);
                tmp = makeNode(REG, root->right->lexeme);
                tmp->val = root->right->val;
                tmp->hasID = 1;
                tmp->ldepth = tmp->rdepth = 0;
                return tmp;
                break;
            case MULDIV:
            case ADDSUB:
            case XOR:
            case OR:
            case AND:
                if(root->left->data == ID) {
                    sprintf(dest, "MOV r%d, [%d]\n", reg++ % MAXREG, findaddr(root->left->lexeme));
                    root->left->val = getval(root->left->lexeme);
                }
                else if(root->left->data == INT) {
                    sprintf(dest, "MOV r%d, %s\n", reg++ % MAXREG, root->left->lexeme);
                    root->left->val = atoi(root->left->lexeme);
                }

                if(root->right->data == ID) {
                    sprintf(dest, "MOV r%d, [%d]\n", reg++ % MAXREG, findaddr(root->right->lexeme));
                    root->right->val = getval(root->right->lexeme);
                }
                else if(root->right->data == INT) {
                    sprintf(dest, "MOV r%d, %s\n", reg++ % MAXREG, root->right->lexeme);
                    root->right->val = atoi(root->right->lexeme);
                }

                if (root->lexeme[0] == '+') {
                    sprintf(dest, "ADD");
                    v = root->left->val + root->right->val;
                }
                else if(root->lexeme[0] == '-') {
                    sprintf(dest, "SUB");
                    v = root->left->val - root->right->val;
                }
                else if(root->lexeme[0] == '*') {
                    sprintf(dest, "MUL");
                    v = root->left->val * root->right->val;
                }
                else if(root->lexeme[0] == '/') {
                    sprintf(dest, "DIV");
                    if(root->right->val == 0) {
                        if(root->right->hasID)
                            v = 0;
                        else
                            err(DIVZERO);
                    }
                    else
                        v = root->left->val / root->right->val;
                }
                else if(root->lexeme[0] == '|') {
                    sprintf(dest, "OR");
                    v = root->left->val | root->right->val;
                }
                else if(root->lexeme[0] == '&') {
                    sprintf(dest, "AND");
                    v = root->left->val & root->right->val;
                }
                else if(root->lexeme[0] == '^') {
                    sprintf(dest, "XOR");
                    v = root->left->val ^ root->right->val;
                }

                sprintf(dest, " r%d, r%d\n", (reg-calcFirst) % MAXREG, (reg-calcLast) % MAXREG);
                if(calcFirst == 1) {
                    sprintf(dest, "MOV r%d, r%d\n", (reg-2) % MAXREG, (reg-1) % MAXREG);
                }
                sprintf(buffer, "%d", (reg-2) % MAXREG);
                reg--;
                tmp = makeNode(REG, buffer);
                tmp->val = v;
                tmp->ldepth = tmp->rdepth = 0;
                tmp->hasID = root->left->hasID | root->right->hasID;
                return tmp;
                break;
            case ID:
                root->val = getval(root->lexeme);
                break;
            case INT:
                root->val = atoi(root->lexeme);
                break;
            default:
                break;  
        }
        return root;
    }
    return NULL;
}