#include <iostream>
#include "codewriter.h"

CodeWriter::CodeWriter(const std::string& filename) {
    outputFile.open(filename);

    if(!outputFile.is_open()){
        std::cerr << "Error: could not open file " << filename << std::endl;
        exit(1);
    }
}

void CodeWriter::writeArithmetic(const std::string command) {
    outputFile << "//" << command << std::endl; // for debugging purposes

    if(command == "add") {
        outputFile << "@SP" << std::endl;
        outputFile << "AM=M-1" << std::endl;
        outputFile << "D=M" << std::endl;
        outputFile << "A=A-1" << std::endl;
        outputFile << "D=D+M" << std::endl;
    }

    else if(command == "sub") {
        outputFile << "@SP" << std::endl;
        outputFile << "AM=M-1" << std::endl;
        outputFile << "D=M" << std::endl;
        outputFile << "A=A-1" << std::endl;
        outputFile << "D=M-D" << std::endl;
    }

    else if(command == "neg") {
        outputFile << "@SP" << std::endl;
        outputFile << "A=M-1" << std::endl;
        outputFile << "M=-M" << std::endl;
    }

    else if (command == "and") {
        outputFile << "@SP" << std::endl;
        outputFile << "AM=M-1" << std::endl;
        outputFile << "D=M" << std::endl;
        outputFile << "A=A-1" << std::endl;
        outputFile << "M=D&M" << std::endl;
    }


}