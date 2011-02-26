#include <iostream>
using namespace std;

int function(int n);
int main ()
{
	int n, result = 7;
	// a) Iterative
	do{
		n = result;
		if(n == 1)
			result = 1;
		else if( (n%2) == 0)
			result = n/2;
		else if( (n%2) == 1)
			result = (3*n) + 1;
	}while(result !=1);
	cout << result << endl;

	// b) Recursive
	cout << function(7) << endl;
	// Total funciton if real numbers are used as input
	//  if input <= 0 error 


	system("PAUSE");
	return 0;
}	

// b) Recursive
int function(int n)
{
	if(n == 1)
		return 1;
	else if( (n%2) == 0)
		function(n/2);
	else if( (n%2) == 1)
		function((3*n) + 1);
}