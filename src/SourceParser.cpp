#include "SourceParser.hpp"


void SourceParser::init()
{
    this->lexer.setName(fileName);
    this->lexer.init();
    this->currentToken = lexer.nextToken();
    this->currentNode = nullptr;
    this->root = nullptr;
}

void SourceParser::parse()
{
    while(this->currentToken.getType() != Token::EMPTY)
    {
        parseDoctype();
        parseComment();
        parseTag();
        parseContent();
        parseClosingTag();
    }
}


void SourceParser::parseDoctype()
{
    if(this->currentToken.getType() == Token::EXCLAMATION)
    {
        this->currentToken = this->lexer.nextToken();
        if (this->currentToken.getType() == Token::LIMITEDSTRING)
        {
            this->currentToken = this->lexer.nextToken();
            if (this->currentToken.getType() == Token::LIMITEDSTRING)
            {
                this->currentToken = this->lexer.nextToken();
                if (this->currentToken.getType() == Token::CLOSETAGSYMBOL)
                {
                    this->currentToken = this->lexer.nextToken();
                }
                else
                {
                    cout << "Blad parsera! Oczekiwano CLOSETAGSYMBOL, a otrzymano: " << this->currentToken << endl;
                    exit(1);
                }
            }
            else
            {
                cout << "Blad parsera! Oczekiwano LIMITEDSTRING, a otrzymano: " << this->currentToken << endl;
                exit(1);
            }
        }
        else
        {
            cout << "Blad parsera! Oczekiwano LIMITEDSTRING, a otrzymano: " << this->currentToken << endl;
            exit(1);
        }
    }
}


void SourceParser::parseComment()
{
    if(this->currentToken.getType() == Token::COMMENT)
        this->currentToken = this->lexer.nextToken();
}


void SourceParser::parseTag()
{
    if(this->currentToken.getType() == Token::OPENTAGSYMBOL)
    {
        this->currentToken = this->lexer.nextToken();
        if (this->currentToken.getType() == Token::LIMITEDSTRING)
        {
            if(this->currentToken.getValue() != "script")
            {
                TagNode *newNode = new TagNode(this->currentToken.getValue());
                if (root == nullptr)
                {
                    root = newNode;
                    this->currentNode = newNode;
                    newNode->setParent(nullptr);
                }
                else
                {
                    if (this->currentNode == nullptr)
                        this->currentNode = root;

                    newNode->setParent(this->currentNode);
                    this->currentNode->addChild(newNode);
                    this->currentNode = newNode;
                }
                setAttributes(newNode);

                this->currentToken = this->lexer.getContent();
                if(this->currentToken.getType() == Token::EMPTY)
                    this->currentToken = this->lexer.nextToken();
            }
            else
            {
                this->lexer.parseScripts();
                this->currentToken = this->lexer.nextToken();
            }
        }
        else
        {
            cout << "Błąd parsera! Oczekiwano LIMITEDSTRING, a otrzymano: " << this->currentToken << endl;
            exit(1);
        }
    }
}


void SourceParser::parseContent()
{
    if(this->currentToken.getType() == Token::LIMITEDSTRING)
    {
        HTMLNode *newNode = new TextNode(this->currentToken.getValue());
        newNode->setParent(this->currentNode);
        this->currentNode->addChild(newNode);
        this->currentToken = this->lexer.nextToken();
    }
}

void SourceParser::parseClosingTag()
{
    if(this->currentToken.getType() == Token::SLASHOPENTAGSYMBOL)
    {
        this->currentToken = this->lexer.nextToken();
        if (this->currentToken.getType() == Token::LIMITEDSTRING)
        {
            this->currentToken = this->lexer.nextToken();
            if (this->currentToken.getType() == Token::CLOSETAGSYMBOL)
            {
                this->currentNode = (TagNode *) this->currentNode->getParent();
                this->currentToken = this->lexer.nextToken();
            }
            else
            {
                cout << "Błąd parsera! Oczekiwano CLOSETAGSYMBOL, a otrzymano: " << this->currentToken << endl;
                exit(1);
            }
        }
        else
        {
            cout << "Błąd parsera! Oczekiwano LIMITEDSTRING, a otrzymano: " << this->currentToken << endl;
            exit(1);
        }
    }
}


