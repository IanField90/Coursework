#include <iostream>
#define ARRAYSIZE 5
using namespace std;

float fToc(float f);
float cTof(float c);
float dblByVal(float x);
void dblByRef(float&);
int boxSA(int x, int y);
//Alpha sting
void arraySort(int *ArrayToSort);

template <typename T>
T Minimum(T *Values){
	int i;
	T answer = Values[0];
		for (i = 1; i < 4; i++){
			if(Values[i] < answer)
				answer = Values[i];
		}
	return answer;
}

int main(){
	float fValueArray[4], fTemperature = 38.2, cTemperature = 22, single = 4.32;
	char cValueArray[4];
	int i, dimX = 10, dimY = 20;

	cout << "The value of single is: " << single << endl;
	cout << "Double single is: " << dblByVal(single) << endl;

	cout << "The value of single is: " << single << endl;
	dblByRef(single);
	cout << "The value of single after dblByRef is now: " << single << endl;
	

	cout << "The temperature in Farenheit is: " << fTemperature << endl;
	cout << "This temperature in Celcius is: " << fToc(fTemperature) << endl;

	cout << "The temperature in Celcius is: " << cTemperature << endl;
	cout << "This temperature in Farenheit is: " << cTof(cTemperature) << endl;


	cout << "The dimensions of the box are: " << dimX << " x " << dimY << endl;
	cout << "The Surface area of the bos is: " << boxSA(dimX, dimY) << endl;


	cout << "Please input 4 float values: " << endl;
	for(i = 0; i < 4; i++){
		cin >> fValueArray[i];
	}

	cout << "The minimum value is: " << Minimum(fValueArray) << endl;
	
	cout << "Please input 4 char values: " << endl;
	for (i = 0; i < 4; i++){
		cin >> cValueArray[i];
	}
	cout << "The minimum value is: " << Minimum(cValueArray) << endl;

	//Alpha sting
	int UnsortedArray[ARRAYSIZE] = {89, 32, 7, 90, 4};
	cout << "Array contains: " << endl;
	for (i = 0; i < ARRAYSIZE; i++){
		cout << UnsortedArray[i] << ", ";
	}

	arraySort(UnsortedArray);
	cout << endl << "After sort Array is now: " <<endl;
	for (i = 0; i < ARRAYSIZE; i++){
		cout << UnsortedArray[i] << ", ";
	}

	system("PAUSE");
	return 0;
}

float fToc(float f){
	return ((f-32) / 9)*5;
}

float cTof(float c){
	return ((c/5)*9) + 32;
}

float dblByVal(float x){
	return (x + x);
}
void dblByRef(float& a){
	a = a + a;
}

int boxSA(int x, int y){
	return x * y;
}

//Alpha Sting
void arraySort(int *ArrayToSort){
	int i, j, temp;
	for (i = 0; i < ARRAYSIZE-1; i++){
		for (j = 0; j < ARRAYSIZE-1; j++){
			if (ArrayToSort[j] > ArrayToSort[j+1]){
				temp = ArrayToSort[j+1];
				ArrayToSort[j+1] = ArrayToSort[j];
				ArrayToSort[j] = temp;
			}
		}
	}
}