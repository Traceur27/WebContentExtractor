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
    ifstream sourceFile;
    char currentChar;
    Position position;
    bool shouldTakeContent;

    char getNextChar();
    string getQuotedString(char nextC); //get all characters between quote symbols
    string getContent(char nextC); //get all characters between <tag> </tag>
    string getComment(); //get all characters between <!-- -->

public:
    Lexer(string);
    ~Lexer();
    Token nextToken();
};


#endif //WEB_CONTENT_EXTRACTOR_LEXER_H
