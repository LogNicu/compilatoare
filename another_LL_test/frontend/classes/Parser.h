//
// Created by nicu on 11/18/23.
//

#ifndef CPP_COMPILER_PARSER_H
#define CPP_COMPILER_PARSER_H
#include "Lexer.h"
#include "expressions/Expression.h"
#include "statements/Statement.h"
#include "Token.h"

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
    std::vector<Statement*> parse();
    Statement* statement();
    Statement* exprStatement();
    Statement* varDecl(Token dataType, Token identifier);
    Statement* returnStatement();
    Statement* funStmt(Token returnType, Token identifier);
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
    Expression *parseUnary();
    Expression *parseCall();
    Expression *parsePrimary();
    void expectType(Token t, Token::Type type);
    bool match(const std::vector<Token::Type>& types);

};

#endif //CPP_COMPILER_PARSER_H
