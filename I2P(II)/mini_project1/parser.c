#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "codeGen.h"

int sbcount = 0, set_incdec = 0;
Symbol table[TBLSIZE];

void initTable(void) {
    strcpy(table[0].name, "x");
    table[0].val = 0;
    strcpy(table[1].name, "y");
    table[1].val = 0;
    strcpy(table[2].name, "z");
    table[2].val = 0;
    sbcount = 3;
}

int getval(char *str) {
    int i = 0;

    for (i = 0; i < sbcount; i++)
        if (strcmp(str, table[i].name) == 0)
            return table[i].val;

    if (sbcount >= TBLSIZE)
        error(RUNOUT);
    
    /*strcpy(table[sbcount].name, str);
    table[sbcount].val = 0;
    sbcount++;
    return 0;*/
    error(NOTDEF);
}

int findaddr(char *str) {
    int i = 0;

    for (i = 0; i < sbcount; i++)
        if (strcmp(str, table[i].name) == 0)
            return 4*i;

    if (sbcount >= TBLSIZE)
        error(RUNOUT);
    
    /*strcpy(table[sbcount].name, str);
    table[sbcount].val = 0;
    sbcount++;
    return 0;*/
    error(NOTDEF);
}

int setval(char *str, int val) {
    int i = 0;

    for (i = 0; i < sbcount; i++) {
        if (strcmp(str, table[i].name) == 0) {
            table[i].val = val;
            return val;
        }
    }

    if (sbcount >= TBLSIZE)
        error(RUNOUT);
    
    strcpy(table[sbcount].name, str);
    table[sbcount].val = val;
    sbcount++;
    return val;
}

