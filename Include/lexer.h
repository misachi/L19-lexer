#ifndef _LEXER_H
#define _LEXER_H

#include <tokenizer.h>

#include <fstream>

namespace Lex {
using c_iter = std::string::const_iterator;

class Lexer {
private:
  std::ifstream file_s;
  std::string line_str;
  c_iter bufferPtr;
  c_iter bufferEnd;

public:
  Lexer(std::string str);
  void getline();
  Token *getToken();
  void ignoreWhiteSpace();
  StringToken *relop_token();
  NumberToken *number_token();
  FloatToken *float_token();
  StringToken *id_token();
  StringToken *delim_token();
  StringToken *op_token();
  StringToken *logic_token();
  ~Lexer();
};
} // namespace Lex

#endif
