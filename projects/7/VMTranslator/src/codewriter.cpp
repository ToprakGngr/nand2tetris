#include <iostream>
#include "codewriter.h"
#include <unordered_map>
#include <filesystem>

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

    // save filename for static operation
    std::filesystem::path p(filename);
    currentFileName = p.stem().string();

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

        else if(segment == "local" || segment == "argument" || segment == "this" || segment == "that") {
            std::string label = segmentTable.at(segment);

            // addr = *local + i, also store the result in D register
            outputFile << "@" << index << std::endl;
            outputFile << "D=A" << std::endl;
            outputFile << "@" << label <<std::endl;
            outputFile << "A=D+M" << std::endl;
            outputFile << "D=M" << std::endl;
            
            // ram[sp] = ram[addr]
            outputFile << "@SP" << std::endl;
            outputFile << "A=M" << std::endl;
            outputFile << "M=D" << std::endl;
            
            // sp++
            outputFile << "@SP" << std::endl;
            outputFile << "M=M+1" << std::endl;
        }

        else if(segment == "static") {
            // label string
            std::string label = currentFileName + "." + std::to_string(index);

            outputFile << "@" << label << std::endl;
            outputFile << "D=M" << std::endl;
            
            outputFile << "@SP" << std::endl;
            outputFile << "A=M" << std::endl;
            outputFile << "M=D" << std::endl;
            outputFile << "@SP" << std::endl;
            outputFile << "M=M+1" << std::endl;
        }

        else if(segment == "temp" || segment == "pointer") {
            int baseAddr = (segment == "temp") ? 5 : 3;
            int targetAddr = baseAddr + index;
            
            outputFile << "@" << targetAddr << std::endl;
            outputFile << "D=M" << std::endl;
            outputFile << "@SP" << std::endl;
            outputFile << "A=M" << std::endl;
            outputFile << "M=D" << std::endl;
            outputFile << "@SP" << std::endl;
            outputFile << "M=M+1" << std::endl;
        }
    }

    if(command == POP_TYPE) {
        if(segment == "constant") {
            std::cerr << "Popping a constant value is not allowed.";
            exit(1);
        }

        else if(segment == "local" || segment == "argument" || segment == "this" || segment == "that") {
            std::string label = segmentTable.at(segment);
            outputFile << "@" << label << std::endl;
            outputFile << "D=M" << std::endl;
            outputFile << "@" << index << std::endl;
            outputFile << "D=D+A" << std::endl;
            outputFile << "@R13" << std::endl;
            outputFile << "M=D" << std::endl;
            outputFile << "@SP" << std::endl;
            outputFile << "AM=M-1" << std::endl;
            outputFile << "D=M" << std::endl;
            outputFile << "@R13" << std::endl;
            outputFile << "A=M" << std::endl;
            outputFile << "M=D" << std::endl;
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