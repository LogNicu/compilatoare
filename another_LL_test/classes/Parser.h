//
// Created by nicu on 11/18/23.
//

#ifndef CPP_COMPILER_PARSER_H
#define CPP_COMPILER_PARSER_H
#include "Lexer.h"
#include "Expression.h"

class Parser {

    typedef Expression* (Parser::*parseBinaryFn)();
    Lexer lex;
    std::vector<Token> tokens;
    int current;
    bool isAtEnd();
    Token advance();
    Token peek();
    Token previous();
    Token consume(Token::Type type, std::string message="");
    Expression* parseBinaryExpr(std::vector<Token::Type> operators, parseBinaryFn operand);
    void error(Token token, std::string message);
public:
    Parser(std::string &s);

    //Statements
    void parse();
    void statement();
    void exprStatement();
    void varDecl();
    ///Expressions
    Expression *parseExpr();
    Expression *parseLogicOr();
    Expression *parseLogicAnd();
    Expression *parseBitOr();
    Expression *parseBitXor();
    Expression *parseBitAnd();
    Expression *parseEquality();
    Expression *parseComparison();
    Expression *parseShift();
    Expression *parseTerm();
    Expression *parseFactor();
    Expression *parsePrimary();
    Expression *parseUnary();
    void expectType(Token t, Token::Type type);
    bool match(const std::vector<Token::Type>& types);

};

#endif //CPP_COMPILER_PARSER_H
