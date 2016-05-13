#include <iostream>
#include "catch.hpp"
#include "../src/Lexer.hpp"


TEST_CASE("File with only one tag")
{
    Lexer lexer("/home/konrad/Dokumenty/CLionProjects/WebContentExtractor/inputFiles/oneTag.html");
    REQUIRE(lexer.nextToken().getValue() == "<!");
    REQUIRE(lexer.nextToken().getValue() == "DOCTYPE");
    REQUIRE(lexer.nextToken().getValue() == "HTML");
    REQUIRE(lexer.nextToken().getValue() == ">");
    REQUIRE(lexer.nextToken().getValue() == "");
}

TEST_CASE("New lines and content inside tags")
{
    Lexer lexer("/home/konrad/Dokumenty/CLionProjects/WebContentExtractor/inputFiles/contentTag.html");
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
    Lexer lexer("/home/konrad/Dokumenty/CLionProjects/WebContentExtractor/inputFiles/quotedString.html");
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

