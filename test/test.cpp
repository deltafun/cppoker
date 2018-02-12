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
        Data::PokerHand expected{ Data::Straight, 5 };
        std::multiset<Data::Card> input = {
            {13, 'H'}, { 2, 'H' }, { 3, 'H' }, { 4, 'H' }, { 5, 'H' } 
        };
        
        Data::PokerHand actual = Eval::GetStraight(input);

        REQUIRE(expected == actual);
    }

    SECTION("Get straight ending with Ace") {
        Data::PokerHand expected{ Data::Straight, 13 };
        std::multiset<Data::Card> input = {
            { 13, 'H' },{ 9, 'H' },{ 10, 'H' },{ 11, 'H' },{ 12, 'H' }
        };

        Data::PokerHand actual = Eval::GetStraight(input);

        REQUIRE(expected == actual);
    }

    SECTION("Get straight with no Ace") {
        Data::PokerHand expected{ Data::Straight, 6 };
        std::multiset<Data::Card> input = {
            { 6, 'H' },{ 2, 'H' },{ 3, 'H' },{ 4, 'H' },{ 5, 'H' }
        };

        Data::PokerHand actual = Eval::GetStraight(input);

        REQUIRE(expected == actual);
    }
}

TEST_CASE("Can get flush from a poker hand") {
    Data::PokerHand expected{ Data::Flush, 13 };
    std::multiset<Data::Card> input = {
        { 13, 'H' },{ 9, 'H' },{ 10, 'H' },{ 11, 'H' },{ 12, 'H' }
    };

    Data::PokerHand actual = Eval::GetFlush(input);

    REQUIRE(expected == actual);
}

TEST_CASE("Can get pairs from a poker hand") {
    std::set<Data::PokerHand> expected = {
        {Data::OnePair, 13}, {Data::OnePair, 10}
    };

    std::multiset<Data::Card> input = {
        { 13, 'H' },{ 10, 'H' },{ 13, 'H' },{ 11, 'H' },{ 10, 'H' }
    };

    std::set<Data::PokerHand> actual = Eval::GetPairs(input);

    REQUIRE(expected == actual);
}

TEST_CASE("Can get 3 of a kind") {
    Data::PokerHand expected{ Data::ThreeOfAKind, 13 };
    std::multiset<Data::Card> input = {
        { 13, 'H' },{ 9, 'H' },{ 13, 'D' },{ 13, 'C' },{ 12, 'H' }
    };

    Data::PokerHand actual = Eval::GetThreeOrFourOfAKind(input);

    REQUIRE(expected == actual);
}

TEST_CASE("Can get 4 of a kind") {
    Data::PokerHand expected{ Data::FourOfAKind, 13 };
    std::multiset<Data::Card> input = {
        { 13, 'H' },{ 9, 'H' },{ 13, 'D' },{ 13, 'C' },{ 13, 'S' }
    };

    Data::PokerHand actual = Eval::GetThreeOrFourOfAKind(input);

    REQUIRE(expected == actual);
}

TEST_CASE("Poker hand evaluators default to high card") {
    std::multiset<Data::Card> input = {
        { 13, 'H' },{ 2, 'D' },{ 10, 'H' },{ 11, 'H' },{ 12, 'H' }
    };

    Data::PokerHand expected{ Data::PokerHandType::HighCard, 13 };
    std::set<Data::PokerHand> expectedPairs = { { Data::HighCard, 13 } };

    SECTION("not a straight") {
        Data::PokerHand actual = Eval::GetStraight(input);
        REQUIRE(expected == actual);
    }

    SECTION("not a flush") {
        Data::PokerHand actual = Eval::GetFlush(input);
        REQUIRE(expected == actual);
    }

    SECTION("no pairs") {
        std::set<Data::PokerHand> actual = Eval::GetPairs(input);
        REQUIRE(expectedPairs == actual);
    }

    SECTION("neither 3 nor 4 of kind") {
        Data::PokerHand actual = Eval::GetThreeOrFourOfAKind(input);
        REQUIRE(expected == actual);
    }
}