#include "PiggyBank.h"
#include <iostream>
// Alpha sting
#define BANKS 100
using namespace std;

void transfer(float amount, PiggyBank &, PiggyBank &);
int main(){

	PiggyBank mine(250), yours ;
	cout<<"Account number (mine): " <<mine.getAccountNo() << endl;
	cout<< "Balance: " << mine.getBalance() << endl;
	mine.deposit (50);
	cout<< "After depositing 50: \n" << mine.getBalance() << endl;
	mine.withdraw (100);
	cout<< "After Withdrawing 100: \n" << mine.getBalance() << endl;

	cout<<"Account number (yours): " << yours.getAccountNo() << endl;
	// Initialised with no parameters meaning balance is 0
	cout<< "Balance: " << yours.getBalance() << endl;

	transfer (50, mine, yours);

	cout<< "After transfer" << endl;
	cout<< "Account number (mine): " << mine.getAccountNo() << endl;
	cout<< "Balance: " << mine.getBalance() << endl;
	cout<< "Account number (yours): " << yours.getAccountNo() << endl;
	cout<< "Balance: " <<yours.getBalance() << endl;


	// Alpha sting
	PiggyBank pBanks[BANKS];
	// Demo of same transaction on all Piggy Banks
	for(int i=0; i<BANKS; i++){
		pBanks[i].deposit(100);
		cout << "pBank["<<i<<"] now has a balance of: "<< pBanks[i].getBalance()<<endl;
	}

	// Single transfer between bank 3 and 37

	transfer(50, pBanks[3], pBanks[37]);
	cout << "Piggy bank 3 now has a balance of: " << pBanks[3].getBalance() << endl;
	cout << "Piggy bank 37 now has a balance of: " << pBanks[37].getBalance() << endl;


	// Allow user to see the results
	system("PAUSE");
	return 0;
}
void transfer (float amount, PiggyBank &payer, PiggyBank &payee){
	if (payer.getBalance() < amount)
		std::cout << "Not enough money available for transfer\n";
	else
	{
		payer.withdraw(amount);
		payee.deposit(amount);
	}
}