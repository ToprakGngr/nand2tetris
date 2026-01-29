#include <string>
#include <fstream>
#include "parser.h"

void Parser::advance() {
    std::string line;

    while(std::getline(inputFile, line)) {
        
        // 1. Remove comments
        size_t commontPos = line.find("//");
        if(commentPos != std::string::npos) {
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

// A-Type instructions and Labels
std::string Parser::symbol() {
    if(instructionType() == A_TYPE){
        return currentCommand.substr(1);
    }
    if(instructionType() == L_TYPE){
        return currentCommand.substr(1, currentCommand.length() - 2);
    }
}

// destination, D
std::string Parser::dest() { 
    size_t equalPos = currentCommand.find("=");
    if(equalPos != std::strig::npos){
        return currentCommand.substr(0, equalPos);
    }
    return "";
}

// Comp. happens after = OR before ;
std::string Parser::comp() {
    size_t equalPos = currentCommand.find('=');
    size_t semiclnPos = currentCommand.find(';');

    int start = (equalPos == std::strig::npos) ? 0 : equalPOs + 1;
    int end = (semiclnPos == std::string::npos) ? currentCommand.length(): semiclnPos;

    return currentCommand.substr(start, end - start);
}











