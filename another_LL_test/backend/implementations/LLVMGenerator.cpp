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

using TypeDef1 = Value* (IRBuilderBase::*)(Value*, Value*, const Twine&, bool, bool);
using TypeDef2 = Value* (IRBuilderBase::*)(Value*, Value*, const Twine&);
using TypeDef3 = Value* (IRBuilderBase::*)(Value*, Value*, const Twine&, bool );
using TypeDef4 = Value* (IRBuilderBase::*)(Value*, Value*, const Twine&, bool );

llvm::LLVMContext LLVMGenerator::context;
void LLVMGenerator::generate(std::vector<Statement*> program) {
    if (pBuilder)
        delete pBuilder;
    pBuilder = new llvm::IRBuilder<>(context);

    for(Statement* statement: program) {
        if(dynamic_cast<ExprStmt*>(statement) != nullptr){
            auto exprStat = dynamic_cast<ExprStmt*>(statement);
            llvm::Value* val = exprEval(exprStat->expr);
        }else if(dynamic_cast<FunDecl*>(statement) != nullptr) {
            parseFunction(statement);
        }else{
            std::cout<<"something else\n";
            statement->print();
        }

    }
}


Value* LLVMGenerator::getBinaryExprValue(std::string key, Value *left, Value *right) {
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
            {">=",&IRBuilderBase::CreateICmpSGE},{"<=",&IRBuilderBase::CreateICmpSLE},
    };
    static std::unordered_map<std::string, TypeDef3> binary_expr_map3 = {
            {"/",&IRBuilderBase::CreateSDiv}
    };
    static std::unordered_map<std::string, TypeDef4> binary_expr_map4 = {
            {">>", &IRBuilderBase::CreateLShr}
    };
    if(key == "/") {
        return (pBuilder->*binary_expr_map3[key])(left, right,"",0);
    }
    if(key == ">>") {
        return (pBuilder->*binary_expr_map4[key])(left, right,"",0);
    }
    if(binary_expr_map1.contains(key)) {
        return (pBuilder->*binary_expr_map1[key])(left, right,"",0,0);
    }
    if(binary_expr_map2.contains(key)) {
        return (pBuilder->*binary_expr_map2[key])(left, right,"");
    }

    throw std::runtime_error("Unknown operator" + key);

}

llvm::Value *LLVMGenerator::exprEval(Expression *expr, std::unordered_map<std::string, llvm::Argument*> *llvm_args_map) {
    //TODO could have used the visitor pattern here ?
    if( dynamic_cast<ExprBinary*>(expr) != nullptr) {
        auto ex = dynamic_cast<ExprBinary *>(expr);
        auto val_left = exprEval(ex->left);
        auto val_right = exprEval(ex->right);

        Value* result = getBinaryExprValue(ex->tokOperator.lexemme, val_left, val_right);
        return result;


    }else if( dynamic_cast<ExprUnary*>(expr) != nullptr) {

        auto ex = dynamic_cast<ExprUnary *>(expr);
        Value* leftVal = exprEval(ex->right);
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
        if(llvm_args_map == nullptr) {
            throw std::runtime_error("Used identifier but nothing in args map");
        }
        if(!llvm_args_map->contains(varName)) {
            throw std::runtime_error("Argsmap does not contain the variable name: "+varName);
        }
        return (*llvm_args_map)[varName];
    }else {
        expr->print();
        throw std::runtime_error("Unknown expression");
    }
}

 llvm::AllocaInst* LLVMGenerator::parseVarDecl(Statement* stmt) {
    VarStmt* varDecl = dynamic_cast<VarStmt*>(stmt);
    auto IntType = llvm::IntegerType::getInt32Ty(context);
    llvm::AllocaInst* var = pBuilder->CreateAlloca(IntType, nullptr,varDecl->varName.lexemme);
    if(varDecl->initializer != nullptr) {
        pBuilder->CreateStore(exprEval(varDecl->initializer),var);
    }
    return var;

}

void LLVMGenerator::parseReturn(Statement *stmt, std::unordered_map<std::string, llvm::Argument*> *llvm_args_map) {
    ReturnStmt* returnStmt = dynamic_cast<ReturnStmt*>(stmt);

    llvm::Value * val= exprEval(returnStmt->expr, llvm_args_map);
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
    for(Statement* stmt: func->statements) {
        if(dynamic_cast<VarStmt*>(stmt) != nullptr) {
            llvm::AllocaInst* variable = parseVarDecl(stmt);
        } else if(dynamic_cast<ReturnStmt*>(stmt) != nullptr) {
            parseReturn(stmt, &llvm_args_map);
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




