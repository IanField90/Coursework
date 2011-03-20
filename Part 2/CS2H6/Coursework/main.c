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
	 for (index = 0; index < (NUM_ROWS * NUM_COLLUMNS); index++) {
		 ret[index] = 0; //initialise all initial temperatures to zero
	 }
	 return ret;
}

float* makeSection(int NoProc){
	int index;
	float *ret;
	ret = (float*)malloc(sizeof(float) * NUM_COLLUMNS / NoProc);
	for (index = 0; index < (NUM_COLLUMNS / NoProc); index++){
		ret[index] = 0; //initialise all allocated memory to 0
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
	float *grid, *recBuff, *sendBuff; 
	MPI_Status Status;
	
	MPI_Init(&argc,&argv);	
	MPI_Comm_size(MPI_COMM_WORLD, &NoProc); 
	MPI_Comm_rank(MPI_COMM_WORLD, &ID);
	
	//If the root node
	if(ID == 0){
		grid = makeGrid(); // Get the grid memory
		setFixedTemp(grid); //top left of grid temperature 5
	}
	
	//all nodes have their own section
	recBuff = makeSection(NoProc);
	sendBuff = makeSection(NoProc);
	
	for(i = 0; i < NUM_TIME_STEPS; i++){
		//Send out 
		MPI_Scatter(grid, NUM_COLLUMNS / NoProc, MPI_FLOAT, 
					recBuff, NUM_COLLUMNS / NoProc, MPI_FLOAT, 
					0, MPI_COMM_WORLD);
		
		//get back in root node
	}
	//free memory again
	free(grid);
	MPI_Finalize();
}
