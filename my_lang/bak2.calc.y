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
%type<number> primary
%type <number> exp
%type <number> unary
%type <number> factor
%type <number> call
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

vardecl: IDENTIFIER '=' exp {$$ = $3; varMap[std::string($1)] = $3; }
;

dumb_name_hack: IDENTIFIER {printf("%s:\n",$1);}
fundecl: FUN dumb_name_hack '(' param_list ')'  '{'  code_block  '}' {printf("\tmv a0, a%d\n\n",regno-1);}
;

param_list: /*empty */ 
	| IDENTIFIER
	| IDENTIFIER ',' param_list

code_block: /*empty*/ 
        | code_block  statement
;



exp: factor 
        | factor '-' factor {printf("\taddiw a%d,a%d,a%d\n", regno,$1,$3); $$ = regno; regno++;   }
        | factor '+' factor {printf("\tsubw a%d,a%d,a%d\n", regno,$1,$3); $$ = regno; regno++;   }
;
factor: unary 
        | unary '*' unary {printf("\tmulw a%d,a%d,a%d\n", regno,$1,$3); $$ = regno; regno++;   }
        | unary '/' unary {printf("\tdivw a%d,a%d,a%d\n", regno,$1,$3); $$ = regno; regno++;   }
;
unary: '-' unary  {printf("\tnegw a%d,a%d\n", regno,$2); $$ = regno; regno++;    } 
| call
;
call: primary 
        | IDENTIFIER '('arg_list ')' {printf("\tcall %s\n",$1);}
;
arg_list: /*empty */ 
	| exp
	| exp ',' arg_list
;
primary: NUM {printf("\tli a%d,%d\n",regno, $1); $$ = regno; regno++;} 
        | IDENTIFIER {$$ = 0;}
        | exp
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
