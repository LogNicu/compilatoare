//
// Created by nicu on 11/18/23.
//

#ifndef CPP_COMPILER_LEXER_H
#define CPP_COMPILER_LEXER_H


#include <string>
#include <unordered_map>

#include "../flex_dir/common_flex.h"
#include "../flex_dir/flex_lexer.h"

class Lexer{
    yyFlexLexer *l;
    std::istringstream* stream;
    std::string text;
public:
    explicit Lexer(std::string& code);
    Token next();
    ~Lexer();

};


#endif //CPP_COMPILER_LEXER_H
