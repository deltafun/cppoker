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

        for (auto it = ++hand.cbegin(); it != hand.end(); ++it) {
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

    Data::PokerHand GetFlush(const std::multiset<Data::Card>& hand) {
        Data::PokerHand highCard = GetHighCard(hand);

        char suit = hand.begin()->suit;

        for (const Data::Card& card : hand) {
            if (card.suit != suit)
                return highCard;
        }

        return { Data::Flush, highCard.value };
    }

    std::set<Data::PokerHand> GetPairs(const std::multiset<Data::Card>& hand) {
        std::set<Data::PokerHand> res;
        int rankToMatch = -1;

        for (auto it = hand.cbegin(); it != hand.end(); ++it) {
            if (it->rank == rankToMatch) {
                res.emplace(Data::OnePair, it->rank);
                rankToMatch = -1;
            }
            else {
                rankToMatch = it->rank;
            }
        }

        if (res.empty())
            res.emplace(GetHighCard(hand));

        return res;
    }

    Data::PokerHand GetThreeOrFourOfAKind(
            const std::multiset<Data::Card>& hand) {
        int rankToMatch = -1;
        int totalMatched = 1;

        for (auto it = hand.cbegin(); it != hand.end(); ++it) {
            if (it->rank == rankToMatch) {
                ++totalMatched;
            }
            else if (totalMatched < 3) {
                rankToMatch = it->rank;
                totalMatched = 1;
            }
        }

        if (totalMatched == 4)
            return { Data::FourOfAKind, rankToMatch };
        else if (totalMatched == 3)
            return { Data::ThreeOfAKind, rankToMatch };
        else
            return { GetHighCard(hand) };
    }

    Data::PokerHand GetHighCard(const std::multiset<Data::Card>& hand) {
        return { Data::HighCard, hand.rbegin()->rank };
    }
}


int main()
{
    return 0;
}