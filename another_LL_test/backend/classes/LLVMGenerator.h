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

    enum class ParamType{
        m_AllocaInst,
        m_funArg,
        m_literal,
        m_Store,
        OTHER
    };

    struct Scope {
        std::unordered_map<std::string, llvm::Argument*> *llvm_args_map;
        std::unordered_map<std::string, llvm::Value*> *variables;
        std::unordered_map<std::string, llvm::Value*> *stores;
        Scope(std::unordered_map<std::string, llvm::Argument*> *llvm_args_map);
        Scope();
        Scope(std::unordered_map<std::string, llvm::Value*> *ariables);
        Scope(std::unordered_map<std::string, llvm::Argument*> *llvm_args_map,
              std::unordered_map<std::string, llvm::Value*> *variables);
        std::pair<llvm::Value*, ParamType> get(std::string key);
        void put(std::string key, llvm::Value* value, ParamType type);
    };
    std::unordered_map<std::string, llvm::Function*> globalScope;
    llvm::IRBuilder<> *pBuilder = 0;
    std::pair<llvm::Value*, LLVMGenerator::ParamType> getBinaryExprValue(std::string key, llvm::Value *left,
                                                                         ParamType lType, llvm::Value *right, ParamType rType);
    void parseVarDecl(Statement* stmt, Scope* scope);
    void parseReturn(Statement* stmt, Scope* scope);
    void parseExprStmt(Statement* stmt, Scope* scope = nullptr);
    static llvm::LLVMContext context;
    llvm::Module* Mod;
public:
    LLVMGenerator(std::string srcFile);
    ~LLVMGenerator();
    std::pair<llvm::Value*, LLVMGenerator::ParamType> exprEval(Expression* expression, Scope* scope);
    llvm::Function* parseFunction(Statement* stmt);
    llvm::Module* generate(std::vector<Statement*> program);

};


#endif //ANOTHER_LL_TEST_LLVMGENERATOR_H
