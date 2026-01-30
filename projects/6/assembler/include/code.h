#ifndef CODE_H
#define CODE_H

#include <unordered_map>
#include <string>

class Code{
    public:
        std::string dest(const std::string& mnemonic);
        std::string comp(const std::string& mnemonic);
        std::string jump(const std::string& mnemonic);

};

#endif
