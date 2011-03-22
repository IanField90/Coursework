//  Created by Ian Field on 16/03/2011.
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define NUM_ROWS 50 //20k
#define NUM_COLUMNS 50 //5k
#define NUM_TIME_STEPS 1000

float* makeBuff(int rows, int columns){
	 int index;
	 float *ret;
	 ret = (float*)malloc(sizeof(float) * rows * columns);
	 for (index = 0; index < (rows * columns); index++) {
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
	float *grid, *recBuff, *sendBuff;
	float *zeroCol;
	MPI_Status Status;
	
	MPI_Init(&argc,&argv);	
	MPI_Comm_size(MPI_COMM_WORLD, &NoProc); 
	MPI_Comm_rank(MPI_COMM_WORLD, &ID);
	
	//If the root node
	if(ID == 0){
		grid = makeBuff(NUM_ROWS, NUM_COLUMNS); // Get the grid memory
		setFixedTemp(grid); //top left of grid temperature 5
		//all nodes have their own section
		recBuff = makeBuff(NUM_ROWS, NUM_COLUMNS / NoProc);
	}
	
	sendBuff = makeBuff(NUM_ROWS, NUM_COLUMNS / NoProc);
	
	for(i = 0; i < NUM_TIME_STEPS; i++){
		//Send out from root node
		MPI_Scatter(grid, NUM_COLUMNS / NoProc, MPI_FLOAT, 
					recBuff, NUM_COLUMNS / NoProc, MPI_FLOAT, 
					0, MPI_COMM_WORLD);
				
		//Top and bottom rows always 0
		//Left and right values relative to the COLUMNS
		//"leftmost" node
		if(ID == 0){
			if(ID+1 <= NoProc){
				//Left = column of 0's
				//Right =
				grid[0][ID+1 * (NUM_COLLUNS / NoProc)]);
			}
		}
		
		//Rightmost node
		if(ID == NoProc-1){
			if(ID-1 >= 0){
				
			}
		}
		
		//All nodes get the same top and bottom fillers (0 temp)
		
					  
		//Receive at root node
		MPI_Gather(sendBuff, NUM_COLUMNS / NoProc, MPI_FLOAT,
				   grid, NUM_COLUMNS / NoProc, MPI_FLOAT,
				   0, MPI_COMM_WORLD);
	}
	//free memory again
	free(grid);
	MPI_Finalize();
}
