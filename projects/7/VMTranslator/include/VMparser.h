#ifndef VMPARSER_H
#define VMPARSER_H

#include <fstream>
#include <string>
#include <vector>

enum InstructionType {
    PUSH_TYPE,
    POP_TYPE,
    ARITHMETIC_TYPE
};

class VMParser {
    private:
        std::ifstream inputFile;
        std::string currentCommand;
        std::vector<std::string> args;
    public:
        VMParser(const std::string& filename);
        InstructionType instructionType();
        
        bool hasMoreLines();
        bool advance();
        void reset();

        std::string arg1();
        int arg2();
};

#endif