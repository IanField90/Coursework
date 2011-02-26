#include <iostream>
#define AMOUNT 1308
using namespace std;
int fifty(int value);
int twenty(int value);
int ten(int value);
int fives(int value);
int twos(int value);
// NOTE: Can state that modulus is used and therefore a set number of steps however large the
// value of change would be.
int main (){
	int curAmount = AMOUNT;
	cout<< "Breakdown of amount: "<<AMOUNT << endl;
	cout<< "Fifties: " << fifty(curAmount) << endl;
	curAmount %= 50;
	
	cout<< "Twenties: " << twenty(curAmount) << endl;
	curAmount %= 20;

	cout<< "Tens: " << ten(curAmount)<< endl;
	curAmount %= 10;

	cout<< "Fives: " << fives(curAmount) << endl;
	curAmount %= 5;

	cout<< "Twos: " << twos(curAmount) << endl;
	cout<< "Ones: " << curAmount%2 << endl;


	system("PAUSE");
	return 0;
}

int fifty(int value){
	return value / 50;
}

int twenty(int value){
	return value / 20;
}

int ten(int value){
	return value/10;
}

int fives(int value){
	return value/5;
}

int twos(int value){
	return value/2;
}