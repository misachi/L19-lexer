#ifndef _LEXER_H
#define _LEXER_H

#include "tokenizer.h"

using c_iter = std::string::const_iterator;
std::string *string_read_file_buffer(std::string filePath);

class Lexer
{
private:
    std::string *inputString;
    c_iter bufferStart;
    c_iter bufferPtr;
    c_iter bufferEnd;
    std::unordered_map<std::string, int> token_names{
        {"WHILE", WHILE},
        {"ELSE", ELSE},
        {"IF", IF},
        {"DO", DO},
        {"RETURN", RETURN},
        {"SWITCH", SWITCH},
        {"CASE", CASE},
        {"BREAK", BREAK},
        {"DEFAULT", DEFAULT},
        {"CONTINUE", CONTINUE},
        {"TRY", TRY},
        {"CATCH", CATCH},
        {"TRUE", TRUE},
        {"FALSE", FALSE},
        {"PUNCT", PUNCT},
        {"<", LT},
        {"==", EQ},
        {"<=", LE},
        {">", GT},
        {">=", GE},
        {"!=", NE},
        {"(", LP},
        {")", RP},
        {"{", LB},
        {"}", RB},
        {"=", ASSIGN}
    };

public:
    Lexer(std::string *str);
    Token *getToken();
    void ignoreWhiteSpace();
    StringToken *getRelopToken();
    NumberToken *getIntegerToken();
    FloatToken *getFloatToken();
    StringToken *getStringToken();
    ~Lexer();
};

#endif
