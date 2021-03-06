#ifndef WEB_CONTENT_EXTRACTOR_TOKEN_H
#define WEB_CONTENT_EXTRACTOR_TOKEN_H

#include <string>
#include <iostream>

using std::string;


class Position
{
    int line;
    int column;

public:
    Position(int l = 1, int c = 1) {this->line = l; this->column = c; }
    void setPosition(int l, int c) {this->line = l; this->column = c;}
    int getLine() {return this->line; }
    int getColumn() {return this->column; }
    void moveRight() {this->column++;}
    void moveDown() {this->line ++; this->column = 1;}
};


class Token
{
public:
    enum Type {OPENTAGSYMBOL, CLOSETAGSYMBOL, SLASHCLOSETAGSYMBOL, SLASHOPENTAGSYMBOL, EQUALS, SINGLEQUOTEDSTRING,
               DOUBLEQUOTEDSTRING, EXCLAMATION, COMMENT, LIMITEDSTRING, STRING, EMPTY};

    Token(string v = "", Type t = EMPTY, Position p = Position(0,0));
    Token(char c, Type t, Position p);

    string getValue();
    void setValue(string v);
    Type getType();
    void setType(Type t);
    Position getPosition();
    Token& operator=(Token token);

private:
    string value;
    Type type;
    Position position;
};

std::ostream& operator<<(std::ostream& os, Token& token);

#endif //WEB_CONTENT_EXTRACTOR_TOKEN_H
