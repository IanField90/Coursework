#include <iostream>
#define VALUE 3
using namespace std;

float fToC(float f);
float cToF(float c);
float dblByVal(float x);

int main ()
{
	cout << fToC(VALUE) << endl;
	cout << cToF(VALUE) << endl;
	cout << dblByVal(VALUE) << endl;
	system("PAUSE");
	return 0;
}

// Farenheit to Celcius conversion
// Injective function
float fToC(float f){
	return ((f-32) / 9)*5;
}

// Celcius to Farenheit conversion
// Injective function
float cToF(float c){
	return ((c/5)*9) + 32;
}

// Double function
// Injective function
float dblByVal(float x)
{
	return x+x;
}
