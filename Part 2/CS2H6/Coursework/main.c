//  Created by Ian Field on 16/03/2011.
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

#define NUM_ROWS 2000 //2000
#define NUM_COLUMNS 50000 //50000
#define NUM_TIME_STEPS 1000
#define TOP_TEMP 100
#define LEFT_TEMP 100
#define BOTTOM_TEMP 100
#define RIGHT_TEMP 100

//2D array of reservations, calloc inits to 0
//follows C convention of x[rows][cols]
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
	//At any stage if memory allocation fails NULL is returned
	return ret;
}

//a single column
double* makeCol(){
	double* ret;
	ret = (double*)calloc(NUM_ROWS, sizeof(double));
	if(ret == NULL){
		return NULL;
	}
	//At any stage if memory allocation fails NULL is returned
	return ret;
}

int main(int argc, char **argv) {
	int NoProc, ID, i, j, k; //counters and MPI variables
	double curVal, topVal, leftVal, rightVal, bottomVal; //store information for calculation in timestep
	double **grid, **grid_new; //2 grids, T-1 and T
	double *leftCol = NULL, *rightCol = NULL;//Store adjacent columns
	double nodeLeft[NUM_ROWS], nodeRight[NUM_ROWS];//store nodes edge columns
	int wait, flag=1;//wait used in printing, Flag used to switch T and T-1 during each timestep
	MPI_Status Status;//Used to store the status of send and recv
	
	MPI_Init(&argc,&argv);//Sets the MPI cluster up
	MPI_Comm_size(MPI_COMM_WORLD, &NoProc); //Queries how many cores are in use
	MPI_Comm_rank(MPI_COMM_WORLD, &ID);//Queries which ID this core has.
	
	
	int generalWidth = ceil((double)NUM_COLUMNS/(double)NoProc); //Calculate the generalWidth to split by
	int remainder = NUM_COLUMNS % (int)ceil((double)NUM_COLUMNS/(double)(NoProc));//remainder after split
	int actualWidth;//The actual width for this core
	if(NoProc>1){
		if(ID == NoProc-1 && remainder > 0){
			actualWidth = remainder;//End core gets remainder as actualWidth
		}else{
			actualWidth = generalWidth;//everything else gets generalWidth
		}
	}else{
		actualWidth = generalWidth;//1 core gets all if only 1
	}
	
	grid = makeBuff(actualWidth, NUM_ROWS); // Get the grid memory
	grid_new = makeBuff(actualWidth, NUM_ROWS); //get grid memory again
	leftCol = makeCol(); //reserve left col
	rightCol = makeCol(); //reserve right col
	//Exit if memory allocation fails
	if(grid == NULL || rightCol == NULL || leftCol == NULL || grid_new == NULL){
		printf("Memory allocation faliure! Fatal.\n");
		return -1;
	}
	//Do this NUM_TIME_STEPS times
	for(i = 0; i < NUM_TIME_STEPS; i++){
		//if not just 1 core
		if(NoProc > 1){
			//Share data if more than one proc
			for(j=0; j<NUM_ROWS; j++){
				//prepare data to send
				if(flag==1){
					nodeLeft[j] = grid[j][0];
					nodeRight[j] = grid[j][actualWidth -1];
				}else{
					nodeLeft[j] = grid_new[j][0];
					nodeRight[j] = grid_new[j][actualWidth -1];
				}
			}
			if(ID == 0){
				//send node's right col
				MPI_Ssend(nodeRight, NUM_ROWS, MPI_DOUBLE, ID+1, 0, MPI_COMM_WORLD);
				//recv adjacent right col
				MPI_Recv(rightCol, NUM_ROWS, MPI_DOUBLE, ID+1, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
			}else if(ID == NoProc-1){
				//recv node's left col
				MPI_Recv(leftCol, NUM_ROWS, MPI_DOUBLE, ID-1, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
				//send adjacent left col
				MPI_Ssend(nodeLeft, NUM_ROWS, MPI_DOUBLE, ID-1, 0, MPI_COMM_WORLD);
			}else{
				//recv adjacent left col
				MPI_Recv(leftCol, NUM_ROWS, MPI_DOUBLE, ID-1, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
				//send node's left col
				MPI_Ssend(nodeLeft, NUM_ROWS, MPI_DOUBLE, ID-1, 0, MPI_COMM_WORLD);
				
				//send node's right col
				MPI_Ssend(nodeRight, NUM_ROWS, MPI_DOUBLE, ID+1, 0, MPI_COMM_WORLD);
				//recv adjacent right col
				MPI_Recv(rightCol, NUM_ROWS, MPI_DOUBLE, ID+1, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
			}
		}
		
		//Traverse across entire section's array
		//Do calculation. j = Current column, k = Current row
		for(k = 0; k < NUM_ROWS; k++){
			for(j = 0; j < actualWidth; j++){
				//Do calculation
				//Top row
				if(k==0){
					topVal = TOP_TEMP;
				}else{
					if(flag==1){
						topVal = grid[k-1][j];
					}else{
						topVal = grid_new[k-1][j];
					}
				}
				//bottom row
				if(k==NUM_ROWS-1){
					bottomVal = BOTTOM_TEMP;
				}else{
					if(flag==1){
						bottomVal = grid[k+1][j];
					}else{
						bottomVal = grid_new[k+1][j];
					}
				}
				//Only left node uses ambient temperature for left col
				if((j==0) && (ID == 0)){
					leftVal = LEFT_TEMP;//only on left node
				}else{
					//left inner
					if(j == 0){
						//get value from leftCol
						leftVal = leftCol[k];
					}else{
						//use left values within the grid
						if(flag==1){
							leftVal = grid[k][j-1];
						}else{
							leftVal = grid_new[k][j-1];
						}
					}
				}
				
				//Only right node uses ambient temperature for right col
				if((j==actualWidth-1) && (ID == NoProc-1)){
					rightVal = RIGHT_TEMP;//only on right node
				}else{
					//right inner
					if(j == actualWidth - 1){
						//getValue from rightCol
						rightVal = rightCol[k];
					}else{
						//use right values within grid
						if(flag==1){
							rightVal = grid[k][j+1];
						}else{
							rightVal = grid_new[k][j+1];
						}
					}
				}
				
				//Inline calculations faster than function call
				if(flag==1){
					curVal = grid[k][j];
					grid_new[k][j] = (curVal + topVal + leftVal + bottomVal + rightVal) / 5;
				}else{
					curVal = grid_new[k][j];
					grid[k][j] = (curVal + topVal + leftVal + bottomVal + rightVal) / 5;
				}
			}
		}
		// update 'grid' to have 'grid_new' value V.Slow (100million assignments)
//		for(j = 0; j < actualWidth; j++){
//			for(k = 0; k < NUM_ROWS; k++){
//				grid[k][j] = grid_new[k][j];
//			}
//		}
		//pointer Swapping. Still not optimum but only 3 assignments vs 100million.
//		temp = grid; 
//		grid = grid_new; 
//		grid_new = temp;
		
		//Flag is most efficient version of dealing with T-1 becoming T
		if (flag == 1) 
			flag = 0; 
		else 
			flag = 1;
	}
//	// print results
//	wait = 1;
//	if(NoProc > 1){
//		for(j=0; j<NUM_ROWS; j++){
//			if(ID == 0){
//				//print then send
//				printf("Node: %d, Row: %d - ",ID, j);
//				for(k = 0; k < actualWidth; k++){
//					printf("%1.2f ", grid[j][k]);
//				}
//				MPI_Ssend(&wait, 1, MPI_INT, ID+1, 0, MPI_COMM_WORLD);
//				MPI_Recv(&wait, 1, MPI_INT,  NoProc-1, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
//			}else if(ID == NoProc -1){
//				//rec then print
//				MPI_Recv(&wait, 1, MPI_INT,  ID-1, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
//				printf("Node: %d, Row: %d - ",ID, j);
//				for(k = 0; k < actualWidth; k++){
//					printf("%1.2f ", grid[j][k]);
//				}
//				//printf("\n");
//				MPI_Ssend(&wait, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
//			}else{
//				//rec, print then send
//				MPI_Recv(&wait, 1, MPI_INT,  ID-1, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
//				printf("Node: %d, Row: %d - ",ID, j);
//				for(k = 0; k < actualWidth; k++){
//					printf("%1.2f ", grid[j][k]);
//				}
//				MPI_Ssend(&wait, 1, MPI_INT, ID+1, 0, MPI_COMM_WORLD);
//			}
//			printf("\n");
//			fflush(stdout);
//			
//		}
//	}else{
//		//just print
//		for(j = 0; j < NUM_ROWS; j++){
//			for(k = 0; k < NUM_COLUMNS; k++){
//		 		printf("%1.2f ", grid[j][k]);
//		 	}
//		 	printf("\n");
//		}
//	}
	
	/*## Free memory again ##*/
	free(leftCol);
	free(rightCol);
	//Each row must be freed first
	for(i = 0; i < NUM_ROWS; i++){
		free(grid_new[i]);
	}
	free(grid_new);
	for(i = 0; i < NUM_ROWS; i++){
		free(grid[i]);
	}
	free(grid);
	MPI_Finalize();//Allow MPI Runner to know the status of the exit
}
