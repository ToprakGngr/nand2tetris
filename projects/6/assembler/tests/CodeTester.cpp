#include <iostream>
#include <string>
#include "code.h"

int main() {
    Code coder;
    
    std::cout << "Testing Code Module..." << std::endl;
    
    // Test 1: Basic A
    std::string res1 = coder.comp("D+A");
    std::cout << "D+A Expect: 0000010 | Got: " << res1 << std::endl;

    // Test 2: The Logic Switch (M)
    std::string res2 = coder.comp("D+M");
    std::cout << "D+M Expect: 1000010 | Got: " << res2 << std::endl;
    
    // Test 3: Dest
    std::cout << "AMD Expect: 111     | Got: " << coder.dest("AMD") << std::endl;

    return 0;
}
