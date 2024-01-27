//
// Created by nicu on 05.01.2024.
//

#include <iostream>
#include "../classes/AlmostOptimizer.h"


std::vector<Instruction> AlmostOptimizer::generate(std::vector<Instruction> instructions) {
    for( int i = 0; i < instructions.size(); i++) {
        Instruction& instr = instructions[i];
        if (instr.instr == InstructionType::LOAD && instr.operands[1].type == OperandType::IMM) {

            int targetReg = instr.operands[0].op;
            int targetVal = instr.operands[1].op;
            std::cout<<"Found a load: [REG]"<<targetReg<<" -> "<<targetVal<<"\n";
            for (int j  = i+1; j < instructions.size(); j++) {
                Instruction& nextInstr = instructions[j];
                std::cout << "\033[96m";
                std::cout<<""<<InstructionTypeToString(nextInstr.instr)<<" ";
                for (auto op: nextInstr.operands) {
                    std::cout<<"["<<OperandTypeToString(op.type)<<"]"<<op.op<<" ";
                }
                for(Operand& op : nextInstr.operands) {
                    if(op.type == OperandType::REG ) {
                        if(op.op == targetReg) {
                            op.type = OperandType::IMM;
                            op.op = targetVal;
                        }else{
                            op.op -= 1;
                        }
                    }
                }
                std::cout<<"\033[0m -> \033[93m"<<InstructionTypeToString(nextInstr.instr)<<" ";
                for (auto op: nextInstr.operands) {
                    std::cout<<"["<<OperandTypeToString(op.type)<<"]"<<op.op<<" ";
                }
                std::cout<<"\n";
                std::cout<<"\033[0m";
            }
            instructions.erase(instructions.begin() + i);
            std::cout<<"-------------------------\n";
        }
    }
    return instructions;
}
