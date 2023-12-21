//
// Created by nicu on 20.12.2023.
//

#include <iostream>
#include "../../classes/expressions/ExprVar.h"

ExprVar::ExprVar(Token varName) : varName(varName){}

void ExprVar::print(int level) {
    const int spaces = 4;
    for(int i = 0; i < level*spaces; i++) {
        std::cout<<' ';
    }
    std::cout<<this->varName<<"\n";
}

ExprVar::~ExprVar() {

}
