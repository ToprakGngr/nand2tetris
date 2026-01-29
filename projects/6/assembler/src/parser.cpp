#include <string>
#include <fstream>
#include "parser.h"

void Parser::advance() {
    std::string line;

    while(std::getline(inputFile, line)) {
        
        // 1. Remove comments
        size_t commontPos = line.find("//");
        if(commentPos != std::npos) {
            line = line.substr(0, commentPos);
        }
        
        // 2. Erase all whitespaces within the line
        std::erase_if(line, [](unsigned char c) { return std::isspace(c); });

        if(line.empty()) continue;

        currentCommand = line;
        return;
    }
}

InstructionType Parser::instructionType() {
    if(currentCommand[0] == '@') return A_TYPE;
    if(currentCommand[0] == '(') return L_TYPE;
    else return C_TYPE;
}

void Parser::symbol_extractor() {
        
}
