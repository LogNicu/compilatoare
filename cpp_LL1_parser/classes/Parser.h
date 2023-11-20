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
    double parseExprP(double val);
    double parseTerm();
    double parseTermP(double val);
    double parseFactor();
    void expect(Token t, Token::Type type);
};

#endif //CPP_COMPILER_PARSER_H
