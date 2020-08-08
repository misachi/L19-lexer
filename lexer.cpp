#include "lexer.h"
#include "tokenizer.h"
#include "util.h"

#include <cctype>
#include <vector>

Lexer::Lexer(std::string *str) {
  inputString = str;
  bufferStart = inputString->cbegin();
  bufferPtr = inputString->cbegin();
  bufferEnd = inputString->cend(); // bufferEnd == EOF
}

Lexer::~Lexer() { delete inputString; }

void Lexer::ignoreWhiteSpace() {
  while ((bufferPtr != bufferEnd) && isspace(*bufferPtr))
    ++bufferPtr;
  bufferStart = bufferPtr;
}

Token *Lexer::getToken() {
  char c;
  while (bufferPtr != bufferEnd) {
    c = *bufferPtr;
    if (std::isspace(c)) {
      ignoreWhiteSpace();
      continue;
    }

    if (std::ispunct(c)) {
      if (c == '=' || c == '<' || c == '>' || c == '!') {
        return relop_token();
      }
      return delim_token();
    }

    if (std::isalpha(c)) {
      return id_token();
    }

    if (std::isdigit(c)) {
      return number_token();
    }
  }
  return new Token{ENDTOKEN};
}

StringToken *Lexer::id_token() {
  std::string str;
  while (std::isalnum(*bufferPtr) || *bufferPtr == '_') {
    str.push_back(*bufferPtr);
    ++bufferPtr;
  }
  StringToken *out_str = new StringToken{str};
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
  switch (*bufferPtr) {
  case '(':
    ++bufferPtr;
    return new StringToken{str, PUNCT};
  case ')':
    ++bufferPtr;
    return new StringToken{str, PUNCT};
  case '{':
    ++bufferPtr;
    return new StringToken{str, PUNCT};
  case '}':
    ++bufferPtr;
    return new StringToken{str, PUNCT};
  default:
    ++bufferPtr;
    return new StringToken{str, PUNCT};
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
        return new StringToken{"==", RELOP};
      } else {
        return new StringToken{"=", ASSIGN};
      }
    case 3:
      if (*bufferPtr == '=') {
        ++bufferPtr;
        return new StringToken{"<=", RELOP};
      } else {
        return new StringToken{"<", RELOP};
      }
    case 5:
      if (*bufferPtr == '=') {
        ++bufferPtr;
        return new StringToken{">=", RELOP};
      } else {
        return new StringToken{">", RELOP};
      }
    case 7:
      if (*bufferPtr == '=') {
        ++bufferPtr;
        return new StringToken{"!=", RELOP};
      }
      break;
    default:
      break;
    }
  }
}