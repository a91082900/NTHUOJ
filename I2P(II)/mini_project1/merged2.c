#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXINS 10000
#define MAXREG 8


extern char instructions[MAXINS][20];
extern int ins_len;
#define MAXLEN 256

// Token types
typedef enum {
    UNKNOWN, END, ENDFILE, 
    INT, ID,
    ADDSUB, MULDIV,
    ASSIGN, 
    LPAREN, RPAREN, 
    INCDEC, INC_ID, DEC_ID,
    AND, OR, XOR, 
    REG
} TokenSet;

// Test if a token matches the current token 
extern int match(TokenSet token);

// Get the next token
extern void advance(void);

// Get the lexeme of the current token
extern char *getLexeme(void);
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

// Error types
typedef enum {
    UNDEFINED, MISPAREN, NOTID, NOTNUMID, NOTFOUND, RUNOUT, NOTLVAL, DIVZERO, SYNTAXERR, NOTDEF, ASSIGNERR
} ErrorType;

// Structure of the symbol table
typedef struct {
    int val;
    char name[MAXLEN];
} Symbol;

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

// The symbol table
extern Symbol table[TBLSIZE];

// Evaluate the syntax tree
extern BTNode* evaluateTree(BTNode *root, int under_assign);

// Print the syntax tree in prefix
extern void printPrefix(BTNode *root);
extern int postfixTraversal(BTNode *root);
extern void freeReg(char *lexeme);


// Initialize the symbol table with builtin variables
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
int main() {
    initTable();
    //printf(">> ");
    while (1) {
        statement();
    }
    return 0;
}
