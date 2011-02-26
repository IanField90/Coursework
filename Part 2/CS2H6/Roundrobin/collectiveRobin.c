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
	
	MPI_Reduce(&Num, &ID, BUFFERSIZE, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	Num += ID;
	printf("Num is: %d", Num);
	
	MPI_Finalize();
}