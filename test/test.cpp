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

TEST_CASE("Poker hand string is converted in poker hand vector of Cards") {
    std::multiset<Data::Card> expect = {
        Data::Card {2, 'H'}, Data::Card {3, 'D'}, Data::Card {5, 'S'},
        Data::Card {9, 'C'}, Data::Card {12, 'D'}
    };

    std::array<std::string, 5> input = { "2H", "3D", "5S", "9C", "KD" };
    std::multiset<Data::Card> actual = Parser::CreateHand(input);

    REQUIRE(expect == actual);
}

TEST_CASE("Can get straights from a poker hand") {
    SECTION("Get straight beginning with Ace") {
        Data::PokerHand expected{ Data::PokerHandType::Straight, 5 };
        std::multiset<Data::Card> input = {
            {13, 'H'}, { 2, 'H' }, { 3, 'H' }, { 4, 'H' }, { 5, 'H' } 
        };
        
        Data::PokerHand actual = Eval::GetStraight(input);

        REQUIRE(expected == actual);
    }

    SECTION("Get straight ending with Ace") {
        Data::PokerHand expected{ Data::PokerHandType::Straight, 13 };
        std::multiset<Data::Card> input = {
            { 13, 'H' },{ 9, 'H' },{ 10, 'H' },{ 11, 'H' },{ 12, 'H' }
        };

        Data::PokerHand actual = Eval::GetStraight(input);

        REQUIRE(expected == actual);
    }

    SECTION("Get straight with no Ace") {
        Data::PokerHand expected{ Data::PokerHandType::Straight, 6 };
        std::multiset<Data::Card> input = {
            { 6, 'H' },{ 2, 'H' },{ 3, 'H' },{ 4, 'H' },{ 5, 'H' }
        };

        Data::PokerHand actual = Eval::GetStraight(input);

        REQUIRE(expected == actual);
    }
}