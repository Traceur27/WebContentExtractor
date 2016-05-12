#include <iostream>
#include "catch.hpp"
#include "../src/Lexer.hpp"


TEST_CASE("File with only one tag")
{
    Lexer lexer("/home/konrad/Dokumenty/CLionProjects/WebContentExtractor/inputFiles/oneTag.html");
    REQUIRE(lexer.nextToken() == "<!");
    REQUIRE(lexer.nextToken() == "DOCTYPE");
    REQUIRE(lexer.nextToken() == "HTML");
    REQUIRE(lexer.nextToken() == ">");
    REQUIRE(lexer.nextToken() == "");
}

TEST_CASE("New lines and content inside tags")
{
    Lexer lexer("/home/konrad/Dokumenty/CLionProjects/WebContentExtractor/inputFiles/contentTag.html");
    REQUIRE(lexer.nextToken() == "<");
    REQUIRE(lexer.nextToken() == "title");
    REQUIRE(lexer.nextToken() == ">");
    REQUIRE(lexer.nextToken() == "Najlepsze filmy");
    REQUIRE(lexer.nextToken() == "</");
    REQUIRE(lexer.nextToken() == "title");
    REQUIRE(lexer.nextToken() == ">");
    REQUIRE(lexer.nextToken() == "");

}

TEST_CASE("Quoted string")
{
    Lexer lexer("/home/konrad/Dokumenty/CLionProjects/WebContentExtractor/inputFiles/quotedString.html");
    REQUIRE(lexer.nextToken() == "<");
    REQUIRE(lexer.nextToken() == "meta");
    REQUIRE(lexer.nextToken() == "name");
    REQUIRE(lexer.nextToken() == "=");
    REQUIRE(lexer.nextToken() == "\"");
    REQUIRE(lexer.nextToken() == "description");
    REQUIRE(lexer.nextToken() == "\"");
    REQUIRE(lexer.nextToken() == "content");
    REQUIRE(lexer.nextToken() == "=");
    REQUIRE(lexer.nextToken() == "\"");
    REQUIRE(lexer.nextToken() == "Ulubione filmy");
    REQUIRE(lexer.nextToken() == "\"");
    REQUIRE(lexer.nextToken() == "/>");
    REQUIRE(lexer.nextToken() == "");
}

