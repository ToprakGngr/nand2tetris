#include <iostream>
#include "VMparser.h"
#include <algorithm> 
#include <cctype>
#include <string>

VMParser::VMParser(const std::string& filename) {
    inputFile.open(filename);

    if(!inputFile.is_open()){
        std::cerr << "Error: could not open file " << filename << std::endl;
        exit(1);
    }
}

static inline void ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char c) {return !std::isspace(c);}));
}

static inline void rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char c) {return !std::isspace(c);}).base(), s.end());
}

static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

bool VMParser::advance() {
    std::string line;

    while(std::getline(inputFile, line)) {
        // 1. Remove comments
        size_t commentPos = line.find("//");
        if(commentPos != std::string::npos) {
            line = line.substr(0, commentPos);
        }
        
        // 2. Erase whitespaces before and after the command
        trim(line);

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