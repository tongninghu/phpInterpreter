#include <string>
#include <cctype>
#include "Lexer.h"

using namespace std;

unordered_map<string, TokenType> ReservedWords {
  {"+", PLUS},
  {"-", MINUS},
  {"*", MUL},
  {"/", DIV},
  {"<", LESS},
  {">", GREAT},
  {"(", LPAREN},
  {")", RPAREN},
  {";", SEMI},
  {",", COMMA},
  {"=", ASSIGN},
  {"{", LBRACE},
  {"}", RBRACE},
  {"<?php", BEGIN},
  {"==", EQ},
  {"!=", NE},
  {"?>", END},
  {"function", FUNCTION},
  {"echo", ECHO},
  {"and", AND},
  {"or", OR},
  {"if", IF},
  {"else", ELSE},
  {"while", WHILE},
  {"return", RETURN}
};

Token::Token() {
  type = EF;
  value = "";
  row = 0;
  column = 0;
}

Token::Token(TokenType t, string v, int row, int column) {
  type = t;
  value = v;
  this->row = row;
  this->column = column;
}

void Token::assign(TokenType t, string v, int row, int column) {
  type = t;
  value = v;
  this->row = row;
  this->column = column;
}

Token& Token::operator=(const Token& t) {
  this->type = t.type;
  this->value = t.value;
  this->row = t.row;
  this->column = t.column;
  return *this;
}

void Token::print() {
  cout << "TokenType: " << type << " with value: " << value << ", row: " <<\
    row << ", column: " << column <<endl;
}

bool operator!=(const Token& l, const Token& r) {
    if (l.type != r.type || l.value != r.value) return true;
    return false;
}


Lexer::Lexer(FILE * fp) {
  fseek(fp, 0, SEEK_END);
  size_t len = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  text.resize(len);
  fread(&text[0], 1, len, fp);
  fclose(fp);

  pos = 0;
  current_char = text[pos];
  end = false;
  row = 0;
  column = 0;
}

void Lexer::advance() {
  if (!end) {
    current_char = text[++pos];
    if (current_char == '\n') {
      row++;
      column = 0;
    }
    column++;
  }
  if (pos == text.size() - 1) {
    end = true;
  }
}

char Lexer::peekChar() {
  int p = pos + 1;
  return text[p];
}

string Lexer::peekString() {
  string s = text.substr(pos, 5);
  return s;
}

void Lexer::skip() {
  while (!end && (current_char == ' ' || current_char == '\n' ||\
    current_char == '\t' || current_char == '\r')) {
    advance();
  }
}

Token Lexer::findNumber() {
  int n = 0;
  string s;
  Token t;
  while (!end && (isdigit(current_char) || current_char == '.')) {
    s += current_char;
    if (current_char == '.') {
      if (n == 1) {
        cout << "error number with row = " << row << " and col = " << column << endl;
        exit;
      }
      else {
        n++;
      }
    }
    advance();
  }
  if (n== 0) {
    t.assign(INTEGER_CONST, s, row, column);
    return t;
  }
  else {
    t.assign(FLOAT_CONST, s, row, column);
    return t;
  }
}

Token Lexer::findString() {
  string s;
  int n = 0;
  advance();
  while (!end && current_char != '"') {
    s += current_char;
    advance();
  }
  if (current_char == '"') advance();
  else {
    cout << "error string with row = " << row << " and col = " << column << endl;
    exit;
  }
  Token t(STRING_CONST, s, row, column);
  return t;
}

Token Lexer::findId() {
  Token t;
  string s;
  int n = 0;
  while (!end && (isalnum(current_char) || current_char == '$' && n == 0)) {
    if (current_char == '$') n++;
    s += current_char;
    advance();
  }

  if (ReservedWords.find(s) != ReservedWords.end()) {
    t.assign(ReservedWords[s], s, row, column);
    return t;
  }

  if (s[0] == '$') {
    t.assign(VARID, s, row, column);
    return t;
  }

  t.assign(FUNCID, s, row, column);
  return t;
}

Token Lexer::get_next_token() {
  Token t;
  if (!end) {

    if (current_char == ' ' || current_char == '\n' || current_char == '\t' ||\
      current_char == '\r') {
      skip();
    }

    if (isdigit(current_char)) return findNumber();

    if (current_char == '"') return findString();

    if (isalpha(current_char) || current_char == '$') return findId();

    if (current_char == '<' && text.size() > pos + 4 && peekString() == "<?php") {
      int n = 5;
      while (n-- > 0) {
        advance();
      }
      t.assign(BEGIN, "<?php", row, column);
      return t;
    }

    if (current_char == '?' && !end && peekChar() == '>') {
        advance();
        advance();
        t.assign(END, "?>", row, column);
        return t;
    }

    if (current_char == '=' && !end && peekChar() == '=') {
        advance();
        advance();
        t.assign(EQ, "==", row, column);
        return t;
    }

    if (current_char == '!' && !end && peekChar() == '=') {
        advance();
        advance();
        t.assign(NE, "!=", row, column);
        return t;
    }

    string s(1, current_char);

    if (ReservedWords.find(s) != ReservedWords.end()) {
      t.assign(ReservedWords[s], s, row, column);
      advance();
      return t;
    }
    cout << "error token with row = " << row << " and col = " << column << endl;
    exit;
  }
  return t;
}
