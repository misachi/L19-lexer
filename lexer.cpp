#include "lexer.h"
#include "util.h"

#include <fstream>
#include <sstream>
#include <cctype>
#include <vector>

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

Token *Lexer::getToken()
{
    char c;
    while (bufferPtr != bufferEnd)
    {
        c = *bufferPtr;
        if (std::isspace(c))
        {
            ignoreWhiteSpace();
            continue;
        }

        if (std::ispunct(c))
        {
            std::string str;
            while (std::ispunct(*bufferPtr))
            {
                switch (*bufferPtr)
                {
                case '(':
                    ++bufferPtr;
                    return new StringToken{"(", LP};
                case ')':
                    ++bufferPtr;
                    return new StringToken{")", RP};
                case '{':
                    ++bufferPtr;
                    return new StringToken{"{", LB};
                case '}':
                    ++bufferPtr;
                    return new StringToken{"}", RB};
                default:
                    str.push_back(*bufferPtr);
                    ++bufferPtr;
                    return new StringToken{str, PUNCT};
                }
            }
        }

        if (c == '=' || c == '<' || c == '>' || c == '!')
        {
            int state = 0;
            while (1)
            {
                switch (state)
                {
                case 0:
                    if (*bufferPtr == '=')
                    {
                        state = 1;
                    } else if (*bufferPtr == '<')
                    {
                        state = 3;
                    } else if (*bufferPtr == '>')
                    {
                        state = 5;
                    } else if (*bufferPtr == '!')
                    {
                        state = 7;
                    }
                    ++bufferPtr;
                    break;
                case 1:
                    if (*bufferPtr == '=') {
                        ++bufferPtr;
                        return new StringToken{"==", RELOP};
                    } else {
                        ++bufferPtr;
                        return new StringToken{"=", ASSIGN};
                    }
                    break;
                case 3:
                    if (*bufferPtr == '=') {
                        ++bufferPtr;
                        return new StringToken{"<=", RELOP};
                    } else
                    {
                        ++bufferPtr;
                        return new StringToken{"<", RELOP};
                    }
                    break;
                case 5:
                    if (*bufferPtr == '=') {
                        ++bufferPtr;
                        return new StringToken{">=", RELOP};
                    } else
                    {
                        ++bufferPtr;
                        return new StringToken{">", RELOP};
                    }
                    break;
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

        if (std::isalpha(c))
        {
            std::string str;
            while (std::isalnum(*bufferPtr) || *bufferPtr == '_')
            {
                str.push_back(*bufferPtr);
                ++bufferPtr;
            }
            auto p = token_names.find(string_to_upper(std::string{str}));
            if (p == token_names.end())
                return new StringToken{str};
            else
                return new StringToken{str, p->second};
        }

        if (std::isdigit(c))
        {
            std::vector<char> ch;
            while (std::isdigit(*bufferPtr))
            {
                ch.push_back(*bufferPtr);
                ++bufferPtr;
            }
            return new NumberToken{std::atoi(ch.data()), NUMBER};
        }
    }
    return new Token{ENDTOKEN};
}
