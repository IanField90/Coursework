#include <iostream>
#include <math.h>
#define VALUE 2.3
// Enciphering power
#define P 7
// Deciphering power
#define Q 23
// Modulo
#define R 55

using namespace std;

float square(float val);
int cipher(char val, int order, int modulo);

int main (){
	// a)
	// f # g
	cout << "i) Function g into f " << square(sqrt(VALUE)) << endl;

	// g # f
	cout << "ii) Function f into g " << sqrt(square(VALUE)) << endl;

	// b)
	char input;
	// tables irrelevent as only related to keys
	int enciphered, deciphered;

	cout << "Please enter a letter to be enciphered: ";
	cin >> input;

	// Does not work with input number greater than 54

	enciphered = cipher(input, P, R);
	cout << "The result after enciphering is: " << enciphered << endl;

	deciphered = cipher(enciphered, Q, R);
	cout << "The result after deciphering is: " << deciphered << endl;

	system("PAUSE");
	return 0;
}

float square(float val){
	return val*val;
}

int cipher(char val, int order, int modulo){
	int result = val;
	// Start at one as assignment = ^1
	for(int i = 1; i < order; i++){
		result = (result * val) % modulo;
	}
	return result;
}