//
// Created by nicu on 11/18/23.
//

#include <stdexcept>
#include <iostream>
#include <vector>
#include <sstream>
#include "../classes/Parser.h"
#include "unordered_set"
#include "../classes/expressions/ExprBinary.h"
#include "../classes/expressions/ExprUnary.h"
#include "../classes/expressions/ExprLiteral.h"
#include "../classes/statements/VarStmt.h"
#include "../classes/statements/ExprStmt.h"
#include "../classes/expressions/ExprCall.h"
#include "../classes/expressions/ExprVar.h"
#include "../classes/statements/FunDecl.h"

Parser::Parser(std::string &s) :   current(0), lex(s){
    Token t=lex.next();
    while(t.type != Token::M_EOF) {
        tokens.push_back(t);
        t = lex.next();
    }
    tokens.push_back(t);
}
static int st_counter = 0;
//#define DEBUG_INFO
static void inline currentIndent() {
#ifdef DEBUG_INFO
    for(int i = 0; i < st_counter;i++) std::cout<<"| ";
#endif
}
//TODO not working:   ((142+!197)-(302*!630))
static inline void debug1(std::string s) {
#ifdef DEBUG_INFO
    currentIndent();
    std::cout << "\033[96m";
    std::cout<<s<<"\n";
    std::cout<<"\033[0m";
    st_counter++;
#endif
}




#define debug() debug1(__PRETTY_FUNCTION__)

static inline  void debug2() {
#ifdef DEBUG_INFO
    st_counter--;
#endif
}
void Parser::expectType(Token t, Token::Type type) {
    if(t.type != type) {
        error(t,"Unexpected token. Expected token of type: "+Token::typeToStr(type));
    }
}

void Parser::parse() {
    debug();
    while (!isAtEnd()) {
        Statement *smt = statement();
        smt->print();
        delete smt;
    }
}

Statement* Parser::statement() {
    debug();
    Statement* stmt;
    if (match({Token::LET})) {
        stmt = varDecl();
    }else if(match({Token::FN})) {
        stmt = funStmt();
    }else{
        stmt = exprStatement();
    }
    return stmt;
}

Statement* Parser::varDecl() {
    debug();
    Token name = consume(Token::IDENTIFIER, "Expected an identifier");
    expectType(advance(), Token::COLON);
    Token type = consume(Token::DATA_TYPE, "Expected a data type");
    expectType(advance(), Token::EQUAL);
    Expression *expr = parseExpr();
    expectType(advance(), Token::SEMICOL);
    return new VarStmt(name,type, expr);


}

Statement *Parser::funStmt() {
    debug();
    Token funName = consume(Token::IDENTIFIER, "Expected an identifier");
    consume(Token::O_PAREN, "Expected open paren after fn");
    std::vector<std::pair<Token, Token>> params;
    while (!match({Token::C_PAREN})) {
        Token name = consume(Token::IDENTIFIER, "Expected an identifier");
        consume(Token::COLON, "Expected : after param name");
        Token type = consume(Token::DATA_TYPE, "Expected a data type");
        if(peek().type != Token::C_PAREN) {
            consume(Token::COMMA, "Expected comma after param");
        }
        params.push_back(std::pair<Token,Token>{name, type});
    }
    Token returnType = Token(Token::DATA_TYPE,0,"void"); //TODO create vod data type;
    if(match({Token::ARROW})) {
        returnType = advance();
    }
    consume(Token::O_ACCOL, "Expected accolade before function body");

    std::vector<Statement*> statements;
    while (!match({Token::C_ACCOL})) {
        statements.push_back(statement());
    }
    return new FunDecl(funName, returnType, params, statements);
//    consume(Token::O_ACCOL, "Expected accolade after function body");



    return nullptr;
}

Statement* Parser::exprStatement() {
    debug();
    Expression* expr = parseExpr();
    expectType(advance(), Token::SEMICOL);
    return new ExprStmt(expr);
}

