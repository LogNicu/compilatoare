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
Parser::Parser(std::string s) :   current(0), lex(std::istringstream (s)){
    Token t=lex.next();
    while(t.type != Token::M_EOF) {
        tokens.push_back(t);
        t = lex.next();
    }
    tokens.push_back({Token::M_EOF,0,0});
}
static int st_counter = 0;
#define DEBUG_INFO
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

double Parser::parseExpr() {
    return parseEquality();
}

double Parser::parseEquality() {
    double val1 = parseComparison();
    while (match( {Token::EQ_EQ,Token::BANG_EQ})) {
        Token next = previous();
        if(next.type == Token::EQ_EQ) {
            val1 = val1 == parseComparison();
        }
        if(next.type == Token::BANG_EQ) {
            val1 = val1 != parseComparison();
        }
    }
    return val1;
}

double Parser::parseComparison() {
    double val1 = parseTerm();
    while (match( {Token::GT,Token::LT,Token::GT_EQ,Token::LT_EQ})) {
        Token next = previous();
        if(next.type == Token::GT) {
            val1 = val1 > parseTerm();
        }
        if(next.type == Token::LT) {
            val1 = val1 < parseTerm();
        }
        if(next.type == Token::GT_EQ) {
            val1 = val1 >= parseTerm();
        }
        if(next.type == Token::LT_EQ) {
            val1 = val1 <= parseTerm();
        }
    }
    return val1;
}

double Parser::parseTerm() {
    double val1 = parseFactor();
    while ( match( {Token::PLUS,Token::MINUS})) {
        Token next = previous();
        if(next.type == Token::PLUS) {
            val1 += parseFactor();
        }
        if(next.type == Token::MINUS) {
            val1 -= parseFactor();
        }
    }
    return val1;
}

double Parser::parseFactor() {
    double val1 = parseUnary();
    while (match( {Token::STAR,Token::SLASH})) {
        Token next = previous();
        if(next.type == Token::STAR) {
            val1 *= parseUnary();
        }
        if(next.type == Token::SLASH) {
            val1 /= parseUnary();
        }
    }
    return val1;
}

double Parser::parseUnary() {
    if(match({Token::BANG,Token::MINUS})) {
        Token tok = previous();
        double val = parseUnary();
        return tok.type == Token::BANG ? !val : -val;
    }else{
        return parsePrimary();
    }
}

double Parser::parsePrimary() {

    if(match({Token::NUMBER})) {
        return previous().value;
    }else if(peek().type == Token::O_PAREN) {
        advance();
        double value = parseExpr();
        expectType(advance(),Token::C_PAREN);
        return value;
    }
    return 0;
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







