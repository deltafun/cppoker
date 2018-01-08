#pragma once

#include "stdafx.h"

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

std::vector<std::string> SplitInputHands(std::string);
//std::vector<std::vector<std::string>> SplitHands(std::vector<std::string>);