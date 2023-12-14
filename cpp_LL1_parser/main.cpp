#include <iostream>
#include <regex>
#include <unordered_map>
#include "classes/Lexer.h"
#include "classes/Parser.h"


int main() {
    std::string line;

    while(std::getline(std::cin,line)) {
        Parser p(line);
        line+=EOF;
        std::cout<<"Result:\n"<<p.parseExpr()<<"\n\n";

    }
    return 0;
}
