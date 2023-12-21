//
// Created by nicu on 15.12.2023.
//

#ifndef ANOTHER_LL_TEST_EXPRLITERAL_H
#define ANOTHER_LL_TEST_EXPRLITERAL_H


#include "../Token.h"
#include "Expression.h"

class ExprLiteral: public Expression {
    Token tokLiteral;
public:
    ExprLiteral(Token tokOperator);
    void print(int level = 0) override;
    ~ExprLiteral() override;
};


#endif //ANOTHER_LL_TEST_EXPRLITERAL_H
