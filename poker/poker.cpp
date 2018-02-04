// poker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "poker.h"

namespace Parser {

    std::array<std::array<std::string, 5>, 2> 
                                    SplitInputHands(const std::string& hands) {
        const int numTokens = 12; // "player: <hand> player: <hand>" gives 12

        std::array<std::array<std::string, 5>, 2> res;

        std::string buf;
        std::istringstream ss(hands);
        
        for (int i = 0; i < numTokens; ++i) {
            ss >> buf;
            if (buf.length() == 2) { // card is 2 char: <Rank><Suit>
                // literally the number 6
                int player = i < numTokens / 2 ? 0 : 1;
                int card = i < numTokens / 2 
                    ? i - 1 :  i - 1 - numTokens / 2;
                res[player][card] = buf;
            }
        }

        return res;
    }

    std::vector<Data::Card> CreateHand(
            const std::array<std::string, 5> hand) {
        std::vector<Data::Card> res;
        res.reserve(5);

        for (const std::string& s : hand) {
            Data::Card card;
            card.rank = Data::Ranks.at(s[0]);
            card.suit = s[1];

            res.emplace_back(card);
        }

        return res;
    }
}


int main()
{
    return 0;
}