#include "lexer.h"

#include <string>

void printToken(Token *tok) {
    tok->print_token();
    // std::cout << dynamic_cast<StringToken *>(tok)->get_attribute() << std::endl;
    delete tok;
}

int main(int argc, char **args)
{
    std::string *path = string_read_file_buffer("foo.txt");
    Lexer lex {path};
    printToken(lex.getToken());
    printToken(lex.getToken());
    printToken(lex.getToken());
    printToken(lex.getToken());
}