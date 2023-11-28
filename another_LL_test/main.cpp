#include <iostream>
#include <regex>
#include <unordered_map>
#include <iomanip>
#include "classes/Lexer.h"
#include "classes/Parser.h"


int main(int argc, char *argv[]) {
    std::string line;
    if(argc > 1) {
        line = std::string (argv[1]);
        Parser p(line);
        std::cout << std::fixed << std::setprecision(5) << p.parseExpr() << "\n";
        return 0;
    }


    while(std::getline(std::cin,line)) {
        Parser p(line);
        line+=EOF;
        std::cout << p.parseExpr() << "\n";

    }
    return 0;
}
