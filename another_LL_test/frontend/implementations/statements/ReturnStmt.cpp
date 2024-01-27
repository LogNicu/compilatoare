//
// Created by nicu on 27.01.2024.
//

#include <iostream>
#include "../../classes/statements/ReturnStmt.h"

void ReturnStmt::print(int level) {
    const int spaces = 4;
    for(int i = 0; i < level*spaces; i++) {
        std::cout<<' ';
    }
    std::cout<<"RETURN: ";
    this->expr->print(level);
}

ReturnStmt::ReturnStmt(Expression *expr) : expr(expr) {}

ReturnStmt::~ReturnStmt() {
    delete expr;
}
