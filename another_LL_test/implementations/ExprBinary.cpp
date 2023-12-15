//
// Created by nicu on 15.12.2023.
//

#include <iostream>
#include "../classes/ExprBinary.h"

ExprBinary::ExprBinary(Token tokOperator, Expression *left, Expression *right) :tokOperator(tokOperator), left(left), right(right) {}

void ExprBinary::print(int level) {
    const int spaces = 4;
    for(int i = 0; i < level*spaces; i++) {
        std::cout<<' ';
    }
    std::cout<<this->tokOperator<<"\n";
    left->print(level+1);
    right->print(level+1);
}

ExprBinary::~ExprBinary() {
    delete left;
    delete right;
}
