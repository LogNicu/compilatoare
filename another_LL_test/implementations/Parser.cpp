//
// Created by nicu on 11/18/23.
//

#include <stdexcept>
#include <iostream>
#include <vector>
#include "../classes/Parser.h"
#include "unordered_set"
#define in(X,...) std::unordered_set<Token::Type>{ __VA_ARGS__ }.contains(X)
Parser::Parser(std::string &s) : lex(s) {}
static int st_counter = 0;
#define DEBUG_INFO
#define DEBUG_LEVEL2
static void inline currentIndent() {
#ifdef DEBUG_INFO
    for(int i = 0; i < st_counter;i++) std::cout<<"| ";
#endif
}

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
    Token next = lex.peek();
    if(next.type != Token::M_EOF && match(next, {Token::EQ_EQ,Token::BANG_EQ})) lex.next();
    while (next.type != Token::M_EOF && match(next, {Token::EQ_EQ,Token::BANG_EQ})) {
        if(next.type == Token::EQ_EQ) {
            val1 = val1 == parseComparison();
        }
        if(next.type == Token::BANG_EQ) {
            val1 = val1 != parseComparison();
        }
        if((lex.peek().type != Token::M_EOF && match(lex.peek(), {Token::EQ_EQ,Token::BANG_EQ})))
            next = lex.next();
        else break;
    }
    return val1;
}

double Parser::parseComparison() {
    double val1 = parseTerm();
    Token next = lex.peek();
    if(next.type != Token::M_EOF && match(next, {Token::GT,Token::LT,Token::GT_EQ,Token::LT_EQ})) lex.next();
    while (next.type != Token::M_EOF && match(next, {Token::GT,Token::LT,Token::GT_EQ,Token::LT_EQ})) {
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
        if((lex.peek().type != Token::M_EOF && match(lex.peek(), {Token::GT,Token::LT,Token::GT_EQ,Token::LT_EQ})))
            next = lex.next();
        else break;
    }
    return val1;
}

double Parser::parseTerm() {
    double val1 = parseFactor();
    Token next = lex.peek();
    if(next.type != Token::M_EOF && match(next, {Token::PLUS,Token::MINUS})) lex.next();
    while (next.type != Token::M_EOF && match(next, {Token::PLUS,Token::MINUS})) {
        if(next.type == Token::PLUS) {
            val1 += parseFactor();
        }
        if(next.type == Token::MINUS) {
            val1 -= parseFactor();
        }
        if((lex.peek().type != Token::M_EOF && match(lex.peek(), {Token::PLUS,Token::MINUS})))
            next = lex.next();
        else break;
    }
    return val1;
}

double Parser::parseFactor() {
    double val1 = parseUnary();
    Token next = lex.peek();
    if(((next.type != Token::M_EOF) && match(next, {Token::STAR,Token::SLASH}))) lex.next();
    while ((next.type != Token::M_EOF) && match(next, {Token::STAR,Token::SLASH})) {
        if(next.type == Token::STAR) {
            val1 *= parseUnary();
        }
        if(next.type == Token::SLASH) {
            val1 /= parseUnary();
        }
        if((lex.peek().type != Token::M_EOF) && match(lex.peek(), {Token::STAR,Token::SLASH}))
            next = lex.next();
        else break;
    }
    return val1;
}

double Parser::parseUnary() {
    Token tok = lex.peek();
    if(match(tok,{Token::BANG,Token::MINUS})) {
        lex.next();
        double val = parseUnary();
        return tok.type == Token::BANG ? !val : -val;
    }else{
        return parsePrimary();
    }
}

double Parser::parsePrimary() {
    Token next = lex.next();
    if(next.type == Token::NUMBER) {
        return next.value;
    }else if(next.type == Token::O_PAREN) {
        double value = parseExpr();
        expectType(lex.next(),Token::C_PAREN);
        return value;
    }
    return 0;
}

bool Parser::isAtEnd() {
    return lex.peek().type == Token::M_EOF;
}

bool Parser::match(Token t, std::vector<Token::Type> types) {
    for(Token::Type type: types) {
        if(t.type == type) {
            return true;
        }
    }
    return false;
}

void Parser::advance() {

}






