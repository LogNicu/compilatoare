//
// Created by nicu on 20.12.2023.
//

#include <iostream>
#include "../../classes/statements/VarStmt.h"

VarStmt::VarStmt(Token varName, Token varType, Expression *initializer) : varName(varName), varType(varType), initializer(initializer)  {}


void VarStmt::print(int level) {

    std::cout<<varName.lexemme<<" of type "<< varType.lexemme<<" -> Has expression:\n";
    initializer->print(level+1);
}

VarStmt::~VarStmt() {
    delete initializer;
}
