//  Created by Ian Field on 16/03/2011.
#include <stdio.h>
#include <stdlib.h>

#define NUM_ROWS 4 //20k
#define NUM_COLUMNS 5 //5k
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
		printf("Row alloc fault\n");
	}
	else{
		for(i = 0; i<rows; i++){
			ret[i] = (double*) calloc(columns, sizeof(double));
				if(ret[i] == NULL){
					printf("Column alloc fault\n");
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
	int divisor, i, j, k;
	double curVal, topVal, leftVal, rightVal, bottomVal;
	double **grid, **grid_new;
	printf("about to allocate grid\n");
	grid = makeBuff(NUM_COLUMNS, NUM_ROWS);
	printf("about to allocate grid_new\n");
	grid_new = makeBuff(NUM_COLUMNS, NUM_ROWS);
	
	//j column, k row
	for(i = 0; i < NUM_TIME_STEPS; i++){
		for(j = 0; j < NUM_COLUMNS; j++){
			for(k = 0; k < NUM_ROWS; k++){
				if(j == 0){
					leftVal = -1;
				}
				if(j == (NUM_COLUMNS) - 1){
					rightVal = -1;
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
					leftVal = grid[k][j-1];
				}
				
				
				if(rightVal == -1){
					rightVal = RIGHT_TEMP;//only on right node
				}else{
					rightVal = grid[k][j+1];
				}
				
				curVal = grid[k][j];
				grid_new[k][j] = calcTemp(curVal, topVal, leftVal, bottomVal, rightVal);
				
			}
		}
		for(j = 0; j < NUM_COLUMNS; j++){
			for(k = 0; k < NUM_ROWS; k++){
				grid[k][j] = grid_new[k][j];
			}
		}
	}

	
	// print results
	printf("Results!\n");
	
	for(j = 0; j < NUM_ROWS; j++){
		for(k = 0; k < NUM_COLUMNS; k++){
			printf("%1.2f ", grid_new[j][k]);
		}
		printf("\n");
	}
	printf("End of Results!\n");
	
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
