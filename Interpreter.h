#ifndef INTERPRETER_H
#define	INTERPRETER_H

#include "SemanticAnalyzer.h"

using namespace std;

class Interpreter: public NodeVisitor {
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
