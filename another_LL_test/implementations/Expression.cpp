//
// Created by nicu on 12/4/23.
//

#include <iostream>
#include "../classes/Expression.h"

Expression::Expression(Token tok) : tok(tok) {}

Expression::Expression(Token tok, std::vector<Expression> operands) : tok(tok), operands(operands) {}

void Expression::print(int level = 0) {

    const int spaces = 4;
    for(int i = 0; i < level*spaces; i++) {
        std::cout<<' ';
    }
    std::cout<<this->tok<<"\n";
    for(Expression exp: operands) {
        exp.print(level+1);
    }

}
