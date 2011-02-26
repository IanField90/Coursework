#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define BUFFERSIZE 1024

/*
int* makeBuffer(int ID){
	int index;
	int* ret;
	ret = (int*)malloc(sizeof(int) * BUFFERSIZE);
	
	for (index=0; index<BUFFERSIZE; index++) {
		ret[index] = ID;
	}
	return ret;
}
*/

int main(int argc, char **argv) {
	int NoProc, ID, Num; 
	MPI_Status Status;
	
	MPI_Init(&argc,&argv);
	
	MPI_Comm_size(MPI_COMM_WORLD, &NoProc); 
	MPI_Comm_rank(MPI_COMM_WORLD, &ID);
	
	
	if(ID == 0){
		Num = 0;
		printf("Process ID: %d. Num: %d\n", ID, Num);
		MPI_Send(&Num, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		MPI_Recv(&Num, 1, MPI_INT, NoProc-1, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
		printf("Final resutl is: %s\n", Num);
	}
	else {
		MPI_Recv(&Num, 1, MPI_INT, ID-1, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
		Num += ID;
		printf("Process ID: %d. Num: %d\n", ID, Num);
		if (ID+1 < NoProc)
			MPI_Send(&Num, 1, MPI_INT, ID+1, 0, MPI_COMM_WORLD);
		else {
			MPI_Send(&Num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		}

	}

	
	MPI_Finalize();
}

/*
 1) Write an MPI program to sum the processes ID of all processes. 
 Each process should print its processes ID and current sum before passing the token on.
 2) Write an MPI program to sum the processes ID of all processes 
 using the reduce collective communication function.
*/
