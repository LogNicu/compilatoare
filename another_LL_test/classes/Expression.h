//
// Created by nicu on 12/4/23.
//

#ifndef ANOTHER_LL_TEST_EXPRESSION_H
#define ANOTHER_LL_TEST_EXPRESSION_H


#include <vector>
#include "Token.h"

class Expression {
public:
    virtual void print(int level = 0) = 0;
    virtual ~Expression() {};
};


#endif //ANOTHER_LL_TEST_EXPRESSION_H
