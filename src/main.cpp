#include <iostream>
#include "Extractor.h"

using namespace std;

int main(int argc, char** argv)
{

    if (argc != 3)
    {
        cout << "Usage: web-content-extractor configFilePath sourceFilePath" << endl;
        exit(0);
    }

    std::string configFileName = argv[1];
    std::string sourceFileName = argv[2];

   /* Lexer lexer(fileName);
    lexer.init();
    Token token = lexer.nextToken();
    while(token.getType() != Token::EMPTY)
    {
        cout << token << endl;
        token = lexer.nextToken();
    }

    SourceParser sourceParser(fileName);
    sourceParser.parse();
    sourceParser.listNodes(sourceParser.getRoot()); */

    Extractor extractor(configFileName, sourceFileName);
    extractor.startExtracting();

    return 0;
}