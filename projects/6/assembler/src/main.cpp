#include <iostream>
#include <iomanip>
#include <string>
#include "parser.h"
#include "code.h"
#include "symboltable.h"
#include <bitset>

int main(int argc, char* argv[]) {
    // if no file is given
    if (argc != 2) {
        std::cerr << "Usage: assembler <InputFile.asm>" << std::endl;
        return 1;
    }

    std::string inputFileName = argv[1];
    std::string outputFileName = inputFileName.substr(0, inputFileName.find_last_of(".")) + ".hack"; 
    
    std::cout << "Assembler is working: " << inputFileName << " -> " << outputFileName << std::endl;

    Parser parser(inputFileName);
    Code code;
    SymbolTable symbolTable;

    // 1. pass to collect the labels
    // so that we can assign them empty ROM spaces
    int romAddress = 0;
    InstructionType insType;

    while(parser.advance()) {
        std::string instruction;
        insType = parser.instructionType();

        if(insType == L_TYPE) {
            instruction = parser.symbol();
            symbolTable.add(instruction, romAddress);
        }
        else {
            romAddress++;
        }
    }
    parser.reset();

    // 2. pass to actual binary conversion
    int ramAddress = 16;

    while (parser.advance()) {
        insType = parser.instructionType();
        std::string instruction;
        std::string output = "";

        // we aready handle this in the 1st pass
        if(insType == L_TYPE) continue;

        if(insType == A_TYPE) {
            instruction = parser.symbol();

            // a symbol cannot start with digit so only check first char
            if(isdigit(instruction[0])) {
                int value = std::stoi(instruction);
                std::string binary = std::bitset<16>(value).to_string();
                output = binary;
            }

            // for the simplicty I do not add complex checks because:
            // the course assumes that the input file will be fine
            else {
                int address;

                if(symbolTable.exists(instruction)){
                    address = symbolTable.retrieve(instruction);
                }
                else {
                    address = ramAddress;
                    symbolTable.add(instruction, address);
                    ramAddress++;
                }
                output = std::bitset<16>().to_string();
            }
        }

        if(insType == C_TYPE) {
            std::string dest = parser.dest();
            std::string comp = parser.comp();
            std::string jump = parser.jump();

            std::string dest_bin = code.dest(dest);
            std::string comp_bin = code.comp(comp);
            std::string jump_bin = code.jump(jump);

            output = "111" + comp_bin + dest_bin + jump_bin;
        }
    }
}
