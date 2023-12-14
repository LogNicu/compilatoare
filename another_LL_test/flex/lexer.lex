/*
 Tokens for a simple expression calculator
*/
%option c++
%option batch
%{
#include "common_flex.h"
#include <vector>
#include <cstdint>
#include <unordered_set>
#include <iostream>


static std::vector<Token> globalVector;
static int i = 0;
static unsigned long long line_counter = 0 ;
static void emitToken(Token t) {
    globalVector.push_back(t);
}
Token getToken() {
    return globalVector[i++];
}
%}
WHT [ \t\r]
ANY_WHT {WHT}*
%%

{WHT}	/* Skip whitespace */

\n {
	line_counter++;
}
_*[a-zA-Z]+ {
	Token tok = {Token::IDENTIFIER, 0 , std::string(yytext),line_counter};
	emitToken(tok);
}


[0-9]+("."[0-9]+)?  {
    emitToken({Token::NUMBER, std::stod(yytext),"",line_counter});/* parse a floating point number */
    return Token::NUMBER;
}
[*+-/()!><&|^]  {

	emitToken({(Token::Type) yytext[0], 0, std::string(yytext)}); /* parse punctuation and end-of-line characters */
	return (Token::Type) yytext[0];
}

">=" {emitToken({Token::GT_EQ,0,">=",line_counter}); return Token::GT_EQ;}

"<=" {emitToken({Token::LT_EQ,0,"<=",line_counter}); return Token::LT_EQ;}


"==" {emitToken({Token::EQ_EQ,0,"==",line_counter}); return Token::EQ_EQ;}


"!=" {emitToken({Token::BANG_EQ,0,"!=",line_counter}); return Token::BANG_EQ;}


"||" {emitToken({Token::LOGIC_OR,0,"||",line_counter}); return Token::LOGIC_OR;}

"&&" {emitToken({Token::LOGIC_AND,0,"&&",line_counter}); return Token::LOGIC_AND;}

"<<" {emitToken({Token::L_SHIFT,0,"<<",line_counter}); return Token::L_SHIFT;}
">>" {emitToken({Token::R_SHIFT,0,">>",line_counter}); return Token::R_SHIFT;}

<<EOF>> {emitToken({Token::M_EOF,0,"END",line_counter}); return Token::M_EOF;};

. {

	std::cout << "\033[91m";
	std::cout<<"{"<<(int64_t)yytext[0]<<"}["<<yytext[0]<<"]\n";
	std::cout<<"\033[0m";
}

%%
//this produces error: (((540+608)+(!974-!811))*((!703+626)+(140*80)))
//(((540+608)+(!974-!811))+((!703+626)+(140+80)))
int yyFlexLexer::yywrap()   { return 1;}
