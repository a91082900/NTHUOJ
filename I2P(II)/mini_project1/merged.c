#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXINS 10000
#define MAXREG 8

#define MAXLEN 256
#define TBLSIZE 64

// Set PRINTERR to 1 to print error message while calling error()
// Make sure you set PRINTERR to 0 before you submit your code
#define PRINTERR 0

// Call this macro to print error message and exit the program
// This will also print where you called it in your program
#define error(errorNum) { \
    if (PRINTERR) \
        fprintf(stderr, "error() called at %s:%d: ", __FILE__, __LINE__); \
    err(errorNum); \
}
#define dest (under_assign ? instructions[ins_len++]: trash)

int reg = 0;
int ins_len = 0;
char trash[20], instructions[MAXINS][20];
// Error types
typedef enum {
    UNDEFINED, MISPAREN, NOTID, NOTNUMID, NOTFOUND, RUNOUT, NOTLVAL, DIVZERO, SYNTAXERR, NOTDEF, ASSIGNERR
} ErrorType;

// Structure of the symbol table
typedef struct {
    int val;
    char name[MAXLEN];
} Symbol;
// Token types
typedef enum {
    UNKNOWN, END, ENDFILE, 
    INT, ID,
    ADDSUB, MULDIV,
    ASSIGN, 
    LPAREN, RPAREN, 
    INCDEC, 
    AND, OR, XOR, 
    REG
} TokenSet;
// Structure of a tree node
typedef struct _Node {
    TokenSet data;
    int val;
    int ldepth;
    int rdepth;
    int hasID;
    char lexeme[MAXLEN];
    struct _Node *left; 
    struct _Node *right;
} BTNode;


int sbcount = 0;
Symbol table[TBLSIZE];

extern BTNode* evaluateTree(BTNode *root, int under_assign);

// Print the syntax tree in prefix
extern void printPrefix(BTNode *root);
extern int postfixTraversal(BTNode *root);
extern int match(TokenSet token);

// Get the next token
extern void advance(void);

// Get the lexeme of the current token
extern char *getLexeme(void);
extern void initTable(void);

// Get the value of a variable
extern int getval(char *str);

// Set the value of a variable
extern int setval(char *str, int val);

extern int findaddr(char *str);

// Make a new node according to token type and lexeme
extern BTNode *makeNode(TokenSet tok, const char *lexe);

// Free the syntax tree
extern void freeTree(BTNode *root);

extern BTNode *factor(void);
extern BTNode *assign_expr();
extern BTNode *or_expr(BTNode*);
extern BTNode *xor_expr(BTNode*);
extern BTNode *and_expr(BTNode*);
extern BTNode *addsub_expr(BTNode*);
extern BTNode *muldiv_expr(BTNode*);
extern BTNode *unary_expr(BTNode*);
//extern BTNode *term(void);
//extern BTNode *expr(void);
extern void statement(void);

// Print error message and exit the program
extern void err(ErrorType errorNum);


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
        retp = makeNode(ASSIGN, "=");
        char op[5];
        strcpy(op, getLexeme());
        if(op[0] == '+')
            retp->right = makeNode(ADDSUB, "+");
        else
            retp->right = makeNode(ADDSUB, "-");
        retp->right->right = makeNode(INT, "1");
        advance();
        if (match(ID)) {
            retp->left = makeNode(ID, getLexeme());
            retp->right->left = makeNode(ID, getLexeme());
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
        for(int i = 0; i < ins_len; i++) {
            printf("%s", instructions[i]);
        }
        printf("MOV r0 [0]\nMOV r1 [4]\nMOV r2 [8]\nEXIT 0\n");
        exit(0);
    } else if (match(END)) {
        //printf(">> ");
        advance();
    } else {
        retp = assign_expr();
        if (match(END)) {
            postfixTraversal(retp);
            retp = evaluateTree(retp, retp->data == ASSIGN);
            /*printf("%d\n", retp->val);
            printf("Prefix traversal: ");
            printPrefix(retp);*/
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
static TokenSet getToken(void);
static TokenSet curToken = UNKNOWN;
static char lexeme[MAXLEN];

TokenSet getToken(void)
{
    int i = 0;
    char c = '\0';

    while ((c = fgetc(stdin)) == ' ' || c == '\t');

    if (isdigit(c)) {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isdigit(c) && i < MAXLEN) {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT;
    } else if (c == '+' || c == '-') {
        lexeme[0] = c;
        char new_c = fgetc(stdin);
        if(c == new_c) {
            lexeme[1] = c;
            lexeme[2] = '\0';
            return INCDEC;
        }
        else {
            ungetc(new_c, stdin);
            lexeme[1] = '\0';
            return ADDSUB;   
        }
    } else if (c == '*' || c == '/') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    } else if (c == '\n') {
        lexeme[0] = '\0';
        return END;
    } else if (c == '=') {
        strcpy(lexeme, "=");
        return ASSIGN;
    } else if (c == '(') {
        strcpy(lexeme, "(");
        return LPAREN;
    } else if (c == ')') {
        strcpy(lexeme, ")");
        return RPAREN;
    } else if (c == '|') {
        strcpy(lexeme, "|");
        return OR;
    } else if (c == '&') {
        strcpy(lexeme, "&");
        return AND;
    } else if (c == '^') {
        strcpy(lexeme, "^");
        return XOR;
    } else if (isalpha(c) || c == '_') {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while ((isalpha(c) || isdigit(c) || c == '_') && i < MAXLEN) {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return ID;
    } else if (c == EOF) {
        return ENDFILE;
    } else {
        return UNKNOWN;
    }
}

void advance(void) {
    curToken = getToken();
}

int match(TokenSet token) {
    if (curToken == UNKNOWN)
        advance();
    return token == curToken;
}

char *getLexeme(void) {
    return lexeme;
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
int main() {
    initTable();
    //printf(">> ");
    while (1) {
        statement();
    }
    return 0;
}
