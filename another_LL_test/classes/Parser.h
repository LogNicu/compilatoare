//
// Created by nicu on 11/18/23.
//

#ifndef CPP_COMPILER_PARSER_H
#define CPP_COMPILER_PARSER_H
#include "Lexer.h"
#include "Expression.h"

class Parser {
    Lexer lex;
    std::vector<Token> tokens;
    int current;
    bool isAtEnd();
    Token advance();
    Token peek();
    Token previous();
public:
    Parser(std::string &s);
    Expression parseExpr();
    Expression parseEquality();
    Expression parseComparison();
    Expression parseTerm();
    Expression parseFactor();
    Expression parsePrimary();
    Expression parseUnary();
    void expectType(Token t, Token::Type type);
    bool match(const std::vector<Token::Type>& types);
};

#endif //CPP_COMPILER_PARSER_H
