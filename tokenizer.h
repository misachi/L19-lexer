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
    LT,
    EQ,
    LE,
    GT,
    GE,
    NE,
    ENDTOKEN
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
        {LT, "<"},
        {EQ, "=="},
        {LE, "<="},
        {GT, ">"},
        {GE, ">="},
        {NE, "!="},
        {ID, "ID"},
        {ENDTOKEN, "EOF"}};

public:
    Token(int n) : type(n){};
    virtual void print_token() const { std::cout << "Type: " << get_type_name() << std::endl; };
    int get_type() const { return type; }
    std::string get_type_name() const { return token_names.at(type); }
    virtual ~Token(){};
};

class NumberToken : public Token
{
private:
    int i_attr;

public:
    NumberToken(int i = NUMBER) : Token(i){};
    void print_token() const
    {
        std::cout << "Type: " << get_type_name() << "  Attribute: " << i_attr << std::endl;
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
    void print_token() const
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
    void print_token() const
    {
        std::cout << "Type: " << get_type_name() << "  Attribute: " << d_attr << std::endl;
    }
    double get_attribute() const { return d_attr; };
    void set_attribute(double d) { d_attr = d; }
    ~FloatToken(){};
};

#endif
