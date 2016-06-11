#ifndef WEB_CONTENT_EXTRACTOR_LEXER_H
#define WEB_CONTENT_EXTRACTOR_LEXER_H

#include <fstream>
#include <iostream>
#include <cstdlib>
#include "Token.hpp"

using namespace std;

class Lexer
{
private:
    string fileName;
    ifstream sourceFile;
    char currentChar;
    Position position;

    char getNextChar();
    string getQuotedString(char nextC); //get all characters between quote symbols
    string getComment(); //get all characters between <!-- -->

public:
    Lexer();
    Lexer(string);
    ~Lexer();
    Token nextToken();
    void init();
    void setName(string fName);
    void parseScripts();
    Token getContent(); //get all characters between <tag> </tag>
};


#endif //WEB_CONTENT_EXTRACTOR_LEXER_H
