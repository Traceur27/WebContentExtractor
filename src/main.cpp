#include <iostream>
#include "Lexer.hpp"
#include "SourceParser.h"

using namespace std;

int main(int argc, char** argv)
{

    if (argc != 2)
    {
        cout << "Usage: web-content-extractor pathToFile" << endl;
        exit(0);
    }

    std::string fileName = argv[1];

   /* Lexer lexer(fileName);
    lexer.init();
    Token token = lexer.nextToken();
    while(token.getType() != Token::EMPTY)
    {
        cout << token << endl;
        token = lexer.nextToken();
    } */

    SourceParser sourceParser(fileName);
    sourceParser.parse();
    sourceParser.listNodes(sourceParser.getRoot());

    return 0;
}