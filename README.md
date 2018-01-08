# C++ Poker

Simple project to practice VC++ and testing using Catch2.
The problem is to parse and evaluate two poker hands to see who is the winner.
See [`PROBLEM.txt`](PROBLEM.txt) for the complete description taken from Cyber-Dojo.org.

## Approach

Current approach is something like:

1. Parse input to seperate White's and Black's two hands.
2. Further parse this to create two Hands.
3. Evaluate the two Hands to get a valid PokerHand.
4. Return the winner of the duel.

Minimal validation. 
Assume they're dealt cards from two seperate decks, 
and if any hand is impossible, the hand gets the lowest possible ranking 
for that so-called hand.