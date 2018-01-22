#include "stdafx.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "poker.h"

TEST_CASE("Input string is split into two poker hand strings") {
    std::array<std::array<std::string, 5>, 2> expect;
    expect[0] = { "2H", "3D", "5S", "9C", "KD" };
    expect[1] = { "2C", "3H", "4S", "8C", "AH" };
    
    std::array<std::array<std::string, 5>, 2> actual
        = Parser::SplitInputHands("Black: 2H 3D 5S 9C KD White: 2C 3H 4S 8C AH");
    
    REQUIRE(expect[0] == actual[0]);
    REQUIRE(expect[1] == actual[1]);
}