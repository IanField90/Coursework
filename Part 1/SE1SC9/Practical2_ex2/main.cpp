#include <iostream>
#define SIZE 4
using namespace std;
	// L4 relationship slide 7.
	//			London, Slough, Reading, Oxford
	//London	0		1			0		1
	//Slough	1		0			1		0 
	//Reading	0		1			0		1
	//Oxford	1		0			1		0
bool myMatrix[SIZE][SIZE] = {
		{false,true,false,true}, 
		{true,false,true,false},
		{false,true,false,true},
		{true,false,true,false}
	};

int main()
{
	int A = 0, B = 2;

	bool transitiveFlag = true;
	for(int k = B; k > A; k--)
	{
		if(myMatrix[k][k-1] == false)
			transitiveFlag = false;
	}
	// Anti-symmetric
	// Rn = Rr U Ra
	// Reflexive OR Asymmetric
	if(((A == B) && myMatrix[B][B]) || (myMatrix[A][B] != myMatrix[B][A]))
		cout <<"Anti-symmetrical\n";
	
	// Equivalence
	// Re = Rr U Rs U Rt
	// Reflexive OR Symmetric OR Transitive

	else if((myMatrix[A][A]) || (myMatrix[A][B] && myMatrix[B][A]) || transitiveFlag)
		cout << "Equivalent\n";

	// A poset (Partial order)
	// Rp = Rr U Rn U Rt
	// Reflexive OR Anti-Symmetric OR Transitive
	else if( ((A == B) && myMatrix[A][A] )    ||    ((myMatrix[A][A] && myMatrix[B][B]) 
		|| (myMatrix[A][B] != myMatrix[B][A]))   ||   (transitiveFlag))
		cout << "A poset\n";

	else
		cout << "Neither Anti-symmetrical, equivalent or a poset\n";


	system("PAUSE");
	return 0;
}