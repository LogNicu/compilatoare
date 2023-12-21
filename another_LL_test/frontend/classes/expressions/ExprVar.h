//
// Created by nicu on 20.12.2023.
//

#ifndef ANOTHER_LL_TEST_EXPRVAR_H
#define ANOTHER_LL_TEST_EXPRVAR_H


#include "Expression.h"

class ExprVar: public Expression{
    Token varName;
public:
    ExprVar(Token varName);
    void print(int level = 0) override;
    ~ExprVar() override;
};


#endif //ANOTHER_LL_TEST_EXPRVAR_H
