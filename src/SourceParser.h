#ifndef WEB_CONTENT_EXTRACTOR_SOURCEPARSER_H
#define WEB_CONTENT_EXTRACTOR_SOURCEPARSER_H

#include "Lexer.hpp"
#include "HTMLNode.h"

class SourceParser
{
private:
    Lexer lexer;
    TagNode * root;
    TagNode * currentNode;
    Token currentToken;

public:
    SourceParser(string fileName);
    ~SourceParser();
    void parse();
    void freeMemory(HTMLNode * currentNode);
    void getAttributes(TagNode * tagNode);
    void listNodes(HTMLNode * node);
    HTMLNode * getRoot();
};


#endif //WEB_CONTENT_EXTRACTOR_SOURCEPARSER_H
