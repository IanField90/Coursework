#pragma once
#include "Card.h"

class Deck
{
public:
	Deck(void);
	~Deck(void);
	Card draw(int rand4, int rand13);
	Card getJoker(){return Joker;}; // Used to check draw function
	void setState(int ran4, int ran13, bool state); // Sets state of card at index [rand4][rand13]
private:
	Card Cards[4][13]; // Deck of cards 4 suits 13 cards in each suit
	Card Joker; // card in-use checker
};
