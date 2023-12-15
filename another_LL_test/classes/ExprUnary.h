//
// Created by nicu on 15.12.2023.
//

#ifndef ANOTHER_LL_TEST_EXPRUNARY_H
#define ANOTHER_LL_TEST_EXPRUNARY_H


#include "Expression.h"

class ExprUnary : public  Expression{
    Expression* right;
    Token tokOperator;
public:
    ExprUnary(Token tokOperator, Expression* right);
    void print(int level = 0) override;
    ~ExprUnary() override;
};


#endif //ANOTHER_LL_TEST_EXPRUNARY_H