Expression *Parser::parseExpr() {
    debug();
    Expression* exp = parseLogicOr();
    return exp;
}

Expression* Parser::parseBinaryExpr(std::vector<Token::Type> operators, parseBinaryFn operand) {
    Expression* left = (this->*operand)();
    while (match(operators)) {
        Token next = previous();
        Expression* right = (this->*operand)();
        left = new ExprBinary(next, left,right);
    }
    return left;
}

Expression* Parser::parseLogicOr() {
    debug();
    return parseBinaryExpr({Token::LOGIC_OR}, &Parser::parseLogicAnd);
}

Expression* Parser::parseLogicAnd() {
    debug();
    return parseBinaryExpr({Token::LOGIC_AND}, &Parser::parseBitOr);
}
Expression* Parser::parseBitOr() {
    debug();
    return parseBinaryExpr({Token::OR}, &Parser::parseBitXor);
}
Expression* Parser::parseBitXor() {
    debug();
    return parseBinaryExpr({Token::XOR}, &Parser::parseBitAnd);
}
Expression* Parser::parseBitAnd() {
    debug();
    return parseBinaryExpr({Token::AND}, &Parser::parseEquality);
}

Expression* Parser::parseEquality() {
    debug();
    return parseBinaryExpr({Token::EQ_EQ,Token::BANG_EQ}, &Parser::parseComparison);
}

Expression* Parser::parseComparison() {
    debug();
    return parseBinaryExpr({Token::GT,Token::LT,Token::GT_EQ,Token::LT_EQ},
                           &Parser::parseShift);
}

Expression* Parser::parseShift() {
    debug();
    return parseBinaryExpr({Token::L_SHIFT,Token::R_SHIFT}, &Parser::parseTerm);
}

Expression* Parser::parseTerm() {
    debug();
    return parseBinaryExpr({Token::PLUS,Token::MINUS}, &Parser::parseFactor);
}

Expression* Parser::parseFactor() {
    debug();
    return parseBinaryExpr({Token::STAR,Token::SLASH}, &Parser::parseUnary);
}

Expression* Parser::parseUnary() {
    debug();
    if(match({Token::BANG,Token::MINUS})) {
        Token tok = previous();
        Expression *val = parseUnary();
        return new ExprUnary(tok,val);
    }else{
        return parseCall();
    }
}

Expression *Parser::parseCall() {
    debug();
    Expression* expr = parsePrimary();
    if(match({Token::O_PAREN})) {
        std::vector<Expression*> arguments;
        do {
            arguments.push_back(parseExpr());
        } while (match({Token::COMMA}));
        consume(Token::C_PAREN,"Expected closed paren after function call start");
        return new ExprCall(expr, arguments);
    }else {
        return expr;
    }
}

Expression* Parser::parsePrimary() {
    debug();
    if(match({Token::NUMBER})) {
        return  new ExprLiteral(previous());
    }else if(peek().type == Token::O_PAREN) {
        advance();
        Expression* value = parseExpr();
        expectType(advance(),Token::C_PAREN);
        return value;
    }else if(match({Token::IDENTIFIER})) {
        return new ExprVar(previous());
    }
    error(peek(),"Expected expression");
}



bool Parser::match(const std::vector<Token::Type>& types) {
    if(peek().type == Token::M_EOF) {
        return false;
    }
    for(Token::Type type: types) {
        if(peek().type == type){
            advance();
            return true;
        }
    }
    return false;
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

Token Parser::previous() {
    return tokens.at(current - 1);
}

bool Parser::isAtEnd() {
    return peek().type == Token::M_EOF;
}

Token Parser::peek() {
    return tokens.at(current);
}

void Parser::error(Token token, std::string message) {
    throw std::runtime_error("[line "+std::to_string(token.lineNumber)+"] Error at '"+token.lexemme+"': "+message);
}

Token Parser::consume(Token::Type type, std::string message) {
    if (peek().type == type) {
        return advance();
    }

    error(peek(), message);
}















