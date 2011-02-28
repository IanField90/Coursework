#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#define TWIST_LIMIT 16
using namespace std;
int generateRandom(int max);
void printCardSuit(Card toPrint);
void printCard(Card toPrint);
void printOptions(int value, Hand pHand, Deck GameDeck, bool stuck, int index);
int calculateHandValue(Hand myHand);
void gameLoop();
void playerTurn(Hand playerCards, Deck GameDeck, int twistIndex);
void computeWinner(Hand computerCards, Hand playerCards);

int main (){
	// print introduction to user
	// FILE version - works if .exe executed directly
	char ruleLetter;
	ifstream ruleFile("Rules.txt");
	if (ruleFile.is_open())
	{
		while(!ruleFile.eof())
		{
			ruleFile.get(ruleLetter);
			cout << ruleLetter;
		}
		ruleFile.close();
	}

	else { // if file open fails
			cout << "Hello, welcome to Ian Field's 21 Card game.\n"
		"The objective of the game is to obtain cards close or the same as "
		"the value 21.\n" 
		"In order to do this you are dealt 2 cards, values: 2-11.\n"
		"Aces count as 11, Number cards have their own values.\n"
		"Picture cards count as the value 10.\n\n"
		"Thus it is possible to obtain 21 from the dealt hand.\n"
		">> 'Busting' is when you have exceeded the value of 21.\n"
		"   When this occurrs your turn is ended.\n"
		">> 'Twisting' is when another card is dealt to you.\n"
		">> 'Sticking' is when you choose to end your turn.\n"
		"   After you have 'stuck' the computer takes it's turn.\n"
		">> 'Burning' is when your cards total X or less.\n"
		"   2 cards are then redealt to you.\n"
		"In the event of a tie. The House wins!\n" << endl;
	}

	// Force real randoms
	srand((int)time(NULL));
	int input;
	do{
		cout << "Enter 1) to play, 2) to exit\n";
		cin >> input;
		if(input == 1)
		{
			system("CLS");//not linux system("cl")
			gameLoop();
		}
		else if(input > 2 || input < 1)
			cout << "Invalid choice\n";
	}while(input != 2);

	return 0;
}

int generateRandom(int max)
{ 
	// generate random seeded from time to ensure true random
	// modulo max as max is index of array + 1
	// will only return 0 - max-1 resulting in no overflow errors
	return (int) rand() % max;
}

void printCardSuit(Card toPrint)
{
	// Spades = 0, Clubs = 1, Hearts = 2, Diamonds = 3
	switch (toPrint.getCardSuit())
	{
		case 0:
			cout << "Spades";
			break;
		case 1:
			cout << "Clubs";
			break;
		case 2:
			cout << "Hearts";
			break;
		case 3:
			cout << "Diamonds";
			break;
	}
}

// displays the information of the card passed
void printCard(Card toPrint)
{
	if(toPrint.getCardDisplay() == 'X')
		cout << "JOKER!\n"; // Used in debugging, should never occur
	else if(toPrint.getCardDisplay() == '!')
	{
		cout << toPrint.getCardValue() << " of "; printCardSuit(toPrint); cout << endl;// 2 of Hearts format
	}
	else
	{
		cout << toPrint.getCardDisplay() << " of "; printCardSuit(toPrint); cout << endl; // A of Hearts format;
	}
} 
// would include in deck class but linking error iostream
void printOptions(int value, Hand pHand, Deck GameDeck, bool stuck, int index)
{
	if(!stuck){
		
		if(value <= 12)
		{	
			// burnable
			cout << "\nThe value of your hand is: " << value <<
				"\nWould you like to:\n"
				"1) Stick\n"
				"2) Twist?\n"
				"3) Burn?\n";
				playerTurn(pHand, GameDeck, index); // 3rd card is next to draw
		}
		else if(value < 21)
		{
			//not burnable
			cout << "\nThe value of your hand is: " << value <<
				"\nWould you like to:\n"
				"1) Stick\n"
				"2) Twist?\n";
			playerTurn(pHand, GameDeck, index); // 3rd card is next to draw
		}
	}
}

