//  Created by Ian Field on 16/03/2011.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>

#define NUM_ROWS 2000
#define NUM_COLUMNS 50000
#define NUM_TIME_STEPS 10
#define TOP_TEMP 100
#define LEFT_TEMP 100
#define BOTTOM_TEMP 100
#define RIGHT_TEMP 100

//2D array of reservations, calloc inits to 0
//returns NULL if at any stage allocation fails
double** makeBuff(int rows, int columns){
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

//Average temp of surrounding 'atoms'
double calcTemp(double o, double t, double l, double r, double b){
	return (o + t + l + r + b) / (double)5;
}

int main(int argc, char **argv) {
	int i, j, k;
	double curVal, topVal, leftVal, rightVal, bottomVal;
	double **grid, **grid_new;//, **temp;
	int flag=1;
	time_t t1, t2;//used to time the application
	//reserve the grid in memory
	//referenced in C convention order array[rows][columns]
	grid = makeBuff(NUM_ROWS, NUM_COLUMNS);
	grid_new = makeBuff(NUM_ROWS, NUM_COLUMNS);
	
	//should memory allocation fail at any stage the program should display an error and exit
	if(grid == NULL || grid_new == NULL){
		printf("Memory allocation failure. Fatal!\n");
		return -1;//return status -1 to inform operating system the program did not execute as expected.
	}
	time(&t1);
	
	//k row, j column, optimised loop with greater iterations inernally
	for(i = 0; i < NUM_TIME_STEPS; i++){
		for(k = 0; k < NUM_ROWS; k++){	
			for(j = 0; j < NUM_COLUMNS; j++){			
				//Do calculation
				if(k==0){
					//top row so use ambient top value
					topVal = TOP_TEMP;
				}else{
					//internal top value
					if(flag==1){
						topVal = grid[k-1][j];
					}else{
						topVal = grid_new[k-1][j];
					}
				}
				
				if(k==NUM_ROWS-1){
					//bottom row so use ambient bottom value
					bottomVal = BOTTOM_TEMP;
				}else{
					//internal bottom value
					if(flag==1){
						bottomVal = grid[k+1][j];
					}else{
						bottomVal = grid_new[k+1][j];
					}
				}
				
				if(j==0){
					//left column so use ambient left value
					leftVal = LEFT_TEMP;
				}else{
					//internal left value
					if(flag==1){
						leftVal = grid[k][j-1];
					}else{
						leftVal = grid_new[k][j-1];
					}
				}
				
				
				if(j==NUM_COLUMNS-1){
					//right column so use ambient right value
					rightVal = RIGHT_TEMP;
				}else{
					//internal right value
					if(flag==1){
						rightVal = grid[k][j+1];
					}else{
						rightVal = grid_new[k][j+1];
					}
				}
				//do actual calculation. Inline has reduced overhead and more efficiency than function call.
				if(flag==1){
					curVal = grid[k][j];
					grid_new[k][j] = (curVal+topVal+leftVal+bottomVal+rightVal) / 5;
				}
				else{
					curVal = grid_new[k][j];
					grid[k][j] = (curVal+topVal+leftVal+bottomVal+rightVal) / 5;
				}
				
			}
		}
		//used to switch T and T-1
		if (flag == 1){
			flag = 0; 
		}else{ 
			flag = 1;
		}
	}
	time(&t2);
	printf("Time taken: %d seconds.\n", (int)(t2-t1));
	// print results
	/*
	printf("Results!\n");
	
	for(j = 0; j < NUM_ROWS; j++){
		for(k = 0; k < NUM_COLUMNS; k++){
			printf("%1.2f ", grid_new[j][k]);
		}
		printf("\n");
	}
	printf("End of Results!\n");
	 */
	
	//double failsafe for freeing memory
	//Free memory
	if(grid_new != NULL){
		for(i = 0; i < NUM_ROWS; i++){
			if(grid_new[i] != NULL){
				free(grid_new[i]);
			}
		}
		free(grid_new);
	}
	//free memory
	if(grid != NULL){
		//Free memory again
		for(i = 0; i < NUM_ROWS; i++){
			if(grid[i] != NULL){
				free(grid[i]);
			}
		}
		free(grid);
	}
	//inform the operating system that the program executed as expected
	return 0;
}
