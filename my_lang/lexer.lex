/*
 Tokens for a simple expression calculator
*/

%{
	#ifdef interactive
		#include "interactive.tab.h"
	#else
		#include "compiler.tab.h"
	#endif
	#include <stdio.h>
	#include <stdlib.h>
%}

%option noyywrap
WHT [ \n\t\r]
%%

{WHT}	/* Skip whitespace */
[0-9]+("."[0-9]+)?  {yylval.number=atof(yytext); return NUM;}/* parse a floating point number */
"fun" {yylval.id_val = strdup(yytext); return FUN;}
[a-zA-Z]* {yylval.id_val = strdup(yytext); return IDENTIFIER;}
[;{},=*+-/()] return *yytext; /* parse punctuation and end-of-line characters */


. 	printf("Invalid character in expression: %s\n", yytext); exit(1);

%%
