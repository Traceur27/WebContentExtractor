#ifndef WEB_CONTENT_EXTRACTOR_LEXER_H
#define WEB_CONTENT_EXTRACTOR_LEXER_H

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

class Lexer
{
private:
    ifstream sourceFile;
    char lastSymbol; //used in special cases when i need to get various strings
    bool closingQuoteSymbol; //i have to remember if quote symbol was the closing one
    string getQuotedString(char alreadyTakenChar); //get all characters between quote symbols
    string getContent(char alreadyTakenChar); //get all characters between <tag> </tag>
    string getComment(char alreadyTakenChar); //get all characters between <!-- -->

public:
    Lexer(string);
    ~Lexer();
    string nextToken();
};


#endif //WEB_CONTENT_EXTRACTOR_LEXER_H
