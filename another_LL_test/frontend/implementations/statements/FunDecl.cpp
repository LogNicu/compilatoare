//
// Created by nicu on 25.12.2023.
//

#include <iostream>
#include "../../classes/statements/FunDecl.h"

FunDecl::FunDecl(Token name, Token returnType, std::vector<std::pair<Token, Token>> params, std::vector<Statement *> statements) :
        name(name), returnType(returnType), params(params), statements(statements){}

void FunDecl::print(int level) {
    std::cout<<"fun declaration: "<<name.lexemme<<"(";
    for (auto &p : params){
        std::cout<<p.first<<": "<<p.second<<", ";
    }
    std::cout<<") -> ";std::cout<<returnType.lexemme<<"{\n";
    for(auto stmt: statements) {
        stmt->print(level+1);
    }
    std::cout<<"}\n";

}

FunDecl::~FunDecl() {
    for(auto stmt: statements) {
        delete stmt;
    }
}
