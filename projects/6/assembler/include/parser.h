#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>

class Parser {
    private:
        std::ifstream inputFile;
        std::string currentCommand;

    public:
        Parser(std::string filename);

        void advance();
};


#endif

