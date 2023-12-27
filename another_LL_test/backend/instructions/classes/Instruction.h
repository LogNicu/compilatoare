//
// Created by nicu on 27.12.2023.
//

#ifndef ANOTHER_LL_TEST_INSTRUCTION_H
#define ANOTHER_LL_TEST_INSTRUCTION_H


#include <vector>
#include "../../../frontend/classes/Token.h"

enum class OperandType {
    IMM, REG
};

#define ENUM_CLASS_TO_STRING(enumType, ...) \
    inline const std::unordered_map<enumType, std::string>& enumType##ToStringMap() { \
        static const std::unordered_map<enumType, std::string> mapping = { __VA_ARGS__ }; \
        return mapping; \
    } \
    inline std::string enumType##ToString(enumType value) { \
        const auto& map = enumType##ToStringMap(); \
        auto it = map.find(value); \
        return (it != map.end()) ? it->second : "Unknown"; \
    }

class Operand {
public:
    const OperandType type;
    const std::string op;
    Operand(const OperandType type, const std::string op);
};
enum class InstructionType {
    LOAD, MOVE,
    ADD, SUB,
    MUL, DIV,
    LSL, LSR, //logical shift left and right
    ASR, //arithmetic shift right
    NE, EQ, // !=, ==
    GT_EQ, LT_EQ, // >=, <=
    GT, LT, // >, <,
    AND, OR, XOR, // &, |, ^
    L_AND, L_OR, // &&, ||
    NEG, // -
    L_NEG// !
};

class Instruction {
public:
    const InstructionType instr;
    const std::vector<Operand> operands;
    Instruction(const InstructionType instr, const std::vector<Operand> operands);
};

ENUM_CLASS_TO_STRING(OperandType,
                        {OperandType::IMM,"IMM"},
                        {OperandType::REG,"REG"}
)

ENUM_CLASS_TO_STRING(InstructionType,
                     {InstructionType::LOAD, "LOAD"},
                     {InstructionType::MOVE, "MOVE"},
                     {InstructionType::ADD, "ADD"},
                     {InstructionType::SUB, "SUB"},
                     {InstructionType::MUL, "MUL"},
                     {InstructionType::DIV, "DIV"},
                     {InstructionType::LSL, "LSL"},
                     {InstructionType::LSR, "LSR"},
                     {InstructionType::ASR, "ASR"},
                     {InstructionType::NE, "NE"},
                     {InstructionType::EQ, "EQ"},
                     {InstructionType::GT_EQ, "GT_EQ"},
                     {InstructionType::LT_EQ, "LT_EQ"},
                     {InstructionType::GT, "GT"},
                     {InstructionType::LT, "LT"},
                     {InstructionType::AND, "AND"},
                     {InstructionType::OR, "OR"},
                     {InstructionType::XOR, "XOR"},
                     {InstructionType::L_AND, "L_AND"},
                     {InstructionType::L_OR, "L_OR"},
                     {InstructionType::NEG, "NEG"},
                     {InstructionType::L_NEG, "L_NEG"}
)

#endif //ANOTHER_LL_TEST_INSTRUCTION_H
