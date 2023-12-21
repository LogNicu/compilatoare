//
// Created by nicu on 21.12.2023.
//

#ifndef ANOTHER_LL_TEST_GENERATOR_H
#define ANOTHER_LL_TEST_GENERATOR_H


#include <string>
#include "../../frontend/classes/expressions/Expression.h"

class Generator {
    static int regno;
public:
    static std::tuple<std::string, int> generate(Expression* expr);
};


#endif //ANOTHER_LL_TEST_GENERATOR_H
