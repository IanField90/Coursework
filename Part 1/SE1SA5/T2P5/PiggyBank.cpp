#include "PiggyBank.h"
#include <iostream>

int PiggyBank::count = 0;
PiggyBank::PiggyBank ( float amount) 
{ 
	balance = amount;
	// using static. Incrementing count, sustains value even when out of scope
	// ?? Like a constant within class same throughout each instance of class
	count++;
	AccountNo = count; // unique account id
}

void PiggyBank::deposit ( float amount )
{
	balance += amount;
}

void PiggyBank::withdraw (float amount)
{
	if(balance > amount)
		balance -= amount;
	else
		std::cout << "Not enough money available\n";
}

// from, to
