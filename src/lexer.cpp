#include "../Include/lexer.h"
#include "../Include/tokenizer.h"
#include "../Include/util.h"

#include <cctype>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using Lex::Lexer;

Lexer::Lexer(std::string str) {
  file_s.open(str);
  bufferPtr = bufferEnd;
}

Lexer::~Lexer() { file_s.close(); }

void Lexer::ignoreWhiteSpace() {
  while ((bufferPtr != bufferEnd) && isspace(*bufferPtr))
    ++bufferPtr;
}

void Lexer::getline() {
  if (bufferPtr == bufferEnd) {
    std::getline(file_s, line_str);
    bufferPtr = line_str.cbegin();
    bufferEnd = line_str.cend();
  }
}

Token *Lexer::getToken() {
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

  return new Token{ENDTOKEN};
}

StringToken *Lexer::id_token() {
  std::string str;
  while (std::isalnum(*bufferPtr) || *bufferPtr == '_') {
    str.push_back(*bufferPtr);
    ++bufferPtr;
  }
  StringToken *out_str{new StringToken{str}};
  std::unordered_map<std::string, int> u_map = out_str->get_token_names();
  auto p = u_map.find(str);
  if (p == u_map.end()) {
    return out_str;
  } else {
    out_str->set_type(p->second);
    return out_str;
  }
}

NumberToken *Lexer::number_token() {
  std::string str;
  while (std::isdigit(*bufferPtr)) {
    str.push_back(*bufferPtr);
    ++bufferPtr;
  }
  return new NumberToken{std::stoi(str), NUMBER};
}

StringToken *Lexer::delim_token() {
  std::string str{*bufferPtr};
  switch (*(bufferPtr++)) {
  case '"':
    return new StringToken{str, DOUBLEQUOTE};
  case '(':
    return new StringToken{str, LP};
  case ')':
    return new StringToken{str, RP};
  case '{':
    return new StringToken{str, LB};
  case '}':
    return new StringToken{str, RB};
  case ';':
    return new StringToken{str, ENDMARKER};
  default:
    return new StringToken{ERRORTOKEN};
  }
}

StringToken *Lexer::relop_token() {
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
      break;
    case 1:
      if (*bufferPtr == '=') {
        ++bufferPtr;
        return new StringToken{"==", EQ};
      } else {
        return new StringToken{"=", ASSIGN};
      }
    case 3:
      if (*bufferPtr == '=') {
        ++bufferPtr;
        return new StringToken{"<=", LE};
      } else if (*bufferPtr == '<') {
        ++bufferPtr;
        return new StringToken{"<<", LSHIFT};
      } else {
        return new StringToken{"<", LT};
      }
    case 5:
      if (*bufferPtr == '=') {
        ++bufferPtr;
        return new StringToken{">=", GE};
      } else if (*bufferPtr == '>') {
        ++bufferPtr;
        return new StringToken{">>", RSHIFT};
      } else {
        return new StringToken{">", GT};
      }
    case 7:
      if (*bufferPtr == '=') {
        ++bufferPtr;
        return new StringToken{"!=", NE};
      }
      break;
    default:
      break;
    }
  }
}

StringToken *Lexer::op_token() {
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
      break;
    case 1:
      if (*bufferPtr == '=') {
        ++bufferPtr;
        return new StringToken{"-=", MINUSEQUAL};
      } else if (*bufferPtr == '-') {
        ++bufferPtr;
        return new StringToken{"--", DEC};
      } else if (*bufferPtr == '>') {
        ++bufferPtr;
        return new StringToken{"->", RETURN_TYPE};
      } else {
        return new StringToken{"-", MINUS};
      }
    case 3:
      if (*bufferPtr == '=') {
        ++bufferPtr;
        return new StringToken{"+=", PLUSEQUAL};
      } else if (*bufferPtr == '+') {
        ++bufferPtr;
        return new StringToken{"++", INC};
      } else {
        return new StringToken{"+", PLUS};
      }
    case 7:
      if (*bufferPtr == '=') {
        ++bufferPtr;
        return new StringToken{"*=", MULTIPLYEQUAL};
      } else {
        return new StringToken{"*", MULTIPLY};
      }
    case 9:
      if (*bufferPtr == '=') {
        ++bufferPtr;
        return new StringToken{"/=", DIVIDEEQUAL};
      } else {
        return new StringToken{"/", DIVIDE};
      }
    default:
      break;
    }
  }
}
