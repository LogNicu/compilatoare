//
// Created by nicu on 21.12.2023.
//

#include <iostream>
#include "../classes/Generator.h"
#include "../../frontend/classes/expressions/ExprBinary.h"
#include "../../frontend/classes/expressions/ExprLiteral.h"
#include "../../frontend/classes/expressions/ExprUnary.h"


int Generator::regno = 0;

std::tuple<std::string, int> Generator::generate(Expression* expr) {
    static std::unordered_map<std::string, std::string> binary_expr_map ={
            {"+", "ADDW"},{"-", "SUBW"},{"/", "DIV"},{"*","MUL"},
            {"<<", "SHIFTL"},{">>", "SHIFTR"},
            {"==", "EQ_EQ"},{"!=", "NOT_EQ"},
            {">", "GT"},{"<","LT"},{">=","GT_EQ"},{"<=","LT_EQ"},
            {"&","AND"},{"|","OR"},{"^","XOR"},
            {"&&","LOG_AND"},{"||","LOG_OR"}
    };
    if( dynamic_cast<ExprBinary*>(expr) != nullptr) {
        auto ex = dynamic_cast<ExprBinary *>(expr);
        auto [sub_left,sub_reg_left] = generate(ex->left);
        auto [sub_right, sub_reg_right] = generate(ex->right);
        if (!binary_expr_map.contains(ex->tokOperator.lexemme)) {
            std::cout<<"unknown op";
        }else{
            std::string s = "\t"+binary_expr_map[ex->tokOperator.lexemme]+ " a"+std::to_string(regno++)
                    +" a"+std::to_string(sub_reg_left)
                    +" a"+std::to_string(sub_reg_right)+"\n";
            return {sub_left + sub_right + s, regno-1};
        }

    }else if( dynamic_cast<ExprUnary*>(expr) != nullptr) {
        auto ex = dynamic_cast<ExprUnary *>(expr);
        auto [sub_expr,sub_reg] = generate(ex->right);
        if(ex->tokOperator.lexemme == "!") {
            std::string s = "\tlogic_neg a"+std::to_string(regno++)+" a"+std::to_string(sub_reg)+"\n";
            return {sub_expr+s, regno-1};
        }else if(ex->tokOperator.lexemme == "-") {
            std::string s = "\tnegw a"+std::to_string(regno++)+" a"+std::to_string(sub_reg)+"\n";
            return {sub_expr+s, regno-1};
        }else{
            std::cout<<"Unwnown unary\n";
        }
    }else if( dynamic_cast<ExprLiteral*>(expr) != nullptr) {
        auto ex = dynamic_cast<ExprLiteral *>(expr);
        return {"\tli a"+std::to_string(regno++)+" "+ex->tokLiteral.lexemme+"\n",regno-1};
    }else {
        std::cout<<"Unknown expression";
    }
    throw std::runtime_error("should be unreachable");
}
