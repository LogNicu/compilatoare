#include <iostream>
#include <iomanip>
#include <fstream>
#include "frontend/classes/Parser.h"
#include "backend/classes/Generator.h"
#include "backend/classes/AlmostOptimizer.h"
#include "frontend/classes/statements/ExprStmt.h"
#include "backend/instructions/classes/Instruction.h"
#include "backend/classes/LLVMGenerator.h"
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/Path.h>
#include <llvm/Support/FileSystem.h>
#include <filesystem>
int main(int argc, char *argv[]) {
    if(argc <= 1) {
        std::cerr <<"Expecting an imput file\n";
        return 0;
    }
    std::string fileName = argv[1];
    std::filesystem::path filePath(fileName);
    // Open the file
    std::ifstream file(filePath);
    if (file.is_open()) {
        // Use a stringstream to read the file content into a string
        std::stringstream buffer;
        buffer << file.rdbuf();

        // Close the file
        file.close();

        // Get the content of the file as a string
        std::string fileContent = buffer.str();
        Parser p(fileContent);
        auto program = p.parse();
        std::filesystem::path outFile = filePath;
        outFile.replace_extension("ll");
        llvm::Module* mod = LLVMGenerator(outFile.filename().string()).generate(program);
        std::error_code err;
        llvm::raw_fd_ostream output(mod->getName(), err, llvm::sys::fs::OF_Text);
        mod->print(output, nullptr);
    } else {
        std::cerr << "Unable to open the file: " << filePath.string() << std::endl;
    }

    return 0;
}
