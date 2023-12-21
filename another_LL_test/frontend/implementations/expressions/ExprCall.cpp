//
// Created by nicu on 20.12.2023.
//

#include <iostream>
#include "../../classes/expressions/ExprCall.h"

ExprCall::ExprCall(Expression* funName, std::vector<Expression *> arguments) : funName(funName), arguments(arguments){}

void ExprCall::print(int level) {
    const int spaces = 4;
    for(int i = 0; i < level*spaces; i++) {
        std::cout<<' ';
    }
    std::cout<<"function ";
    funName->print(level);
    for (Expression* expr: this->arguments) {
        expr->print(level+1);
    }
}

ExprCall::~ExprCall() {
    for (Expression* expr: this->arguments) {
        delete expr;
    }
}
