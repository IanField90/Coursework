#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define BUFFERSIZE 10

int* MakeBuffer(int ID, int Len)
{
	int Index;
	int* Ret;

	Ret = (int*)malloc(sizeof(int) * Len);
			
	for(Index=0;Index<Len;Index++)
		Ret[Index] = ID;
		
	return Ret;
}

int main(int argc, char **argv)
{
	int NoProc, ID, Index; 
	int *SendB;
	int *RecB;

	MPI_Init(&argc,&argv);

	MPI_Comm_size(MPI_COMM_WORLD,&NoProc);
	MPI_Comm_rank(MPI_COMM_WORLD,&ID);

	SendB = MakeBuffer(ID, BUFFERSIZE);
	if(ID == 0)
		RecB = MakeBuffer(ID, BUFFERSIZE * NoProc);
	
	MPI_Gather( SendB, BUFFERSIZE, MPI_INT,
				RecB, BUFFERSIZE, MPI_INT,
				0, MPI_COMM_WORLD);


	free(SendB);
	if(ID == 0)
	{
		for(Index=0;Index<NoProc;Index++)
			printf("Root (0) has at %d, %d\n", Index*BUFFERSIZE, RecB[Index*BUFFERSIZE]);
		free(RecB);
	}
	MPI_Finalize();
}