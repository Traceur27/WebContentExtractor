#ifndef WEB_CONTENT_EXTRACTOR_EXTRACTOR_H
#define WEB_CONTENT_EXTRACTOR_EXTRACTOR_H

#include "SourceParser.h"

class Extractor
{
private:
    SourceParser configuration;
    SourceParser source;
    bool compareTagNodes(TagNode * t1, TagNode * t2);

public:
    Extractor(string configFileName, string sourceFileName);
    void startExtracting();
    void extract(HTMLNode * config, HTMLNode * source);
    bool compareNodes(HTMLNode * first, HTMLNode * second);
};


#endif //WEB_CONTENT_EXTRACTOR_EXTRACTOR_H
