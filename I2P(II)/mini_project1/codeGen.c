#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codeGen.h"

#define dest (under_assign ? instructions[ins_len++]: trash)
#define max(a,b) (((a) > (b)) ? (a) : (b))

int regs[MAXREG] = {0, 0, 0, 0, 1, 1, 1, 1};
int ins_len = 0;
char trash[20], instructions[MAXINS][20];

int getAvaliableReg() {
    for(int i = 4; i < MAXREG; i++) {
        if(regs[i]) {
            regs[i] = 0;
            return i;
        }
    }
    error(RUNOUT);
}

void freeReg(char *lexeme) {
    regs[lexeme[0]-'0'] = 1;
}

// Evaluate the syntax tree
BTNode* evaluateTree(BTNode *root, int under_assign) {
    if(root != NULL) {
        if(!under_assign) {
            under_assign = root->data == ASSIGN || root->data == INC_ID || root->data == DEC_ID;
        }

        if(root->rdepth > root->ldepth)
            root->right = evaluateTree(root->right, under_assign);
        if(root->data != ASSIGN)
            root->left = evaluateTree(root->left, under_assign);
        if(root->ldepth >= root->rdepth)
            root->right = evaluateTree(root->right, under_assign);

        int addr = 0;
        BTNode *tmp;
        char buffer[20];
        int r;
        switch (root->data) {
            case ASSIGN:
                if(root->right->data == INT) {
                    r = getAvaliableReg();
                    sprintf(dest, "MOV r%d, %d\n", r, root->right->val);
                    sprintf(root->right->lexeme, "%d", r);
                    root->right->data = REG;
                }
                if(root->left->data != ID || root->right->data != REG) {
                    error(ASSIGNERR);
                }
                setval(root->left->lexeme, root->right->val);
                addr = findaddr(root->left->lexeme);
                if(addr <= 8) {
                    sprintf(dest, "MOV r%d, r%s\n", addr/4, root->right->lexeme);
                }
                else {
                    sprintf(dest, "MOV [%d], r%s\n", addr, root->right->lexeme);
                }
                tmp = makeNode(REG, root->right->lexeme);
                tmp->val = root->right->val;
                return tmp;
                break;
            case ADDSUB:
            case MULDIV:
            case AND:
            case OR:
            case XOR:
                if(root->left->data == INT && root->right->data == INT) {
                    if(root->lexeme[0] == '+') {
                        root->val = root->left->val + root->right->val;
                    }
                    else if(root->lexeme[0] == '-') {
                        root->val = root->left->val - root->right->val;
                    }
                    else if(root->lexeme[0] == '*') {
                        root->val = root->left->val * root->right->val;
                    }
                    else if(root->lexeme[0] == '/') {
                        if(root->right->val == 0)
                            error(DIVZERO);
                        root->val = root->left->val / root->right->val;
                    }
                    else if(root->lexeme[0] == '^') {
                        root->val = root->left->val ^ root->right->val;
                    }
                    else if(root->lexeme[0] == '&') {
                        root->val = root->left->val & root->right->val;
                    }
                    else if(root->lexeme[0] == '|') {
                        root->val = root->left->val | root->right->val;
                    }
                    sprintf(buffer, "%d", root->val);
                    tmp = makeNode(INT, buffer);
                    return tmp;
                }
                else if(root->left->data == INT && root->right->data == REG) {
                    r = getAvaliableReg();
                    sprintf(dest, "MOV r%d, %d\n", r, root->left->val);
                    sprintf(root->left->lexeme, "%d", r);
                    root->left->data = REG;
                }
                else if(root->right->data == INT && root->left->data == REG) {
                    if(root->lexeme[0] == '/' && root->right->val == 0)
                        error(DIVZERO);
                    r = getAvaliableReg();
                    sprintf(dest, "MOV r%d, %d\n", r, root->right->val);
                    sprintf(root->right->lexeme, "%d", r);
                    root->right->data = REG;
                }
                else if(root->left->data != REG || root->right->data != REG) {
                    error(SYNTAXERR);
                }

                if(root->lexeme[0] == '+') {
                    root->val = root->left->val + root->right->val;
                    sprintf(dest, "ADD");
                }
                else if(root->lexeme[0] == '-') {
                    root->val = root->left->val - root->right->val;
                    sprintf(dest, "SUB");
                }
                else if(root->lexeme[0] == '*') {
                    root->val = root->left->val * root->right->val;
                    sprintf(dest, "MUL");
                }
                else if(root->lexeme[0] == '/') {
                    if(root->right->val != 0)
                        root->val = root->left->val / root->right->val;
                    else
                        root->val = 0;
                    sprintf(dest, "DIV");
                }
                else if(root->lexeme[0] == '^') {
                    root->val = root->left->val ^ root->right->val;
                    sprintf(dest, "XOR");
                }
                else if(root->lexeme[0] == '&') {
                    root->val = root->left->val & root->right->val;
                    sprintf(dest, "AND");
                }
                else if(root->lexeme[0] == '|') {
                    root->val = root->left->val | root->right->val;
                    sprintf(dest, "OR");
                }
                tmp = makeNode(REG, root->left->lexeme);
                tmp->val = root->val;                
                sprintf(dest, " r%s, r%s\n", root->left->lexeme, root->right->lexeme);

                freeReg(root->right->lexeme);
                return tmp;
                break;
            case INT: // the value of INT is set when node is made
                break;
            case ID:
                root->val = getval(root->lexeme);
                addr = findaddr(root->lexeme);
                r = getAvaliableReg();
                if(addr <= 8) {
                    sprintf(dest, "MOV r%d, r%d\n", r, addr/4);
                    sprintf(root->lexeme, "%d", r);
                }
                else {
                    sprintf(dest, "MOV r%d, [%d]\n", r, addr);
                    sprintf(root->lexeme, "%d", r);
                }
                root->data = REG;
                break;
            case INC_ID:
            case DEC_ID:
                root->val = getval(root->lexeme);
                addr = findaddr(root->lexeme);
                if(addr <= 8) {
                    sprintf(root->lexeme, "%d", addr/4);
                    sprintf(dest, "%s r%d, r3\n", (root->data == INC_ID ? "ADD": "SUB"), addr/4);
                }
                else {
                    r = getAvaliableReg();
                    sprintf(dest, "MOV r%d, [%d]\n", r, addr);
                    sprintf(root->lexeme, "%d", r);
                    
                    sprintf(dest, "%s r%s, r3\n", (root->data == INC_ID ? "ADD": "SUB"), root->lexeme);
                    sprintf(dest, "MOV [%d], r%s\n", addr, root->lexeme);
                }
                root->data = REG;
                root->val = root->val + (root->data == INC_ID ? 1: -1);
                break;
            default:
                break;
        }
        return root;
    }
    return NULL;
}

void printPrefix(BTNode *root) {

}
int postfixTraversal(BTNode *root) {
    if(root != NULL) {
        root->ldepth = 1 + postfixTraversal(root->left);
        root->rdepth = 1 + postfixTraversal(root->right);
        return max(root->ldepth, root->rdepth);
    }
    return -1;
}
