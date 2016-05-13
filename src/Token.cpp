#include "Token.h"

Token::Token(string v, Token::Type t)
{
    this->value = v;
    this->type = t;
}

Token::Token(char c, Type t)
{
    this->value = c;
    this->type = t;
}

string Token::getValue()
{
    return this->value;
}

void Token::setValue(string v)
{
    this->value = v;
}

Token::Type Token::getType()
{
    return this->type;
}

void Token::setType(Type t)
{
    this->type = t;
}