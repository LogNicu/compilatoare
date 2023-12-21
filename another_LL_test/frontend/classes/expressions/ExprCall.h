//
// Created by nicu on 20.12.2023.
//

#ifndef ANOTHER_LL_TEST_EXPRCALL_H
#define ANOTHER_LL_TEST_EXPRCALL_H


#include "Expression.h"

class ExprCall: public Expression {
    Expression* funName;
    std::vector<Expression*> arguments;
public:
    ExprCall(Expression* funName, std::vector<Expression*> arguments);
    void print(int level = 0) override;
    ~ExprCall() override;
};


#endif //ANOTHER_LL_TEST_EXPRCALL_H
