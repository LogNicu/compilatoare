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


_*[a-zA-Z]+ {
	Token tok = {Token::IDENTIFIER, 0 , std::string(yytext)};
	emitToken(tok);
}


[0-9]+("."[0-9]+)?  {
    emitToken({Token::NUMBER, std::stod(yytext)});/* parse a floating point number */
    return Token::NUMBER;
}
[*+-/()!><]  {

	emitToken({(Token::Type) yytext[0], 0, std::string(yytext)}); /* parse punctuation and end-of-line characters */
	return (Token::Type) yytext[0];
}

">=" {emitToken({Token::GT_EQ}); return Token::GT_EQ;}

"<=" {emitToken({Token::LT_EQ}); return Token::LT_EQ;}


"==" {emitToken({Token::EQ_EQ}); return Token::EQ_EQ;}

"!=" {emitToken({Token::BANG_EQ}); return Token::BANG_EQ;}

"!" {emitToken({Token::BANG}); return Token::BANG;}

<<EOF>> {emitToken({Token::M_EOF}); return Token::M_EOF;};

. {

	std::cout << "\033[91m";
	std::cout<<"{"<<(int64_t)yytext[0]<<"}["<<yytext[0]<<"]\n";
	std::cout<<"\033[0m";
}

%%
//this produces error: (((540+608)+(!974-!811))*((!703+626)+(140*80)))
//(((540+608)+(!974-!811))+((!703+626)+(140+80)))
int yyFlexLexer::yywrap()   { return 1;}
