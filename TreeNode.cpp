#include "TreeNode.h"
#include "SemanticAnalyzer.h"

using namespace std;

/*------------------------------Program-----------------------------------*/


Program::~Program() {
  for (int i = 0; i < children.size(); i++) {
    delete children[i];
  }
}

void Program::visit(SemanticAnalyzer* a) {   // create symbol table
  //cout << "visit program" << endl;
  ScopedSymbolTable* p = new ScopedSymbolTable;
  a->current_scope = p;
  a->current_level = 0;

  for (int i = 0; i < children.size(); i++) {
    children[i]->visit(a);
  }
  //cout << "leave program" << endl;
}


/*------------------------------Constant-----------------------------------*/


string Constant::getValue() {
  return t.value;
}

TokenType Constant::getValueType() {
  return t.type;
}

void Constant::visit(SemanticAnalyzer* a) {
  //cout << "visit Constant" << endl;
  //value.print();
  //cout << "leave Constant" << endl;
}


/*------------------------------UnaryOP-----------------------------------*/


UnaryOP::~UnaryOP() {
  delete expr;
}

string UnaryOP::getValue() {
  return value;
}

TokenType UnaryOP::getValueType() {
  return valueType;
}

void UnaryOP::visit(SemanticAnalyzer* a) {
  //cout << "visit UnaryOP" << endl;
  expr->visit(a);
  valueType = expr->getValueType();
  if (op.type == PLUS) {
    if (valueType == INTEGER || valueType == INTEGER_CONST) {
      value = to_string(stoi(expr->getValue()));
    }
    else if (valueType == FLOAT || valueType == FLOAT_CONST) {
      value = to_string(stof(expr->getValue()));
    }
    else {
      cout << "cannot use positive for string number" << endl;
      exit(0);
    }
  }
  else if (op.type == MINUS) {
    if (valueType == INTEGER || valueType == INTEGER_CONST) {
      value = to_string(-1 * stoi(expr->getValue()));
    }
    else if (valueType == FLOAT || valueType == FLOAT_CONST) {
      value = to_string(-1 * stof(expr->getValue()));
    }
    else {
      cout << "cannot use negative for string number" << endl;
      cout << "string:" << expr->getValue() << endl;
      exit(0);
    }
  }
  //cout << "leave UnaryOP" << endl;
}



/*------------------------------BinaryOP-----------------------------------*/



string BinaryOP::getValue() {
  return value;
}

TokenType BinaryOP::getValueType() {
  return valueType;
}

BinaryOP::~BinaryOP() {
  delete left;
  delete right;
}

void BinaryOP::visit(SemanticAnalyzer* a) {
  //cout << "visit BinaryOP" << endl;
  left->visit(a);
  right->visit(a);
  valueType = left->getValueType();
  if (op.type == PLUS) {
    if (valueType == INTEGER || valueType == INTEGER_CONST) {
      value = to_string(stoi(left->getValue()) + stoi(right->getValue()));
      valueType == INTEGER_CONST;
    }
    else if (valueType == FLOAT || valueType == FLOAT_CONST) {
      value = to_string(stof(left->getValue()) + stof(right->getValue()));
      valueType == FLOAT_CONST;
    }
    else {
      value = left->getValue() + right->getValue();
      valueType == STRING_CONST;
    }
  }
  else if (op.type == MINUS) {
    if (valueType== INTEGER || valueType == INTEGER_CONST) {
      value = to_string(stoi(left->getValue()) - stoi(right->getValue()));
      valueType == INTEGER_CONST;
    }
    else if (valueType == FLOAT || valueType == FLOAT_CONST) {
      value = to_string(stof(left->getValue()) - stof(right->getValue()));
      valueType == FLOAT_CONST;
    }
    else {
      cout << "cannot use MINUS for string number" << endl;
      exit(0);
    }
  }
  else if (op.type == MUL) {
    if (valueType == INTEGER || valueType == INTEGER_CONST) {
      value = to_string(stoi(left->getValue()) * stoi(right->getValue()));
      valueType == INTEGER_CONST;
    }
    else if (valueType == FLOAT || valueType == FLOAT_CONST) {
      value = to_string(stof(left->getValue()) * stof(right->getValue()));
      valueType == FLOAT_CONST;
    }
    else {
      cout << "cannot use MUL for string number" << endl;
      exit(0);
    }
  }
  else if (op.type == DIV) {
    if (valueType == INTEGER || valueType == INTEGER_CONST) {
      value = to_string(stoi(left->getValue()) / stoi(right->getValue()));
      valueType == INTEGER_CONST;
    }
    else if (valueType == FLOAT || valueType == FLOAT_CONST) {
      value = to_string(stof(left->getValue()) / stof(right->getValue()));
      valueType == FLOAT_CONST;
    }
    else {
      cout << "cannot use DIV for string number" << endl;
      exit(0);
    }
  }
  else if (op.type == LESS) {
    if (valueType == INTEGER || valueType == INTEGER_CONST) {
      if (stoi(left->getValue()) < stoi(right->getValue())) value = "1";
      else value = "0";
    }
    else if (valueType == FLOAT || valueType == FLOAT_CONST) {
      if (stof(left->getValue()) < stof(right->getValue())) value = "1";
      else value = "0";
    }
    else {
      cout << "cannot use LESS for string number" << endl;
      exit(0);
    }
    valueType = INTEGER_CONST;
  }
  else if (op.type == GREAT) {
    if (valueType == INTEGER || valueType == INTEGER_CONST) {
      if (stoi(left->getValue()) > stoi(right->getValue())) value = "1";
      else value = "0";
    }
    else if (valueType == FLOAT || valueType == FLOAT_CONST) {
      if (stof(left->getValue()) > stof(right->getValue())) value = "1";
      else value = "0";
    }
    else {
      cout << "cannot use GREAT for string number" << endl;
      exit(0);
    }
    valueType = INTEGER_CONST;
  }
  else if (op.type == EQ) {
    if (left->getValue() == right->getValue()) value = "1";
    else value = "0";
    valueType = INTEGER_CONST;
  }
  else if (op.type == NE) {
    if (left->getValue() != right->getValue()) value = "1";
    else value = "0";
    valueType = INTEGER_CONST;
  }
  else if (op.type == AND) {
    if (left->getValue() != "0" && right->getValue() != "0") value = "1";
    else value = "0";
    valueType = INTEGER_CONST;
  }
  else if (op.type == OR) {
    if (left->getValue() != "0" || right->getValue() != "0") value = "1";
    else value = "0";
    valueType = INTEGER_CONST;
  }
  //op.print();
  //cout << "leave BinaryOP" << endl;
}


