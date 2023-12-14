//
// Created by nicu on 11/18/23.
//

#include "../classes/Lexer.h"
#include <regex>
#include <string>
//#######################################################################################################
extern Token getToken();
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

