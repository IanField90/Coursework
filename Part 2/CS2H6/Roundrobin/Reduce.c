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
		Ret[Index] = ID;
		
	return Ret;
}

int main(int argc, char **argv)
{
	int NoProc, ID; 
	int *SendB, *RecB;

	MPI_Init(&argc,&argv);

	MPI_Comm_size(MPI_COMM_WORLD,&NoProc);
	MPI_Comm_rank(MPI_COMM_WORLD,&ID);

	SendB = MakeBuffer(ID);
	RecB = MakeBuffer(ID);

	MPI_Reduce(SendB, RecB, BUFFERSIZE, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if(ID == 0)
		printf("Process %d Buffer[0] %d Buffer[1] %d\n", ID, RecB[0], RecB[1]);

	free(RecB);
	free(SendB);
	MPI_Finalize();
}
