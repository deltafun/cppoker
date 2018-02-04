#pragma once

#include "stdafx.h"

namespace Data {

    const std::map<char, int> Ranks = {
        { '2', 2 }, { '3', 3 }, { '4', 4 }, { '5', 5 }, { '6', 6 }, { '7', 7 },
        { '8', 8 }, { '9', 9 }, 
        { 'J', 10 }, { 'Q', 11 }, { 'K', 12 }, { 'A', 13 }
    };

    struct Card {
        int rank;
        char suit;
    };

    inline bool operator==(const Card& lhs, const Card& rhs) {
        return lhs.rank == rhs.rank && lhs.suit == rhs.suit;
    }
}

namespace Parser {
    std::array<std::array<std::string, 5>, 2> 
                                    SplitInputHands(const std::string& hands);
    std::vector<Data::Card> CreateHand(
        const std::array<std::string, 5> hand);
}