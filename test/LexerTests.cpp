#include <iostream>
#include "catch.hpp"
#include "../src/Lexer.hpp"


TEST_CASE("File with only one tag")
{
    //Lexer lexer("/home/konrad/Dokumenty/CLionProjects/WebContentExtractor/inputFiles/oneTag.html");
    Lexer lexer("../inputFiles/oneTag.html");
    REQUIRE(lexer.nextToken().getValue() == "<!");
    REQUIRE(lexer.nextToken().getValue() == "DOCTYPE");
    REQUIRE(lexer.nextToken().getValue() == "HTML");
    REQUIRE(lexer.nextToken().getValue() == ">");
    REQUIRE(lexer.nextToken().getValue() == "");
}

TEST_CASE("New lines and content inside tags")
{
    //Lexer lexer("/home/konrad/Dokumenty/CLionProjects/WebContentExtractor/inputFiles/contentTag.html");
    Lexer lexer("../inputFiles/contentTag.html");
    REQUIRE(lexer.nextToken().getValue() == "<");
    REQUIRE(lexer.nextToken().getValue() == "title");
    REQUIRE(lexer.nextToken().getValue() == ">");
    REQUIRE(lexer.nextToken().getValue() == "Najlepsze filmy");
    REQUIRE(lexer.nextToken().getValue() == "</");
    REQUIRE(lexer.nextToken().getValue() == "title");
    REQUIRE(lexer.nextToken().getValue() == ">");
    REQUIRE(lexer.nextToken().getValue() == "");

}

TEST_CASE("Quoted string")
{
    //Lexer lexer("/home/konrad/Dokumenty/CLionProjects/WebContentExtractor/inputFiles/quotedString.html");
    Lexer lexer("../inputFiles/quotedString.html");
    REQUIRE(lexer.nextToken().getValue() == "<");
    REQUIRE(lexer.nextToken().getValue() == "meta");
    REQUIRE(lexer.nextToken().getValue() == "name");
    REQUIRE(lexer.nextToken().getValue() == "=");
    REQUIRE(lexer.nextToken().getValue() == "\"");
    REQUIRE(lexer.nextToken().getValue() == "description");
    REQUIRE(lexer.nextToken().getValue() == "\"");
    REQUIRE(lexer.nextToken().getValue() == "content");
    REQUIRE(lexer.nextToken().getValue() == "=");
    REQUIRE(lexer.nextToken().getValue() == "\"");
    REQUIRE(lexer.nextToken().getValue() == "Ulubione filmy");
    REQUIRE(lexer.nextToken().getValue() == "\"");
    REQUIRE(lexer.nextToken().getValue() == "/>");
    REQUIRE(lexer.nextToken().getValue() == "");
}

TEST_CASE("Commented string")
{
    //Lexer lexer("/home/konrad/Dokumenty/CLionProjects/WebContentExtractor/inputFiles/comments.html");
    Lexer lexer("../inputFiles/comments.html");
    REQUIRE(lexer.nextToken().getValue() == "<!");
    REQUIRE(lexer.nextToken().getValue() == "DOCTYPE");
    REQUIRE(lexer.nextToken().getValue() == "HTML");
    REQUIRE(lexer.nextToken().getValue() == ">");
    REQUIRE(lexer.nextToken().getValue() == "<!--");
    REQUIRE(lexer.nextToken().getValue() == " <html lang=\"pl\"> ");
    REQUIRE(lexer.nextToken().getValue() == "-->");
    REQUIRE(lexer.nextToken().getValue() == "");
}

TEST_CASE("JavaScript comments")
{
    //Lexer lexer("/home/konrad/Dokumenty/CLionProjects/WebContentExtractor/inputFiles/commentsJavaScript.html");
    Lexer lexer("../inputFiles/commentsJavaScript.html");
    REQUIRE(lexer.nextToken().getValue() == "<");
    REQUIRE(lexer.nextToken().getValue() == "script");
    REQUIRE(lexer.nextToken().getValue() == "src");
    REQUIRE(lexer.nextToken().getValue() == "=");
    REQUIRE(lexer.nextToken().getValue() == "\"");
    REQUIRE(lexer.nextToken().getValue() == "Onet.pl_pliki/pl1-sst-w.js");
    REQUIRE(lexer.nextToken().getValue() == "\"");
    REQUIRE(lexer.nextToken().getValue() == "async");
    REQUIRE(lexer.nextToken().getValue() == "=");
    REQUIRE(lexer.nextToken().getValue() == "\"");
    REQUIRE(lexer.nextToken().getValue() == "\"");
    REQUIRE(lexer.nextToken().getValue() == ">");
    REQUIRE(lexer.nextToken().getValue() == "</");
    REQUIRE(lexer.nextToken().getValue() == "script");
    REQUIRE(lexer.nextToken().getValue() == ">");
    REQUIRE(lexer.nextToken().getValue() == "<");
    REQUIRE(lexer.nextToken().getValue() == "script");
    REQUIRE(lexer.nextToken().getValue() == "type");
    REQUIRE(lexer.nextToken().getValue() == "=");
    REQUIRE(lexer.nextToken().getValue() == "\"");
    REQUIRE(lexer.nextToken().getValue() == "text/javascript");
    REQUIRE(lexer.nextToken().getValue() == "\"");
    REQUIRE(lexer.nextToken().getValue() == ">");
    REQUIRE(lexer.nextToken().getValue() == "/* <![CDATA[ */  window.suggestmeyes_loaded = true;/* ]]> */");
    REQUIRE(lexer.nextToken().getValue() == "</");
    REQUIRE(lexer.nextToken().getValue() == "script");
    REQUIRE(lexer.nextToken().getValue() == ">");
    REQUIRE(lexer.nextToken().getValue() == "");
}