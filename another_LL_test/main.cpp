#include <iostream>
#include <iomanip>
#include "classes/Parser.h"


int main(int argc, char *argv[]) {
    std::string line;
    if(argc > 1) {
        line = std::string (argv[1]);
        Parser p(line);
        Expression *exp = p.parseExpr();
        exp->print();
        delete exp;
        return 0;
    }
    while(std::getline(std::cin,line)) {
        Parser p(line);
        Expression *exp = p.parseExpr();
        exp->print();
        delete exp;
    }
    return 0;
}
