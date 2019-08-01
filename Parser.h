#ifndef PARSER_H
#define	PARSER_H

#include <string>
#include <vector>
#include "Lexer.h"

using namespace std;

class AST {};

class Program: public AST{
  public:
    vector<AST*> children;
};

class Constant: public AST {
  public:
    Token value;
};

class UnaryOP: public AST {
  public:
    Token op;
    AST* expr;
};

class BinaryOP: public AST {
  public:
    AST* left;
    Token op;
    AST* right;
};

class Compound: public AST {
  public:
    vector<AST*> children;
};

class Assign: public AST {
  public:
    AST* left;
    Token op;
    AST* right;
};

class Var: public AST{
  public:
    Token name;
};

class IfAndElse: public AST{
  public:
    vector<AST*> children;
};

class IfOrElse: public AST{
  public:
    AST* test;
    AST* compound;
};

class While: public AST{
  public:
    AST* test;
    AST* compound;
};

class FunctionDecl: public AST{
  public:
    AST* id;
    vector<AST*> parameters;
    AST* compound;
};

class FunctionCall: public AST{
  public:
    AST* id;
    vector<AST*> parameters;
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
};

#endif
