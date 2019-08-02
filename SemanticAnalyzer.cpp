#include "SemanticAnalyzer.h"

using namespace std;

VarSymbol::VarSymbol(TokenType t) {
  this->type = t;
}

ScopedSymbolTable::ScopedSymbolTable(string name, int c, ScopedSymbolTable* scope) {
  scope_name = name;
  scope_level = c;
  enclosing_scope = scope;
}

void ScopedSymbolTable::insert(Symbol s) {
  symbols.insert({s.name, s});
}

Symbol ScopedSymbolTable::LookUp(string name) {
  if (symbols.find(name) != symbols.end()) {
    return symbols[name];
  }
  else {
    Symbol a;
    return a;
  }
}

void SemanticAnalyzer::NodeVisit(AST* tree) {
  tree->visit(this);
}
