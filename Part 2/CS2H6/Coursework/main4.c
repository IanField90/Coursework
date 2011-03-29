//  Created by Ian Field on 16/03/2011.
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

#define NUM_ROWS 30 //20000
#define NUM_COLUMNS 30 //5000
#define NUM_TIME_STEPS 1000
#define TOP_TEMP 100
#define LEFT_TEMP 100
#define BOTTOM_TEMP 100
#define RIGHT_TEMP 100

//2D array of reservations, calloc inits to 0
double** makeBuff(int columns, int rows){
	int i;
	double** ret;
	ret = (double**) calloc(rows, sizeof(double*));
	if(ret == NULL){
		return NULL;
	}
	else{
		for(i = 0; i<rows; i++){
			ret[i] = (double*) calloc(columns, sizeof(double));
			if(ret[i] == NULL){
				return NULL;
			}
		}
	}
	return ret;
}

//a single column
double* makeCol(){
	double* ret;
	ret = (double*)calloc(NUM_ROWS, sizeof(double));
	if(ret == NULL){
		return NULL;
	}
	return ret;
}

//Average temp of surrounding 'atoms'
double calcTemp(double o, double t, double l, double r, double b){
	return (o + t + l + r + b) / 5;
}

//BUG - Every ID-1th Column is 0.00

