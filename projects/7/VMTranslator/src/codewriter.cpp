#include <iostream>
#include "codewriter.h"

CodeWriter::CodeWriter(const std::string& filename) {
    outputFile.open(filename);

    if(!outputFile.is_open()){
        std::cerr << "Error: could not open file " << filename << std::endl;
        exit(1);
    }
}

