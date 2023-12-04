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
//        std::cout << std::fixed << std::setprecision(5) << p.parseExpr() << "\n";
        p.parseExpr().print(0);
        return 0;
    }

//    line = "(((540+608)+(!974-!811))*((!703+626)+(140*80)))";
    while(std::getline(std::cin,line)) {
        Parser p(line);
        p.parseExpr().print(0);
    }
    return 0;
}
