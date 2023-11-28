//
// Created by nicu on 11/18/23.
//

#ifndef CPP_COMPILER_PARSER_H
#define CPP_COMPILER_PARSER_H
#include "Lexer.h"

class Parser {
    Lexer lex;

public:
    Parser(std::string &s);
    double parseExpr();
    double parseComparison();
    double parseTerm();
    double parseFactor();
    double parsePrimary();
    double parseUnary();
    void expectType(Token t, Token::Type type);
    bool isAtEnd();
    bool match(Token t, std::vector<Token::Type> types);
    void advance();
};

#endif //CPP_COMPILER_PARSER_H
