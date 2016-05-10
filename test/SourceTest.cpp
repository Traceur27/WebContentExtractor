#include <iostream>
#include "catch.hpp"
#include "../src/Source.hpp"


TEST_CASE("nextChar tests")
{
    std::string fileName = "/home/konrad/Dokumenty/CLionProjects/WebContentExtractor/index.html";
    std::string answer;
    Source src(fileName);
    src.init();
    REQUIRE(src.nextChar() == "<");
    REQUIRE(src.nextChar() == "!");

    answer = src.nextChar();
    while(answer != "")
        answer = src.nextChar();
    REQUIRE(answer == "");
}


TEST_CASE("prevChar tests")
{
    std::string fileName = "/home/konrad/Dokumenty/CLionProjects/WebContentExtractor/index.html";
    std::string answer;
    Source src(fileName);
    src.init();
    src.setPosition(1);
    REQUIRE(src.prevChar() == "<");
    REQUIRE(src.prevChar() == "");
}

