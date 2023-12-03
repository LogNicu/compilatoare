//
// Created by nicu on 11/18/23.
//

#ifndef CPP_COMPILER_LEXER_H
#define CPP_COMPILER_LEXER_H


#include <string>
#include <unordered_map>
#include <FlexLexer.h>
#include "../flex/common_flex.h"

class Lexer{
    yyFlexLexer *l;
    std::istringstream* stream;
    std::string text;
    std::string::const_iterator pos;
public:
    explicit Lexer(std::string& code);
    Token next();
    ~Lexer();

};


#endif //CPP_COMPILER_LEXER_H
