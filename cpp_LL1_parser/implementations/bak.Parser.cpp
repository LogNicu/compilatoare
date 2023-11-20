//
// Created by nicu on 11/18/23.
//

#include <stdexcept>
#include <iostream>
#include "../classes/Parser.h"

Parser::Parser(std::string &s) : lex(s){}
static int st_counter = 0;

static inline void debug(std::string s) {
    for(int i = 0; i < st_counter;i++) std::cout<<"  ";
    std::cout<<s<<"\n";
    st_counter++;
}

double Parser::parseExpr() {
    debug("parseExpr()");
    double  v = parseExp1(parseTerm1());
    st_counter--;
    return v;
}

double Parser::parseExp1(double val) {
    debug("parseExp1()");
    double val1;
    Token tok = lex.next();
    if(tok.type == Token::PLUS){
        val1 = parseTerm1();
        double v =  val + parseTerm1();
        st_counter--;
        return v;
    }else if(tok.type == Token::MINUS) {
        val1 = parseTerm1();
        double v = val - parseTerm1();
        st_counter--;
        return v;
    }else if(tok.type == Token::M_EOF){
        st_counter--;
        return 0;
    }else{

    }
    return 0;
}

double Parser::parseTerm1() {
    debug("parseTerm1()");
    int val = parseLow();
    if(lex.peek().type == Token::PLUS || lex.peek().type == Token::MINUS) {
        return val;
    }
    double v = parseTerm2(val);
    st_counter--;
    return v;
}

double Parser::parseTerm2(double val) {
    debug("parseTerm2()");
    double val1;
    Token peek = lex.peek();
    if(peek.type == Token::PLUS || peek.type == Token::MINUS || peek.type == Token::C_PAREN) {
        st_counter--;
        return val;
    }
    Token tok = lex.next();
    if(tok.type == Token::STAR){
        val1 = parseLow();
        double v= val * parseTerm2(val1);
        st_counter--;
        return v;
    }else if(tok.type == Token::SLASH) {
        val1 = parseLow();
        double  v = val / parseTerm2(val1);
        st_counter--;
        return v;
    }else if(tok.type == Token::M_EOF){
        st_counter--;
        return 1;
    }
    throw std::runtime_error("IDK1");
    return 0;
}

double Parser::parseLow() {
    debug("parseLow()");
    Token tok = lex.next();
    if(tok.type == Token::O_PAREN) {
        double val = parseExpr();
        expect(lex.next(), Token::C_PAREN);
        st_counter--;
        return val;
    }else if(tok.type == Token::NUMBER) {
        st_counter--;
        return tok.value;
    }
    throw std::runtime_error("IDK2: "+tok.typeToStr());
}

void Parser::expect(Token t, Token::Type type) {
    if(t.type != type) {
        throw std::runtime_error("Error: Unexpected token");
    }
}
