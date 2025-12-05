#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "llvm/IR/Instructions.h"
#include <map>
#include <string>
#include <vector>

using namespace llvm;

class SymbolTable {
private:
    // Pila de scopes: cada scope es un mapa de nombre -> AllocaInst*
    std::vector<std::map<std::string, AllocaInst*>> scopes;

public:
    SymbolTable() {
        // Scope global inicial
        pushScope();
    }

    void pushScope() {
        scopes.push_back(std::map<std::string, AllocaInst*>());
    }

    void popScope() {
        if (!scopes.empty()) {
            scopes.pop_back();
        }
    }

    // Declarar variable en el scope actual
    void declare(const std::string& name, AllocaInst* alloca) {
        if (!scopes.empty()) {
            scopes.back()[name] = alloca;
        }
    }

    // Buscar variable en todos los scopes (desde el más interno)
    AllocaInst* lookup(const std::string& name) {
        for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
            auto found = it->find(name);
            if (found != it->end()) {
                return found->second;
            }
        }
        return nullptr;
    }

    // Verificar si existe en scope actual
    bool existsInCurrentScope(const std::string& name) {
        if (scopes.empty()) return false;
        return scopes.back().find(name) != scopes.back().end();
    }
};

#endif // SYMBOL_TABLE_H