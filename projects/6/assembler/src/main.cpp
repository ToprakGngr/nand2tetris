#include <iostream>
#include <iomanip>
#include <string>
#include "parser.h"
#include "code.h"
#include "symboltable.h"

int main(int argc, char* argv[]) {
    // if no file is given
    if (argc != 2) {
        std::cerr << "Usage: assembler <InputFile.asm>" << std::endl;
        return 1;
    }

    std::string inputFileName = argv[1];
    std::string outputFileName = inputFileName.substr(0, inputFileName.find_last_of(".")) + ".hack"; 
    
    std::cout << "Assembler is working: " << inputFileName << " -> " << outputFileName << std::endl;

    int romAddress = 0;
    Parser parser(inputFileName);
    Code code;
    SymbolTable symbolTable;

    // 1. pass to collect the labels
    while(parser.advance()) {
        
    }

}
