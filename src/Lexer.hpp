#ifndef WEB_CONTENT_EXTRACTOR_LEXER_H
#define WEB_CONTENT_EXTRACTOR_LEXER_H

#include <fstream>
#include <iostream>
#include <cstdlib>
#include "Token.h"

using namespace std;

class Lexer
{
private:
    ifstream sourceFile;
    char lastSymbol; //used in special cases when i need to get various strings
    bool closingQuoteSymbol; //i have to remember if quote symbol was the closing one
    bool endComment;
    string getQuotedString(char alreadyTakenChar); //get all characters between quote symbols
    string getContent(char alreadyTakenChar); //get all characters between <tag> </tag>
    string getComment(char alreadyTakenChar); //get all characters between <!-- -->

public:
    Lexer(string);
    ~Lexer();
    Token nextToken();
};


#endif //WEB_CONTENT_EXTRACTOR_LEXER_H
