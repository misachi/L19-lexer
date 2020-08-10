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
  MINUS,
  PLUS,
  MULTIPLY,
  DIVIDE,
  MINUSEQUAL,
  PLUSEQUAL,
  MULTIPLYEQUAL,
  DIVIDEEQUAL,
  FLOAT,
  ERRORTOKEN,
  ENDMARKER,
  DOUBLEQUOTE,
  OPERATOR,
  INC,
  DEC,
  LOGICAL_AND,
  LOGICAL_OR,
  LSHIFT,
  RSHIFT,
  FUNC,
  RETURN_TYPE,
};

class Token {
public:
  Token(int n) : type(n){};
  virtual void print_token() const {};
  int get_type() const { return type; }
  std::unordered_map<std::string, int> get_token_names() const {
    return keyword_tokens;
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
    case LP:
        return "LP";
    case RP:
        return "RP";
    case LB:
        return "LB";
    case RB:
        return "RB";
    case ENDMARKER:
      return "ENDMARKER";
    case LT:
        return "LT";
    case EQ:
        return "EQ";
    case LE:
        return "LE";
    case GT:
        return "GT";
    case GE:
        return "GE";
    case NE:
      return "NE";
    case MINUS:
        return "MINUS";
    case PLUS:
        return "PLUS";
    case MULTIPLY:
        return "MULTIPLY";
    case MINUSEQUAL:
        return "MINUSEQUAL";
    case PLUSEQUAL:
        return "PLUSEQUAL";
    case MULTIPLYEQUAL:
        return "MULTIPLYEQUAL";
    case DIVIDEEQUAL:
        return "DIVIDEEQUAL";
    case DIVIDE:
        return "DIVIDE";
    case INC:
        return "INCR";
    case DEC:
        return "DECR";
    case LOGICAL_AND:
        return "LOGICAL_AND";
    case LOGICAL_OR:
        return "LOGICAL_OR";
    case LSHIFT:
        return "LSHIFT";
    case RSHIFT:
        return "RSHIFT";
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
    case FUNC:
      return "FUNC";
    case RETURN_TYPE:
      return "RETURN_TYPE";
    default:
      return "ERRORTOKEN";
    }
  }
  virtual ~Token(){};

private:
  int type;
  std::unordered_map<std::string, int> keyword_tokens{
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
      {"func", FUNC},
  };
};

class NumberToken : public Token {
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
private:
  int i_attr;
};

class StringToken : public Token {
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
private:
  std::string s_attr;
};

class FloatToken : public Token {
public:
  FloatToken(int i = FLOATNUMBER) : Token(i){};
  void print_token() const {
    std::cout << "Type: " << get_type_name() << "  Attribute: " << d_attr
              << std::endl;
  }
  double get_attribute() const { return d_attr; };
  void set_attribute(double d) { d_attr = d; }
  ~FloatToken(){};
private:
  double d_attr;
};

#endif
