#include "SemanticAnalyzer.h"

using namespace std;

VarSymbol::VarSymbol(Token t) {
  this->t = t;
  this->name = t.value;
}

FuntionSymbol::FuntionSymbol(Token t) {
  this->t = t;
  this->name = t.value;
}

ScopedSymbolTable::ScopedSymbolTable(string name, int c, ScopedSymbolTable* scope) {
  scope_name = name;
  scope_level = c;
  enclosing_scope = scope;
}

ScopedSymbolTable::~ScopedSymbolTable() {
  delete enclosing_scope;
  for (pair<string, Symbol*> element : symbols) {
  	delete element.second;
  }
}

void ScopedSymbolTable::insert(Symbol* s) {
  symbols.insert({s->name, s});
}

Symbol* ScopedSymbolTable::LookUp(string name, bool SearchEnclosing) {
  if (symbols.find(name) != symbols.end()) {
    return symbols[name];
  }
  else {
    if (SearchEnclosing) {
      ScopedSymbolTable *parent = enclosing_scope;
      while (parent) {
        if (parent->symbols.find(name) != parent->symbols.end()) {
          return parent->symbols[name];
        }
        parent = parent->enclosing_scope;
      }
    }
    Symbol* a = new Symbol;
    return a;
  }
}

SemanticAnalyzer::~SemanticAnalyzer(){
  delete current_scope;
}

void SemanticAnalyzer::NodeVisit(AST* tree) {
  tree->visit(this);
}
