#include <string>
#include "code.h"

// All of the tables filled according to the Project 4 documents

std::string Code::dest(const std::string& mnemonic) {
    if(mnemonic.empty()) return "000";

    static const std::unordered_map<std::string, std::string> dest_table = {
        {"A", "100"},
        {"D", "010"},
        {"M", "001"},
        {"AD", "110"},
        {"AM", "101"},
        {"DM", "011"},
        {"AMD", "111"}
    };

    if(dest_table.count(mnemonic)) return dest_table.at(mnemonic);
    
    // invalid, still return default 000
    return "000";
}

// Trick in this function, ALU takes 2 inputs: D register and Mux output
// Mux has 2 inputs: A and M
// ALU does NOT know which one it takes, it does the same operation
// Which means, D+A and D+M is strictly the same for ALU
// Only difference is abit is 0 (A) or 1 (M)
// We keep it seperate with a flag and concatane it later
std::string Code::comp(const std::string& mnemonic){
    std::string aBit = "0";
    std::string cleanMne = mnemonic;

    size_t mPos = mnemonic.find('M');
    if(mPos != std::string::npos){
        for(char& c: cleanMne ) {
            if(c == 'M') c = 'A';
        }
        aBit = "1";
    }

    // use reference here: https://b1391bd6-da3d-477d-8c01-38cdf774495a.filesusr.com/ugd/44046b_7ef1c00a714c46768f08c459a6cab45a.pdf
    static const std::unordered_map<std::string, std::string> comp_table = {
        {"0", "101010"},
        {"1", "111111"},
        {"-1", "111010"},
        {"D", "001100"},
        {"A", "110000"},
        {"!D", "001101"},
        {"!A", "110001"},
        {"-D", "001111"},
        {"-A", "110011"},
        {"D+1", "011111"},
        {"A+1", "110111"},
        {"D-1", "001110"},
        {"A-1", "110010"},
        {"D+A", "000010"},
        {"D-A", "010011"},
        {"A-D", "000111"},
        {"D&A", "000000"},
        {"D|A", "010101"}
    };

    if(comp_table.count(cleanMne)){
        return aBit + comp_table.at(cleanMne);
    }

    return "0000000";

}

std::string Code::jump(const std::string& mnemonic){
     if(mnemonic.empty()) return "000";

    static const std::unordered_map<std::string, std::string> jump_table = {
        {"null", "000"},
        {"JGT", "001"},
        {"JEQ", "010"},
        {"JGE", "011"},
        {"JLT", "100"},
        {"JNE", "101"},
        {"JLE", "110"},
        {"JMP", "111"},
    };

    if(jump_table.count(mnemonic)) return jump_table.at(mnemonic);
    
    // invalid, still return default 000
    return "000";
}
