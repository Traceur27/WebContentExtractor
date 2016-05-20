#include <iostream>
#include "catch.hpp"
#include "../src/Lexer.hpp"


TEST_CASE("File with only one tag")
{
    //Lexer lexer("/home/konrad/Dokumenty/CLionProjects/WebContentExtractor/inputFiles/oneTag.html");
    Lexer lexer("../inputFiles/oneTag.html");
    Token token = lexer.nextToken();
    REQUIRE(token.getValue() == "<!");
    REQUIRE(token.getType() == Token::EXCLAMATION);
    token = lexer.nextToken();
    REQUIRE(token.getValue() == "DOCTYPE");
    REQUIRE(token.getType() == Token::LIMITEDSTRING);
    token = lexer.nextToken();
    REQUIRE(token.getValue() == "HTML");
    REQUIRE(token.getType() == Token::LIMITEDSTRING);
    token = lexer.nextToken();
    REQUIRE(token.getValue() == ">");
    REQUIRE(token.getType() == Token::CLOSETAGSYMBOL);
    token = lexer.nextToken();
    REQUIRE(token.getValue() == "");
    REQUIRE(token.getType() == Token::EMPTY);
}

 TEST_CASE("New lines and content inside tags")
{
    //Lexer lexer("/home/konrad/Dokumenty/CLionProjects/WebContentExtractor/inputFiles/contentTag.html");
    Lexer lexer("../inputFiles/contentTag.html");
    Token token = lexer.nextToken();
    REQUIRE(token.getValue() == "<");
    REQUIRE(token.getType() == Token::OPENTAGSYMBOL);
    token = lexer.nextToken();
    REQUIRE(token.getValue() == "title");
    REQUIRE(token.getType() == Token::LIMITEDSTRING);
    token = lexer.nextToken();
    REQUIRE(token.getValue() == ">");
    REQUIRE(token.getType() == Token::CLOSETAGSYMBOL);
    token = lexer.nextToken();
    REQUIRE(token.getValue() == "Najlepsze filmy");
    REQUIRE(token.getType() == Token::LIMITEDSTRING);
    token = lexer.nextToken();
    REQUIRE(token.getValue() == "</");
    REQUIRE(token.getType() == Token::SLASHOPENTAGSYMBOL);
    token = lexer.nextToken();
    REQUIRE(token.getValue() == "title");
    REQUIRE(token.getType() == Token::LIMITEDSTRING);
    token = lexer.nextToken();
    REQUIRE(token.getValue() == ">");
    REQUIRE(token.getType() == Token::CLOSETAGSYMBOL);
    token = lexer.nextToken();
    REQUIRE(token.getValue() == "");
    REQUIRE(token.getType() == Token::EMPTY);

}

TEST_CASE("Quoted string")
{
    //Lexer lexer("/home/konrad/Dokumenty/CLionProjects/WebContentExtractor/inputFiles/quotedString.html");
    Lexer lexer("../inputFiles/quotedString.html");
    Token token = lexer.nextToken();
    REQUIRE(token.getValue() == "<");
    REQUIRE(token.getType() == Token::OPENTAGSYMBOL);
    token = lexer.nextToken();
    REQUIRE(token.getValue() == "meta");
    REQUIRE(token.getType() == Token::LIMITEDSTRING);
    token = lexer.nextToken();
    REQUIRE(token.getValue() == "name");
    REQUIRE(token.getType() == Token::LIMITEDSTRING);
    token = lexer.nextToken();
    REQUIRE(token.getValue() == "=");
    REQUIRE(token.getType() == Token::EQUALS);
    token = lexer.nextToken();
    REQUIRE(token.getValue() == "\"description\"");
    REQUIRE(token.getType() == Token::DOUBLEQUOTEDSTRING);
    token = lexer.nextToken();
    REQUIRE(token.getValue() == "content");
    REQUIRE(token.getType() == Token::LIMITEDSTRING);
    token = lexer.nextToken();
    REQUIRE(token.getValue() == "=");
    REQUIRE(token.getType() == Token::EQUALS);
    token = lexer.nextToken();
    REQUIRE(token.getValue() == "\"Ulubione filmy\"");
    REQUIRE(token.getType() == Token::DOUBLEQUOTEDSTRING);
    token = lexer.nextToken();
    REQUIRE(token.getValue() == "/>");
    REQUIRE(token.getType() == Token::SLASHCLOSETAGSYMBOL);
    token = lexer.nextToken();
    REQUIRE(token.getValue() == "");
    REQUIRE(token.getType() == Token::EMPTY);
}


TEST_CASE("Commented string")
{
    //Lexer lexer("/home/konrad/Dokumenty/CLionProjects/WebContentExtractor/inputFiles/comments.html");
    Lexer lexer("../inputFiles/comments.html");
    Token token = lexer.nextToken();
    REQUIRE(token.getValue() == "<!");
    REQUIRE(token.getType() == Token::EXCLAMATION);
    token = lexer.nextToken();
    REQUIRE(token.getValue() == "DOCTYPE");
    REQUIRE(token.getType() == Token::LIMITEDSTRING);
    token = lexer.nextToken();
    REQUIRE(token.getValue() == "HTML");
    REQUIRE(token.getType() == Token::LIMITEDSTRING);
    token = lexer.nextToken();
    REQUIRE(token.getValue() == ">");
    REQUIRE(token.getType() == Token::CLOSETAGSYMBOL);
    token = lexer.nextToken();
    REQUIRE(token.getValue() == "<!-- <html lang=\"pl\"> -->");
    REQUIRE(token.getType() == Token::COMMENT);
    token = lexer.nextToken();
    REQUIRE(token.getValue() == "");
    REQUIRE(token.getType() == Token::EMPTY);
}