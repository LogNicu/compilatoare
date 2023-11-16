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
int regno = 0;
int funcno = 0;
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
line:   fundecl 
        | statement 

statement: exp ';' 
        | vardecl ';' 
;

fun_call: IDENTIFIER '(' arg_list ')' {printf("\tcall %s\n",$1);}

vardecl: IDENTIFIER '=' exp {$$ = $3; varMap[std::string($1)] = $3; }
;

operand: NUM {printf("\tli a%d,%d\n",regno, $1); $$ = regno; regno++;} 
        | IDENTIFIER {}
        | fun_call {printf("\tmv a%d, a0\n",regno); $$ = regno; regno++;} 
;

dumb_name_hack: IDENTIFIER {printf("%s:\n",$1);}
fundecl: FUN dumb_name_hack '(' param_list ')'  '{'  code_block  '}' {printf("\tmv a0, a%d\n\tret\n\n",regno-1);}
;

param_list: /*empty */ 
	| IDENTIFIER
	| IDENTIFIER ',' param_list
arg_list: /*empty */ 
	| exp
	| exp ',' arg_list
;

code_block: /*empty*/ 
        | code_block  statement
;

exp:      exp '+' exp_mult_div     {printf("\taddiw a%d,a%d,a%d\n", regno,$1,$3); $$ = regno; regno++;   }
        | exp '-' exp_mult_div     {printf("\tsubw a%d,a%d,a%d\n", regno,$1,$3); $$ = regno; regno++;   }
        | exp_mult_div  {$$ = $1;}
;
exp_mult_div:  exp_mult_div '*' exp_group_op_neg      {printf("\tmulw a%d,a%d,a%d\n", regno,$1,$3); $$ = regno; regno++;   }
        | exp_mult_div '/' exp_group_op_neg      {printf("\tdivw a%d,a%d,a%d\n", regno,$1,$3); $$ = regno; regno++;   }
        | exp_group_op_neg {$$ = $1;}
        ;
exp_group_op_neg: operand {$$ = $1;}
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
