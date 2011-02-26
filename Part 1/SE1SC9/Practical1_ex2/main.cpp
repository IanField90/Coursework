#include <iostream>
#define SIZE 15
using namespace std;

bool Unique (int *array);
int icount = 0, jcount = 0;

int main (){
	int myArray[SIZE] = {8, 17, 38, 2, 4, 73, 2, 8, 18, 23, 27, 13, 22, 1372, 211};
	bool result;
	
	result = Unique(myArray);
	cout << "1 is distinct, 0 is not distinct. The result is: " << result << endl;
	cout << "The value of icount is: " << icount << endl;
	cout << "The value of jcount is: " << jcount << endl;
	system("PAUSE"); // Allow user to see result
	return 0;
}

bool Unique (int *array){
	
	for(int i = 0; i < SIZE; i++){
		icount++;
		for(int j = 1; j < SIZE; j++){
			if(i != j){
				if(array[i] == array[j]){
					return false;
				}
			} 
			jcount++;
		}
	}
	return true; // if none match after searching entire array
}