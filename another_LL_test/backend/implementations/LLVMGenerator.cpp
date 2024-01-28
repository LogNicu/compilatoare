//
// Created by nicu on 27.01.2024.
//

#include <iostream>
#include <any>
#include "../classes/LLVMGenerator.h"
#include "../../frontend/classes/expressions/ExprBinary.h"
#include "../../frontend/classes/expressions/ExprUnary.h"
#include "../../frontend/classes/expressions/ExprLiteral.h"
#include "../../frontend/classes/statements/ExprStmt.h"
#include "../../frontend/classes/statements/FunDecl.h"
#include "../../frontend/classes/statements/VarStmt.h"
#include "../../frontend/classes/statements/ReturnStmt.h"
#include "../../frontend/classes/expressions/ExprVar.h"

using llvm::IRBuilderBase;
using llvm::Value;
using llvm::Twine;
using llvm::IRBuilder;


llvm::LLVMContext LLVMGenerator::context;

LLVMGenerator::Scope::Scope(std::unordered_map<std::string, llvm::Argument *> *llvm_args_map) : llvm_args_map(llvm_args_map),
                                                            variables(new std::unordered_map<std::string, llvm::Value *>){}

LLVMGenerator::Scope::Scope(std::unordered_map<std::string, llvm::Value *> *variables) :variables(variables),
                                                                                        llvm_args_map(nullptr){}

LLVMGenerator::Scope::Scope(std::unordered_map<std::string, llvm::Argument *> *llvm_args_map,
                            std::unordered_map<std::string, llvm::Value *> *variables): llvm_args_map(llvm_args_map),
                                                                                        variables(variables){}

llvm::Value *LLVMGenerator::Scope::get(std::string key) {
    if(llvm_args_map->contains(key)) {
        return (*llvm_args_map)[key];
    }
    if(variables->contains(key)) {
        return (*variables)[key];
    }
    std::cout<<"========================\n";
    for(auto it: *llvm_args_map) {
        llvm::outs()<<it.first<<" <-> ";it.second->print(llvm::outs());llvm::outs()<<"\n";
    }
    std::cout<<"========================\n";
    for(auto it: *variables) {
        llvm::outs()<<it.first<<" <-> ";it.second->print(llvm::outs());llvm::outs()<<"\n";
    }
    std::cout<<"========================\n";
    std::string error_message = "Couldn't get variable from scope\n";
    error_message += std::string{"llvm_args_map -> "} + (llvm_args_map != nullptr ? "size: "+std::to_string(llvm_args_map->size())+"\n":"is null\n");
    error_message += std::string{"variables -> "} + (variables != nullptr ? "size: "+std::to_string(variables->size())+"\n":"is null\n");
    throw std::runtime_error(error_message);

}

void LLVMGenerator::Scope::put(std::string key, llvm::Value *value) {
    (*variables)[key] = value;
}

void LLVMGenerator::generate(std::vector<Statement*> program) {
    if (pBuilder)
        delete pBuilder;
    pBuilder = new llvm::IRBuilder<>(context);

    for(Statement* statement: program) {
        if(dynamic_cast<ExprStmt*>(statement) != nullptr){
            parseExprStmt(statement, nullptr);
        }else if(dynamic_cast<FunDecl*>(statement) != nullptr) {
            parseFunction(statement);
        }else{
            std::cout<<"something else\n";
            statement->print();
        }

    }
}


Value* LLVMGenerator::getBinaryExprValue(std::string key, Value *left, Value *right) {
    using TypeDef1 = Value* (IRBuilderBase::*)(Value*, Value*, const Twine&, bool, bool);
    using TypeDef2 = Value* (IRBuilderBase::*)(Value*, Value*, const Twine&);
    static std::unordered_map<std::string, TypeDef1> binary_expr_map1 = {
            {"+", &IRBuilderBase::CreateAdd},
            {"-", &IRBuilderBase::CreateSub},
            {"<<",&IRBuilderBase::CreateShl},
            {"*", &IRBuilderBase::CreateMul}
    };

    static std::unordered_map<std::string, TypeDef2> binary_expr_map2 = {
            {"&", &IRBuilderBase::CreateAnd},
            {"|", &IRBuilderBase::CreateOr},
            {"^", &IRBuilderBase::CreateXor},
            {"&&", &IRBuilderBase::CreateLogicalAnd},
            {"||", &IRBuilderBase::CreateLogicalOr},
            {"==", &IRBuilderBase::CreateICmpEQ},{"!=", &IRBuilderBase::CreateICmpNE},
            {">", &IRBuilderBase::CreateICmpSGT},{"<", &IRBuilderBase::CreateICmpSLT},
            {">=",&IRBuilderBase::CreateICmpSGE},{"<=",&IRBuilderBase::CreateICmpSLE}
    };
    if(key == "/") {
        return pBuilder->CreateSDiv(left,right);
    }
    if(key == ">>") {
        return pBuilder->CreateLShr(left,right);
    }
    if(key == "=") {
        pBuilder->CreateStore(right, left);
        return right;
    }
    if(binary_expr_map1.contains(key)) {
        return (pBuilder->*binary_expr_map1[key])(left, right,"",0,0);
    }
    if(binary_expr_map2.contains(key)) {
        return (pBuilder->*binary_expr_map2[key])(left, right,"");
    }

    throw std::runtime_error("Unknown operator" + key);

}