// Cycles through the hand passed and sums
// values of the cards.
// As hands are initialised to have all jokers
// the jokers are not totaled up
int calculateHandValue(Hand myHand)
{
	int total = 0;
	for(int i = 0; i < 11; i++)
	{
		if(myHand.getCard(i).getCardDisplay() != 'X')
			total += myHand.getCard(i).getCardValue();
	}
	return total;
}

void gameLoop()
{
	//MAKE DECK & HANDS - NOTE: Redeclare each game loop
	Deck GameDeck; // 52 cards, 4 suits, 13 different values
	Hand compHand(GameDeck), pHand(GameDeck);
	srand((int)time(NULL)); // random within loop

	// Get initial cards for computer 2 cards randomly selected
	do{
		compHand.addToHand(generateRandom(4), generateRandom(13), GameDeck, 0);
	}while(compHand.getCard(0).getCardDisplay() == 'X'); // Joker check
	// Ensures that the card generated is not joker i.e. has not been used
	do{
		compHand.addToHand(generateRandom(4), generateRandom(13), GameDeck, 1);
	}while(compHand.getCard(1).getCardDisplay() == 'X'); // Joker check
	// Ensures that the card generated is not joker i.e. has not been used

	// Get initial cards for player
	do{
		pHand.addToHand(generateRandom(4), generateRandom(13), GameDeck, 0);
	}while(pHand.getCard(0).getCardDisplay() == 'X'); // Joker check
	// Ensures that the card generated is not joker i.e. has not been used
	do{
		pHand.addToHand(generateRandom(4), generateRandom(13), GameDeck, 1);
	}while(pHand.getCard(1).getCardDisplay() == 'X'); // Joker check
	// Ensures that the card generated is not joker i.e. has not been used
	
	// Show player cards
	cout << "Your hand is:\n";
	// prints the first two player's cards to user
	printCard(pHand.getCard(0));
	printCard(pHand.getCard(1));

	// if not already at 21, 22 is dual ace auto bust
	if(calculateHandValue(pHand) <= 21)
	{
		// passes hand value, player hand, deck and false (not stuck) and index 2
		// to print options. Ensuring if card is drawn the card does not replace
		// an existing card
		printOptions(calculateHandValue(pHand), pHand, GameDeck, false, 2);
		
		// 'AI loop'
		while(calculateHandValue(compHand) <= TWIST_LIMIT)
		{
			int twistIndex = 2;
			do{
				compHand.addToHand(generateRandom(4), generateRandom(13), GameDeck, twistIndex);
			}while(compHand.getCard(twistIndex).getCardDisplay() == 'X'); // Joker check
			// Ensures that the card generated is not joker i.e. has not been used
			twistIndex++;
		}
		computeWinner(compHand, pHand);
	}
	else if (pHand.getCard(0).getCardDisplay() == 'A' && pHand.getCard(1).getCardDisplay() == 'A')
			cout << "Dual Ace Bust\n";
}
void playerTurn(Hand playerCards, Deck GameDeck, int twistIndex)
{
	int usrOption;
	cin >> usrOption; // Take option from user either 1, 2 or 3. Any other is erroneous
	if(calculateHandValue(playerCards) <=12 && usrOption == 3)
	{
		// burn - redeal
		cout << "Burning\n";
		do{
			playerCards.addToHand(generateRandom(4), generateRandom(13), GameDeck, 0);
		}while(playerCards.getCard(0).getCardDisplay() == 'X'); // Joker check
		// Ensures that the card generated is not joker i.e. has not been used

		do{
			playerCards.addToHand(generateRandom(4), generateRandom(13), GameDeck, 1);
		}while(playerCards.getCard(1).getCardDisplay() == 'X'); // Joker check
		// Ensures that the card generated is not joker i.e. has not been used
		
		// Display cards
		cout << "Your hand is:\n";
		printCard(playerCards.getCard(0));
		printCard(playerCards.getCard(1));

		// passes hand value, player hand, deck and false (not stuck) and index
		// to print options. Using Index Ensures card is drawn the card does not replace
		// an existing card
		printOptions(calculateHandValue(playerCards), playerCards, GameDeck, false, twistIndex);
	}
	else if(usrOption == 2 && calculateHandValue(playerCards) < 21)
	{
		// twist
		cout << "Twisting\n";
		if(playerCards.getCard(twistIndex).getCardDisplay() == 'X')
		{
			//stuff
			do{
				playerCards.addToHand(generateRandom(4), generateRandom(13), GameDeck, twistIndex);
			}while(playerCards.getCard(twistIndex).getCardDisplay() == 'X'); // Joker check
			// Ensures that the card generated is not joker i.e. has not been used
			twistIndex++;

			cout << "Your hand is:\n";
			for(int j = 0; j < 11; j++)
			{
				if(playerCards.getCard(j).getCardDisplay() != 'X')
					printCard(playerCards.getCard(j));
			}
		}
		//end if
		printOptions(calculateHandValue(playerCards), playerCards, GameDeck, false, twistIndex);
	}
	else if(usrOption == 1)
	{
		// stick - begin comp turn
		cout << "Stuck\n";
		// Causes loop to exit - Computer turn now begins
	}
	else
	{
		cout << "Invalid option, please retry\n";
		printOptions(calculateHandValue(playerCards), playerCards, GameDeck, false, twistIndex);
	}
}

