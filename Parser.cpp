#include "Parser.h"
#include "SemanticAnalyzer.h"
#include "TreeNode.h"

using namespace std;


Parser::Parser(Lexer* l) {
  lexer = l;
  current_token = get_next_token();
}

Token Parser::get_next_token() {
  return lexer->get_next_token();
}

void Parser::eat(TokenType type) {
  if (current_token.type == type) {
  //  cout << "eat value: " << current_token.value << endl;
    current_token = get_next_token();
  }
  else {
    cout << "error unmatched token, want to match: " << type << ", current is: "\
     << current_token.type << ", row: " << current_token.row << ", col: "\
      << current_token.column << endl;
    exit(0);
  }
}

// Program*
AST* Parser::program() {
  eat(BEGIN);
  Program* p = new Program;
  p->children = statement_list();
  eat(END);
  return p;
}

 // vector<VarDecl*>
vector<AST*> Parser::parameter_list() {
  vector<AST*> list;
  list.push_back(variable_def());

  while (current_token.type == COMMA) {
    eat(COMMA);
    list.push_back(variable_def());
  }
  return list;
}

// Compound*
AST* Parser::compound_statement() {
  Compound* p = new Compound;
  eat(LBRACE);
  p->children = statement_list();
  eat(RBRACE);
  return p;
}

// vector<return from statement>
vector<AST*> Parser::statement_list() {
  vector<AST*> list;
  list.push_back(statement());

  while (current_token.type == FUNCID || current_token.type == FUNCTION ||\
     current_token.type == VARID  || current_token.type == IF ||\
      current_token.type == WHILE || current_token.type == ECHO) {

    list.push_back(statement());
  }
  return list;
}

// FunctionDecl* | FunctionCall* | Assign* | IfAndElse* | While* | NoOp*
AST* Parser::statement() {
  AST *p = new AST;

  if (current_token.type == FUNCTION) {
    p = function_def();
  }
  else if (current_token.type == FUNCID) {
    p = function_call();
  }
  else if (current_token.type == VARID) {
    p = assign_statement();
  }
  else if (current_token.type == IF) {
    p = if_statement();
  }
  else if (current_token.type == WHILE) {
    p = while_statement();
  }
  else if (current_token.type == ECHO) {
    p = echo_statement();
  }
  else {
    p = empty();
  }
  return p;
}

// FunctionDecl*
AST* Parser::function_def() {
  FunctionDecl* p = new FunctionDecl;

  eat(FUNCTION);
  p->id = variable_def();
  eat(LPAREN);
  if (current_token.type != RPAREN) {
    p->parameters = parameter_list();
  }
  eat(RPAREN);
  p->compound = compound_statement();
  return p;
}

//  FunctionCall*
AST* Parser::function_call() {
  FunctionCall* p = new FunctionCall;

  p->id = variable();
  eat(LPAREN);
  if (current_token.type != RPAREN) {
    p->parameters.push_back(expr());
    while (current_token.type == COMMA) {
      eat(COMMA);
      p->parameters.push_back(expr());
    }
  }
  eat(RPAREN);
  eat(SEMI);
  return p;
}

// Assign*
AST* Parser::assign_statement() {
  Assign* p = new Assign;

  p->left = variable_def();
  if (current_token.type == ASSIGN) {
    p->op = current_token;
    eat(ASSIGN);
    p->right = test();
  }
  eat(SEMI);
  return p;
}

AST* Parser::echo_statement() {
  Echo* p = new Echo;

  eat(ECHO);
  p->expr = expr();
  eat(SEMI);
  return p;
}

// IfAndElse*
AST* Parser::if_statement() {
  IfAndElse* p = new IfAndElse;

  p->children.push_back(ifelse());
  while (current_token.type == ELSE) {
    p->children.push_back(ifelse());
  }
  return p;
}

// IfOrElse*
AST* Parser::ifelse() {
  IfOrElse* p = new IfOrElse;
  if (current_token.type == IF) {
    eat(IF);
    eat(LPAREN);
    p->test = test();
    eat(RPAREN);
  }
  else {
    eat(ELSE);
    if (current_token.type == IF) {
      eat(IF);
      eat(LPAREN);
      p->test = test();
      eat(RPAREN);
    }
  }
  p->compound = compound_statement();
  return p;
}

// While*
AST* Parser::while_statement() {
  While* p = new While;

  eat(WHILE);
  eat(LPAREN);
  p->test = test();
  eat(RPAREN);
  p->compound = compound_statement();
  return p;
}

// NoOp*
AST* Parser::empty() {
  NoOp* p = new NoOp;
  return p;
}

// BinaryOp*
AST* Parser::test() {
  AST* p = and_test();

  while (current_token.type == OR) {
    BinaryOP *q = new BinaryOP;
    q->left = p;
    q->op = current_token;
    eat(OR);
    q->right = and_test();
    p = q;
  }
  return p;
}

// BinaryOp*
AST* Parser::and_test() {
  AST* p = comparison();

  while (current_token.type == AND) {
    BinaryOP *q = new BinaryOP;
    q->left = p;
    q->op = current_token;
    eat(AND);
    q->right = comparison();
    p = q;
  }
  return p;
}

// BinaryOp*
AST* Parser::comparison() {
  AST* p = expr();

  while (current_token.type == LESS || current_token.type == GREAT || current_token.type == EQ\
     || current_token.type == NE) {

     BinaryOP* q = new BinaryOP;
     q->left = p;
     q->op = current_token;
     eat(current_token.type);
     q->right = expr();
     p = q;
  }
  return p;
}

// BinaryOp*
AST* Parser::expr() {
  AST* p = term();

  while (current_token.type == PLUS || current_token.type == MINUS) {
     BinaryOP* q = new BinaryOP;
     q->left = p;
     q->op = current_token;
     eat(current_token.type);
     q->right = term();
     p = q;
  }
  return p;
}

// BinaryOP*
AST* Parser::term() {
  AST* p = factor();

  while (current_token.type == MUL || current_token.type == DIV) {
     BinaryOP* q = new BinaryOP;
     q->left = p;
     q->op = current_token;
     eat(current_token.type);
     q->right = factor();
     p = q;
  }
  return p;
}

// UnaryOP* | return from atom
AST* Parser::factor() {
  if (current_token.type == PLUS || current_token.type == MINUS) {
    UnaryOP* p = new UnaryOP;
    p->op = current_token;
    eat(current_token.type);
    p->expr = factor();
    return p;
  }
  else {
    return atom();
  }
}

 // Constant* | BinaryOP* | Var*
AST* Parser::atom() {
  if (current_token.type == INTEGER_CONST || current_token.type == FLOAT_CONST ||\
     current_token.type == STRING_CONST) {
    Constant* p = new Constant;
    p->t = current_token;
    eat(current_token.type);
    return p;
  }
  else if (current_token.type == LPAREN) {
    eat(LPAREN);
    AST* p = test();
    eat(RPAREN);
    return p;
  }
  else {
    return variable();
  }
}

 // Var*
AST* Parser::variable() {
  Var* p = new Var;
  p->t = current_token;
  eat(current_token.type);
  return p;
}

// VarDecl*
AST* Parser::variable_def() {
  VarDecl* p = new VarDecl;
  p->t = current_token;
  eat(current_token.type);
  return p;
}
