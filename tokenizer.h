#ifndef _TOKENIZER_H
#define _TOKENIZER_H

#include <iostream>
#include <string>
#include <unordered_map>

using c_iter = std::string::const_iterator;

// Token types
enum {
  WHILE = 100,
  ELSE,
  IF,
  DO,
  FOR,
  RETURN,
  SWITCH,
  CASE,
  BREAK,
  DEFAULT,
  CONTINUE,
  TRY,
  CATCH,
  TRUE,
  FALSE,
  NUMBER,
  ID,
  RELOP,
  FLOATNUMBER,
  ASSIGN,
  LT,
  EQ,
  LE,
  GT,
  GE,
  NE,
  ENDTOKEN,
  LP, // left parenthesis
  RP, // right parenthesis
  LB, // left bracket
  RB, // right bracket
  PUNCT,
  DOUBLEQ, // Double quotes
  MINUS,
  PLUS,
  MULTIPLY,
  DIVIDE,
  FLOAT,
  ERRORTOKEN,
};

class Token {
private:
  int type;
  std::unordered_map<std::string, int> token_names{
      {"while", WHILE},
      {"else", ELSE},
      {"for", FOR},
      {"if", IF},
      {"do", DO},
      {"return", RETURN},
      {"switch", SWITCH},
      {"case", CASE},
      {"break", BREAK},
      {"default", DEFAULT},
      {"continue", CONTINUE},
      {"try", TRY},
      {"catch", CATCH},
      {"true", TRUE},
      {"false", FALSE},
  };

public:
  Token(int n) : type(n){};
  virtual void print_token() const {};
  int get_type() const { return type; }
  std::unordered_map<std::string, int> get_token_names() const {
    return token_names;
  };
  void set_type(int tp) { type = tp; };
  std::string get_type_name() const { return type_name(type); }
  static std::string type_name(int name = ERRORTOKEN) {
    switch (name) {
    case WHILE:
      return "WHILE";
    case ELSE:
      return "ELSE";
    case IF:
      return "IF";
    case DO:
      return "DO";
    case RETURN:
      return "RETURN";
    case BREAK:
      return "BREAK";
    case DEFAULT:
      return "DEFAULT";
    case CONTINUE:
      return "CONTINUE";
    case TRY:
      return "TRY";
    case CATCH:
      return "CATCH";
    case TRUE:
      return "TRUE";
    case FALSE:
      return "FALSE";
    case PUNCT:
      return "PUNCT";
    case RELOP:
      return "RELOP";
    case NUMBER:
      return "NUMBER";
    case FLOAT:
      return "FLOAT";
    case FOR:
      return "FOR";
    case ID:
      return "ID";
    case ASSIGN:
      return "ASSIGN";
    default:
      return "ERRORTOKEN";
    }
  }
  virtual ~Token(){};
};

class NumberToken : public Token {
private:
  int i_attr;

public:
  NumberToken(int i = NUMBER) : Token(i){};
  NumberToken(int attr, int i = ID) : Token(i), i_attr(attr){};
  void print_token() const {
    std::cout << "Type: " << get_type_name() << "  Attribute: " << i_attr
              << std::endl;
  };
  int get_attribute() const { return i_attr; };
  void set_attribute(int i) { i_attr = i; }
  ~NumberToken(){};
};

class StringToken : public Token {
private:
  std::string s_attr;

public:
  StringToken(int i = ID) : Token(i){};
  StringToken(std::string attr, int i = ID) : Token(i), s_attr(attr){};
  void print_token() const {
    std::cout << "Type: " << get_type_name() << "  Attribute: " << s_attr
              << std::endl;
  }
  std::string get_attribute() const { return s_attr; };
  void set_attribute(std::string s) { s_attr = s; }
  ~StringToken(){};
};

class FloatToken : public Token {
private:
  double d_attr;

public:
  FloatToken(int i = FLOATNUMBER) : Token(i){};
  void print_token() const {
    std::cout << "Type: " << get_type_name() << "  Attribute: " << d_attr
              << std::endl;
  }
  double get_attribute() const { return d_attr; };
  void set_attribute(double d) { d_attr = d; }
  ~FloatToken(){};
};

#endif
