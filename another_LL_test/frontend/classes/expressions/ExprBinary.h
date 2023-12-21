//
// Created by nicu on 15.12.2023.
//

#ifndef ANOTHER_LL_TEST_EXPRBINARY_H
#define ANOTHER_LL_TEST_EXPRBINARY_H


#include "Expression.h"

class ExprBinary: public Expression{
    Expression* left;
    Expression* right;
    Token tokOperator;
public:
    ExprBinary(Token tokOperator, Expression* left, Expression* right);
    void print(int level = 0) override;
    ~ExprBinary() override;
};


#endif //ANOTHER_LL_TEST_EXPRBINARY_H
