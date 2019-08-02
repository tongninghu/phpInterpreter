#ifndef PARSER_H
#define	PARSER_H

#include "Lexer.h"
#include <string>
#include <vector>


class SemanticAnalyzer;

using namespace std;

class AST {
  public:
    virtual void visit(SemanticAnalyzer* a) {}
    virtual Token getToken() {}
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

    virtual void visit(SemanticAnalyzer* a);
};

class UnaryOP: public AST {
  public:
    Token op;
    AST* expr;

    ~UnaryOP();
    virtual void visit(SemanticAnalyzer* a);
};

class BinaryOP: public AST {
  public:
    AST* left;
    Token op;
    AST* right;

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

class Var: public AST{
  public:
    Token t;
    string value;
    virtual Token getToken();
    virtual void visit(SemanticAnalyzer* a);
};

class VarDecl: public AST{
  public:
    Token t;
    string value;
    virtual Token getToken();
    virtual void visit(SemanticAnalyzer* a);
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

class Parser{
  public:
    Lexer* lexer;
    Token current_token;

    Parser(Lexer* l);
    Token get_next_token();
    void eat(TokenType type);

    AST* program(); // Program*
    vector<AST*> parameter_list(); // vector<Var*>
    AST* compound_statement(); // Compound*
    vector<AST*> statement_list(); // vector<return from statement>
    AST* statement(); // Compound* | FunctionDecl* | FunctionCall* | Assign* | IfAndElse* | While* | NoOp*
    AST* function_def();  // FunctionDecl*
    AST* function_call(); //  FunctionCall*
    AST* assignment_statement(); // Assign*
    AST* if_statement();  // IfAndElse*
    AST* ifelse(); // IfOrElse*
    AST* while_statement(); // While*
    AST* empty(); // NoOp*
    AST* test();  // BinaryOp*
    AST* and_test();  // BinaryOp*
    AST* comparison(); // BinaryOp*
    AST* expr();  // BinaryOp*
    AST* term();  // BinaryOP*
    AST* factor();  // UnaryOP* | return from atom
    AST* atom();   // Constant* | BinaryOP* | Var*
    AST* variable();  // Var*
    AST* variable_def();  // Var*
};

#endif