void computeWinner(Hand computerCards, Hand playerCards)
{
	// As computer wins when it has 21 reguardless
	// this case is first
	if(calculateHandValue(computerCards) == 21)
	{
		cout << "Computer wins with 21 hand!\n";
	}
	// If player has 21 and computer doesn't
	// they win
	else if(calculateHandValue(playerCards) == 21)
	{
		cout << "You win!\n"
			"Computer had:\n";
		// Display all cards in computers hand that aren't Jokers
		// This proves to the player no foul play
		for(int j = 0; j < 11; j++)
		{
			if(computerCards.getCard(j).getCardDisplay() != 'X')
				printCard(computerCards.getCard(j));
		}
	}
	// If computer hasn't busted and has a higher score than the player computer wins
	else if((calculateHandValue(computerCards) > calculateHandValue(playerCards)) && (calculateHandValue(computerCards) < 21))
	{
		cout << "Computer wins! With: \n";
		// Display all cards in computers hand that aren't Jokers
		// This proves to the player no foul play
		for(int j = 0; j < 11; j++)
		{
			if(computerCards.getCard(j).getCardDisplay() != 'X')
				printCard(computerCards.getCard(j));
		}
		cout << "Computer cards value is: " << calculateHandValue(computerCards) << endl;
	}
	// If player hasn't busted and has a higher score than computer
	else if((calculateHandValue(computerCards) < calculateHandValue(playerCards)) && calculateHandValue(playerCards) < 21)
	{
		cout << "You win!\n"
			"Computer had:\n";
		// Display all cards in computers hand that aren't Jokers
		// This proves to the player no foul play
		for(int j = 0; j < 11; j++)
		{
			if(computerCards.getCard(j).getCardDisplay() != 'X')
			printCard(computerCards.getCard(j));
		}
	}
	// If player has busted. At this stage computer 'wins'
	else if(calculateHandValue(playerCards) > 21)
		cout << "You've busted!\n";
	else
	{ // If computer busted
		cout << "You win!\n" 
			"Computer had:\n";
		for(int j = 0; j < 11; j++)
		{
			if(computerCards.getCard(j).getCardDisplay() != 'X')
			printCard(computerCards.getCard(j));
		}
		cout << "Computer busted!\n";
	}
}