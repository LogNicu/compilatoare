//
// Created by nicu on 11/18/23.
//

#include <stdexcept>
#include <iostream>
#include <vector>
#include <sstream>
#include "../classes/Parser.h"
#include "unordered_set"
#include "../classes/ExprBinary.h"
#include "../classes/ExprUnary.h"
#include "../classes/ExprLiteral.h"

#define in(X,...) std::unordered_set<Token::Type>{ __VA_ARGS__ }.contains(X)
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
        error(t,"Unexpected token");
    }
}

Expression *Parser::parseExpr() {
    debug();

    Expression* exp = parseLogicOr();
    if (!isAtEnd()) {
        expectType(peek(), Token::M_EOF);
    }
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
        return parsePrimary();
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







