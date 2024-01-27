//
// Created by nicu on 05.01.2024.
//

#ifndef ANOTHER_LL_TEST_ALMOSTOPTIMIZER_H
#define ANOTHER_LL_TEST_ALMOSTOPTIMIZER_H


#include <vector>
#include "../instructions/classes/Instruction.h"

class AlmostOptimizer {
public:
    static std::vector<Instruction> generate(std::vector<Instruction> instructions);
};


#endif //ANOTHER_LL_TEST_ALMOSTOPTIMIZER_H
