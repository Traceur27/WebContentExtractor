#include <iostream>
#include "catch.hpp"
#include "../src/SourceParser.hpp"

TEST_CASE("Only doctype")
{
    SourceParser sourceParser("../inputFiles/oneTag.html");
    sourceParser.parse();
    REQUIRE(1 == 1);
}

TEST_CASE("HTML comment")
{
    SourceParser sourceParser("../inputFiles/comments.html");
    sourceParser.parse();
    REQUIRE(1 == 1);
}

TEST_CASE("HTML tag with content")
{
    SourceParser sourceParser("/home/konrad/Dokumenty/CLionProjects/WebContentExtractor/inputFiles/contentTag.html");
    sourceParser.parse();
    REQUIRE(1 == 1);
}

TEST_CASE("HTML tag with attributes")
{
    SourceParser sourceParser("/home/konrad/Dokumenty/CLionProjects/WebContentExtractor/inputFiles/quotedString.html");
    sourceParser.parse();
    REQUIRE(1 == 1);
}

TEST_CASE("Normal html document")
{
    SourceParser sourceParser("/home/konrad/Dokumenty/CLionProjects/WebContentExtractor/inputFiles/index.html");
    sourceParser.parse();
    REQUIRE(1 == 1);
}