#include "tokenizer.h"
#include "lexer.h"

#include <string>
#include <fstream>
#include <sstream>

std::string* string_read_file_buffer(std::string filePath)
{
    std::ifstream ifs {filePath};
    std::ostringstream oss {};
    oss << ifs.rdbuf();
    std::string *str = new std::string{oss.str()};
    ifs.close();
    return str;
}

Lexer::Lexer(std::string *str) {
    inputString = str;
    bufferStart = inputString->cbegin();
    bufferPtr = inputString->cbegin();
    bufferEnd = --inputString->cend();  // bufferEnd == EOF
}
Lexer::Lexer(c_iter start, c_iter ptr, c_iter end) : bufferStart(start), bufferPtr(ptr), bufferEnd(end) {}

Lexer::~Lexer() {
    delete inputString;
}

void Lexer::ignoreWhiteSpace() {
    while ((bufferPtr != bufferEnd) && 
            (*bufferPtr == ' ' ||
            *bufferPtr == '\n' ||
            *bufferPtr == '\t' || 
            *bufferPtr == '\r')
        )
    {

        ++bufferPtr;
    }
    bufferStart = bufferPtr;
}

void Lexer::backup() {
    if(bufferPtr != bufferEnd)
        --bufferPtr;
}