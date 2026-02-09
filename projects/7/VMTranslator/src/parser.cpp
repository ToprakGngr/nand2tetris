#include <string>
#include <fstream>
#include <iostream>
#include "VMparser.h"

VMParser::VMParser(const std::string& filename) {
    inputFile.open(filename);

    if(!inputFile.is_open()){
        std::cerr << "Error: could not open file " << filename << std::endl;
        exit(1);
    }
}

bool VMParser::advance() {
    std::string line;

    while(std::getline(inputFile, line)) {
        // 1. Remove comments
        size_t commentPos = line.find("//");
        if(commentPos != std::string::npos) {
            line = line.substr(0, commentPos);
        }
        
        // 2. Erase all whitespaces within the line
        std::erase_if(line, [](unsigned char c) { return std::isspace(c); });

        if(line.empty()) continue;

        currentCommand = line;
        return true;
    }
    return false;
}

// move the cursor to the beginning
void VMParser::reset() {
    inputFile.clear();
    inputFile.seekg(0);
}