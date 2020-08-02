#include "lexer.h"
#include "util.h"

#include <fstream>
#include <sstream>
#include <cctype>

std::string *string_read_file_buffer(std::string filePath)
{
    std::ifstream ifs{filePath};
    std::ostringstream oss{};
    oss << ifs.rdbuf();
    std::string *str = new std::string{oss.str()};
    ifs.close();
    return str;
}

Lexer::Lexer(std::string *str)
{
    inputString = str;
    bufferStart = inputString->cbegin();
    bufferPtr = inputString->cbegin();
    bufferEnd = inputString->cend(); // bufferEnd == EOF
}

Lexer::~Lexer()
{
    delete inputString;
}

void Lexer::ignoreWhiteSpace()
{
    while ((bufferPtr != bufferEnd) && isspace(*bufferPtr))
        ++bufferPtr;
    bufferStart = bufferPtr;
}

void Lexer::backup()
{
    if (bufferPtr != bufferEnd)
        ++bufferPtr;
}

Token *Lexer::getToken()
{
    char c;
    while (bufferPtr != bufferEnd)
    {
        c = *bufferPtr;
        if (isspace(c))
        {
            ignoreWhiteSpace();
            continue;
        }

        if (isalpha(c))
        {
            std::string str;
            while (isalnum(*bufferPtr))
            {
                str.push_back(*bufferPtr);
                ++bufferPtr;
            }
            backup();
            auto p = token_names.find(string_to_upper(std::string{str}));
            if (p == token_names.end())
                return new StringToken{str};
            else
                return new StringToken{str, p->second};
        }

        if (isdigit(c))
        {
            while (isdigit(*bufferPtr))
            {
                /* code */
            }
        }
    }
    return new Token{ENDTOKEN};
}
