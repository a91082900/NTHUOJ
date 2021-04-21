#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lex.h"
#include "parser.h"

// This package is a calculator
// It works like a Python interpretor
// Example:
// >> y = 2
// >> z = 2
// >> x = 3 * y + 4 / (2 * z)
// It will print the answer of every line
// You should turn it into an expression compiler
// And print the assembly code according to the input

// This is the grammar used in this package
// You can modify it according to the spec and the slide
// statement  :=  ENDFILE | END | expr END
// expr    	  :=  term expr_tail
// expr_tail  :=  ADDSUB term expr_tail | NiL
// term 	  :=  factor term_tail
// term_tail  :=  MULDIV factor term_tail| NiL
// factor	  :=  INT | ADDSUB INT |
//		   	      ID  | ADDSUB ID  | 
//		   	      ID ASSIGN expr |
//		   	      LPAREN expr RPAREN |
//		   	      ADDSUB LPAREN expr RPAREN
/*  
    statement        := END | assign_expr END 
    assign_expr      := ID ASSIGN assign_expr | or_expr 
    or_expr          := xor_expr or_expr_tail 
    or_expr_tail     := OR xor_expr or_expr_tail | NiL 
    xor_expr         := and_expr xor_expr_tail 
    xor_expr_tail    := XOR and_expr xor_expr_tail | NiL 
    and_expr         := addsub_expr and_expr_tail | NiL 
    and_expr_tail    := AND addsub_expr and_expr_tail | NiL 
    addsub_expr      := muldiv_expr addsub_expr_tail 
    addsub_expr_tail := ADDSUB muldiv_expr addsub_expr_tail | NiL 
    muldiv_expr      := unary_expr muldiv_expr_tail 
    muldiv_expr_tail := MULDIV unary_expr muldiv_expr_tail | NiL 
    unary_expr       := ADDSUB unary_expr | factor 
    factor           := INT | ID | INCDEC ID | LPAREN assign_expr RPAREN
*/
int main() {
    initTable();
    //printf(">> ");
    while (1) {
        statement();
    }
    return 0;
}
