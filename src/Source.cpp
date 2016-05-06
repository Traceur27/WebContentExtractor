#include "Source.h"

Source::Source(string fileName)
{
    this->sourceFileName = fileName;
}

void Source::init()
{
    ifstream sourceFile;
    sourceFile.open(this->sourceFileName.c_str());

    char c;
    sourceFile >> c;
    while( c != EOF)
    {
        this->content.append(c + "");
        sourceFile >> c;
    }
}

string Source::nextChar()
{
    (this->position)++;
    if(this->content[position] >= this->content.length())
    {
        this->position = this->content.length();
        return "";
    }
    return "" + this->content[position];
}

string Source::prevChar()
{
    (this->position)--;
    if(this->content[position] <= 0)
    {
        this->position = -1;
        return "";
    }
    return "" + this->content[position];
}

long Source::getPosition()
{
    return this->position;
}

void Source::setPosition(int p)
{
    if(p < 0 || p > this->content.length())
        return;
    this->position = p;
}











