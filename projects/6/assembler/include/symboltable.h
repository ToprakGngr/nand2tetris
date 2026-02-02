#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <unordered_map>
#include <string>

class SymbolTable {
    private:
        std::unordered_map<std::string, int> symbol_table;
        void initializePreDefined();
    public:
        SymbolTable();
        void add();


};

#endif