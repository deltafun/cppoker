#pragma once

#include "stdafx.h"

namespace Parser {
    std::array<std::array<std::string, 5>, 2> 
                                    SplitInputHands(const std::string& hands);
}


enum class Suit { Diamonds, Hearts, Clubs, Spades };

enum class Rank {
    Two, Three, Four, Five, Six, Seven, Eight, Nine, Jack, Queen, King, Ace
};

struct Card {
    const Rank rank;
    const Suit suit;
};

struct PokerHand {
    const std::array<Card, 5> cards;
    const Rank highCard;
};