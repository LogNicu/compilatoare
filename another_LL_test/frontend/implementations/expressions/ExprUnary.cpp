//
// Created by nicu on 15.12.2023.
//

#include <iostream>
#include "../../classes/expressions/ExprUnary.h"

ExprUnary::ExprUnary(Token tokOperator, Expression *right) : tokOperator(tokOperator), right(right) {}

void ExprUnary::print(int level) {
    const int spaces = 4;
    for(int i = 0; i < level*spaces; i++) {
        std::cout<<' ';
    }
    std::cout<<this->tokOperator<<"\n";
    right->print(level+1);
}

ExprUnary::~ExprUnary() {
    delete right;
}
