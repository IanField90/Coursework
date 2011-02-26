#include "Deck.h"

Deck::Deck(void)
{
	//loop through each suit value
	// Spades = 0, Clubs = 1, Hearts = 2, Diamonds = 3
	for(int i = 0; i < 4; i++)
	{
		//loop through each card value
		for(int j = 0; j < 13; j++)
		{
			// j is card value - 1
			if(j == 0)
			{
				//if Ace
				Deck::Cards[i][j].Create(i, 11, 'A');
			}
			else if(j == 10)
			{
				//if Jack
				Deck::Cards[i][j].Create(i, 10, 'J');
			}
			else if (j == 11)
			{
				//if Queen
				Deck::Cards[i][j].Create(i, 10, 'Q');
			}
			else if (j == 12)
			{
				//if King
				Deck::Cards[i][j].Create(i, 10, 'K');
			}
			else 
				Deck::Cards[i][j].Create(i, j+1); // default symbol assigned to ! used to check print value
		}
	}
	Deck::Joker.Create(100, 100, 'X');
	// End of Deck creation. All cards populated
}

Deck::~Deck(void)
{
}

Card Deck::draw(int rand4, int rand13)
{
	if(Deck::Cards[rand4][rand13].getCardState() == false)
	{
		Deck::setState(rand4, rand13, true); // set in use
		return Deck::Cards[rand4][rand13]; // give caller the card
	}
	else
		return Deck::getJoker();
	// used in Joker check later to ensure drawn card is usable
	// otherwise random numbers are regenerated
}

void Deck::setState(int ran4, int ran13, bool state)
{
	Deck::Cards[ran4][ran13].setCardState(state); // change the card state to in use
}