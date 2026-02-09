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