#include <iostream>
#define SIZE 5
using namespace std;

void Maximum(int *array);
int _count = 0, result;

int main(int argc, char * const argv[]) {
	int myArray[SIZE] = {26, 83, 63, 3, 18 }; // Not counted as a step as it would created elsewhere
	
	Maximum(myArray);

	cout << "Array maximum is: " << result << endl;
	cout << "\nCount is: " << _count << endl;

	system("PAUSE");
	return 0;
}

void Maximum(int *array){
	result = array[0];

	for(int i = 1; i<SIZE; i++){
		
		if(array[i] > result){		
			result = array[i];
		}
		_count++; // For loop
	}
}