#pragma once

#include "stdafx.h"

namespace Data {

    const std::map<char, int> Ranks = {
        { '2', 2 }, { '3', 3 }, { '4', 4 }, { '5', 5 }, { '6', 6 }, { '7', 7 },
        { '8', 8 }, { '9', 9 }, 
        { 'J', 10 }, { 'Q', 11 }, { 'K', 12 }, { 'A', 13 }
    };

    const std::map<char, int> Suits = {
        {'C', 0}, {'D', 1}, {'H', 2}, {'S', 3}
    };

    struct Card {
        int rank;
        int suit;

        Card(int rank, char suit) {
            this->rank = rank;
            this->suit = Data::Suits.at(suit);
        }

        Card(char rank, char suit) {
            this->rank = Data::Ranks.at(rank);
            this->suit = Data::Suits.at(suit);
        }
    };

    inline bool operator==(const Card& lhs, const Card& rhs) {
        return lhs.rank == rhs.rank && lhs.suit == rhs.suit;
    }

    inline bool operator<(const Card& lhs, const Card& rhs) {
        return lhs.rank < rhs.rank || 
              (lhs.rank == rhs.rank && lhs.suit < rhs.suit);
    }

    inline bool operator>(const Card& lhs, const Card& rhs) {
        return lhs.rank > rhs.rank ||
              (lhs.suit == rhs.rank && lhs.suit > rhs.suit);
    }
}

namespace Parser {
    std::array<std::array<std::string, 5>, 2> 
                                    SplitInputHands(const std::string& hands);
    std::set<Data::Card> CreateHand(
        const std::array<std::string, 5> hand);
}