int main(int argc, char **argv) {
	int NoProc, ID, i, j, k, divisor;
	double curVal, topVal, leftVal, rightVal, bottomVal;
	double **grid, **grid_new;
	double *leftCol = NULL, *rightCol = NULL;
	double nodeLeft[NUM_ROWS], nodeRight[NUM_ROWS];
	int wait;
	MPI_Status Status;
	
	MPI_Init(&argc,&argv);	
	MPI_Comm_size(MPI_COMM_WORLD, &NoProc); 
	MPI_Comm_rank(MPI_COMM_WORLD, &ID);
	
	
	int generalWidth = ceil((double)NUM_COLUMNS/(double)NoProc);
	int remainder = NUM_COLUMNS % (int)ceil((double)NUM_COLUMNS/(double)NoProc);
	int actualWidth;
	if(NoProc>1){
		if(ID == NoProc-1 && remainder > 0){
			actualWidth = remainder+1; //generalWidth - remainder; ??
		}else{
			actualWidth = generalWidth;
		}
	}else{
		actualWidth = generalWidth;//1 proc
	}
	
	grid = makeBuff(actualWidth, NUM_ROWS); // Get the grid memory
	grid_new = makeBuff(actualWidth, NUM_ROWS); //get grid memory again
	leftCol = makeCol(); //reserve left col
	rightCol = makeCol(); //reserve right col
	if(grid == NULL || rightCol == NULL || leftCol == NULL || grid_new == NULL){
		printf("Memory allocation faliure! Fatal.\n");
		return -1;
	}
	
	for(i = 0; i < NUM_TIME_STEPS; i++){
		//Share data if more than one proc
		for(j=0; j<NUM_ROWS; j++){
			nodeLeft[j] = grid[j][0];
			nodeRight[j] = grid[j][actualWidth -1];
		}
		
		if(NoProc > 1){
			if(ID == 0){
				//send right col
				MPI_Ssend(nodeRight, 
						  NUM_ROWS, MPI_DOUBLE, ID+1, 0, MPI_COMM_WORLD);
				//recv right col
				MPI_Recv(rightCol, NUM_ROWS, 
						 MPI_DOUBLE,  ID+1, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
			}else if(ID == NoProc-1){
				//recv left col
				MPI_Recv(leftCol, NUM_ROWS, 
						 MPI_DOUBLE,  ID-1, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
				//send left col
				MPI_Ssend(nodeLeft, NUM_ROWS, MPI_DOUBLE, ID-1, 0, MPI_COMM_WORLD);
			}else{
				//recv left col
				MPI_Recv(leftCol, NUM_ROWS, 
						 MPI_DOUBLE,  ID-1, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
				//send left col
				MPI_Ssend(nodeLeft, NUM_ROWS, MPI_DOUBLE, ID-1, 0, MPI_COMM_WORLD);
				
				//send right col
				MPI_Ssend(nodeRight, 
						  NUM_ROWS, MPI_DOUBLE, ID + 1, 0, MPI_COMM_WORLD);
				//recv right col
				MPI_Recv(rightCol, NUM_ROWS, 
						 MPI_DOUBLE,  ID+1, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
			}
		}
		
		//Traverse across entire section's array
		//Do calculation. j = Current column, k = Current row
		for(j = 0; j < actualWidth; j++){
			for(k = 0; k < NUM_ROWS; k++){
				/*## START edges ##*/
				//only left and right nodes have left and right edges
				if(ID == 0){
					if(j == 0){
						leftVal = -1;
					}
				}
				if(ID == NoProc-1){
					if(j == actualWidth - 1){
						rightVal = -1;
					}
				}
				//all nodes have top and bottom edges
				if(k==0){
					topVal = -1;
				}
				if(k == NUM_ROWS -1){
					bottomVal = -1;
				}
				/*## END edges ##*/
				
				//Do calculation
				if(topVal == -1){
					topVal = TOP_TEMP;
				}else{
					topVal = grid[k-1][j];
				}
				
				if(bottomVal == -1){
					bottomVal = BOTTOM_TEMP;
				}else{
					bottomVal = grid[k+1][j];
				}
				
				if(leftVal == -1){
					leftVal = LEFT_TEMP;//only on left node
				}else{
					//left inner
					if(j == 0){
						//get value from leftCol
						leftVal = leftCol[k];
					}else{
						leftVal = grid[k][j-1];
					}
				}
				
				if(rightVal == -1){
					rightVal = RIGHT_TEMP;//only on right node
				}else{
					//right inner
					if(j == actualWidth - 1){
						//getValue from rightCol
						rightVal = rightCol[k];
					}else{
						rightVal = grid[k][j+1];
					}
				}
				
				curVal = grid[k][j];
				grid_new[k][j] = calcTemp(curVal, topVal, leftVal, bottomVal, rightVal);
			}
		}
		// update 'grid' to have 'grid_new' value
		for(j = 0; j < actualWidth; j++){
			for(k = 0; k < NUM_ROWS; k++){
				grid[k][j] = grid_new[k][j];
			}
		}
	}
	// print results
	wait = 1;
	if(NoProc > 1){
		for(j=0; j<NUM_ROWS; j++){
			if(ID == 0){
				//print then send
				printf("Node: %d, Row: %d - ",ID, j);
				for(k = 0; k < actualWidth; k++){
					printf("%1.2f ", grid[j][k]);
				}
				MPI_Ssend(&wait, 1, MPI_INT, ID+1, 0, MPI_COMM_WORLD);
				MPI_Recv(&wait, 1, MPI_INT,  NoProc-1, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
			}else if(ID == NoProc -1){
				//rec then print
				MPI_Recv(&wait, 1, MPI_INT,  ID-1, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
				printf("Node: %d, Row: %d - ",ID, j);
				for(k = 0; k < actualWidth; k++){
					printf("%1.2f ", grid[j][k]);
				}
				//printf("\n");
				MPI_Ssend(&wait, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
			}else{
				//rec, print then send
				MPI_Recv(&wait, 1, MPI_INT,  ID-1, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
				printf("Node: %d, Row: %d - ",ID, j);
				for(k = 0; k < actualWidth; k++){
					printf("%1.2f ", grid[j][k]);
				}
				MPI_Ssend(&wait, 1, MPI_INT, ID+1, 0, MPI_COMM_WORLD);
			}
			printf("\n");
			fflush(stdout);
			
		}
	}else{
		//just print
		 for(j = 0; j < NUM_ROWS; j++){
			 for(k = 0; k < NUM_COLUMNS; k++){
				 printf("%1.2f ", grid[j][k]);
			 }
			 printf("\n");
		 }
	}
	
	/*## Free memory again ##*/
	free(leftCol);
	free(rightCol);
	for(i = 0; i < NUM_ROWS; i++){
		free(grid_new[i]);
	}
	free(grid_new);
	for(i = 0; i < NUM_ROWS; i++){
		free(grid[i]);
	}
	free(grid);
	MPI_Finalize();
}
