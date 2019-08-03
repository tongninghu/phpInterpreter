#ifndef PARSER_H
#define	PARSER_H

#include <string>
#include <vector>
#include "TreeNode.h"


class SemanticAnalyzer;


using namespace std;


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
    AST* assign_statement(); // Assign*
    AST* echo_statement(); // Echo*
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
