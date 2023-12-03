/*
 Tokens for a simple expression calculator
*/
%option c++
%{
#include "common_flex.h"
#include <vector>
#include<iostream>


static std::vector<Token> globalVector;
static int i = 0;
static void emitToken(Token t) {
    globalVector.push_back(t);
}
Token getToken() {
    return globalVector[i++];
}
%}
WHT [ \n\t\r]
%%

{WHT}	/* Skip whitespace */
[0-9]+("."[0-9]+)?  {
    emitToken(Token(Token::NUMBER,  std::stod(yytext),0));/* parse a floating point number */
    return -2;
}
[*+-/()!><]  {
    emitToken(Token((Token::Type) *yytext, 0, *yytext)); /* parse punctuation and end-of-line characters */
    return -3;
}
<<EOF>> {emitToken(Token(Token::M_EOF)); return 0;};
. 	printf("Invalid character in expression: %s\n", yytext); exit(1);

%%
int yyFlexLexer::yywrap()   { return 1;}