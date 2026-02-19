#include <iostream>
#include <iomanip>
#include <string>
#include "VMparser.h"
#include "codewriter.h"
#include "types.h"
#include <bitset>
#include <fstream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./VMTranslator <source.vm>" << std::endl;
        return 1;
    }

    std::string inputFileName = argv[1];
    std::string outputFileName = inputFileName.substr(0, inputFileName.find_last_of(".")) + ".asm";

    VMParser parser(inputFileName);
    CodeWriter codeWriter(outputFileName);
    InstructionType instructionType;

    std::cout << "Translating: " << inputFileName << " -> " << outputFileName << "..." << std::endl;

    
    while(parser.advance()) {
        std::string instruction;
        instructionType = parser.instructionType();

        if(instructionType == ARITHMETIC_TYPE){
            // such as "add" is  the first argument for the arithmetic ops.
            codeWriter.writeArithmetic(parser.arg1());
        }

        else if(instructionType == POP_TYPE || instructionType == PUSH_TYPE){
            continue;
        }

        std::string arg1 = parser.arg1();
        int arg2 = parser.arg2();
    }


    return 0;
}