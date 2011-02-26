#include <iostream>
#define SIZE 4
using namespace std;
int main (){
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
	int A = 1, B = 0;
	// Reflexive
	if( A == B){
		bool reflexiveFlag = myMatrix[A][B];
		if (reflexiveFlag == true){
			cout <<"Reflexive" << endl;
		}
		else
			cout <<"Not reflexive"<<endl;
	}
	// Symmetric
	else if(myMatrix[A][B] == true && myMatrix[B][A] == true)
		cout <<"Symmetrical\n";
	else{
		// Transitive
		bool transitiveFlag = true;
		for(int k = A; k > B; k--)
		{
			if(myMatrix[k][k-1] == false)
			transitiveFlag = false;
		}
		if(transitiveFlag)
			cout << "Transitive\n";
		else
			cout << "Neither Reflexive, Symmetrical or Transitive\n";
	}

	system("PAUSE");
	return 0;
}
