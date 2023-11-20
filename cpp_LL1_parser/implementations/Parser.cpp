//
// Created by nicu on 11/18/23.
//

#include <stdexcept>
#include <iostream>
#include "../classes/Parser.h"
#include "unordered_set"
#define in(X,...) std::unordered_set<Token::Type>{ __VA_ARGS__ }.contains(X)
Parser::Parser(std::string &s) : lex(s){}
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
void Parser::expect(Token t, Token::Type type) {
    if(t.type != type) {
        throw std::runtime_error("Error: Unexpected token");
    }
}

double Parser::parseExpr() {
    debug();

    double val1 = parseTerm();
#ifdef DEBUG_LEVEL2
    currentIndent(); std::cout<<"val1 from parseTerm() = "<<val1<<"\n";
#endif
    double val2 = parseExprP(val1);
#ifdef DEBUG_LEVEL2
    currentIndent(); std::cout<<"val2 from parseExprP("<<val1<<") = "<<val2<<"\n";
#endif
    debug2();
    return val2;
}

double Parser::parseExprP(double val) {
    debug1( (__PRETTY_FUNCTION__ + std::string("{")+std::to_string(val)+"}"));
    Token peek = lex.peek();
#ifdef DEBUG_LEVEL2
    currentIndent(); std::cout<<"Peek to next: "<<peek<<"\n";
#endif
    if(in(peek.type, Token::C_PAREN)) {
        debug2();
        return val;
    }
    Token tok = lex.next();
#ifdef DEBUG_LEVEL2
    currentIndent(); std::cout<<"CurrentToken: "<<tok<<"\n";
#endif
    if(tok.type == Token::PLUS) {
        double val2 = parseTerm();
#ifdef DEBUG_LEVEL2
        currentIndent(); std::cout<<"val2 from parseTerm() = "<<val2<<"\n";
#endif
        double val3 = parseExprP(val+val2);
#ifdef DEBUG_LEVEL2
        currentIndent(); std::cout<<"val3 from parseExprP("<<val<<"+"<<val2<<") = "<<val3<<"\n";
#endif
        debug2();
        return  val3;
    }else if(tok.type == Token::MINUS) {
        double val2 = parseTerm();
#ifdef DEBUG_LEVEL2
        currentIndent(); std::cout<<"val2 from parseTerm() = "<<val2<<"\n";
#endif
        double val3 = parseExprP(val-val2);
#ifdef DEBUG_LEVEL2
        currentIndent(); std::cout<<"val3 from parseExprP("<<val<<"-"<<val2<<") = "<<val3<<"\n";
#endif
        debug2();
        return val3;
    }else if(tok.type == Token::M_EOF) {
        debug2();
        return val;
    }
    throw std::runtime_error("IDK1: "+tok.toString());
    return 0;
}

double Parser::parseTerm() {
    debug();
    double val1 = parseFactor();
#ifdef DEBUG_LEVEL2
    currentIndent(); std::cout<<"val1 from parseFactor() = "<<val1<<"\n";
#endif
    double val2 = parseTermP(val1);
#ifdef DEBUG_LEVEL2
    currentIndent(); std::cout<<"val2 from parseTermP("<<val1<<") = "<< val2<<"\n";
#endif
    debug2();
    return val2;
}

double Parser::parseTermP(double val) {
    debug1( (__PRETTY_FUNCTION__ + std::string("{")+std::to_string(val)+"}"));
    Token peek = lex.peek();
#ifdef DEBUG_LEVEL2
    currentIndent(); std::cout<<"Peek to next: "<<peek<<"\n";
#endif
    if(in(peek.type, Token::PLUS, Token::MINUS, Token::C_PAREN)) {
        debug2();
        return val;
    }
    Token tok = lex.next();
#ifdef DEBUG_LEVEL2
    currentIndent(); std::cout<<"CurrentToken: "<<tok<<"\n";
#endif
    if(tok.type == Token::STAR) {
        double val2 = parseFactor();
#ifdef DEBUG_LEVEL2
        currentIndent(); std::cout<<"val2 from parseFactor() = "<<val2<<"\n";
#endif
        double  val3 = parseTermP(val*val2);
#ifdef DEBUG_LEVEL2
        currentIndent(); std::cout<<"val3 from parseExprP("<<val<<"*"<<val2<<") = "<<val3<<"\n";
#endif
        debug2();
        return  val3;
    }else if(tok.type == Token::SLASH) {
        double val2 = parseFactor();
#ifdef DEBUG_LEVEL2
        currentIndent(); std::cout<<"val2 from parseFactor() = "<<val2<<"\n";
#endif
        double  val3 = parseTermP(val/val2);
#ifdef DEBUG_LEVEL2
        currentIndent(); std::cout<<"val3 from parseExprP("<<val<<"/"<<val2<<") = "<<val3<<"\n";
#endif
        debug2();
        return val3;
    }else if(tok.type == Token::M_EOF) {
        debug2();
        return val;
    }
    throw std::runtime_error("IDK2: "+tok.toString());
    return 0;
}

double Parser::parseFactor() {
    debug();
    Token tok = lex.next();
#ifdef DEBUG_LEVEL2
    currentIndent(); std::cout<<"CurrentToken: "<<tok<<"\n";
#endif
    if(tok.type == Token::NUMBER) {
        debug2();
        return tok.value;
    }else if(tok.type == Token::O_PAREN) {
        double  value = parseExpr();
#ifdef DEBUG_LEVEL2
        currentIndent(); std::cout<<"value from parseExpr() = "<<value<<"\n";
#endif
        expect(lex.next(),Token::C_PAREN);
        debug2();
        return value;
    }
    return 0;
}

