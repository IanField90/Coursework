//  Created by Ian Field on 16/03/2011.
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define NUM_ROWS 50 //20k
#define NUM_COLLUMNS 50 //5k
#define NUM_TIME_STEPS 1000

float* makeGrid(){
	 int index;
	 float *ret;
	 ret = (float*)malloc(sizeof(float) * NUM_ROWS * NUM_COLLUMNS);
	 for (index=0; index<(NUM_ROWS * NUM_COLLUMNS); index++) {
		 ret[index] = 0; //initialise all initial temperatures to zero
	 }
	 return ret;
}

void setFixedTemp(float *grid){
	grid[0][0] = 5.0;
}

float calcTemp(float orig, float top, float left, float right, float bottom){
	return orig + top + left + right + bottom / 5;
}

int main(int argc, char **argv) {
	int NoProc, ID, Num, i, j;
	float *grid; 
	MPI_Status Status;
	
	MPI_Init(&argc,&argv);	
	MPI_Comm_size(MPI_COMM_WORLD, &NoProc); 
	MPI_Comm_rank(MPI_COMM_WORLD, &ID);
	
	//If the root node
	if(ID == 0){
		grid = makeGrid(); // Get the grid memory
		setFixedTemp(grid); //top left of grid temperature 5
	}
	
	
	/*
	//Main program loop
	for(i = 0; i < NUM_TIME_STEPS; i++){
		//Send proportion of buffer to each node
		//ID * (NUM_ROWS / NoProc); //start
		//ID+1 * (NUM_ROWS / NoProc); //finish data set
		for(j = 0; j < NUM_COLLUMNS; j++){
			
		}
	}
	*/
	//free memory again
	free(grid);
	MPI_Finalize();
}
