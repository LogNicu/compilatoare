#include <iostream>
#include <iomanip>
#include <fstream>
#include "frontend/classes/Parser.h"
#include "backend/classes/Generator.h"
#include "frontend/classes/statements/ExprStmt.h"
#include "backend/instructions/classes/Instruction.h"

int main(int argc, char *argv[]) {
    std::string line;
    if(argc > 1) {
        line = std::string (argv[1]);
        Parser p(line);
        p.parse();
        return 0;
    }


    while(std::getline(std::cin,line)) {
        Parser p(line);
        auto* statement = dynamic_cast<ExprStmt *>(p.exprStatement());
        auto regno_discard_me = Generator::generate(statement->expr);
        for(auto inst: Generator::instructionList) {
            std::cout<<"\t"<<InstructionTypeToString(inst.instr)<<" ";
            for (auto op: inst.operands) {
                std::cout<<"["<<OperandTypeToString(op.type)<<"]"<<op.op<<" ";
            }
            std::cout<<"\n";
        }
    }
/*
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

*/
    return 0;
}
