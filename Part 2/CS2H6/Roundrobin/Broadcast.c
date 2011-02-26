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
	int NoProc, ID, *Buffer;

	MPI_Init(&argc,&argv);

	MPI_Comm_size(MPI_COMM_WORLD,&NoProc);
	MPI_Comm_rank(MPI_COMM_WORLD,&ID);

	Buffer = MakeBuffer(ID);

	MPI_Bcast(Buffer, BUFFERSIZE, MPI_INT, 0,  MPI_COMM_WORLD);

	printf("Process %d Buffer[0] %d\n", ID, Buffer[0]);

	free(Buffer);
	MPI_Finalize();
}
