#include "symboltable.h"

void SymbolTable::initializePreDefined() {
    for(int i = 0; i < 16; i++) {
        std::string key = 'R' + std::to_string(i);
        symbol_table.insert({key, 0});
    }
    symbol_table.insert({"SP", 0});
    symbol_table.insert({"LCL", 1});
    symbol_table.insert({"ARG", 2});
    symbol_table.insert({"THIS", 3});
    symbol_table.insert({"THAT", 4});

    symbol_table.insert({"KBD", 24576});
    symbol_table.insert({"THAT", 16384});
}

SymbolTable::SymbolTable() {
    initializePreDefined();
}

void SymbolTable::add(const std::string& symbol, int address){
    symbol_table.insert({symbol, address});
}