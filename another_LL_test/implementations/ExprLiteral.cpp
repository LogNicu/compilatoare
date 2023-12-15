//
// Created by nicu on 15.12.2023.
//

#include <iostream>
#include "../classes/ExprLiteral.h"

ExprLiteral::ExprLiteral(Token tokLiteral) : tokLiteral(tokLiteral){}

void ExprLiteral::print(int level) {
    const int spaces = 4;
    for(int i = 0; i < level*spaces; i++) {
        std::cout<<' ';
    }
    std::cout<<this->tokLiteral<<"\n";
}
ExprLiteral::~ExprLiteral() {}
