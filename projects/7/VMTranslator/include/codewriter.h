#ifndef CODEWRITER_H
#define CODEWRITER_H

#include <fstream>
#include "types.h"

class CodeWriter {
    private:
        std::ofstream outputFile;
    public:
        CodeWriter(const std::string& filename);
        void writeArithmetic(const std::string command);
        void writePushPop(InstructionType command, const std::string& segment, int index);
};


#endif