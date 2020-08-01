#ifndef _TOKENIZER_H
#define _TOKENIZER_H

#include <iostream>
#include <string>

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
    FLOAT,
    LT,
    EQ,
    LE,
    GT,
    GE,
    NE,
};

class Token
{
private:
    int type;
public:
    Token(int n) : type(n) {};
    virtual void print_token() const = 0;
    int get_type() const { return type; }
    virtual ~Token() {};
};

class NumberToken : public Token
{
private:
    int i_attr;
public:
    NumberToken(int i=NUMBER) : Token(i) {};
    void print_token() const{
         std::cout << "Type: " << get_type() << "\nAttribute: " << i_attr << std::endl; 
    }
    int get_attribute() const { return i_attr; };
    void set_attribute(int i) { i_attr = i; }
    ~NumberToken() {};
};

class StingToken : public Token
{
private:
    std::string s_attr;
public:
    StingToken(int i=ID) : Token(i) {};
    void print_token() const{
         std::cout << "Type: " << get_type() << "\nAttribute: " << s_attr << std::endl; 
    }
    std::string get_attribute() const { return s_attr; };
    void set_attribute(std::string s) { s_attr = s; }
    ~StingToken() {};
};

class FloatToken : public Token
{
private:
    double d_attr;
public:
    FloatToken(int i=FLOAT) : Token(i) {};
    void print_token() const{
         std::cout << "Type: " << get_type() << "\nAttribute: " << d_attr << std::endl; 
    }
    double get_attribute() const { return d_attr; };
    void set_attribute(double d) { d_attr = d; }
    ~FloatToken() {};
};

#endif