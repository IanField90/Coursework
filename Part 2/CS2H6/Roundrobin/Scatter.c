#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define BUFFERSIZE 1024

int* MakeBuffer(int ID)
{
	int Index;
	int* Ret;

	Ret = (int*)malloc(sizeof(int) * BUFFERSIZE);
			
	for(Index=0;Index<BUFFERSIZE;Index++)
	{
		if(ID == 0)
			Ret[Index] = Index;
		else
			Ret[Index] = -1;
	}
	
	return Ret;
}

int main(int argc, char **argv)
{
	int NoProc, ID; 
	int *SendB;
	int *RecB;

	MPI_Init(&argc,&argv);

	MPI_Comm_size(MPI_COMM_WORLD,&NoProc);
	MPI_Comm_rank(MPI_COMM_WORLD,&ID);

	SendB = MakeBuffer(ID);
	RecB = MakeBuffer(ID);

	MPI_Scatter(SendB, 100, MPI_INT,	
				RecB, 100, MPI_INT, 
				0, MPI_COMM_WORLD);
	
	printf("Process %d Buffer[0] %d\n", ID, RecB[0]);

	free(SendB);
	free(RecB);
	MPI_Finalize();
}
