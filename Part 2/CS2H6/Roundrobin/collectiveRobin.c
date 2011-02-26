#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define BUFFERSIZE 1024

 int* makeBuffer(int ID){
 int index;
 int* ret;
 ret = (int*)malloc(sizeof(int) * BUFFERSIZE);
 
 for (index=0; index<BUFFERSIZE; index++) {
 ret[index] = ID;
 }
 return ret;
 }

int main(int argc, char **argv) {
	int NoProc, ID, Num; 
	MPI_Status Status;
	
	MPI_Init(&argc,&argv);
	
	MPI_Comm_size(MPI_COMM_WORLD, &NoProc); 
	MPI_Comm_rank(MPI_COMM_WORLD, &ID);
	
	
	if(ID == 0){
		Num = 0;
		MPI_Send(&Num, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
	}
	else {
		MPI_Recv(&Num, 1, MPI_INT, ID-1, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
		Num += ID;
		if (ID+1 < NoProc)
			MPI_Send(&Num, 1, MPI_INT, ID+1, 0, MPI_COMM_WORLD);
	}
	
	printf("I am %d/%d Num = %d\n", ID, NoProc, Num);
	
	MPI_Finalize();
}