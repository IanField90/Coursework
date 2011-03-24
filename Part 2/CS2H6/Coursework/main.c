//  Created by Ian Field on 16/03/2011.
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define NUM_ROWS 50 //20k
#define NUM_COLUMNS 50 //5k
#define NUM_TIME_STEPS 1000

//2D array of reservations, calloc inits to 0
float** makeBuff(int rows, int columns){
	int i;
	float** ret;
	ret = (float**) calloc(columns, sizeof(float));
	for(i=0; i<columns; i++){
		ret[i] = (float*) calloc(rows, sizeof(float));
	}
	return ret;
}

//Top left is 5.0
void setFixedTemp(float **grid){
	grid[0][0] = 5.0;
}

//Average temp of surrounding 'atoms'
float calcTemp(float o, float t, float l, float r, float b, int divisor){
	return o + t + l + r + b / divisor;
}

int main(int argc, char **argv) {
	int NoProc, ID, Num, i, j, k;
	int divisor, curVal, topVal, leftVal, rightVal, bottomVal;
	float **grid, **recBuff, **sendBuff;
	MPI_Status Status;
	
	MPI_Init(&argc,&argv);	
	MPI_Comm_size(MPI_COMM_WORLD, &NoProc); 
	MPI_Comm_rank(MPI_COMM_WORLD, &ID);
	
	//If the root node
	if(ID == 0){
		grid = makeBuff(NUM_ROWS, NUM_COLUMNS); // Get the grid memory
		setFixedTemp(grid);
	}
	//Each node has T-1 and T buffers
	recBuff = makeBuff(NUM_ROWS, NUM_COLUMNS / NoProc);
	sendBuff = makeBuff(NUM_ROWS, NUM_COLUMNS / NoProc);
	
	for(i = 0; i < NUM_TIME_STEPS; i++){
		//Send out from root node
		MPI_Scatter(grid, NUM_COLUMNS / NoProc, MPI_FLOAT, 
					recBuff, NUM_COLUMNS / NoProc, MPI_FLOAT, 
					0, MPI_COMM_WORLD);
		
		//Traverse across entire section's array
		//Do calculation. j = Current column, k = Current row
		for(j = 0; j < NUM_COLUMNS / NoProc; j++){
			for(k = 0; k < NUM_ROWS; k++){
				divisor = 5;
				
				//Left node's top, bottom and grid's left corners
				if(ID == 0){
					if(k == 0){
						//top row
						divisor--;
						topVal = -1;
					}
					if(k == NUM_ROWS - 1){
						//bottom row
						divisor--;
						bottomVal = -1;
					}
					if(j == 0){
						//left column
						divisor--;
						leftVal = -1;
					}
					//corners accounted for
				}
				//Right node's top, bottom and grid's right corners
				if(ID == NoProc - 1){
					if(k == 0){
						//top row
						divisor--;
						topVal = -1;
					}
					if(k == NUM_ROWS - 1){
						//bottom row
						divisor--;
						bottomVal = -1;
					}
					if(j == NUM_COLUMNS / NoProc - 1){
						//right column
						divisor--;
						rightVal = -1;
					}
					//corners accounted for
				}
				
				//Do calculation
				if(topVal == -1){
					topVal = 0;
				}else{
					topVal = recBuff[k-1][j];
				}
				
				if(leftVal == -1){
					leftVal = 0;
				}else{
					leftVal = recBuff[k][j-1];
				}
				
				if(bottomVal == -1){
					bottomVal = 0;
				}else{
					bottomVal = recBuff[k+1][j];
				}
				
				if(rightVal == -1){
					rightVal = 0;
				}else{
					rightVal = recBuff[k][j+1];
				}
				
				curVal = recBuff[k][j];
				sendBuff[k][j] = calcTemp(curVal, topVal, leftVal, bottomVal, rightVal, divisor);
			}
		}
		
		//Receive at root node
		MPI_Gather(sendBuff, NUM_COLUMNS / NoProc, MPI_FLOAT,
				   grid, NUM_COLUMNS / NoProc, MPI_FLOAT,
				   0, MPI_COMM_WORLD);
	}
	// print results
	if(ID == 0){
		//print
		printf("Results!\n");
		
		for(j = 0; j < NUM_ROWS; j++){
			for(k = 0; k < NUM_COLUMNS; k++){
				printf("%1.2f ", grid[j][k]);
			}
			printf("\n");
		}
		printf("End of Results!\n");
	}
	
	//Free memory again
	free(grid);
	free(recBuff);
	free(sendBuff);
	MPI_Finalize();
}