void SourceParser::setAttributes(TagNode *tagNode)
{
    this->currentToken = this->lexer.nextToken();
    while(this->currentToken.getType() != Token::CLOSETAGSYMBOL || this->currentToken.getType() != Token::SLASHCLOSETAGSYMBOL)
    {
        if(this->currentToken.getType() == Token::CLOSETAGSYMBOL)
        {
            break;
        }
        else if(this->currentToken.getType() == Token::SLASHCLOSETAGSYMBOL)
        {
            this->currentNode = (TagNode*)this->currentNode->getParent();
            break;
        }
        else if(this->currentToken.getType() == Token::LIMITEDSTRING)
        {
            Token nextToken = this->lexer.nextToken();
            if(nextToken.getType() == Token::LIMITEDSTRING) //Dwa LIMITEDSTRING po sobie
            {
                this->currentNode->addAttribute(this->currentToken.getValue(), "");
                this->currentToken = nextToken;
            }
            else if(nextToken.getType() == Token::EQUALS)
            {
                nextToken = this->lexer.nextToken();
                if(nextToken.getType() == Token::DOUBLEQUOTEDSTRING || nextToken.getType() == Token::SINGLEQUOTEDSTRING ||
                        nextToken.getType() == Token::LIMITEDSTRING)
                {
                    this->currentNode->addAttribute(this->currentToken.getValue(), nextToken.getValue());
                    this->currentToken = this->lexer.nextToken();
                }
                else
                {
                    cout << "Błąd parsera! Oczekiwano DOUBLEQUOTEDSTRING, SINGLEQUOTEDSTRING, ";
                    cout << "lub LIMITEDSTRING a otrzymano: " << this->currentToken << endl;
                    exit(1);
                }
            }
            else
            {
                cout << "Błąd parsera! Oczekiwano LIMITEDSTRING lub EQUALS, a otrzymano: " << this->currentToken << endl;
                exit(1);
            }
        }
        else
        {
            cout << "Błąd parsera! Oczekiwano CLOSETAGSYMBOL lub SLASHCLOSETAGSYMBOL, a otrzymano: " << this->currentToken << endl;
            exit(1);
        }

    }
}


SourceParser::~SourceParser()
{
    if(this->root != nullptr)
    {
        freeMemory(this->root);
    }
}

void SourceParser::freeMemory(HTMLNode *currentNode)
{
    if(currentNode != nullptr)
    {
        if(currentNode->checkIfIsTextNode())
        {
            delete currentNode;
            return;
        }
        else
        {
            TagNode *tagNode = (TagNode *)currentNode;
            for(int i = 0; i < tagNode->getNumberOfChildrenNodes(); ++i)
            {
                freeMemory(tagNode->getChildrenNode(i));
            }
            delete currentNode;
        }
    }
}

void SourceParser::listNodes(HTMLNode * currentNode)
{
    if(currentNode != nullptr)
    {
        if(currentNode->checkIfIsTextNode())
        {
            cout << *((TextNode*)currentNode) << endl;
            return;
        }
        else
        {
            TagNode *tagNode = (TagNode *)currentNode;
            cout << *tagNode << endl;
            for(int i = 0; i < tagNode->getNumberOfChildrenNodes(); ++i)
            {
                listNodes(tagNode->getChildrenNode(i));
            }
        }
    }
}

HTMLNode *SourceParser::getRoot()
{
    return this->root;
}

void SourceParser::setFileName(string fName)
{
    this->fileName = fName;
}

SourceParser::SourceParser(string fName)
{
    this->fileName = fName;
    this->init();
}




