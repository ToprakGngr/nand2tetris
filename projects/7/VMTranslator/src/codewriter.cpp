#include <iostream>
#include "codewriter.h"
#include <unordered_map>

CodeWriter::CodeWriter(const std::string& filename) {
    outputFile.open(filename);

    if(!outputFile.is_open()){
        std::cerr << "Error: could not open file " << filename << std::endl;
        exit(1);
    }
    segmentTable = {
        {"local", "LCL"},      // RAM[1] points to the base of local
        {"argument", "ARG"},   // RAM[2] points to the base of argument
        {"this", "THIS"},      // RAM[3] points to the base of this
        {"that", "THAT"}       // RAM[4] points to the base of that
    };

}

void CodeWriter::writePushPop(InstructionType command, const std::string& segment, int index) {
    outputFile << "//" << command << std::endl; // for debugging purposes

    if(command == PUSH_TYPE) {
        if(segment == "constant") {
            // D = i
            outputFile << "@" << index << std::endl;
            outputFile << "D=A" << std::endl;

            // Ram[sp] = i
            outputFile << "@SP" << std::endl;
            outputFile << "A=M" << std::endl;
            outputFile << "M=D" << std::endl;
            
            // SP++
            outputFile << "@SP" << std::endl;
            outputFile << "M=M+1" << std::endl;
            
        }
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

    else if (command == "or") {
        outputFile << "@SP" << std::endl;
        outputFile << "AM=M-1" << std::endl;
        outputFile << "D=M" << std::endl;
        outputFile << "A=A-1" << std::endl;
        outputFile << "M=D|M" << std::endl;
    }

    else if (command == "not") {
        outputFile << "@SP" << std::endl;
        outputFile << "A=M-1" << std::endl;
        outputFile << "M=!M" << std::endl; 
    }
}