llvm::Value *LLVMGenerator::exprEval(Expression *expr, Scope* scope) {
    //TODO could have used the visitor pattern here ?
    if( dynamic_cast<ExprBinary*>(expr) != nullptr) {
        auto ex = dynamic_cast<ExprBinary *>(expr);
        auto val_left = exprEval(ex->left, scope);
        auto val_right = exprEval(ex->right, scope);

        Value* result = getBinaryExprValue(ex->tokOperator.lexemme, val_left, val_right);
        return result;


    }else if( dynamic_cast<ExprUnary*>(expr) != nullptr) {

        auto ex = dynamic_cast<ExprUnary *>(expr);
        Value* leftVal = exprEval(ex->right, scope);
        if(ex->tokOperator.lexemme == "!") {
            return pBuilder->CreateNot(leftVal);
        }else if(ex->tokOperator.lexemme == "-") {
            return pBuilder->CreateNeg(leftVal);
        }else{
            throw std::runtime_error("Unknown unary");
        }
    }else if( dynamic_cast<ExprLiteral*>(expr) != nullptr) {
        auto ex = dynamic_cast<ExprLiteral *>(expr);
        if(ex->tokLiteral.type == Token::NUMBER) {
            return llvm::ConstantInt::get(llvm::IntegerType::getInt32Ty(context), ex->tokLiteral.value);
        }else{
            throw std::runtime_error("Unknown literal");
        }
    }if(dynamic_cast<ExprVar*>(expr) != nullptr) {
        auto ex = dynamic_cast<ExprVar *>(expr);
        std::string &varName = ex->varName.lexemme;
        return scope->get(varName);
    }else {
        expr->print();
        throw std::runtime_error("Unknown expression");
    }
}

 llvm::AllocaInst* LLVMGenerator::parseVarDecl(Statement* stmt, Scope* scope) {
    VarStmt* varDecl = dynamic_cast<VarStmt*>(stmt);
    auto IntType = llvm::IntegerType::getInt32Ty(context);
    llvm::AllocaInst* var = pBuilder->CreateAlloca(IntType, nullptr,varDecl->varName.lexemme);
    if(varDecl->initializer != nullptr) {
        pBuilder->CreateStore(exprEval(varDecl->initializer, scope),var);
    }
    scope->put(varDecl->varName.lexemme, var);
    return var;

}

void LLVMGenerator::parseReturn(Statement *stmt, Scope* scope) {
    ReturnStmt* returnStmt = dynamic_cast<ReturnStmt*>(stmt);

    llvm::Value * val= exprEval(returnStmt->expr, scope);
    pBuilder->CreateRet(val);

}

llvm::Function *LLVMGenerator::parseFunction(Statement *stmt) {
    FunDecl* func = dynamic_cast<FunDecl*>(stmt);
    std::vector<std::pair<Token,Token>> &arguments = func->params;
    std::string &returnType = func->returnType.lexemme;
    std::unordered_map<std::string, llvm::Argument*> llvm_args_map;
    auto IntType = llvm::IntegerType::getInt32Ty(context);
    std::vector<llvm::Type*> llvmTypeParams;
    for (std::pair<Token, Token> & p: arguments) {
        llvmTypeParams.push_back(IntType);
    }
    llvm::FunctionType* funcType = llvm::FunctionType::get(
            /*Return Type*/ IntType,
            /*Params*/ llvmTypeParams,
            /*isVarArg*/ false);
    llvm::Function* llvmFunction = llvm::Function::Create(funcType, llvm::GlobalValue::ExternalLinkage, func->name.lexemme, Mod);
    llvmFunction->setCallingConv(llvm::CallingConv::C);
    {
        int index = 0;
        for (llvm::Function::arg_iterator args = llvmFunction->arg_begin(); args != llvmFunction->arg_end(); args++) {
            llvm::Argument *m_arg = &(*args);
            llvm_args_map[arguments[index].first.lexemme] = m_arg;
            m_arg->setName(arguments[index].second.lexemme);
            index++;
        }
    }
    llvm::BasicBlock* entry = llvm::BasicBlock::Create(context, "entry", llvmFunction);
    pBuilder->SetInsertPoint(entry);
    Scope scope {&llvm_args_map};
    for(Statement* stmt: func->statements) {
        if(dynamic_cast<VarStmt*>(stmt) != nullptr) {
            llvm::AllocaInst* variable = parseVarDecl(stmt, &scope);
        } else if(dynamic_cast<ReturnStmt*>(stmt) != nullptr) {
            parseReturn(stmt, &scope);
        }else if(dynamic_cast<ExprStmt*>(stmt) != nullptr) {
            parseExprStmt(stmt,&scope);
        }else {
            std::cout<<"other kind of statement\n";
            stmt->print();
        }
    }

    llvmFunction->print(llvm::outs());
    std::cout<<"\n";
    return llvmFunction;
}

LLVMGenerator::LLVMGenerator() {
    Mod = new llvm::Module("f.ll", context);
}

void LLVMGenerator::parseExprStmt(Statement *stmt, Scope *scope) {
    ExprStmt* exp = dynamic_cast<ExprStmt*> (stmt);
    exprEval(exp->expr, scope);
}

