//
// Created by nicu on 20.12.2023.
//

#ifndef ANOTHER_LL_TEST_EXPRSTMT_H
#define ANOTHER_LL_TEST_EXPRSTMT_H


#include "Statement.h"
#include "../expressions/Expression.h"

class ExprStmt : public Statement{
public:
    Expression* expr;
    ExprStmt(Expression* expr);
    void print(int level = 0) override;
    ~ExprStmt() override;
};


#endif //ANOTHER_LL_TEST_EXPRSTMT_H
