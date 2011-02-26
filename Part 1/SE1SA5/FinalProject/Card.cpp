#include "Card.h"

Card::Card(void)
{
}

Card::~Card(void)
{
}

void Card::Create(int suit, int value, char name)
{
	Card::cardSuit = suit; // Spades = 0, Clubs = 1, Hearts = 2, Diamonds = 3
	Card::cardState = false; // Not in use initially
	Card::cardValue = value; // Value of the card
	Card::display = name; // only for Jack, Queen, King and Ace
}

void Card::setCardState(bool state)
{
	Card::cardState = state; // Changes the card's state to in use
}