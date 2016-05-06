#ifndef WEBCONTENTEXTRACTOR_SOURCE_H
#define WEBCONTENTEXTRACTOR_SOURCE_H
#include <string>
#include <fstream>

using namespace std;

class Source
{
private:
    string sourceFileName;
    string content;
    long position = -1;

public:
    Source(string fileName);
    void init();
    string nextChar();
    string prevChar();
    long getPosition();
    void setPosition(int p);

};


#endif //WEBCONTENTEXTRACTOR_SOURCE_H
