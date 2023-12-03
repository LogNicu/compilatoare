cmake_minimum_required(VERSION 3.22)
project(another_LL_test)
find_package(FLEX REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_custom_command(
        OUTPUT lex.yy.cc
        COMMAND flex
        ARGS -o ${CMAKE_CURRENT_SOURCE_DIR}/flex/lex.yy.cc
        --header-file=${CMAKE_CURRENT_SOURCE_DIR}/flex/flex_lexer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/flex/lexer.lex
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/flex/lexer.lex
        COMMENT "Generating lexer.c"
        VERBATIM
)
add_custom_target(lexer_target DEPENDS lex.yy.cc)

add_executable(another_LL_test main.cpp
        classes/Token.h
        classes/Lexer.h
        classes/Parser.h
        implementations/Lexer.cpp
        implementations/Parser.cpp
        implementations/Token.cpp
        flex/lexer.lex
        flex/flex_lexer.h
        flex/lex.yy.cc
        flex/common_flex.h)

add_dependencies(another_LL_test lexer_target)