#include <iostream>
#include "Lexer.hpp"

using namespace std;

int main(int argc, char** argv)
{

    if (argc != 2)
    {
        cout << "Usage: web-content-extractor pathToFile" << endl;
        exit(0);
    }

    //std::string fileName = "/home/konrad/Dokumenty/CLionProjects/WebContentExtractor/inputFiles/index.html";
    std::string fileName = argv[1];
    Lexer lexer(fileName);
    Token token = lexer.nextToken();
    while(token.getType() != Token::EMPTY)
    {
        cout << token.getValue() << " " << token.getType() << endl;
        token = lexer.nextToken();
    }

    return 0;
}