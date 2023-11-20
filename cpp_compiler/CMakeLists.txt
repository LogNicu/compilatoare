cmake_minimum_required(VERSION 3.22)
project(cpp_compiler)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpp_compiler main.cpp
        implementations/Lexer.cpp
        classes/Lexer.h
        implementations/Parser.cpp
        classes/Parser.h)
