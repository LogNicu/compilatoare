//
// Created by nicu on 27.01.2024.
//

#ifndef ANOTHER_LL_TEST_LLVMGENERATOR_H
#define ANOTHER_LL_TEST_LLVMGENERATOR_H


#include <vector>
#include "../../frontend/classes/statements/Statement.h"
#include "../../frontend/classes/expressions/Expression.h"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
class LLVMGenerator {
    llvm::IRBuilder<> *pBuilder = 0;
    llvm::Value* getBinaryExprValue(std::string key, llvm::Value *left, llvm::Value *right);
    llvm::AllocaInst* parseVarDecl(Statement* stmt);
    void parseReturn(Statement* stmt, std::unordered_map<std::string, llvm::Argument*> *llvm_args_map = nullptr);
    static llvm::LLVMContext context;
    llvm::Module* Mod;
public:
    LLVMGenerator();
    llvm::Value* exprEval(Expression* expression,  std::unordered_map<std::string, llvm::Argument*> *llvm_args_map = nullptr);
    llvm::Function* parseFunction(Statement* stmt);
    void generate(std::vector<Statement*> program);

};


#endif //ANOTHER_LL_TEST_LLVMGENERATOR_H
