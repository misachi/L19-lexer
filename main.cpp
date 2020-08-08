#include <sstream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "lexer.h"
#include "tokenizer.h"

static std::string *string_read_file_buffer(std::string filePath);

static inline void printToken(Token *tok)
{
    tok->print_token();
    delete tok;
}

int main(int argc, char **args)
{
    if (argc < 2)
        throw std::length_error("Argument Count Error");
    std::string *path = string_read_file_buffer(args[1]);
    Lexer lex {path};

    Token *tok = lex.getToken();
    while (tok->get_type() != ENDTOKEN)
    {
        printToken(tok);
        tok = lex.getToken();
    }
    delete tok;
    
}

static std::string *string_read_file_buffer(std::string filePath)
{
    std::ifstream ifs{filePath};
    std::ostringstream oss{};
    oss << ifs.rdbuf();
    std::string *str = new std::string{oss.str()};
    ifs.close();
    return str;
}
