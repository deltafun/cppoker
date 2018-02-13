#pragma once

#include "stdafx.h"

namespace Data {

    enum PokerHandType {
        HighCard, OnePair, TwoPair, ThreeOfAKind, Straight, Flush, FullHouse,
        FourOfAKind, StraightFlush
    };

    const std::map<PokerHandType, std::string> PrintPokerHandType = {
        {HighCard, "high card"}, {OnePair, "one pair"}, {TwoPair, "two pair"},
        {ThreeOfAKind, "three of a kind"}, {Straight, "straight"},
        {Flush, "flush"}, {FullHouse, "full house"}, 
        {FourOfAKind, "four of a kind"}, {StraightFlush, "straight flush"}
    };

    const std::map<char, int> Ranks = {
        { '2', 2 }, { '3', 3 }, { '4', 4 }, { '5', 5 }, { '6', 6 }, { '7', 7 },
        { '8', 8 }, { '9', 9 }, 
        { 'J', 10 }, { 'Q', 11 }, { 'K', 12 }, { 'A', 13 }
    };

    const std::map<int, std::string> PrintRanks = {
        {10, "Jack"}, {11, "Queen"}, {12, "King"}, {13, "Ace"}
    };

    struct Card {
        int rank;
        char suit;

        Card(int rank, char suit) {
            this->rank = rank;
            this->suit = suit;
        }

        Card(char rank, char suit) {
            this->rank = Data::Ranks.at(rank);
            this->suit = suit;
        }

    };

    inline bool operator==(const Card& lhs, const Card& rhs) {
        return lhs.rank == rhs.rank;
    }

    inline bool operator<(const Card& lhs, const Card& rhs) {
        return lhs.rank < rhs.rank;
    }

    inline bool operator>(const Card& lhs, const Card& rhs) {
        return lhs.rank > rhs.rank;
    }

    struct PokerHand {
        PokerHandType type;
        int value;

        PokerHand(PokerHandType type, int value) : type(type), value(value) {}
    };

    inline bool operator==(const PokerHand& lhs, const PokerHand& rhs) {
        return lhs.type == rhs.type && lhs.value == rhs.value;
    }

    inline bool operator!=(const PokerHand& lhs, const PokerHand& rhs) {
        return lhs.type != rhs.type || lhs.value != rhs.value;
    }

    inline bool operator<(const PokerHand& lhs, const PokerHand& rhs) {
        return lhs.type < rhs.type 
            || (lhs.type == rhs.type && lhs.value < rhs.value);
    }

    inline bool operator>(const PokerHand& lhs, const PokerHand& rhs) {
        return lhs.type > rhs.type 
            || (lhs.type == rhs.type && lhs.value > rhs.value);
    }

    inline std::ostream& operator<<(std::ostream& os, const PokerHand& hand) {
        os << "(" << hand.type << ", " << hand.value << ")";
        return os;
    }
}

namespace Parser {
    std::array<std::array<std::string, 5>, 2> SplitInputHands(
        const std::string& hands);
    std::multiset<Data::Card> CreateHand(
        const std::array<std::string, 5>& hand);
}

namespace Eval {
    Data::PokerHand GetStraight(const std::multiset<Data::Card>& hand);
    Data::PokerHand GetFlush(const std::multiset<Data::Card>& hand);
    std::set<Data::PokerHand> GetPairs(const std::multiset<Data::Card>& hand);
    Data::PokerHand GetThreeOrFourOfAKind(
        const std::multiset<Data::Card>& hand);
    Data::PokerHand GetHighCard(const std::multiset<Data::Card>& hand);
    Data::PokerHand GetPokerHand(const std::multiset<Data::Card>& hand);
}

namespace Game {
    std::string PlayPoker(const std::string& hands);
}