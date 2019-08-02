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
    Token t;
    string value;
    VarSymbol(Token t);
};

class FuntionSymbol: public Symbol {
  public:
    Token t;
    vector<Symbol> parameters;
    FuntionSymbol(Token t);
};


class ScopedSymbolTable {
  private:
      unordered_map<string, Symbol*> symbols;
  public:
    string scope_name;
    int scope_level;
    ScopedSymbolTable* enclosing_scope;

    ScopedSymbolTable(string name = "global", int c = 0, ScopedSymbolTable* scope = NULL);
    ~ScopedSymbolTable();
    void insert(Symbol* s);
    Symbol* LookUp(string name, bool SearchEnclosing = false);
};


class SemanticAnalyzer {
  public:
    ScopedSymbolTable* current_scope;
    int current_level;

    ~SemanticAnalyzer();
    void NodeVisit(AST* tree);
};

#endif
