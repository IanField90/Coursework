#include <iostream>
#define SIZE 4
using namespace std;
void MatAdd(bool A[SIZE][SIZE], bool B[SIZE][SIZE], bool C[SIZE][SIZE]);
void MatMult(bool A[SIZE][SIZE], bool B[SIZE][SIZE], bool C[SIZE][SIZE]);

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

	// L4 relationship slide 7 1's to 0 and 0 to 1.
	//			London, Slough, Reading, Oxford
	//London	1		0			1		0
	//Slough	0		1			0		1 
	//Reading	1		0			1		0
	//Oxford	0		1			0		1
bool myMatrixReversed[SIZE][SIZE] = {
		{true,false,true,false},
		{false,true,false,true},
		{true,false,true,false},
		{false,true,false,true} 
};

bool group1_1[4][4] = {
	{1,1,0,0},
	{1,1,1,0},
	{0,1,1,1},
	{0,0,1,1}
};

bool group1_2[5][5] = {
	{0,1,0,0,0},
	{0,0,1,0,0},
	{0,0,0,1,0},
	{0,0,0,0,1},
	{0,0,0,0,0}
};

bool group1_3[12][12] = {
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0},
	{0,1,0,0,0,0,0,0,0,0,0,0},
	{0,1,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,0,0,1,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,1,0}
};

bool group2_1[4][4] = {
	{0,1,0,0},
	{0,0,1,0},
	{1,0,0,0},
	{1,0,0,0}
};

bool group2_2[4][4] = {
	{0,1,0,0},
	{0,0,0,1},
	{1,0,0,0},
	{0,0,1,0}
};

bool group2_3[3][3] = {
	{1,0,0},
	{1,0,0},
	{1,0,0}
};

bool resultMatrix[SIZE][SIZE] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};

int main ()
{
	MatMult(myMatrix, myMatrixReversed, resultMatrix);
	MatAdd(myMatrix, myMatrixReversed, resultMatrix);

	system("PAUSE");
	return 0;
}

void MatAdd(bool A[SIZE][SIZE], bool B[SIZE][SIZE], bool C[SIZE][SIZE])
{

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			C[i][j] = A[i][j] || B[i][j];
		}
	}
}

void MatMult(bool A[SIZE][SIZE], bool B[SIZE][SIZE], bool C[SIZE][SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			for (int k = 0; k < SIZE; k++)
			{

				C[i][j] = C[i][j] || A[i][j] && B[i][j];
		
			}
		}
	}
}


void TransitiveClosure(bool M[SIZE][SIZE])
{
	bool A[SIZE][SIZE], B[SIZE][SIZE];
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++){
			A[i][j] = M[i][j];
			B[i][j] = A[i][j];
		}
	}
	for( int i = 2; i <= SIZE; i++){
		MatMult(A, M, A);
		MatAdd(B, A, B); // Same as binary OR i.e. MatOr
	}
}