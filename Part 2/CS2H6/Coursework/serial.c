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

//Average temp of surrounding 'atoms'
double calcTemp(double o, double t, double l, double r, double b){
	return (o + t + l + r + b) / (double)5;
}

int main(int argc, char **argv) {
	int i, j, k;
	double curVal, topVal, leftVal, rightVal, bottomVal;
	double **grid, **grid_new;//, **temp;
	int flag=1;
	time_t t1, t2;
	grid = makeBuff(NUM_COLUMNS, NUM_ROWS);
	grid_new = makeBuff(NUM_COLUMNS, NUM_ROWS);
	if(grid == NULL || grid_new == NULL){
		printf("Memory allocation failure. Fatal!\n");
		return -1;
	}
	time(&t1);
	//j column, k row
	//optimise K
	for(i = 0; i < NUM_TIME_STEPS; i++){
		for(k = 0; k < NUM_ROWS; k++){	
			for(j = 0; j < NUM_COLUMNS; j++){			
				//Do calculation
				if(k==0){
					topVal = TOP_TEMP;
				}else{
					if(flag==1){
						topVal = grid[k-1][j];
					}else{
						topVal = grid_new[k-1][j];
					}
				}
				
				if(k==NUM_ROWS-1){
					bottomVal = BOTTOM_TEMP;
				}else{
					if(flag==1){
						bottomVal = grid[k+1][j];
					}else{
						bottomVal = grid_new[k+1][j];
					}
				}
				
				if(j==0){
					leftVal = LEFT_TEMP;//only on left node
				}else{
					//left inner
					if(flag==1){
						leftVal = grid[k][j-1];
					}else{
						leftVal = grid_new[k][j-1];
					}
				}
				
				
				if(j==NUM_COLUMNS-1){
					rightVal = RIGHT_TEMP;//only on right node
				}else{
					if(flag==1){
						rightVal = grid[k][j+1];
					}else{
						rightVal = grid_new[k][j+1];
					}
				}
				
				if(flag==1){
					curVal = grid[k][j];
					grid_new[k][j] = (curVal+topVal+leftVal+bottomVal+rightVal) / 5;//calcTemp(curVal, topVal, leftVal, bottomVal, rightVal);
				}
				else{
					curVal = grid_new[k][j];
					grid[k][j] = (curVal+topVal+leftVal+bottomVal+rightVal) / 5;//calcTemp(curVal, topVal, leftVal, bottomVal, rightVal);
				}
				
			}
		}
//		for(j = 0; j < NUM_COLUMNS; j++){
//			for(k = 0; k < NUM_ROWS; k++){
//				grid[k][j] = grid_new[k][j];
//			}
//		}
		if (flag == 1) flag = 0; else flag = 1;
//		temp = grid; 
//		grid = grid_new; 
//		grid_new = temp;
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
	
	if(grid_new != NULL){
		for(i = 0; i < NUM_ROWS; i++){
			if(grid_new[i] != NULL){
				free(grid_new[i]);
			}
		}
		free(grid_new);
	}
	if(grid != NULL){
		//Free memory again
		for(i = 0; i < NUM_ROWS; i++){
			if(grid[i] != NULL){
				free(grid[i]);
			}
		}
		free(grid);
	}
	return 0;
}
