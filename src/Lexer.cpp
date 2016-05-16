#include "Lexer.hpp"

Lexer::Lexer(string fName)
{
    this->sourceFile.open(fName.c_str());
    this->closingQuoteSymbol = false;
    this->endComment = false;

    if(!this->sourceFile.is_open())
    {
        cout << "Cannot open file" << endl;
        exit(1);
    }
}


Lexer::~Lexer()
{
    if(this->sourceFile.is_open())
        this->sourceFile.close();
}


Token Lexer::nextToken()
{
    char c = (char)this->sourceFile.get();
    char nextC;
    string buffer;

    if(c == EOF)
        return Token("", Token::EMPTY);
    if(this->lastSymbol == '\'' || this->lastSymbol == '\"')
    {
        if(!this->closingQuoteSymbol) //if it's closing quote don't call getQuotedString
        {
            string ret = getQuotedString(c);
            if (ret.length() != 0)
                return Token(ret, Token::STRING);
        }
    }
    if(this->lastSymbol == '-')
    {
        string ret = getComment(c);
        if(ret.length() != 0)
            return Token(ret, Token::STRING);
    }
    if(this->lastSymbol == '>')
    {
        while(isspace(c)) //omit all whitespaces
            c = (char)this->sourceFile.get();

        string ret = getContent(c);
        if(ret.length() != 0)
            return Token(ret, Token::LIMITEDSTRING);
    }
    if(this->endComment)
    {
        //first - already taken
        this->sourceFile.get(); //-
        this->sourceFile.get(); //>
        this->endComment = false;
        return Token("-->", Token::COMMENTEND);
    }

    while(isspace(c)) //omit all whitespaces
        c = (char)this->sourceFile.get();

    if(c == '=') // single character tokens
        return Token(c, Token::EQUALS);
    else if(c == '>')
    {
        this->lastSymbol = '>';
        return Token(c, Token::CLOSETAGSYMBOL);
    }
    else if(c == '\'')
    {
        if(this->closingQuoteSymbol)
            this->closingQuoteSymbol = false;
        else
            this->lastSymbol = c;

        return Token(c, Token::SINGLEQUOTE);

    }
    else if(c == '\"')
    {
        if(this->closingQuoteSymbol)
            this->closingQuoteSymbol = false;
        else
            this->lastSymbol = c;

        return Token(c, Token::DOUBLEQUOTE);
    }
    else if(c == '<') //tokens starting with "<"
    {
        nextC = (char)this->sourceFile.peek();

        if(nextC == '!')
        {
            this->sourceFile.get();
            if(this->sourceFile.peek() == '-')
            {
                this->sourceFile.seekg(1, ios_base::cur);
                if(this->sourceFile.peek() == '-')
                {
                    this->sourceFile.seekg(-1, ios_base::cur);
                    this->sourceFile.get();
                    this->sourceFile.get();
                    this->lastSymbol = '-';
                    return Token("<!--", Token::COMMENTSTART);
                }
                else
                {
                    this->sourceFile.seekg(-1, ios_base::cur);
                }
            }
            return Token("<!", Token::EXCLAMATION);
        }
        else if(nextC == '/')
        {
            this->sourceFile.get();
            return Token("</", Token::SLASHOPENTAGSYMBOL);
        }
        else
            return Token("<", Token::OPENTAGSYMBOL);
    }
    else if(c == '/')
    {
        nextC = (char)this->sourceFile.peek();
        if(nextC == '>')
        {
            this->sourceFile.get();
            this->lastSymbol = '>';
            return Token("/>", Token::SLASHCLOSETAGSYMBOL);
        }
    }
    else //collect all symbols to whitespace, <, >, /, space, =
    {
        string buffer;
        buffer += c;
        char peekedChar = (char)this->sourceFile.peek();
        while(peekedChar != '<' && peekedChar != '>' && peekedChar != ' ' && peekedChar != '/' &&
              peekedChar != '=' && peekedChar != EOF)
        {
            buffer += this->sourceFile.get();
            peekedChar = (char)this->sourceFile.peek();
        }

        return Token(buffer, Token::LIMITEDSTRING);
    }
}

//Collect all chars until next quote symbol
string Lexer::getQuotedString(char alreadyTakenChar)
{
    string stringToReturn;
    if(alreadyTakenChar == this->lastSymbol)
    {
        this->closingQuoteSymbol = true;
        this->lastSymbol = ' ';
        return "";
    }
    stringToReturn += alreadyTakenChar;
    while(this->sourceFile.peek() != this->lastSymbol && this->sourceFile.peek() != EOF)
            stringToReturn += this->sourceFile.get();

    this->lastSymbol = ' ';
    this->closingQuoteSymbol = true;
    return stringToReturn;
}

string Lexer::getContent(char alreadyTakenChar)
{
    string stringToReturn;
    if(alreadyTakenChar == '<')
    {
        this->lastSymbol = ' ';
        return "";
    }

    if(alreadyTakenChar == '/')
        if(this->sourceFile.peek() == '*')
        {
            this->sourceFile.get();
            stringToReturn += "/";
            stringToReturn += getJavaScriptComment('*');
            alreadyTakenChar = ' ';
        }

    stringToReturn += alreadyTakenChar;
    char peekValue = (char)this->sourceFile.peek();
    while(peekValue != '<' && peekValue != EOF)
    {
        if(peekValue == '/')
        {
            this->sourceFile.seekg(1, ios_base::cur);
            if (this->sourceFile.peek() == '*')
            {
                this->sourceFile.seekg(-1, ios_base::cur);
                this->sourceFile.get();
                this->sourceFile.get();
                stringToReturn += "/";
                stringToReturn += getJavaScriptComment('*');
            }
            else
                this->sourceFile.seekg(-1, ios_base::cur);
        }
        else
            stringToReturn += this->sourceFile.get();

        peekValue = (char)this->sourceFile.peek();
    }

    this->lastSymbol = ' ';
    return stringToReturn;
}

string Lexer::getComment(char alreadyTakenChar)
{
    string stringToReturn;
    stringToReturn += alreadyTakenChar;
    while (this->sourceFile.peek() != EOF)
    {
        char c = (char) this->sourceFile.peek();
        if (c == '-')
        {
            this->sourceFile.seekg(1, ios_base::cur);
            if (this->sourceFile.peek() == '-')
            {
                this->sourceFile.seekg(1, ios_base::cur);
                if(this->sourceFile.peek() == '>')
                {
                    this->sourceFile.seekg(-2, ios_base::cur);
                    break;
                }
                this->sourceFile.seekg(-2, ios_base::cur);
            }
            else
                this->sourceFile.seekg(-1, ios_base::cur);
        }

        c = (char) this->sourceFile.get();
        stringToReturn += c;
    }

    this->lastSymbol = ' ';
    this->endComment = true;
    return stringToReturn;
}

string Lexer::getJavaScriptComment(char alreadyTakenChar)
{
    string buffer;
    buffer += alreadyTakenChar;

    char nextC = (char) this->sourceFile.peek();
    while(nextC != EOF)
    {
        if(nextC == '*')
        {
            this->sourceFile.seekg(1, ios_base::cur);
            if(this->sourceFile.peek() == '/')
            {
                this->sourceFile.seekg(-1, ios_base::cur);
                this->sourceFile.get();
                this->sourceFile.get();
                buffer += "*/";
                return buffer;
            }
        }

        buffer += this->sourceFile.get();
        nextC = (char) this->sourceFile.peek();
    }
    return "";
}