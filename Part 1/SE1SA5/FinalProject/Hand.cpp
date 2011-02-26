#include "Hand.h"

Hand::Hand(Deck d)
{	// 11 cards is maximum to create 21, 4 x A, 4 x 2, 3 x 3
	// initialise all cards to joker for future calculations
	for(int i = 0; i < 11; i++)
		Hand::playerHand[i] = d.getJoker();
}

Hand::~Hand(void)
{
}
void Hand::addToHand(int rand1, int rand2, Deck d, int index)
{
			Hand::playerHand[index] = d.draw(rand1, rand2); 
			// place new card at index
			// new rands generated if draw() returns joker
}