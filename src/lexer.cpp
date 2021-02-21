#include "../Include/lexer.h"
#include "../Include/tokenizer.h"
#include "../Include/util.h"

#include <cctype>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using Lex::Lexer;
using Lex::Token;

Lexer::Lexer(std::string str) {
  file_s.open(str);
  bufferPtr = bufferEnd;
}

Lexer::~Lexer() { file_s.close(); }

void Lexer::ignoreWhiteSpace() {
  while ((bufferPtr != bufferEnd) && isspace(*bufferPtr)) {
    ++bufferPtr;
    ++token.col;
  }
}

void Lexer::getline() {
  if (bufferPtr == bufferEnd) {
    std::getline(file_s, line_str);
    ++token.line;
    token.col = 1;
    bufferPtr = line_str.cbegin();
    bufferEnd = line_str.cend();
  }
}

Token Lexer::getToken() {
  char c;

next:
  getline();
  while (bufferPtr != bufferEnd) {
    c = *bufferPtr;
    if (std::isspace(c)) {
      ignoreWhiteSpace();
      continue;
    }
    if (std::ispunct(c)) {
      if (c == '=' || c == '<' || c == '>' || c == '!') {
        return relop_token();
      } else if (c == '+' || c == '-' || c == '*' || c == '/') {
        return op_token();
      }
      return delim_token();
    }

    if (std::isalpha(c)) {
      return id_token();
    }

    if (std::isdigit(c)) {
      return number_token();
    }
    getline();
  }

  if (!file_s.eof())
    goto next;
  token.token = new Tokenize::Token{Tokenize::ENDTOKEN};;
  return token;
}

Token Lexer::id_token() {
  std::string str;
  while (std::isalnum(*bufferPtr) || *bufferPtr == '_') {
    str.push_back(*bufferPtr);
    ++bufferPtr;
    ++token.col;
  }
  auto *out_str{new Tokenize::StringToken{str}};
  std::unordered_map<std::string, int> u_map = out_str->get_token_names();
  auto p = u_map.find(str);

  if (p != u_map.end())
    out_str->set_type(p->second);

  token.token = out_str;
  return token;
}

Token Lexer::number_token() {
  std::string str;
  while (std::isdigit(*bufferPtr)) {
    str.push_back(*bufferPtr);
    ++bufferPtr;
    ++token.col;
  }
  token.token = new Tokenize::NumberToken{std::stoi(str), Tokenize::NUMBER};
  return token;
}

Token Lexer::delim_token() {
  std::string str{*bufferPtr};
  Tokenize::Token *tok = nullptr;
  switch (*(bufferPtr++)) {
  case '"':
    tok = new Tokenize::StringToken{str, Tokenize::DOUBLEQUOTE};
    break;
  case '(':
    tok = new Tokenize::StringToken{str, Tokenize::LP};
    break;
  case ')':
    tok = new Tokenize::StringToken{str, Tokenize::RP};
    break;
  case '{':
    tok = new Tokenize::StringToken{str, Tokenize::LB};
    break;
  case '}':
    tok = new Tokenize::StringToken{str, Tokenize::RB};
    break;
  case ';':
    tok = new Tokenize::StringToken{str, Tokenize::ENDMARKER};
    break;
  default:
    tok = new Tokenize::StringToken{str, Tokenize::ERRORTOKEN};
    token.token = tok;
    panic();
    break;
  }
  token.token = tok;
  ++token.col;
  return token;
}

Token Lexer::relop_token() {
  int state = 0;
  while (1) {
    switch (state) {
    case 0:
      if (*bufferPtr == '=') {
        state = 1;
      } else if (*bufferPtr == '<') {
        state = 3;
      } else if (*bufferPtr == '>') {
        state = 5;
      } else if (*bufferPtr == '!') {
        state = 7;
      }
      ++bufferPtr;
      ++token.col;
      break;
    case 1:
      if (*bufferPtr == '=') {
        ++bufferPtr;
        ++token.col;
        token.token = new Tokenize::StringToken{"==", Tokenize::EQ};
      } else {
        token.token = new Tokenize::StringToken{"=", Tokenize::ASSIGN};
      }
      return token;
    case 3:
      if (*bufferPtr == '=') {
        ++bufferPtr;
        ++token.col;
        token.token = new Tokenize::StringToken{"<=", Tokenize::LE};
      } else if (*bufferPtr == '<') {
        ++bufferPtr;
        ++token.col;
        token.token = new Tokenize::StringToken{"<<", Tokenize::LSHIFT};
      } else {
        token.token = new Tokenize::StringToken{"<", Tokenize::LT};
      }
      return token;
    case 5:
      if (*bufferPtr == '=') {
        ++bufferPtr;
        ++token.col;
        token.token = new Tokenize::StringToken{">=", Tokenize::GE};
      } else if (*bufferPtr == '>') {
        ++bufferPtr;
        ++token.col;
        token.token = new Tokenize::StringToken{">>", Tokenize::RSHIFT};
      } else {
        token.token = new Tokenize::StringToken{">", Tokenize::GT};
      }
      return token;
    case 7:
      if (*bufferPtr == '=') {
        ++bufferPtr;
        ++token.col;
        token.token = new Tokenize::StringToken{"!=", Tokenize::NE};
        return token;
      }
      break;
    default:
      break;
    }
  }
}

Token Lexer::op_token() {
  int state = 0;
  while (1) {
    switch (state) {
    case 0:
      if (*bufferPtr == '-') {
        state = 1;
      } else if (*bufferPtr == '+') {
        state = 3;
      } else if (*bufferPtr == '*') {
        state = 7;
      } else if (*bufferPtr == '/') {
        state = 9;
      }

      ++bufferPtr;
      ++token.col;
      break;
    case 1:
      if (*bufferPtr == '=') {
        ++bufferPtr;
        ++token.col;
        token.token = new Tokenize::StringToken{"-=", Tokenize::MINUSEQUAL};
      } else if (*bufferPtr == '-') {
        ++bufferPtr;
        ++token.col;
        token.token = new Tokenize::StringToken{"--", Tokenize::DEC};
      } else if (*bufferPtr == '>') {
        ++bufferPtr;
        ++token.col;
        token.token = new Tokenize::StringToken{"->", Tokenize::RETURN_TYPE};
      } else {
        token.token = new Tokenize::StringToken{"-", Tokenize::MINUS};
      }
      return token;
    case 3:
      if (*bufferPtr == '=') {
        ++bufferPtr;
        ++token.col;
        token.token = new Tokenize::StringToken{"+=", Tokenize::PLUSEQUAL};
      } else if (*bufferPtr == '+') {
        ++bufferPtr;
        ++token.col;
        token.token = new Tokenize::StringToken{"++", Tokenize::INC};
      } else {
        token.token = new Tokenize::StringToken{"+", Tokenize::PLUS};
      }
      return token;
    case 7:
      if (*bufferPtr == '=') {
        ++bufferPtr;
        ++token.col;
        token.token = new Tokenize::StringToken{"*=", Tokenize::MULTIPLYEQUAL};
      } else {
        token.token = new Tokenize::StringToken{"*", Tokenize::MULTIPLY};
      }
      return token;
    case 9:
      if (*bufferPtr == '=') {
        ++bufferPtr;
        ++token.col;
        token.token = new Tokenize::StringToken{"/=", Tokenize::DIVIDEEQUAL};
      } else {
        token.token = new Tokenize::StringToken{"/", Tokenize::DIVIDE};
      }
      return token;
    default:
      break;
    }
  }
}
