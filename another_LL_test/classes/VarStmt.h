//
// Created by nicu on 20.12.2023.
//

#ifndef ANOTHER_LL_TEST_VARSTMT_H
#define ANOTHER_LL_TEST_VARSTMT_H


#include "Statement.h"
#include "Expression.h"

class VarStmt : public Statement{
    Token varName;
    Token varType;
    Expression* initializer;
public:
    VarStmt(Token varName, Token varType, Expression* initializer);
    void print(int level = 0) override;
    ~VarStmt() override;

};


#endif //ANOTHER_LL_TEST_VARSTMT_H
