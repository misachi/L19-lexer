#ifndef _LEXER_H
#define _LEXER_H

#include <string>
#include "tokenizer.h"

using c_iter = std::string::const_iterator;
std::string string_read_file_buffer(std::string filePath);

class Lexer
{
private:
    std::string *inputString;
    c_iter bufferStart;
    c_iter bufferPtr;
    c_iter bufferEnd;
public:
    Lexer(std::string *str);
    Lexer(c_iter start, c_iter ptr, c_iter end);
    Token* getToken();
    void ignoreWhiteSpace();
    StringToken* checkRelop();
    NumberToken* checkInteger();
    FloatToken* checkFloat();
    StringToken* checkString();
    void backup(); // Step back one level from the current location pointed to by bufferPtr
    ~Lexer() {};
};

#endif
