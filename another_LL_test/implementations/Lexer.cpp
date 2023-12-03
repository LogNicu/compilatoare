//
// Created by nicu on 11/18/23.
//


#include "../flex/common_flex.h"
#include "../classes/Lexer.h"
#include "../classes/Token.h"
#include <regex>


//#######################################################################################################

Lexer::Lexer(std::string& code)
{
    stream = new std::istringstream (code);
    l = new yyFlexLexer(stream);
}

Lexer::~Lexer() {
    delete stream;
    delete l;
}

Token Lexer::next() {
    l->yylex();
    return getToken();
}



#undef stringify

