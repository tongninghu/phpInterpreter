#include "Parser.h"

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
    cout << "eat type: " << current_token.type << ", with value: " << current_token.value << endl;
    current_token = get_next_token();
  }
  else {
    cout << "error unmatched token, want to match: " << type << ", current is: "\
     << current_token.type << ", row: " << current_token.row << ", col: " << current_token.column << endl;
    exit;
  }
}

// Program*
AST* Parser::program() {
//cout << "VISIT program" << endl;
  eat(BEGIN);
  Program* p = new Program;
  p->children = statement_list();
  eat(END);
  return p;
}

 // vector<Var*>
vector<AST*> Parser::parameter_list() {
//cout << "VISIT parameter_list" << endl;
  vector<AST*> list;
  list.push_back(variable());

  while (current_token.type == COMMA) {
    eat(COMMA);
    list.push_back(variable());
  }
  return list;
}

// Compound*
AST* Parser::compound_statement() {
//cout << "VISIT compound_statement" << endl;
  Compound* p = new Compound;
  eat(LBRACE);
  p->children = statement_list();
  eat(RBRACE);
  return p;
}

// vector<return from statement>
vector<AST*> Parser::statement_list() {
//cout << "VISIT statement_list" << endl;
  vector<AST*> list;
  list.push_back(statement());

  while (current_token.type == SEMI) {
    eat(SEMI);
    list.push_back(statement());
  }
  return list;
}

// Compound* | FunctionDecl* | FunctionCall* | Assign* | IfAndElse* | While* | NoOp*
AST* Parser::statement() {
//cout << "VISIT statement" << endl;
  AST *p = new AST;

  if (current_token.type == LBRACE) {
    p = compound_statement();
  }
  else if (current_token.type == FUNCTION) {
    p = function_def();
  }
  else if (current_token.type == FUNCID) {
    p = function_call();
  }
  else if (current_token.type == VARID) {
    p = assignment_statement();
  }
  else if (current_token.type == IF) {
    p = if_statement();
  }
  else if (current_token.type == WHILE) {
    p = while_statement();
  }
  else {
    p = empty();
  }
  return p;
}

// FunctionDecl*
AST* Parser::function_def() {
//cout << "VISIT function_def" << endl;
  FunctionDecl* p = new FunctionDecl;

  eat(FUNCTION);
  p->id = variable();
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
//cout << "VISIT function_call" << endl;
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
  return p;
}

// Assign*
AST* Parser::assignment_statement() {
//cout << "VISIT assignment_statement" << endl;
  Assign* p = new Assign;

  p->left = variable();
  p->op = current_token;
  eat(ASSIGN);
  p->right = test();
  return p;
}

// IfAndElse*
AST* Parser::if_statement() {
//cout << "VISIT if_statement" << endl;
  IfAndElse* p = new IfAndElse;

  p->children.push_back(ifelse());
  while (current_token.type == ELSE) {
    p->children.push_back(ifelse());
  }
  return p;
}

// IfOrElse*
AST* Parser::ifelse() {
//cout << "VISIT ifelse" << endl;
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
//cout << "VISIT while_statement" << endl;
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
//cout << "VISIT empty" << endl;
  NoOp* p = new NoOp;
  return p;
}

// BinaryOp*
AST* Parser::test() {
//cout << "VISIT test" << endl;
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
//cout << "VISIT and_test" << endl;
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
//cout << "VISIT comparison" << endl;
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
//cout << "VISIT expr" << endl;
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
//cout << "VISIT term" << endl;
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
//cout << "VISIT factor" << endl;
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

 // Constant* | BinaryOP* | Variable*
AST* Parser::atom() {
//cout << "VISIT atom" << endl;
  if (current_token.type == INTEGER_CONST || current_token.type == FLOAT_CONST ||\
     current_token.type == STRING_CONST) {
    Constant* p = new Constant;
    p->value = current_token;
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
//cout << "VISIT variable" << endl;
  Var* p = new Var;
  p->name = current_token;
  eat(current_token.type);
  return p;
}
