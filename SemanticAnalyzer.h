#ifndef SEMANTICANALYZER_H
#define	SEMANTICANALYZER_H

#include "Parser.h"

using namespace std;

class Symbol {
  string name;
};

class VarSymbol: public Symbol {
  TokenType type;
};

class BuiltInTypeSymbol: public Symbol {
  TokenType type;
};

class FuntionSymbol: public Symbol {
  TokenType type;
};

class ScopedSymbolTable {
  vector<Symbol> symbols;
  string scope_name;
  int scope_level;
  ScopedSymbolTable* enclosing_scope;

  void insert(Symbol s);
  Symbol lookUp(string name);
};

class NodeVisitor {
  void visit(AST* node);
};



class SemanticAnalyzer: public NodeVisitor {
  ScopedSymbolTable* current_scope;

  void visit_Program(AST* node);
  void visit_Constant(AST* node);
  void visit_UnaryOP(AST* node);
  void visit_BinaryOP(AST* node);
  void visit_Compound(AST* node);
  void visit_Assign(AST* node);
  void visit_Variable(AST* node);
  void visit_IfAndElse(AST* node);
  void visit_IfOrElse(AST* node);
  void visit_While(AST* node);
  void visit_FunctionDecl(AST* node);
  void visit_FunctionCall(AST* node);
  void visit_NoOp(AST* node);
};

#endif
