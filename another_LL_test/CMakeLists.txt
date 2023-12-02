cmake_minimum_required(VERSION 3.22)
project(another_LL_test)
find_package(FLEX)

set(CMAKE_CXX_STANDARD 20)
#set(MY_CUSTOM_COMMAND flex --header-file=flex_lexer.h lexer.l)
#execute_process(
#        COMMAND ${MY_CUSTOM_COMMAND}
#        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/flex
#        RESULT_VARIABLE CMD_RESULT
#)

#add_custom_target(RunMyCommand
#        COMMAND ${MY_CUSTOM_COMMAND}
#        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/flex
#        COMMENT "Running my custom command"
#)

#if(CMD_RESULT EQUAL 0)
#    message("Custom command executed successfully!")
#else()
#    message(FATAL_ERROR "Custom command failed with result: ${CMD_RESULT}")
#endif()
add_executable(another_LL_test main.cpp
        classes/Token.h
        classes/Lexer.h
        classes/Parser.h
        implementations/Lexer.cpp
        implementations/Parser.cpp
        implementations/Token.cpp
        flex/lexer.l
        flex/flex_lexer.h
        flex/lex.yy.cc
        flex/common_flex.h)

target_link_libraries(another_LL_test ${FLEX_LIBRARIES})