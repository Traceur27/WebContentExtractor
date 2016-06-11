#include "Lexer.hpp"

Lexer::Lexer() {}

Lexer::Lexer(string fName)
{
    this->fileName = fName;
}

void Lexer::init()
{
    this->sourceFile.open(this->fileName);;

    if(!this->sourceFile.is_open())
    {
        cout << "Cannot open file" << endl;
        exit(1);
    }

    this->currentChar = this->getNextChar();
}

Lexer::~Lexer()
{
    if(this->sourceFile.is_open())
        this->sourceFile.close();
}


Token Lexer::nextToken()
{
    char nextC = this->getNextChar();
    string buffer;

    if(this->currentChar == EOF)
        return Token("", Token::EMPTY, this->position);

    while(isspace(this->currentChar)) //omit all whitespaces
    {
        this->currentChar = nextC;
        nextC = this->getNextChar();
    }

    if(this->currentChar == '=')
    {
        this->currentChar = nextC;
        return Token('=', Token::EQUALS, this->position);
    }
    else if(this->currentChar == '>')
    {
        this->currentChar = nextC;
        return Token('>', Token::CLOSETAGSYMBOL, this->position);
    }
    else if(this->currentChar == '\'')
    {
        string s = this->getQuotedString(nextC);
        return Token(s, Token::SINGLEQUOTEDSTRING, this->position);
    }
    else if(this->currentChar == '\"')
    {
        string s = this->getQuotedString(nextC);
        return Token(s, Token::DOUBLEQUOTEDSTRING, this->position);
    }
    else if(this->currentChar == '<') //tokens starting with "<"
    {
        if(nextC == '!')
        {
            this->currentChar = this->getNextChar();
            if(this->currentChar == '-')
            {
                string s = getComment();
                return Token(s, Token::COMMENT, this->position);
            }
            else
            {
                return Token("<!", Token::EXCLAMATION, this->position);
            }
        }
        else if(nextC == '/')
        {
            this->currentChar = this->getNextChar();
            return Token("</", Token::SLASHOPENTAGSYMBOL, this->position);
        }
        else
        {
            this->currentChar = nextC;
            return Token("<", Token::OPENTAGSYMBOL, this->position);
        }
    }
    else if(this->currentChar == '/')
    {
        if(nextC == '>')
        {
            this->currentChar = this->getNextChar();
            return Token("/>", Token::SLASHCLOSETAGSYMBOL, this->position);
        }
    }
    else //collect all symbols to whitespace, <, >, /, space, =
    {
        string buffer;
        buffer += this->currentChar;

        while(nextC != '<' && nextC != '>' && nextC != ' ' && nextC != '/' &&
                nextC != '=' && nextC != EOF)
        {
            buffer += nextC;
            nextC = this->getNextChar();
        }

        this->currentChar = nextC;
        return Token(buffer, Token::LIMITEDSTRING, this->position);
    }
}

//Collect all chars until next quote symbol
string Lexer::getQuotedString(char nextC)
{
    string stringToReturn;
    stringToReturn += this->currentChar;

    if(this->currentChar == '\'')
    {
        while(nextC != '\'' && nextC != EOF)
        {
            stringToReturn += nextC;
            nextC = this->getNextChar();
        }
    }
    else
    {
        while(nextC != '\"' && nextC != EOF)
        {
            stringToReturn += nextC;
            nextC = this->getNextChar();
        }
    }

    if(nextC != '\'' && nextC != '\"')
    {
        cout << "Brak zakonczenia cudzyslowiu!" << endl;
        exit(1);
    }

    stringToReturn += nextC;
    this->currentChar = this->getNextChar();
    return stringToReturn;
}

Token Lexer::getContent()
{
    string stringToReturn;
    char nextC = this->currentChar;

    while(isspace(nextC)) //omit all whitespaces
    {
        nextC = this->getNextChar();
    }

    this->currentChar = nextC;

    if(this->currentChar == '<')
        return Token("", Token::EMPTY, this->position);

    while(nextC != '<' && nextC != EOF)
    {
        stringToReturn += nextC;
        nextC = this->getNextChar();
    }

    if(nextC == EOF)
    {
        cout << "Brak zakonczenia zawartosci tagu" << endl;
        exit(1);
    }

    this->currentChar = nextC;
    return Token(stringToReturn, Token::LIMITEDSTRING, this->position);
}


string Lexer::getComment()
{
    string stringToReturn = "<!-";

    char nextChar = this->getNextChar();
    if(nextChar != '-')
    {
        cout << "Bledny symbol rozpoczecia komentarza HTML" << endl;
        exit(1);
    }
    stringToReturn += '-';

    nextChar = this->getNextChar();
    while(nextChar != EOF)
    {
        if(nextChar == '-')
        {
            stringToReturn += nextChar;
            nextChar = this->getNextChar();
            if(nextChar == '-')
            {
                stringToReturn += nextChar;
                nextChar = this->getNextChar();
                if(nextChar == '>')
                {
                    this->currentChar = this->getNextChar();
                    stringToReturn += ">";
                    return stringToReturn;
                }
                else
                    continue;
            }
            else
                continue;
        }

        stringToReturn += nextChar;
        nextChar = this->getNextChar();
    }

    cout << "Brak zakonczenia komentarza" << endl;
    exit(1);
}


char Lexer::getNextChar()
{
    char c = (char) this->sourceFile.get();
    if(c == '\n')
        this->position.moveDown();
    else
        this->position.moveRight();

    return c;
}

void Lexer::setName(string fName)
{
    this->fileName = fName;
}

void Lexer::parseScripts()
{
    char currentCharacter = this->getNextChar();
    while(currentCharacter != EOF)
    {
        if(currentCharacter == '<')
        {
            string closeTag;
            closeTag += currentCharacter;
            for (int i = 0; i < 8; ++i)
            {
                closeTag += this->getNextChar();
            }

            if(closeTag == "</script>")
                return;
            else
                currentCharacter = this->getNextChar();
        }
        else
            currentCharacter = this->getNextChar();
    }
}



