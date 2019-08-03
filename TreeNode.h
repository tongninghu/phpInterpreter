#ifndef TREENODE_H
#define	TREENODE_H

#include <string>
#include <vector>
#include "Lexer.h"

class SemanticAnalyzer;

using namespace std;

class AST {
  public:
    virtual void visit(SemanticAnalyzer* a) {}
    virtual void visit(SemanticAnalyzer* a, bool& stop) {}
    virtual void visit(SemanticAnalyzer* a, string value, TokenType type, bool funcCall = false) {}
    virtual Token getToken() {}
    virtual string getValue() {}
    virtual TokenType getValueType() {}
    virtual vector<AST*> getParameters() {}
    virtual AST* getCompound() {}
    virtual void assignValue(string s) {}
    virtual void assignValueType(TokenType t) {}
};

class Program: public AST{
  public:
    vector<AST*> children;

    ~Program();
    virtual void visit(SemanticAnalyzer* a);
};

class Constant: public AST {
  public:
    Token t;

    virtual string getValue();
    virtual TokenType getValueType();
    virtual void visit(SemanticAnalyzer* a);
};

class UnaryOP: public AST {
  public:
    Token op;
    AST* expr;
    string value;
    TokenType valueType;

    virtual string getValue();
    virtual TokenType getValueType();
    ~UnaryOP();
    virtual void visit(SemanticAnalyzer* a);
};

class BinaryOP: public AST {
  public:
    AST* left;
    Token op;
    AST* right;
    string value;
    TokenType valueType;

    virtual string getValue();
    virtual TokenType getValueType();
    ~BinaryOP();
    virtual void visit(SemanticAnalyzer* a);
};

class Compound: public AST {
  public:
    vector<AST*> children;

    ~Compound();
    virtual void visit(SemanticAnalyzer* a);
};

class Assign: public AST {
  public:
    AST* left;
    Token op;
    AST* right;

    ~Assign();
    virtual void visit(SemanticAnalyzer* a);
};

class Echo: public AST {
  public:
    AST* expr;

    ~Echo();
    virtual void visit(SemanticAnalyzer* a);
};

class Var: public AST{
  public:
    Token t;
    string value;
    TokenType valueType;

    virtual string getValue();
    virtual TokenType getValueType();
    virtual Token getToken();
    virtual void visit(SemanticAnalyzer* a);
};

class VarDecl: public AST{
  public:
    Token t;

    virtual Token getToken();
    virtual void visit(SemanticAnalyzer* a);
    virtual void visit(SemanticAnalyzer* a, string value, TokenType type, bool funcCall = false);
};

class IfAndElse: public AST{
  public:
    vector<AST*> children;

    ~IfAndElse();
    virtual void visit(SemanticAnalyzer* a);
};

class IfOrElse: public AST{
  public:
    AST* test;
    AST* compound;

    ~IfOrElse();
    virtual void visit(SemanticAnalyzer* a, bool& stop);
    virtual void visit(SemanticAnalyzer* a);
};

class While: public AST{
  public:
    AST* test;
    AST* compound;

    ~While();
    virtual void visit(SemanticAnalyzer* a);
};

class FunctionDecl: public AST{
  public:
    AST* id;
    vector<AST*> parameters;
    AST* compound;

    ~FunctionDecl();
    virtual vector<AST*> getParameters();
    virtual AST* getCompound();
    virtual void visit(SemanticAnalyzer* a);
};

class FunctionCall: public AST{
  public:
    AST* id;
    vector<AST*> parameters;

    ~FunctionCall();
    virtual void visit(SemanticAnalyzer* a);
};

class NoOp: public AST{};

#endif