/*------------------------------Compound-----------------------------------*/



Compound::~Compound() {
  for (int i = 0; i < children.size(); i++) {
    delete children[i];
  }
}

void Compound::visit(SemanticAnalyzer* a) {
  //cout << "visit Compound" << endl;
  for (int i = 0; i < children.size(); i++) {
    children[i]->visit(a);
  }
  //cout << "leave Compound" << endl;
}




/*------------------------------Assign-----------------------------------*/



Assign::~Assign() {
  delete left;
  delete right;
}

void Assign::visit(SemanticAnalyzer* a) {
  //cout << "visit Assign" << endl;
  string value;
  TokenType type;
  if (op.type == ASSIGN) {
    right->visit(a);
    value = right->getValue();
    type = right->getValueType();
    left->visit(a, value, type);
  }
  else {
    left->visit(a);
  }

  //op.print();
  //cout << "leave Assign" << endl;
}



/*------------------------------Echo-----------------------------------*/



Echo::~Echo() {
  delete expr;
}

void Echo::visit(SemanticAnalyzer* a) {
  expr->visit(a);
  string value = expr->getValue();

  for (int i = 0; i < value.size(); i++) {
    if (value[i] == '\\' && i < (value.size() - 1) && value[i + 1] == 'n') {
      i++;
      cout << endl;
    }
    else cout << value[i];
  }
}



/*--------------------------------Var-----------------------------------*/



string Var::getValue() {
  return value;
}

TokenType Var::getValueType() {
  return valueType;
}

Token Var::getToken() {
  return t;
}

void Var::visit(SemanticAnalyzer* a) {
  Symbol* s = a->current_scope->LookUp(t.value, true);
  if (s->name == "") {
    cout << "undefined variable" << endl;
    exit(0);
  }
  else {
    valueType = s->getValueType();
    value = s->getValue();
  }

  //name.print();
  //cout << "leave Var" << endl;
}



/*--------------------------------VarDecl-----------------------------------*/


Token VarDecl::getToken() {
  return t;
}

void VarDecl::visit(SemanticAnalyzer* a) {
  Symbol* s = a->current_scope->LookUp(t.value, true);
  if (s->name == "") {
    VarSymbol *v = new VarSymbol(t);
    a->current_scope->insert(v);
  }
  //name.print();
  //cout << "leave VarDecl" << endl;
}

