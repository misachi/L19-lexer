#ifndef _LEXER_H
#define _LEXER_H

#include <tokenizer.h>

#include <sstream>
#include <string>
#include <fstream>
#include <stdexcept>

namespace Lex {
using c_iter = std::string::const_iterator;

struct Token {
  Token() : token(nullptr) {};
  Token(Tokenize::Token *tok) : token(tok) {};
  Tokenize::Token *token;
  int line;
  int col;
};

class Lexer {
private:
  std::ifstream file_s;
  std::string line_str;
  c_iter bufferPtr;
  c_iter bufferEnd;
  Token token;

public:
  Lexer(std::string str);
  void panic() {
    token.token->print_token();
    std::ostringstream os;
    os << "Invalid token on line " << token.line << " " << "column " << token.col << std::endl;
    throw std::runtime_error(os.str());
  };
  Token peekToken();
  void getline();
  Token getToken();
  void ignoreWhiteSpace();
  Token relop_token();
  Token number_token();
  Token float_token();
  Token id_token();
  Token delim_token();
  Token op_token();
  Token logic_token();
  ~Lexer();
};
} // namespace Lex

#endif
