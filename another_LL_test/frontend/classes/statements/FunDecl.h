//
// Created by nicu on 25.12.2023.
//

#ifndef ANOTHER_LL_TEST_FUNDECL_H
#define ANOTHER_LL_TEST_FUNDECL_H


#include <vector>
#include "Statement.h"
#include "../Token.h"

class FunDecl : public Statement {
public:
    Token name;
    Token returnType;
    std::vector<std::pair<Token,Token>> params;
    std::vector<Statement*> statements;
    FunDecl(Token name, Token returnType, std::vector<std::pair<Token,Token>> params, std::vector<Statement*> statements);
    void print(int level = 0) override;
    ~FunDecl() override;
};


#endif //ANOTHER_LL_TEST_FUNDECL_H
