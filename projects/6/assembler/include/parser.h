#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>

enum InstructionType {
    A_TYPE, 
    L_TYPE, 
    C_TYPE
};

class Parser {
    private:
        std::ifstream inputFile;
        std::string currentCommand;

    public:
        Parser(const std::string& filename);

        bool advance();
        InstructionType instructionType();
        bool hasMoreLines();
        std::string symbol();
        std::string dest();
        std::string comp();
        std::string jump();
        
};


#endif

