//
// Created by nicu on 11/18/23.
//

#include <stdexcept>
#include <iostream>
#include <vector>
#include <sstream>
#include "../classes/Parser.h"
#include "unordered_set"
#define in(X,...) std::unordered_set<Token::Type>{ __VA_ARGS__ }.contains(X)
Parser::Parser(std::string &s) :   current(0), lex(s){
    Token t=lex.next();
    while(t.type != Token::M_EOF) {
        tokens.push_back(t);
        t = lex.next();
    }
    tokens.push_back({Token::M_EOF});
}
static int st_counter = 0;
//#define DEBUG_INFO
#define DEBUG_LEVEL2
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
        throw std::runtime_error("Error: Unexpected token: "+t.typeToStr());
    }
}

Expression Parser::parseExpr() {
    debug();
    return parseEquality();
}

Expression Parser::parseEquality() {
    debug();
    Expression val1 = parseComparison();
    while (match( {Token::EQ_EQ,Token::BANG_EQ})) {
        Token next = previous();
        Expression right = parseComparison();
        val1 = Expression(next,{val1,right});
    }
    return val1;
}

Expression Parser::parseComparison() {
    debug();
    Expression val1 = parseTerm();
    while (match( {Token::GT,Token::LT,Token::GT_EQ,Token::LT_EQ})) {
        Token next = previous();
        Expression right = parseTerm();
        val1 = Expression(next,{val1,right});
    }
    return val1;
}

Expression Parser::parseTerm() {
    debug();
    Expression val1 = parseFactor();
    while ( match( {Token::PLUS,Token::MINUS})) {
        Token next = previous();
        Expression right = parseFactor();
        val1 = Expression(next,{val1,right});
    }
    return val1;
}

Expression Parser::parseFactor() {
    debug();
    Expression val1 = parseUnary();
    while (match( {Token::STAR,Token::SLASH})) {
        Token next = previous();
        Expression right = parseUnary();
        val1 = Expression(next,{val1,right});
    }
    return val1;
}

Expression Parser::parseUnary() {
    debug();
    if(match({Token::BANG,Token::MINUS})) {
        Token tok = previous();
        Expression val = parseUnary();
        return Expression(tok,{val});
    }else{
        return parsePrimary();
    }
}

Expression Parser::parsePrimary() {
    debug();
    if(match({Token::NUMBER})) {
        return Expression(previous());
    }else if(peek().type == Token::O_PAREN) {
        advance();
        Expression value = parseExpr();
        expectType(advance(),Token::C_PAREN);
        return value;
    }
    throw std::runtime_error("Error: Unknown primary: "+peek().toString());
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







