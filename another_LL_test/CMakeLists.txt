cmake_minimum_required(VERSION 3.26)
project(another_LL_test)

set(CMAKE_CXX_STANDARD 20)

add_executable(another_LL_test main.cpp
        classes/Lexer.h
        classes/Parser.h
        implementations/Lexer.cpp
        implementations/Parser.cpp)
