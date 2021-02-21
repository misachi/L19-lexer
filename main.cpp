#include <stdexcept>
#include <string>

#include "Include/lexer.h"
#include "Include/tokenizer.h"

using Lex::Lexer;

int main(int argc, char **args)
{
    if (argc < 2)
        throw std::runtime_error{"No file to parse"};

    std::string str{args[1]};
    Lexer lex{str};

    auto tok = lex.getToken();
    while (tok.token->get_type() != Tokenize::ENDTOKEN)
    {
        tok.token->print_token();
        delete tok.token;
        tok = lex.getToken();
    }
    delete tok.token;
}

