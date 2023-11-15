/* Infix notation calculator--calc */

%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int yylex(void);
void yyerror(char *);
int regno = 0;
int funcno = 0;
%}

/* Define types for semantic values */
%union{
	int number;
}


/* Declare tokens and types for various values */
%token <number> NUM
%type <number> exp
%type <number> exp_lower
%type <number> exp_lowerer

/* Grammar for a simple calculator */
%%
input:    /* empty string */
        | input line
;
X: {printf("funcno:%d\n",funcno++);}
;
line:     '\n'
        | X exp '\n'  {printf("\tmowv a0, a%d\n\tret\n", $2); }
;

exp:    exp_lower  {$$ = $1;}
        | exp '+' exp_lower        { $$ = $1 + $3;    }
        | exp '-' exp_lower       {printf("\tsubw a%d,a%d,a%d\n", regno,$1,$3); $$ = regno; regno++;   }
;
exp_lower: 
        exp_lowerer
        | exp_lower '*' exp_lowerer        { $$ = $1 * $3;    }
        | exp_lower '/' exp_lowerer        { $$ = $1 / $3;    }

        ;
exp_lowerer: 
        NUM {printf("\tli a%d,%d\n",regno, $1); $$ = regno; regno++;}  /*li a5,2*/
        | '(' exp ')' { $$ = $2;    }
        | '-' exp_lowerer {printf("\tnegw a%d,a%d\n", regno,$2); $$ = regno; regno++;    } /* negw a0,a0 */
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
