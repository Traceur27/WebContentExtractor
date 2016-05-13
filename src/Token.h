#ifndef WEB_CONTENT_EXTRACTOR_TOKEN_H
#define WEB_CONTENT_EXTRACTOR_TOKEN_H

#include <string>

using std::string;

class Token
{
public:
    enum Type {OPENTAGSYMBOL, CLOSETAGSYMBOL, SLASHCLOSETAGSYMBOL, SLASHOPENTAGSYMBOL, EQUALS, SINGLEQUOTE,
               DOUBLEQUOTE, EXCLAMATION, COMMENTSTART, COMMENTEND, LIMITEDSTRING, STRING, EMPTY};

    Token(string v, Type t);
    Token(char c, Type t);

    string getValue();
    void setValue(string v);
    Type getType();
    void setType(Type t);

private:
    string value;
    Type type;
};


#endif //WEB_CONTENT_EXTRACTOR_TOKEN_H
