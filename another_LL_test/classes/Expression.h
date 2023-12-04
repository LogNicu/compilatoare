//
// Created by nicu on 12/4/23.
//

#ifndef ANOTHER_LL_TEST_EXPRESSION_H
#define ANOTHER_LL_TEST_EXPRESSION_H


#include <vector>
#include "Token.h"

class Expression {
    Token tok;
    std::vector<Expression> operands;
public:
    Expression(Token tok);
    Expression(Token tok, std::vector<Expression> operands);
    void print(int level);
};


#endif //ANOTHER_LL_TEST_EXPRESSION_H
