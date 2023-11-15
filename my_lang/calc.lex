/*
 Tokens for a simple expression calculator
*/

%{
	#include "calc.tab.h"
	#include <stdio.h>
	#include <stdlib.h>
%}

%option noyywrap
WHT [ \t\r]
%%

{WHT}	/* Skip whitespace */

[0-9]+("."[0-9]+)?  {yylval.number=atof(yytext); return NUM;}/* parse a floating point number */
[a-zA-Z]* {yylval.id_val =strdup(yytext); return IDENTIFIER;}
[{},=*+-/\n()] return *yytext; /* parse punctuation and end-of-line characters */


. 	printf("Invalid character in expression: %s\n", yytext); exit(1);

%%
