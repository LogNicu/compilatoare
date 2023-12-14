#include <iostream>
#include <iomanip>
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
    //TODO explore what happens when you pass unknown Tokens
    //such as tokens that have been defined in lexer but have no rule in the parser
    // a good candidate would be LOGIC_AND (in this version)
//    line = "(((540+608)+(!974-!811))*((!703+626)+(140*80)))";
    while(std::getline(std::cin,line)) {
        Parser p(line);
        p.parseExpr().print(0);
    }
    return 0;
}
