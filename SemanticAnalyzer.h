#ifndef SEMANTICANALYZER_H
#define	SEMANTICANALYZER_H

#include <unordered_map>
#include "Parser.h"

using namespace std;


class Symbol {
  public:
    string name = "";
};

class VarSymbol: public Symbol {
  public:
    TokenType type;

    VarSymbol(TokenType t);
};

class FuntionSymbol: public Symbol {
  public:
    TokenType type;
    vector<Symbol> parameters;
};

class ScopedSymbolTable {
  private:
      unordered_map<string, Symbol> symbols;
  public:
    string scope_name;
    int scope_level;
    ScopedSymbolTable* enclosing_scope;

    ScopedSymbolTable(string name = "global", int c = 0, ScopedSymbolTable* scope = NULL);
    void insert(Symbol s);
    Symbol LookUp(string name);
};


class SemanticAnalyzer {
  public:
    ScopedSymbolTable* current_scope;
    int current_level;

    void NodeVisit(AST* tree);
};

#endif
