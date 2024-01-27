//
// Created by nicu on 21.12.2023.
//

#include <iostream>
#include "../classes/Generator.h"
#include "../../frontend/classes/expressions/ExprBinary.h"
#include "../../frontend/classes/expressions/ExprLiteral.h"
#include "../../frontend/classes/expressions/ExprUnary.h"
#include "../instructions/classes/Instruction.h"


int Generator::regno = 0;
//TODO: is it ok to change it to just int ? i just want the last reg used
std::tuple<std::vector<Instruction>,int> Generator::generate(Expression* expr) {
    static std::vector<Instruction> instructionList;
    static std::unordered_map<std::string, InstructionType> binary_expr_map ={
            //unary negation is not included in the map
            {"+", InstructionType::ADD},{"-", InstructionType::SUB},{"/", InstructionType::DIV},{"*",InstructionType::MUL},
            {"<<", InstructionType::LSL},{">>", InstructionType::ASR},
            {"==", InstructionType::EQ},{"!=", InstructionType::NE},
            {">", InstructionType::GT},{"<",InstructionType::LT},{">=",InstructionType::GT_EQ},{"<=",InstructionType::LT_EQ},
            {"&",InstructionType::AND},{"|",InstructionType::OR},{"^",InstructionType::XOR},
            {"&&",InstructionType::L_AND},{"||",InstructionType::L_OR},
            {"!", InstructionType::L_NEG}
    };

    if( dynamic_cast<ExprBinary*>(expr) != nullptr) {
        auto ex = dynamic_cast<ExprBinary *>(expr);
        auto [vec_discard_me,sub_reg_left] = generate(ex->left);
        auto [vec_discard_me2,sub_reg_right] = generate(ex->right);
        if (!binary_expr_map.contains(ex->tokOperator.lexemme)) {
            std::cout<<"unknown op";
        }else{
            std::vector<Operand> ops = {
                    {OperandType::REG, regno++},
                    {OperandType::REG, sub_reg_left},
                    {OperandType::REG, sub_reg_right}
            };
            InstructionType t = binary_expr_map[ex->tokOperator.lexemme];
            instructionList.emplace_back(t, ops);
            return {instructionList,regno-1};
        }

    }else if( dynamic_cast<ExprUnary*>(expr) != nullptr) {

        auto ex = dynamic_cast<ExprUnary *>(expr);
        auto [vec_discard_me,sub_reg] = generate(ex->right);
        if(ex->tokOperator.lexemme == "!") {
            std::vector<Operand> ops = {
                    {OperandType::REG, regno++},
                    {OperandType::REG, sub_reg}
            };
            InstructionType t = binary_expr_map[ex->tokOperator.lexemme];
            instructionList.emplace_back(t, ops);
            return {instructionList,regno-1};
        }else if(ex->tokOperator.lexemme == "-") {
            std::vector<Operand> ops = {
                    {OperandType::REG, regno++},
                    {OperandType::REG, sub_reg}
            };
            InstructionType t = InstructionType::NEG;
            instructionList.emplace_back(t, ops);
            return {instructionList,regno-1};
        }else{
            std::cout<<"Unwnown unary\n";
        }
    }else if( dynamic_cast<ExprLiteral*>(expr) != nullptr) {
        auto ex = dynamic_cast<ExprLiteral *>(expr);
        std::vector<Operand> ops = {
                {OperandType::REG, regno++},
                {OperandType::IMM, std::stoi(ex->tokLiteral.lexemme)}, //TODO, do something about this
        };
        InstructionType t = InstructionType::LOAD;
        instructionList.emplace_back(t, ops);
        return {instructionList,regno-1};
    }else {
        std::cout<<"Unknown expression";
    }
    throw std::runtime_error("should be unreachable");
}
