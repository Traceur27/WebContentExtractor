#include <iostream>
#include "Source.hpp"
#include <sstream>

Source::Source(string fileName)
{
    this->sourceFileName = fileName;
}

void Source::init()
{
    ifstream sourceFile;
    sourceFile.open(this->sourceFileName.c_str());

    if(!sourceFile.is_open())
    {
        std::cout << "Cannot open file" << std::endl;
        exit(1);
    }

    sourceFile.seekg(0, std::ios::end);
    (this->content).reserve(sourceFile.tellg());
    sourceFile.seekg(0, std::ios::beg);

    (this->content).assign((std::istreambuf_iterator<char>(sourceFile)), std::istreambuf_iterator<char>());

}

string Source::nextChar()
{
    (this->position)++;
    if(position >= this->content.size())
    {
        this->position = this->content.size();
        return "";
    }

    return string(1, this->content[position]);
}

string Source::prevChar()
{
    (this->position)--;
    if(position < 0)
    {
        this->position = -1;
        return "";
    }

    return string(1, this->content[position]);
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











