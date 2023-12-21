#include <iostream>
#include <iomanip>
#include <fstream>
#include "frontend/classes/Parser.h"


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

//    while(std::getline(std::cin,line)) {
//        Parser p(line);
//        p.parse();
//    }
    std::string filepath = "/home/nicu/Projects/compilatoare/another_LL_test/code.rs";

    // Open the file
    std::ifstream file(filepath);

    // Check if the file is open
    if (file.is_open()) {
        // Use a stringstream to read the file content into a string
        std::stringstream buffer;
        buffer << file.rdbuf();

        // Close the file
        file.close();

        // Get the content of the file as a string
        std::string fileContent = buffer.str();
        Parser p(fileContent);
        p.parse();
    } else {
        std::cerr << "Unable to open the file: " << filepath << std::endl;
    }

    return 0;
}
