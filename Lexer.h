#ifndef LEXER_H
#define	LEXER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>

using namespace std;

enum TokenType {
  PLUS,
  MINUS,
  MUL,
  DIV,
  LESS,
  GREAT,
  LPAREN,
  RPAREN,
  SEMI,
  COMMA,
  ASSIGN,
  LBRACE,
  RBRACE,
  FUNCTION,
  ECHO,
  BEGIN,
  END,
  AND,
  OR,
  EQ,
  NE,
  IF,
  ELSE,
  WHILE,
  RETURN,
  VARID,
  FUNCID,
  INTEGER_CONST,
  FLOAT_CONST,
  STRING_CONST,
  INTEGER,
  FLOAT,
  STRING,
  EF
};

class Token {
  public:
    TokenType type;
    string value;
    int row;
    int column;

    Token();
    Token(TokenType t, string v, int row = 0, int column = 0);
    void assign(TokenType t, string v, int row, int column);
    Token& operator=(const Token& t);
    void print();

    friend bool operator!=(const Token& l, const Token& r);
};

class Lexer {
  public:
    string text;
    bool end;
    int pos;
    char current_char;
    int row;
    int column;

    Lexer(FILE * fp);
    void advance();
    char peekChar();
    string peekString();
    void skip();
    Token findNumber();
    Token findString();
    Token findId();
    Token get_next_token();
};

#endif
