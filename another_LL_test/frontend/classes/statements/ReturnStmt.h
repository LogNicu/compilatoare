//
// Created by nicu on 27.01.2024.
//

#ifndef ANOTHER_LL_TEST_RETURNSTMT_H
#define ANOTHER_LL_TEST_RETURNSTMT_H


#include "Statement.h"
#include "../expressions/Expression.h"

class ReturnStmt : public Statement {
public:
    Expression* expr;
    ReturnStmt(Expression* expr);
    void print(int level = 0) override;
    ~ReturnStmt() override;
};


#endif //ANOTHER_LL_TEST_RETURNSTMT_H
