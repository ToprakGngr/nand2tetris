#include <iostream>
#include <iomanip>
#include "parser.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./HackAssembler <filename.asm>" << std::endl;
        return 1;
    }

    std::cout << "Testing Parser on: " << argv[1] << "\n" << std::endl;
    std::cout << std::left << std::setw(15) << "TYPE" 
              << std::setw(15) << "SYMBOL" 
              << std::setw(10) << "DEST" 
              << std::setw(10) << "COMP" 
              << std::setw(10) << "JUMP" << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;

    Parser parser(argv[1]);

    // For this test, let's just loop 20 times
    for (int i = 0; i < 20; i++) {
        parser.advance();
        
        // If the parser hit EOF, we should stop
        InstructionType type = parser.instructionType();
        
        if (type == A_TYPE) {
            std::cout << std::left << std::setw(15) << "A_COMMAND" 
                      << std::setw(15) << parser.symbol() 
                      << "n/a       n/a       n/a" << std::endl;
        } 
        else if (type == L_TYPE) {
            std::cout << std::left << std::setw(15) << "L_COMMAND" 
                      << std::setw(15) << parser.symbol() 
                      << "n/a       n/a       n/a" << std::endl;
        } 
        else if (type == C_TYPE) {
            // Put brackets [] around strings to spot hidden spaces!
            std::string d = "[" + parser.dest() + "]";
            std::string c = "[" + parser.comp() + "]";
            std::string j = "[" + parser.jump() + "]";

            std::cout << std::left << std::setw(15) << "C_COMMAND" 
                      << std::setw(15) << "n/a" 
                      << std::setw(10) << d 
                      << std::setw(10) << c 
                      << std::setw(10) << j << std::endl;
        }
    }

    return 0;
}
