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
        Parser(std::string filename);

        void advance();
        InstructionType instructionType();
        void symbol_extractor();
        
};


#endif

