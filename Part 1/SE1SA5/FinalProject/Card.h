#pragma once
class Card
{
public:
	// Default 'b' to be checked for non picture cards
	Card(void);
	~Card(void);

	bool getCardState(){return cardState;};
	void setCardState(bool state);
	int getCardSuit(){return cardSuit;};// Spades = 0, Clubs = 1, Hearts = 2, Diamonds = 3
	int getCardValue(){return cardValue;};
	char getCardDisplay(){return display;};
	void Create(int suit, int value, char name = '!'); // ! is default display value for non picture/joker cards

private:
	bool cardState;
	int cardValue;
	int cardSuit;// Spades = 0, Clubs = 1, Hearts = 2, Diamonds = 3
	char display;
};