BTNode *makeNode(TokenSet tok, const char *lexe) {
    BTNode *node = (BTNode*)malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->data = tok;
    if(tok == INT)
        node->val = atoi(node->lexeme);
    else
        node->val = 0;
    node->ldepth = node->rdepth = 0;
    node->hasID = tok == ID;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void freeTree(BTNode *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// factor := INT | ADDSUB INT |
//		   	 ID  | ADDSUB ID  | 
//		   	 ID ASSIGN expr |
//		   	 LPAREN expr RPAREN |
//		   	 ADDSUB LPAREN expr RPAREN
// factor := INT | ID | INCDEC ID | LPAREN assign_expr RPAREN
BTNode *factor(void) {
    BTNode *retp = NULL, *left = NULL;

    if (match(INT)) {
        retp = makeNode(INT, getLexeme());
        advance();
    } else if (match(ID)) {
        left = makeNode(ID, getLexeme());
        advance();
        if (!match(ASSIGN)) {
            retp = left;
        } /*else {
            retp = makeNode(ASSIGN, getLexeme());
            advance();
            retp->left = left;
            retp->right = expr();
        }*/
    } else if (match(INCDEC)) {
        set_incdec = 1;
        //retp = makeNode(ASSIGN, "=");
        char op[5];
        strcpy(op, getLexeme());
        TokenSet op_type;
        if(op[0] == '+')
            op_type = INC_ID;
        else
            op_type = DEC_ID;
        advance();
        if (match(ID)) {
            retp = makeNode(op_type, getLexeme());
            advance();
        } else {
            error(NOTID);
        }
    } else if (match(LPAREN)) {
        advance();
        retp = assign_expr();
        if (match(RPAREN))
            advance();
        else
            error(MISPAREN);
    } else {
        error(NOTNUMID);
    }
    return retp;
}

// term      := factor term_tail
// term_tail := MULDIV factor term_tail | NiL
/*BTNode *term(void) {
    BTNode *retp = NULL, *left = NULL;

    retp = left = factor();
    while (match(MULDIV)) {
        retp = makeNode(MULDIV, getLexeme());
        advance();
        retp->left = left;
        retp->right = factor();
        left = retp;
    }
    return retp;
}

// expr      := term expr_tail
// expr_tail := ADDSUB term expr_tail | NiL
BTNode *expr(void) {
    BTNode *retp = NULL, *left = NULL;

    retp = left = term();
    while (match(ADDSUB)) {
        retp = makeNode(ADDSUB, getLexeme());
        advance();
        retp->left = left;
        retp->right = term();
        left = retp;
    }
    return retp;
}
*/
BTNode *unary_expr(BTNode *left) {
    if(left != NULL)
        return left;
    BTNode *retp = NULL;
    if (match(ADDSUB)) {
        retp = makeNode(ADDSUB, getLexeme());
        retp->left = makeNode(INT, "0");
        advance();
        retp->right = unary_expr(NULL);
    }
    else
        retp = factor();
    return retp;
}

BTNode *muldiv_expr(BTNode *left) {
    BTNode *retp = NULL;
    retp = left = unary_expr(left);
    while (match(MULDIV)) {
        retp = makeNode(MULDIV, getLexeme());
        advance();
        retp->left = left;
        retp->right = unary_expr(NULL);
        left = retp;
    }
    return retp;
}

BTNode *addsub_expr(BTNode *left) {
    BTNode *retp = NULL;
    retp = left = muldiv_expr(left);
    while (match(ADDSUB)) {
        retp = makeNode(ADDSUB, getLexeme());
        advance();
        retp->left = left;
        retp->right = muldiv_expr(NULL);
        left = retp;
    }
    return retp;
}

BTNode *and_expr(BTNode *left) {
    BTNode *retp = NULL;
    retp = left = addsub_expr(left);
    while (match(AND)) {
        retp = makeNode(AND, getLexeme());
        advance();
        retp->left = left;
        retp->right = addsub_expr(NULL);
        left = retp;
    }
    return retp;
}

BTNode *xor_expr(BTNode *left) {
    BTNode *retp = NULL;
    retp = left = and_expr(left);
    while (match(XOR)) {
        retp = makeNode(XOR, getLexeme());
        advance();
        retp->left = left;
        retp->right = and_expr(NULL);
        left = retp;
    }
    return retp;
}

BTNode *or_expr(BTNode *left) {
    BTNode *retp = NULL;
    retp = left = xor_expr(left);
    while (match(OR)) {
        retp = makeNode(OR, getLexeme());
        advance();
        retp->left = left;
        retp->right = xor_expr(NULL);
        left = retp;
    }
    return retp;
}

BTNode *assign_expr(void) {
    BTNode *retp = NULL, *left = NULL;
    if(match(ID)) {
        left = makeNode(ID, getLexeme());
        advance();
        if(match(ASSIGN)) {
            retp = makeNode(ASSIGN, getLexeme());
            advance();
            retp->left = left;
            retp->right = assign_expr();
        }
        else {
            retp = or_expr(left);
        }
    }
    else
        retp = or_expr(NULL);  
    return retp;
}

// statement := ENDFILE | END | expr END
void statement(void) {
    BTNode *retp = NULL;

    if (match(ENDFILE)) {
        printf("MOV r0 [0] \nMOV r1 [4]\nMOV r2 [8]\n");
        if(set_incdec) {
            printf("MOV r3 1\n");
        }
        for(int i = 0; i < ins_len; i++) {
            printf("%s", instructions[i]);
        }
        printf("EXIT 0\n");
        exit(0);
    } else if (match(END)) {
        //printf(">> ");
        advance();
    } else {
        retp = assign_expr();
        if (match(END)) {
            postfixTraversal(retp);
            /*printf("Prefix traversal: ");
            printPrefix(retp);*/
            retp = evaluateTree(retp, retp->data == ASSIGN || retp->data == INC_ID || retp->data == DEC_ID);
            //printf("%d\n", retp->val);
            freeReg(retp->lexeme);
            freeTree(retp);
            //printf("\n>> ");
            advance();
        } else {
            error(SYNTAXERR);
        }
    }
}

void err(ErrorType errorNum) {
    if (PRINTERR) {
        fprintf(stderr, "error: ");
        switch (errorNum) {
            case MISPAREN:
                fprintf(stderr, "mismatched parenthesis\n");
                break;
            case NOTNUMID:
                fprintf(stderr, "number or identifier expected\n");
                break;
            case NOTFOUND:
                fprintf(stderr, "variable not defined\n");
                break;
            case RUNOUT:
                fprintf(stderr, "out of memory\n");
                break;
            case NOTLVAL:
                fprintf(stderr, "lvalue required as an operand\n");
                break;
            case DIVZERO:
                fprintf(stderr, "divide by constant zero\n");
                break;
            case SYNTAXERR:
                fprintf(stderr, "syntax error\n");
                break;
            case NOTID:
                fprintf(stderr, "expeted an identifier\n");
                break;
            case NOTDEF:
                fprintf(stderr, "variable not defined\n");
                break;
            case ASSIGNERR:
                fprintf(stderr, "error during assigning values\n");
                break;
            default:
                fprintf(stderr, "undefined error\n");
                break;
        }
    }
    printf("EXIT 1\n");
    exit(0);
}
