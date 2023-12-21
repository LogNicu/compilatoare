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
static unsigned long long line_counter = 1 ;
static void emitToken(Token t) {
    globalVector.push_back(t);
}
Token getToken() {
    return globalVector[i++];
}
%}
WHT [ \t\r]
ANY_WHT {WHT}*
%x DATA_TYPE_STATE

%%

{WHT}	/* Skip whitespace */

\n {
	line_counter++;
}


"let" { //let has to be put before identifier so identifier doesn't match first
	emitToken({Token::LET,0,"let",line_counter}); return Token::R_SHIFT;
} 

_*[a-zA-Z]+ {
	Token tok = {Token::IDENTIFIER, 0 , std::string(yytext),line_counter};
	emitToken(tok);
}


[0-9]+("."[0-9]+)?  {
    emitToken({Token::NUMBER, std::stod(yytext),std::string(yytext),line_counter});/* parse a floating point number */
    return Token::NUMBER;
}
[*+-/()!><&|^;=,]  {

	emitToken({(Token::Type) yytext[0], 0, std::string(yytext)}); 
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

":" {
	emitToken({Token::COLON, 0, std::string(yytext)});
	yy_push_state(DATA_TYPE_STATE);
}


"->"  {
	emitToken({Token::ARROW,0,"->",line_counter});
	yy_push_state(DATA_TYPE_STATE);
}

<DATA_TYPE_STATE>[a-zA-Z]+[0-9]* {
	Token tok = {Token::DATA_TYPE, 0 , std::string(yytext),line_counter};
	emitToken(tok);
	yy_pop_state();
}

<DATA_TYPE_STATE>{WHT} /*skip whitespace*/
<DATA_TYPE_STATE>\n {
	line_counter++;
}
<DATA_TYPE_STATE>. {
	emitToken({Token::ERROR_TOK,0,std::string(yytext),line_counter});
	return Token::ERROR_TOK;
}

<<EOF>> {emitToken({Token::M_EOF,0,"END",line_counter}); return Token::M_EOF;};

. {
	emitToken({Token::ERROR_TOK,0,std::string(yytext),line_counter});
	return Token::ERROR_TOK;
}

%%
//this produces error: (((540+608)+(!974-!811))*((!703+626)+(140*80)))
//(((540+608)+(!974-!811))+((!703+626)+(140+80)))
int yyFlexLexer::yywrap()   { return 1;}
