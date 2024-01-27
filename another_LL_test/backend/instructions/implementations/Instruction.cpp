//
// Created by nicu on 27.12.2023.
//

#include "../classes/Instruction.h"

Operand::Operand(const OperandType type, const int op) : type(type), op(op) {}

Instruction::Instruction(const InstructionType instr, const std::vector<Operand> operands) : instr(instr), operands(operands){}
