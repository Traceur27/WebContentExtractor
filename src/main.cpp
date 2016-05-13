#include <iostream>
#include "Lexer.hpp"

using namespace std;

int main()
{
    std::string fileName = "/home/konrad/Dokumenty/CLionProjects/WebContentExtractor/inputFiles/index.html";
    Lexer lexer(fileName);
    Token token = lexer.nextToken();
    while(token.getType() != Token::EMPTY)
    {
        cout << token.getValue() << endl;
        token = lexer.nextToken();
    }

    return 0;
}