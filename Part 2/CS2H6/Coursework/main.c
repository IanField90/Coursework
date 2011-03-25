//  Created by Ian Field on 16/03/2011.
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define NUM_ROWS 50 //20k
#define NUM_COLUMNS 50 //5k
#define NUM_TIME_STEPS 1000

//2D array of reservations, calloc inits to 0
float** makeBuff(int columns, int rows){
	int i;
	float** ret;
	ret = (float**) calloc(rows, sizeof(float*));
	if(ret == NULL){
		printf("Row alloc fault\n");
	}
	else{
		for(i = 0; i<rows; i++){
			ret[i] = (float*) calloc(columns, sizeof(float));
			if(ret[i] == NULL){
				printf("Column alloc fault\n");
			}
		}
	}
	return ret;
}

//a single column
float* makeCol(){
	float* ret;
	ret = (float*)calloc(NUM_ROWS, sizeof(float));
	if(ret == NULL){
		printf("Inner column alloc failure");
	}
	return ret;
}

//Top left is 5.0
void setFixedTemp(float **grid){
	grid[0][0] = 5.0;
}

//Average temp of surrounding 'atoms'
float calcTemp(float o, float t, float l, float r, float b, int divisor){
	return (o + t + l + r + b) / (float)divisor;
}

int main(int argc, char **argv) {
	int NoProc, ID, i, j, k, divisor;
	float curVal, topVal, leftVal, rightVal, bottomVal;
	float **grid, **recBuff, **sendBuff;
	float *leftCol = NULL, *rightCol = NULL;
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
		
		leftCol = makeCol();
		rightCol = makeCol();
		//TODO Send to each node the left and right columns
		
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
				
				if(bottomVal == -1){
					bottomVal = 0;
				}else{
					bottomVal = recBuff[k+1][j];
				}

				//TODO 'inner edges' not if -1 as that is 
				if(leftVal == -1){
					leftVal = 0;
				}else{
					//left inner
					if(j == 0){
						//get value from leftCol
						//leftVal = leftCol[k];
					}else{
						leftVal = recBuff[k][j-1];
					}
				}
				
				
				if(rightVal == -1){
					rightVal = 0;
				}else{
					//right inner
					if(j == NUM_COLUMNS / NoProc - 1){
						//getValue from rightCol
						//rightVal = rightCol[k];
					}else{
						rightVal = recBuff[k][j+1];
					}
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
	if(sendBuff != NULL){
		for(i = 0; i < NUM_ROWS; i++){
			if(sendBuff[i] != NULL){
				free(sendBuff[i]);
			}
		}
		free(sendBuff);
	}
	if(recBuff != NULL){
		//Free memory again
		for(i = 0; i < NUM_ROWS; i++){
			if(recBuff[i] != NULL){
				free(recBuff[i]);
			}
		}
		free(recBuff);
	}
	MPI_Finalize();
}
