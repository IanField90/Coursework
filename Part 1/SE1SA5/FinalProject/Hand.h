#pragma once
#include "Card.h"
#include "Deck.h"
class Hand
{
public:
	Hand(Deck d); // Uses the deck to generate joker full hand
	~Hand(void);
	void addToHand(int rand1, int rand2, Deck d, int index); // Put the card in the hand - repeated until not joker
	Card getCard(int index){return Hand::playerHand[index];}; // Return the card at this location in the hand
private:
	Card playerHand[11]; // Used to store 11 different cards (maximum cards to draw to make 21
};
