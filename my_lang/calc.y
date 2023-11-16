/* Infix notation calculator--calc */

%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include<iostream>
#include <unordered_map>
int yylex(void);
void yyerror(char *);
int current_block = 0;
std::unordered_map<std::string, int> varMap;
void yyerror(const char *s) {
    fprintf(stderr, "Syntax error: %s\n", s);
    // You can print the stack or expression here
}
%}

/* Define types for semantic values */

%define parse.error verbose
%union{
	int number;
        char* id_val;
}


/* Declare tokens and types for various values */
%token <number> NUM
%token <id_val> IDENTIFIER
%token <id_val> FUN
%type<number> vardecl
%type<number> operand
%type<number>fun_call
%type <number> exp
%type <number> exp_mult_div
%type <number> exp_group_op_neg
/* Grammar for a simple calculator */
%%
input:    /* empty string */
        | input line
;

;
/* line:     '\n'
        | exp '\n' {printf("Result: %d\n", $1);}
        | vardecl '\n' {printf("Declared var with value: %d\n", $1);}
        | fundecl 
;
*/
line: fundecl | statement

statement: exp ';'
        | vardecl ';'
;

fun_call: IDENTIFIER '(' ')' {$$ = 0;}

vardecl: IDENTIFIER '=' exp {$$ = $3; varMap[std::string($1)] = $3; }
;

operand: NUM {$$ = $1;}
        | IDENTIFIER {$$ = varMap[std::string($1)]; }
        | fun_call
;

fundecl: FUN  IDENTIFIER '(' param_list ')' code_block
;

param_list: /*empty */ 
	| IDENTIFIER
	| IDENTIFIER ',' param_list
;

code_block: /*empty*/ 
        | code_block  statement
;

exp:    exp_mult_div  {$$ = $1;}
        | exp_mult_div '+' exp_mult_div     { $$ = $1 + $3;    }
        | exp_mult_div '-' exp_mult_div     { $$ = $1 + $3;    }
;
exp_mult_div: 
        exp_group_op_neg {$$ = $1;}
        | exp_group_op_neg '*' exp_group_op_neg       { $$ = $1 * $3;    }
        | exp_group_op_neg '/' exp_group_op_neg      { $$ = $1 / $3;    }

        ;
exp_group_op_neg: 
        operand {$$ = $1;}
        | '(' exp ')' { $$ = $2;    }
        | '-' exp_group_op_neg {$$ = -$2;}
        ;
%%

///TODO make something viable, add support for variable declaration ? function names ?

void yyerror (char *s)  /* Called by yyparse on error */
{
	printf ("%s\n", s);
	exit(0);
}

int main()
{
	yyparse();
	return 0;
}
