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

    std::multiset<Data::Card> CreateHand(
            const std::array<std::string, 5>& hand) {
        std::multiset<Data::Card> res;

        for (const std::string& s : hand) {
            // <rank><suit>
            res.emplace(s[0], s[1]);
        }

        return res;
    }
}

namespace Eval {
    Data::PokerHand GetStraight(const std::multiset<Data::Card>& hand) {
        Data::PokerHand highCard = GetHighCard(hand);
        int cardsInSequence = 0;
        int lastCardRank = hand.begin()->rank;

        bool straightBeginsWithAce = false;

        for (auto it = ++hand.begin(); it != hand.end(); ++it) {
            if (lastCardRank + 1 == it->rank) {
                ++cardsInSequence;
            }
            // check for straight starting with Ace
            else if (it->rank == 13 
                     && cardsInSequence == hand.size() - 2
                     && lastCardRank == 2 + (hand.size() - 2)) {
                ++cardsInSequence;
                straightBeginsWithAce = true;
            } 

            lastCardRank = it->rank;
        }

        int highCardValue = straightBeginsWithAce
            ? 2 + (hand.size() - 2)
            : highCard.value;

        return cardsInSequence == hand.size() - 1
            ? Data::PokerHand{ Data::Straight, highCardValue }
            : highCard;
    }

    Data::PokerHand GetHighCard(const std::multiset<Data::Card>& hand) {
        return { Data::HighCard, hand.rbegin()->rank };
    }
}


int main()
{
    return 0;
}