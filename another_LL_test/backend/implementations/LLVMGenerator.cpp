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
#include "../../frontend/classes/expressions/ExprCall.h"

using llvm::IRBuilderBase;
using llvm::Value;
using llvm::Twine;
using llvm::IRBuilder;


llvm::LLVMContext LLVMGenerator::context;



LLVMGenerator::Scope::Scope(std::unordered_map<std::string, llvm::Argument *> *llvm_args_map) : llvm_args_map(llvm_args_map),
                                                            variables(new std::unordered_map<std::string, llvm::Value *>),
                                                            stores(new std::unordered_map<std::string, llvm::Value *>){}

LLVMGenerator::Scope::Scope() : variables(new std::unordered_map<std::string, llvm::Value *>),
                                stores(new std::unordered_map<std::string, llvm::Value *>){}
LLVMGenerator::Scope::Scope(std::unordered_map<std::string, llvm::Value *> *variables) :variables(variables),
                                                                                        stores(new std::unordered_map<std::string, llvm::Value *>),
                                                                                        llvm_args_map(nullptr){}

LLVMGenerator::Scope::Scope(std::unordered_map<std::string, llvm::Argument *> *llvm_args_map,
                            std::unordered_map<std::string, llvm::Value *> *variables): llvm_args_map(llvm_args_map),
                                                                                        variables(variables){}

std::pair<llvm::Value*, LLVMGenerator::ParamType> LLVMGenerator::Scope::get(std::string key) {
    if(llvm_args_map->contains(key)) {
        return {(*llvm_args_map)[key], ParamType::m_funArg};
    }
    if(stores->contains(key)) {
        return {(*stores)[key], ParamType::m_Store};
    }
    if(variables->contains(key)) {
        return {(*variables)[key], ParamType::m_AllocaInst};
    }
    std::string error_message = "Couldn't get variable from scope\n";
    error_message += std::string{"llvm_args_map -> "} + (llvm_args_map != nullptr ? "size: "+std::to_string(llvm_args_map->size())+"\n":"is null\n");
    error_message += std::string{"variables -> "} + (variables != nullptr ? "size: "+std::to_string(variables->size())+"\n":"is null\n");
    throw std::runtime_error(error_message);

}

void LLVMGenerator::Scope::put(std::string key, llvm::Value *value, ParamType type) {
    if (type == ParamType::m_Store) {
        (*stores)[key] = value;
    }else if(type == ParamType::m_AllocaInst) {
        (*variables)[key] = value;
    }else if(type == ParamType::m_funArg) {
        std::cout<<"DEBUG ERROR\n";
    }

}

llvm::Module* LLVMGenerator::generate(std::vector<Statement*> program) {
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
    return Mod;
}


std::pair<llvm::Value*, LLVMGenerator::ParamType> LLVMGenerator::getBinaryExprValue(std::string key, Value *left, ParamType lType, Value *right, ParamType rType) {
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


    using llvm::LoadInst;
    using llvm::Align;
    using llvm::AllocaInst;
    auto IntType = llvm::IntegerType::getInt32Ty(context);
    if(key == "=") {
//        AllocaInst *intPtr = pBuilder->CreateAlloca(IntType, nullptr, "intPtr");
//        if(rType == ParamType::m_AllocaInst) {
//            AllocaInst* x = pBuilder->CreateAlloca(IntType, nullptr, "temp");
//            pBuilder->CreateStore(right, x);
//            LoadInst* right1 = pBuilder->CreateLoad(IntType, x, false, right->getName());
//            right1->setAlignment(Align(4));
//            right = right1;
//        }
        pBuilder->CreateStore(right, left);
        return {right, ParamType::m_AllocaInst};
    }


    if(lType == ParamType::m_AllocaInst) {
        LoadInst* left1 = pBuilder->CreateLoad(IntType, left, false, left->getName());
        left1->setAlignment(Align(4));
        left = left1;
    }
    if(rType == ParamType::m_AllocaInst) {
        LoadInst* right1 = pBuilder->CreateLoad(IntType, right, false, right->getName());
        right1->setAlignment(Align(4));
        right = right1;
    }

    if(key == "/") {
        return {pBuilder->CreateSDiv(left,right), ParamType::OTHER};
    }

    if(key == ">>") {
        return {pBuilder->CreateLShr(left,right), ParamType::OTHER};
    }
    if(binary_expr_map1.contains(key)) {
        return {(pBuilder->*binary_expr_map1[key])(left, right,"",0,0), ParamType::OTHER};
    }
    if(binary_expr_map2.contains(key)) {
        return {(pBuilder->*binary_expr_map2[key])(left, right,""), ParamType::OTHER};
    }

    throw std::runtime_error("Unknown operator" + key);

}

