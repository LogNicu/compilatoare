//
// Created by nicu on 20.12.2023.
//

#include "../classes/ExprStmt.h"

ExprStmt::ExprStmt(Expression *expr) : expr(expr) {}

void ExprStmt::print(int level) {
    this->expr->print();
}

ExprStmt::~ExprStmt() {
    delete this->expr;
}
