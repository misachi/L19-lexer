#include <sstream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <lexer.h>
#include <tokenizer.h>

using Lex::Lexer;

int main(int argc, char **args)
{
    if (argc < 2)
        throw std::runtime_error{"No file to parse"};

    std::string str{args[1]};
    Lexer lex{str};

    auto tok = lex.getToken();
    while (tok->get_type() != ENDTOKEN)
    {
        tok->print_token();
        delete tok;
        tok = lex.getToken();
    }
    delete tok;
}

