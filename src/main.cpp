#include <iostream>
#include "Lexer.hpp"

using namespace std;

int main()
{
    std::string fileName = "/home/konrad/Dokumenty/CLionProjects/WebContentExtractor/inputFiles/index.html";
    Lexer lexer(fileName);
    string token = lexer.nextToken();
    while(token != "")
    {
        cout << token << endl;
        token = lexer.nextToken();
    }

    return 0;
}