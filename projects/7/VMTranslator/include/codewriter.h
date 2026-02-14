#ifndef CODEWRITER_H
#define CODEWRITER_H

#include <fstream>
#include <unordered_map>
#include <string>
#include "types.h"

class CodeWriter {
    private:
        std::string currentFileName;
        std::ofstream outputFile;
        std::unordered_map<std::string, std::string> segmentTable;
    public:
        CodeWriter(const std::string& filename);
        void writeArithmetic(const std::string command);
        void writePushPop(InstructionType command, const std::string& segment, int index);
};


#endif