void VarDecl::visit(SemanticAnalyzer* a, string value, TokenType type, bool funcCall) {
  //cout << "visit VarDecl" << endl;
  if (!funcCall) {
    Symbol* s = a->current_scope->LookUp(t.value, true);
    if (s->name == "") {
      VarSymbol *v = new VarSymbol(t);
      v->value = value;
      v->valueType = type;
      a->current_scope->insert(v);
    }
    else {
      s->getValue() = value;
      s->getValueType() = type;
    }
  }
  else {
    Symbol* s = a->current_scope->LookUp(t.value, false);
    if (s->name == "") {
      VarSymbol *v = new VarSymbol(t);
      v->value = value;
      v->valueType = type;
      a->current_scope->insert(v);
    }
    else {
      s->getValue() = value;
      s->getValueType() = type;
    }
  }

  //name.print();
  //cout << "leave VarDecl" << endl;
}


/*--------------------------------IfAndElse-----------------------------------*/


IfAndElse::~IfAndElse() {
  for (int i = 0; i < children.size(); i++) {
    delete children[i];
  }
}

void IfAndElse::visit(SemanticAnalyzer* a) {
//  cout << "visit IfAndElse" << endl;
  bool stop = false;
  for (int i = 0; i < children.size(); i++) {
    if (i < children.size() - 1) {
      children[i]->visit(a, stop);
    }

    if (stop || i == children.size() - 1) {
      children[i]->visit(a);
      break;
    }
  }
//  cout << "leave IfAndElse" << endl;
}


/*--------------------------------IfOrElse-----------------------------------*/


IfOrElse::~IfOrElse() {
  delete test;
  delete compound;
}

void IfOrElse::visit(SemanticAnalyzer* a, bool& stop) {
  test->visit(a);
  if (test->getValue() != "0") {
    stop = true;
  }
}

void IfOrElse::visit(SemanticAnalyzer* a) {   // create symbol table
  ScopedSymbolTable* table = new ScopedSymbolTable("ifelse", a->current_level + 1,\
   a->current_scope);
  a->current_scope = table;
  a->current_level += 1;

  compound->visit(a);

  a->current_scope = a->current_scope->enclosing_scope;
  a->current_level -= 1;
}


/*--------------------------------While-----------------------------------*/


While::~While() {
  delete test;
  delete compound;
}

void While::visit(SemanticAnalyzer* a) {   // create symbol table
  //cout << "visit While" << endl;
  ScopedSymbolTable* table = new ScopedSymbolTable("while", a->current_level + 1,\
   a->current_scope);
  a->current_scope = table;
  a->current_level += 1;

  test->visit(a);
  while (test->getValue() != "0") {
    compound->visit(a);
    test->visit(a);
  }

  a->current_scope = a->current_scope->enclosing_scope;
  a->current_level -= 1;
  //cout << "leave While" << endl;
}


/*--------------------------------FunctionDecl-----------------------------------*/


FunctionDecl::~FunctionDecl() {
  delete id;
  for (int i = 0; i < parameters.size(); i++) {
    delete parameters[i];
  }
  delete compound;
}

vector<AST*> FunctionDecl::getParameters() {
  return parameters;
}

AST* FunctionDecl::getCompound() {
  return compound;
}

void FunctionDecl::visit(SemanticAnalyzer* a) {   // create symbol table
  //cout << "visit FunctionDecl" << endl;

  Symbol* s = a->current_scope->LookUp(id->getToken().value, false);
  if (s->name == "") {
    FuntionSymbol *f = new FuntionSymbol(id->getToken(), this);
    a->current_scope->insert(f);
  }
  else {
    cout << "error duplicate function define" << endl;
    exit(0);
  }
  //cout << "leave FunctionDecl" << endl;
}


/*--------------------------------FunctionCall-----------------------------------*/


FunctionCall::~FunctionCall() {
  delete id;
  for (int i = 0; i < parameters.size(); i++) {
    delete parameters[i];
  }
}

void FunctionCall::visit(SemanticAnalyzer* a) {
  //cout << "visit FunctionCall" << endl;

  Symbol* s = a->current_scope->LookUp(id->getToken().value, false);
  if (s->name == "") {
    cout << "undefined function" << endl;
    exit(0);
  }

  ScopedSymbolTable* table = new ScopedSymbolTable("function", a->current_level\
   + 1, a->current_scope);

  a->current_scope = table;
  a->current_level += 1;

  AST* function = s->getTreeNode();


  for (int i = 0; i < parameters.size(); i++) {
    parameters[i]->visit(a);
    function->getParameters()[i]->visit(a, parameters[i]->getValue(), parameters[i]->getValueType(), true);
  }

  function->getCompound()->visit(a);

/*

  for (int i = 0; i < parameters.size(); i++) {
    parameters[i]->visit(a);
  }  */

  a->current_scope = a->current_scope->enclosing_scope;
  a->current_level -= 1;
  //cout << "leave FunctionCall" << endl;
}
