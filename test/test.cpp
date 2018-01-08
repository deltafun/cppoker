#include "stdafx.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "poker.h"

TEST_CASE("Input string is split into two poker hand strings") {

    std::vector<std::string> expected;
    expected.push_back("2H 3D 5S 9C KD");
    expected.push_back("2C 3H 4S 8C AH");

    std::vector<std::string> actual
        = SplitInputHands("Black: 2H 3D 5S 9C KD White: 2C 3H 4S 8C AH");
    
    REQUIRE(expected[0] == actual[0]);
    REQUIRE(expected[1] == actual[1]);
}