cmake_minimum_required(VERSION 3.22)
project(another_LL_test)
find_package(FLEX REQUIRED)
find_package(LLVM REQUIRED CONFIG)
set(CMAKE_CXX_STANDARD 20)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_custom_command(
        OUTPUT lex.yy.cc
        COMMAND flex
        ARGS -o ${CMAKE_CURRENT_SOURCE_DIR}/frontend/flex_dir/lex.yy.cc
        --header-file=${CMAKE_CURRENT_SOURCE_DIR}/frontend/flex_dir/flex_lexer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/frontend/flex_dir/lexer.lex
        DEPENDS frontend/flex_dir/lexer.lex
        COMMENT "Generating lexer.c"
        VERBATIM
)
add_custom_target(lexer_target DEPENDS lex.yy.cc)

add_executable(another_LL_test main.cpp
        frontend/classes/Token.h
        frontend/classes/Lexer.h
        frontend/classes/Parser.h
        frontend/implementations/Lexer.cpp
        frontend/implementations/Parser.cpp
        frontend/implementations/Token.cpp
        frontend/flex_dir/lexer.lex
        frontend/flex_dir/flex_lexer.h
        frontend/flex_dir/lex.yy.cc
        frontend/flex_dir/common_flex.h
        frontend/classes/expressions/Expression.h
        frontend/implementations/expressions/ExprBinary.cpp
        frontend/classes/expressions/ExprBinary.h
        frontend/implementations/expressions/ExprUnary.cpp
        frontend/classes/expressions/ExprUnary.h
        frontend/implementations/expressions/ExprLiteral.cpp
        frontend/classes/expressions/ExprLiteral.h
        frontend/implementations/statements/Statement.cpp
        frontend/classes/statements/Statement.h
        frontend/implementations/statements/VarStmt.cpp
        frontend/classes/statements/VarStmt.h
        frontend/implementations/statements/ExprStmt.cpp
        frontend/classes/statements/ExprStmt.h
        frontend/implementations/expressions/ExprCall.cpp
        frontend/classes/expressions/ExprCall.h
        frontend/implementations/expressions/ExprVar.cpp
        frontend/classes/expressions/ExprVar.h
        backend/implementations/Generator.cpp
        backend/classes/Generator.h
        frontend/implementations/statements/FunDecl.cpp
        frontend/classes/statements/FunDecl.h
        backend/instructions/implementations/Instruction.cpp
        backend/instructions/classes/Instruction.h
        backend/implementations/AlmostOptimizer.cpp
        backend/classes/AlmostOptimizer.h
        frontend/implementations/statements/ReturnStmt.cpp
        frontend/classes/statements/ReturnStmt.h
        backend/implementations/LLVMGenerator.cpp
        backend/classes/LLVMGenerator.h)

add_dependencies(another_LL_test lexer_target)

target_link_libraries(another_LL_test LLVM)