std::pair<llvm::Value*, LLVMGenerator::ParamType> LLVMGenerator::exprEval(Expression *expr, Scope* scope) {
    //TODO could have used the visitor pattern here ?
    if( dynamic_cast<ExprBinary*>(expr) != nullptr) {
        auto ex = dynamic_cast<ExprBinary *>(expr);
        auto val_left = exprEval(ex->left, scope);
        auto val_right = exprEval(ex->right, scope);

        auto result = getBinaryExprValue(ex->tokOperator.lexemme, val_left.first, val_left.second, val_right.first, val_right.second);
        return result;


    }else if( dynamic_cast<ExprUnary*>(expr) != nullptr) {

        auto ex = dynamic_cast<ExprUnary *>(expr);
        auto leftVal = exprEval(ex->right, scope);
        if(ex->tokOperator.lexemme == "!") {
            return {pBuilder->CreateNot(leftVal.first), ParamType::OTHER};
        }else if(ex->tokOperator.lexemme == "-") {
            return {pBuilder->CreateNeg(leftVal.first),ParamType::OTHER};
        }else{
            throw std::runtime_error("Unknown unary");
        }
    }else if( dynamic_cast<ExprLiteral*>(expr) != nullptr) {
        auto ex = dynamic_cast<ExprLiteral *>(expr);
        if(ex->tokLiteral.type == Token::NUMBER) {
            return {llvm::ConstantInt::get(llvm::IntegerType::getInt32Ty(context), ex->tokLiteral.value), ParamType::m_literal};
        }else{
            throw std::runtime_error("Unknown literal");
        }
    }else if(dynamic_cast<ExprVar*>(expr) != nullptr) {
        auto ex = dynamic_cast<ExprVar *>(expr);
        std::string &varName = ex->varName.lexemme;
        return scope->get(varName);
    }else if(dynamic_cast<ExprCall*>(expr) != nullptr){
        auto ex = dynamic_cast<ExprCall*>(expr);
        auto functionName = dynamic_cast<ExprVar*>(ex->funName);
        if(!globalScope.contains(functionName->varName.lexemme)) {
            throw std::runtime_error("Function doesn't exist\n");
        }
        auto func =  globalScope[functionName->varName.lexemme];
        std::vector<Value*> arguments;
        for (auto arg: ex->arguments) {
            auto arg1 = exprEval(arg, scope);
            if(arg1.second == ParamType::m_AllocaInst) {
                auto IntType = llvm::IntegerType::getInt32Ty(context);
                ExprVar* exp1 = dynamic_cast<ExprVar*>(arg);
                if(exp1 == nullptr) {std::cerr<<"expression should have been cast\n";}
                auto left = scope->get(exp1->varName.lexemme).first;
                llvm::LoadInst* left1 = pBuilder->CreateLoad(IntType, left, false, left->getName());
                left1->setAlignment(llvm::Align(4));
                arguments.push_back(left1);

            }else{
                arguments.push_back(arg1.first);
            }

        }
        auto callInst = pBuilder->CreateCall(func, arguments);
        return {callInst, ParamType::OTHER};
    }else {
        expr->print();
        throw std::runtime_error("Unknown expression");
    }
}

void LLVMGenerator::parseVarDecl(Statement* stmt, Scope* scope) {
    VarStmt* varDecl = dynamic_cast<VarStmt*>(stmt);
    auto IntType = llvm::IntegerType::getInt32Ty(context);
    llvm::AllocaInst* var = pBuilder->CreateAlloca(IntType, nullptr,varDecl->varName.lexemme);
    if(varDecl->initializer != nullptr) {
        auto storeInst = pBuilder->CreateStore(exprEval(varDecl->initializer, scope).first, var);
        scope->put(varDecl->varName.lexemme, storeInst, ParamType::m_Store);
    }else{
        scope->put(varDecl->varName.lexemme, var, ParamType::m_AllocaInst);
    }
    if(varDecl->others.size() > 0) {
        for(std::pair<Token, Expression*> v1 : varDecl->others) {
            llvm::AllocaInst* var1 = pBuilder->CreateAlloca(IntType, nullptr,v1.first.lexemme);
            if(v1.second != nullptr) {
                auto storeInst = pBuilder->CreateStore(exprEval(v1.second, scope).first, var1);
                scope->put(v1.first.lexemme, storeInst, ParamType::m_Store);
            }else{
                scope->put(v1.first.lexemme, var1, ParamType::m_AllocaInst);
            }

        }
    }


}

void LLVMGenerator::parseReturn(Statement *stmt, Scope* scope) {
    ReturnStmt* returnStmt = dynamic_cast<ReturnStmt*>(stmt);

    llvm::Value * val= exprEval(returnStmt->expr, scope).first;
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
    if(globalScope.contains(func->name.lexemme)) {
        throw std::runtime_error("Function already exists\n");
    }
    globalScope[func->name.lexemme]= llvmFunction;
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
            parseVarDecl(stmt, &scope);
        } else if(dynamic_cast<ReturnStmt*>(stmt) != nullptr) {
            parseReturn(stmt, &scope);
        }else if(dynamic_cast<ExprStmt*>(stmt) != nullptr) {
            parseExprStmt(stmt,&scope);
        }else {
            std::cout<<"other kind of statement\n";
            stmt->print();
        }
    }

    return llvmFunction;
}

LLVMGenerator::LLVMGenerator(std::string srcFile) {
    Mod = new llvm::Module(srcFile, context);
    Mod->setDataLayout("e-m:e-i64:64-f80:128-n8:16:32:64-S128");
    Mod->setTargetTriple("x86_64-pc-linux-gnu");
}

void LLVMGenerator::parseExprStmt(Statement *stmt, Scope *scope) {
    ExprStmt* exp = dynamic_cast<ExprStmt*> (stmt);
    exprEval(exp->expr, scope);
}

LLVMGenerator::~LLVMGenerator() {
//    Mod->print(llvm::outs(), nullptr);
}

