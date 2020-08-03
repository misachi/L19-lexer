#ifndef _TOKENIZER_H
#define _TOKENIZER_H

#include <iostream>
#include <string>
#include <unordered_map>

#define BUFSIZE 4096

// Token types
enum
{
    WHILE = 100,
    ELSE,
    IF,
    DO,
    FOR,
    RETURN,
    SWITCH,
    CASE,
    BREAK,
    DEFAULT,
    CONTINUE,
    TRY,
    CATCH,
    TRUE,
    FALSE,
    NUMBER,
    ID,
    RELOP,
    FLOATNUMBER,
    ASSIGN,
    LT,
    EQ,
    LE,
    GT,
    GE,
    NE,
    ENDTOKEN,
    LP, // left parenthesis
    RP, // right parenthesis
    LB, // left bracket
    RB,  // right bracket
    PUNCT,
    DOUBLEQ, // Double quotes
    MINUS,
    PLUS,
    MULTIPLY,
    DIVIDE,
};

class Token
{
private:
    int type;
    std::unordered_map<int, std::string> token_names{
        {WHILE, "WHILE"},
        {ELSE, "ELSE"},
        {IF, "IF"},
        {DO, "DO"},
        {RETURN, "RETURN"},
        {SWITCH, "SWITCH"},
        {CASE, "CASE"},
        {BREAK, "BREAK"},
        {DEFAULT, "DEFAULT"},
        {CONTINUE, "CONTINUE"},
        {TRY, "TRY"},
        {CATCH, "CATCH"},
        {TRUE, "TRUE"},
        {FALSE, "FALSE"},
        {ASSIGN, "="},
        {LT, "LT"},
        {EQ, "EQ"},
        {LE, "LE"},
        {GT, "GT"},
        {GE, "GE"},
        {NE, "NE"},
        {ID, "ID"},
        {ENDTOKEN, "EOF"},
        {LP, "LP"},
        {RP, "RP"},
        {LB, "LB"},
        {RB, "RB"},
        {FOR, "FOR"},
        {RELOP, "RELOP"},
        {PUNCT, "PUNCT"}
    };

public:
    Token(int n) : type(n){};
    virtual void print_token() { std::cout << "Type: " << get_type_name() << std::endl; };
    int get_type() const { return type; }
    std::unordered_map<int, std::string> get_token_names() { return token_names; }
    virtual std::string get_type_name() { return token_names.at(type);}
    virtual ~Token(){};
};

class NumberToken : public Token
{
private:
    int i_attr;

public:
    NumberToken(int i = NUMBER) : Token(i){};
    NumberToken(int attr, int i = ID) : Token(i), i_attr(attr){};
    void print_token()
    {
        std::cout << "Type: " << get_type_name() << "  Attribute: " << i_attr << std::endl;
    }
    std::string get_type_name() {
        auto token_names = get_token_names();
        int type = get_type();
        auto p = token_names.find(type);
        if (p == token_names.end())
            token_names[type] = i_attr;
        return token_names.at(type);
    }
    int get_attribute() const { return i_attr; };
    void set_attribute(int i) { i_attr = i; }
    ~NumberToken(){};
};

class StringToken : public Token
{
private:
    std::string s_attr;

public:
    StringToken(int i = ID) : Token(i){};
    StringToken(std::string attr, int i = ID) : Token(i), s_attr(attr){};
    void print_token()
    {
        std::cout << "Type: " << get_type_name() << "  Attribute: " << s_attr << std::endl;
    }
    std::string get_attribute() const { return s_attr; };
    void set_attribute(std::string s) { s_attr = s; }
    ~StringToken(){};
};

class FloatToken : public Token
{
private:
    double d_attr;

public:
    FloatToken(int i = FLOATNUMBER) : Token(i){};
    void print_token()
    {
        std::cout << "Type: " << get_type_name() << "  Attribute: " << d_attr << std::endl;
    }
    double get_attribute() const { return d_attr; };
    void set_attribute(double d) { d_attr = d; }
    ~FloatToken(){};
};

#endif
