#include "lexer.h"

#include <string>

void printToken(Token *tok) {
    tok->print_token();
    delete tok;
}

int main(int argc, char **args)
{
    std::string *path = string_read_file_buffer("foo.txt");
    Lexer lex {path};

    Token *tok = lex.getToken();
    while (tok->get_type() != ENDTOKEN)
    {
        printToken(tok);
        tok = lex.getToken();
    }
    delete tok;
    
}