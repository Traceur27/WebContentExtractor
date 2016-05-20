#include "Token.hpp"

Token::Token(string v, Token::Type t, Position p)
{
    this->value = v;
    this->type = t;
    this->position = p;
}

Token::Token(char c, Type t, Position p)
{
    this->value = c;
    this->type = t;
    this->position = p;
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

Token &Token::operator=(Token token)
{
    this->value = token.value;
    this->type = token.type;
    this->position = token.position;
    return *this;
}



/*std::ostream& operator<<( std::ostream& os, const Token::Type& type )
{
    switch(type)
    {
        case Token::OPENTAGSYMBOL: os << "OPENTAGSYMBOL"; break;
        case Token::CLOSETAGSYMBOL: os << "CLOSETAGSYMBOL"; break;
        case Token::SLASHCLOSETAGSYMBOL: os << "SLASHCLOSETAGSYMBOL"; break;
        case Token::SLASHOPENTAGSYMBOL: os << "SLASHOPENTAGSYMBOL"; break;
        case Token::EQUALS: os << "EQUALS"; break;
        case Token::SINGLEQUOTEDSTRING: os << "SINGLEQUOTEDSTRING"; break;
        case Token::DOUBLEQUOTEDSTRING: os << "DOUBLEQUOTEDSTRING"; break;
        case Token::EXCLAMATION: os << "EXCLAMATION"; break;
        case Token::COMMENT: os << "COMMENT"; break;
        case Token::LIMITEDSTRING: os << "LIMITEDSTRING"; break;
        case Token::STRING: os << "STRING"; break;
        case Token::EMPTY: os << "EMPTY"; break;
    }
    return os;
} */